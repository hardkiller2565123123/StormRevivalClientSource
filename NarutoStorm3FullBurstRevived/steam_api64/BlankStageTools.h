#pragma once
#include <cstdint>

namespace BlankStageTools
{
    enum class Mode
    {
        Off = 0,
        SkipVanillaProps,
        SkipPropsAndMobs
    };

    struct State
    {
        bool enabled;
        Mode mode;
        bool skipStageObjects;
        bool skipMobDummies;
        bool skipRandomMobDummies;
        bool keepBossAndCamera;
        bool logDecisions;
        unsigned int skippedStageObjects;
        unsigned int skippedMobDummies;
        unsigned int skippedRandomMobs;
        unsigned int activeStageObjects;
        unsigned int activeMobObjects;
        bool anyStageMode;
        bool hideInsteadOfDestroy;
        bool realHookModeArmed;
    };

    State& GetState();
    void SetMode(Mode mode);
    void ResetCounters();
    void UpdateActiveCounts(unsigned int stageObjectCount, unsigned int mobObjectCount);
    void ArmRealHookMode(bool armed);

    // Safe gate helpers. These are designed to be called from hooks once the
    // exact hook addresses/signatures are verified in IDA.
    bool ShouldSkipStageObjectSpawn(std::uintptr_t callerAddress);
    bool ShouldSkipMobDummySpawn(std::uintptr_t callerAddress);
    bool ShouldSkipRandomMobSpawn(std::uintptr_t callerAddress);

    struct ListOperationResult
    {
        unsigned int total;
        unsigned int changed;
        unsigned int invalid;
        bool success;
    };

    // Real runtime helpers for verified pointers. These do not call fake subs.
    // StageObjectList layout confirmed from sub_1405C0590/sub_1405C06E4/sub_1405C0788:
    // +0x08 begin, +0x10 end, entries are raw pointers, raw+448 update flag, raw+452 draw flag.
    unsigned int CountVectorPointers(std::uintptr_t vectorBase);
    unsigned int CountStageObjectList(std::uintptr_t stageObjectListBase);
    ListOperationResult SetStageObjectListDrawUpdate(std::uintptr_t stageObjectListBase, bool enabled);

    void LogPlan();
}
