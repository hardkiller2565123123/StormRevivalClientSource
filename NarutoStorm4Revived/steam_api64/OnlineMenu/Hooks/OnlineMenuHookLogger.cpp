#include "OnlineMenuHookLogger.h"
#include "../Core/SRLogger.h"

#include <string>

namespace StormRevival::OnlineMenu::Hooks
{
    static HookDefinition g_hooks[] =
    {
        { "Hook_Flash_InvokeWithArgs_sub_140607BA0", "0x140607BA0", "Trace all Flash ActionScript calls with arguments.", HookInstallStatus::Pending },
        { "Hook_Flash_InvokeNoArgs_sub_140607B5C", "0x140607B5C", "Trace no-argument Flash calls such as SetLock/Restart/CallFinalize.", HookInstallStatus::Pending },
        { "Hook_Flash_InvokeReturn_sub_140607B7C", "0x140607B7C", "Trace Flash getter calls such as GetMode/GetModeBattele.", HookInstallStatus::Pending },
        { "Hook_Flash_RegisterMovie_sub_14060759C", "0x14060759C", "Trace SWF/GFX movie registration.", HookInstallStatus::Pending },
        { "Hook_Flash_UnregisterMovie_sub_1406078CC", "0x1406078CC", "Trace movie unload/finalize.", HookInstallStatus::Pending },
        { "Hook_Flash_RegisterCallbacks_sub_1401FD0AC", "0x1401FD0AC", "Trace ActionScript callback registration table.", HookInstallStatus::Pending },

        { "Hook_MainMenu_Init_sub_140676250", "0x140676250", "Trace netbattlemainmenu Initialize and startup args.", HookInstallStatus::Pending },
        { "Hook_MainMenu_GetMode_sub_1406760F4", "0x1406760F4", "Trace selected main menu mode.", HookInstallStatus::Pending },
        { "Hook_MainMenu_GetModeBattle_sub_140676164", "0x140676164", "Trace selected battle mode/submode.", HookInstallStatus::Pending },
        { "Hook_MainMenu_GetLimitEvent_sub_1406761E0", "0x1406761E0", "Trace selected limit event id.", HookInstallStatus::Pending },
        { "Hook_MainMenu_Update_sub_1405C0AA0", "0x1405C0AA0", "Trace main menu update/selection transition.", HookInstallStatus::Pending },
        { "Hook_MainMenu_ActionDispatch_sub_1405C17B4", "0x1405C17B4", "Trace mode action dispatch.", HookInstallStatus::Pending },
        { "Hook_MainMenu_StateMap_sub_1405C3064", "0x1405C3064", "Trace selected mode to state mapping.", HookInstallStatus::Pending },

        { "Hook_Banner_Init_sub_140671D28", "0x140671D28", "Trace net battle banner Initialize.", HookInstallStatus::Pending },
        { "Hook_Banner_SetMode_sub_1406722A0", "0x1406722A0", "Trace title/banner mode selection.", HookInstallStatus::Pending },

        { "Hook_Lobby_Init_sub_1406734A8", "0x1406734A8", "Trace netbattlelobby Initialize.", HookInstallStatus::Pending },
        { "Hook_Lobby_Finalize_sub_1406732AC", "0x1406732AC", "Trace netbattlelobby finalize.", HookInstallStatus::Pending },
        { "Hook_Lobby_GetLock_sub_140673374", "0x140673374", "Trace lobby getLock1 getter.", HookInstallStatus::Pending },
        { "Hook_Lobby_GetVsOk_sub_140673438", "0x140673438", "Trace lobby CallGetVsOk getter.", HookInstallStatus::Pending },
    };

    static const char* StatusText(HookInstallStatus status)
    {
        switch (status)
        {
        case HookInstallStatus::Pending: return "PENDING";
        case HookInstallStatus::Installed: return "INSTALLED";
        case HookInstallStatus::Failed: return "FAILED";
        case HookInstallStatus::Skipped: return "SKIPPED";
        default: return "UNKNOWN";
        }
    }

