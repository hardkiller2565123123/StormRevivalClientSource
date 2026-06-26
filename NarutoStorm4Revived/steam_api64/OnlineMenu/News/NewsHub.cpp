#include "NewsHub.h"
#include "../MainMenu/NetBattleMainMenu.h"

namespace StormRevival::OnlineMenu::News
{
    void Show(GamePtr ui)
    {
        MainMenu::VoiceIn(ui);
        MainMenu::SetVoiceText(ui, "Storm Revival News\\nOnline menu research active.\\nLobby UI mapping in progress.");
    }
}
