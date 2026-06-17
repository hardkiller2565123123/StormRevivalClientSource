#include "StdInc.h"
#include "AssetDecodePipeline.h"
#include "AssetPreviewResolver.h"
#include "AssetPreview.h"
#include "AssetTextureInfo.h"
#include "XfbinInspector.h"
#include "AssetNuccDecoder.h"
#include "AssetNotification.h"
#include "Logger.h"

#include <filesystem>
#include <fstream>
#include <sstream>

namespace
{
    AssetDecodePipeline::DecodeStats g_LastStats;

    std::string SanitizePathPart(std::string value)
    {
        for (char& c : value)
        {
            if (c == ':' || c == '*' || c == '?' || c == '"' || c == '<' || c == '>' || c == '|')
                c = '_';
        }

        return value;
    }

    std::filesystem::path OutputRoot()
    {
        return std::filesystem::path(AssetBrowser::GetDumpFolder()) / "Decoded";
    }

    std::filesystem::path OutputPathForAsset(const AssetBrowser::AssetEntry& asset)
    {
        std::string virtualPath = asset.VirtualPath.empty() ? asset.Name : asset.VirtualPath;
        virtualPath = SanitizePathPart(virtualPath);

        if (asset.IsCpkEntry && !asset.ArchivePath.empty())
        {
            std::filesystem::path archiveName = std::filesystem::path(asset.ArchivePath).filename();
            return OutputRoot() / "CPK" / archiveName / virtualPath;
        }

        if (asset.Source == AssetBrowser::AssetSource::Mod)
            return OutputRoot() / "Mods" / virtualPath;

        return OutputRoot() / "Game" / virtualPath;
    }

    bool CopyFileSafe(const std::string& from, const std::filesystem::path& to)
    {
        std::error_code ec;
        std::filesystem::create_directories(to.parent_path(), ec);
        std::filesystem::copy_file(from, to, std::filesystem::copy_options::overwrite_existing, ec);
        return !ec;
    }

    bool WriteTextFile(const std::filesystem::path& path, const std::string& text)
    {
        std::error_code ec;
        std::filesystem::create_directories(path.parent_path(), ec);

        std::ofstream file(path, std::ios::out | std::ios::trunc);

        if (!file.is_open())
            return false;

        file << text;
        return true;
    }

    bool ToolExists(const std::filesystem::path& tool)
    {
        std::error_code ec;
        return std::filesystem::exists(tool, ec) && std::filesystem::is_regular_file(tool, ec);
    }

    bool LaunchToolAndWait(const std::filesystem::path& tool, const std::string& args)
    {
        if (!ToolExists(tool))
            return false;

        STARTUPINFOA si{};
        PROCESS_INFORMATION pi{};
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;

        std::string command = "\"" + tool.string() + "\" " + args;

        if (!CreateProcessA(nullptr, command.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi))
            return false;

        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD exitCode = 1;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        return exitCode == 0;
    }

    bool TryExternalAudioDecode(const AssetBrowser::AssetEntry& asset, const std::string& inputPath, const std::filesystem::path& outputPath)
    {
        if (!AssetBrowser::IsAudioPreviewable(asset))
            return false;

        std::filesystem::path wavPath = outputPath;
        wavPath.replace_extension(".wav");

        std::error_code ec;
        std::filesystem::create_directories(wavPath.parent_path(), ec);

        const std::filesystem::path tools = AssetBrowser::GetToolsFolder();
        const std::filesystem::path vgmstreamCli = tools / "vgmstream-cli.exe";
        const std::filesystem::path vgmstreamTest = tools / "test.exe";
        const std::filesystem::path hca2wav = tools / "hca2wav.exe";
        const std::filesystem::path adx2wav = tools / "adx2wav.exe";

        if (ToolExists(vgmstreamCli) &&
            LaunchToolAndWait(vgmstreamCli, "-o \"" + wavPath.string() + "\" \"" + inputPath + "\"") &&
            std::filesystem::exists(wavPath, ec))
        {
            return true;
        }

        if (ToolExists(vgmstreamTest) &&
            LaunchToolAndWait(vgmstreamTest, "-o \"" + wavPath.string() + "\" \"" + inputPath + "\"") &&
            std::filesystem::exists(wavPath, ec))
        {
            return true;
        }

        if (asset.Extension == ".hca" &&
            ToolExists(hca2wav) &&
            LaunchToolAndWait(hca2wav, "\"" + inputPath + "\" \"" + wavPath.string() + "\"") &&
            std::filesystem::exists(wavPath, ec))
        {
            return true;
        }

        if (asset.Extension == ".adx" &&
            ToolExists(adx2wav) &&
            LaunchToolAndWait(adx2wav, "\"" + inputPath + "\" \"" + wavPath.string() + "\"") &&
            std::filesystem::exists(wavPath, ec))
        {
            return true;
        }

        return false;
    }

