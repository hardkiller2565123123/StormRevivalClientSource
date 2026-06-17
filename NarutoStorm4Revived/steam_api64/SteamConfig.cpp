#include "StdInc.h"
#include "SteamConfig.h"
#include "Logger.h"

namespace
{
    SteamConfig::Config g_Config;
    std::string g_Path;
    bool g_DlcDiskCacheValid = false;
    bool g_DlcDiskCacheValue = false;

    std::string GetExeFolder()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path().string();
    }

    std::string ReadString(const char* key, const char* fallback)
    {
        char buffer[512]{};
        GetPrivateProfileStringA("steam", key, fallback, buffer, sizeof(buffer), g_Path.c_str());
        return buffer;
    }

    int ReadInt(const char* key, int fallback)
    {
        return GetPrivateProfileIntA("steam", key, fallback, g_Path.c_str());
    }

    std::vector<AppId_t> ParseDlcList(const std::string& value)
    {
        std::vector<AppId_t> result;
        std::stringstream stream(value);
        std::string item;

        while (std::getline(stream, item, ','))
        {
            item.erase(std::remove_if(item.begin(), item.end(), [](unsigned char c)
            {
                return std::isspace(c) != 0;
            }), item.end());

            if (item.empty())
                continue;

            char* end = nullptr;
            unsigned long parsed = std::strtoul(item.c_str(), &end, 10);
            if (end && *end == '\0' && parsed > 0)
                result.push_back(static_cast<AppId_t>(parsed));
        }

        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

    std::string FormatDlcList(const std::vector<AppId_t>& appIDs)
    {
        std::string result;
        for (AppId_t appID : appIDs)
        {
            if (!result.empty())
                result += ",";
            result += std::to_string(appID);
        }
        return result;
    }




    std::vector<std::string> ParseStringList(const std::string& value)
    {
        std::vector<std::string> result;
        std::stringstream stream(value);
        std::string item;
        while (std::getline(stream, item, ','))
        {
            item.erase(item.begin(), std::find_if(item.begin(), item.end(), [](unsigned char c){ return std::isspace(c) == 0; }));
            item.erase(std::find_if(item.rbegin(), item.rend(), [](unsigned char c){ return std::isspace(c) == 0; }).base(), item.end());
            if (!item.empty())
                result.push_back(item);
        }
        std::sort(result.begin(), result.end());
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

    std::string FormatStringList(const std::vector<std::string>& values)
    {
        std::string result;
        for (const std::string& value : values)
        {
            if (value.empty())
                continue;
            if (!result.empty())
                result += ",";
            result += value;
        }
        return result;
    }

    std::string Trim(std::string value)
    {
        value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char c)
        {
            return std::isspace(c) == 0;
        }));

        value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char c)
        {
            return std::isspace(c) == 0;
        }).base(), value.end());

        return value;
    }

    std::string Lower(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });
        return value;
    }

    std::string DefaultDlcFolder()
    {
        return (std::filesystem::path(GetExeFolder()) / "dlc").string();
    }

    bool DirectoryHasAnyFiles(const std::filesystem::path& folder)
    {
        std::error_code ec;
        if (!std::filesystem::exists(folder, ec) || !std::filesystem::is_directory(folder, ec))
            return false;

        for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
        {
            if (ec)
            {
                ec.clear();
                continue;
            }

            if (it->is_regular_file(ec))
                return true;
        }

        return false;
    }

    bool FileExists(const std::filesystem::path& file)
    {
        std::error_code ec;
        return std::filesystem::exists(file, ec) && std::filesystem::is_regular_file(file, ec);
    }

    bool DirectoryExists(const std::filesystem::path& folder)
    {
        std::error_code ec;
        return std::filesystem::exists(folder, ec) && std::filesystem::is_directory(folder, ec);
    }


    bool PathContainsText(const std::filesystem::path& path, const std::string& token)
    {
        if (token.empty())
            return false;
        return Lower(path.generic_string()).find(Lower(token)) != std::string::npos;
    }

    std::string NormalizeGamePathToken(std::string token)
    {
        const size_t colon = token.find(':');
        if (colon != std::string::npos)
            token = token.substr(colon + 1);
        std::replace(token.begin(), token.end(), '/', static_cast<char>(std::filesystem::path::preferred_separator));
        return token;
    }

    bool GamePathExists(const std::filesystem::path& exeFolder, const char* token)
    {
        if (!token || !*token)
            return false;

        const std::string normalized = NormalizeGamePathToken(token);
        if (normalized.find('%') != std::string::npos)
            return false;

        const std::filesystem::path fullPath = exeFolder / normalized;
        std::error_code ec;
        return std::filesystem::exists(fullPath, ec);
    }

    const char* const* AllDlcTokens(size_t& count)
    {
        static const char* tokens[] =
        {
            "TUTORIAL_STORY_DLC2_004",
            "IsClearDlcCmnParam",
            "dlc/ep_r2b/st30_s020",
            "dlc/ep_r2b/pt11_s010",
            "dlc/ep_r2b/pt11_s020",
            "dlc/ep_r2b/pt42_s020",
            "dlc/ep_r2b/pt42_s030",
            "dlc/ep_r2b/pt42_s040",
            "dlc/ep_r2b/pt45_s010",
            "data/st/st_script_dlc.xfbin",
            "dlc/ep_gar/",
            "dlc/ep_sik/",
            "st/dlc/ep_r2b/",
            "pt/dlc/ep_r2b/",
            "dlc/ep_r2b/pt",
            "sim:data/sim/dlcpackdata.cpk",
            "DLC_ex_13",
            "DLC02_SUB_BATTLE_09",
            "DLC02_SUB_BATTLE_13",
            "DLCCheck",
            "DLCDegradeConfiurm",
            "DlcBorutoDownload",
            "DlcLimitCostumeDownload",
            "DlcCommonAddContentsDownload",
            "DLCUpdateConfiurm",
            "DisableDLC",
            "DLC_cha_050",
            "DLC_cha_052",
            "DLC_cha_054",
            "DLC_cha_051",
            "DLC_cha_044",
            "DLC_cha_047",
            "DLC_cha_053",
            "DLC_cha_059",
            "DLC_cha_056",
            "DLC_cha_064",
            "DLC_cha_055",
            "DLC_cha_068",
            "DLC_cha_072",
            "DLC_cha_069",
            "DLC_cha_070",
            "DLC_cha_067",
            "DLC_cha_071",
            "DLC_cha_063",
            "DLC_cha_042",
            "DLC_cha_081",
            "DLC_cha_079",
            "DLC_cha_080",
            "DLC_cha_075",
            "DLC_cha_073",
            "DLC_cha_014",
            "DLC_cha_017",
            "DLC_cha_019",
            "DLC_cha_022",
            "DLC_cha_026",
            "DLC_28",
            "DLC_29",
            "DLC_30",
            "DLC_44",
            "DLC_45",
            "DLC_39_Xbox",
            "DLCDegradeConf",
            "DLC_27",
            "DLC_38",
            "DLC_36_Xbox",
            "DLC_24",
            "DLC_notice_012_steam",
            "DLC_notice_014_steam",
            "DLC_notice_016_steam",
            "DLC_notice_015_steam",
            "DLC_ex_04",
            "PL_ANM_WIN_S_DLC",
            "PL_ANM_WIN_L_DLC",
            "data/no_release/message/plus_dlc/PLAT/LANG/messageInfo.bin.xfbin",
            "ClearDlcCmnParam",
            "DLC_ex_16",
            "DLC_ex_14",
            "dlc/%d",
            "BindDlcData",
            "CheckBattleCut",
            "CheckTutorial",
            "CheckHintWindow",
            "ResultCheck",
            "AskResultCheckEnd",
            "CheckLineUp",
            "CheckLineup",
            "CheckIndex",
            "ccStateShopCheckLineUp",
            "UnlockCharacterCheck",
            "UnlockCollectionCheck",
            "DLCCheck",
            "ccSceneGameModeSelect::CheckRtbAddContents",
            "ccSceneDownloadContentsPossessCheck",
            "BattleDownloadContents",
            "IsEnableR2bContents",
            "ADDCONTENT_INSTALL",
            "contentLoaderInfo",
            "data/ui/flash/FLASH_PLAT/load_contents/load_contents.swf",
            "LoadContents",
            "SetDisableRtbContents",
            "NotifyRtbContents",
            "data/network/PLAT/COMMON_ADD_CONTENTS.xfbin",
            "COMMON_ADD_CONTENTS",
            "data/system/content_info.xfbin",
            "ContentOffset",
            "ContentSize",
            "ccDownloadContentAnalyze_Win32.cpp",
            "E2009022412:Cannot get the contents file info details.",
            "DlcThread"
        };

        count = ARRAYSIZE(tokens);
        return tokens;
    }

    bool DlcFolderHasAnyListedToken(const std::filesystem::path& folder)
    {
        std::error_code ec;
        if (!std::filesystem::exists(folder, ec) || !std::filesystem::is_directory(folder, ec))
            return false;

        size_t tokenCount = 0;
        const char* const* tokens = AllDlcTokens(tokenCount);

        for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
        {
            if (ec)
            {
                ec.clear();
                continue;
            }

            const std::string itemPath = it->path().generic_string();
            for (size_t i = 0; i < tokenCount; ++i)
            {
                if (PathContainsText(itemPath, tokens[i]))
                    return true;
            }
        }

        return false;
    }

    bool HasListedDlcGamePath(const std::filesystem::path& exeFolder)
    {
        size_t tokenCount = 0;
        const char* const* tokens = AllDlcTokens(tokenCount);
        for (size_t i = 0; i < tokenCount; ++i)
        {
            if (GamePathExists(exeFolder, tokens[i]))
                return true;
        }
        return false;
    }

    void InvalidateDlcDiskCache()
    {
        g_DlcDiskCacheValid = false;
        g_DlcDiskCacheValue = false;
    }

    bool IsSmallInternalDlcId(AppId_t appID)
    {
        // The game also has internal string IDs like DLC_24..DLC_45 and DLC_ex_13/14/16.
        // If those IDs are passed into our Steam layer, treat them as DLC identifiers when
        // the local /dlc payload exists.
        return appID >= 1 && appID <= 100;
    }

    const char* const* DlcTokens(AppId_t appID, size_t& count)
    {
        static const char* preorder[] = { "416410", "preorder", "pre_order", "pre-order", "boruto", "sarada", "kakashi" };
        static const char* shikamaru[] = { "416420", "shikamaru", "dlc1", "dlc_1", "scenario1", "scenario_1" };
        static const char* gaara[] = { "416421", "gaara", "dlc2", "dlc_2", "scenario2", "scenario_2" };
        static const char* soundFour[] = { "416422", "sound", "soundfour", "sound_four", "dlc3", "dlc_3", "scenario3", "scenario_3" };
        static const char* seasonBonus[] = { "416423", "season", "bonus" };
        static const char* seasonPass[] = { "416424", "seasonpass", "season_pass" };
        static const char* festival[] = { "435160", "traditional", "festival", "costume" };
        static const char* boruto[] = { "495160", "roadtoboruto", "road_to_boruto", "rtb", "boruto" };

        count = 0;
        switch (appID)
        {
        case 416410: count = ARRAYSIZE(preorder); return preorder;
        case 416420: count = ARRAYSIZE(shikamaru); return shikamaru;
        case 416421: count = ARRAYSIZE(gaara); return gaara;
        case 416422: count = ARRAYSIZE(soundFour); return soundFour;
        case 416423: count = ARRAYSIZE(seasonBonus); return seasonBonus;
        case 416424: count = ARRAYSIZE(seasonPass); return seasonPass;
        case 435160: count = ARRAYSIZE(festival); return festival;
        case 495160: count = ARRAYSIZE(boruto); return boruto;
        default: return nullptr;
        }
    }

    bool FolderHasDlcToken(const std::filesystem::path& folder, AppId_t appID)
    {
        std::error_code ec;
        if (!std::filesystem::exists(folder, ec) || !std::filesystem::is_directory(folder, ec))
            return false;

        size_t tokenCount = 0;
        const char* const* tokens = DlcTokens(appID, tokenCount);
        if (!tokens || tokenCount == 0)
            return false;

        for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
        {
            if (ec)
            {
                ec.clear();
                continue;
            }

            const std::string itemName = Lower(it->path().filename().string());
            for (size_t i = 0; i < tokenCount; ++i)
            {
                if (itemName.find(tokens[i]) != std::string::npos)
                    return true;
            }
        }

        return false;
    }


    std::vector<std::string> BuildDlcContentProbePaths()
    {
        std::vector<std::string> paths =
        {
            "sim:data/sim/dlcpackdata.cpk",
            "data/sim/dlcpackdata.cpk",
            "data/st/st_script_dlc.xfbin",
            "data/system/content_info.xfbin",
            "data/network/PLAT/COMMON_ADD_CONTENTS.xfbin",
            "data/ui/flash/FLASH_PLAT/load_contents/load_contents.swf",
            "data/no_release/message/plus_dlc/PLAT/LANG/messageInfo.bin.xfbin",
            "dlc/ep_gar/",
            "dlc/ep_sik/",
            "dlc/ep_r2b/",
            "dlc/ep_r2b/st30_s020",
            "dlc/ep_r2b/pt11_s010",
            "dlc/ep_r2b/pt11_s020",
            "dlc/ep_r2b/pt42_s020",
            "dlc/ep_r2b/pt42_s030",
            "dlc/ep_r2b/pt42_s040",
            "dlc/ep_r2b/pt45_s010",
            "st/dlc/ep_r2b/",
            "pt/dlc/ep_r2b/"
        };

        for (int i = 1; i <= 100; ++i)
            paths.push_back(std::string("dlc/") + std::to_string(i));

        return paths;
    }

    void WriteString(const char* key, const std::string& value)
    {
        WritePrivateProfileStringA("steam", key, value.c_str(), g_Path.c_str());
    }

    void WriteInt(const char* key, int value)
    {
        WritePrivateProfileStringA("steam", key, std::to_string(value).c_str(), g_Path.c_str());
    }

    SteamConfig::Mode ParseMode(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c){ return (char)std::tolower(c); });
        if (value == "revived" || value == "official" || value == "ns2revived")
            return SteamConfig::Mode::RevivedServer;
        if (value == "custom" || value == "customserver" || value == "server")
            return SteamConfig::Mode::CustomServer;
        if (value == "steam" || value == "passthrough")
            return SteamConfig::Mode::SteamPassthrough;
        return SteamConfig::Mode::Offline;
    }
}

