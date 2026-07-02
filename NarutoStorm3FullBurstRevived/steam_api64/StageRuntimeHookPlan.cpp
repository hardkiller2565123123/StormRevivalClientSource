#include "StdInc.h"
#include "StageRuntimeHookPlan.h"

namespace
{
    static const StageRuntimeHookPlan::KnownVectorOffsets kOffsets =
    {
        792, // stage prop active list: begin/end/cap pointer vector
        840  // mob dummy active list: begin/end/cap pointer vector
    };

    static const StageRuntimeHookPlan::HookTarget kTargets[] =
    {
        { "StageObjectManager_SpawnObjectFromDescriptor", "sub_1402CC0D8", "return 1", "Any-stage prop spawn gate. Skip to blank the stage props." },
        { "BossStage_SpawnMobDummyByName", "sub_1402CBFC0", "return 0", "Named mob dummy gate. Skip for full blank mode." },
        { "BossStage_SpawnRandomMobDummy", "sub_1402CBE48", "return 0", "Random mob dummy gate. Skip for full blank mode." },
        { "RuntimeModel_SetVisibility", "sub_140689200", "call only after pointer verification", "Hide/restore existing RuntimeModels for clean-current-stage mode." },
        { "GlobalChunkLookup", "sub_140734E30", "normal call", "Find selected asset by XFBIN path + chunk type + chunk name." }
    };
}

namespace StageRuntimeHookPlan
{
    const KnownVectorOffsets& GetVectorOffsets()
    {
        return kOffsets;
    }

    const HookTarget* GetHookTargets(int* count)
    {
        if (count)
            *count = static_cast<int>(sizeof(kTargets) / sizeof(kTargets[0]));
        return kTargets;
    }

    unsigned int CountPointerVector(std::uintptr_t vectorBase)
    {
        if (!vectorBase)
            return 0;

        const std::uintptr_t begin = *reinterpret_cast<const std::uintptr_t*>(vectorBase + 0);
        const std::uintptr_t end = *reinterpret_cast<const std::uintptr_t*>(vectorBase + 8);
        if (!begin || !end || end < begin)
            return 0;

        return static_cast<unsigned int>((end - begin) / sizeof(void*));
    }
}
