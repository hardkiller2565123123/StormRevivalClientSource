#include "StdInc.h"
#include "ResourceRedirector.h"
#include "Logger.h"
#include "HookManager.h"

#include <Windows.h>
#include <MinHook.h>
#include <algorithm>
#include <atomic>
#include <filesystem>
#include <mutex>
#include <sstream>
#include <unordered_map>

namespace fs = std::filesystem;

namespace
{
    constexpr uintptr_t kRvaResourceGetOrLoad = 0x14126CE30 - 0x140000000;   // sub_14126CE30
    constexpr uintptr_t kRvaScaleformQueueMovie = 0x140BEEE70 - 0x140000000; // sub_140BEEE70

    using ResourceGetOrLoadFn = int64_t(__fastcall*)(int64_t manager, const char* path, int64_t args);
    using ScaleformQueueMovieFn = int64_t(__fastcall*)(void* manager, const char* path, int priorityFront);

    ResourceGetOrLoadFn g_ResourceGetOrLoad = nullptr;
    ScaleformQueueMovieFn g_ScaleformQueueMovie = nullptr;

    uintptr_t g_Base = 0;
    std::atomic<bool> g_Enabled{ true };
    std::mutex g_Mutex;

    std::string g_ModsRoot;
    std::vector<std::string> g_ModFolders;
    std::vector<ResourceTypes::LoadedResourceRow> g_Rows;
    std::unordered_map<std::string, size_t> g_RowIndex;

    std::string ToLowerSlashes(std::string value)
    {
        std::replace(value.begin(), value.end(), '\\', '/');
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return (char)std::tolower(c); });
        while (!value.empty() && value.front() == '/')
            value.erase(value.begin());
        return value;
    }

    std::string ExeDir()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        fs::path p(path);
        return p.parent_path().string();
    }

    bool FileExists(const fs::path& p)
    {
        std::error_code ec;
        return fs::exists(p, ec) && fs::is_regular_file(p, ec);
    }

    bool EndsWithXfbin(const std::string& path)
    {
        const std::string low = ToLowerSlashes(path);
        return low.size() >= 6 && low.substr(low.size() - 6) == ".xfbin";
    }

    // If the game asks for data/ui/a/b without .xfbin, also try .xfbin.
    std::vector<std::string> CandidateRelativePaths(const char* rawPath)
    {
        std::vector<std::string> out;
        if (!rawPath || !rawPath[0])
            return out;

        std::string p = ToLowerSlashes(rawPath);

        // Strip drive-like prefix used by nucc resource paths: sim:data/ui/foo.xfbin
        size_t colon = p.find(':');
        if (colon != std::string::npos && colon + 1 < p.size())
            p = p.substr(colon + 1);

        out.push_back(p);

        // The normalized resource lookup strips .xfbin. Let mods work both ways.
        if (!EndsWithXfbin(p))
            out.push_back(p + ".xfbin");

        return out;
    }

    ResourceTypes::RedirectHit FindRedirect(ResourceTypes::RedirectKind kind, const char* rawPath)
    {
        ResourceTypes::RedirectHit hit{};
        hit.kind = kind;
        hit.originalPath = rawPath ? rawPath : "";

        if (!g_Enabled.load() || !rawPath || !rawPath[0])
            return hit;

        const auto candidates = CandidateRelativePaths(rawPath);
        std::lock_guard<std::mutex> lock(g_Mutex);

        for (const std::string& modFolder : g_ModFolders)
        {
            fs::path modPath(modFolder);
            const std::string modName = modPath.filename().string();

            for (const std::string& rel : candidates)
            {
                fs::path candidate = modPath / fs::path(rel);
                if (FileExists(candidate))
                {
                    hit.redirected = true;
                    hit.moddedPath = candidate.string();
                    hit.modName = modName;
                    return hit;
                }
            }
        }

        return hit;
    }

    void AddRow(const ResourceTypes::RedirectHit& hit)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);

        std::ostringstream key;
        key << (int)hit.kind << "|" << ToLowerSlashes(hit.originalPath);
        const std::string k = key.str();

        auto it = g_RowIndex.find(k);
        if (it != g_RowIndex.end())
        {
            ResourceTypes::LoadedResourceRow& row = g_Rows[it->second];
            row.requestCount++;
            if (hit.redirected)
            {
                row.redirected = true;
                row.finalPath = hit.moddedPath;
                row.modName = hit.modName;
            }
            return;
        }

        ResourceTypes::LoadedResourceRow row{};
        row.kind = hit.kind;
        row.originalPath = hit.originalPath;
        row.finalPath = hit.redirected ? hit.moddedPath : hit.originalPath;
        row.modName = hit.modName;
        row.redirected = hit.redirected;
        row.requestCount = 1;

        g_RowIndex[k] = g_Rows.size();
        g_Rows.push_back(row);
    }

    int64_t __fastcall ResourceGetOrLoad_Hook(int64_t manager, const char* path, int64_t args)
    {
        ResourceTypes::RedirectHit hit = FindRedirect(ResourceTypes::RedirectKind::XfbinResource, path);
        AddRow(hit);

        if (hit.redirected)
        {
            Logger::Info("[ResourceRedirect][XFBIN] " + hit.originalPath + " -> " + hit.moddedPath);
            return g_ResourceGetOrLoad(manager, hit.moddedPath.c_str(), args);
        }

        Logger::Info(std::string("[Resource][XFBIN] ") + (path ? path : "<null>"));
        return g_ResourceGetOrLoad(manager, path, args);
    }

    int64_t __fastcall ScaleformQueueMovie_Hook(void* manager, const char* path, int priorityFront)
    {
        ResourceTypes::RedirectHit hit = FindRedirect(ResourceTypes::RedirectKind::ScaleformMovie, path);
        AddRow(hit);

        if (hit.redirected)
        {
            Logger::Info("[ResourceRedirect][Scaleform] " + hit.originalPath + " -> " + hit.moddedPath);
            return g_ScaleformQueueMovie(manager, hit.moddedPath.c_str(), priorityFront);
        }

        Logger::Info(std::string("[Resource][Scaleform] ") + (path ? path : "<null>"));
        return g_ScaleformQueueMovie(manager, path, priorityFront);
    }

    bool InstallHook(uintptr_t address, void* detour, void** original, const char* name)
    {
        if (MH_CreateHook(reinterpret_cast<void*>(address), detour, original) != MH_OK)
        {
            Logger::Error(std::string("ResourceRedirector: MH_CreateHook failed for ") + name);
            return false;
        }
        if (MH_EnableHook(reinterpret_cast<void*>(address)) != MH_OK)
        {
            Logger::Error(std::string("ResourceRedirector: MH_EnableHook failed for ") + name);
            return false;
        }
        Logger::Info(std::string("ResourceRedirector hook installed: ") + name);
        return true;
    }
}

