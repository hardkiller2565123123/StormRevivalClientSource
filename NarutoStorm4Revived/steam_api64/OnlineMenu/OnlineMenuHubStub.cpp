#include "OnlineMenuHubStub.h"

#include <Windows.h>
#include <atomic>
#include <cstdint>
#include <cstdio>

#include "../MinHook.h"

namespace Evo
{
namespace OnlineMenuHubStub
{
    namespace
    {
        // IDA target:
        // sub_1406DF984 = ccSceneOnlineStoreNew factory.
        // This is called when the Online Battle Store button is selected.
        using OnlineStoreFactoryFn = std::int64_t(__fastcall*)(std::int64_t sceneParam);

        constexpr std::uintptr_t kImageBase = 0x140000000ull;
        constexpr std::uintptr_t kOnlineStoreFactoryVa = 0x1406DF984ull;

        OnlineStoreFactoryFn g_originalOnlineStoreFactory = nullptr;
        std::atomic<bool> g_installed{ false };
        std::atomic<bool> g_hubOpen{ false };
        int g_selectedButton = 0;
        HWND g_overlayWindow = nullptr;
        WNDPROC g_originalWndProc = nullptr;

        struct HubButton
        {
            const wchar_t* label;
            const char* debugAction;
        };

        constexpr HubButton kButtons[] =
        {
            { L"Server Status", "Server Status selected" },
            { L"Room Browser", "Room Browser selected" },
            { L"Leaderboard", "Leaderboard selected" },
            { L"News", "News selected" },
            { L"Settings", "Settings selected" },
            { L"Unlock All", "Unlock All selected" },
            { L"Close", "Close selected" }
        };

        constexpr int kButtonCount = static_cast<int>(sizeof(kButtons) / sizeof(kButtons[0]));

        std::uintptr_t Rebase(std::uintptr_t idaVa)
        {
            const auto module = reinterpret_cast<std::uintptr_t>(GetModuleHandleW(nullptr));
            return module + (idaVa - kImageBase);
        }

        void SafeLog(const char* msg)
        {
            if (!msg)
                return;

            OutputDebugStringA(msg);
            OutputDebugStringA("\n");
        }

        void ActivateSelectedButton()
        {
            if (g_selectedButton < 0 || g_selectedButton >= kButtonCount)
                return;

            SafeLog(kButtons[g_selectedButton].debugAction);

            if (g_selectedButton == kButtonCount - 1)
                g_hubOpen.store(false);
        }

        HWND FindGameWindow()
        {
            const DWORD pid = GetCurrentProcessId();
            struct EnumState
            {
                DWORD pid;
                HWND hwnd;
            } state{ pid, nullptr };

            EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL
            {
                auto* state = reinterpret_cast<EnumState*>(lParam);
                DWORD windowPid = 0;
                GetWindowThreadProcessId(hwnd, &windowPid);
                if (windowPid != state->pid)
                    return TRUE;

                if (!IsWindowVisible(hwnd))
                    return TRUE;

                wchar_t title[256]{};
                GetWindowTextW(hwnd, title, 256);
                if (title[0] == L'\0')
                    return TRUE;

                state->hwnd = hwnd;
                return FALSE;
            }, reinterpret_cast<LPARAM>(&state));

            return state.hwnd;
        }

