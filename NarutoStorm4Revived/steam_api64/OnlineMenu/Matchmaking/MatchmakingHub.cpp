#include "MatchmakingHub.h"

namespace StormRevival::OnlineMenu::Matchmaking
{
    void MatchmakingHub::SetState(const MatchmakingState& state)
    {
        m_state = state;
    }

    const MatchmakingState& MatchmakingHub::State() const
    {
        return m_state;
    }
}
