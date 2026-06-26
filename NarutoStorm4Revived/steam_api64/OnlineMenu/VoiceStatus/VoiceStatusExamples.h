#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::VoiceStatus
{
    void Show(std::uintptr_t netBattleMainMenuUi);
    void Hide(std::uintptr_t netBattleMainMenuUi);
    void SetText(std::uintptr_t netBattleMainMenuUi, const char* text);

    void ExampleServerStatus(std::uintptr_t netBattleMainMenuUi);
}
