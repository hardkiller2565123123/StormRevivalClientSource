#pragma once
#include <cstdint>
#include <string>

namespace StormRevival
{
    enum class RuntimePatchKind
    {
        FixedAddressHook,
        OnlineMenuMutation,
        StoreReplacement,
        SyntheticMenuMode,
        SlotExpansion,
        CharacterRosterPatch,
        StageSceneExpansion,
        ResourceMemoryPatch
    };

    struct RuntimeExeProfile
    {
        bool supported = false;
        bool fixedAddressesAllowed = false;
        bool safeModeUnknownExe = true;
        std::uint32_t crc32 = 0;
        std::uint64_t size = 0;
        std::string name;
        std::string reason;
    };

    class RuntimeSafetyGate
    {
    public:
        static void Initialize();
        static const RuntimeExeProfile& Profile();

        // True only when this patch is safe for the current executable.
        static bool Allow(RuntimePatchKind kind);

        // Logs a compact one-line summary. Does not spam hook tables.
        static void LogSummaryOnce();

        static bool IsSupportedExe();
        static bool IsUnknownExeSafeMode();

    private:
        static RuntimeExeProfile DetectCurrentExe();
    };
}
