#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Hooks
{
    void InstallOnlineMenuHookStubs();
    void ShutdownOnlineMenuHookStubs();

    // These are call-in helpers for future real detours.
    void OnFlashInvokeWithArgs(GamePtr ui, const char* movie, const char* root, const char* functionName, int argc);
    void OnFlashInvokeNoArgs(GamePtr ui, const char* movie, const char* root, const char* functionName);
    void OnFlashGetter(GamePtr ui, const char* movie, const char* root, const char* functionName, int result);
    void OnMainMenuModeRead(int mode);
    void OnBattleModeRead(int mode);
}
