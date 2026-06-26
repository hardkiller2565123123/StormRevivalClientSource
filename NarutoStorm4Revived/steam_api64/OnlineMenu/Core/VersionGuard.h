#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu
{
    struct GameVersionInfo
    {
        bool Supported;
        std::uint32_t Crc32;
        const char* Name;
    };

    GameVersionInfo DetectGameVersion();
    bool IsSupportedGameVersion();
}
