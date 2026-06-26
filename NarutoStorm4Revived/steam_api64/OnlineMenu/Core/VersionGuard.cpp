#include "VersionGuard.h"

namespace StormRevival::OnlineMenu
{
    GameVersionInfo DetectGameVersion()
    {
        GameVersionInfo info;
        info.Supported = true;
        info.Crc32 = 0;
        info.Name = "Naruto Storm 4 Offline Research Build";
        return info;
    }

    bool IsSupportedGameVersion()
    {
        return DetectGameVersion().Supported;
    }
}
