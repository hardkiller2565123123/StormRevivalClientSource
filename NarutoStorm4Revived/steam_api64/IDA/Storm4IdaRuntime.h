#pragma once

#include <cstdint>
#include <cstddef>

namespace Storm4IdaRuntime
{
    enum class TargetKind
    {
        Function,
        String,
        DataTable
    };

    struct KnownTarget
    {
        const char* Name;
        uintptr_t Rva;
        TargetKind Kind;
        bool SignatureKnown;
        const char* Notes;
    };

    using UnlockCharacterCheckCoreFn = __int64(__fastcall*)();

    bool IsSupportedStorm4Version();
    uintptr_t Absolute(uintptr_t rva);
    bool IsReadable(uintptr_t absoluteAddress);
    bool IsExecutable(uintptr_t absoluteAddress);
    bool IsTargetPresent(const KnownTarget& target);
    const char* KindName(TargetKind kind);
    const KnownTarget* Targets(size_t& count);
    UnlockCharacterCheckCoreFn UnlockCharacterCheckCore();
    int CountPresentTargets();
}
