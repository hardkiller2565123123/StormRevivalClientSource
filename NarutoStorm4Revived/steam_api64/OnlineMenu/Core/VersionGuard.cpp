#include "VersionGuard.h"
#include "SRLogger.h"
#include <Windows.h>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cctype>

namespace StormRevival::OnlineMenu
{
    namespace
    {
        bool g_cached = false;
        GameVersionInfo g_info;

        std::string Narrow(const wchar_t* w)
        {
            if (!w)
                return std::string();
            int len = WideCharToMultiByte(CP_UTF8, 0, w, -1, nullptr, 0, nullptr, nullptr);
            if (len <= 0)
                return std::string();
            std::string out(static_cast<std::size_t>(len - 1), '\0');
            WideCharToMultiByte(CP_UTF8, 0, w, -1, &out[0], len, nullptr, nullptr);
            return out;
        }

        std::string Hex32(std::uint32_t value)
        {
            std::ostringstream ss;
            ss << "0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value;
            return ss.str();
        }

        std::uint32_t Crc32Update(std::uint32_t crc, const unsigned char* data, DWORD count)
        {
            crc = ~crc;
            for (DWORD i = 0; i < count; ++i)
            {
                crc ^= data[i];
                for (int bit = 0; bit < 8; ++bit)
                    crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
            }
            return ~crc;
        }

        bool GetExeInfo(std::string& path, std::uint32_t& crcOut, std::uint64_t& sizeOut)
        {
            wchar_t exePath[MAX_PATH]{};
            if (!GetModuleFileNameW(nullptr, exePath, MAX_PATH))
                return false;
            path = Narrow(exePath);

            HANDLE file = CreateFileW(exePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                      nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (file == INVALID_HANDLE_VALUE)
                return false;

            LARGE_INTEGER li{};
            if (GetFileSizeEx(file, &li))
                sizeOut = static_cast<std::uint64_t>(li.QuadPart);

            std::uint32_t crc = 0;
            unsigned char buffer[64 * 1024];
            DWORD read = 0;
            while (ReadFile(file, buffer, sizeof(buffer), &read, nullptr) && read > 0)
                crc = Crc32Update(crc, buffer, read);

            CloseHandle(file);
            crcOut = crc;
            return true;
        }

        bool ConfigAllowFixedAddresses()
        {
            char path[MAX_PATH]{};
            GetModuleFileNameA(nullptr, path, MAX_PATH);
            char* slash = strrchr(path, '\\');
            if (slash)
                *(slash + 1) = '\0';
            strcat_s(path, "NarutoStorm4Revived\\steam_config.ini");
            return GetPrivateProfileIntA("OnlineMenu", "online_menu_allow_fixed_addresses", 0, path) != 0;
        }

        bool LooksLikeEvolutionExe(const std::string& path)
        {
            std::string lower = path;
            for (std::size_t i = 0; i < lower.size(); ++i)
                lower[i] = static_cast<char>(tolower(static_cast<unsigned char>(lower[i])));
            return lower.find("evo") != std::string::npos || lower.find("evolution") != std::string::npos;
        }

        // Known CRC list intentionally starts strict. Add verified CRCs here only after a clean boot.
        GameExeProfile KnownProfileFromCrc(std::uint32_t crc)
        {
            switch (crc)
            {
            default:
                return GameExeProfile::Unknown;
            }
        }
    }

    GameVersionInfo DetectGameVersion()
    {
        if (g_cached)
            return g_info;

        g_cached = true;
        g_info = GameVersionInfo();
        g_info.Supported = false;
        g_info.FixedAddressHooksAllowed = false;
        g_info.PatternScanRequired = true;
        g_info.Crc32 = 0;
        g_info.ImageSize = 0;
        g_info.Profile = GameExeProfile::Unknown;
        g_info.Name = "Unknown Storm 4 EXE";
        g_info.Reason = "No verified CRC/profile. Fixed 0x140 addresses are disabled.";

        GetExeInfo(g_info.ExePath, g_info.Crc32, g_info.ImageSize);

        const bool forcedFixed = ConfigAllowFixedAddresses();
        if (forcedFixed)
        {
            g_info.Supported = true;
            g_info.FixedAddressHooksAllowed = true;
            g_info.PatternScanRequired = false;
            g_info.Profile = GameExeProfile::FixedAddressOverride;
            g_info.Name = "Manual fixed-address override";
            g_info.Reason = "steam_config.ini [OnlineMenu] online_menu_allow_fixed_addresses=1";
            return g_info;
        }

        const GameExeProfile known = KnownProfileFromCrc(g_info.Crc32);
        if (known != GameExeProfile::Unknown)
        {
            g_info.Supported = true;
            g_info.FixedAddressHooksAllowed = true;
            g_info.PatternScanRequired = false;
            g_info.Profile = known;
            g_info.Name = known == GameExeProfile::EvolutionCustom ? "Evolution custom EXE" : "Vanilla Steam EXE";
            g_info.Reason = "CRC matched verified fixed-address profile.";
            return g_info;
        }

        if (LooksLikeEvolutionExe(g_info.ExePath))
        {
            g_info.Name = "Unverified Evolution-like EXE";
            g_info.Reason = "EXE name looks like Evolution, but CRC is not whitelisted. Pattern scan only.";
        }

        return g_info;
    }

    bool IsSupportedGameVersion()
    {
        return DetectGameVersion().Supported;
    }

    bool AreFixedAddressHooksAllowed()
    {
        return DetectGameVersion().FixedAddressHooksAllowed;
    }

    bool ShouldSkipMenuMutation()
    {
        const GameVersionInfo info = DetectGameVersion();
        return !info.Supported && info.PatternScanRequired;
    }

    void LogGameVersionInfo()
    {
        const GameVersionInfo info = DetectGameVersion();
        Log::Info("[VersionGuard] EXE=" + info.ExePath);
        Log::Info("[VersionGuard] crc32=" + Hex32(info.Crc32) + " size=" + std::to_string(static_cast<unsigned long long>(info.ImageSize)));
        Log::Info(std::string("[VersionGuard] supported=") + (info.Supported ? "yes" : "no") +
                  " fixedAddresses=" + (info.FixedAddressHooksAllowed ? "yes" : "no") +
                  " patternScanRequired=" + (info.PatternScanRequired ? "yes" : "no") +
                  " profile=" + info.Name);
        Log::Warn("[VersionGuard] " + info.Reason);
    }
}
