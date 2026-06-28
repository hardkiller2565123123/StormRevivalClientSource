#include "SlotExpansionManager.h"
#include "CharacterSlotExpansionManager.h"
#include "Logger.h"
#include "Scene.h"
#include "SteamConfig.h"
#include <Windows.h>
#include <algorithm>
#include <filesystem>
#include <string>

namespace
{
    SlotExpansionConfig g_Config{
        true, // auto-apply runtime expansions after startup
        true, // stage/scene runtime expansion
        false, // character roster runtime stays diagnostics-only until select-grid offsets are verified
        8000, // startup delay in ms; lets the game initialize its tables first
        512,  // character roster target; final char-select table patch still required
        512,  // costume roster target; final costume table patch still required
        512,  // stage content slots
        512,  // scene factory slots
        1000, // BGM mapping slots
        512,  // projectile slots
        256,  // partner slots
        512,  // team ultimate jutsu slots
        512,  // special condition rows
        1000  // character relation rows
    };

    bool g_StageExpansionRequested = false;
    bool g_StageExpansionApplied = false;
    bool g_AutoApplyThreadStarted = false;
    const char* g_LastStatus = "Slot expansion manager initialized.";

    SlotExpansionConfig Defaults()
    {
        return SlotExpansionConfig{ true, true, false, 8000, 512, 512, 512, 512, 1000, 512, 256, 512, 512, 1000 };
    }

    std::string ConfigPath()
    {
        std::string path = SteamConfig::GetPath();
        if (!path.empty())
            return path;

        char exePath[MAX_PATH]{};
        GetModuleFileNameA(nullptr, exePath, MAX_PATH);
        return (std::filesystem::path(exePath).parent_path() / "NarutoStorm4Revived" / "steam_config.ini").string();
    }

    int ClampInt(int value, int low, int high)
    {
        return std::max(low, std::min(value, high));
    }

    int ReadSlotInt(const char* key, int fallback)
    {
        return GetPrivateProfileIntA("slots", key, fallback, ConfigPath().c_str());
    }

    void WriteSlotInt(const char* key, int value)
    {
        WritePrivateProfileStringA("slots", key, std::to_string(value).c_str(), ConfigPath().c_str());
    }

    void ClampConfig()
    {
        g_Config.AutoApplyDelayMs = ClampInt(g_Config.AutoApplyDelayMs, 1000, 60000);
        g_Config.ExtraCharacterSlots = ClampInt(g_Config.ExtraCharacterSlots, 0, 4096);
        g_Config.ExtraCostumeSlots = ClampInt(g_Config.ExtraCostumeSlots, 0, 4096);
        g_Config.ExtraStageSlots = ClampInt(g_Config.ExtraStageSlots, 0, 4096);
        g_Config.ExtraSceneSlots = ClampInt(g_Config.ExtraSceneSlots, 0, 4096);
        g_Config.ExtraBgmSlots = ClampInt(g_Config.ExtraBgmSlots, 0, 8192);
        g_Config.ExtraProjectileSlots = ClampInt(g_Config.ExtraProjectileSlots, 0, 4096);
        g_Config.ExtraPartnerSlots = ClampInt(g_Config.ExtraPartnerSlots, 0, 4096);
        g_Config.ExtraTeamUltimateSlots = ClampInt(g_Config.ExtraTeamUltimateSlots, 0, 4096);
        g_Config.ExtraConditionSlots = ClampInt(g_Config.ExtraConditionSlots, 0, 4096);
        g_Config.ExtraCharRelationSlots = ClampInt(g_Config.ExtraCharRelationSlots, 0, 8192);
    }

    DWORD WINAPI AutoApplyThread(LPVOID)
    {
        Sleep(static_cast<DWORD>(g_Config.AutoApplyDelayMs));
        SlotExpansionManager::ApplyRuntimeExpansions();
        return 0;
    }
}

namespace SlotExpansionManager
{
    void Init()
    {
        Load();
        CharacterSlotExpansionManager::Init();
        g_LastStatus = "Slot expansion manager initialized from saved config.";
        Logger::Info("SlotExpansionManager initialized from " + ConfigPath());

        if (g_Config.AutoApplyRuntime && !g_AutoApplyThreadStarted)
        {
            g_AutoApplyThreadStarted = true;
            HANDLE thread = CreateThread(nullptr, 0, AutoApplyThread, nullptr, 0, nullptr);
            if (thread)
            {
                CloseHandle(thread);
                Logger::Info("SlotExpansionManager scheduled runtime auto-apply after " + std::to_string(g_Config.AutoApplyDelayMs) + "ms");
            }
            else
            {
                Logger::Error("SlotExpansionManager failed to start runtime auto-apply thread");
            }
        }
    }

    const SlotExpansionConfig& GetConfig()
    {
        return g_Config;
    }

    SlotExpansionConfig& MutableConfig()
    {
        return g_Config;
    }

    void ResetDefaults()
    {
        g_Config = Defaults();
        Save();
        g_LastStatus = "Slot expansion defaults restored.";
        Logger::Info("SlotExpansionManager defaults restored");
    }

