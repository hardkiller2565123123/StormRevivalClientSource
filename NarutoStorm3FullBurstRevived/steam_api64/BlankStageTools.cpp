#include "StdInc.h"
#include "BlankStageTools.h"
#include "Logger.h"

#include <sstream>
#include <cstdint>

namespace
{
    //Gobal Stage States Dont Change.
    BlankStageTools::State g_State =
    {
        false,
        BlankStageTools::Mode::Off,
        false,
        false,
        false,
        true,
        true,
        0,
        0,
        0,
        0,
        0,
        true,
        true,
        false
    };

    //Tells Game Were To Point Stuff
    bool IsReasonablePointer(std::uintptr_t p)
    {
        return p > 0x10000ull && p < 0x0000800000000000ull;
    }

    template <typename Fn>
    bool ProtectedWrite(Fn fn)
    {
#ifdef _MSC_VER
        __try
        {
            fn();
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
#else
        fn();
        return true;
#endif
    }

    unsigned int CountPointerRange(std::uintptr_t begin, std::uintptr_t end)
    {
        if (!IsReasonablePointer(begin) || !IsReasonablePointer(end) || end < begin)
            return 0;
        const std::uintptr_t bytes = end - begin;
        if ((bytes & 7ull) != 0 || bytes > (8ull * 200000ull))
            return 0;
        return static_cast<unsigned int>(bytes / 8ull);
    }

    const char* ModeName(BlankStageTools::Mode mode)
    {
        switch (mode)
        {
        case BlankStageTools::Mode::SkipVanillaProps: return "Skip vanilla props";
        case BlankStageTools::Mode::SkipPropsAndMobs: return "Skip props and mobs";
        default: return "Off";
        }
    }
}
//Just here To hold All Props stuff For a Blank Stage. This is used for testing and modding.
namespace BlankStageTools
{

    //Just Checks Prop States.
    State& GetState()
    {
        return g_State;
    }

	//Just Sets The Mode For The Blank Stage.
    void SetMode(Mode mode)
    {
        g_State.mode = mode;
        g_State.enabled = mode != Mode::Off;
        g_State.skipStageObjects = mode == Mode::SkipVanillaProps || mode == Mode::SkipPropsAndMobs;
        g_State.skipMobDummies = mode == Mode::SkipPropsAndMobs;
        g_State.skipRandomMobDummies = mode == Mode::SkipPropsAndMobs;
        g_State.keepBossAndCamera = true;

        std::ostringstream oss;
        oss << "BlankStage mode changed: " << ModeName(mode)
            << " | skipStageObjects=" << g_State.skipStageObjects
            << " skipMobDummies=" << g_State.skipMobDummies
            << " keepBossAndCamera=" << g_State.keepBossAndCamera;
        Logger::Info(oss.str());
    }
    //Reset Objects
    void ResetCounters()
    {
        g_State.skippedStageObjects = 0;
        g_State.skippedMobDummies = 0;
        g_State.skippedRandomMobs = 0;
    }

    //Updates Live Counter With All Activate Objects in Stage.
    void UpdateActiveCounts(unsigned int stageObjectCount, unsigned int mobObjectCount)
    {
        g_State.activeStageObjects = stageObjectCount;
        g_State.activeMobObjects = mobObjectCount;
    }
    //Hooks The Stages To Get Objects Names Values Ect.
    void ArmRealHookMode(bool armed)
    {
        g_State.realHookModeArmed = armed;
        Logger::Info(armed ? "BlankStage: real hook mode armed." : "BlankStage: real hook mode disarmed.");
    }
	//Checks If Stage Should Skips Objects Spawn depending if Something Breaking Ect.
    bool ShouldSkipStageObjectSpawn(std::uintptr_t callerAddress)
    {
        (void)callerAddress;
        if (!g_State.enabled || !g_State.skipStageObjects)
            return false;
        ++g_State.skippedStageObjects;
        if (g_State.logDecisions)
            Logger::Info("BlankStage: would skip StageObjectManager_SpawnObjectFromDescriptor call.");
        return true;
    }
    //Check If Stage Should Skip Dummy Spawn If Functally Working.
    bool ShouldSkipMobDummySpawn(std::uintptr_t callerAddress)
    {
        (void)callerAddress;
        if (!g_State.enabled || !g_State.skipMobDummies)
            return false;
        ++g_State.skippedMobDummies;
        if (g_State.logDecisions)
            Logger::Info("BlankStage: would skip BossStage_SpawnMobDummyByName call.");
        return true;
    }

