#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Research
{
    struct LobbyRoomLayout
    {
        static constexpr int CurrentPlayers = 0x28; // +40
        static constexpr int MaxPlayers     = 0x2C; // +44
        static constexpr int PlayerBase     = 0xE8; // +232
        static constexpr int PlayerStride   = 0x48; // 72
    };

    struct LobbyPlayerLayout
    {
        static constexpr int HostFlag   = 0x24; // +36
        static constexpr int VoiceState = 0x28; // +40
        static constexpr int PingValue  = 0x2C; // +44
        static constexpr int PlayerId   = 0x40; // +64
    };

    enum class LobbyUiMode : int
    {
        Mode100 = 100,
        Mode110 = 110,
        Mode120 = 120,
        Mode130 = 130,
        Mode140 = 140
    };

    int PingToBars(int pingMs);
    int LobbyGameModeToUiMode(int gameMode);
    const char* LatestReverseEngineeringPercent();
    const char* LatestNextSubs();
}
