#include "StdInc.h"
#include "WindowedFullscreen.h"
#include "Logger.h"
#include "HookManager.h"

namespace
{
    constexpr uintptr_t kCreateMainWindowRVA = 0x138EF0;
    constexpr uintptr_t kExclusiveFullscreenRVA = 0x1392A0;

    using CreateMainWindow_t = __int64(__fastcall*)(__int64 self, int width, int height, char fullscreen);
    using ExclusiveFullscreen_t = int(__fastcall*)(__int64 self, char enable);

    CreateMainWindow_t oCreateMainWindow = nullptr;
    ExclusiveFullscreen_t oExclusiveFullscreen = nullptr;

    uintptr_t g_CreateMainWindowAddr = 0;
    uintptr_t g_ExclusiveFullscreenAddr = 0;

    HWND g_GameWindow = nullptr;
    WNDPROC g_OriginalWndProc = nullptr;
    HANDLE g_LateThread = nullptr;
    bool g_Installed = false;

    RECT GetMonitorRect(HWND hwnd)
    {
        HMONITOR monitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);

        MONITORINFO info{};
        info.cbSize = sizeof(info);

        if (GetMonitorInfoW(monitor, &info))
            return info.rcMonitor;

        RECT fallback{};
        fallback.left = 0;
        fallback.top = 0;
        fallback.right = GetSystemMetrics(SM_CXSCREEN);
        fallback.bottom = GetSystemMetrics(SM_CYSCREEN);
        return fallback;
    }

    void ApplyBorderless(HWND hwnd)
    {
        if (!hwnd)
            return;

        RECT rect = GetMonitorRect(hwnd);

        SetWindowLongPtrW(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
        SetWindowLongPtrW(hwnd, GWL_EXSTYLE, 0);

        ShowWindow(hwnd, SW_RESTORE);

        SetWindowPos(
            hwnd,
            HWND_TOP,
            rect.left,
            rect.top,
            rect.right - rect.left,
            rect.bottom - rect.top,
            SWP_NOOWNERZORDER |
            SWP_FRAMECHANGED |
            SWP_SHOWWINDOW);

        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    }

    LRESULT CALLBACK hkWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_ACTIVATEAPP:
            return CallWindowProcW(g_OriginalWndProc, hwnd, msg, TRUE, lParam);

        case WM_ACTIVATE:
            if (LOWORD(wParam) == WA_INACTIVE)
                return CallWindowProcW(g_OriginalWndProc, hwnd, msg, MAKEWPARAM(WA_ACTIVE, HIWORD(wParam)), lParam);
            break;

        case WM_KILLFOCUS:
            return 0;

        case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_MINIMIZE)
                return 0;
            break;

        case WM_SIZE:
        case WM_MOVE:
        case WM_DISPLAYCHANGE:
            ApplyBorderless(hwnd);
            break;
        }

        return CallWindowProcW(g_OriginalWndProc, hwnd, msg, wParam, lParam);
    }

    void HookWndProc(HWND hwnd)
    {
        if (!hwnd || g_OriginalWndProc)
            return;

        g_OriginalWndProc = reinterpret_cast<WNDPROC>(
            SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc)));

        if (g_OriginalWndProc)
            Logger::Info("WindowedFullscreen: WndProc hooked");
        else
            Logger::Error("WindowedFullscreen: failed to hook WndProc");
    }

    __int64 __fastcall hkCreateMainWindow(__int64 self, int width, int height, char fullscreen)
    {
        Logger::Info("WindowedFullscreen: forcing native borderless create");

        __int64 result = oCreateMainWindow(self, width, height, 0);

        HWND hwnd = *reinterpret_cast<HWND*>(self + 32);
        *reinterpret_cast<int*>(self + 48) = 0;

        g_GameWindow = hwnd;

        ApplyBorderless(hwnd);
        HookWndProc(hwnd);

        Logger::Info("WindowedFullscreen: native borderless applied after CreateWindowExW");
        return result;
    }

    int __fastcall hkExclusiveFullscreen(__int64 self, char enable)
    {
        if (self)
        {
            *reinterpret_cast<int*>(self + 48) = 0;

            HWND hwnd = *reinterpret_cast<HWND*>(self + 32);
            if (hwnd)
            {
                g_GameWindow = hwnd;
                ApplyBorderless(hwnd);
                HookWndProc(hwnd);
            }
        }

        Logger::Info("WindowedFullscreen: blocked exclusive fullscreen request");
        return 0;
    }

    DWORD WINAPI LateApplyThread(LPVOID)
    {
        for (int i = 0; i < 120; ++i)
        {
            HWND hwnd = FindWindowW(L"MME_Sample", L"MME_Sample");

            if (hwnd)
            {
                g_GameWindow = hwnd;
                ApplyBorderless(hwnd);
                HookWndProc(hwnd);

                Logger::Info("WindowedFullscreen: late-applied to existing MME_Sample window");
                return 0;
            }

            Sleep(500);
        }

        Logger::Error("WindowedFullscreen: failed to find MME_Sample window");
        return 0;
    }
}