    //Just Skips The Random Version Of The Function Above This One. Dont Know Why It Exist But Its Here.
    bool ShouldSkipRandomMobSpawn(std::uintptr_t callerAddress)
    {
        (void)callerAddress;
        if (!g_State.enabled || !g_State.skipRandomMobDummies)
            return false;
        ++g_State.skippedRandomMobs;
        if (g_State.logDecisions)
            Logger::Info("BlankStage: would skip BossStage_SpawnRandomMobDummy call.");
        return true;
    }

    //Just Count All The Active Vectors And Were They Point To.
    unsigned int CountVectorPointers(std::uintptr_t vectorBase)
    {
        if (!IsReasonablePointer(vectorBase))
            return 0;
#ifdef _MSC_VER
        __try
        {
            const std::uintptr_t begin = *reinterpret_cast<std::uintptr_t*>(vectorBase + 0x00);
            const std::uintptr_t end = *reinterpret_cast<std::uintptr_t*>(vectorBase + 0x08);
            return CountPointerRange(begin, end);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
#else
        const std::uintptr_t begin = *reinterpret_cast<std::uintptr_t*>(vectorBase + 0x00);
        const std::uintptr_t end = *reinterpret_cast<std::uintptr_t*>(vectorBase + 0x08);
        return CountPointerRange(begin, end);
#endif
    }
    //Generate A List Of All Object Actve. 
    unsigned int CountStageObjectList(std::uintptr_t stageObjectListBase)
    {
        if (!IsReasonablePointer(stageObjectListBase))
            return 0;
#ifdef _MSC_VER
        __try
        {
            const std::uintptr_t begin = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x08);
            const std::uintptr_t end = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x10);
            return CountPointerRange(begin, end);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
#else
        const std::uintptr_t begin = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x08);
        const std::uintptr_t end = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x10);
        return CountPointerRange(begin, end);
#endif
    }

    ListOperationResult SetStageObjectListDrawUpdate(std::uintptr_t stageObjectListBase, bool enabled)
    {
        ListOperationResult out{ 0, 0, 0, false };
        if (!IsReasonablePointer(stageObjectListBase))
            return out;

        const bool ok = ProtectedWrite([&]()
        {
            const std::uintptr_t begin = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x08);
            const std::uintptr_t end = *reinterpret_cast<std::uintptr_t*>(stageObjectListBase + 0x10);
            out.total = CountPointerRange(begin, end);
            if (!out.total)
                return;

            std::uintptr_t* entries = reinterpret_cast<std::uintptr_t*>(begin);
            for (unsigned int i = 0; i < out.total; ++i)
            {
                const std::uintptr_t raw = entries[i];
                if (!IsReasonablePointer(raw))
                {
                    ++out.invalid;
                    continue;
                }

                
                // raw + 448 = update flag, raw + 452 = draw flag.
                *reinterpret_cast<int*>(raw + 448) = enabled ? 1 : 0;
                *reinterpret_cast<int*>(raw + 452) = enabled ? 1 : 0;
                ++out.changed;
            }
        });

        out.success = ok;
        g_State.activeStageObjects = out.total;
        Logger::Info(std::string(enabled ? "StageObjectList: show/update enabled " : "StageObjectList: hide/update disabled ") +
            "total=" + std::to_string(out.total) +
            " changed=" + std::to_string(out.changed) +
            " invalid=" + std::to_string(out.invalid));
        return out;
    }

    //Just Logs Random Stuff.
    void LogPlan()
    {
        Logger::Info("BlankStage hook plan:");
        Logger::Info("  1) Gate StageObjectManager_SpawnObjectFromDescriptor / sub_1402CC0D8 for vanilla prop loop only.");
        Logger::Info("  2) Gate BossStage_SpawnMobDummyByName / sub_1402CBFC0 when full blank mode is enabled.");
        Logger::Info("  3) Gate BossStage_SpawnRandomMobDummy / sub_1402CBE48 when full blank mode is enabled.");
        Logger::Info("  4) Keep camera, boss/player setup, EFFECT_EVENT, BossStage_FinalizeLoad, and BossStage_CreateBossUIManager.");
        Logger::Info("  5) Any-stage mode hooks the generic spawn paths instead of hardcoding STAGE_SI31B.");
        Logger::Info("  6) Current-stage blank should hide active RuntimeModels first, not free/delete them.");
    }
}
