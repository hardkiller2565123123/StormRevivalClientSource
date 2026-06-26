#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Hooks
{
    enum class KnownMenuMode
    {
        Unknown = -1,
        Mode0 = 0,
        Mode1 = 1,
        Mode3 = 3,
        Mode4 = 4,
        Mode7Ignored = 7,
        Mode8 = 8,
        Mode9 = 9,
        Mode10 = 10,
        Mode11 = 11,

        StormRevivalSettings = 100,
        StormRevivalStatus = 101,
        StormRevivalUnlocks = 102,
        StoreAsSettings = 13
    };

    void InstallMenuActionHook();
    bool ShouldHijackMode(int mode);
    void HandleHijackedMode(GamePtr menuUi, int mode);
}
