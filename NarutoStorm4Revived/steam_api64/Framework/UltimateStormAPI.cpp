#include "StdInc.h"
#include "UltimateStormAPI.h"
#include "Logger.h"
#include "Common.h"
#include "FileParser.h"
#include "ModManager.h"
#include "PluginManager.h"
#include "HookFunctions.h"
#include "PatternScan.h"

#include <atomic>
#include <filesystem>
#include <fstream>
#include <mutex>

std::atomic_bool g_IsUpdateAvailable(false);
std::string g_RemoteLatestVersion;
std::string config_path;

namespace
{
    std::once_flag g_InitOnce;
    bool g_Ready = false;

    std::filesystem::path ExeFolder()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
    }

    void EnsureRuntimeFolders()
    {
        const auto root = ExeFolder() / "NarutoStorm4Revived";
        const char* folders[] = { "Mods", "Plugins", "Lua", "Tools", "Cache", "Config", "logs", "storage" };
        for (const char* f : folders)
        {
            try { std::filesystem::create_directories(root / f); } catch (...) {}
        }

        config_path = (root / "Config" / "UltimateStormAPI.ini").string();
    }

    void WriteRuntimeManifest()
    {
        try
        {
            const auto manifest = ExeFolder() / "NarutoStorm4Revived" / "Config" / "StormAPI_Merged.txt";
            std::ofstream out(manifest, std::ios::out | std::ios::trunc);
            out << "UltimateStormAPI merged directly into steam_api64 root.\n";
            out << "Original creator credit: TheLeonX.\n";
            out << "xinput9_1_0 proxy files were intentionally not included.\n";
            out << "Runtime folders are under NarutoStorm4Revived, not a separate StormAPI folder.\n";
        }
        catch (...) {}
    }
}

int __stdcall UltimateStormAPI::Main()
{
    std::call_once(g_InitOnce, []()
    {
        EnsureRuntimeFolders();
        WriteRuntimeManifest();
        g_Ready = true;
        Logger::Info("UltimateStormAPI merged runtime initialized without xinput proxy");
    });
    return 1;
}

int __stdcall UltimateStormAPI::LoopConsole()
{
    return g_Ready ? 1 : 0;
}

int __stdcall UltimateStormAPI::LoopGame()
{
    return g_Ready ? 1 : 0;
}

void UltimateStormAPI::Update()
{
    if (!g_Ready)
        Main();
}

void UltimateStormAPI::PreRender()
{
    if (!g_Ready)
        Main();
}

void UltimateStormAPI::PostRender()
{
}

void UltimateStormAPI::OnGUI(bool, __int64, __int64)
{
    if (!g_Ready)
        Main();
}

void UltimateStormAPI::ReadFrameworkFiles(bool)
{
    if (!g_Ready)
        Main();
    Logger::Info("UltimateStormAPI ReadFrameworkFiles: using NarutoStorm4Revived runtime folders");
}
