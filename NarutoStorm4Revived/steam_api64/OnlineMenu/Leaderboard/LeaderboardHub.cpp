#include "LeaderboardHub.h"
#include "FakeLeaderboardData.h"
#include "../MainMenu/NetBattleMainMenu.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::Leaderboard
{
    void Show(GamePtr ui)
    {
        // Local fake data path. This is safe for GitHub and does not expose any service keys.
        MainMenu::VoiceIn(ui);
        MainMenu::SetVoiceText(ui, BuildLeaderboardVoiceText(10).c_str());

        Log::Info("Local fake leaderboard opened.");
        for (const auto& row : GetFakeLeaderboard())
        {
            Log::Info("Leaderboard row #" + std::to_string(row.Rank) +
                " name=" + row.Name +
                " bp=" + std::to_string(row.BP) +
                " card={" + row.Card.Title + ", " + row.Card.Region + ", " + row.Card.MainCharacter + "}");
        }
    }
}
