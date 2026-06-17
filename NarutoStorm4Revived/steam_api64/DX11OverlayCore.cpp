#include "DX11OverlayInternal.h"
#include "DX11Overlay.h"
#include "FrameworkAddon.h"
#include "StormAPIBridge.h"
#include "Logger.h"
#include "MinHook.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

#include <urlmon.h>
#include <wincodec.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "windowscodecs.lib")

namespace
{
    constexpr double kTargetFrameSeconds = 1.0 / 60.0;
    constexpr wchar_t kStormApiAvatarUrl[] = L"https://avatars.githubusercontent.com/u/92672927?v=4";

    LARGE_INTEGER g_FramePaceFrequency{};
    LARGE_INTEGER g_LastPacedPresent{};
    bool g_FramePacerReady = false;
    bool g_TimerResolutionRaised = false;

    ID3D11ShaderResourceView* g_StormApiAvatarView = nullptr;
    bool g_StormApiAvatarLoadTried = false;

    void RaiseTimerResolutionForPacing()
    {
        if (g_TimerResolutionRaised)
            return;

        HMODULE winmm = LoadLibraryA("winmm.dll");
        if (!winmm)
            return;

        using TimeBeginPeriodFn = UINT(WINAPI*)(UINT);
        TimeBeginPeriodFn timeBeginPeriodFn =
            reinterpret_cast<TimeBeginPeriodFn>(GetProcAddress(winmm, "timeBeginPeriod"));

        if (timeBeginPeriodFn && timeBeginPeriodFn(1) == 0)
            g_TimerResolutionRaised = true;
    }

    void ResetFramePacer()
    {
        g_LastPacedPresent.QuadPart = 0;
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

        if (g_LastPacedPresent.QuadPart == 0)
        {
            g_LastPacedPresent = now;
            return;
        }

        const LONGLONG targetTicks =
            static_cast<LONGLONG>(static_cast<double>(g_FramePaceFrequency.QuadPart) * kTargetFrameSeconds);

        const LONGLONG targetPresent = g_LastPacedPresent.QuadPart + targetTicks;

        while (now.QuadPart < targetPresent)
        {
            const double remainingMs =
                static_cast<double>(targetPresent - now.QuadPart) * 1000.0 /
                static_cast<double>(g_FramePaceFrequency.QuadPart);

            if (remainingMs > 2.0)
                Sleep(1);
            else if (remainingMs > 0.25)
                Sleep(0);
            else
                YieldProcessor();

            QueryPerformanceCounter(&now);
        }

        if (now.QuadPart > targetPresent + (targetTicks * 4))
            g_LastPacedPresent = now;
        else
            g_LastPacedPresent.QuadPart = targetPresent;
    }

    UINT EffectivePresentSyncInterval(UINT requestedSyncInterval)
    {
        if (g_GraphicsVsync)
            return requestedSyncInterval > 0 ? requestedSyncInterval : 1;

        return 0;
    }

    std::wstring GetExeFolderW()
    {
        wchar_t exePath[MAX_PATH]{};
        GetModuleFileNameW(nullptr, exePath, MAX_PATH);

        wchar_t* slash = wcsrchr(exePath, L'\\');
        if (slash)
            *slash = L'\0';

        return exePath;
    }

    bool EnsureDirectoryW(const std::wstring& path)
    {
        DWORD attrs = GetFileAttributesW(path.c_str());
        if (attrs != INVALID_FILE_ATTRIBUTES)
            return (attrs & FILE_ATTRIBUTE_DIRECTORY) != 0;

        return CreateDirectoryW(path.c_str(), nullptr) != FALSE ||
               GetLastError() == ERROR_ALREADY_EXISTS;
    }

