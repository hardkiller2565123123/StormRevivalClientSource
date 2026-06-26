#include "StormRevivalOnlineMenu.h"
#include "Core/SRLogger.h"
#include "Config/OnlineMenuConfig.h"
#include "Flash/FlashBridge.h"
#include "CustomMenu/CustomMenuEntry.h"
#include "Hooks/MenuHookScaffold.h"
#include "Hooks/MenuActionHook.h"
#include "Research/Progress.h"

namespace StormRevival::OnlineMenu
{
    void Install()
    {
        auto& cfg = Config::Get();
        if (cfg.EnableInstallLog)
        {
            Log::Info("Installing OFFLINE decompiled OnlineMenu pack with true custom-option scaffold.");
            Log::Info(Research::ProgressTable);
        }

        Flash::Install();
        CustomMenu::Install();
        Hooks::InstallMenuActionHook();
        Hooks::InstallSafeHooks();
    }

    void Shutdown()
    {
        Hooks::ShutdownHooks();
        CustomMenu::Shutdown();
        Log::Info("OnlineMenu pack shutdown.");
    }
}