namespace SteamConfig
{
    bool Init()
    {
        g_Path = (std::filesystem::path(GetExeFolder()) / "NarutoStorm4Revived" / "steam_config.ini").string();
        try { std::filesystem::create_directories(std::filesystem::path(g_Path).parent_path()); } catch (...) {}
        Load();
        Logger::Info(std::string("SteamConfig initialized mode=") + ModeName(g_Config.CurrentMode) + " path=" + g_Path);
        return true;
    }

    bool Load()
    {
        if (g_Path.empty())
            g_Path = (std::filesystem::path(GetExeFolder()) / "NarutoStorm4Revived" / "steam_config.ini").string();

        if (!std::filesystem::exists(g_Path))
            Save();

        Mode requestedMode = ParseMode(ReadString("mode", "offline"));
        if (requestedMode == Mode::SteamPassthrough)
        {
            Logger::Info(
                std::string("SteamConfig blocked Steam passthrough; ignored requested mode=") +
                ModeName(requestedMode));
            requestedMode = Mode::Offline;
        }

        g_Config.CurrentMode = requestedMode;
        g_Config.PersonaName = ReadString("persona", "NS4Revived");
        g_Config.SteamID = std::strtoull(ReadString("steamid", "76561199006065889").c_str(), nullptr, 10);
        g_Config.CustomServerHost = ReadString("custom_server", "127.0.0.1");
        g_Config.CustomServerPort = ReadInt("custom_port", 47584);
        g_Config.BlockOfficialTraffic = true;
        g_Config.LanOnly = ReadInt("lan_only", 1) != 0;
        g_Config.LogPackets = ReadInt("log_packets", 1) != 0;
        g_Config.EnableLocalStorage = ReadInt("local_storage", 1) != 0;
        g_Config.EnableLocalStats = ReadInt("local_stats", 1) != 0;
        g_Config.EnableLocalMatchmaking = ReadInt("local_matchmaking", 1) != 0;
        g_Config.AutoInstanceSteamID = ReadInt("auto_instance_steamid", 1) != 0;
        g_Config.AutoDetectSteamID = ReadInt("auto_detect_steamid", 1) != 0;
        g_Config.EnableEmbeddedMasterServer = ReadInt("embedded_master", 1) != 0;
        g_Config.RadminPeers = ParseStringList(ReadString("radmin_peers", ""));
        g_Config.EvolutionFolders = ParseStringList(ReadString("evolution_folders", "NarutoStorm4Revived\\mods\\StormEvolution,NarutoStorm4Revived\\StormEvolution"));
        g_Config.OwnedDlcAppIds = ParseDlcList(ReadString("owned_dlc", ""));
        g_Config.DlcFolder = Trim(ReadString("dlc_folder", DefaultDlcFolder().c_str()));
        if (g_Config.DlcFolder.empty())
            g_Config.DlcFolder = DefaultDlcFolder();
        g_Config.AutoDetectDlcFolder = ReadInt("auto_detect_dlc_folder", 1) != 0;
        g_Config.EnableDlcUnlock = ReadInt("enable_dlc_unlock", 0) != 0;
        InvalidateDlcDiskCache();
        return true;
    }