    bool FileExistsW(const std::wstring& path)
    {
        DWORD attrs = GetFileAttributesW(path.c_str());
        return attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    std::wstring GetStormApiAvatarPath()
    {
        const std::wstring base = GetExeFolderW();
        const std::wstring revivedDir = base + L"\\NarutoStorm4Revived";
        const std::wstring cacheDir = revivedDir + L"\\Cache";

        EnsureDirectoryW(revivedDir);
        EnsureDirectoryW(cacheDir);

        return cacheDir + L"\\stormapi_theleonx_avatar.png";
    }

    bool DownloadStormApiAvatar(const std::wstring& path)
    {
        if (FileExistsW(path))
            return true;

        HRESULT hr = URLDownloadToFileW(
            nullptr,
            kStormApiAvatarUrl,
            path.c_str(),
            0,
            nullptr);

        return SUCCEEDED(hr) && FileExistsW(path);
    }

    bool LoadTextureFromPngWIC(const std::wstring& path, ID3D11ShaderResourceView** outSrv)
    {
        if (!g_Device || !outSrv)
            return false;

        *outSrv = nullptr;

        HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        if (FAILED(coInit) && coInit != RPC_E_CHANGED_MODE)
            return false;

        IWICImagingFactory* factory = nullptr;
        IWICBitmapDecoder* decoder = nullptr;
        IWICBitmapFrameDecode* frame = nullptr;
        IWICFormatConverter* converter = nullptr;

        HRESULT hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&factory));

        if (SUCCEEDED(hr))
        {
            hr = factory->CreateDecoderFromFilename(
                path.c_str(),
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnLoad,
                &decoder);
        }

        if (SUCCEEDED(hr))
            hr = decoder->GetFrame(0, &frame);

        if (SUCCEEDED(hr))
            hr = factory->CreateFormatConverter(&converter);

        if (SUCCEEDED(hr))
        {
            hr = converter->Initialize(
                frame,
                GUID_WICPixelFormat32bppRGBA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0,
                WICBitmapPaletteTypeCustom);
        }

        UINT width = 0;
        UINT height = 0;

        if (SUCCEEDED(hr))
            hr = converter->GetSize(&width, &height);

        std::vector<unsigned char> pixels;

        if (SUCCEEDED(hr) && width > 0 && height > 0)
        {
            pixels.resize(static_cast<size_t>(width) * static_cast<size_t>(height) * 4);
            hr = converter->CopyPixels(
                nullptr,
                width * 4,
                static_cast<UINT>(pixels.size()),
                pixels.data());
        }

        if (SUCCEEDED(hr))
        {
            D3D11_TEXTURE2D_DESC desc{};
            desc.Width = width;
            desc.Height = height;
            desc.MipLevels = 1;
            desc.ArraySize = 1;
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.SampleDesc.Count = 1;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

            D3D11_SUBRESOURCE_DATA data{};
            data.pSysMem = pixels.data();
            data.SysMemPitch = width * 4;

            ID3D11Texture2D* texture = nullptr;
            hr = g_Device->CreateTexture2D(&desc, &data, &texture);

            if (SUCCEEDED(hr) && texture)
            {
                hr = g_Device->CreateShaderResourceView(texture, nullptr, outSrv);
                texture->Release();
            }
        }

        if (converter) converter->Release();
        if (frame) frame->Release();
        if (decoder) decoder->Release();
        if (factory) factory->Release();

        return SUCCEEDED(hr) && *outSrv;
    }

    void EnsureStormApiAvatarLoaded()
    {
        if (g_StormApiAvatarLoadTried || g_StormApiAvatarView || !g_Device)
            return;

        g_StormApiAvatarLoadTried = true;

        const std::wstring avatarPath = GetStormApiAvatarPath();

        if (!DownloadStormApiAvatar(avatarPath))
        {
            Logger::Error("StormAPI avatar download failed");
            return;
        }

        if (LoadTextureFromPngWIC(avatarPath, &g_StormApiAvatarView))
            Logger::Info("StormAPI avatar loaded from GitHub/cache");
        else
            Logger::Error("StormAPI avatar texture load failed");
    }
}

void CleanupRenderTarget()
{
    SAFE_RELEASE(g_RenderTargetView);
}

