#include "DX11OverlayInternal.h"
#include "DX9Overlay.h"
#include "FrameworkAddon.h"
#include "MinHook.h"
#include "imgui_impl_dx9.h"

#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

namespace
{
    using EndSceneFn = HRESULT(__stdcall*)(IDirect3DDevice9*);
    using ResetFn = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);

    EndSceneFn g_OriginalEndScene = nullptr;
    ResetFn g_OriginalReset = nullptr;
    IDirect3DDevice9* g_Dx9Device = nullptr;
    void* g_EndSceneTarget = nullptr;
    void* g_ResetTarget = nullptr;
    bool g_Dx9HookReady = false;
    constexpr double kTargetFrameSeconds = 1.0 / 60.0;
    LARGE_INTEGER g_FramePaceFrequency{};
    LARGE_INTEGER g_LastPacedFrame{};
    bool g_FramePacerReady = false;
    bool g_TimerResolutionRaised = false;

    void RaiseTimerResolutionForPacing()
    {
        if (g_TimerResolutionRaised)
            return;

        HMODULE winmm = LoadLibraryA("winmm.dll");
        if (!winmm)
            return;

        using TimeBeginPeriodFn = UINT(WINAPI*)(UINT);
        TimeBeginPeriodFn timeBeginPeriodFn = reinterpret_cast<TimeBeginPeriodFn>(GetProcAddress(winmm, "timeBeginPeriod"));
        if (timeBeginPeriodFn && timeBeginPeriodFn(1) == 0)
            g_TimerResolutionRaised = true;
    }

    void ResetFramePacer()
    {
        g_LastPacedFrame.QuadPart = 0;
    }

    void PaceFrameForLowLatency60()
    {
        if (g_GraphicsVsync || !g_GraphicsWindowedFullscreen)
        {
            ResetFramePacer();
            return;
        }

        RaiseTimerResolutionForPacing();

        if (!g_FramePacerReady)
        {
            QueryPerformanceFrequency(&g_FramePaceFrequency);
            g_FramePacerReady = g_FramePaceFrequency.QuadPart > 0;
        }

        if (!g_FramePacerReady)
            return;

        LARGE_INTEGER now{};
        QueryPerformanceCounter(&now);

        if (g_LastPacedFrame.QuadPart == 0)
        {
            g_LastPacedFrame = now;
            return;
        }

        const LONGLONG targetTicks = static_cast<LONGLONG>(static_cast<double>(g_FramePaceFrequency.QuadPart) * kTargetFrameSeconds);
        const LONGLONG targetFrame = g_LastPacedFrame.QuadPart + targetTicks;

        while (now.QuadPart < targetFrame)
        {
            const double remainingMs = static_cast<double>(targetFrame - now.QuadPart) * 1000.0 / static_cast<double>(g_FramePaceFrequency.QuadPart);

            if (remainingMs > 2.0)
                Sleep(1);
            else if (remainingMs > 0.25)
                Sleep(0);
            else
                YieldProcessor();

            QueryPerformanceCounter(&now);
        }

        if (now.QuadPart > targetFrame + (targetTicks * 4))
            g_LastPacedFrame = now;
        else
            g_LastPacedFrame.QuadPart = targetFrame;
    }

    HWND CreateDummyDx9Window()
    {
        WNDCLASSEXA wc{};
        wc.cbSize = sizeof(wc);
        wc.lpfnWndProc = DefWindowProcA;
        wc.hInstance = GetModuleHandleA(nullptr);
        wc.lpszClassName = "NarutoRevivalDummyDX9Window";
        RegisterClassExA(&wc);

        return CreateWindowExA(
            0,
            wc.lpszClassName,
            "NarutoRevivalDummyDX9Window",
            WS_OVERLAPPEDWINDOW,
            0,
            0,
            100,
            100,
            nullptr,
            nullptr,
            wc.hInstance,
            nullptr);
    }

    bool CreateDummyDx9Device(IDirect3DDevice9** outDevice)
    {
        if (!outDevice)
            return false;

        *outDevice = nullptr;

        HWND dummyWindow = CreateDummyDx9Window();
        if (!dummyWindow)
            return false;

        IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
        if (!d3d)
        {
            DestroyWindow(dummyWindow);
            return false;
        }

        D3DPRESENT_PARAMETERS params{};
        params.Windowed = TRUE;
        params.SwapEffect = D3DSWAPEFFECT_DISCARD;
        params.hDeviceWindow = dummyWindow;
        params.BackBufferFormat = D3DFMT_UNKNOWN;

        HRESULT hr = d3d->CreateDevice(
            D3DADAPTER_DEFAULT,
            D3DDEVTYPE_HAL,
            dummyWindow,
            D3DCREATE_SOFTWARE_VERTEXPROCESSING,
            &params,
            outDevice);

        d3d->Release();
        DestroyWindow(dummyWindow);

        return SUCCEEDED(hr) && *outDevice;
    }

    bool HookGameWindowDx9(IDirect3DDevice9* device)
    {
        if (g_GameWindow && g_OriginalWndProc)
            return true;

        D3DDEVICE_CREATION_PARAMETERS creation{};
        if (FAILED(device->GetCreationParameters(&creation)) || !creation.hFocusWindow)
            return false;

        g_GameWindow = creation.hFocusWindow;
        g_OriginalWndProc = reinterpret_cast<WNDPROC>(
            SetWindowLongPtrA(g_GameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(OverlayWndProc)));

        return g_OriginalWndProc != nullptr;
    }

    bool InitImGuiDx9(IDirect3DDevice9* device)
    {
        if (g_ImGuiReady)
            return true;

        if (!device || !HookGameWindowDx9(device))
            return false;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
        io.MouseDrawCursor = true;

        ApplyStyle();

        ImGui_ImplWin32_Init(g_GameWindow);
        ImGui_ImplDX9_Init(device);

        g_ImGuiReady = true;
        Logger::Info("DX9 overlay: ImGui initialized in-game");
        return true;
    }

    void DrawImGuiDx9(IDirect3DDevice9* device)
    {
        if (!InitImGuiDx9(device))
            return;

        UpdateFps();
        UpdateHotkeys();

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        DrawAlwaysStatusBar();
        DrawAnimatedTopMenu();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

    HRESULT __stdcall EndSceneHook(IDirect3DDevice9* device)
    {
        g_Dx9Device = device;

        if (g_OverlayEnabled)
            DrawImGuiDx9(device);

        PaceFrameForLowLatency60();

        return g_OriginalEndScene(device);
    }

    HRESULT __stdcall ResetHook(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params)
    {
        if (g_ImGuiReady)
            ImGui_ImplDX9_InvalidateDeviceObjects();

        const HRESULT result = g_OriginalReset(device, params);

        if (SUCCEEDED(result) && g_ImGuiReady)
            ImGui_ImplDX9_CreateDeviceObjects();

        return result;
    }
}

