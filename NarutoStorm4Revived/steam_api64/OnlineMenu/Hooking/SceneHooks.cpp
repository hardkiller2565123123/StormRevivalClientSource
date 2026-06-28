#include "SceneHooks.h"
#include "UniversalHookRegistry.h"
#include "UniversalHookAddresses.h"
#include "UniversalHookPatterns.h"
#include "../Core/SRLogger.h"
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::Hooking::SceneHooks
{
    namespace
    {
        using FnBossSceneCreate = std::int64_t(__fastcall*)(const char*);
        using FnSetSceneName = std::uintptr_t*(__fastcall*)(std::uintptr_t, char*);

        FnBossSceneCreate g_BossSceneCreate = nullptr;
        FnSetSceneName g_SetSceneName = nullptr;

        std::int64_t __fastcall DetourBossSceneCreate(const char* sceneName)
        {
            Log::Info(std::string("[SceneHook] Create boss scene: ") + (sceneName ? sceneName : "<null>"));
            return g_BossSceneCreate ? g_BossSceneCreate(sceneName) : 0;
        }

        std::uintptr_t* __fastcall DetourSetSceneName(std::uintptr_t self, char* sceneName)
        {
            Log::Info(std::string("[SceneHook] Set scene name: ") + (sceneName ? sceneName : "<null>"));
            return g_SetSceneName ? g_SetSceneName(self, sceneName) : nullptr;
        }

        HookSpec g_specs[] =
        {
            { "Scene.BossSceneCreate.sub_1406E4BC0", HookGroup::Scene, Addresses::Scene::BossSceneCreate, reinterpret_cast<void*>(&DetourBossSceneCreate), reinterpret_cast<void**>(&g_BossSceneCreate), "Boss/adventure scene object creation", Patterns::Scene::BossSceneCreate, 0 },
            { "Scene.SetSceneName.sub_140AB4550", HookGroup::Scene, Addresses::Scene::SetSceneName, reinterpret_cast<void*>(&DetourSetSceneName), reinterpret_cast<void**>(&g_SetSceneName), "Scene name string assignment", Patterns::Scene::SetSceneName, 0 },
        };
    }

    void Install()
    {
        Log::Info("[SceneHooks] Installing scene hooks.");
        InstallHooks(g_specs, static_cast<int>(sizeof(g_specs) / sizeof(g_specs[0])));
    }

    void Shutdown()
    {
        Log::Info("[SceneHooks] Shutdown requested.");
    }
}
