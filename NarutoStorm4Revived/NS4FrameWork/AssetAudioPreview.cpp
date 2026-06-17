#include "StdInc.h"
#include "AssetAudioPreview.h"
#include "AssetPreviewResolver.h"
#include "AssetPreview.h"
#include "imgui.h"

#include <mmsystem.h>
#include <sstream>

namespace
{
    using PlaySoundA_t = BOOL(WINAPI*)(LPCSTR, HMODULE, DWORD);

    PlaySoundA_t ResolvePlaySound()
    {
        static HMODULE winmm = LoadLibraryA("winmm.dll");
        static PlaySoundA_t playSound = winmm ? reinterpret_cast<PlaySoundA_t>(GetProcAddress(winmm, "PlaySoundA")) : nullptr;
        return playSound;
    }

    bool IsPlayableWave(const AssetBrowser::AssetEntry& asset)
    {
        return asset.Extension == ".wav";
    }

    std::string BuildAudioInfo(const std::string& path, const AssetBrowser::AssetEntry& asset)
    {
        std::vector<unsigned char> bytes;
        AssetPreview::ReadBytes(path, bytes, 256 * 1024);

        std::ostringstream out;
        out << "Audio Asset\n";
        out << "Path: " << path << "\n";
        out << "Type: " << asset.Extension << "\n";
        out << "Bytes loaded for header: " << bytes.size() << "\n";

        if (bytes.size() >= 12 && std::memcmp(bytes.data(), "RIFF", 4) == 0 && std::memcmp(bytes.data() + 8, "WAVE", 4) == 0)
        {
            out << "Container: RIFF WAVE\n";
            out << "Preview: can play directly through Windows audio\n";
        }
        else if (asset.Extension == ".adx")
        {
            out << "Container: CRI ADX stream\n";
            out << "Preview: needs ADX decode hook or external CRI decoder before direct playback\n";
        }
        else if (asset.Extension == ".acb" || asset.Extension == ".awb" || asset.Extension == ".hca")
        {
            out << "Container: CRI audio bank/stream\n";
            out << "Preview: indexed here; direct playback needs CRI/HCA decode support\n";
        }
        else if (asset.Extension == ".ogg")
        {
            out << "Container: OGG stream\n";
            out << "Preview: indexed here; Windows direct playback depends on installed codecs\n";
        }

        out << "\nHeader Hex\n";
        out << AssetPreview::BuildHex(bytes, 512);
        return out.str();
    }
}

namespace AssetAudioPreview
{
    void Stop()
    {
        if (auto playSound = ResolvePlaySound())
            playSound(nullptr, nullptr, 0);
    }

    void Draw(const AssetBrowser::AssetEntry& asset, bool autoDumpBeforePreview)
    {
        std::string path;
        const bool hasFile = AssetPreviewResolver::ResolveReadablePath(asset, path, autoDumpBeforePreview);

        ImGui::Text("Audio Preview");

        if (!hasFile)
        {
            ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f), "Audio file is not readable yet.");
            return;
        }

        ImGui::TextWrapped("%s", path.c_str());

        const bool playable = IsPlayableWave(asset) && ResolvePlaySound();

        if (ImGui::Button("Play", ImVec2(80, 24)))
        {
            if (playable)
                ResolvePlaySound()(path.c_str(), nullptr, SND_FILENAME | SND_ASYNC);
        }

        ImGui::SameLine();

        if (ImGui::Button("Stop", ImVec2(80, 24)))
            Stop();

        ImGui::SameLine();

        if (!playable)
            ImGui::TextDisabled("Direct playback is ready for WAV. CRI formats need a decoder/hook pass.");

        ImGui::Separator();
        std::string info = BuildAudioInfo(path, asset);
        ImGui::BeginChild("##AudioInfo", ImVec2(0, 0), true);
        ImGui::TextWrapped("%s", info.c_str());
        ImGui::EndChild();
    }
}
