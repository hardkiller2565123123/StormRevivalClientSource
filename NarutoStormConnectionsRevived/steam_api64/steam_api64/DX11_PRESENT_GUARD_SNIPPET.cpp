// Add this style of guard at the TOP of your hooked Present function.
// It prevents crashes when the swapchain/device/context or ImGui state is not ready yet.

HRESULT __stdcall hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    if (!swapChain)
        return oPresent ? oPresent(swapChain, syncInterval, flags) : E_INVALIDARG;

    __try
    {
        if (!g_Device || !g_Context)
        {
            ID3D11Device* device = nullptr;
            if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device))) && device)
            {
                g_Device = device;
                g_Device->GetImmediateContext(&g_Context);
            }
        }

        if (g_Device && g_Context && !NSCRevived::CrashFix::IsStopping())
        {
            // existing ImGui/overlay render code goes here
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        NSCRevived::CrashFix::Log("CRASH BLOCKED in hkPresent. ExceptionCode=0x%08lX", GetExceptionCode());
    }

    return oPresent ? oPresent(swapChain, syncInterval, flags) : S_OK;
}
