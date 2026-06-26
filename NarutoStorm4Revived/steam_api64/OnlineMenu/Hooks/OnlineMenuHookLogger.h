#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Hooks
{
    enum class HookInstallStatus
    {
        Pending,
        Installed,
        Failed,
        Skipped
    };

    struct HookDefinition
    {
        const char* Name;
        const char* Address;
        const char* Purpose;
        HookInstallStatus Status;
    };

    void InstallOnlineMenuHookLogging();
    void ShutdownOnlineMenuHookLogging();

    void LogHookPlanned(const char* hookName, const char* address, const char* purpose);
    void LogHookInstalled(const char* hookName, const char* address);
    void LogHookFailed(const char* hookName, const char* address, const char* reason);
    void LogHookSkipped(const char* hookName, const char* address, const char* reason);

    void LogHookHit(const char* hookName);
    void LogHookHitValue(const char* hookName, int value);
    void LogFlashCall(const char* movie, const char* root, const char* functionName, int argc);
    void LogFlashGetterResult(const char* functionName, int result);

    const HookDefinition* GetOnlineMenuHooks();
    int GetOnlineMenuHookCount();
}
