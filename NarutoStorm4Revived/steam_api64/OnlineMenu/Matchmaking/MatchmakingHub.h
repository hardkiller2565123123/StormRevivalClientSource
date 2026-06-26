#pragma once
#include <string>
#include "../RoomBrowser/RoomInfo.h"

namespace StormRevival::OnlineMenu::Matchmaking
{
    enum class MatchFlowState
    {
        Idle,
        Searching,
        CreatingRoom,
        JoiningRoom,
        InLobby,
        StartingBattle,
        Error
    };

    struct MatchmakingState
    {
        MatchFlowState state = MatchFlowState::Idle;
        RoomBrowser::RoomMode mode = RoomBrowser::RoomMode::Unknown;
        std::string statusText;
        int lastError = 0;
    };

    class MatchmakingHub
    {
    public:
        void SetState(const MatchmakingState& state);
        const MatchmakingState& State() const;

    private:
        MatchmakingState m_state;
    };
}
