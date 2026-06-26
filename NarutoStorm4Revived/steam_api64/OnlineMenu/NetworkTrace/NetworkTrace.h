#pragma once
#include <string>

namespace StormRevival::OnlineMenu::NetworkTrace
{
    enum class NetEventType
    {
        Unknown,
        CreateRoom,
        SearchRoom,
        JoinRoom,
        LeaveRoom,
        StartBattle,
        LobbyUpdate,
        PlayerJoin,
        PlayerLeave
    };

    void LogEvent(NetEventType type, const std::string& message);
}
