#include "DX11OverlayInternal.h"
#include "DevToolsManager.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <shellapi.h>

namespace
{
    struct DevToolsState
    {
        bool initialized = false;

        bool enableSceneViewer = true;
        bool enableSceneTransitions = true;
        bool enableNetworkViewer = true;
        bool enableLobbyInspector = true;
        bool enablePacketLogger = false;
        bool enableP2PLogger = false;
        bool enableDebugMenuTools = false;
        bool enableHiddenSceneLoader = false;
        bool enableObjectInspector = false;
        bool enableMemoryExplorer = false;
        bool enableAssetHotReload = true;
        bool enableModConflicts = true;
        bool enableModLoadOrder = true;
        bool enablePackageBuilder = true;
        bool enableScreenshotMode = false;
        bool enableReplayTools = false;
        bool enableRuntimeOffsetScanner = false;
        bool enableDeveloperConsole = true;

        bool contentNoRelease = false;
        bool contentTui = false;
        bool contentStormEvolution = true;
        bool logRedirectedFiles = true;
        bool disableDlcRedirects = false;
        bool safeContentMode = true;

        char currentScene[128] = "unknown";
        char previousScene[128] = "unknown";
        char networkState[256] = "offline / not in network scene";
        char lobbyState[256] = "none";
        char selectedScene[128] = "ccSceneTitle";
        char consoleInput[256] = "";
        char memoryExpression[128] = "";
        char packageName[128] = "NewStormMod";

        uint64_t currentLobbyId = 0;
        uint64_t hostSteamId = 0;
        uint64_t localSteamId = 0;
        uint64_t remoteSteamId = 0;
        int lobbyMembers = 0;
        int lobbyLimit = 2;
        int lastSearchResults = 0;
        int packetCount = 0;
        int p2pPackets = 0;

        std::vector<std::string> sceneTransitions;
        std::vector<std::string> loadedPaths;
        std::vector<std::string> networkEvents;
        std::vector<std::string> consoleLines;
        std::vector<std::string> bookmarks;
    };

    DevToolsState g_State;

    std::filesystem::path GetGameFolder()
    {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        return std::filesystem::path(path).parent_path();
    }

    std::filesystem::path GetReportFolder()
    {
        std::filesystem::path folder = GetGameFolder() / "NarutoStorm4Revived" / "DevToolsReports";
        std::error_code ec;
        std::filesystem::create_directories(folder, ec);
        return folder;
    }