bool CreateRenderTarget(IDXGISwapChain* swapChain)
{
    if (g_RenderTargetView)
        return true;

    if (!swapChain || !g_Device)
        return false;

    ID3D11Texture2D* backBuffer = nullptr;

    HRESULT hr = swapChain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backBuffer));

    if (FAILED(hr) || !backBuffer)
    {
        Logger::Error("DX11 overlay: failed to get backbuffer");
        return false;
    }

    hr = g_Device->CreateRenderTargetView(backBuffer, nullptr, &g_RenderTargetView);
    backBuffer->Release();

    if (FAILED(hr) || !g_RenderTargetView)
    {
        Logger::Error("DX11 overlay: failed to create render target view");
        return false;
    }

    Logger::Info("DX11 overlay: render target created");
    return true;
}

LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (g_MenuOpen && g_ImGuiReady)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDrawCursor = g_DrawMouseCursor;

        if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
            return TRUE;

        if (g_BlockGameInputWhenOpen)
        {
            switch (msg)
            {
            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_CHAR:
                return TRUE;
            }
        }
    }

    if (g_OriginalWndProc)
        return CallWindowProcA(g_OriginalWndProc, hwnd, msg, wParam, lParam);

    return DefWindowProcA(hwnd, msg, wParam, lParam);
}

bool HookGameWindow()
{
    if (!g_GameWindow || g_OriginalWndProc)
        return true;

    g_OriginalWndProc = reinterpret_cast<WNDPROC>(
        SetWindowLongPtrA(
            g_GameWindow,
            GWLP_WNDPROC,
            reinterpret_cast<LONG_PTR>(OverlayWndProc)));

    if (!g_OriginalWndProc)
    {
        Logger::Error("DX11 overlay: failed to hook game window proc");
        return false;
    }

    Logger::Info("DX11 overlay: game window proc hooked");
    return true;
}

void ApplyStyle()
{
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 0.0f;
    style.WindowPadding = ImVec2(9.0f, 8.0f);
    style.FramePadding = ImVec2(8.0f, 4.0f);
    style.ItemSpacing = ImVec2(8.0f, 6.0f);

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.025f, 0.030f, 0.038f, 0.94f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.015f, 0.018f, 0.024f, 0.62f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.020f, 0.024f, 0.032f, 0.98f);
    colors[ImGuiCol_Button] = ImVec4(0.10f, 0.28f, 0.50f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.16f, 0.40f, 0.70f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.48f, 0.84f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.32f, 0.62f, 1.00f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.12f, 0.32f, 0.56f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.18f, 0.44f, 0.74f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.22f, 0.50f, 0.86f, 1.00f);
}

bool InitImGui(IDXGISwapChain* swapChain)
{
    if (g_ImGuiReady)
        return true;

    if (!swapChain)
        return false;

    HRESULT hr = swapChain->GetDevice(
        __uuidof(ID3D11Device),
        reinterpret_cast<void**>(&g_Device));

    if (FAILED(hr) || !g_Device)
    {
        Logger::Error("DX11 overlay: failed to get D3D11 device");
        return false;
    }

    g_Device->GetImmediateContext(&g_Context);

    if (!g_Context)
    {
        Logger::Error("DX11 overlay: failed to get D3D11 context");
        SAFE_RELEASE(g_Device);
        return false;
    }

    DXGI_SWAP_CHAIN_DESC desc{};
    hr = swapChain->GetDesc(&desc);

    if (FAILED(hr) || !desc.OutputWindow)
    {
        Logger::Error("DX11 overlay: failed to get game window from swapchain");
        SAFE_RELEASE(g_Context);
        SAFE_RELEASE(g_Device);
        return false;
    }

    g_GameWindow = desc.OutputWindow;

    if (!CreateRenderTarget(swapChain))
    {
        SAFE_RELEASE(g_Context);
        SAFE_RELEASE(g_Device);
        return false;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.MouseDrawCursor = true;

    ApplyStyle();

    ImGui_ImplWin32_Init(g_GameWindow);
    ImGui_ImplDX11_Init(g_Device, g_Context);

    HookGameWindow();

    g_ImGuiReady = true;

    Logger::Info("DX11 overlay: ImGui initialized in-game");
    return true;
}

void ShutdownImGui()
{
    FrameworkAddon::Shutdown();

    if (g_ImGuiReady)
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        g_ImGuiReady = false;
    }

    if (g_GameWindow && g_OriginalWndProc)
    {
        SetWindowLongPtrA(g_GameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_OriginalWndProc));
        g_OriginalWndProc = nullptr;
    }

    CleanupRenderTarget();
    SAFE_RELEASE(g_StormApiAvatarView);
    g_StormApiAvatarLoadTried = false;

    SAFE_RELEASE(g_Context);
    SAFE_RELEASE(g_Device);
}

