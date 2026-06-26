#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::MainMenu
{
    void Initialize(GamePtr ui);
    void Start(GamePtr ui);
    void Lock(GamePtr ui);
    void Unlock(GamePtr ui);
    void Restart(GamePtr ui);
    void Message(GamePtr ui, const char* text);
    void SetEventLock(GamePtr ui, bool locked);
    void SetBingoItem(GamePtr ui, bool enabled);
    void VoiceIn(GamePtr ui);
    void VoiceOut(GamePtr ui);
    void SetVoiceText(GamePtr ui, const char* text);
    void RenameStoreButtonToSettings(GamePtr ui);
}
