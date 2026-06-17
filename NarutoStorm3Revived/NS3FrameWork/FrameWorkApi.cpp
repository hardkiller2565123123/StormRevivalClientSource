#include "DX11OverlayInternal.h"

namespace
{
    bool g_Initialized = false;

    void EnsureInitialized()
    {
        if (g_Initialized)
            return;

        Logger::Init();
        Logger::Info("NS3FrameWork.dll add-on initialized");

        NS2Config::Init();
        ModRedirector::Init();
        LuaManager::Init();
        LuaHooks::Init();
        OverlayConsole::Init();
        PatchManager::Init();

        NS2Offsets::LogAll();
        ModRedirector::Scan();

        AssetBrowser::Init();
        AssetRelations::Init();
        AssetNotification::Init();
        AssetOverrideManager::Init();
        AssetHexEditor::Init();
        AssetPackageCreator::Init();
        AssetFavorites::Init();
        AssetDuplicateFinder::Init();
        AssetConflictScanner::Init();
        AssetBackupManager::Init();
        AssetBulkExtractor::Init();
        RuntimeHookBootstrap::Init();
        AssetPreloadManager::Init();
        AssetTaskQueue::Init();

        Logger::Info("NS3FrameWork.dll asset tools initialized");
        g_Initialized = true;
    }
}

void CleanupRenderTarget()
{
    Logger::Info("NS3FrameWork.dll render-target reset requested; client owns the active swapchain.");
}

extern "C" __declspec(dllexport) int __cdecl Framework_GetApiVersion()
{
    return 1;
}

extern "C" __declspec(dllexport) const char* __cdecl Framework_GetDisplayName()
{
    return "NS3 Revived FrameWork";
}

extern "C" __declspec(dllexport) void __cdecl Framework_BindImGuiContext(ImGuiContext* context)
{
    if (context)
        ImGui::SetCurrentContext(context);
}

extern "C" __declspec(dllexport) void __cdecl Framework_BindClientRenderState(
    ID3D11Device* device,
    ID3D11DeviceContext* context,
    HWND gameWindow,
    int currentFps)
{
    g_Device = device;
    g_Context = context;
    g_GameWindow = gameWindow;
    g_CurrentFps = currentFps;
}

namespace
{
    enum FrameworkTab
    {
        FW_GRAPHICS,
        FW_CONTROLS,
        FW_CAMERA,
        FW_ASSETS,
        FW_MODS,
        FW_PATCHES
    };

    int g_FrameworkTab = FW_GRAPHICS;

