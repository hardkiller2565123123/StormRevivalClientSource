#include "StdInc.h"
#include "InputFocusGuard.h"
#include "HookManager.h"
#include "Logger.h"

#include <Xinput.h>

namespace
{
    using XInputGetStateFn = DWORD(WINAPI*)(DWORD, XINPUT_STATE*);

    XInputGetStateFn g_OriginalXInputGetState = nullptr;
    void* g_HookedTarget = nullptr;
    HWND g_GameWindow = nullptr;
    HANDLE g_Thread = nullptr;
    std::atomic<bool> g_Stop{ false };
    std::atomic<bool> g_LoggedBlocked{ false };

    std::string ToLowerString(std::string text)
    {
        for (char& c : text)
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        return text;
    }

    std::string GetCurrentProcessName()
    {
        char exePath[MAX_PATH]{};
        GetModuleFileNameA(nullptr, exePath, MAX_PATH);

        std::string path = exePath;
        const size_t slash = path.find_last_of("\\/");
        if (slash != std::string::npos)
            path = path.substr(slash + 1);

        return ToLowerString(path);
    }

    bool IsStorm4GameProcess()
    {
        const std::string exe = GetCurrentProcessName();
        return exe == "nsuns4.exe" ||
            exe.find("nsuns4") != std::string::npos ||
            (exe.find("naruto") != std::string::npos && exe.find("storm") != std::string::npos);
    }

    BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM)
    {
        DWORD windowProcessId = 0;
        GetWindowThreadProcessId(hwnd, &windowProcessId);

        if (windowProcessId != GetCurrentProcessId() || !IsWindowVisible(hwnd))
            return TRUE;

        char title[256]{};
        GetWindowTextA(hwnd, title, sizeof(title));
        if (title[0] == '\0' ||
            strstr(title, "Debug Console") ||
            strstr(title, "Naruto Revival Offline Debug Console") ||
            strstr(title, "PowerShell") ||
            strstr(title, "Command Prompt"))
        {
            return TRUE;
        }

        g_GameWindow = hwnd;
        return FALSE;
    }

    HWND FindGameWindow()
    {
        if (g_GameWindow && IsWindow(g_GameWindow))
            return g_GameWindow;

        g_GameWindow = nullptr;
        EnumWindows(EnumWindowsCallback, 0);
        return g_GameWindow;
    }

    bool GameHasForeground()
    {
        HWND game = FindGameWindow();
        if (!game)
            return true;

        HWND foreground = GetForegroundWindow();
        return foreground == game || IsChild(game, foreground);
    }

    DWORD WINAPI XInputGetStateHook(DWORD userIndex, XINPUT_STATE* state)
    {
        if (!GameHasForeground())
        {
            if (state)
                std::memset(state, 0, sizeof(*state));

            if (!g_LoggedBlocked.exchange(true))
                Logger::Info("InputFocusGuard blocking controller input for background instance");

            return ERROR_DEVICE_NOT_CONNECTED;
        }

        g_LoggedBlocked = false;
        return g_OriginalXInputGetState ? g_OriginalXInputGetState(userIndex, state) : ERROR_DEVICE_NOT_CONNECTED;
    }

    FARPROC FindXInputGetState()
    {
        const char* names[] = { "xinput1_4.dll", "xinput1_3.dll", "xinput9_1_0.dll", "xinput1_2.dll", "xinput1_1.dll" };
        for (const char* name : names)
        {
            HMODULE module = GetModuleHandleA(name);
            if (!module)
                module = LoadLibraryA(name);
            if (!module)
                continue;
            FARPROC proc = GetProcAddress(module, "XInputGetState");
            if (proc)
                return proc;
        }
        return nullptr;
    }

    DWORD WINAPI HookThread(LPVOID)
    {
        for (int i = 0; i < 120 && !g_Stop; ++i)
        {
            FARPROC proc = FindXInputGetState();
            if (proc)
            {
                g_HookedTarget = reinterpret_cast<void*>(proc);
                if (HookManager::Create(g_HookedTarget, reinterpret_cast<void*>(&XInputGetStateHook), reinterpret_cast<void**>(&g_OriginalXInputGetState)) &&
                    HookManager::Enable(g_HookedTarget))
                {
                    Logger::Info("InputFocusGuard hooked XInputGetState");
                    return 0;
                }
            }
            Sleep(500);
        }
        Logger::Error("InputFocusGuard could not hook XInputGetState");
        return 0;
    }
}

namespace InputFocusGuard
{
    bool Init()
    {
        if (!IsStorm4GameProcess())
        {
            Logger::Info("InputFocusGuard skipped because this process is not NSUNS4");
            return true;
        }

        g_Stop = false;
        g_Thread = CreateThread(nullptr, 0, HookThread, nullptr, 0, nullptr);
        return g_Thread != nullptr;
    }

    void Shutdown()
    {
        g_Stop = true;
        if (g_HookedTarget)
            HookManager::Disable(g_HookedTarget);
        if (g_Thread)
        {
            CloseHandle(g_Thread);
            g_Thread = nullptr;
        }
        g_HookedTarget = nullptr;
        g_OriginalXInputGetState = nullptr;
    }
}