    bool Save()
    {
        if (g_Path.empty())
            g_Path = (std::filesystem::path(GetExeFolder()) / "NarutoStorm4Revived" / "steam_config.ini").string();
        try { std::filesystem::create_directories(std::filesystem::path(g_Path).parent_path()); } catch (...) {}
        WriteString("mode", ModeName(g_Config.CurrentMode));
        WriteString("persona", g_Config.PersonaName);
        WriteString("steamid", std::to_string(g_Config.SteamID));
        WriteString("custom_server", g_Config.CustomServerHost);
        WriteInt("custom_port", g_Config.CustomServerPort);
        WriteInt("block_official", g_Config.BlockOfficialTraffic ? 1 : 0);
        WriteInt("lan_only", g_Config.LanOnly ? 1 : 0);
        WriteInt("log_packets", g_Config.LogPackets ? 1 : 0);
        WriteInt("local_storage", g_Config.EnableLocalStorage ? 1 : 0);
        WriteInt("local_stats", g_Config.EnableLocalStats ? 1 : 0);
        WriteInt("local_matchmaking", g_Config.EnableLocalMatchmaking ? 1 : 0);
        WriteInt("auto_instance_steamid", g_Config.AutoInstanceSteamID ? 1 : 0);
        WriteInt("auto_detect_steamid", g_Config.AutoDetectSteamID ? 1 : 0);
        WriteInt("embedded_master", g_Config.EnableEmbeddedMasterServer ? 1 : 0);
        WriteString("radmin_peers", FormatStringList(g_Config.RadminPeers));
        WriteString("evolution_folders", FormatStringList(g_Config.EvolutionFolders));
        WriteString("owned_dlc", FormatDlcList(g_Config.OwnedDlcAppIds));
        WriteString("dlc_folder", g_Config.DlcFolder.empty() ? DefaultDlcFolder() : g_Config.DlcFolder);
        WriteInt("auto_detect_dlc_folder", g_Config.AutoDetectDlcFolder ? 1 : 0);
        WriteInt("enable_dlc_unlock", g_Config.EnableDlcUnlock ? 1 : 0);
        return true;
    }

