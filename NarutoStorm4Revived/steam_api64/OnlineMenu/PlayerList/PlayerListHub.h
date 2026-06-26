#pragma once
#include <vector>
#include "PlayerInfo.h"

namespace StormRevival::OnlineMenu::PlayerList
{
    class PlayerListHub
    {
    public:
        void Clear();
        void AddOrUpdate(const PlayerInfo& player);
        const std::vector<PlayerInfo>& Players() const;

    private:
        std::vector<PlayerInfo> m_players;
    };
}
