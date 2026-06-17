#include "CrashFix.h"
#include <cstdio>
#include <cstdarg>
#include <atomic>
#include <string>

// IMPORTANT:
// Rename this declaration if your original startup function has a different name.
// Put your old DllMain/CreateThread startup body into this function.
extern void NSCRevived_FrameworkMain(HMODULE module);

namespace
{
    std::atomic<bool> g_started{ false };
    std::atomic<bool> g_stopping{ false };
    HMODULE g_module = nullptr;

    std::wstring GetGameDir()
    {
        wchar_t path[MAX_PATH]{};
        GetModuleFileNameW(nullptr, path, MAX_PATH);
        std::wstring s(path);
        const size_t slash = s.find_last_of(L"\\/");
        if (slash != std::wstring::npos)
            s.resize(slash + 1);
        return s;
    }

    DWORD WINAPI FrameworkThread(LPVOID param) noexcept
    {
        HMODULE module = static_cast<HMODULE>(param);

        __try
        {
            NSCRevived::CrashFix::Log("Framework thread started");

            if (NSCRevived::CrashFix::HooksDisabledByFlag())
            {
                NSCRevived::CrashFix::Log("Safe mode active: NSCRevived_DisableHooks.flag found, skipping hook startup");
                return 0;
            }

            // Give the game a moment to finish its own Steam/DX startup.
            // This avoids a lot of loader-lock / early swap-chain crashes.
            Sleep(1500);

            NSCRevived_FrameworkMain(module);
            NSCRevived::CrashFix::Log("Framework startup finished");
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            NSCRevived::CrashFix::Log("CRASH BLOCKED in framework thread. ExceptionCode=0x%08lX", GetExceptionCode());
        }

        return 0;
    }
}

namespace NSCRevived::CrashFix
{
    void Log(const char* fmt, ...) noexcept
    {
        __try
        {
            const std::wstring dir = GetGameDir() + L"logs\\";
            CreateDirectoryW(dir.c_str(), nullptr);

            const std::wstring file = dir + L"NarutoStormConnectionsRevived_crashfix.log";
            FILE* f = nullptr;
            _wfopen_s(&f, file.c_str(), L"ab");
            if (!f)
                return;

            SYSTEMTIME st{};
            GetLocalTime(&st);
            std::fprintf(f, "[%04u-%02u-%02u %02u:%02u:%02u] ",
                st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

            va_list args;
            va_start(args, fmt);
            std::vfprintf(f, fmt, args);
            va_end(args);

            std::fprintf(f, "\n");
            std::fclose(f);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
        }
    }

    bool HooksDisabledByFlag() noexcept
    {
        const std::wstring flag = GetGameDir() + L"NSCRevived_DisableHooks.flag";
        return GetFileAttributesW(flag.c_str()) != INVALID_FILE_ATTRIBUTES;
    }

    bool IsStopping() noexcept
    {
        return g_stopping.load(std::memory_order_acquire);
    }

    void Start(HMODULE module) noexcept
    {
        g_module = module;
        g_stopping.store(false, std::memory_order_release);

        bool expected = false;
        if (!g_started.compare_exchange_strong(expected, true))
            return;

        HANDLE thread = CreateThread(nullptr, 0, FrameworkThread, module, 0, nullptr);
        if (thread)
            CloseHandle(thread);
        else
            Log("CreateThread failed. GetLastError=%lu", GetLastError());
    }

    void Stop() noexcept
    {
        g_stopping.store(true, std::memory_order_release);
        Log("Process detach requested");
    }
}
