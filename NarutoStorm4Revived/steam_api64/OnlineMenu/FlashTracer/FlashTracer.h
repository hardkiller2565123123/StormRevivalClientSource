#pragma once
#include <string>

namespace StormRevival::OnlineMenu::FlashTracer
{
    struct FlashCall
    {
        std::string movie;
        std::string root;
        std::string functionName;
        int argCount = 0;
    };

    void Install();
    void LogCall(const FlashCall& call);
}