    std::string NowText()
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);
        char buffer[64]{};
        sprintf_s(buffer, "%04u-%02u-%02u_%02u-%02u-%02u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        return buffer;
    }

    void PushLimited(std::vector<std::string>& list, const std::string& text, size_t maxCount = 512)
    {
        list.push_back(text);
        if (list.size() > maxCount)
            list.erase(list.begin(), list.begin() + (list.size() - maxCount));
    }

    void AddConsole(const std::string& text)
    {
        PushLimited(g_State.consoleLines, text, 300);
        Logger::Info("[DevTools] " + text);
    }

    void DumpLines(const char* name, const std::vector<std::string>& lines)
    {
        const auto path = GetReportFolder() / (std::string(name) + "_" + NowText() + ".txt");
        std::ofstream out(path, std::ios::binary);
        for (const auto& line : lines)
            out << line << "\n";
        AddConsole(std::string("Wrote report: ") + path.string());
    }

    void DumpStateReport()
    {
        const auto path = GetReportFolder() / ("devtools_state_" + NowText() + ".txt");
        std::ofstream out(path, std::ios::binary);
        out << "NS4FrameWork DevTools State\n";
        out << "Scene=" << g_State.currentScene << "\n";
        out << "PreviousScene=" << g_State.previousScene << "\n";
        out << "NetworkState=" << g_State.networkState << "\n";
        out << "LobbyState=" << g_State.lobbyState << "\n";
        out << "LobbyId=" << g_State.currentLobbyId << "\n";
        out << "Members=" << g_State.lobbyMembers << "/" << g_State.lobbyLimit << "\n";
        out << "LastSearchResults=" << g_State.lastSearchResults << "\n";
        out << "PacketCount=" << g_State.packetCount << "\n";
        out << "P2PPackets=" << g_State.p2pPackets << "\n";
        out << "\nSceneTransitions\n";
        for (const auto& line : g_State.sceneTransitions) out << line << "\n";
        out << "\nLoadedPaths\n";
        for (const auto& line : g_State.loadedPaths) out << line << "\n";
        out << "\nNetworkEvents\n";
        for (const auto& line : g_State.networkEvents) out << line << "\n";
        AddConsole(std::string("Wrote state report: ") + path.string());
    }

    bool HotkeyPressed(int vk)
    {
        return (GetAsyncKeyState(vk) & 1) != 0;
    }

    void DrawBool(const char* label, bool& value, const char* help = nullptr)
    {
        ImGui::Checkbox(label, &value);
        if (help)
            HelpMarker(help);
    }

    void DrawListBox(const char* title, const std::vector<std::string>& lines, float height = 210.0f)
    {
        ImGui::TextUnformatted(title);
        ImGui::BeginChild(title, ImVec2(0.0f, height), true, ImGuiWindowFlags_HorizontalScrollbar);
        for (const auto& line : lines)
            ImGui::TextUnformatted(line.c_str());
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY() - 4.0f)
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();
    }

    void DrawOverview()
    {
        ImGui::Text("DevTools Status");
        ImGui::Separator();
        ImGui::Columns(2, nullptr, false);
        ImGui::Text("Current Scene"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.currentScene); ImGui::NextColumn();
        ImGui::Text("Network State"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.networkState); ImGui::NextColumn();
        ImGui::Text("Lobby State"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.lobbyState); ImGui::NextColumn();
        ImGui::Text("Lobby"); ImGui::NextColumn(); ImGui::Text("%llu", static_cast<unsigned long long>(g_State.currentLobbyId)); ImGui::NextColumn();
        ImGui::Text("Members"); ImGui::NextColumn(); ImGui::Text("%d / %d", g_State.lobbyMembers, g_State.lobbyLimit); ImGui::NextColumn();
        ImGui::Text("Search Results"); ImGui::NextColumn(); ImGui::Text("%d", g_State.lastSearchResults); ImGui::NextColumn();
        ImGui::Columns(1);

        ImGui::Spacing();
        if (ImGui::Button("Dump Full DevTools Report")) DumpStateReport();
        ImGui::SameLine();
        if (ImGui::Button("Clear Runtime Logs"))
        {
            g_State.sceneTransitions.clear();
            g_State.loadedPaths.clear();
            g_State.networkEvents.clear();
            AddConsole("Runtime logs cleared");
        }
    }

    void DrawSceneTools()
    {
        DrawBool("Live Scene Viewer", g_State.enableSceneViewer, "Shows the current game scene/state when hooks feed it.");
        DrawBool("Scene Transition Logger", g_State.enableSceneTransitions, "Records scene changes for debugging hangs.");
        DrawBool("Hidden Scene Loader", g_State.enableHiddenSceneLoader, "UI scaffold for future direct scene switching.");
        DrawBool("Force Debug Menu Tools", g_State.enableDebugMenuTools, "UI scaffold for DebugMenu/no_release experiments.");

        ImGui::Separator();
        ImGui::InputText("Scene Name", g_State.selectedScene, sizeof(g_State.selectedScene));
        if (ImGui::Button("Queue Scene Load Command"))
            AddConsole(std::string("scene command queued: ") + g_State.selectedScene);
        ImGui::SameLine();
        if (ImGui::Button("Mark Current Scene"))
            DevToolsManager::SetCurrentScene(g_State.selectedScene);

        DrawListBox("Scene Transitions", g_State.sceneTransitions);
    }

    void DrawNetworkTools()
    {
        DrawBool("Network State Viewer", g_State.enableNetworkViewer);
        DrawBool("Lobby Inspector", g_State.enableLobbyInspector);
        DrawBool("Packet Logger", g_State.enablePacketLogger);
        DrawBool("P2P Logger", g_State.enableP2PLogger);

        ImGui::Separator();
        ImGui::Text("Lobby ID: %llu", static_cast<unsigned long long>(g_State.currentLobbyId));
        ImGui::Text("Host SteamID: %llu", static_cast<unsigned long long>(g_State.hostSteamId));
        ImGui::Text("Local SteamID: %llu", static_cast<unsigned long long>(g_State.localSteamId));
        ImGui::Text("Remote SteamID: %llu", static_cast<unsigned long long>(g_State.remoteSteamId));
        ImGui::Text("Members: %d / %d", g_State.lobbyMembers, g_State.lobbyLimit);
        ImGui::Text("P2P Packets: %d", g_State.p2pPackets);

        if (ImGui::Button("Dump Network Events")) DumpLines("network_events", g_State.networkEvents);
        ImGui::SameLine();
        if (ImGui::Button("Fake Network Event")) DevToolsManager::AddNetworkEvent("manual test network event");

        DrawListBox("Network Events", g_State.networkEvents);
    }

    void DrawContentTools()
    {
        DrawBool("Enable data\\no_release", g_State.contentNoRelease, "For debug/no_release experiments. Keep off unless testing.");
        DrawBool("Enable data\\tui", g_State.contentTui, "For TUI/debug UI experiments. Keep off unless testing.");
        DrawBool("Enable StormEvolution", g_State.contentStormEvolution);
        DrawBool("Log Redirected Files", g_State.logRedirectedFiles);
        DrawBool("Disable DLC Redirects", g_State.disableDlcRedirects);
        DrawBool("Safe Content Mode", g_State.safeContentMode, "Prefer requested-only redirects, never full recursive mounting.");
        DrawBool("Runtime Asset Hot Reload", g_State.enableAssetHotReload);

        ImGui::Separator();
        if (ImGui::Button("Reload Content Roots")) AddConsole("content roots reload requested");
        ImGui::SameLine();
        if (ImGui::Button("Dump Loaded Paths")) DumpLines("loaded_paths", g_State.loadedPaths);
        ImGui::SameLine();
        if (ImGui::Button("Fake Loaded Path")) DevToolsManager::AddLoadedPath("manual/test/path.xfbin");

        DrawListBox("Loaded / Redirected Paths", g_State.loadedPaths);
    }

    void DrawModTools()
    {
        DrawBool("Mod Conflict Detector", g_State.enableModConflicts);
        DrawBool("Mod Load Order Manager", g_State.enableModLoadOrder);
        DrawBool("Built-In Package Builder", g_State.enablePackageBuilder);
        ImGui::InputText("Package Name", g_State.packageName, sizeof(g_State.packageName));

        if (ImGui::Button("Scan Mod Conflicts")) AddConsole("mod conflict scan requested");
        ImGui::SameLine();
        if (ImGui::Button("Build .ns4mod Package")) AddConsole(std::string("package build requested: ") + g_State.packageName);
        ImGui::SameLine();
        if (ImGui::Button("Open Mods Folder")) ShellExecuteA(nullptr, "open", (GetGameFolder() / "NarutoStorm4Revived" / "mods").string().c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }

    void DrawMemoryTools()
    {
        DrawBool("Memory Explorer", g_State.enableMemoryExplorer);
        DrawBool("Object Inspector", g_State.enableObjectInspector);
        DrawBool("Runtime Offset Scanner", g_State.enableRuntimeOffsetScanner);
        ImGui::InputText("Address / Pattern", g_State.memoryExpression, sizeof(g_State.memoryExpression));
        if (ImGui::Button("Add Bookmark"))
        {
            PushLimited(g_State.bookmarks, g_State.memoryExpression, 128);
            AddConsole(std::string("memory bookmark added: ") + g_State.memoryExpression);
        }
        ImGui::SameLine();
        if (ImGui::Button("Scan Offsets")) AddConsole("runtime offset scan requested");
        DrawListBox("Memory Bookmarks", g_State.bookmarks, 180.0f);
    }

    void DrawMediaTools()
    {
        DrawBool("Screenshot Mode", g_State.enableScreenshotMode);
        DrawBool("Replay Tools", g_State.enableReplayTools);
        if (ImGui::Button("Hide HUD Toggle Request")) AddConsole("hide HUD toggle requested");
        ImGui::SameLine();
        if (ImGui::Button("Frame Advance Request")) AddConsole("frame advance requested");
        ImGui::SameLine();
        if (ImGui::Button("Slow Motion Request")) AddConsole("slow motion requested");
    }

    void ExecuteConsoleCommand(const std::string& command)
    {
        if (command.empty())
            return;

        AddConsole(std::string("> ") + command);

        if (command == "help")
        {
            AddConsole("commands: help, dump, clear, scene <name>, reload, paths, net, lobby");
        }
        else if (command == "dump")
        {
            DumpStateReport();
        }
        else if (command == "clear")
        {
            g_State.consoleLines.clear();
        }
        else if (command == "reload")
        {
            AddConsole("reload requested");
        }
        else if (command == "paths")
        {
            DumpLines("loaded_paths", g_State.loadedPaths);
        }
        else if (command == "net" || command == "lobby")
        {
            DumpLines("network_events", g_State.networkEvents);
        }
        else if (command.rfind("scene ", 0) == 0)
        {
            std::string scene = command.substr(6);
            DevToolsManager::SetCurrentScene(scene.c_str());
        }
        else
        {
            AddConsole("unknown command");
        }
    }

    void DrawConsoleTools()
    {
        DrawBool("Developer Console", g_State.enableDeveloperConsole);
        ImGui::InputText("Command", g_State.consoleInput, sizeof(g_State.consoleInput));
        ImGui::SameLine();
        if (ImGui::Button("Run"))
        {
            ExecuteConsoleCommand(g_State.consoleInput);
            g_State.consoleInput[0] = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("Help")) ExecuteConsoleCommand("help");
        DrawListBox("Console", g_State.consoleLines, 260.0f);
    }
}

