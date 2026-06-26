#pragma once
#include <vector>
#include "RoomInfo.h"

namespace StormRevival::OnlineMenu::RoomBrowser
{
    class RoomBrowserHub
    {
    public:
        void Clear();
        void AddRoom(const RoomInfo& room);
        const std::vector<RoomInfo>& Rooms() const;

    private:
        std::vector<RoomInfo> m_rooms;
    };
}
