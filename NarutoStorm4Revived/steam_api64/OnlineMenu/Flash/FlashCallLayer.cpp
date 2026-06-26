#include "FlashCallLayer.h"

namespace StormRevival::OnlineMenu::Flash
{
    static FlashSymbols g_symbols{};

    void SetSymbols(const FlashSymbols& symbols)
    {
        g_symbols = symbols;
    }

    const FlashSymbols& Symbols()
    {
        return g_symbols;
    }

    bool CanUse()
    {
        return g_symbols.callFlashWithArgs != 0 || g_symbols.callFlashNoArgs != 0;
    }

    void CallNoArgs(GamePtr, const char*, const char*, const char*)
    {
        // TODO:
        // Once addresses are resolved, call:
        // sub_140607B5C(ui, movie, root, functionName)
    }

    void CallString(GamePtr, const char*, const char*, const char*, const char*)
    {
        // TODO:
        // Build game ASValue/string argument and call:
        // sub_140607BA0(ui, movie, root, functionName, 0, args, 1)
    }
}
