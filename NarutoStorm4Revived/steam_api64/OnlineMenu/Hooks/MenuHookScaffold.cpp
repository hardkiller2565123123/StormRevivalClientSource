#include "MenuHookScaffold.h"
#include "OnlineMenuHookLogger.h"
#include "OnlineMenuHookStubs.h"
#include "../Core/SRLogger.h"
#include "../Config/OnlineMenuConfig.h"

namespace StormRevival::OnlineMenu::Hooks
{
    void InstallSafeHooks()
    {
        InstallOnlineMenuHookLogging();
        InstallOnlineMenuHookStubs();

        auto& cfg = Config::Get();
        if (!cfg.EnableMenuResearchHooks)
        {
            Log::Info("[Hook] EnableMenuResearchHooks=false. Real detours are skipped, but hook logging is active.");
            Log::Info("[Hook] When ready, set EnableMenuResearchHooks=true and attach MinHook detours.");
            return;
        }

        Log::Info("[Hook] EnableMenuResearchHooks=true. Real detour install point reached.");
        Log::Info("[Hook] Add MinHook create/enable calls here and call LogHookInstalled/LogHookFailed per function.");
    }

    void ShutdownHooks()
    {
        ShutdownOnlineMenuHookStubs();
        ShutdownOnlineMenuHookLogging();
        Log::Info("OnlineMenu hook shutdown.");
    }
}