void DrawAlwaysStatusBar()
{
    if (!g_OverlayEnabled || !g_ShowStatusBar)
        return;

    ImGui::SetNextWindowPos(ImVec2(6.0f, 5.0f), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.42f);

    ImGui::Begin(
        "##NS4StatusOnly",
        nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav);

    std::string text;

    if (g_StatusShowName)
        text += "NS4 Revived";

    if (g_StatusShowBuild)
    {
        if (!text.empty()) text += " | ";
        text += "Build ";
        text += __DATE__;
        text += " ";
        text += __TIME__;
    }

    if (g_StatusShowFps)
    {
        if (!text.empty()) text += " | ";
        text += "FPS ";
        text += std::to_string(g_CurrentFps);
    }

    if (g_StatusShowHotkey)
    {
        if (!text.empty()) text += " | ";
        text += "F1";
    }

    ImGui::TextUnformatted(text.c_str());
    ImGui::End();
}


void DrawStormAPINotification()
{
    if (!g_OverlayEnabled || !g_ImGuiReady)
        return;

    EnsureStormApiAvatarLoaded();

    static double firstSeen = -1.0;
    if (firstSeen < 0.0)
        firstSeen = ImGui::GetTime();

    const double elapsed = ImGui::GetTime() - firstSeen;
    if (elapsed > 5.25)
        return;

    const float inT = static_cast<float>(std::min(1.0, elapsed / 0.34));
    const float outT = elapsed < 4.05 ? 0.0f : static_cast<float>(std::min(1.0, (elapsed - 4.05) / 0.62));

    const float easeIn = 1.0f - std::pow(1.0f - inT, 3.0f);
    const float easeOut = outT * outT * (3.0f - 2.0f * outT);
    const float alpha = std::max(0.0f, 1.0f - easeOut);
    const float pulse = 0.5f + 0.5f * std::sin(static_cast<float>(elapsed * 9.5));

    const float width = 430.0f;
    const float height = 106.0f;
    const float x = -width + 14.0f + (width + 28.0f) * easeIn - 36.0f * easeOut;
    const float y = 58.0f;

    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 20.0f);

    ImGui::Begin("##StormApiTheLeonXToast", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoNav |
        ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImDrawList* draw = ImGui::GetWindowDrawList();
    const ImVec2 a = ImGui::GetWindowPos();
    const ImVec2 s = ImGui::GetWindowSize();
    const ImVec2 b(a.x + s.x, a.y + s.y);

    auto col = [&](int r, int g, int bl, float mul)
        {
            return IM_COL32(r, g, bl, static_cast<int>(255.0f * alpha * mul));
        };

    draw->AddRectFilled(ImVec2(a.x + 7, a.y + 8), ImVec2(b.x + 7, b.y + 8), col(0, 0, 0, 0.42f), 22.0f);

    draw->AddRectFilledMultiColor(
        a,
        b,
        col(22, 72, 255, 0.96f),
        col(145, 54, 255, 0.95f),
        col(8, 15, 36, 0.98f),
        col(13, 30, 60, 0.98f));

    draw->AddRect(a, b, col(120, 235, 255, 0.95f), 20.0f, 0, 1.7f + pulse * 1.3f);
    draw->AddRectFilled(ImVec2(a.x, a.y), ImVec2(a.x + 7.0f + pulse * 6.0f, b.y), col(75, 235, 255, 1.0f), 20.0f);

    const ImVec2 orb(a.x + 54.0f, a.y + 53.0f);
    const float glowRadius = 34.0f + pulse * 4.0f;
    const float avatarRadius = 27.0f;

    draw->AddCircleFilled(orb, glowRadius, col(90, 220, 255, 0.16f), 64);
    draw->AddCircleFilled(orb, avatarRadius + 3.0f, col(10, 15, 32, 0.92f), 64);

    if (g_StormApiAvatarView)
    {
        const ImVec2 imgMin(orb.x - avatarRadius, orb.y - avatarRadius);
        const ImVec2 imgMax(orb.x + avatarRadius, orb.y + avatarRadius);

        draw->AddImageRounded(
            reinterpret_cast<ImTextureID>(g_StormApiAvatarView),
            imgMin,
            imgMax,
            ImVec2(0, 0),
            ImVec2(1, 1),
            col(255, 255, 255, 1.0f),
            avatarRadius);
    }
    else
    {
        draw->AddCircleFilled(orb, avatarRadius, col(35, 80, 190, 0.95f), 64);
        draw->AddText(ImVec2(orb.x - 7.0f, orb.y - 12.0f), col(255, 255, 255, 1.0f), "S");
    }

    draw->AddCircle(orb, avatarRadius + 2.0f + pulse * 1.5f, col(190, 248, 255, 1.0f), 64, 2.5f);

    draw->AddText(ImVec2(a.x + 98.0f, a.y + 16.0f), col(255, 255, 255, 1.0f), "Ultimate Storm API");
    draw->AddText(ImVec2(a.x + 98.0f, a.y + 42.0f), col(224, 240, 255, 0.98f), "Created by TheLeonX");
    draw->AddText(ImVec2(a.x + 98.0f, a.y + 66.0f), col(165, 225, 255, 0.95f), "Integrated with NarutoStorm4Revived");

    ImGui::End();
    ImGui::PopStyleVar(2);
}