    const Config& Get() { return g_Config; }
    Config& Mutable() { return g_Config; }
    bool IsOffline() { return g_Config.CurrentMode == Mode::Offline; }
    bool IsCustomServer() { return g_Config.CurrentMode == Mode::CustomServer; }
    bool IsRevivedServer() { return g_Config.CurrentMode == Mode::RevivedServer; }
    bool ShouldBlockOfficialTraffic() { return g_Config.BlockOfficialTraffic; }
    bool IsLanOnly() { return g_Config.LanOnly; }

    bool IsDlcUnlockEnabled()
    {
        return g_Config.EnableDlcUnlock;
    }

    void SetDlcUnlockEnabled(bool enabled)
    {
        if (g_Config.EnableDlcUnlock == enabled)
            return;

        g_Config.EnableDlcUnlock = enabled;
        InvalidateDlcDiskCache();
        Save();
        Logger::Info(std::string("DLC unlock override ") + (enabled ? "enabled" : "disabled"));
    }

    bool IsOwnedDlc(AppId_t appID)
    {
        return std::find(g_Config.OwnedDlcAppIds.begin(), g_Config.OwnedDlcAppIds.end(), appID) != g_Config.OwnedDlcAppIds.end();
    }

    bool HasDlcContentOnDisk()
    {
        if (!g_Config.EnableDlcUnlock || !g_Config.AutoDetectDlcFolder)
            return false;

        if (g_DlcDiskCacheValid)
            return g_DlcDiskCacheValue;

        const std::filesystem::path exeFolder = GetExeFolder();
        const std::filesystem::path dlcFolder = g_Config.DlcFolder.empty() ? DefaultDlcFolder() : g_Config.DlcFolder;

        bool found = false;

        for (const std::string& probe : BuildDlcContentProbePaths())
        {
            if (GamePathExists(exeFolder, probe.c_str()))
            {
                found = true;
                break;
            }
        }

        // Exact game string paths and content paths from the binary dump.
        if (HasListedDlcGamePath(exeFolder))
            found = true;

        // Common packed and folder layouts used by NS4 DLC installs.
        if (!found && FileExists(exeFolder / "data" / "sim" / "dlcpackdata.cpk"))
            found = true;

        if (!found && FileExists(exeFolder / "data" / "st" / "st_script_dlc.xfbin"))
            found = true;

        if (!found && DirectoryExists(exeFolder / "dlc" / "ep_gar"))
            found = true;

        if (!found && DirectoryExists(exeFolder / "dlc" / "ep_sik"))
            found = true;

        if (!found && DirectoryExists(exeFolder / "dlc" / "ep_r2b"))
            found = true;

        if (!found && DirectoryExists(exeFolder / "st" / "dlc" / "ep_r2b"))
            found = true;

        if (!found && DirectoryExists(exeFolder / "pt" / "dlc" / "ep_r2b"))
            found = true;

        for (int i = 1; !found && i <= 100; ++i)
        {
            if (DirectoryExists(exeFolder / "dlc" / std::to_string(i)))
                found = true;
        }

        if (!found && DlcFolderHasAnyListedToken(dlcFolder))
            found = true;

        if (!found && DirectoryHasAnyFiles(dlcFolder))
            found = true;

        g_DlcDiskCacheValue = found;
        g_DlcDiskCacheValid = true;
        return found;
    }

