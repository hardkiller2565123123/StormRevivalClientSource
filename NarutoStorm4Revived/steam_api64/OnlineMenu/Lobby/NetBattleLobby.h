#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Lobby
{
    void Initialize(GamePtr ui);
    void SetUser(GamePtr ui, int slot, const char* name);
    void SetWave(GamePtr ui, int slot, int bars);
    void SetVoice(GamePtr ui, int slot, bool enabled);
    void SetFriend(GamePtr ui, int slot, int state);
    void SetHostNo(GamePtr ui, int slot);
    void SetWinStreak(GamePtr ui, int streak);
    void SetNum(GamePtr ui, int current, int max);
    void SetReadyState(GamePtr ui, int slot, bool ready);
}
