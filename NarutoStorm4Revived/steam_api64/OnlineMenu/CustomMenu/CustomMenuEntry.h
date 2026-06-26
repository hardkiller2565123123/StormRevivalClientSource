#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    enum class EntryPlacement
    {
        BelowOnlineMatch,
        ReuseStore,
        ReuseBingoBook,
        ReuseExistingSafeButton
    };

    struct EntryDefinition
    {
        const char* Label = "StormRevival Settings";
        const char* Description = "Player count, unlock stubs, status, and research tools.";
        EntryPlacement Placement = EntryPlacement::BelowOnlineMatch;
        bool Enabled = true;
    };

    void Install();
    void Shutdown();

    void OnCustomEntrySelected();
    void TryInjectBelowOnlineMatch(GamePtr netBattleMainMenuUi);
}
