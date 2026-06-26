#include "SettingsHub.h"
#include "../Leaderboard/FakeLeaderboardData.h"
#include "../MainMenu/NetBattleMainMenu.h"
#include "../Research/Progress.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::Settings
{
    void Show(GamePtr ui)
    {
        /*
            This is the local offline Settings screen.
            It is opened by reusing the stock Store button until a true extra SWF row
            is solved. No external store or network service is contacted.
        */
        MainMenu::VoiceIn(ui);
        MainMenu::RenameStoreButtonToSettings(ui);
        MainMenu::SetVoiceText(
            ui,
            "StormRevival Settings\\n"
            "Mode: Offline local\\n"
            "Leaderboard: fake local rows\\n"
            "Store: blocked and rerouted\\n"
            "Online Menu RE: see docs");

        Log::Info("StormRevival Settings opened from Store replacement.");
        Log::Info("Research progress: " + std::string(Research::ProgressTable));
        Log::Info("Fake leaderboard rows available: " + std::to_string(Leaderboard::GetFakeLeaderboard().size()));
    }
}
