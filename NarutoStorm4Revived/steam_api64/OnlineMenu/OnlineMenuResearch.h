#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace OnlineMenuResearch
{
    struct FlashCallInfo
    {
        const char* owner;
        const char* swf;
        const char* root;
        const char* method;
        int argCount;
        const char* notes;
    };

    const std::vector<FlashCallInfo>& KnownFlashCalls();
    std::string BuildResearchReport();
}
