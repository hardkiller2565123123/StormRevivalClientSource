#include "NetworkTrace.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::NetworkTrace
{
    static const char* Name(NetEventType type)
    {
        switch (type)
        {
        case NetEventType::CreateRoom: return "CreateRoom";
        case NetEventType::SearchRoom: return "SearchRoom";
        case NetEventType::JoinRoom: return "JoinRoom";
        case NetEventType::LeaveRoom: return "LeaveRoom";
        case NetEventType::StartBattle: return "StartBattle";
        case NetEventType::LobbyUpdate: return "LobbyUpdate";
        case NetEventType::PlayerJoin: return "PlayerJoin";
        case NetEventType::PlayerLeave: return "PlayerLeave";
        default: return "Unknown";
        }
    }

    void LogEvent(NetEventType type, const std::string& message)
    {
        Log::Info(std::string("NetworkTrace ") + Name(type) + ": " + message);
    }
}
