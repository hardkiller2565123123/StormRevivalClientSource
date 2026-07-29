#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace ResourceTypes
{
    enum class RedirectKind : int
    {
        XfbinResource,
        ScaleformMovie
    };

    struct RedirectHit
    {
        RedirectKind kind{};
        std::string originalPath;
        std::string moddedPath;
        std::string modName;
        bool redirected = false;
    };

    struct LoadedResourceRow
    {
        RedirectKind kind{};
        std::string originalPath;
        std::string finalPath;
        std::string modName;
        bool redirected = false;
        uint32_t requestCount = 0;
    };
}
