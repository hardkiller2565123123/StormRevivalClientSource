#include "StdInc.h"

#include "HookText.h"
#include "PopupManager.h"

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
#include "RuntimeUiOptions.h"
#include "InputFocusGuard.h"
#include "PopupTypes.h"
#include "ClassicSelectTheme.h"
#include "Overlay/RuntimeEditorOverlay.h"
#include "AudioCueRedirector.h"

#include <string>

static HANDLE g_MainThread = nullptr;

static void LogStartupPhase(const char* phase)
{
    Logger::Info(std::string("[STARTUP] ") + phase);
}

static DWORD WINAPI MainThread(LPVOID)
{
    if (!Logger::Init())
        return 0;

    Logger::Info("NarutoStormConnectionsRevived offline Steam layer loaded");

    HMODULE exe = GetModuleHandleA(nullptr);
    uintptr_t gameBase = reinterpret_cast<uintptr_t>(exe);

    LogStartupPhase("Diagnostics");
    SteamDiagnostics::Init();
    SteamDiagnostics::MarkSteam("Startup", "offline Steam layer loaded");

    if (!HookManager::Init())
    {
        Logger::Error("Hook manager failed to initialize");
        return 0;
    }

    LogStartupPhase("Early offline Steam bootstrap");

    // Bring the whole offline Steam stack online immediately, before save/profile/stat/menu code
    // starts making decisions. Do not remove UI features; this is only an early bootstrap.
    FakeSteamCore::Init();
    SteamConfig::Init();
    SteamIDManager::Init();
    SteamSessionManager::Init();
    SteamLobbyManager::Init();
    SteamP2PManager::Init();
    SteamAuth::Init();
    SteamCallbackManager::Init();
    SteamCallResultManager::Init();
    SteamPersonaManager::Init();
    SteamStorageLocal::Init();
    SteamStatsLocal::Init();

    LogStartupPhase("Early online/menu bootstrap");

    // Install online/menu bypass hooks as early as possible and immediately force launch state.
    OnlineCheckBypass::Init();

    LogStartupPhase("Custom audio redirector");
    if (!AudioCueRedirector::Init())
        Logger::Error("AudioCueRedirector failed to initialize");

    LogStartupPhase("Runtime UI options and F2 workspace");
    RuntimeUiOptions::Init();

    if (!RuntimeEditorOverlay::Init())
        Logger::Error("RuntimeEditorOverlay failed to initialize");

    LogStartupPhase("Runtime text, popup, and reverse-map tools");

    if (!HookText::Install())
        Logger::Error("HookText failed to install");

    if (!PopupManager::Init(gameBase))
    {
        Logger::Error("PopupManager failed to initialize");
    }
    else
    {
        PopupTypes::TimedPopupConfig startupPopup;
        startupPopup.delayMs = 5000;
        startupPopup.durationMs = 10000;
        startupPopup.allowInputClose = false;
        startupPopup.useFade = true;
        startupPopup.fadeDurationMs = 300;

        if (PopupManager::ShowTimedWelcome(startupPopup))
            Logger::Info("PopupManager initialized. Startup popup scheduled after 5 seconds.");
        else
            Logger::Error("PopupManager initialized but failed to schedule startup popup");
    }

    if (!ClassicSelectTheme::Init(gameBase))
        Logger::Error("ClassicSelectTheme failed to initialize");

    if (!SteamProxy::Init())
    {
        Logger::Error("Steam proxy failed to initialize");
        return 0;
    }

    RuntimeEditorOverlay::Update();

    LogStartupPhase("Network hooks and overlay");

    SteamFactoryRegistry::Dump();

    if (!NetworkHooks::Init())
        Logger::Error("Network hooks failed to initialize");

    if (!InputFocusGuard::Init())
        Logger::Error("Input focus guard failed to initialize");

    if (!DX11Overlay::Init())
        Logger::Error("DX11 overlay failed to initialize");



    WindowedFullscreen::Init();
    ModLoader::LoadMods();

    Logger::Info("NarutoStormConnectionsRevived initialized");
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
        if (g_MainThread)
        {
            CloseHandle(g_MainThread);
            g_MainThread = nullptr;
        }

        break;
    }

    case DLL_PROCESS_DETACH:
    {
        RuntimeEditorOverlay::Shutdown();
        DX11Overlay::Shutdown();
        InputFocusGuard::Shutdown();
        NetworkHooks::Shutdown();
        OnlineCheckBypass::Shutdown();
        AudioCueRedirector::Shutdown();

        ClassicSelectTheme::Shutdown();
        RuntimeUiOptions::Shutdown();
        PopupManager::Shutdown();
        HookText::Shutdown();

        FakeSteamCore::Shutdown();
        HookManager::Shutdown();
        SteamDiagnostics::Shutdown();
        Logger::Shutdown();

        break;
    }
    }

    return TRUE;
}