    bool IsDlcInstalledOnDisk(AppId_t appID)
    {
        if (!g_Config.EnableDlcUnlock || !g_Config.AutoDetectDlcFolder)
            return false;

        const std::filesystem::path exeFolder = GetExeFolder();
        const std::filesystem::path dlcFolder = g_Config.DlcFolder.empty() ? DefaultDlcFolder() : g_Config.DlcFolder;

        if (FolderHasDlcToken(dlcFolder, appID))
            return true;

        if (IsSmallInternalDlcId(appID) && HasDlcContentOnDisk())
            return true;

        // Road to Boruto/story DLC paths from the game strings.
        if (appID == 495160 &&
            (DirectoryExists(exeFolder / "dlc" / "ep_r2b") ||
             FileExists(exeFolder / "data" / "sim" / "dlcpackdata.cpk")))
        {
            return true;
        }

        // Gaara/Shikamaru DLC paths from the game strings.
        if ((appID == 416421 && DirectoryExists(exeFolder / "dlc" / "ep_gar")) ||
            (appID == 416420 && DirectoryExists(exeFolder / "dlc" / "ep_sik")))
        {
            return true;
        }

        // Some NS4 installs place all owned DLC payloads together in /dlc without appid names.
        // In that case, use the non-empty DLC folder as the installed-content signal.
        return DirectoryHasAnyFiles(dlcFolder);
    }

