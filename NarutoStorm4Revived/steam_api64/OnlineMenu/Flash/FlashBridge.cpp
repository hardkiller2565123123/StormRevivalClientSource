#include "FlashBridge.h"
#include "../Core/SRLogger.h"
#include "../Hooks/OnlineMenuHookLogger.h"

#include <string>

namespace StormRevival::OnlineMenu::Flash
{
    void Install()
    {
        Log::Info("FlashBridge installed. Runtime invoke targets are still safe stubs until real hooks are wired.");
    }

    void TraceCall(const Target& target, const char* functionName, int argc)
    {
        Log::Info(
            std::string("FlashCall movie=") +
            (target.Movie ? target.Movie : "<null>") +
            " root=" +
            (target.Root ? target.Root : "<null>") +
            " function=" +
            (functionName ? functionName : "<null>") +
            " argc=" +
            std::to_string(argc));

        Hooks::LogFlashCall(target.Movie, target.Root, functionName, argc);
    }

    void CallNoArgs(GamePtr, const Target& target, const char* functionName)
    {
        TraceCall(target, functionName, 0);
    }

    void CallInt(GamePtr, const Target& target, const char* functionName, int)
    {
        TraceCall(target, functionName, 1);
    }

    void CallText(GamePtr, const Target& target, const char* functionName, const char*)
    {
        TraceCall(target, functionName, 1);
    }
}