    std::string BuildDecodeReport(const AssetBrowser::AssetEntry& asset, const std::string& inputPath, const std::filesystem::path& outputPath)
    {
        std::ostringstream out;
        out << "Naruto Storm 4 Asset Decode Report\n";
        out << "===================================\n";
        out << "Name: " << asset.Name << "\n";
        out << "Virtual Path: " << asset.VirtualPath << "\n";
        out << "Extension: " << asset.Extension << "\n";
        out << "Source: " << AssetBrowser::SourceName(asset.Source) << "\n";
        out << "Input: " << inputPath << "\n";
        out << "Output: " << outputPath.string() << "\n";
        out << "CPK Entry: " << (asset.IsCpkEntry ? "yes" : "no") << "\n";

        if (asset.IsCpkEntry)
        {
            out << "Archive: " << asset.ArchivePath << "\n";
            out << "Entry: " << asset.ArchiveEntryPath << "\n";
        }

        AssetPreview::PreviewState preview{};
        if (AssetPreview::BuildPreview(asset, preview, true))
        {
            out << "\nPreview Status: " << preview.Status << "\n";
            out << preview.Text << "\n";
        }

        if (asset.Extension == ".xfbin" || asset.Extension == ".xbin" || asset.Extension == ".nud")
        {
            AssetNuccDecoder::DecodedAsset decoded{};
            if (AssetNuccDecoder::DecodeAsset(asset, decoded, true))
            {
                out << "\n";
                out << AssetNuccDecoder::BuildReport(decoded);
            }

            XfbinInspector::XfbinInfo info{};
            if (XfbinInspector::Inspect(asset, info, true))
            {
                out << "\n";
                out << XfbinInspector::BuildReport(info);
            }
        }

        if (AssetBrowser::IsTexturePreviewable(asset))
        {
            AssetTextureInfo::TextureInfo info{};
            if (AssetTextureInfo::Inspect(asset, info, true))
            {
                out << "\nTexture Metadata\n";
                out << "----------------\n";
                out << AssetTextureInfo::BuildText(info) << "\n";
            }
        }

        if (AssetBrowser::IsAudioPreviewable(asset))
        {
            out << "\nAudio Decode\n";
            out << "------------\n";
            out << "WAV can be copied/played directly. CRI ADX/ACB/AWB/HCA decode uses optional tools in the Tools folder.\n";
            out << "Supported optional tool names: vgmstream-cli.exe, test.exe, hca2wav.exe, adx2wav.exe.\n";
        }

        return out.str();
    }

