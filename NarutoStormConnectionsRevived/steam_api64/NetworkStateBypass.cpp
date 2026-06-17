#include "StdInc.h"
#include "NetworkStateBypass.h"
#include "Logger.h"

namespace
{
    std::atomic<bool> g_Initialized{ false };
    std::string g_Report = "NetworkStateBypass not initialized";

    bool PatchString(const char* from, const char* to)
    {
        if (!from || !to)
            return false;
        const size_t fromLen = strlen(from);
        const size_t toLen = strlen(to);
        if (fromLen == 0 || toLen > fromLen)
            return false;

        HMODULE module = GetModuleHandleW(nullptr);
        if (!module)
            return false;

        auto* base = reinterpret_cast<unsigned char*>(module);
        auto* dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;
        auto* nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;
        const size_t imageSize = static_cast<size_t>(nt->OptionalHeader.SizeOfImage);
        bool patchedAny = false;

        for (size_t i = 0; i + fromLen < imageSize; ++i)
        {
            MEMORY_BASIC_INFORMATION mbi{};
            if (!VirtualQuery(base + i, &mbi, sizeof(mbi)))
                break;
            const auto* regionBase = static_cast<unsigned char*>(mbi.BaseAddress);
            const size_t regionSize = static_cast<size_t>(mbi.RegionSize);
            const bool readable = mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_NOACCESS) && !(mbi.Protect & PAGE_GUARD);
            if (!readable)
            {
                i = static_cast<size_t>((regionBase + regionSize) - base);
                continue;
            }

            for (size_t j = 0; j + fromLen <= regionSize; ++j)
            {
                unsigned char* p = const_cast<unsigned char*>(regionBase + j);
                if (memcmp(p, from, fromLen) == 0)
                {
                    DWORD oldProtect = 0;
                    if (VirtualProtect(p, fromLen, PAGE_EXECUTE_READWRITE, &oldProtect))
                    {
                        memcpy(p, to, toLen);
                        if (toLen < fromLen)
                            memset(p + toLen, '.', fromLen - toLen);
                        FlushInstructionCache(GetCurrentProcess(), p, fromLen);
                        DWORD ignored = 0;
                        VirtualProtect(p, fromLen, oldProtect, &ignored);
                        patchedAny = true;
                    }
                }
            }

            i = static_cast<size_t>((regionBase + regionSize) - base);
        }

        return patchedAny;
    }
}

bool NetworkStateBypass::Init()
{
    if (g_Initialized.exchange(true))
        return true;

    int patched = 0;
    patched += PatchString("ONLINE_ERROR", "ONLINE_CHECK") ? 1 : 0;
    patched += PatchString("OnlineError", "OnlineCheck") ? 1 : 0;
    patched += PatchString("StateOnlineStorageError", "StateOnlineCheck") ? 1 : 0;
    patched += PatchString("ccSceneNetwork::StateOnlineStorageError.", "ccSceneNetwork::StateOnlineCheck") ? 1 : 0;

    std::ostringstream ss;
    ss << "NetworkStateBypass initialized, online-error aliases patched=" << patched;
    g_Report = ss.str();
    Logger::Info(g_Report);
    return true;
}

void NetworkStateBypass::Tick()
{
}

const char* NetworkStateBypass::Report()
{
    return g_Report.c_str();
}

void NetworkStateBypass::Shutdown()
{
    g_Initialized = false;
}