namespace DX9Overlay
{
    bool Init()
    {
        if (g_Dx9HookReady)
            return true;

        IDirect3DDevice9* dummyDevice = nullptr;
        if (!CreateDummyDx9Device(&dummyDevice))
        {
            Logger::Error("DX9 overlay: failed to create dummy device");
            return false;
        }

        void** vtable = *reinterpret_cast<void***>(dummyDevice);
        g_ResetTarget = vtable[16];
        g_EndSceneTarget = vtable[42];
        dummyDevice->Release();

        if (MH_CreateHook(g_EndSceneTarget, reinterpret_cast<void*>(EndSceneHook), reinterpret_cast<void**>(&g_OriginalEndScene)) != MH_OK ||
            MH_EnableHook(g_EndSceneTarget) != MH_OK)
        {
            Logger::Error("DX9 overlay: failed to hook EndScene");
            return false;
        }

        if (MH_CreateHook(g_ResetTarget, reinterpret_cast<void*>(ResetHook), reinterpret_cast<void**>(&g_OriginalReset)) != MH_OK ||
            MH_EnableHook(g_ResetTarget) != MH_OK)
        {
            Logger::Error("DX9 overlay: failed to hook Reset");
            MH_DisableHook(g_EndSceneTarget);
            return false;
        }

        g_Dx9HookReady = true;
        Logger::Info("DX9 overlay initialized");
        return true;
    }

    void Shutdown()
    {
        FrameworkAddon::Shutdown();

        if (g_ImGuiReady)
        {
            ImGui_ImplDX9_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();
            g_ImGuiReady = false;
        }

        if (g_GameWindow && g_OriginalWndProc)
        {
            SetWindowLongPtrA(g_GameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_OriginalWndProc));
            g_OriginalWndProc = nullptr;
        }

        if (g_EndSceneTarget)
            MH_DisableHook(g_EndSceneTarget);

        if (g_ResetTarget)
            MH_DisableHook(g_ResetTarget);

        g_Dx9Device = nullptr;
        g_EndSceneTarget = nullptr;
        g_ResetTarget = nullptr;
        g_Dx9HookReady = false;
        Logger::Info("DX9 overlay shutdown");
    }
}
