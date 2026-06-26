#include "PlayerInfo.h"

namespace StormRevival::OnlineMenu::PlayerList
{
    int PingToBars(int pingMs)
    {
        if (pingMs <= 0) return 0;
        if (pingMs <= 70) return 3;
        if (pingMs <= 250) return 2;
        return 1;
    }
}
