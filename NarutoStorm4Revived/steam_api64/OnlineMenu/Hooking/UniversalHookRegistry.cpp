#include "UniversalHookRegistry.h"
#include "PatternScanner.h"
#include "../Core/VersionGuard.h"
#include "HookManager.h"
#include "../Core/SRLogger.h"
#include <Windows.h>
#include <sstream>
#include <iomanip>

namespace StormRevival::OnlineMenu::Hooking
{
    namespace
    {
        std::vector<HookState> g_states;
        constexpr std::uintptr_t ImageBaseLabel = 0x140000000ULL;

        std::string Hex(std::uintptr_t value)
        {
            std::ostringstream ss;
            ss << "0x" << std::hex << std::uppercase << value;
            return ss.str();
        }

        bool IsExecutableAddress(std::uintptr_t address)
        {
            MEMORY_BASIC_INFORMATION mbi{};
            if (!VirtualQuery(reinterpret_cast<void*>(address), &mbi, sizeof(mbi)))
                return false;
            if (mbi.State != MEM_COMMIT)
                return false;
            const DWORD p = mbi.Protect & 0xFF;
            return p == PAGE_EXECUTE || p == PAGE_EXECUTE_READ || p == PAGE_EXECUTE_READWRITE || p == PAGE_EXECUTE_WRITECOPY;
        }

        bool ResolveHookRuntimeAddress(const HookSpec& spec, HookState& state)
        {
            state.RuntimeAddress = 0;
            state.ResolvedByPattern = false;

            const bool fixedAllowed = AreFixedAddressHooksAllowed();
            if (fixedAllowed && spec.AbsoluteAddress)
            {
                state.RuntimeAddress = ResolveAbsolute(spec.AbsoluteAddress);
                return true;
            }

            if (spec.Pattern && *spec.Pattern)
            {
                const PatternResult result = FindPatternInMainModule(spec.Pattern, spec.PatternOffset, true);
                if (result.Found)
                {
                    state.RuntimeAddress = result.Address;
                    state.ResolvedByPattern = true;
                    Log::Info("[Pattern OK] " + state.Name + " -> " + Hex(state.RuntimeAddress));
                    return true;
                }

                state.Error = std::string("Pattern scan failed: ") + (result.Error ? result.Error : "unknown error");
                return false;
            }

            state.Error = "Fixed address disabled for this EXE and no verified pattern exists yet";
            return false;
        }
    }

    const char* GroupName(HookGroup group)
    {
        switch (group)
        {
        case HookGroup::UI: return "UI";
        case HookGroup::ActionScript: return "ActionScript";
        case HookGroup::Resources: return "Resources";
        case HookGroup::Stage: return "Stage";
        case HookGroup::Scenario: return "Scenario";
        case HookGroup::Scene: return "Scene";
        case HookGroup::Entity: return "Entity";
        case HookGroup::Network: return "Network";
        case HookGroup::Debug: return "Debug";
        default: return "Unknown";
        }
    }

    std::uintptr_t ResolveAbsolute(std::uintptr_t absoluteAddress)
    {
        HMODULE exe = GetModuleHandleW(nullptr);
        const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(exe);
        if (absoluteAddress >= ImageBaseLabel)
            return base + (absoluteAddress - ImageBaseLabel);
        return base + absoluteAddress;
    }

    bool InstallHook(const HookSpec& spec)
    {
        HookState state;
        state.Name = spec.Name ? spec.Name : "<unnamed>";
        state.Group = spec.Group;
        state.AbsoluteAddress = spec.AbsoluteAddress;
        state.RuntimeAddress = 0;
        state.ResolvedByPattern = false;
        state.Notes = spec.Notes ? spec.Notes : "";
        state.Created = false;
        state.Enabled = false;

        if (!spec.Detour || !spec.Original)
        {
            state.Error = "Missing detour/original pointer";
            Log::Warn("[Hook SKIP] " + state.Name + " reason=" + state.Error);
            g_states.push_back(state);
            return false;
        }

        if (!ResolveHookRuntimeAddress(spec, state))
        {
            Log::Warn("[Hook SKIP] " + state.Name + " reason=" + state.Error);
            g_states.push_back(state);
            return false;
        }

        if (!IsExecutableAddress(state.RuntimeAddress))
        {
            state.Error = "Runtime address is not executable: " + Hex(state.RuntimeAddress);
            Log::Warn("[Hook SKIP] " + state.Name + " " + state.Error);
            g_states.push_back(state);
            return false;
        }

        if (!HookManager::Create(reinterpret_cast<void*>(state.RuntimeAddress), spec.Detour, spec.Original))
        {
            state.Error = "MH_CreateHook failed at " + Hex(state.RuntimeAddress);
            Log::Error("[Hook FAIL] " + state.Name + " " + state.Error);
            g_states.push_back(state);
            return false;
        }
        state.Created = true;

        if (!HookManager::Enable(reinterpret_cast<void*>(state.RuntimeAddress)))
        {
            state.Error = "MH_EnableHook failed at " + Hex(state.RuntimeAddress);
            Log::Error("[Hook FAIL] " + state.Name + " " + state.Error);
            g_states.push_back(state);
            return false;
        }

        state.Enabled = true;
        Log::Info("[Hook OK] [" + std::string(GroupName(spec.Group)) + "] " + state.Name +
                  " @ " + Hex(state.RuntimeAddress) +
                  (state.ResolvedByPattern ? " pattern" : " fixed") +
                  " " + state.Notes);
        g_states.push_back(state);
        return true;
    }

    void InstallHooks(const HookSpec* specs, int count)
    {
        for (int i = 0; specs && i < count; ++i)
            InstallHook(specs[i]);
    }

    void DisableAll()
    {
        for (auto& state : g_states)
        {
            if (state.Enabled)
            {
                HookManager::Disable(reinterpret_cast<void*>(state.RuntimeAddress));
                state.Enabled = false;
                Log::Info("[Hook OFF] " + state.Name);
            }
        }
    }

    void DumpHookTable()
    {
        Log::Info("========== StormRevival Universal Hook Table ==========");
        for (const auto& state : g_states)
        {
            Log::Info(std::string(state.Enabled ? "[ON]  " : "[OFF] ") +
                      "[" + GroupName(state.Group) + "] " + state.Name +
                      " abs=" + Hex(state.AbsoluteAddress) +
                      " runtime=" + Hex(state.RuntimeAddress) +
                      (state.ResolvedByPattern ? " pattern" : " fixed/none") +
                      (state.Error.empty() ? "" : " error=" + state.Error));
        }
    }

    const std::vector<HookState>& GetHookStates()
    {
        return g_states;
    }
}
