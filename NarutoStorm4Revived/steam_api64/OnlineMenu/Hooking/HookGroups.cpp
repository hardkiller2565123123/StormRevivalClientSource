#include "HookGroups.h"
#include "UniversalHookRegistry.h"
#include "FlashBridgeHooks.h"
#include "StageResourceHooks.h"
#include "ScenarioHooks.h"
#include "SceneHooks.h"
#include "../Core/SRLogger.h"
#include <string>

namespace StormRevival::OnlineMenu::Hooking
{
    namespace
    {
        /*
            Crash-safe defaults.

            The broad 2026-06-26 hook pass crashed during startup after Resource/Scenario
            instrumentation began firing. Keep all unsafe groups compiled and centralized,
            but do not install them by default. Re-enable ONE group at a time only after
            the UI-only build boots cleanly.
        */
        constexpr bool EnableUiHooks       = true;
        constexpr bool EnableStageHooks    = false;
        constexpr bool EnableScenarioHooks = false;
        constexpr bool EnableSceneHooks    = false;

        void LogDisabledGroup(const char* name, const char* reason)
        {
            Log::Warn(std::string("[HookGroups] ") + name + " disabled: " + reason);
        }
    }

    void InstallAll()
    {
        Log::Info("[HookGroups] Installing crash-safe universal hooks. UI bridge only by default.");

        if (EnableUiHooks)
            FlashBridgeHooks::Install();
        else
            LogDisabledGroup("FlashBridgeHooks", "EnableUiHooks=false");

        if (EnableStageHooks)
            StageResourceHooks::Install();
        else
            LogDisabledGroup("StageResourceHooks", "unsafe startup hook group; keep off until UI-only boot is stable");

        if (EnableScenarioHooks)
            ScenarioHooks::Install();
        else
            LogDisabledGroup("ScenarioHooks", "unsafe/hot XML hook group; keep off until tested individually");

        if (EnableSceneHooks)
            SceneHooks::Install();
        else
            LogDisabledGroup("SceneHooks", "disabled for crash isolation");

        DumpHookTable();
    }

    void ShutdownAll()
    {
        Log::Info("[HookGroups] Shutdown all universal hooks.");
        FlashBridgeHooks::Shutdown();
        StageResourceHooks::Shutdown();
        ScenarioHooks::Shutdown();
        SceneHooks::Shutdown();
        DisableAll();
    }
}
