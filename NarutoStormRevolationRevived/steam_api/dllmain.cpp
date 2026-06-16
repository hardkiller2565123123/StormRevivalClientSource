#include "StdInc.h"

#include "Logger.h"
#include "SteamProxy.h"
#include "HookManager.h"
#include "NetworkHooks.h"
#include "DX11Overlay.h"
#include "WindowedFullscreen.h"
#include "ModLoader.h"

#include "SteamConfig.h"
#include "SteamIDManager.h"
#include "SteamSessionManager.h"
#include "SteamLobbyManager.h"
#include "SteamP2PManager.h"
#include "SteamAuth.h"
#include "SteamCallbackManager.h"
#include "SteamCallResultManager.h"
#include "SteamDiagnostics.h"
#include "SteamFactoryRegistry.h"
#include "SteamPersonaManager.h"
#include "SteamStorageLocal.h"
#include "SteamStatsLocal.h"
#include "FakeSteamCore.h"
#include "OnlineCheckBypass.h"
#include "InputFocusGuard.h"

static HANDLE g_MainThread = nullptr;

static DWORD WINAPI MainThread(LPVOID)
{
    if (!Logger::Init())
        return 0;

    Logger::Info("NarutoStormRevolationRevived offline Steam layer loaded");
    SteamDiagnostics::Init();
    SteamDiagnostics::MarkSteam("Startup", "offline Steam layer loaded");

    if (!SteamProxy::Init())
    {
        Logger::Error("Steam proxy failed to initialize");
        return 0;
    }

    if (!HookManager::Init())
    {
        Logger::Error("Hook manager failed to initialize");
        return 0;
    }

    SteamConfig::Init();
    SteamIDManager::Init();
    SteamSessionManager::Init();
    SteamLobbyManager::Init();
    SteamP2PManager::Init();
    SteamAuth::Init();
    SteamCallbackManager::Init();
    SteamCallResultManager::Init();
    FakeSteamCore::Init();
    SteamPersonaManager::Init();
    SteamStorageLocal::Init();
    SteamStatsLocal::Init();
    OnlineCheckBypass::Init();

    SteamFactoryRegistry::Dump();

    if (!NetworkHooks::Init())
        Logger::Error("Network hooks failed to initialize");

    if (!InputFocusGuard::Init())
        Logger::Error("Input focus guard failed to initialize");

    if (!DX11Overlay::Init())
        Logger::Error("DX11 overlay failed to initialize");

    WindowedFullscreen::Init();
    ModLoader::LoadMods();

    Logger::Info("NarutoStormRevolationRevived initialized");
    return 0;



}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(module);
        g_MainThread = CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
        break;
    }
    case DLL_PROCESS_DETACH:
    {
        NetworkHooks::Shutdown();
        InputFocusGuard::Shutdown();
        OnlineCheckBypass::Shutdown();
        FakeSteamCore::Shutdown();
        DX11Overlay::Shutdown();
        HookManager::Shutdown();
        SteamDiagnostics::Shutdown();
        Logger::Shutdown();
        break;
    }
    }
    return TRUE;
}

