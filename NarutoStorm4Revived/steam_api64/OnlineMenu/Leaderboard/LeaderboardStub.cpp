#include "LeaderboardStub.h"
#include "FakeLeaderboardData.h"

namespace StormRevival::OnlineMenu::Leaderboard
{
    void ShowLeaderboardStub(std::uintptr_t)
    {
        /*
            Offline fake leaderboard stub.

            The real ranking pipeline is still being reversed. Current known ranking
            strings include BATTLE_RANKING_BP_* and BATTLE_RANKING_RANK_WIN_*.
            Until the Steam leaderboard backend replacement is complete, this local
            list gives the UI a realistic data source for testing.
        */
        (void)GetFakeLeaderboard();
    }
}
