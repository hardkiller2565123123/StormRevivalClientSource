#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Dialogs
{
    // Wrapper notes:
    // sub_140659358 = CreateMsgWindow
    // sub_140659780 = SetMessageText
    // sub_1406595F4 = OpenWindow
    // sub_1406594DC = IsClosed
    void ShowResearchDialog(std::uintptr_t dialogUi);
}
