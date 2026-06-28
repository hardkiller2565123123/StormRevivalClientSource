#include "StdInc.h"
#include "StormAPIBridge.h"
#include "Logger.h"
#include "UltimateStormAPI.h"

namespace
{
    bool g_Initialized = false;
    int g_SourceFiles = 0;

    std::filesystem::path ExeFolderInternal()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
    }

    int CountMergedApiFiles()
    {
        int count = 0;
        try
        {
            const auto root = ExeFolderInternal() / "steam_api64";
            if (std::filesystem::exists(root))
            {
                for (const auto& entry : std::filesystem::directory_iterator(root))
                {
                    if (!entry.is_regular_file())
                        continue;
                    const auto ext = entry.path().extension().string();
                    if (ext == ".cpp" || ext == ".h")
                        ++count;
                }
            }
        }
        catch (...) {}
        return count;
    }

    void EnsureRuntimeFolder(const std::filesystem::path& path)
    {
        try { std::filesystem::create_directories(path); } catch (...) {}
    }
}

namespace StormAPIBridge
{
    std::filesystem::path ExeFolder()
    {
        return ExeFolderInternal();
    }

    std::filesystem::path RootFolder()
    {
        return ExeFolder() / "NarutoStorm4Revived";
    }

    std::filesystem::path SourceFolder()
    {
        return ExeFolder() / "steam_api64";
    }

    int BundledSourceFileCount()
    {
        return g_SourceFiles;
    }

    const char* CreditText()
    {
        return "StormApi Loaded - Created by TheLeonX";
    }

    bool Init()
    {
        if (g_Initialized)
            return true;

        const auto root = RootFolder();
        EnsureRuntimeFolder(root / "Mods");
        EnsureRuntimeFolder(root / "Plugins");
        EnsureRuntimeFolder(root / "Lua");
        EnsureRuntimeFolder(root / "Tools");
        EnsureRuntimeFolder(root / "Cache");
        EnsureRuntimeFolder(root / "Config");
        EnsureRuntimeFolder(root / "logs");
        EnsureRuntimeFolder(root / "storage");

        g_SourceFiles = CountMergedApiFiles();
        UltimateStormAPI::Main();
        UltimateStormAPI::ReadFrameworkFiles(false);

        g_Initialized = true;
        Logger::Info("StormAPIBridge initialized: UltimateStormAPI merged into steam_api64 root; no separate StormAPI folder; files=" + std::to_string(g_SourceFiles));
        return true;
    }

    void Shutdown()
    {
        if (!g_Initialized)
            return;
        Logger::Info("StormAPIBridge shutdown");
        g_Initialized = false;
    }

    bool IsEnabled()
    {
        return g_Initialized;
    }
}
