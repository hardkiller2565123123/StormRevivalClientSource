#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Leaderboard
{
    struct LeaderboardRow
    {
        int rank = 0;
        const char* name = "";
        int score = 0;
    };

    void ShowLeaderboardStub(std::uintptr_t ui);
}
