#include "StdInc.h"
#include "ResourceRedirector.h"
#include "HookManager.h"
#include "Logger.h"

#include <Windows.h>
#include <MinHook.h>

#include <algorithm>
#include <atomic>
#include <cctype>
#include <filesystem>
#include <mutex>
#include <sstream>
#include <vector>
#include <unordered_map>

namespace fs = std::filesystem;

namespace
{
    // RVA map from current NSC x64 build.
    constexpr uintptr_t kRvaResourceGetOrLoad = 0x126CE30;   // sub_14126CE30
    constexpr uintptr_t kRvaScaleformQueueMovie = 0xBEEE70;  // sub_140BEEE70

    using ResourceGetOrLoadFn = int64_t(__fastcall*)(int64_t manager, const char* path, int64_t args);
    using ScaleformQueueMovieFn = int64_t(__fastcall*)(void* manager, const char* path, int priorityFront);

    ResourceGetOrLoadFn g_ResourceGetOrLoad = nullptr;
    ScaleformQueueMovieFn g_ScaleformQueueMovie = nullptr;

    uintptr_t g_Base = 0;
    std::atomic<bool> g_Enabled{ true };
    std::mutex g_Mutex;

    std::string g_ModsRoot;
    std::vector<std::string> g_ModFolders;
    std::vector<ResourceTypes::ModFileEntry> g_ModFiles;

    // exact normalized rel path -> mod file
    std::unordered_map<std::string, ResourceTypes::ModFileEntry> g_ByRelative;

    // filename only -> first mod file with that filename
    std::unordered_map<std::string, ResourceTypes::ModFileEntry> g_ByFileName;

    std::vector<ResourceTypes::LoadedResourceRow> g_Rows;
    std::unordered_map<std::string, size_t> g_RowIndex;

