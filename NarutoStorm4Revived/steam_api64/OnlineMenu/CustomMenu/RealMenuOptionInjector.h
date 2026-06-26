#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    struct InjectionResult
    {
        bool Attempted = false;
        bool Added = false;
        int AddedCount = 0;
    };

    // This is the non-replacement path. It does not hijack Store/BingoBook.
    // It is designed to be called when netbattlemainmenu is initialized or refreshed.
    //
    // Current safe behavior:
    // - Registers synthetic option modes 100/101/102 in C++.
    // - Traces the intended Flash insertion.
    //
    // To make it render as a real row, wire one of these:
    // - netbattlemainmenu option provider hook
    // - SelectNo/SelectNo2 callback table extension
    // - SWF option list edit
    InjectionResult TryAddRowsBelowOnlineMatch(GamePtr netBattleMainMenuUi);

    // Call this from the menu action callback. This handles only the new synthetic modes.
    bool HandleSyntheticMode(GamePtr menuUi, int mode);
}
