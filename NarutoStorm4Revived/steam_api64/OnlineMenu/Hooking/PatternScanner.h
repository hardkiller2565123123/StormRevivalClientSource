#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Hooking
{
    struct PatternResult
    {
        bool Found;
        std::uintptr_t Address;
        const char* Error;
    };

    // Scans the main NSUNS4.exe image. Pattern format: "48 8B ?? ?? 89".
    // The scanner searches executable sections only by default.
    PatternResult FindPatternInMainModule(const char* idaPattern, int relativeOffset = 0, bool executableOnly = true);
}
