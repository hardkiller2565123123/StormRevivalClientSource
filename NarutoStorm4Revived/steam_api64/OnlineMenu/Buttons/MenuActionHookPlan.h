#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Buttons
{
    enum class MenuMode : int
    {
        Mode0 = 0,
        Mode1 = 1,
        Mode3 = 3,
        Mode4 = 4,
        Mode7Ignored = 7,
        Mode8 = 8,
        Mode9 = 9,
        Mode10 = 10,
        Mode11 = 11
    };

    struct MenuActionEvent
    {
        std::uintptr_t callbackObject = 0;
        std::uintptr_t eventObject = 0;
        int mode = -1;
    };

    bool ShouldHijackMode(int mode);
    void OnHijackedMode(const MenuActionEvent& event);
}
