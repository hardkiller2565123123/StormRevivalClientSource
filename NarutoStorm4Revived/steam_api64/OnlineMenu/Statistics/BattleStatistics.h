#pragma once

namespace StormRevival::OnlineMenu::Statistics
{
    struct BattleStatistics
    {
        int bp = 0;
        int rank = 0;
        int wins = 0;
        int losses = 0;
        int winStreak = 0;
        int disconnects = 0;
    };

    inline int TotalMatches(const BattleStatistics& stats)
    {
        return stats.wins + stats.losses;
    }
}
