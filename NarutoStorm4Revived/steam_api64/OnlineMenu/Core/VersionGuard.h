#pragma once
#include <cstdint>
#include <string>

namespace StormRevival::OnlineMenu
{
    enum class GameExeProfile
    {
        Unknown,
        VanillaSteam,
        EvolutionCustom,
        FixedAddressOverride
    };

    struct GameVersionInfo
    {
        bool Supported;
        bool FixedAddressHooksAllowed;
        bool PatternScanRequired;
        std::uint32_t Crc32;
        std::uint64_t ImageSize;
        GameExeProfile Profile;
        std::string Name;
        std::string ExePath;
        std::string Reason;
    };

    GameVersionInfo DetectGameVersion();
    bool IsSupportedGameVersion();
    bool AreFixedAddressHooksAllowed();
    bool ShouldSkipMenuMutation();
    void LogGameVersionInfo();
}
