#include "RoomBrowserHub.h"

namespace StormRevival::OnlineMenu::RoomBrowser
{
    void RoomBrowserHub::Clear()
    {
        m_rooms.clear();
    }

    void RoomBrowserHub::AddRoom(const RoomInfo& room)
    {
        m_rooms.push_back(room);
    }

    const std::vector<RoomInfo>& RoomBrowserHub::Rooms() const
    {
        return m_rooms;
    }
}