    bool Load()
    {
        const SlotExpansionConfig defaults = Defaults();
        g_Config.AutoApplyRuntime = ReadSlotInt("auto_apply_runtime", defaults.AutoApplyRuntime ? 1 : 0) != 0;
        g_Config.EnableStageSceneRuntime = ReadSlotInt("enable_stage_scene_runtime", defaults.EnableStageSceneRuntime ? 1 : 0) != 0;
        g_Config.EnableCharacterRosterRuntime = ReadSlotInt("enable_character_roster_runtime", defaults.EnableCharacterRosterRuntime ? 1 : 0) != 0;
        g_Config.AutoApplyDelayMs = ReadSlotInt("auto_apply_delay_ms", defaults.AutoApplyDelayMs);
        g_Config.ExtraCharacterSlots = ReadSlotInt("extra_character_slots", defaults.ExtraCharacterSlots);
        g_Config.ExtraCostumeSlots = ReadSlotInt("extra_costume_slots", defaults.ExtraCostumeSlots);
        g_Config.ExtraStageSlots = ReadSlotInt("extra_stage_slots", defaults.ExtraStageSlots);
        g_Config.ExtraSceneSlots = ReadSlotInt("extra_scene_slots", defaults.ExtraSceneSlots);
        g_Config.ExtraBgmSlots = ReadSlotInt("extra_bgm_slots", defaults.ExtraBgmSlots);
        g_Config.ExtraProjectileSlots = ReadSlotInt("extra_projectile_slots", defaults.ExtraProjectileSlots);
        g_Config.ExtraPartnerSlots = ReadSlotInt("extra_partner_slots", defaults.ExtraPartnerSlots);
        g_Config.ExtraTeamUltimateSlots = ReadSlotInt("extra_team_ultimate_slots", defaults.ExtraTeamUltimateSlots);
        g_Config.ExtraConditionSlots = ReadSlotInt("extra_condition_slots", defaults.ExtraConditionSlots);
        g_Config.ExtraCharRelationSlots = ReadSlotInt("extra_character_relation_slots", defaults.ExtraCharRelationSlots);
        ClampConfig();
        return true;
    }

    bool Save()
    {
        ClampConfig();
        try
        {
            std::filesystem::create_directories(std::filesystem::path(ConfigPath()).parent_path());
        }
        catch (...)
        {
        }

        WriteSlotInt("auto_apply_runtime", g_Config.AutoApplyRuntime ? 1 : 0);
        WriteSlotInt("enable_stage_scene_runtime", g_Config.EnableStageSceneRuntime ? 1 : 0);
        WriteSlotInt("enable_character_roster_runtime", g_Config.EnableCharacterRosterRuntime ? 1 : 0);
        WriteSlotInt("auto_apply_delay_ms", g_Config.AutoApplyDelayMs);
        WriteSlotInt("extra_character_slots", g_Config.ExtraCharacterSlots);
        WriteSlotInt("extra_costume_slots", g_Config.ExtraCostumeSlots);
        WriteSlotInt("extra_stage_slots", g_Config.ExtraStageSlots);
        WriteSlotInt("extra_scene_slots", g_Config.ExtraSceneSlots);
        WriteSlotInt("extra_bgm_slots", g_Config.ExtraBgmSlots);
        WriteSlotInt("extra_projectile_slots", g_Config.ExtraProjectileSlots);
        WriteSlotInt("extra_partner_slots", g_Config.ExtraPartnerSlots);
        WriteSlotInt("extra_team_ultimate_slots", g_Config.ExtraTeamUltimateSlots);
        WriteSlotInt("extra_condition_slots", g_Config.ExtraConditionSlots);
        WriteSlotInt("extra_character_relation_slots", g_Config.ExtraCharRelationSlots);
        g_LastStatus = "Runtime slot settings saved. Restart to apply saved count changes.";
        Logger::Info("SlotExpansionManager saved runtime slot config");
        return true;
    }

    void ApplyRuntimeExpansions()
    {
        ClampConfig();
        CharacterSlotExpansionManager::RunDiagnostics();
        StageSlotExpansion::SetExtraCapacity(g_Config.ExtraSceneSlots);

        if (g_Config.EnableStageSceneRuntime)
        {
            ApplyStageExpansion();
            return;
        }

        g_LastStatus = "Runtime slot expansion loaded; stage/scene expansion disabled in config.";
        Logger::Info("SlotExpansionManager runtime auto-apply skipped stage/scene expansion by config");
    }

    bool ApplyStageExpansion()
    {
        g_StageExpansionRequested = true;
        StageSlotExpansion::SetExtraCapacity(g_Config.ExtraSceneSlots);

        if (g_StageExpansionApplied)
        {
            g_LastStatus = "Stage expansion was already applied.";
            return true;
        }

        if (StageSlotExpansion::ExpandSceneList())
        {
            g_StageExpansionApplied = true;
            g_LastStatus = "Stage/scene expansion applied.";
            Logger::Info("SlotExpansionManager applied stage/scene expansion");
            return true;
        }

        g_LastStatus = StageSlotExpansion::LastStatus();
        Logger::Error(std::string("SlotExpansionManager stage expansion failed: ") + g_LastStatus);
        return false;
    }

    bool StageExpansionRequested()
    {
        return g_StageExpansionRequested;
    }

    bool StageExpansionApplied()
    {
        return g_StageExpansionApplied;
    }

    const char* LastStatus()
    {
        return g_LastStatus;
    }
}
