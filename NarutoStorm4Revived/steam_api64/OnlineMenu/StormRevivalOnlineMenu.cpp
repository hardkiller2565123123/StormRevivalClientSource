#include "StormRevivalOnlineMenu.h"
#include "Core/SRLogger.h"
#include "Core/VersionGuard.h"
#include "Config/OnlineMenuConfig.h"
#include "Flash/FlashBridge.h"
#include "CustomMenu/CustomMenuEntry.h"
#include "Hooks/MenuHookScaffold.h"
#include "Hooks/MenuActionHook.h"
#include "Research/Progress.h"
#include "Hooking/HookGroups.h"
#include "CustomUI/CustomOptionSystem.h"
#include "ActionScript/ActionScriptIntegrationNotes.h"
#include "NS4GFX/MenuExpansion.h"

namespace StormRevival::OnlineMenu
{
    void Install()
    {
        auto& cfg = Config::Get();
        if (cfg.EnableInstallLog)
        {
            Log::Info("Installing OFFLINE decompiled OnlineMenu pack with version gate + pattern scanner.");
            Log::Info(Research::ProgressTable);
        }

        LogGameVersionInfo();

        Flash::Install();
        CustomUI::Install();
        NS4GFX::RegisterActionScriptBackedMenus();
        Log::Info(ActionScript::GetIntegrationSummary());

        // Pattern/fixed-address hook resolver lives inside Hooking::InstallAll().
        // On unknown EXEs, fixed addresses are skipped and only verified patterns are allowed.
        Hooking::InstallAll();

        if (ShouldSkipMenuMutation())
        {
            Log::Warn("[VersionGuard] Menu mutation skipped for unsupported EXE. CustomMenu, StoreReplacement, and synthetic modes are OFF.");
            Log::Warn("[VersionGuard] Add verified signatures in OnlineMenu\\Hooking\\UniversalHookPatterns.h or set online_menu_allow_fixed_addresses=1 only for a known-good EXE.");
            Hooks::InstallSafeHooks();
            return;
        }

        CustomMenu::Install();
        Hooks::InstallMenuActionHook();
        Hooks::InstallSafeHooks();
    }

    void Shutdown()
    {
        Hooking::ShutdownAll();
        Hooks::ShutdownHooks();
        CustomUI::Shutdown();
        CustomMenu::Shutdown();
        Log::Info("OnlineMenu pack shutdown.");
    }
}