    bool DecodeOne(const AssetBrowser::AssetEntry& asset, AssetDecodePipeline::DecodeStats& stats)
    {
        ++stats.Total;
        stats.LastStatus = asset.VirtualPath.empty() ? asset.Name : asset.VirtualPath;

        std::filesystem::path outputPath = OutputPathForAsset(asset);
        std::string readablePath;

        bool copied = false;

        if (asset.IsCpkEntry)
        {
            copied = AssetBrowser::DumpAsset(asset, false);

            if (AssetPreviewResolver::ResolveReadablePath(asset, readablePath, true))
            {
                copied = CopyFileSafe(readablePath, outputPath);
            }

            if (copied)
                ++stats.Extracted;
        }
        else if (AssetPreviewResolver::ResolveReadablePath(asset, readablePath, true))
        {
            copied = CopyFileSafe(readablePath, outputPath);

            if (copied)
                ++stats.Copied;
        }

        if (!copied && readablePath.empty())
        {
            ++stats.Failed;
            WriteTextFile(outputPath.string() + ".decode_failed.txt", BuildDecodeReport(asset, readablePath, outputPath));
            return false;
        }

        bool externalDecoded = false;

        if (!readablePath.empty())
            externalDecoded = TryExternalAudioDecode(asset, readablePath, outputPath);

        if (externalDecoded)
            ++stats.ExternalDecoded;

        const bool shouldReport =
            asset.Extension == ".xfbin" ||
            asset.Extension == ".xbin" ||
            asset.Extension == ".nud" ||
            asset.Extension == ".nut" ||
            asset.Extension == ".gfx" ||
            asset.Extension == ".swf" ||
            asset.Extension == ".cpk" ||
            AssetBrowser::IsAudioPreviewable(asset) ||
            AssetBrowser::IsTexturePreviewable(asset);

        if (shouldReport)
        {
            if (WriteTextFile(outputPath.string() + ".decode_report.txt", BuildDecodeReport(asset, readablePath, outputPath)))
                ++stats.Reported;
        }

        if (!externalDecoded && AssetBrowser::IsAudioPreviewable(asset) && asset.Extension != ".wav")
            ++stats.Unsupported;

        ++stats.Decoded;
        return true;
    }
}

namespace AssetDecodePipeline
{
    bool DecodeAsset(const AssetBrowser::AssetEntry& asset)
    {
        DecodeStats stats{};
        stats.OutputRoot = OutputRoot().string();
        bool ok = DecodeOne(asset, stats);
        g_LastStats = stats;

        AssetNotification::PushInfo("Decode", ok ? "Asset decoded/extracted." : "Asset decode failed.");
        return ok;
    }

    DecodeStats DecodeSelectedAssets(const std::vector<AssetBrowser::AssetEntry>& assets)
    {
        DecodeStats stats{};
        stats.OutputRoot = OutputRoot().string();

        for (const auto& asset : assets)
            DecodeOne(asset, stats);

        g_LastStats = stats;
        AssetNotification::PushInfo("Decode", "Decoded selected assets: " + std::to_string(stats.Decoded));
        Logger::Info("AssetDecodePipeline selected decode finished count=" + std::to_string(stats.Decoded));
        return g_LastStats;
    }

    DecodeStats DecodeAllAssets()
    {
        DecodeStats stats{};
        stats.OutputRoot = OutputRoot().string();

        const auto assets = AssetBrowser::GetAssets();

        for (const auto& asset : assets)
            DecodeOne(asset, stats);

        g_LastStats = stats;
        AssetNotification::PushInfo("Decode", "Decoded all indexed assets: " + std::to_string(stats.Decoded));
        Logger::Info("AssetDecodePipeline full decode finished count=" + std::to_string(stats.Decoded));
        return g_LastStats;
    }

    const DecodeStats& GetLastStats()
    {
        return g_LastStats;
    }

    std::string BuildLastReport()
    {
        std::ostringstream out;
        out << "Decode output: " << g_LastStats.OutputRoot << "\n";
        out << "Total: " << g_LastStats.Total << "\n";
        out << "Decoded: " << g_LastStats.Decoded << "\n";
        out << "Extracted: " << g_LastStats.Extracted << "\n";
        out << "Copied: " << g_LastStats.Copied << "\n";
        out << "Reports: " << g_LastStats.Reported << "\n";
        out << "External audio decoded: " << g_LastStats.ExternalDecoded << "\n";
        out << "Need external decoder: " << g_LastStats.Unsupported << "\n";
        out << "Failed: " << g_LastStats.Failed << "\n";
        out << "Last: " << g_LastStats.LastStatus << "\n";
        return out.str();
    }
}
