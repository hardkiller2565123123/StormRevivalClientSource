#include "LatestLobbyResearch.h"

namespace StormRevival::OnlineMenu::Research
{
    int PingToBars(int pingMs)
    {
        if (pingMs <= 0) return 0;
        if (pingMs <= 70) return 3;
        if (pingMs <= 250) return 2;
        return 1;
    }

    int LobbyGameModeToUiMode(int gameMode)
    {
        switch (gameMode)
        {
        case 4: return 100;
        case 5: return 110;
        case 6: return 130;
        case 7: return 140;
        case 8: return 120;
        default: return 100;
        }
    }

    const char* LatestReverseEngineeringPercent()
    {
        return
            "Online Menu RE progress:\n"
            "Flash/Scaleform bridge: 95-100%\n"
            "netbattlemainmenu: 90-95%\n"
            "netbattlelobby UI: 95-100%\n"
            "Lobby player slots: 95%\n"
            "Host/voice/friend/ping/winstreak: 95-100%\n"
            "Lobby room data layout: 85-90%\n"
            "Steam persona/friend path: 90-95%\n"
            "Room search display: 80-85%\n"
            "Lobby create/join flow: 70-75%\n"
            "Match start flow: 40-50%\n"
            "Ranked matchmaking: 30-35%\n"
            "P2P/session backend: 25-30%\n"
            "Overall online menu/lobby layer: about 78-82%.";
    }

    const char* LatestNextSubs()
    {
        return
            "Next subs to research:\n"
            "sub_140675494 // setUser, player name/rank/icon/title\n"
            "sub_1406749F4 // setNum current/max player count\n"
            "sub_140674C58 // CallsetOnUser\n"
            "sub_140AEB470 // friend/relationship status lookup\n"
            "sub_140674200 // CallsetRoomInfoIconHost\n"
            "sub_140607BA0 // Flash invoke dispatcher\n"
            "sub_14060759C // Flash movie loader\n"
            "sub_140870220 // Flash object resolver\n"
            "sub_1409A6298 // Flash movie creation path\n"
            "sub_140607254 // Flash movie map insert/lookup\n"
            "sub_140AE7B00 // selected/current lobby user\n"
            "sub_140AE7B90 // lobby state/transition check\n"
            "sub_14060685C // selected opponent/player ID sync\n"
            "sub_1405B76BC // battle launch preparation\n"
            "sub_1406B33B4 // NetManager readiness/sync\n"
            "sub_1406B2850 // NetManager ready flag\n"
            "sub_1406B2834 // NetManager online state\n"
            "sub_1406B20F8 // NetManager task start/update";
    }
}
