#pragma once

// Storm Evo Online Menu research scaffold.
// This folder is intentionally DISABLED. Nothing here is called yet.
// Purpose: keep our IDA findings organized until we have safe hook targets.

namespace OnlineMenuNotes
{
    // Confirmed IDA targets:
    // ccSceneNetworkMenu_New.cpp initializer: sub_1405C0890
    // netbattlemainmenu initializer: sub_140676250
    // Flash invoke bridge: sub_140607BA0 / sub_140607B5C
    // Player card bridge: sub_1406A5F38 -> data/ui/flash/FLASH_PLAT/net_card/net_card.swf
    // Event banner bridge: sub_140671D48 -> netbattleeventbanner

    constexpr unsigned long long SceneNetworkMenuNew_Init = 0x1405C0890ull;
    constexpr unsigned long long NetBattleMainMenu_Init = 0x140676250ull;
    constexpr unsigned long long NetBattleMainMenu_Start = 0x140676A68ull;
    constexpr unsigned long long NetBattleMainMenu_SetLock = 0x140676A18ull;
    constexpr unsigned long long PlayerCard_SetInfo = 0x1406A60D4ull;
    constexpr unsigned long long PlayerCard_Invoke = 0x1406A5F38ull;
    constexpr unsigned long long Banner_Invoke = 0x140671D48ull;
    constexpr unsigned long long Banner_SetTitle = 0x140672320ull;
    constexpr unsigned long long Banner_SetTextTitle = 0x140672384ull;

    constexpr const char* MainSwfName = "netbattlemainmenu";
    constexpr const char* MainSwfRoot = "_root.all_nut";
    constexpr const char* CardSwfPath = "data/ui/flash/FLASH_PLAT/net_card/net_card.swf";
    constexpr const char* CardSwfRoot = "_root.all_nut.all_card";
    constexpr const char* BannerSwfName = "netbattleeventbanner";
    constexpr const char* BannerSwfRoot = "_root.all_nut.all_banner";
}
