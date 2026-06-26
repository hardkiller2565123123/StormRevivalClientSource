#include "ResearchNotes.h"

namespace StormRevival::OnlineMenu::Research
{
    const char* CurrentCapabilitySummary()
    {
        return
            "Current online menu capability map:\n"
            "- Flash movie loading and ActionScript invocation mapped.\n"
            "- netbattlemainmenu setup/state/action flow mostly mapped.\n"
            "- netbattlelobby init, full refresh, player slots, host, voice, friend, ping bars, win streak, and count mapped.\n"
            "- Steam persona name, friend check, lobby SteamID enumeration, ping-to-bars, and lobby type->UI mode mapped.\n"
            "- Store overlay path identified for replacement/hijack.\n";
    }

    const char* NextStubList()
    {
        return
            "Next stubs:\n"
            "sub_140AE6670 callers\n"
            "sub_140AE6720 callers\n"
            "sub_140673408 callers\n"
            "sub_140AE7B60\n"
            "sub_140AE7AA0\n"
            "sub_140AE7A40\n"
            "sub_140AE8160\n"
            "sub_1405C014C\n"
            "sub_1405B5A74\n"
            "sub_1406B20F8\n"
            "sub_1406B2834\n"
            "sub_1406B2850\n"
            "sub_1406B2AD0\n"
            "sub_1406B2A78\n"
            "sub_1406B3B00\n";
    }
}