namespace DevToolsManager
{
    bool Init()
    {
        if (g_State.initialized)
            return true;

        g_State.initialized = true;
        AddConsole("DevTools Manager initialized");
        AddConsole("Hotkeys: F2 DevTools, F3 reload roots, F4 dump state, F5 hot reload request");
        return true;
    }

    void Shutdown()
    {
        if (!g_State.initialized)
            return;
        AddConsole("DevTools Manager shutdown");
        g_State.initialized = false;
    }

    void TickHotkeys()
    {
        if (!g_State.initialized)
            return;

        if (HotkeyPressed(VK_F3)) AddConsole("F3 reload content roots requested");
        if (HotkeyPressed(VK_F4)) DumpStateReport();
        if (HotkeyPressed(VK_F5)) AddConsole("F5 runtime hot reload requested");
    }

    void DrawPage()
    {
        TickHotkeys();

        if (ImGui::BeginTabBar("##DevToolsTabs"))
        {
            if (ImGui::BeginTabItem("Overview")) { DrawOverview(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Scene")) { DrawSceneTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Network")) { DrawNetworkTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Content")) { DrawContentTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Mods")) { DrawModTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Memory")) { DrawMemoryTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Media")) { DrawMediaTools(); ImGui::EndTabItem(); }
            if (ImGui::BeginTabItem("Console")) { DrawConsoleTools(); ImGui::EndTabItem(); }
            ImGui::EndTabBar();
        }
    }

    void SetCurrentScene(const char* sceneName)
    {
        if (!sceneName || !*sceneName)
            return;
        if (strcmp(g_State.currentScene, sceneName) != 0)
        {
            strcpy_s(g_State.previousScene, g_State.currentScene);
            strcpy_s(g_State.currentScene, sceneName);
            AddSceneTransition(g_State.previousScene, g_State.currentScene);
        }
    }

    void SetNetworkState(const char* stateText)
    {
        if (stateText) strcpy_s(g_State.networkState, stateText);
    }

    void SetLobbyState(const char* stateText)
    {
        if (stateText) strcpy_s(g_State.lobbyState, stateText);
    }

    void AddSceneTransition(const char* fromScene, const char* toScene)
    {
        std::ostringstream ss;
        ss << NowText() << " " << (fromScene ? fromScene : "?") << " -> " << (toScene ? toScene : "?");
        PushLimited(g_State.sceneTransitions, ss.str());
    }

    void AddLoadedPath(const char* path)
    {
        if (path && *path)
            PushLimited(g_State.loadedPaths, std::string(NowText() + " " + path), 1000);
    }

    void AddNetworkEvent(const char* eventText)
    {
        if (eventText && *eventText)
            PushLimited(g_State.networkEvents, std::string(NowText() + " " + eventText), 1000);
    }
}