    void DrawFrameworkTab(const char* label, int tab)
    {
        const bool selected = g_FrameworkTab == tab;
        if (selected)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.38f, 0.68f, 1.00f));

        if (ImGui::Button(label, ImVec2(86.0f, 22.0f)))
        {
            g_FrameworkTab = tab;
            g_SelectedSubPage = 0;
        }

        if (selected)
            ImGui::PopStyleColor();
    }

    void DrawFrameworkLeftNav()
    {
        switch (g_FrameworkTab)
        {
        case FW_GRAPHICS:
            DrawLeftButton("Display", 0);
            DrawLeftButton("Anti-Aliasing", 1);
            DrawLeftButton("Quality", 2);
            DrawLeftButton("Overlay", 3);
            DrawLeftButton("Advanced", 4);
            break;
        case FW_CONTROLS:
            DrawLeftButton("General", 0);
            DrawLeftButton("Mouse", 1);
            DrawLeftButton("Binds", 2);
            DrawLeftButton("Advanced", 3);
            break;
        case FW_CAMERA:
            DrawLeftButton("Free Camera", 0);
            DrawLeftButton("Coordinates", 1);
            DrawLeftButton("Viewer Tools", 2);
            break;
        case FW_ASSETS:
            DrawLeftButton("Browser", 0);
            DrawLeftButton("Stages", 1);
            DrawLeftButton("Characters", 2);
            DrawLeftButton("Models", 3);
            DrawLeftButton("Textures", 4);
            DrawLeftButton("Audio", 5);
            DrawLeftButton("Packages", 6);
            DrawLeftButton("Mod Overrides", 7);
            DrawLeftButton("Lua Scripts", 8);
            DrawLeftButton("Lua Autorun", 9);
            DrawLeftButton("Lua Overrides", 10);
            DrawLeftButton("Lua Console", 11);
            DrawLeftButton("Lua Functions", 12);
            DrawLeftButton("Tools", 13);
            break;
        case FW_MODS:
            DrawLeftButton("Loader", 0);
            DrawLeftButton("Folders", 1);
            break;
        case FW_PATCHES:
            DrawLeftButton("Display", 0);
            DrawLeftButton("Gameplay", 1);
            DrawLeftButton("Safety", 2);
            DrawLeftButton("Status", 3);
            break;
        }
    }

    void DrawFrameworkPage()
    {
        switch (g_FrameworkTab)
        {
        case FW_GRAPHICS: DrawGraphicsPage(); break;
        case FW_CONTROLS: DrawControlsPage(); break;
        case FW_CAMERA: DrawCameraPage(); break;
        case FW_ASSETS: DrawAssetsPage(); break;
        case FW_MODS: DrawModsPage(); break;
        case FW_PATCHES: DrawPatchesPage(); break;
        }
    }

    void SelectFrameworkTabFromClient(int clientTab)
    {
        switch (clientTab)
        {
        case TAB_GRAPHICS: g_FrameworkTab = FW_GRAPHICS; break;
        case TAB_CONTROLS: g_FrameworkTab = FW_CONTROLS; break;
        case TAB_CAMERA: g_FrameworkTab = FW_CAMERA; break;
        case TAB_ASSETS: g_FrameworkTab = FW_ASSETS; break;
        case TAB_MODS: g_FrameworkTab = FW_MODS; break;
        case TAB_PATCHES: g_FrameworkTab = FW_PATCHES; break;
        default: break;
        }
    }

    void DrawSelectedFrameworkTab()
    {
        const float leftWidth = ImGui::GetContentRegionAvail().x < 900.0f ? 185.0f : 220.0f;
        ImGui::BeginChild("##FrameworkLeftNav", ImVec2(leftWidth, 0.0f), true);
        DrawFrameworkLeftNav();
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("##FrameworkPage", ImVec2(0.0f, 0.0f), true);
        DrawFrameworkPage();
        ImGui::EndChild();

        AssetNotification::DrawToasts();
    }
}

extern "C" __declspec(dllexport) void __cdecl Framework_OnClientGui()
{
    EnsureInitialized();

    ImGui::Text("NS3FrameWork.dll Options");
    ImGui::Separator();

    DrawFrameworkTab("Graphics", FW_GRAPHICS); ImGui::SameLine();
    DrawFrameworkTab("Controls", FW_CONTROLS); ImGui::SameLine();
    DrawFrameworkTab("Camera", FW_CAMERA); ImGui::SameLine();
    DrawFrameworkTab("Assets", FW_ASSETS); ImGui::SameLine();
    DrawFrameworkTab("Mods", FW_MODS); ImGui::SameLine();
    DrawFrameworkTab("Patches", FW_PATCHES);

    ImGui::Separator();

    DrawSelectedFrameworkTab();
}

extern "C" __declspec(dllexport) void __cdecl Framework_OnClientTab(int clientTab)
{
    EnsureInitialized();
    SelectFrameworkTabFromClient(clientTab);
    DrawSelectedFrameworkTab();
}

extern "C" __declspec(dllexport) void __cdecl Framework_OnClientShutdown()
{
    if (!g_Initialized)
        return;

    RuntimeHookBootstrap::Shutdown();
    AssetBulkExtractor::Shutdown();
    AssetBackupManager::Shutdown();
    AssetConflictScanner::Shutdown();
    AssetDuplicateFinder::Shutdown();
    AssetFavorites::Shutdown();
    AssetPackageCreator::Shutdown();
    AssetHexEditor::Shutdown();
    AssetOverrideManager::Shutdown();
    AssetNotification::Shutdown();
    AssetTaskQueue::Shutdown();
    AssetPreloadManager::Shutdown();
    AssetModelViewer::Shutdown();
    AssetTexturePreview::Shutdown();
    AssetRelations::Shutdown();
    ModRedirector::Shutdown();
    PatchManager::Shutdown();
    OverlayConsole::Shutdown();
    LuaHooks::Shutdown();
    LuaManager::Shutdown();

    Logger::Info("NS3FrameWork.dll add-on shutdown");
    g_Initialized = false;
}
