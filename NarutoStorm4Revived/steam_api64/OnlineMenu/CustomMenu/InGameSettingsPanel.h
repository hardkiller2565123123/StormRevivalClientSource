#pragma once

namespace StormRevival::OnlineMenu::CustomMenu
{
    struct InGameSettingsState
    {
        int CurrentPlayerCount = 0;
        bool UnlockAllVisible = true;
        bool UnlockAllEnabled = false;
        bool ServerStatusVisible = true;
        bool ResearchInfoVisible = true;
    };

    InGameSettingsState& State();
    void ShowSettingsPanel();
}