void DrawImGui(IDXGISwapChain* swapChain)
{
    if (!InitImGui(swapChain))
        return;

    if (!CreateRenderTarget(swapChain))
        return;

    UpdateFps();
    UpdateHotkeys();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DrawAlwaysStatusBar();
    DrawStormAPINotification();
    DrawAnimatedTopMenu();

    ImGui::Render();

    g_Context->OMSetRenderTargets(1, &g_RenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

HRESULT __stdcall PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    g_PresentSeen = true;
    const bool loginGateActive = false;

    if (g_OverlayEnabled)
        DrawImGui(swapChain);

    if (loginGateActive)
        Sleep(33);

    PaceFrameForLowLatency60();

    return g_OriginalPresent(swapChain, loginGateActive ? 1 : EffectivePresentSyncInterval(syncInterval), flags);
}

HRESULT __stdcall ResizeBuffersHook(
    IDXGISwapChain* swapChain,
    UINT bufferCount,
    UINT width,
    UINT height,
    DXGI_FORMAT newFormat,
    UINT swapChainFlags)
{
    CleanupRenderTarget();

    return g_OriginalResizeBuffers(
        swapChain,
        bufferCount,
        width,
        height,
        newFormat,
        swapChainFlags);
}

HWND CreateDummyWindow()
{
    WNDCLASSEXA wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.lpszClassName = "NS4RevivedDummyDX11Window";

    RegisterClassExA(&wc);

    return CreateWindowA(
        wc.lpszClassName,
        "NS4RevivedDummyDX11Window",
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

bool CreateDummySwapChain(IDXGISwapChain** outSwapChain)
{
    *outSwapChain = nullptr;

    HWND hwnd = CreateDummyWindow();

    if (!hwnd)
        return false;

    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 100;
    sd.BufferDesc.Height = 100;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    D3D_FEATURE_LEVEL featureLevel{};
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        outSwapChain,
        &device,
        &featureLevel,
        &context);

    SAFE_RELEASE(context);
    SAFE_RELEASE(device);

    DestroyWindow(hwnd);
    UnregisterClassA("NS4RevivedDummyDX11Window", GetModuleHandleA(nullptr));

    return SUCCEEDED(hr) && *outSwapChain;
}

