#pragma once
#include "StdInc.h"

namespace SteamConfig
{
    enum class Mode
    {
        Offline,
        CustomServer,
        RevivedServer,
        SteamPassthrough
    };

    struct Config
    {
        Mode CurrentMode = Mode::Offline;
        std::string PersonaName = "NS4Revived";
        uint64_t SteamID = 76561199006065889ull;
        std::string CustomServerHost = "127.0.0.1";
        int CustomServerPort = 47584;
        bool BlockOfficialTraffic = true;
        bool LanOnly = true;
        bool LogPackets = true;
        bool EnableLocalStorage = true;
        bool EnableLocalStats = true;
        bool EnableLocalMatchmaking = true;
        bool AutoInstanceSteamID = true;
        bool AutoDetectSteamID = true;
        bool EnableEmbeddedMasterServer = true;
        std::vector<std::string> RadminPeers;
        std::vector<std::string> EvolutionFolders;
        std::vector<AppId_t> OwnedDlcAppIds;
        std::string DlcFolder;
        bool AutoDetectDlcFolder = true;
        bool EnableDlcUnlock = false;
    };

    bool Init();
    bool Load();
    bool Save();

    const Config& Get();
    Config& Mutable();

    bool IsOffline();
    bool IsCustomServer();
    bool IsRevivedServer();
    bool ShouldBlockOfficialTraffic();
    bool IsLanOnly();
    bool IsDlcUnlockEnabled();
    void SetDlcUnlockEnabled(bool enabled);
    bool IsOwnedDlc(AppId_t appID);
    bool HasDlcContentOnDisk();
    bool IsDlcInstalledOnDisk(AppId_t appID);
    bool IsDlcAvailable(AppId_t appID);
    const std::string& GetDlcFolder();
    std::string GetGameFolder();
    std::vector<std::string> GetDlcContentProbePaths();
    std::vector<std::string> GetRadminPeers();
    std::vector<std::string> GetEvolutionFolders();
    std::string GetDlcInstallDir(AppId_t appID);

    std::string GetString(const char* key, const char* fallback);
    bool GetBool(const char* key, bool fallback);

    const std::string& GetPath();
    const char* ModeName(Mode mode);
}
