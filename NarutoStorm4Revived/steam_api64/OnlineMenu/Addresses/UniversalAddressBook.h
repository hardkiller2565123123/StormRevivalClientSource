#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Addresses
{
    /*
        UniversalAddressBook

        These are research RVAs/absolute-style labels from the current Storm 4 PC
        reverse engineering pass. Keep them centralized so hooks and docs do not
        scatter magic numbers across the project.

        Notes:
        - These addresses are version-sensitive.
        - Do not hard patch without version checks.
        - Use for local/offline research only.
    */
    struct AddressEntry
    {
        const char* Name;
        std::uintptr_t Address;
        const char* Meaning;
    };

    constexpr AddressEntry OnlineMenuAddressBook[] =
    {
        { "sub_14060759C", 0x14060759C, "RegisterFlashMovie / SWF-GFX movie registration" },
        { "sub_140607BA0", 0x140607BA0, "InvokeFlashWithArgs / ActionScript call with args" },
        { "sub_140607B5C", 0x140607B5C, "InvokeFlashNoArgs / ActionScript call no args" },
        { "sub_140607B7C", 0x140607B7C, "InvokeFlashReturnValue wrapper" },
        { "sub_1406078CC", 0x1406078CC, "UnregisterFlashMovie / movie unload" },
        { "sub_140607A04", 0x140607A04, "Install ccUiFlash::Update callback" },
        { "sub_1401FD0AC", 0x1401FD0AC, "RegisterFlashCallbacks / ActionScript callback table binder" },

        { "sub_140676250", 0x140676250, "ccUiFlashNetBattleMainMenu Initialize" },
        { "sub_140676054", 0x140676054, "ccUiFlashNetBattleMainMenu finalize" },
        { "sub_1406760F4", 0x1406760F4, "netbattlemainmenu.GetMode" },
        { "sub_140676164", 0x140676164, "netbattlemainmenu.GetModeBattele" },
        { "sub_1406761D4", 0x1406761D4, "Main menu selection/state flag read" },
        { "sub_1406761D8", 0x1406761D8, "Main menu transition flag read and clear" },
        { "sub_1406761E0", 0x1406761E0, "netbattlemainmenu.GetSelectLimitEventId" },
        { "sub_140676904", 0x140676904, "netbattlemainmenu.SetBingoItem" },
        { "sub_14067699C", 0x14067699C, "netbattlemainmenu.SetEventLock" },
        { "sub_140676A34", 0x140676A34, "netbattlemainmenu.Restart" },
        { "sub_140676A9C", 0x140676A9C, "netbattlemainmenu.SetUnLock" },

        { "sub_1405C17B4", 0x1405C17B4, "Online selected mode dispatch" },
        { "sub_1405C1910", 0x1405C1910, "Online selected mode network cleanup/start branch" },
        { "sub_1405C2FFC", 0x1405C2FFC, "Battle mode/submode mapper" },
        { "sub_1405C3064", 0x1405C3064, "Main mode to scene/state mapper" },
        { "sub_1405C33FC", 0x1405C33FC, "Mode check helper" },
        { "sub_1405C343C", 0x1405C343C, "Battle mode check helper" },

        { "sub_140671C94", 0x140671C94, "Event/banner object constructor" },
        { "sub_140671D28", 0x140671D28, "Banner Initialize" },
        { "sub_1406722A0", 0x1406722A0, "Banner/title mode setup" },
        { "sub_140672320", 0x140672320, "setTitleBanner" },
        { "sub_140672384", 0x140672384, "SetTextTitle" },

        { "sub_1406A5E7C", 0x1406A5E7C, "Online card/profile UI object constructor" },
        { "sub_1406A5F18", 0x1406A5F18, "Card/Profile Initialize" },
        { "sub_1406A6060", 0x1406A6060, "Set owner scene" },
        { "sub_1406A6068", 0x1406A6068, "SetAlwaysOpen" },
        { "sub_1406A60D4", 0x1406A60D4, "setCardInfo / RequestSetCardInfo player card builder" },

        { "sub_1406B3DCC", 0x1406B3DCC, "Lobby member persona lookup" },
        { "sub_140AE6010", 0x140AE6010, "Steam persona name from CSteamID" },
        { "sub_140AE6670", 0x140AE6670, "Lobby/session valid check" },
        { "sub_140AE6720", 0x140AE6720, "Lobby member ID getter" },
    };

    constexpr int OnlineMenuAddressBookCount =
        static_cast<int>(sizeof(OnlineMenuAddressBook) / sizeof(OnlineMenuAddressBook[0]));
}
