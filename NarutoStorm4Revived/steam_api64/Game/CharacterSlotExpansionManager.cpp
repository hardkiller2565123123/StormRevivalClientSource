#include "CharacterSlotExpansionManager.h"
#include "Common.h"
#include "Logger.h"
#include "PatternScan.h"
#include "SlotExpansionManager.h"
#include "Storm4IdaRuntime.h"
#include <Windows.h>
#include <cstdio>
#include <cstring>

namespace
{
    bool g_DiagnosticsReady = false;
    bool g_RuntimeEnabled = false;
    char g_LastStatus[1536] = "Character slot diagnostics have not run.";

    bool IsStorm4()
    {
        return GameVersion && std::strcmp(GameVersion, "1.09") == 0;
    }

    bool IsConnections()
    {
        return GameVersion && std::strcmp(GameVersion, "1.60") == 0;
    }

    bool CanReadPointer(uintptr_t address)
    {
        if (!address)
            return false;

        __try
        {
            volatile uintptr_t value = *reinterpret_cast<uintptr_t*>(address);
            (void)value;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }
}

namespace CharacterSlotExpansionManager
{
    void Init()
    {
        g_RuntimeEnabled = SlotExpansionManager::GetConfig().EnableCharacterRosterRuntime;
        g_DiagnosticsReady = false;
        std::snprintf(g_LastStatus, sizeof(g_LastStatus),
            "Character roster runtime is %s. Diagnostics are safe; visible roster patch still needs select-grid offsets.",
            g_RuntimeEnabled ? "enabled" : "disabled");
        Logger::Info(g_LastStatus);
    }

    void RunDiagnostics()
    {
        const SlotExpansionConfig& config = SlotExpansionManager::GetConfig();
        const __int64 costumeLimitFunction = PatternScan::Scan("48xxxxxxxx55565741xx41xx41xx41xx48xxxxxxxxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxx");
        const __int64 costumeLimitCompare = PatternScan::Scan("488B7DA083F8");

        uintptr_t getCharCode = 0;
        uintptr_t getCostumeCode = 0;
        if (IsStorm4())
        {
            getCharCode = static_cast<uintptr_t>(moduleBase + 0x5289FC);
            getCostumeCode = static_cast<uintptr_t>(moduleBase + 0x528B18);
        }
        else if (IsConnections())
        {
            getCharCode = static_cast<uintptr_t>(moduleBase + 0x58F3D0);
            getCostumeCode = static_cast<uintptr_t>(moduleBase + 0x58F5A0);
        }

        const bool costumePatchFound = costumeLimitFunction > 1 && costumeLimitCompare > 1;
        const bool charLookupReadable = CanReadPointer(getCharCode);
        const bool costumeLookupReadable = CanReadPointer(getCostumeCode);
        const bool storm4IdaVersionOk = Storm4IdaRuntime::IsSupportedStorm4Version();
        const int storm4IdaTargetsPresent = storm4IdaVersionOk ? Storm4IdaRuntime::CountPresentTargets() : 0;
        size_t storm4IdaTargetCount = 0;
        Storm4IdaRuntime::Targets(storm4IdaTargetCount);
        const bool unlockCoreCallable = Storm4IdaRuntime::UnlockCharacterCheckCore() != nullptr;

        g_DiagnosticsReady = costumePatchFound && charLookupReadable && costumeLookupReadable;

        std::snprintf(g_LastStatus, sizeof(g_LastStatus),
            "Character diagnostics: version=%s targetChars=%d targetCostumes=%d costumePatch=%s charLookup=%s costumeLookup=%s idaTargets=%d/%zu unlockCore=%s visibleGridPatch=missing.",
            GameVersion ? GameVersion : "unknown",
            config.ExtraCharacterSlots,
            config.ExtraCostumeSlots,
            costumePatchFound ? "found" : "missing",
            charLookupReadable ? "readable" : "missing",
            costumeLookupReadable ? "readable" : "missing",
            storm4IdaTargetsPresent,
            storm4IdaTargetCount,
            unlockCoreCallable ? "callable" : "not callable");

        if (g_DiagnosticsReady)
            Logger::Info(g_LastStatus);
        else
            Logger::Error(g_LastStatus);
    }

    bool DiagnosticsReady()
    {
        return g_DiagnosticsReady;
    }

    bool RuntimeEnabled()
    {
        return g_RuntimeEnabled;
    }

    const char* LastStatus()
    {
        return g_LastStatus;
    }
}
