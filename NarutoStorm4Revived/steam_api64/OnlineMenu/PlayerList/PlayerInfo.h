#pragma once
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::PlayerList
{
    struct PlayerInfo
    {
        int slot = -1;
        int sourceIndex = -1;
        int playerId = -1;
        std::uint64_t steamId = 0;

        std::string name;
        bool occupied = false;
        bool selected = false;
        bool host = false;
        bool friendIcon = false;
        bool voiceEnabled = false;

        int pingMs = 0;
        int signalBars = 0;
        int winStreak = 0;
        int iconOrTitle = 0;
        int bp = 0;
        int rank = 0;
    };

    int PingToBars(int pingMs);
}
