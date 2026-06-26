#include "DX11OverlayInternal.h"
#include "RuntimeDeveloperTools.h"
#include "OverlayConsole.h"
#include "AssetBrowser.h"
#include "AssetNotification.h"
#include "AssetPreloadManager.h"
#include "ModRedirector.h"
#include "PatchManager.h"
#include "RuntimeAssetTelemetry.h"
#include "Logger.h"

#include <mutex>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <deque>
#include <filesystem>

namespace
{
    RuntimeDeveloperTools::ToolState g_State;
    std::mutex g_Mutex;
    std::deque<std::string> g_Transitions;
    std::deque<std::string> g_PacketEvents;
    std::deque<std::string> g_LoadedFiles;

    char g_CommandInput[256]{};
    char g_SceneInput[128] = "ccSceneNetwork";
    char g_MemoryAddressInput[64]{};
    char g_MemorySearchInput[64]{};
    bool g_Initialized = false;

    std::string GameDir()
    {
        char path[MAX_PATH]{};
        GetModuleFileNameA(nullptr, path, MAX_PATH);
        std::filesystem::path p(path);
        return p.parent_path().string();
    }

    std::string NowStamp()
    {
        SYSTEMTIME st{};
        GetLocalTime(&st);
        char buffer[64]{};
        sprintf_s(buffer, "%04u-%02u-%02u_%02u-%02u-%02u",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        return buffer;
    }

    std::filesystem::path FrameworkLogDir()
    {
        std::filesystem::path dir = std::filesystem::path(GameDir()) / "NarutoStorm4Revived" / "FrameworkReports";
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }

    void PushLimited(std::deque<std::string>& q, const std::string& line, size_t limit)
    {
        q.push_back(line);
        while (q.size() > limit)
            q.pop_front();
    }

    bool SafeReadMemory(uintptr_t address, void* out, size_t size)
    {
        if (!address || !out || !size)
            return false;

        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(reinterpret_cast<void*>(address), &mbi, sizeof(mbi)))
            return false;

        if (mbi.State != MEM_COMMIT)
            return false;

        const DWORD protect = mbi.Protect & 0xff;
        if (protect == PAGE_NOACCESS || protect == PAGE_EXECUTE)
            return false;

        const uintptr_t regionStart = reinterpret_cast<uintptr_t>(mbi.BaseAddress);
        const uintptr_t regionEnd = regionStart + mbi.RegionSize;
        if (address + size > regionEnd)
            return false;

        __try
        {
            memcpy(out, reinterpret_cast<const void*>(address), size);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    std::string HexDump(uintptr_t address, size_t size)
    {
        std::vector<unsigned char> bytes(size);
        if (!SafeReadMemory(address, bytes.data(), bytes.size()))
            return "Unreadable memory";

        std::ostringstream out;
        out << std::hex << std::setfill('0');
        for (size_t i = 0; i < bytes.size(); ++i)
        {
            if (i % 16 == 0)
                out << "\n" << std::setw(16) << (address + i) << ": ";
            out << std::setw(2) << static_cast<int>(bytes[i]) << " ";
        }
        return out.str();
    }

    uintptr_t ParseAddress(const char* text)
    {
        if (!text || !*text)
            return 0;

        std::string s = text;
        int base = 16;
        if (s.rfind("0x", 0) == 0 || s.rfind("0X", 0) == 0)
            s = s.substr(2);

        return static_cast<uintptr_t>(_strtoui64(s.c_str(), nullptr, base));
    }

    void DrawHeaderBadge(const char* text, const ImVec4& color)
    {
        ImGui::SameLine();
        ImGui::TextColored(color, "%s", text);
    }

    void DrawSceneViewer()
    {
        ImGui::Text("Live Scene Viewer");
        DrawHeaderBadge(g_State.EnableSceneViewer ? "[ON]" : "[OFF]", g_State.EnableSceneViewer ? ImVec4(0.35f, 1.0f, 0.35f, 1.0f) : ImVec4(1, .4f, .3f, 1));
        ImGui::Separator();

        ImGui::Checkbox("Enable scene viewer", &g_State.EnableSceneViewer);
        ImGui::Checkbox("Scene transition logger", &g_State.EnableTransitionLogger);
        ImGui::Checkbox("Safe mode, no direct scene jumps", &g_State.SafeMode);

        ImGui::Text("Current scene: %s", g_State.CurrentScene.c_str());
        ImGui::Text("Previous scene: %s", g_State.PreviousScene.c_str());
        ImGui::Text("Network scene: %s", g_State.NetworkScene.c_str());

        ImGui::InputText("Scene name", g_SceneInput, sizeof(g_SceneInput));
        if (ImGui::Button("Request Scene Load", ImVec2(160, 24)))
            RuntimeDeveloperTools::RequestSceneLoad(g_SceneInput);
        ImGui::SameLine();
        if (ImGui::Button("Force Debug Menu Request", ImVec2(190, 24)))
            RuntimeDeveloperTools::RequestDebugMenuEnable();

        ImGui::TextDisabled("Scene loading is logged/requested unless you later wire exact NS4 scene offsets.");

        auto transitions = RuntimeDeveloperTools::GetTransitions();
        ImGui::BeginChild("##SceneTransitions", ImVec2(0, 180), true);
        for (const auto& line : transitions)
            ImGui::TextUnformatted(line.c_str());
        ImGui::EndChild();
    }

    void DrawNetworkViewer()
    {
        ImGui::Text("Network State Viewer / Lobby Inspector");
        ImGui::Separator();

        ImGui::Checkbox("Enable network viewer", &g_State.EnableNetworkViewer);
        ImGui::Checkbox("Enable lobby inspector", &g_State.EnableLobbyInspector);
        ImGui::Checkbox("Enable packet logger", &g_State.EnablePacketLogger);

        ImGui::Columns(2, "##NetCols", false);
        ImGui::Text("Lobby ID"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.LobbyId.c_str()); ImGui::NextColumn();
        ImGui::Text("Lobby State"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.LobbyState.c_str()); ImGui::NextColumn();
        ImGui::Text("Members"); ImGui::NextColumn(); ImGui::Text("%d / %d", g_State.LobbyMembers, g_State.LobbyLimit); ImGui::NextColumn();
        ImGui::Text("Search Results"); ImGui::NextColumn(); ImGui::Text("%d", g_State.SearchResults); ImGui::NextColumn();
        ImGui::Text("P2P Sessions"); ImGui::NextColumn(); ImGui::Text("%d", g_State.P2PSessions); ImGui::NextColumn();
        ImGui::Text("Host SteamID"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.HostSteamId.c_str()); ImGui::NextColumn();
        ImGui::Text("Local SteamID"); ImGui::NextColumn(); ImGui::TextUnformatted(g_State.LocalSteamId.c_str()); ImGui::NextColumn();
        ImGui::Columns(1);

        if (ImGui::Button("Dump Network Report", ImVec2(170, 24)))
            RuntimeDeveloperTools::DumpRuntimeReport();
        ImGui::SameLine();
        if (ImGui::Button("Clear Packet Events", ImVec2(170, 24)))
        {
            std::lock_guard<std::mutex> lock(g_Mutex);
            g_PacketEvents.clear();
        }

        auto packets = RuntimeDeveloperTools::GetPacketEvents();
        ImGui::BeginChild("##PacketEvents", ImVec2(0, 180), true);
        for (const auto& line : packets)
            ImGui::TextUnformatted(line.c_str());
        ImGui::EndChild();
    }

    void DrawContentControls()
    {
        ImGui::Text("Debug / TUI / Content Controls");
        ImGui::Separator();

        ImGui::Checkbox("Enable Debug/TUI loader", &g_State.DebugTuiLoader);
        ImGui::Checkbox("Enable data\\no_release", &g_State.NoReleaseRoot);
        ImGui::Checkbox("Enable data\\tui", &g_State.TuiRoot);
        ImGui::Checkbox("Enable StormEvolution", &g_State.StormEvolution);
        ImGui::Checkbox("Log redirected files", &g_State.LogRedirectedFiles);
        ImGui::Checkbox("Disable DLC redirects", &g_State.DisableDlcRedirects);

        if (ImGui::Button("Reload Content Roots", ImVec2(180, 24)))
            RuntimeDeveloperTools::ReloadContentRoots();
        ImGui::SameLine();
        if (ImGui::Button("Dump Loaded Paths", ImVec2(170, 24)))
            RuntimeDeveloperTools::DumpLoadedFilePaths();
        ImGui::SameLine();
        if (ImGui::Button("Hot Reload Assets", ImVec2(170, 24)))
            RuntimeDeveloperTools::RequestHotReload();

        ImGui::Text("Last redirected file:");
        ImGui::TextWrapped("%s", g_State.LastRedirectedFile.empty() ? "none" : g_State.LastRedirectedFile.c_str());
        ImGui::Text("Last loaded asset:");
        ImGui::TextWrapped("%s", g_State.LastLoadedAsset.empty() ? "none" : g_State.LastLoadedAsset.c_str());

        auto files = RuntimeDeveloperTools::GetLoadedFiles();
        ImGui::BeginChild("##LoadedFiles", ImVec2(0, 190), true);
        for (const auto& line : files)
            ImGui::TextUnformatted(line.c_str());
        ImGui::EndChild();
    }

    void DrawMemoryExplorer()
    {
        ImGui::Text("Memory Explorer");
        ImGui::Separator();
        ImGui::Checkbox("Enable memory explorer", &g_State.EnableMemoryExplorer);
        ImGui::TextDisabled("Safe reader uses VirtualQuery and guarded memcpy. Write support is intentionally off.");

        ImGui::InputText("Address hex", g_MemoryAddressInput, sizeof(g_MemoryAddressInput));
        uintptr_t address = ParseAddress(g_MemoryAddressInput);
        if (address)
        {
            std::string dump = HexDump(address, 128);
            ImGui::BeginChild("##MemoryDump", ImVec2(0, 170), true);
            ImGui::TextUnformatted(dump.c_str());
            ImGui::EndChild();
        }

        HMODULE mainModule = GetModuleHandleA(nullptr);
        ImGui::Text("Main module base: 0x%p", mainModule);
        ImGui::InputText("String search note", g_MemorySearchInput, sizeof(g_MemorySearchInput));
        ImGui::TextDisabled("Full string scanner can be wired later once offsets/ranges are confirmed.");
    }

    void DrawConsoleTools()
    {
        ImGui::Text("Developer Console");
        ImGui::Separator();
        ImGui::Checkbox("Enable developer console", &g_State.EnableDeveloperConsole);

        if (ImGui::InputText("Command", g_CommandInput, sizeof(g_CommandInput), ImGuiInputTextFlags_EnterReturnsTrue))
        {
            auto result = OverlayConsole::Execute(g_CommandInput);
            g_State.LastCommandResult = result.Message;
            g_CommandInput[0] = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("Run", ImVec2(70, 24)))
        {
            auto result = OverlayConsole::Execute(g_CommandInput);
            g_State.LastCommandResult = result.Message;
            g_CommandInput[0] = 0;
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear", ImVec2(70, 24)))
            OverlayConsole::Clear();

        const auto& lines = OverlayConsole::GetLines();
        ImGui::BeginChild("##DevConsoleLines", ImVec2(0, 240), true);
        for (const auto& line : lines)
            ImGui::TextUnformatted(line.c_str());
        ImGui::EndChild();
    }

    void DrawReplayScreenshotTools()
    {
        ImGui::Text("Screenshot / Replay Tools");
        ImGui::Separator();
        ImGui::Checkbox("Enable screenshot tools", &g_State.EnableScreenshotTools);
        ImGui::Checkbox("Enable replay tools", &g_State.EnableReplayTools);

        static bool hideHud = false;
        static bool pauseAnimations = false;
        static bool slowMotion = false;
        static float slowMotionScale = 0.50f;
        static bool freeCameraRequest = false;

        ImGui::Checkbox("Hide HUD request", &hideHud);
        ImGui::Checkbox("Pause animations request", &pauseAnimations);
        ImGui::Checkbox("Free camera request", &freeCameraRequest);
        ImGui::Checkbox("Slow motion request", &slowMotion);
        ImGui::SliderFloat("Slow motion scale", &slowMotionScale, 0.05f, 1.0f, "%.2f");
        ImGui::TextDisabled("These are request flags until exact NS4 render/time offsets are wired.");
    }

    void DrawRuntimeTelemetry()
    {
        RuntimeAssetTelemetry::DrawDebugPanel();
    }
}

namespace RuntimeDeveloperTools
{
    bool Init()
    {
        if (g_Initialized)
            return true;

        Logger::Info("RuntimeDeveloperTools initialized");
        OverlayConsole::AddLine("RuntimeDeveloperTools loaded. Commands: dev_dump, scene_dump, content_reload, hotreload, dump_loaded_paths.");
        g_Initialized = true;
        return true;
    }

    void Shutdown()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Transitions.clear();
        g_PacketEvents.clear();
        g_LoadedFiles.clear();
        g_Initialized = false;
    }

    ToolState& State()
    {
        return g_State;
    }

    void TickHotkeys()
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.WantTextInput)
            return;

        if (ImGui::IsKeyPressed(ImGuiKey_F2, false))
        {
            RequestDebugMenuEnable();
            AssetNotification::PushInfo("Debug tools", "F2 debug menu request logged");
        }
        if (ImGui::IsKeyPressed(ImGuiKey_F3, false))
        {
            ReloadContentRoots();
            AssetNotification::PushInfo("Content", "F3 content roots reloaded");
        }
        if (ImGui::IsKeyPressed(ImGuiKey_F4, false))
        {
            DumpLoadedFilePaths();
            AssetNotification::PushInfo("Runtime", "F4 loaded paths dumped");
        }
        if (ImGui::IsKeyPressed(ImGuiKey_F5, false))
        {
            RequestHotReload();
            AssetNotification::PushInfo("Hot reload", "F5 hot reload requested");
        }
    }

