#pragma once
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu::Lobby
{
    struct LobbyPlayerSnapshot
    {
        int slot = -1;
        int playerId = -1;
        bool selected = false;
        bool host = false;
        int voiceState = 0;
        bool voiceActive = false;
        int pingValue = 0;
        int signalBars = 0;
        int friendState = 0;
        std::string personaName;
        int iconOrTitle = 0;
    };

    struct LobbyRoomSnapshot
    {
        int currentPlayers = 0;
        int maxPlayers = 0;
        int selectedSlot = -1;
        int uiMode = 100;
        bool locked = false;
        bool userPanelVisible = false;
    };

    inline int PlayerOffset(int index)
    {
        return 0xE8 + (index * 0x48);
    }
}