    bool IsDlcAvailable(AppId_t appID)
    {
        if (appID == 349040)
            return true;

        if (!g_Config.EnableDlcUnlock)
            return false;

        return IsOwnedDlc(appID) || IsDlcInstalledOnDisk(appID);
    }

    const std::string& GetDlcFolder()
    {
        if (g_Config.DlcFolder.empty())
            g_Config.DlcFolder = DefaultDlcFolder();
        return g_Config.DlcFolder;
    }

    std::string GetGameFolder()
    {
        return GetExeFolder();
    }

    std::vector<std::string> GetDlcContentProbePaths()
    {
        return BuildDlcContentProbePaths();
    }



    std::vector<std::string> GetRadminPeers()
    {
        return g_Config.RadminPeers;
    }

    std::vector<std::string> GetEvolutionFolders()
    {
        std::vector<std::string> out = g_Config.EvolutionFolders;
        if (out.empty())
        {
            out.push_back("NarutoStorm4Revived\\mods\\StormEvolution");
            out.push_back("NarutoStorm4Revived\\StormEvolution");
        }
        return out;
    }

    std::string GetDlcInstallDir(AppId_t appID)
    {
        std::filesystem::path base = GetDlcFolder();
        const std::string appText = std::to_string(static_cast<unsigned long long>(appID));
        std::filesystem::path byApp = base / appText;
        std::error_code ec;
        if (std::filesystem::exists(byApp, ec))
            return byApp.string();
        return base.string();
    }

    const std::string& GetPath() { return g_Path; }

    const char* ModeName(Mode mode)
    {
        switch (mode)
        {
        case Mode::CustomServer: return "custom";
        case Mode::RevivedServer: return "revived";
        case Mode::SteamPassthrough: return "steam";
        default: return "offline";
        }
    }
}
