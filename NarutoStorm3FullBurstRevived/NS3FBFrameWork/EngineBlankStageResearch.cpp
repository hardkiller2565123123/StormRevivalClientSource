#include "EngineBlankStageResearch.h"
#include <windows.h>
#include <cstdio>

namespace
{
    void DebugLine(const char* text)
    {
        OutputDebugStringA(text);
        OutputDebugStringA("\n");
    }
}

namespace EngineBlankStageResearch
{
    void LogSummary()
    {
        DebugLine("[BlankStageResearch] Spawn path: sub_1402CC0D8 -> sub_1402E20A4 -> sub_140687CC0 -> sub_14068B540");
        DebugLine("[BlankStageResearch] Vanilla prop loops: sub_1402CA87C and sub_1402CBA28");
        DebugLine("[BlankStageResearch] Skip targets: sub_1402CC0D8, sub_1402CBFC0, sub_1402CBE48");
        DebugLine("[BlankStageResearch] Keep: sub_1402CB928, sub_1402CA7F0, sub_1402C9D80, camera, boss/player, EFFECT_EVENT");
    }
}
