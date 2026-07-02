#pragma once
#include <cstdint>

namespace StageRuntimeHookPlan
{
    struct KnownVectorOffsets
    {
        std::uintptr_t stageObjectVectorOffset; // a1 + 792: begin/end/cap of stage props
        std::uintptr_t mobObjectVectorOffset;   // a1 + 840: begin/end/cap of mob dummies
    };

    struct HookTarget
    {
        const char* name;
        const char* address;
        const char* safeReturn;
        const char* purpose;
    };

    const KnownVectorOffsets& GetVectorOffsets();
    const HookTarget* GetHookTargets(int* count);

    // Read-only helper for HUD counters once the current stage context pointer is known.
    unsigned int CountPointerVector(std::uintptr_t vectorBase);
}
