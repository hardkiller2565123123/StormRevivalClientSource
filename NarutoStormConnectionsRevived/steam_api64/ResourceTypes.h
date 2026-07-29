#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace ResourceTypes
{
    enum class RedirectKind : int
    {
        XfbinResource = 0,
        ScaleformMovie = 1
    };

    struct RedirectHit
    {
        RedirectKind Kind = RedirectKind::XfbinResource;
        std::string OriginalPath;
        std::string FinalPath;
        std::string ModName;
        bool Redirected = false;
    };

    struct LoadedResourceRow
    {
        RedirectKind Kind = RedirectKind::XfbinResource;
        std::string OriginalPath;
        std::string FinalPath;
        std::string ModName;
        bool Redirected = false;
        uint32_t RequestCount = 0;
    };

    struct ModFileEntry
    {
        std::string ModName;
        std::string AbsolutePath;
        std::string RelativePath;
        std::string FileName;
    };
}