    void DrawPage()
    {
        TickHotkeys();

        static int devPage = 0;
        ImGui::BeginChild("##DevToolsNav", ImVec2(210.0f, 0.0f), true);
        const char* pages[] = {
            "Scene Viewer", "Network / Lobby", "Content Controls", "Memory Explorer",
            "Console", "Telemetry", "Screenshot / Replay"
        };
        for (int i = 0; i < IM_ARRAYSIZE(pages); ++i)
        {
            if (devPage == i)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.18f, 0.42f, 0.72f, 1.0f));
            if (ImGui::Button(pages[i], ImVec2(-1.0f, 25.0f)))
                devPage = i;
            if (devPage == i)
                ImGui::PopStyleColor();
        }
        ImGui::Separator();
        ImGui::TextWrapped("Hotkeys: F2 Debug, F3 Roots, F4 Dump, F5 Hot Reload");
        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("##DevToolsPage", ImVec2(0, 0), true);
        switch (devPage)
        {
        case 0: DrawSceneViewer(); break;
        case 1: DrawNetworkViewer(); break;
        case 2: DrawContentControls(); break;
        case 3: DrawMemoryExplorer(); break;
        case 4: DrawConsoleTools(); break;
        case 5: DrawRuntimeTelemetry(); break;
        case 6: DrawReplayScreenshotTools(); break;
        default: DrawSceneViewer(); break;
        }
        ImGui::EndChild();
    }

    void SetCurrentScene(const std::string& scene)
    {
        if (scene.empty() || scene == g_State.CurrentScene)
            return;

        std::string previous = g_State.CurrentScene;
        g_State.PreviousScene = previous;
        g_State.CurrentScene = scene;
        AddTransition(previous, scene);
    }

    void SetNetworkState(const std::string& scene, const std::string& lobbyState)
    {
        g_State.NetworkScene = scene;
        g_State.LobbyState = lobbyState;
    }

    void SetLobbyInfo(const std::string& lobbyId, const std::string& host, const std::string& local, int members, int limit)
    {
        g_State.LobbyId = lobbyId;
        g_State.HostSteamId = host;
        g_State.LocalSteamId = local;
        g_State.LobbyMembers = members;
        g_State.LobbyLimit = limit;
    }

    void SetLastRedirectedFile(const std::string& path)
    {
        g_State.LastRedirectedFile = path;
        std::lock_guard<std::mutex> lock(g_Mutex);
        PushLimited(g_LoadedFiles, "redirected: " + path, 300);
    }

    void SetLastLoadedAsset(const std::string& path)
    {
        g_State.LastLoadedAsset = path;
        std::lock_guard<std::mutex> lock(g_Mutex);
        PushLimited(g_LoadedFiles, "loaded: " + path, 300);
    }

    void AddTransition(const std::string& from, const std::string& to)
    {
        if (!g_State.EnableTransitionLogger)
            return;
        std::lock_guard<std::mutex> lock(g_Mutex);
        PushLimited(g_Transitions, from + " -> " + to, 200);
        Logger::Info("SceneTransition: " + from + " -> " + to);
    }

    void AddPacketEvent(const std::string& eventText)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        PushLimited(g_PacketEvents, eventText, 300);
        if (g_State.EnablePacketLogger)
            Logger::Info("PacketEvent: " + eventText);
    }

    void ReloadContentRoots()
    {
        AssetBrowser::StartAsyncScan(false);
        ModRedirector::Scan();
        g_State.LastCommandResult = "Content roots reload requested.";
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info("RuntimeDeveloperTools requested content root reload");
    }

    void DumpRuntimeReport()
    {
        auto path = FrameworkLogDir() / ("runtime_report_" + NowStamp() + ".txt");
        std::ofstream out(path);
        out << "NS4FrameWork Runtime Report\n";
        out << "GameDir=" << GameDir() << "\n";
        out << "Scene=" << g_State.CurrentScene << "\n";
        out << "PreviousScene=" << g_State.PreviousScene << "\n";
        out << "NetworkScene=" << g_State.NetworkScene << "\n";
        out << "LobbyState=" << g_State.LobbyState << "\n";
        out << "LobbyID=" << g_State.LobbyId << "\n";
        out << "Members=" << g_State.LobbyMembers << "/" << g_State.LobbyLimit << "\n";
        out << "LastRedirectedFile=" << g_State.LastRedirectedFile << "\n";
        out << "LastLoadedAsset=" << g_State.LastLoadedAsset << "\n\n";

        out << "Transitions\n";
        for (const auto& s : GetTransitions()) out << s << "\n";
        out << "\nPacket Events\n";
        for (const auto& s : GetPacketEvents()) out << s << "\n";
        out << "\nLoaded Files\n";
        for (const auto& s : GetLoadedFiles()) out << s << "\n";

        g_State.LastCommandResult = "Runtime report written: " + path.string();
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info(g_State.LastCommandResult);
    }

    void DumpLoadedFilePaths()
    {
        auto path = FrameworkLogDir() / ("loaded_paths_" + NowStamp() + ".txt");
        std::ofstream out(path);
        for (const auto& s : GetLoadedFiles())
            out << s << "\n";
        g_State.LastCommandResult = "Loaded paths written: " + path.string();
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info(g_State.LastCommandResult);
    }

    void RequestHotReload()
    {
        AssetBrowser::StartAsyncScan(false);
        AssetPreloadManager::StartFullPreload(false);
        g_State.LastCommandResult = "Hot reload requested: asset scan + preload queued.";
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info(g_State.LastCommandResult);
    }

    void RequestDebugMenuEnable()
    {
        g_State.LastCommandResult = "Debug menu enable requested. Waiting for exact ccDebugMenu offsets/hook binding.";
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info(g_State.LastCommandResult);
        AddTransition(g_State.CurrentScene, "DebugMenu(requested)");
    }

    void RequestSceneLoad(const std::string& sceneName)
    {
        if (sceneName.empty())
            return;
        g_State.LastCommandResult = "Scene load requested: " + sceneName;
        OverlayConsole::AddLine(g_State.LastCommandResult);
        Logger::Info(g_State.LastCommandResult);
        AddTransition(g_State.CurrentScene, sceneName + "(requested)");
    }

    std::vector<std::string> GetTransitions()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return std::vector<std::string>(g_Transitions.begin(), g_Transitions.end());
    }

    std::vector<std::string> GetPacketEvents()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return std::vector<std::string>(g_PacketEvents.begin(), g_PacketEvents.end());
    }

    std::vector<std::string> GetLoadedFiles()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return std::vector<std::string>(g_LoadedFiles.begin(), g_LoadedFiles.end());
    }
}
