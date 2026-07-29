#include "StdInc.h"
#include "HookText.h"
#include "Logger.h"
#include "HookManager.h"
#include "Runtime/ResourceRedirector.h"
#include "Overlay/RuntimeEditorOverlay.h"

// Drop these calls into your existing MainThread after HookManager::Init().
// This keeps F1 clean and moves runtime tools to the standalone F2 editor.
static void InstallStormApiRuntimeSystems(uintptr_t gameBase)
{
    // ResourceRedirector scans every folder under:
    // NarutoStormConnectionsRevived/mods/<ModName>/...
    // If a matching data/... path exists there, the game request is redirected.
    if (!ResourceRedirector::Init(gameBase))
        Logger::Error("ResourceRedirector failed to initialize");

    if (!RuntimeEditorOverlay::Init())
        Logger::Error("RuntimeEditorOverlay failed to initialize");
}

static void ShutdownStormApiRuntimeSystems()
{
    RuntimeEditorOverlay::Shutdown();
    ResourceRedirector::Shutdown();
}

// In your DX11 overlay render loop, call this without requiring F1 to be open:
// RuntimeEditorOverlay::Update();
