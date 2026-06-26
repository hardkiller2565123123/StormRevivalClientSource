#include "MenuActionHookPlan.h"

namespace StormRevival::OnlineMenu::Buttons
{
    bool ShouldHijackMode(int mode)
    {
        // Start conservative. Do NOT hijack everything.
        // Recommended test: only hijack one known noncritical mode.
        return mode == 7; // current research says mode 7 is ignored.
    }

    void OnHijackedMode(const MenuActionEvent&)
    {
        // TODO:
        // Show Storm Revival popup/help/voice text here.
        //
        // Planned options:
        // - Server Status
        // - Player Count
        // - Leaderboard
        // - Settings
        // - Unlock All placeholder
    }
}
