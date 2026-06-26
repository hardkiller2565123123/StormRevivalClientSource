#include "OnlineMenuHookStubs.h"
#include "OnlineMenuHookLogger.h"
#include "../Core/SRLogger.h"

#include <string>

namespace StormRevival::OnlineMenu::Hooks
{
    void InstallOnlineMenuHookStubs()
    {
        Log::Info("[Hook] Installing OnlineMenu hook stubs.");
        LogHookSkipped("Hook_Flash_InvokeWithArgs_sub_140607BA0", "0x140607BA0", "Detour not attached yet; logging scaffold ready.");
        LogHookSkipped("Hook_Flash_InvokeNoArgs_sub_140607B5C", "0x140607B5C", "Detour not attached yet; logging scaffold ready.");
        LogHookSkipped("Hook_Flash_InvokeReturn_sub_140607B7C", "0x140607B7C", "Detour not attached yet; logging scaffold ready.");
        LogHookSkipped("Hook_Flash_RegisterCallbacks_sub_1401FD0AC", "0x1401FD0AC", "Detour not attached yet; logging scaffold ready.");
        LogHookSkipped("Hook_MainMenu_GetMode_sub_1406760F4", "0x1406760F4", "Detour not attached yet; logging scaffold ready.");
        LogHookSkipped("Hook_MainMenu_GetModeBattle_sub_140676164", "0x140676164", "Detour not attached yet; logging scaffold ready.");
        Log::Info("[Hook] Hook stubs installed successfully.");
    }

    void ShutdownOnlineMenuHookStubs()
    {
        Log::Info("[Hook] OnlineMenu hook stubs shutdown.");
    }

    void OnFlashInvokeWithArgs(GamePtr, const char* movie, const char* root, const char* functionName, int argc)
    {
        LogHookHit("Hook_Flash_InvokeWithArgs_sub_140607BA0");
        LogFlashCall(movie, root, functionName, argc);
    }

    void OnFlashInvokeNoArgs(GamePtr, const char* movie, const char* root, const char* functionName)
    {
        LogHookHit("Hook_Flash_InvokeNoArgs_sub_140607B5C");
        LogFlashCall(movie, root, functionName, 0);
    }

    void OnFlashGetter(GamePtr, const char* movie, const char* root, const char* functionName, int result)
    {
        LogHookHit("Hook_Flash_InvokeReturn_sub_140607B7C");
        LogFlashCall(movie, root, functionName, 0);
        LogFlashGetterResult(functionName, result);
    }

    void OnMainMenuModeRead(int mode)
    {
        LogHookHitValue("Hook_MainMenu_GetMode_sub_1406760F4", mode);
    }

    void OnBattleModeRead(int mode)
    {
        LogHookHitValue("Hook_MainMenu_GetModeBattle_sub_140676164", mode);
    }
}
