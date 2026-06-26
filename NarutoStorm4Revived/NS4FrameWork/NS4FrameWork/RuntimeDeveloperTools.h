#pragma once
#include "StdInc.h"
#include "RuntimeAssetTelemetry.h"

namespace RuntimeDeveloperTools
{
    struct ToolState
    {
        bool EnableSceneViewer = true;
        bool EnableNetworkViewer = true;
        bool EnableLobbyInspector = true;
        bool EnableTransitionLogger = true;
        bool EnableContentControls = true;
        bool EnableMemoryExplorer = false;
        bool EnablePacketLogger = false;
        bool EnableHotReload = true;
        bool EnableDebugMenuTools = true;
        bool EnableDeveloperConsole = true;
        bool EnableScreenshotTools = true;
        bool EnableReplayTools = true;
        bool SafeMode = true;

        bool DebugTuiLoader = true;
        bool NoReleaseRoot = true;
        bool TuiRoot = true;
        bool StormEvolution = true;
        bool LogRedirectedFiles = true;
        bool DisableDlcRedirects = false;

        std::string CurrentScene = "unknown";
        std::string PreviousScene = "unknown";
        std::string NetworkScene = "unknown";
        std::string LobbyState = "not in lobby";
        std::string LobbyId = "0";
        std::string HostSteamId = "0";
        std::string LocalSteamId = "0";
        std::string LastRedirectedFile;
        std::string LastLoadedAsset;
        std::string LastCommandResult;
        int LobbyMembers = 0;
        int LobbyLimit = 2;
        int P2PSessions = 0;
        int SearchResults = 0;
    };

    bool Init();
    void Shutdown();

    ToolState& State();
    void TickHotkeys();
    void DrawPage();

    void SetCurrentScene(const std::string& scene);
    void SetNetworkState(const std::string& scene, const std::string& lobbyState);
    void SetLobbyInfo(const std::string& lobbyId, const std::string& host, const std::string& local, int members, int limit);
    void SetLastRedirectedFile(const std::string& path);
    void SetLastLoadedAsset(const std::string& path);
    void AddTransition(const std::string& from, const std::string& to);
    void AddPacketEvent(const std::string& eventText);

    void ReloadContentRoots();
    void DumpRuntimeReport();
    void DumpLoadedFilePaths();
    void RequestHotReload();
    void RequestDebugMenuEnable();
    void RequestSceneLoad(const std::string& sceneName);

    std::vector<std::string> GetTransitions();
    std::vector<std::string> GetPacketEvents();
    std::vector<std::string> GetLoadedFiles();
}
