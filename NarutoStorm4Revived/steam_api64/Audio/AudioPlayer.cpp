#include "AudioPlayer.h"

#include "Logger.h"
#include "SteamDiagnostics.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

namespace
{
    constexpr const char* kAlias = "ns4revived_title_music";

    bool g_Initialized = false;
    bool g_Enabled = false;
    bool g_Playing = false;
    std::string g_Status = "not initialized";
    std::filesystem::path g_AudioFolder;
    std::filesystem::path g_TitleMusicPath;

    std::filesystem::path ExeFolder()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
    }

    std::filesystem::path RevivedFolder()
    {
        return ExeFolder() / "NarutoStorm4Revived";
    }

    std::filesystem::path AudioConfigPath()
    {
        return RevivedFolder() / "Config" / "Audio.ini";
    }

    std::string ReadString(const char* section, const char* key, const char* fallback)
    {
        char buffer[MAX_PATH]{};
        GetPrivateProfileStringA(section, key, fallback, buffer, static_cast<DWORD>(sizeof(buffer)), AudioConfigPath().string().c_str());
        return buffer;
    }

    int ReadInt(const char* section, const char* key, int fallback)
    {
        return GetPrivateProfileIntA(section, key, fallback, AudioConfigPath().string().c_str());
    }

    bool FileExists(const std::filesystem::path& file)
    {
        std::error_code ec;
        return std::filesystem::exists(file, ec) && std::filesystem::is_regular_file(file, ec);
    }

    void EnsureFolders()
    {
        std::error_code ec;
        std::filesystem::create_directories(RevivedFolder() / "Config", ec);
        ec.clear();
        std::filesystem::create_directories(g_AudioFolder, ec);
    }

    void CloseAlias()
    {
        mciSendStringA((std::string("stop ") + kAlias).c_str(), nullptr, 0, nullptr);
        mciSendStringA((std::string("close ") + kAlias).c_str(), nullptr, 0, nullptr);
        g_Playing = false;
    }

    std::string MciErrorText(MCIERROR error)
    {
        char buffer[256]{};
        if (mciGetErrorStringA(error, buffer, static_cast<UINT>(sizeof(buffer))))
            return buffer;
        return "MCI error " + std::to_string(error);
    }

    bool PlayFile(const std::filesystem::path& file, int volumePercent)
    {
        CloseAlias();

        const std::string open = "open \"" + file.string() + "\" type mpegvideo alias " + kAlias;
        MCIERROR error = mciSendStringA(open.c_str(), nullptr, 0, nullptr);
        if (error != 0)
        {
            g_Status = "open failed: " + MciErrorText(error);
            return false;
        }

        const int clampedVolume = std::clamp(volumePercent, 0, 100) * 10;
        const std::string volume = "setaudio " + std::string(kAlias) + " volume to " + std::to_string(clampedVolume);
        mciSendStringA(volume.c_str(), nullptr, 0, nullptr);

        const std::string play = "play " + std::string(kAlias) + " repeat";
        error = mciSendStringA(play.c_str(), nullptr, 0, nullptr);
        if (error != 0)
        {
            g_Status = "play failed: " + MciErrorText(error);
            CloseAlias();
            return false;
        }

        g_Playing = true;
        g_Status = "playing " + file.string();
        return true;
    }
}

namespace TitleMusicOverride
{
    bool Init()
    {
        if (g_Initialized)
            return g_Playing;

        g_Initialized = true;
        g_AudioFolder = RevivedFolder() / "Audio";
        EnsureFolders();

        g_Enabled = ReadInt("TitleMusic", "Enabled", 1) != 0;
        const std::string configuredFile = ReadString("TitleMusic", "File", "Title.mp3");
        const int volume = ReadInt("TitleMusic", "Volume", 80);
        g_TitleMusicPath = std::filesystem::path(configuredFile).is_absolute()
            ? std::filesystem::path(configuredFile)
            : g_AudioFolder / configuredFile;

        SteamDiagnostics::Mark("Audio", "Title music override init", g_TitleMusicPath.string());

        if (!g_Enabled)
        {
            g_Status = "disabled in NarutoStorm4Revived\\Config\\Audio.ini";
            Logger::Info("Title music override disabled");
            return false;
        }

        if (!FileExists(g_TitleMusicPath))
        {
            g_Status = "waiting for " + g_TitleMusicPath.string();
            Logger::Warn("Title music override file missing: " + g_TitleMusicPath.string());
            return false;
        }

        const bool played = PlayFile(g_TitleMusicPath, volume);
        if (played)
            Logger::Info("Title music override started: " + g_TitleMusicPath.string());
        else
            Logger::Warn("Title music override failed: " + g_Status);

        return played;
    }

    void Shutdown()
    {
        CloseAlias();
        if (g_Initialized)
            Logger::Info("Title music override shutdown");
        g_Initialized = false;
        g_Status = "shutdown";
    }

    bool Restart()
    {
        Shutdown();
        return Init();
    }

    bool IsEnabled()
    {
        return g_Enabled;
    }

    bool IsPlaying()
    {
        return g_Playing;
    }

    std::string AudioFolder()
    {
        if (g_AudioFolder.empty())
            g_AudioFolder = RevivedFolder() / "Audio";
        return g_AudioFolder.string();
    }

    std::string TitleMusicPath()
    {
        if (g_TitleMusicPath.empty())
            g_TitleMusicPath = RevivedFolder() / "Audio" / "Title.mp3";
        return g_TitleMusicPath.string();
    }

    std::string Status()
    {
        return g_Status;
    }
}
