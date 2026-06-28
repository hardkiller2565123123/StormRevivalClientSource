#include "StageResourceHooks.h"
#include "UniversalHookRegistry.h"
#include "UniversalHookAddresses.h"
#include "UniversalHookPatterns.h"
#include "../Core/SRLogger.h"
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::Hooking::StageResourceHooks
{
    namespace
    {
        using FnStageFilterLoad = std::int64_t(__fastcall*)(std::uintptr_t, int);
        using FnDbLoad = std::int64_t(__fastcall*)(std::uintptr_t, const char*);
        using FnDbLookup = std::int64_t(__fastcall*)(std::uintptr_t, std::uintptr_t, std::uintptr_t);
        using FnStageFilterApply = std::int64_t(__fastcall*)(float*, const char*, const char*);

        FnStageFilterLoad g_StageFilterLoad = nullptr;
        FnDbLoad g_DbLoad = nullptr;
        FnDbLookup g_DbLookup = nullptr;
        FnStageFilterApply g_StageFilterApply = nullptr;

        std::int64_t __fastcall DetourStageFilterLoad(std::uintptr_t self, int mode)
        {
            Log::Info("[StageHook] sub_1403B0074 stage filter load mode=" + std::to_string(mode));
            return g_StageFilterLoad ? g_StageFilterLoad(self, mode) : 0;
        }

        std::int64_t __fastcall DetourDbLoad(std::uintptr_t manager, const char* path)
        {
            if (path)
                Log::Info(std::string("[ResourceHook] DB/XFBIN load: ") + path);
            return g_DbLoad ? g_DbLoad(manager, path) : 0;
        }

        std::int64_t __fastcall DetourDbLookup(std::uintptr_t db, std::uintptr_t type, std::uintptr_t key)
        {
            Log::Info("[ResourceHook] DB lookup sub_140A139F0");
            return g_DbLookup ? g_DbLookup(db, type, key) : 0;
        }

        std::int64_t __fastcall DetourStageFilterApply(float* state, const char* file, const char* stageId)
        {
            Log::Info(std::string("[StageHook] Apply stage filter file=") + (file ? file : "<null>") + " stage=" + (stageId ? stageId : "<null>"));
            return g_StageFilterApply ? g_StageFilterApply(state, file, stageId) : 0;
        }

        HookSpec g_specs[] =
        {
            { "Stage.StageFilterLoad.sub_1403B0074", HookGroup::Stage, Addresses::Stage::StageFilterLoad, reinterpret_cast<void*>(&DetourStageFilterLoad), reinterpret_cast<void**>(&g_StageFilterLoad), "Stage variant / stageFilter.xfbin loader", Patterns::Stage::StageFilterLoad, 0 },
            { "Resource.DatabaseLoad.sub_140A03D30", HookGroup::Resources, Addresses::Resources::DatabaseLoad, reinterpret_cast<void*>(&DetourDbLoad), reinterpret_cast<void**>(&g_DbLoad), "Generic XFBIN database load", Patterns::Resources::DatabaseLoad, 0 },
            { "Resource.DatabaseLookup.sub_140A139F0", HookGroup::Resources, Addresses::Resources::DatabaseLookup, reinterpret_cast<void*>(&DetourDbLookup), reinterpret_cast<void**>(&g_DbLookup), "Generic database key lookup", Patterns::Resources::DatabaseLookup, 0 },
            { "Stage.StageFilterApply.sub_140A0FDB0", HookGroup::Stage, Addresses::Stage::StageFilterApply, reinterpret_cast<void*>(&DetourStageFilterApply), reinterpret_cast<void**>(&g_StageFilterApply), "Apply stage filter parameters", Patterns::Stage::StageFilterApply, 0 },
        };
    }

    void Install()
    {
        Log::Info("[StageResourceHooks] Installing stage/resource hooks.");
        InstallHooks(g_specs, static_cast<int>(sizeof(g_specs) / sizeof(g_specs[0])));
    }

    void Shutdown()
    {
        Log::Info("[StageResourceHooks] Shutdown requested.");
    }
}
