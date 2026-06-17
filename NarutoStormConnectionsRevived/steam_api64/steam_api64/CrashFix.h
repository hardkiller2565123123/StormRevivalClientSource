#pragma once
#include <windows.h>

namespace NSCRevived::CrashFix
{
    void Start(HMODULE module) noexcept;
    void Stop() noexcept;
    bool IsStopping() noexcept;
    bool HooksDisabledByFlag() noexcept;
    void Log(const char* fmt, ...) noexcept;
}
