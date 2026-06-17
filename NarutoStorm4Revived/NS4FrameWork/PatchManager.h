#pragma once
#include "StdInc.h"

namespace PatchManager
{
    struct PatchState
    {
        bool BorderlessFullscreen = true;
        bool NativeUltrawide = false;
        bool MultiMonitor = false;
        bool DisableIntro = false;
        bool AutoSkipCutscenes = false;
        bool UnlockAllTemporary = false;
        bool UnlockAllPermanent = false;
        bool HighRefreshFix = false;
        bool BackgroundPauseFix = true;
        bool SkipOnlineChecks = true;
        bool RuntimePatchLab = true;
    };

    struct RuntimePatchInfo
    {
        std::string Name;
        uintptr_t Rva = 0;
        size_t Size = 0;
        bool Applied = false;
        std::string Status;
    };

    struct RuntimePatchResult
    {
        bool Success = false;
        uintptr_t Address = 0;
        size_t BytesChanged = 0;
        std::string Status;
    };

    bool Init();
    void Shutdown();

    PatchState& State();
    const PatchState& GetState();

    void ApplySafePatches();
    void ApplyDisplayPatches();
    void ApplyGameplayPatches();

    uintptr_t ModuleBase();
    RuntimePatchResult ApplyRuntimePatchByRva(const std::string& name, uintptr_t rva, const std::vector<unsigned char>& expected, const std::vector<unsigned char>& replacement);
    RuntimePatchResult ApplyRuntimePatchByPattern(const std::string& name, const std::vector<unsigned char>& pattern, const std::vector<unsigned char>& replacement);
    RuntimePatchResult RevertRuntimePatch(const std::string& name);
    const std::vector<RuntimePatchInfo>& RuntimePatches();
    std::string RuntimePatchSummary();
}
