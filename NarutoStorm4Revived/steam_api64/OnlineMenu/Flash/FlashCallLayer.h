#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Flash
{
    using GamePtr = std::uintptr_t;

    // Research names only. These are NOT safe to call until addresses are resolved for your exe.
    struct FlashSymbols
    {
        GamePtr callFlashWithArgs = 0;   // sub_140607BA0
        GamePtr callFlashNoArgs   = 0;   // sub_140607B5C
        GamePtr callFlashReturn   = 0;   // sub_140607B7C
        GamePtr objectExists      = 0;   // sub_140607CBC
        GamePtr loadMovie         = 0;   // sub_14060759C
    };

    void SetSymbols(const FlashSymbols& symbols);
    const FlashSymbols& Symbols();

    // Safe research wrapper: logs intended calls, does not patch memory by default.
    bool CanUse();
    void CallNoArgs(GamePtr ui, const char* movie, const char* root, const char* functionName);
    void CallString(GamePtr ui, const char* movie, const char* root, const char* functionName, const char* text);
}