    std::string ToLowerSlashes(std::string value)
    {
        std::replace(value.begin(), value.end(), '\\', '/');
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });

        while (!value.empty() && value.front() == '/')
            value.erase(value.begin());

        return value;
    }

    std::string StripResourcePrefix(std::string value)
    {
        value = ToLowerSlashes(std::move(value));

        // nucc paths can be sim:data/ui/...
        const size_t colon = value.find(':');
        if (colon != std::string::npos && colon + 1 < value.size())
            value = value.substr(colon + 1);

        // If a full absolute path is ever passed, keep the useful data/... tail.
        const size_t dataPos = value.find("data/");
        if (dataPos != std::string::npos)
            value = value.substr(dataPos);

        return value;
    }

    std::string FileNameOnly(const std::string& path)
    {
        const std::string p = ToLowerSlashes(path);
        const size_t slash = p.find_last_of('/');
        if (slash == std::string::npos)
            return p;
        return p.substr(slash + 1);
    }

    bool EndsWith(const std::string& value, const char* suffix)
    {
        const std::string s = suffix ? suffix : "";
        return value.size() >= s.size() && value.compare(value.size() - s.size(), s.size(), s) == 0;
    }

    std::string ExeDir()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        return fs::path(path).parent_path().string();
    }

    bool FileExists(const fs::path& path)
    {
        std::error_code ec;
        return fs::exists(path, ec) && fs::is_regular_file(path, ec);
    }

    std::vector<std::string> CandidateKeys(const char* rawPath)
    {
        std::vector<std::string> keys;
        if (!rawPath || !rawPath[0])
            return keys;

        const std::string stripped = StripResourcePrefix(rawPath);
        if (stripped.empty())
            return keys;

        auto add = [&](std::string key)
        {
            key = ToLowerSlashes(std::move(key));
            if (!key.empty() && std::find(keys.begin(), keys.end(), key) == keys.end())
                keys.push_back(key);
        };

        add(stripped);

        // Native lookup often strips .xfbin, so support both keys.
        if (EndsWith(stripped, ".xfbin"))
            add(stripped.substr(0, stripped.size() - 6));
        else
            add(stripped + ".xfbin");

        // Scaleform can ask for .swf while packed files may be .gfx.
        if (EndsWith(stripped, ".swf"))
            add(stripped.substr(0, stripped.size() - 4) + ".gfx");
        if (EndsWith(stripped, ".gfx"))
            add(stripped.substr(0, stripped.size() - 4) + ".swf");

        return keys;
    }

    void InsertModFile(const ResourceTypes::ModFileEntry& entry)
    {
        // First mod alphabetically wins. This makes load order deterministic.
        if (!g_ByRelative.count(entry.RelativePath))
            g_ByRelative.emplace(entry.RelativePath, entry);

        if (!g_ByFileName.count(entry.FileName))
            g_ByFileName.emplace(entry.FileName, entry);
    }

    ResourceTypes::RedirectHit FindRedirect(ResourceTypes::RedirectKind kind, const char* rawPath)
    {
        ResourceTypes::RedirectHit hit{};
        hit.Kind = kind;
        hit.OriginalPath = rawPath ? rawPath : "";
        hit.FinalPath = hit.OriginalPath;

        if (!g_Enabled.load() || !rawPath || !rawPath[0])
            return hit;

        const std::vector<std::string> candidates = CandidateKeys(rawPath);
        std::lock_guard<std::mutex> lock(g_Mutex);

        for (const std::string& key : candidates)
        {
            auto it = g_ByRelative.find(key);
            if (it != g_ByRelative.end())
            {
                hit.Redirected = true;
                hit.FinalPath = it->second.AbsolutePath;
                hit.ModName = it->second.ModName;
                return hit;
            }
        }

        // Last-resort similar match: same filename anywhere in mods.
        for (const std::string& key : candidates)
        {
            auto it = g_ByFileName.find(FileNameOnly(key));
            if (it != g_ByFileName.end())
            {
                hit.Redirected = true;
                hit.FinalPath = it->second.AbsolutePath;
                hit.ModName = it->second.ModName;
                return hit;
            }
        }

        return hit;
    }

    void AddRow(const ResourceTypes::RedirectHit& hit)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);

        std::ostringstream key;
        key << static_cast<int>(hit.Kind) << "|" << ToLowerSlashes(hit.OriginalPath);
        const std::string mapKey = key.str();

        auto it = g_RowIndex.find(mapKey);
        if (it != g_RowIndex.end())
        {
            ResourceTypes::LoadedResourceRow& row = g_Rows[it->second];
            ++row.RequestCount;
            if (hit.Redirected)
            {
                row.Redirected = true;
                row.FinalPath = hit.FinalPath;
                row.ModName = hit.ModName;
            }
            return;
        }

        ResourceTypes::LoadedResourceRow row{};
        row.Kind = hit.Kind;
        row.OriginalPath = hit.OriginalPath;
        row.FinalPath = hit.FinalPath;
        row.ModName = hit.ModName;
        row.Redirected = hit.Redirected;
        row.RequestCount = 1;

        g_RowIndex[mapKey] = g_Rows.size();
        g_Rows.push_back(row);
    }

    int64_t __fastcall ResourceGetOrLoad_Hook(int64_t manager, const char* path, int64_t args)
    {
        const ResourceTypes::RedirectHit hit = FindRedirect(ResourceTypes::RedirectKind::XfbinResource, path);
        AddRow(hit);

        if (hit.Redirected)
        {
            Logger::Info("[ResourceRedirect][XFBIN] " + hit.OriginalPath + " -> " + hit.FinalPath + " mod=" + hit.ModName);
            return g_ResourceGetOrLoad(manager, hit.FinalPath.c_str(), args);
        }

        Logger::Info(std::string("[Resource][XFBIN] ") + (path ? path : "<null>"));
        return g_ResourceGetOrLoad(manager, path, args);
    }

    int64_t __fastcall ScaleformQueueMovie_Hook(void* manager, const char* path, int priorityFront)
    {
        const ResourceTypes::RedirectHit hit = FindRedirect(ResourceTypes::RedirectKind::ScaleformMovie, path);
        AddRow(hit);

        if (hit.Redirected)
        {
            Logger::Info("[ResourceRedirect][Scaleform] " + hit.OriginalPath + " -> " + hit.FinalPath + " mod=" + hit.ModName);
            return g_ScaleformQueueMovie(manager, hit.FinalPath.c_str(), priorityFront);
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

        const bool resourceOk = InstallHook(
            g_Base + kRvaResourceGetOrLoad,
            reinterpret_cast<void*>(ResourceGetOrLoad_Hook),
            reinterpret_cast<void**>(&g_ResourceGetOrLoad),
            "sub_14126CE30 ResourceManager_GetOrLoad");

        const bool scaleformOk = InstallHook(
            g_Base + kRvaScaleformQueueMovie,
            reinterpret_cast<void*>(ScaleformQueueMovie_Hook),
            reinterpret_cast<void**>(&g_ScaleformQueueMovie),
            "sub_140BEEE70 ScaleformManager_QueueMovieLoad");

        Logger::Info("ResourceRedirector initialized root=" + g_ModsRoot);
        return resourceOk && scaleformOk;
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
        g_ModFiles.clear();
        g_ByRelative.clear();
        g_ByFileName.clear();

        std::error_code ec;
        if (!fs::exists(g_ModsRoot, ec))
            fs::create_directories(g_ModsRoot, ec);

        auto addModFile = [&](const fs::path& absolute, const fs::path& rootForRelative, const std::string& modName)
        {
            std::error_code relEc;
            fs::path relPath = fs::relative(absolute, rootForRelative, relEc);
            if (relEc)
                relPath = absolute.filename();

            ResourceTypes::ModFileEntry entry{};
            entry.ModName = modName;
            entry.AbsolutePath = absolute.string();
            entry.RelativePath = StripResourcePrefix(relPath.string());
            entry.FileName = FileNameOnly(entry.RelativePath);

            if (entry.RelativePath.empty() || entry.FileName.empty())
                return;

            g_ModFiles.push_back(entry);
            InsertModFile(entry);

            // Common loose-file aliases. Native lookup may strip .xfbin. Scaleform may request .swf
            // while a mod author ships .gfx, or the other way around.
            if (EndsWith(entry.RelativePath, ".xfbin"))
            {
                ResourceTypes::ModFileEntry alias = entry;
                alias.RelativePath = entry.RelativePath.substr(0, entry.RelativePath.size() - 6);
                InsertModFile(alias);
            }
            if (EndsWith(entry.RelativePath, ".swf"))
            {
                ResourceTypes::ModFileEntry alias = entry;
                alias.RelativePath = entry.RelativePath.substr(0, entry.RelativePath.size() - 4) + ".gfx";
                InsertModFile(alias);
            }
            if (EndsWith(entry.RelativePath, ".gfx"))
            {
                ResourceTypes::ModFileEntry alias = entry;
                alias.RelativePath = entry.RelativePath.substr(0, entry.RelativePath.size() - 4) + ".swf";
                InsertModFile(alias);
            }
        };

        // Supports both styles:
        //   mods/MyMod/data/...      = named mod folder
        //   mods/data/...            = loose root override
        //   mods/somefile.xfbin      = filename-only fallback override
        for (const auto& entry : fs::recursive_directory_iterator(g_ModsRoot, ec))
        {
            if (ec)
                break;
            if (!entry.is_regular_file(ec))
                continue;

            const fs::path abs = entry.path();
            fs::path relToMods = fs::relative(abs, g_ModsRoot, ec);
            if (ec)
                relToMods = abs.filename();

            std::string modName = "LooseRoot";
            fs::path rootForRelative = g_ModsRoot;

            auto it = relToMods.begin();
            if (it != relToMods.end())
            {
                const std::string first = it->string();
                const fs::path maybeMod = fs::path(g_ModsRoot) / first;
                std::error_code dirEc;
                if (fs::is_directory(maybeMod, dirEc) && ToLowerSlashes(first) != "data")
                {
                    modName = first;
                    rootForRelative = maybeMod;
                }
            }

            if (std::find(g_ModFolders.begin(), g_ModFolders.end(), rootForRelative.string()) == g_ModFolders.end())
                g_ModFolders.push_back(rootForRelative.string());

            addModFile(abs, rootForRelative, modName);
        }

        std::sort(g_ModFolders.begin(), g_ModFolders.end());
        std::sort(g_ModFiles.begin(), g_ModFiles.end(), [](const ResourceTypes::ModFileEntry& a, const ResourceTypes::ModFileEntry& b)
        {
            if (a.ModName != b.ModName)
                return a.ModName < b.ModName;
            return a.RelativePath < b.RelativePath;
        });

        Logger::Info("ResourceRedirector: mod folders=" + std::to_string(g_ModFolders.size()) +
            " files=" + std::to_string(g_ModFiles.size()) +
            " exactKeys=" + std::to_string(g_ByRelative.size()) +
            " filenameKeys=" + std::to_string(g_ByFileName.size()));
    }

    bool Enabled()
    {
        return g_Enabled.load();
    }

    void SetEnabled(bool enabled)
    {
        g_Enabled.store(enabled);
    }

    std::string ModsRoot()
    {
        return g_ModsRoot;
    }

    std::vector<std::string> ModFolders()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return g_ModFolders;
    }

    std::vector<ResourceTypes::ModFileEntry> SnapshotModFiles()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return g_ModFiles;
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
