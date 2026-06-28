#include "StdInc.h"
#include "DebugContentLoader.h"
#include "Logger.h"

namespace DebugContentLoader
{
    bool Init()
    {
        // Debug/TUI is now integrated into DlcContentLoader's existing MinHook file hooks.
        // This file intentionally does not install another CreateFile/GetFileAttributes hook chain.
        Logger::Info("[DebugContentLoader] skipped: handled by DlcContentLoader");
        return true;
    }

    void Shutdown()
    {
    }
}
