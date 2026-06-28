#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace StormRevival::OnlineMenu::Hooking
{
    enum class HookGroup
    {
        UI,
        ActionScript,
        Resources,
        Stage,
        Scenario,
        Scene,
        Entity,
        Network,
        Debug
    };

    struct HookSpec
    {
        const char* Name;
        HookGroup Group;
        std::uintptr_t AbsoluteAddress;
        void* Detour;
        void** Original;
        const char* Notes;
        const char* Pattern;
        int PatternOffset;
    };

    struct HookState
    {
        std::string Name;
        HookGroup Group;
        std::uintptr_t AbsoluteAddress;
        std::uintptr_t RuntimeAddress;
        bool ResolvedByPattern;
        bool Created;
        bool Enabled;
        std::string Notes;
        std::string Error;
    };

    bool InstallHook(const HookSpec& spec);
    void InstallHooks(const HookSpec* specs, int count);
    void DisableAll();
    void DumpHookTable();
    const std::vector<HookState>& GetHookStates();

    std::uintptr_t ResolveAbsolute(std::uintptr_t absoluteAddress);
    const char* GroupName(HookGroup group);
}
