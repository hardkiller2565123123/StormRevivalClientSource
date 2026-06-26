#include "PlayerListHub.h"

namespace StormRevival::OnlineMenu::PlayerList
{
    void PlayerListHub::Clear()
    {
        m_players.clear();
    }

    void PlayerListHub::AddOrUpdate(const PlayerInfo& player)
    {
        for (auto& item : m_players)
        {
            if (item.slot == player.slot)
            {
                item = player;
                return;
            }
        }
        m_players.push_back(player);
    }

    const std::vector<PlayerInfo>& PlayerListHub::Players() const
    {
        return m_players;
    }
}