    static void SetStatus(const char* hookName, HookInstallStatus status)
    {
        for (auto& hook : g_hooks)
        {
            if (std::string(hook.Name) == hookName)
            {
                hook.Status = status;
                return;
            }
        }
    }

    void InstallOnlineMenuHookLogging()
    {
        Log::Info("========== OnlineMenu Hook Logging ==========");
        Log::Info("Hook logging initialized. This lists every planned hook and reports install/hit events.");

        for (const auto& hook : g_hooks)
        {
            Log::Info(std::string("[Hook][Plan] ") + hook.Name +
                " address=" + hook.Address +
                " status=" + StatusText(hook.Status) +
                " purpose=" + hook.Purpose);
        }

        Log::Info("To enable real detours, wire MinHook calls and call LogHookInstalled/Failed per hook.");
        Log::Info("============================================");
    }

    void ShutdownOnlineMenuHookLogging()
    {
        Log::Info("========== OnlineMenu Hook Logging Shutdown ==========");
        for (const auto& hook : g_hooks)
        {
            Log::Info(std::string("[Hook][Final] ") + hook.Name +
                " address=" + hook.Address +
                " status=" + StatusText(hook.Status));
        }
        Log::Info("=====================================================");
    }

    void LogHookPlanned(const char* hookName, const char* address, const char* purpose)
    {
        Log::Info(std::string("[Hook][Plan] ") + (hookName ? hookName : "<null>") +
            " address=" + (address ? address : "<null>") +
            " purpose=" + (purpose ? purpose : "<null>"));
    }

    void LogHookInstalled(const char* hookName, const char* address)
    {
        SetStatus(hookName, HookInstallStatus::Installed);
        Log::Info(std::string("[Hook][Installed] ") + (hookName ? hookName : "<null>") +
            " address=" + (address ? address : "<null>"));
    }

    void LogHookFailed(const char* hookName, const char* address, const char* reason)
    {
        SetStatus(hookName, HookInstallStatus::Failed);
        Log::Error(std::string("[Hook][Failed] ") + (hookName ? hookName : "<null>") +
            " address=" + (address ? address : "<null>") +
            " reason=" + (reason ? reason : "<null>"));
    }

    void LogHookSkipped(const char* hookName, const char* address, const char* reason)
    {
        SetStatus(hookName, HookInstallStatus::Skipped);
        Log::Warn(std::string("[Hook][Skipped] ") + (hookName ? hookName : "<null>") +
            " address=" + (address ? address : "<null>") +
            " reason=" + (reason ? reason : "<null>"));
    }

    void LogHookHit(const char* hookName)
    {
        Log::Info(std::string("[Hook][Hit] ") + (hookName ? hookName : "<null>"));
    }

    void LogHookHitValue(const char* hookName, int value)
    {
        Log::Info(std::string("[Hook][Hit] ") + (hookName ? hookName : "<null>") +
            " value=" + std::to_string(value));
    }

    void LogFlashCall(const char* movie, const char* root, const char* functionName, int argc)
    {
        Log::Info(std::string("[Hook][FlashCall] movie=") + (movie ? movie : "<null>") +
            " root=" + (root ? root : "<null>") +
            " function=" + (functionName ? functionName : "<null>") +
            " argc=" + std::to_string(argc));
    }

    void LogFlashGetterResult(const char* functionName, int result)
    {
        Log::Info(std::string("[Hook][FlashGetter] function=") +
            (functionName ? functionName : "<null>") +
            " result=" + std::to_string(result));
    }

    const HookDefinition* GetOnlineMenuHooks()
    {
        return g_hooks;
    }

    int GetOnlineMenuHookCount()
    {
        return static_cast<int>(sizeof(g_hooks) / sizeof(g_hooks[0]));
    }
}
