#include "RuntimeSafetyGate.h"
#include <windows.h>
#include <string>
#include <vector>

// Replace these includes with your project's real config/logger headers.
#include "Logger.h"
#include "SteamConfig.h"

namespace StormRevival
{
    static RuntimeExeProfile g_Profile{};
    static bool g_Initialized = false;
    static bool g_Logged = false;

    // Known-good profiles. Add Evolution/custom EXE CRC here after confirming.
    struct KnownProfile
    {
        std::uint32_t crc32;
        std::uint64_t size;
        const char* name;
        bool fixedAddressesAllowed;
    };

    static const KnownProfile kKnownProfiles[] =
    {
        // Sentinel keeps MSVC from seeing a zero-sized array while the table is empty.
        { 0u, 0ull, nullptr, false },
        // Example only. Keep fixed addresses disabled until verified.
        // { 0x12345678u, 24686592ull, "NS4 Evolution verified", true },
    };

    static std::uint32_t Crc32File(const std::wstring& path)
    {
        HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (h == INVALID_HANDLE_VALUE)
            return 0;

        std::uint32_t crc = 0xFFFFFFFFu;
        BYTE buf[64 * 1024];
        DWORD read = 0;

        while (ReadFile(h, buf, sizeof(buf), &read, nullptr) && read)
        {
            for (DWORD i = 0; i < read; ++i)
            {
                crc ^= buf[i];
                for (int b = 0; b < 8; ++b)
                    crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
            }
        }

        CloseHandle(h);
        return ~crc;
    }

    static std::wstring CurrentExePath()
    {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        return path;
    }

    static std::uint64_t FileSize64(const std::wstring& path)
    {
        WIN32_FILE_ATTRIBUTE_DATA data{};
        if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data))
            return 0;
        ULARGE_INTEGER size{};
        size.HighPart = data.nFileSizeHigh;
        size.LowPart = data.nFileSizeLow;
        return size.QuadPart;
    }

    RuntimeExeProfile RuntimeSafetyGate::DetectCurrentExe()
    {
        RuntimeExeProfile p{};
        p.safeModeUnknownExe = SteamConfig::GetBool("safe_mode_unknown_exe", true);

        const std::wstring exe = CurrentExePath();
        p.crc32 = Crc32File(exe);
        p.size = FileSize64(exe);
        p.name = "Unknown Storm 4 EXE";
        p.reason = "CRC/size not in verified profile table";

        for (const auto& known : kKnownProfiles)
        {
            if (!known.name)
                continue;

            if (known.crc32 == p.crc32 && known.size == p.size)
            {
                p.supported = true;
                p.fixedAddressesAllowed = known.fixedAddressesAllowed;
                p.name = known.name;
                p.reason = "verified executable profile";
                return p;
            }
        }

        p.supported = false;
        p.fixedAddressesAllowed = false;
        return p;
    }

    void RuntimeSafetyGate::Initialize()
    {
        if (g_Initialized)
            return;

        g_Profile = DetectCurrentExe();

        // Explicit hard override stays dangerous and should never be default.
        if (!g_Profile.supported && SteamConfig::GetBool("allow_fixed_addresses_unknown_exe", false))
        {
            g_Profile.fixedAddressesAllowed = true;
            g_Profile.reason = "manual override: allow_fixed_addresses_unknown_exe=1";
        }

        g_Initialized = true;
        LogSummaryOnce();
    }

    const RuntimeExeProfile& RuntimeSafetyGate::Profile()
    {
        if (!g_Initialized)
            Initialize();
        return g_Profile;
    }

    bool RuntimeSafetyGate::IsSupportedExe()
    {
        return Profile().supported;
    }

    bool RuntimeSafetyGate::IsUnknownExeSafeMode()
    {
        const auto& p = Profile();
        return !p.supported && p.safeModeUnknownExe;
    }

    bool RuntimeSafetyGate::Allow(RuntimePatchKind kind)
    {
        const auto& p = Profile();

        if (p.supported)
            return true;

        if (!p.safeModeUnknownExe)
            return false;

        switch (kind)
        {
        case RuntimePatchKind::FixedAddressHook:
        case RuntimePatchKind::OnlineMenuMutation:
        case RuntimePatchKind::StoreReplacement:
        case RuntimePatchKind::SyntheticMenuMode:
        case RuntimePatchKind::SlotExpansion:
        case RuntimePatchKind::CharacterRosterPatch:
        case RuntimePatchKind::StageSceneExpansion:
        case RuntimePatchKind::ResourceMemoryPatch:
            return false;
        default:
            return false;
        }
    }

    void RuntimeSafetyGate::LogSummaryOnce()
    {
        if (g_Logged)
            return;
        g_Logged = true;

        const auto& p = Profile();
        char msg[512]{};
        sprintf_s(msg,
            "RuntimeSafetyGate: exe=%s crc32=0x%08X size=%llu supported=%s fixedHooks=%s safeMode=%s",
            p.name.c_str(),
            p.crc32,
            static_cast<unsigned long long>(p.size),
            p.supported ? "yes" : "no",
            p.fixedAddressesAllowed ? "yes" : "no",
            p.safeModeUnknownExe ? "yes" : "no");

        Logger::Info(msg);

        if (!p.supported)
            Logger::Warn("RuntimeSafetyGate: unsupported EXE, unsafe memory patchers are disabled.");
    }
}
