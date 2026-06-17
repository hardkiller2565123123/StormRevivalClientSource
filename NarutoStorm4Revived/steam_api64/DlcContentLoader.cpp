#include "StdInc.h"
#include "DlcContentLoader.h"
#include "HookManager.h"
#include "Logger.h"
#include "SteamConfig.h"

namespace
{
    using CreateFileA_t = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    using CreateFileW_t = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    using GetFileAttributesA_t = DWORD(WINAPI*)(LPCSTR);
    using GetFileAttributesW_t = DWORD(WINAPI*)(LPCWSTR);
    using FindFirstFileA_t = HANDLE(WINAPI*)(LPCSTR, LPWIN32_FIND_DATAA);
    using FindFirstFileW_t = HANDLE(WINAPI*)(LPCWSTR, LPWIN32_FIND_DATAW);

    CreateFileA_t oCreateFileA = nullptr;
    CreateFileW_t oCreateFileW = nullptr;
    GetFileAttributesA_t oGetFileAttributesA = nullptr;
    GetFileAttributesW_t oGetFileAttributesW = nullptr;
    FindFirstFileA_t oFindFirstFileA = nullptr;
    FindFirstFileW_t oFindFirstFileW = nullptr;

    thread_local bool g_InHook = false;

    std::string WideToUtf8(LPCWSTR value)
    {
        if (!value)
            return {};

        int len = WideCharToMultiByte(CP_UTF8, 0, value, -1, nullptr, 0, nullptr, nullptr);
        if (len <= 1)
            return {};

        std::string out(static_cast<size_t>(len - 1), '\0');
        WideCharToMultiByte(CP_UTF8, 0, value, -1, out.data(), len, nullptr, nullptr);
        return out;
    }

    std::wstring Utf8ToWide(const std::string& value)
    {
        if (value.empty())
            return {};

        int len = MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, nullptr, 0);
        if (len <= 1)
            return {};