namespace ResourceRedirector
{
    bool Init(uintptr_t gameBase)
    {
        g_Base = gameBase;
        g_ModsRoot = (fs::path(ExeDir()) / "NarutoStormConnectionsRevived" / "mods").string();
        fs::create_directories(g_ModsRoot);
        RescanMods();

        const bool ok1 = InstallHook(g_Base + kRvaResourceGetOrLoad, (void*)ResourceGetOrLoad_Hook, (void**)&g_ResourceGetOrLoad, "sub_14126CE30 ResourceManager_GetOrLoad");
        const bool ok2 = InstallHook(g_Base + kRvaScaleformQueueMovie, (void*)ScaleformQueueMovie_Hook, (void**)&g_ScaleformQueueMovie, "sub_140BEEE70 ScaleformManager_QueueMovieLoad");

        Logger::Info("ResourceRedirector initialized root=" + g_ModsRoot);
        return ok1 && ok2;
    }

    void Shutdown()
    {
        if (g_Base)
        {
            MH_DisableHook(reinterpret_cast<void*>(g_Base + kRvaResourceGetOrLoad));
            MH_DisableHook(reinterpret_cast<void*>(g_Base + kRvaScaleformQueueMovie));
        }
        Logger::Info("ResourceRedirector shutdown");
    }

    void RescanMods()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_ModFolders.clear();

        std::error_code ec;
        if (!fs::exists(g_ModsRoot, ec))
            fs::create_directories(g_ModsRoot, ec);

        for (const auto& entry : fs::directory_iterator(g_ModsRoot, ec))
        {
            if (entry.is_directory(ec))
                g_ModFolders.push_back(entry.path().string());
        }

        std::sort(g_ModFolders.begin(), g_ModFolders.end());
        Logger::Info("ResourceRedirector: mod folders=" + std::to_string(g_ModFolders.size()));
    }

    bool Enabled() { return g_Enabled.load(); }
    void SetEnabled(bool enabled) { g_Enabled.store(enabled); }
    std::string ModsRoot() { return g_ModsRoot; }

    std::vector<std::string> ModFolders()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return g_ModFolders;
    }

    std::vector<ResourceTypes::LoadedResourceRow> SnapshotRows()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return g_Rows;
    }

    void ClearLogRows()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Rows.clear();
        g_RowIndex.clear();
    }
}
