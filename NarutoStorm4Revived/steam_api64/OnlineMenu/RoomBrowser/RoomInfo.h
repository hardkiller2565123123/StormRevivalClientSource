#pragma once
#include <string>
#include <vector>
#include "../PlayerList/PlayerInfo.h"

namespace StormRevival::OnlineMenu::RoomBrowser
{
    enum class RoomMode
    {
        Unknown,
        PlayerMatch,
        RankMatch,
        EndlessMatch,
        Tournament
    };

    struct RoomInfo
    {
        int roomId = -1;
        std::string roomName;
        std::string hostName;
        RoomMode mode = RoomMode::Unknown;
        int uiMode = 100;
        int currentPlayers = 0;
        int maxPlayers = 0;
        bool locked = false;
        bool voiceEnabled = false;
        bool hostIcon = false;
        std::vector<PlayerList::PlayerInfo> players;
    };
}