        std::wstring out(static_cast<size_t>(len - 1), L'\0');
        MultiByteToWideChar(CP_UTF8, 0, value.c_str(), -1, out.data(), len);
        return out;
    }

    std::string Lower(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });
        return value;
    }

    bool EndsWith(const std::string& value, const std::string& suffix)
    {
        return value.size() >= suffix.size() &&
            value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    std::string NormalizeGamePath(std::string value)
    {
        value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
        std::replace(value.begin(), value.end(), '/', static_cast<char>(std::filesystem::path::preferred_separator));

        const size_t simPrefix = value.find("sim:");
        if (simPrefix != std::string::npos)
            value.erase(simPrefix, 4);

        while (!value.empty() && (value.front() == '\\' || value.front() == '/'))
            value.erase(value.begin());

        return value;
    }

    bool IsWildcardPath(const std::string& path)
    {
        return path.find('*') != std::string::npos || path.find('?') != std::string::npos;
    }

    bool IsBlockedSidecarFile(const std::string& path)
    {
        const std::string lower = Lower(path);
        return lower.find("checksum") != std::string::npos ||
            lower.find("launcher") != std::string::npos ||
            EndsWith(lower, ".exe") ||
            EndsWith(lower, ".bat") ||
            EndsWith(lower, ".cmd") ||
            EndsWith(lower, ".ps1");
    }

    bool IsReadableGameContent(const std::string& path)
    {
        const std::string lower = Lower(path);
        if (IsBlockedSidecarFile(lower))
            return false;

        static const char* exts[] =
        {
            ".cpk", ".xfbin", ".gfx", ".nsh", ".nut", ".bin", ".swf", ".xml", ".tex", ".dds", ".png", ".txt", ".ini"
        };

        for (const char* ext : exts)
        {
            if (EndsWith(lower, ext))
                return true;
        }

        return lower.find("data") != std::string::npos || lower.find("dlc") != std::string::npos;
    }

    bool ExistsPathA(const std::string& path)
    {
        if (!oGetFileAttributesA || path.empty())
            return false;

        DWORD attrs = oGetFileAttributesA(path.c_str());
        return attrs != INVALID_FILE_ATTRIBUTES;
    }

    bool ShouldHandleRequest(const std::string& raw)
    {
        if (raw.empty() || !SteamConfig::IsDlcUnlockEnabled())
            return false;

        const std::string lower = Lower(raw);
        if (IsReadableGameContent(raw))
            return true;

        static const char* requiredTokens[] =
        {
            "dlc",
            "add_contents",
            "common_add_contents",
            "content_info",
            "dlcpackdata",
            "load_contents",
            "plus_dlc",
            "st_script_dlc",
            "ep_r2b",
            "ep_gar",
            "ep_sik",
            "evolution",
            "charicon",
            "charsel",
            "duel_",
            "freebtl_",
            "gametitle",
            "gauge_",
            "net_",
            "preset",
            "stagesel",
            "vsload",
            "xcmn",
            "network",
            "networkmode_",
            "network_sys_",
            "netbattle",
            "netmatch",
            "net_event",
            "net_search",
            "net_match",
            "net_offline",
            "net_rank",
            "net_card",
            "net_cmn",
            "net_top",
            "networkevent",
            "neteventparam",
            "neteventcharaselectparam",
            "netrankparam",
            "netbattlematchingwindow",
            "netbattlesessionselect"
        };

        for (const char* token : requiredTokens)
        {
            if (lower.find(token) != std::string::npos)
                return true;
        }

        return false;
    }

    void AddUnique(std::vector<std::string>& out, const std::filesystem::path& path)
    {
        std::string value = path.string();
        if (value.empty())
            return;

        if (std::find(out.begin(), out.end(), value) == out.end())
            out.push_back(value);
    }

    std::vector<std::string> BuildCandidates(const std::string& raw)
    {
        std::vector<std::string> result;
        if (!ShouldHandleRequest(raw))
            return result;

        const std::filesystem::path gameFolder = SteamConfig::GetGameFolder();
        const std::filesystem::path dlcFolder = SteamConfig::GetDlcFolder();
        const std::string normalized = NormalizeGamePath(raw);
        const std::filesystem::path relative = normalized;
        const std::string lower = Lower(normalized);

        if (!relative.empty() && !relative.is_absolute())
        {
            // StormEvolution loose-file override layer. This lets a release folder contain
            // data/evolution/*.cpk, data/ui/*.gfx, data/system/*.xfbin, etc. and have the
            // game read those files without needing them copied into the game root.
            for (const std::string folder : SteamConfig::GetEvolutionFolders())
            {
                if (!folder.empty() && !IsBlockedSidecarFile(relative.string()))
                    AddUnique(result, std::filesystem::path(folder) / relative);
            }

            AddUnique(result, gameFolder / relative);
            AddUnique(result, dlcFolder / relative);
            AddUnique(result, gameFolder / "dlc" / relative);

            if (lower.rfind("dlc", 0) == 0)
            {
                std::filesystem::path withoutDlc;
                bool skipped = false;
                for (const auto& part : relative)
                {
                    if (!skipped)
                    {
                        skipped = true;
                        continue;
                    }
                    withoutDlc /= part;
                }

                if (!withoutDlc.empty())
                    AddUnique(result, dlcFolder / withoutDlc);
            }
        }

        for (const std::string& probe : SteamConfig::GetDlcContentProbePaths())
        {
            const std::string probeNorm = NormalizeGamePath(probe);
            const std::string probeLower = Lower(probeNorm);
            if (probeLower.empty())
                continue;

            if (lower.find(probeLower) != std::string::npos || probeLower.find(lower) != std::string::npos)
            {
                AddUnique(result, gameFolder / probeNorm);
                AddUnique(result, dlcFolder / probeNorm);
                AddUnique(result, gameFolder / "dlc" / probeNorm);
            }
        }

        if (lower.find("dlcpackdata.cpk") != std::string::npos)
        {
            AddUnique(result, gameFolder / "data" / "sim" / "dlcpackdata.cpk");
            AddUnique(result, dlcFolder / "data" / "sim" / "dlcpackdata.cpk");
            AddUnique(result, dlcFolder / "dlcpackdata.cpk");
            AddUnique(result, gameFolder / "dlc" / "data" / "sim" / "dlcpackdata.cpk");
            AddUnique(result, gameFolder / "dlc" / "dlcpackdata.cpk");
        }

        if (lower.find("content_info.xfbin") != std::string::npos)
        {
            AddUnique(result, gameFolder / "data" / "system" / "content_info.xfbin");
            AddUnique(result, dlcFolder / "data" / "system" / "content_info.xfbin");
            AddUnique(result, dlcFolder / "content_info.xfbin");
        }

        if (lower.find("common_add_contents.xfbin") != std::string::npos)
        {
            AddUnique(result, gameFolder / "data" / "network" / "PLAT" / "COMMON_ADD_CONTENTS.xfbin");
            AddUnique(result, dlcFolder / "data" / "network" / "PLAT" / "COMMON_ADD_CONTENTS.xfbin");
            AddUnique(result, dlcFolder / "COMMON_ADD_CONTENTS.xfbin");
        }


        // If the game requests only a file name or a platform-specific path, also search the
        // StormEvolution folders recursively by matching the same relative suffix/file name.
        if (IsReadableGameContent(normalized))
        {
            const std::string wantedName = Lower(std::filesystem::path(normalized).filename().string());
            for (const std::string folderText : SteamConfig::GetEvolutionFolders())
            {
                if (folderText.empty())
                    continue;

                std::error_code ec;
                const std::filesystem::path folder = folderText;
                if (!std::filesystem::exists(folder, ec) || !std::filesystem::is_directory(folder, ec))
                    continue;

                for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
                {
                    if (ec) { ec.clear(); continue; }
                    if (!it->is_regular_file(ec))
                        continue;

                    const std::string found = it->path().generic_string();
                    if (IsBlockedSidecarFile(found))
                        continue;

                    const std::string foundLower = Lower(found);
                    const std::string foundName = Lower(it->path().filename().string());
                    if ((!wantedName.empty() && foundName == wantedName) || EndsWith(foundLower, Lower(normalized)))
                        AddUnique(result, it->path());
                }
            }
        }

        return result;
    }

    std::string FindExistingCandidate(const std::string& raw)
    {
        for (const std::string& candidate : BuildCandidates(raw))
        {
            if (ExistsPathA(candidate))
                return candidate;
        }
        return {};
    }

    std::string FindStormEvolutionOverride(const std::string& raw)
    {
        if (!ShouldHandleRequest(raw))
            return {};

        const std::string normalized = NormalizeGamePath(raw);
        if (normalized.empty() || std::filesystem::path(normalized).is_absolute() || !IsReadableGameContent(normalized))
            return {};

        const std::filesystem::path relative = normalized;
        for (const std::string folder : SteamConfig::GetEvolutionFolders())
        {
            if (folder.empty())
                continue;

            const std::filesystem::path candidate = std::filesystem::path(folder) / relative;
            if (!IsBlockedSidecarFile(candidate.string()) && ExistsPathA(candidate.string()))
                return candidate.string();
        }

        return {};
    }

    HANDLE WINAPI hkCreateFileA(LPCSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES security, DWORD creationDisposition, DWORD flags, HANDLE templateFile)
    {
        if (g_InHook || !fileName || !oCreateFileA)
            return oCreateFileA(fileName, desiredAccess, shareMode, security, creationDisposition, flags, templateFile);

        g_InHook = true;

        const std::string overridePath = FindStormEvolutionOverride(fileName);
        if (!overridePath.empty())
        {
            HANDLE overrideHandle = oCreateFileA(overridePath.c_str(), desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
            if (overrideHandle != INVALID_HANDLE_VALUE)
            {
                Logger::Info(std::string("StormEvolution override CreateFileA: ") + fileName + " -> " + overridePath);
                g_InHook = false;
                return overrideHandle;
            }
        }

        HANDLE handle = oCreateFileA(fileName, desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
        DWORD originalError = GetLastError();

        if (handle == INVALID_HANDLE_VALUE && (originalError == ERROR_FILE_NOT_FOUND || originalError == ERROR_PATH_NOT_FOUND))
        {
            const std::string redirect = FindExistingCandidate(fileName);
            if (!redirect.empty())
            {
                handle = oCreateFileA(redirect.c_str(), desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
                if (handle != INVALID_HANDLE_VALUE)
                {
                    Logger::Info(std::string("DLC loader redirected CreateFileA: ") + fileName + " -> " + redirect);
                    g_InHook = false;
                    return handle;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return handle;
    }

    HANDLE WINAPI hkCreateFileW(LPCWSTR fileName, DWORD desiredAccess, DWORD shareMode, LPSECURITY_ATTRIBUTES security, DWORD creationDisposition, DWORD flags, HANDLE templateFile)
    {
        if (g_InHook || !fileName || !oCreateFileW)
            return oCreateFileW(fileName, desiredAccess, shareMode, security, creationDisposition, flags, templateFile);

        g_InHook = true;

        const std::string rawForOverride = WideToUtf8(fileName);
        const std::string overridePath = FindStormEvolutionOverride(rawForOverride);
        const std::wstring overridePathW = Utf8ToWide(overridePath);
        if (!overridePathW.empty())
        {
            HANDLE overrideHandle = oCreateFileW(overridePathW.c_str(), desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
            if (overrideHandle != INVALID_HANDLE_VALUE)
            {
                Logger::Info(std::string("StormEvolution override CreateFileW: ") + rawForOverride + " -> " + overridePath);
                g_InHook = false;
                return overrideHandle;
            }
        }

        HANDLE handle = oCreateFileW(fileName, desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
        DWORD originalError = GetLastError();

        if (handle == INVALID_HANDLE_VALUE && (originalError == ERROR_FILE_NOT_FOUND || originalError == ERROR_PATH_NOT_FOUND))
        {
            const std::string raw = WideToUtf8(fileName);
            const std::string redirect = FindExistingCandidate(raw);
            const std::wstring redirectW = Utf8ToWide(redirect);
            if (!redirectW.empty())
            {
                handle = oCreateFileW(redirectW.c_str(), desiredAccess, shareMode, security, creationDisposition, flags, templateFile);
                if (handle != INVALID_HANDLE_VALUE)
                {
                    Logger::Info(std::string("DLC loader redirected CreateFileW: ") + raw + " -> " + redirect);
                    g_InHook = false;
                    return handle;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return handle;
    }

    DWORD WINAPI hkGetFileAttributesA(LPCSTR fileName)
    {
        if (g_InHook || !fileName || !oGetFileAttributesA)
            return oGetFileAttributesA(fileName);

        g_InHook = true;
        DWORD attrs = oGetFileAttributesA(fileName);
        DWORD originalError = GetLastError();

        if (attrs == INVALID_FILE_ATTRIBUTES && (originalError == ERROR_FILE_NOT_FOUND || originalError == ERROR_PATH_NOT_FOUND))
        {
            const std::string redirect = FindExistingCandidate(fileName);
            if (!redirect.empty())
            {
                attrs = oGetFileAttributesA(redirect.c_str());
                if (attrs != INVALID_FILE_ATTRIBUTES)
                {
                    Logger::Info(std::string("DLC loader redirected GetFileAttributesA: ") + fileName + " -> " + redirect);
                    g_InHook = false;
                    return attrs;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return attrs;
    }

    DWORD WINAPI hkGetFileAttributesW(LPCWSTR fileName)
    {
        if (g_InHook || !fileName || !oGetFileAttributesW)
            return oGetFileAttributesW(fileName);

        g_InHook = true;
        DWORD attrs = oGetFileAttributesW(fileName);
        DWORD originalError = GetLastError();

        if (attrs == INVALID_FILE_ATTRIBUTES && (originalError == ERROR_FILE_NOT_FOUND || originalError == ERROR_PATH_NOT_FOUND))
        {
            const std::string raw = WideToUtf8(fileName);
            const std::string redirect = FindExistingCandidate(raw);
            const std::wstring redirectW = Utf8ToWide(redirect);
            if (!redirectW.empty())
            {
                attrs = oGetFileAttributesW(redirectW.c_str());
                if (attrs != INVALID_FILE_ATTRIBUTES)
                {
                    Logger::Info(std::string("DLC loader redirected GetFileAttributesW: ") + raw + " -> " + redirect);
                    g_InHook = false;
                    return attrs;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return attrs;
    }

    HANDLE WINAPI hkFindFirstFileA(LPCSTR fileName, LPWIN32_FIND_DATAA data)
    {
        if (g_InHook || !fileName || !oFindFirstFileA)
            return oFindFirstFileA(fileName, data);

        g_InHook = true;
        HANDLE handle = oFindFirstFileA(fileName, data);
        DWORD originalError = GetLastError();

        if (handle == INVALID_HANDLE_VALUE && IsWildcardPath(fileName))
        {
            for (const std::string& candidate : BuildCandidates(fileName))
            {
                handle = oFindFirstFileA(candidate.c_str(), data);
                if (handle != INVALID_HANDLE_VALUE)
                {
                    Logger::Info(std::string("DLC loader redirected FindFirstFileA: ") + fileName + " -> " + candidate);
                    g_InHook = false;
                    return handle;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return handle;
    }

    HANDLE WINAPI hkFindFirstFileW(LPCWSTR fileName, LPWIN32_FIND_DATAW data)
    {
        if (g_InHook || !fileName || !oFindFirstFileW)
            return oFindFirstFileW(fileName, data);

        g_InHook = true;
        HANDLE handle = oFindFirstFileW(fileName, data);
        DWORD originalError = GetLastError();

        const std::string raw = WideToUtf8(fileName);
        if (handle == INVALID_HANDLE_VALUE && IsWildcardPath(raw))
        {
            for (const std::string& candidate : BuildCandidates(raw))
            {
                const std::wstring candidateW = Utf8ToWide(candidate);
                if (candidateW.empty())
                    continue;

                handle = oFindFirstFileW(candidateW.c_str(), data);
                if (handle != INVALID_HANDLE_VALUE)
                {
                    Logger::Info(std::string("DLC loader redirected FindFirstFileW: ") + raw + " -> " + candidate);
                    g_InHook = false;
                    return handle;
                }
            }
        }

        SetLastError(originalError);
        g_InHook = false;
        return handle;
    }

    template<typename Fn>
    bool HookKernel(const char* name, void* detour, Fn* original)
    {
        HMODULE kernel = GetModuleHandleA("kernel32.dll");
        if (!kernel)
            kernel = LoadLibraryA("kernel32.dll");
        if (!kernel)
            return false;

        void* target = reinterpret_cast<void*>(GetProcAddress(kernel, name));
        if (!target)
            return false;

        if (!HookManager::Create(target, detour, reinterpret_cast<void**>(original)))
            return false;

        if (!HookManager::Enable(target))
            return false;

        Logger::Info(std::string("DLC loader hooked kernel32!") + name);
        return true;
    }
}

namespace DlcContentLoader
{
    bool Init()
    {
        bool ok = true;
        ok &= HookKernel("CreateFileA", reinterpret_cast<void*>(&hkCreateFileA), &oCreateFileA);
        ok &= HookKernel("CreateFileW", reinterpret_cast<void*>(&hkCreateFileW), &oCreateFileW);
        ok &= HookKernel("GetFileAttributesA", reinterpret_cast<void*>(&hkGetFileAttributesA), &oGetFileAttributesA);
        ok &= HookKernel("GetFileAttributesW", reinterpret_cast<void*>(&hkGetFileAttributesW), &oGetFileAttributesW);
        ok &= HookKernel("FindFirstFileA", reinterpret_cast<void*>(&hkFindFirstFileA), &oFindFirstFileA);
        ok &= HookKernel("FindFirstFileW", reinterpret_cast<void*>(&hkFindFirstFileW), &oFindFirstFileW);

        for (const std::string folderText : SteamConfig::GetEvolutionFolders())
        {
            std::error_code ec;
            const std::filesystem::path folder = folderText;
            if (!std::filesystem::exists(folder, ec) || !std::filesystem::is_directory(folder, ec))
                continue;

            int count = 0;
            for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
            {
                if (ec) { ec.clear(); continue; }
                if (!it->is_regular_file(ec))
                    continue;
                const std::string item = it->path().string();
                if (IsBlockedSidecarFile(item))
                    continue;
                ++count;
                if (count <= 30)
                    Logger::Info("StormEvolution content registered: " + item);
            }
            Logger::Info("StormEvolution folder active: " + folder.string() + " files=" + std::to_string(count));
        }

        Logger::Info(std::string("DLC content loader initialized ") + (ok ? "OK" : "WITH FAILURES"));
        return ok;
    }

    void Shutdown()
    {
        Logger::Info("DLC content loader shutdown");
    }
}