namespace WindowedFullscreen
{
    bool Init()
    {
        if (g_Installed)
            return true;

        HMODULE exe = GetModuleHandleW(nullptr);
        if (!exe)
        {
            Logger::Error("WindowedFullscreen: failed to get exe module");
            return false;
        }

        uintptr_t base = reinterpret_cast<uintptr_t>(exe);

        g_CreateMainWindowAddr = base + kCreateMainWindowRVA;
        g_ExclusiveFullscreenAddr = base + kExclusiveFullscreenRVA;

        if (!HookManager::Create(
            reinterpret_cast<void*>(g_CreateMainWindowAddr),
            reinterpret_cast<void*>(&hkCreateMainWindow),
            reinterpret_cast<void**>(&oCreateMainWindow)))
        {
            Logger::Error("WindowedFullscreen: failed to hook CreateMainWindow");
            return false;
        }

        if (!HookManager::Enable(reinterpret_cast<void*>(g_CreateMainWindowAddr)))
        {
            Logger::Error("WindowedFullscreen: failed to enable CreateMainWindow hook");
            return false;
        }

        if (!HookManager::Create(
            reinterpret_cast<void*>(g_ExclusiveFullscreenAddr),
            reinterpret_cast<void*>(&hkExclusiveFullscreen),
            reinterpret_cast<void**>(&oExclusiveFullscreen)))
        {
            Logger::Error("WindowedFullscreen: failed to hook ExclusiveFullscreen");
            return false;
        }

        if (!HookManager::Enable(reinterpret_cast<void*>(g_ExclusiveFullscreenAddr)))
        {
            Logger::Error("WindowedFullscreen: failed to enable ExclusiveFullscreen hook");
            return false;
        }

        g_LateThread = CreateThread(nullptr, 0, LateApplyThread, nullptr, 0, nullptr);
        if (g_LateThread)
        {
            CloseHandle(g_LateThread);
            g_LateThread = nullptr;
        }

        g_Installed = true;
        Logger::Info("WindowedFullscreen: native hooks installed");
        return true;
    }

    void Shutdown()
    {
        if (g_CreateMainWindowAddr)
            HookManager::Disable(reinterpret_cast<void*>(g_CreateMainWindowAddr));

        if (g_ExclusiveFullscreenAddr)
            HookManager::Disable(reinterpret_cast<void*>(g_ExclusiveFullscreenAddr));

        if (g_GameWindow && g_OriginalWndProc)
            SetWindowLongPtrW(g_GameWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_OriginalWndProc));

        g_OriginalWndProc = nullptr;
        g_GameWindow = nullptr;
        g_Installed = false;

        Logger::Info("WindowedFullscreen: shutdown");
    }
}
