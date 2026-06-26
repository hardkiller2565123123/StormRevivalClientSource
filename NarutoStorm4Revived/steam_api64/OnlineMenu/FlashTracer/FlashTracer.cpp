#include "FlashTracer.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::FlashTracer
{
    void Install()
    {
        Log::Info("FlashTracer ready. Recommended hooks: sub_140607BA0, sub_140607B5C, sub_14060759C.");
    }

    void LogCall(const FlashCall& call)
    {
        Log::Info(
            "FlashCall movie=" + call.movie +
            " root=" + call.root +
            " fn=" + call.functionName +
            " argc=" + std::to_string(call.argCount));
    }
}
