#include "StdInc.h"
#include "HookManager.h"
#include "Logger.h"

namespace HookManager
{
    bool Init()
    {
        auto result = MH_Initialize();

        if (result != MH_OK)
        {
            Logger::Error("MH_Initialize failed");
            return false;
        }

        Logger::Info("MinHook initialized");
        return true;
    }

    void Shutdown()
    {
        MH_STATUS disableStatus = MH_DisableHook(MH_ALL_HOOKS);
        if (disableStatus != MH_OK && disableStatus != MH_ERROR_NOT_INITIALIZED)
            Logger::Error("MH_DisableHook(MH_ALL_HOOKS) failed during shutdown");

        MH_STATUS uninitStatus = MH_Uninitialize();
        if (uninitStatus != MH_OK && uninitStatus != MH_ERROR_NOT_INITIALIZED)
            Logger::Error("MH_Uninitialize failed during shutdown");

        Logger::Info("MinHook shutdown");
    }

    bool Create(void* target, void* detour, void** original)
    {
        auto result = MH_CreateHook(
            target,
            detour,
            original
        );

        if (result != MH_OK)
        {
            Logger::Error("MH_CreateHook failed");
            return false;
        }

        return true;
    }

    bool Enable(void* target)
    {
        auto result = MH_EnableHook(target);

        if (result != MH_OK)
        {
            Logger::Error("MH_EnableHook failed");
            return false;
        }

        return true;
    }

    bool Disable(void* target)
    {
        auto result = MH_DisableHook(target);

        if (result != MH_OK)
        {
            Logger::Error("MH_DisableHook failed");
            return false;
        }

        return true;
    }
}