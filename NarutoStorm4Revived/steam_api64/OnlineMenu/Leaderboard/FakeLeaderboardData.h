#pragma once
#include <string>
#include <vector>

namespace StormRevival::OnlineMenu::Leaderboard
{
    /*
        Local-only fake leaderboard model.

        This is intentionally deterministic and offline. It does not call Supabase,
        Steam backend, public services, or any private API. It exists so the open
        source offline build can show realistic leaderboard rows while the real
        backend is still being researched.
    */
    struct FakePlayerCard
    {
        std::string Title;
        std::string Region;
        std::string MainCharacter;
        std::string FavoriteMode;
        int Wins = 0;
        int Losses = 0;
        int WinStreak = 0;
    };

    struct FakeLeaderboardEntry
    {
        int Rank = 0;
        std::string Name;
        int BP = 0;
        int Grade = 0;
        FakePlayerCard Card;
    };

    const std::vector<FakeLeaderboardEntry>& GetFakeLeaderboard();
    std::string BuildLeaderboardVoiceText(int maxRows = 10);
    std::string BuildPlayerCardText(const FakeLeaderboardEntry& entry);
}
