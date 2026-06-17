// Put this around MinHook startup so hooks cannot initialize twice.

#include <atomic>
static std::atomic<bool> g_hooksInitialized{ false };

bool InitHooksSafe()
{
    bool expected = false;
    if (!g_hooksInitialized.compare_exchange_strong(expected, true))
        return true;

    __try
    {
        if (MH_Initialize() != MH_OK)
        {
            NSCRevived::CrashFix::Log("MH_Initialize failed");
            return false;
        }

        // Create hooks here.
        // IMPORTANT: only enable hooks after every required target pointer is valid.
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        NSCRevived::CrashFix::Log("CRASH BLOCKED in InitHooksSafe. ExceptionCode=0x%08lX", GetExceptionCode());
        return false;
    }
}
