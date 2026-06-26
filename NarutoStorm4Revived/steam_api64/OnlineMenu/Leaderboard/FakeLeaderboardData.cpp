#include "FakeLeaderboardData.h"

#include <algorithm>
#include <sstream>

namespace StormRevival::OnlineMenu::Leaderboard
{
    const std::vector<FakeLeaderboardEntry>& GetFakeLeaderboard()
    {
        static const std::vector<FakeLeaderboardEntry> rows =
        {
            { 1, "StormSage",       98240, 15, { "Hero of the Storm", "NA",   "Naruto",        "Ranked",       428,  51, 22 } },
            { 2, "UchihaByte",      94110, 14, { "Sharingan Analyst", "EU",   "Sasuke",        "Player Match", 401,  63, 18 } },
            { 3, "LeafPacket",      90275, 14, { "LAN Veteran",       "NA",   "Minato",        "Endless",      377,  80, 12 } },
            { 4, "RamenRouter",     86190, 13, { "Hidden Port Master","ASIA", "Kakashi",       "Ranked",       350,  91, 11 } },
            { 5, "AkatsukiPing",    82860, 13, { "Red Cloud",         "JP",   "Itachi",        "Tournament",   329, 104,  9 } },
            { 6, "NinjaPacket",     79010, 12, { "Packet Shinobi",    "EU",   "Madara",        "Ranked",       310, 113,  8 } },
            { 7, "ChakraCache",     75440, 12, { "Local Save Hero",   "NA",   "Hinata",        "Player Match", 288, 120,  7 } },
            { 8, "NineTailNet",     71125, 11, { "Offline Beast",     "ASIA", "Obito",         "Endless",      260, 130,  6 } },
            { 9, "SenjuSocket",     68770, 11, { "First Hokage LAN",  "NA",   "Hashirama",     "Ranked",       249, 141,  5 } },
            {10, "ScrollSync",      65005, 10, { "Archive Keeper",    "EU",   "Sakura",        "Free Battle",  231, 150,  4 } },
            {11, "HiddenHost",      62190, 10, { "Lobby Founder",     "NA",   "Shisui",        "Player Match", 220, 160,  4 } },
            {12, "ByakuganBuild",   59880,  9, { "Open Source Ninja", "JP",   "Neji",          "Tournament",   201, 170,  3 } },
        };

        return rows;
    }

    std::string BuildPlayerCardText(const FakeLeaderboardEntry& entry)
    {
        std::ostringstream ss;
        ss << "Player Card\\n"
           << "Name: " << entry.Name << "\\n"
           << "Rank: #" << entry.Rank << "\\n"
           << "BP: " << entry.BP << "\\n"
           << "Grade: " << entry.Grade << "\\n"
           << "Title: " << entry.Card.Title << "\\n"
           << "Region: " << entry.Card.Region << "\\n"
           << "Main: " << entry.Card.MainCharacter << "\\n"
           << "Mode: " << entry.Card.FavoriteMode << "\\n"
           << "W/L: " << entry.Card.Wins << "/" << entry.Card.Losses << "\\n"
           << "Streak: " << entry.Card.WinStreak;
        return ss.str();
    }

    std::string BuildLeaderboardVoiceText(int maxRows)
    {
        const auto& rows = GetFakeLeaderboard();
        const int count = std::max(0, std::min(maxRows, static_cast<int>(rows.size())));

        std::ostringstream ss;
        ss << "StormRevival Local Leaderboard\\n";
        for (int i = 0; i < count; ++i)
        {
            const auto& row = rows[static_cast<size_t>(i)];
            ss << row.Rank << ". " << row.Name << " - " << row.BP << " BP";
            if (i + 1 < count)
                ss << "\\n";
        }

        return ss.str();
    }
}