        LRESULT CALLBACK HubWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
        {
            if (g_hubOpen.load())
            {
                if (msg == WM_KEYDOWN)
                {
                    if (wParam == VK_ESCAPE || wParam == VK_BACK || wParam == 'B')
                    {
                        g_hubOpen.store(false);
                        InvalidateRect(hwnd, nullptr, TRUE);
                        return 0;
                    }

                    if (wParam == VK_UP || wParam == 'W')
                    {
                        g_selectedButton = (g_selectedButton + kButtonCount - 1) % kButtonCount;
                        InvalidateRect(hwnd, nullptr, TRUE);
                        return 0;
                    }

                    if (wParam == VK_DOWN || wParam == 'S')
                    {
                        g_selectedButton = (g_selectedButton + 1) % kButtonCount;
                        InvalidateRect(hwnd, nullptr, TRUE);
                        return 0;
                    }

                    if (wParam == VK_RETURN || wParam == VK_SPACE || wParam == 'A')
                    {
                        ActivateSelectedButton();
                        InvalidateRect(hwnd, nullptr, TRUE);
                        return 0;
                    }
                }

                if (msg == WM_PAINT)
                {
                    PAINTSTRUCT ps{};
                    HDC hdc = BeginPaint(hwnd, &ps);
                    RECT rc{};
                    GetClientRect(hwnd, &rc);

                    HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
                    FillRect(hdc, &rc, black);
                    DeleteObject(black);

                    SetBkMode(hdc, TRANSPARENT);
                    SetTextColor(hdc, RGB(235, 235, 235));

                    HFONT titleFont = CreateFontW(34, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Segoe UI");
                    HFONT bodyFont = CreateFontW(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        CLEARTYPE_QUALITY, DEFAULT_PITCH, L"Segoe UI");

                    HFONT old = static_cast<HFONT>(SelectObject(hdc, titleFont));
                    RECT title{ 60, 55, rc.right - 60, 110 };
                    DrawTextW(hdc, L"Storm Revival Hub", -1, &title, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

                    SelectObject(hdc, bodyFont);

                    RECT status{ 80, 120, rc.right - 80, 156 };
                    DrawTextW(hdc, L"Players Online: 0  |  Server: Offline LAN  |  Build: research mode", -1, &status, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

                    int y = 175;
                    for (int i = 0; i < kButtonCount; ++i)
                    {
                        RECT row{ 80, y, rc.right - 80, y + 44 };

                        HBRUSH fill = CreateSolidBrush(i == g_selectedButton ? RGB(60, 85, 130) : RGB(28, 28, 28));
                        FillRect(hdc, &row, fill);
                        DeleteObject(fill);

                        HPEN border = CreatePen(PS_SOLID, 1, i == g_selectedButton ? RGB(130, 170, 235) : RGB(70, 70, 70));
                        HGDIOBJ oldPen = SelectObject(hdc, border);
                        HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));
                        Rectangle(hdc, row.left, row.top, row.right, row.bottom);
                        SelectObject(hdc, oldBrush);
                        SelectObject(hdc, oldPen);
                        DeleteObject(border);

                        RECT textRow{ row.left + 18, row.top, row.right - 18, row.bottom };
                        DrawTextW(hdc, kButtons[i].label, -1, &textRow, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
                        y += 52;
                    }

                    RECT help{ 80, rc.bottom - 58, rc.right - 80, rc.bottom - 24 };
                    DrawTextW(hdc, L"Up/Down to choose, A/Enter to select, B/Back/Esc to close", -1, &help, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

                    SelectObject(hdc, old);
                    DeleteObject(titleFont);
                    DeleteObject(bodyFont);
                    EndPaint(hwnd, &ps);
                    return 0;
                }
            }

            return CallWindowProcW(g_originalWndProc, hwnd, msg, wParam, lParam);
        }

        void EnsureWndProcHook()
        {
            if (g_overlayWindow && g_originalWndProc)
                return;

            HWND hwnd = FindGameWindow();
            if (!hwnd)
                return;

            g_overlayWindow = hwnd;
            g_originalWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HubWndProc)));
            if (g_originalWndProc)
                SafeLog("Storm Revival Hub window procedure hook installed");
        }

        void OpenHub()
        {
            EnsureWndProcHook();
            g_selectedButton = 0;
            g_hubOpen.store(true);
            if (g_overlayWindow)
            {
                SetForegroundWindow(g_overlayWindow);
                InvalidateRect(g_overlayWindow, nullptr, TRUE);
                UpdateWindow(g_overlayWindow);
            }
            SafeLog("Storm Revival Hub opened from Store button; original Steam Store blocked");
        }

        std::int64_t __fastcall HookOnlineStoreFactory(std::int64_t sceneParam)
        {
            // Block the real Steam Store scene and open our black-screen native stub instead.
            OpenHub();

            // Important: returning 0 prevents ccSceneOnlineStoreNew from being created.
            // If this causes a softlock on a specific build, change this to:
            // return g_originalOnlineStoreFactory ? g_originalOnlineStoreFactory(sceneParam) : 0;
            return 0;
        }
    }

    bool IsOpen()
    {
        return g_hubOpen.load();
    }


    void OpenFromStore()
    {
        OpenHub();
    }

    void Close()
    {
        g_hubOpen.store(false);
        if (g_overlayWindow)
            InvalidateRect(g_overlayWindow, nullptr, TRUE);
    }

    void Install()
    {
        if (g_installed.exchange(true))
            return;

        const auto target = reinterpret_cast<void*>(Rebase(kOnlineStoreFactoryVa));
        if (MH_CreateHook(target, &HookOnlineStoreFactory, reinterpret_cast<void**>(&g_originalOnlineStoreFactory)) != MH_OK)
        {
            SafeLog("Storm Revival Hub Store hook failed: MH_CreateHook");
            return;
        }

        if (MH_EnableHook(target) != MH_OK)
        {
            SafeLog("Storm Revival Hub Store hook failed: MH_EnableHook");
            return;
        }

        SafeLog("Storm Revival Hub Store hook installed at sub_1406DF984");
    }

    void Uninstall()
    {
        if (!g_installed.exchange(false))
            return;

        const auto target = reinterpret_cast<void*>(Rebase(kOnlineStoreFactoryVa));
        MH_DisableHook(target);

        if (g_overlayWindow && g_originalWndProc)
        {
            SetWindowLongPtrW(g_overlayWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_originalWndProc));
            g_overlayWindow = nullptr;
            g_originalWndProc = nullptr;
        }
    }
}
}
