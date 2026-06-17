#include "StdInc.h"
#include "OnlineCheckBypass.h"
#include "OnlineStorageBypass.h"
#include "NetworkStateBypass.h"
#include "Logger.h"

namespace
{
    std::atomic<bool> g_Running{ false };
    HANDLE g_Thread = nullptr;
    std::string g_Report = "OnlineCheckBypass not initialized";

    constexpr uintptr_t kNSCDefaultImageBase = 0x140000000ull;
    constexpr uintptr_t kStateOnlineCheckA_VA = 0x141090FE0ull;
    constexpr uintptr_t kStateOnlineCheckB_VA = 0x141091140ull;

    uintptr_t RvaFromVA(uintptr_t va)
    {
        return va - kNSCDefaultImageBase;
    }

    bool GetMainImage(unsigned char*& base, size_t& imageSize)
    {
        HMODULE module = GetModuleHandleW(nullptr);
        if (!module)
            return false;

        base = reinterpret_cast<unsigned char*>(module);
        auto* dos = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
        if (dos->e_magic != IMAGE_DOS_SIGNATURE)
            return false;

        auto* nt = reinterpret_cast<PIMAGE_NT_HEADERS>(base + dos->e_lfanew);
        if (nt->Signature != IMAGE_NT_SIGNATURE)
            return false;

        imageSize = static_cast<size_t>(nt->OptionalHeader.SizeOfImage);
        return true;
    }

    bool WriteMemory(void* address, const void* data, size_t size)
    {
        if (!address || !data || size == 0)
            return false;

        DWORD oldProtect = 0;
        if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        memcpy(address, data, size);
        FlushInstructionCache(GetCurrentProcess(), address, size);

        DWORD ignored = 0;
        VirtualProtect(address, size, oldProtect, &ignored);
        return true;
    }

    bool PatchFunctionReturnInt(uintptr_t va, int value)
    {
        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return false;

        const uintptr_t rva = RvaFromVA(va);
        if (rva + 16 >= imageSize)
            return false;

        unsigned char* target = base + rva;

        // x64: mov eax, imm32 ; ret ; nop...
        // Works for bool/int state handlers and is safe for x64 calling convention.
        unsigned char patch[8] = { 0xB8, 0, 0, 0, 0, 0xC3, 0x90, 0x90 };
        memcpy(&patch[1], &value, sizeof(value));
        return WriteMemory(target, patch, sizeof(patch));
    }

    bool PatchMainModuleString(const char* from, const char* to)
    {
        if (!from || !to)
            return false;

        const size_t fromLen = strlen(from);
        const size_t toLen = strlen(to);
        if (fromLen == 0 || toLen > fromLen)
            return false;

        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return false;

        bool patched = false;
        for (size_t offset = 0; offset < imageSize;)
        {
            MEMORY_BASIC_INFORMATION mbi{};
            if (!VirtualQuery(base + offset, &mbi, sizeof(mbi)))
                break;

            auto* regionBase = static_cast<unsigned char*>(mbi.BaseAddress);
            const size_t regionSize = static_cast<size_t>(mbi.RegionSize);
            const bool readable = mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_NOACCESS) && !(mbi.Protect & PAGE_GUARD);

            if (readable)
            {
                for (size_t i = 0; i + fromLen <= regionSize; ++i)
                {
                    unsigned char* p = regionBase + i;
                    if (memcmp(p, from, fromLen) != 0)
                        continue;

                    DWORD oldProtect = 0;
                    if (!VirtualProtect(p, fromLen, PAGE_EXECUTE_READWRITE, &oldProtect))
                        continue;

                    memcpy(p, to, toLen);
                    if (toLen < fromLen)
                        memset(p + toLen, 0x20, fromLen - toLen);
                    FlushInstructionCache(GetCurrentProcess(), p, fromLen);
                    DWORD ignored = 0;
                    VirtualProtect(p, fromLen, oldProtect, &ignored);
                    patched = true;
                }
            }

            offset = static_cast<size_t>((regionBase + regionSize) - base);
        }

        return patched;
    }

    DWORD WINAPI WatchThread(LPVOID)
    {
        Logger::Info("OnlineCheckBypass watchdog started");

        while (g_Running.load())
        {
            OnlineCheckBypass::ForceConnectedState();
            OnlineStorageBypass::Tick();
            NetworkStateBypass::Tick();
            Sleep(1000);
        }

        Logger::Info("OnlineCheckBypass watchdog stopped");
        return 0;
    }
}

bool OnlineCheckBypass::Init()
{
    if (g_Running.exchange(true))
        return true;

    int stringPatches = 0;
    stringPatches += PatchMainModuleString("ONLINE_ERROR", "ONLINE_CHECK") ? 1 : 0;
    stringPatches += PatchMainModuleString("OnlineError", "OnlineCheck") ? 1 : 0;
    stringPatches += PatchMainModuleString("NetError", "NetOpen ") ? 1 : 0;
    stringPatches += PatchMainModuleString("DISCONNECT_CHECK", "ONLINE_CHECK....") ? 1 : 0;
    stringPatches += PatchMainModuleString("DISCONNECT_PENALTY_WARNING", "ONLINE_CHECK................") ? 1 : 0;
    stringPatches += PatchMainModuleString("LOGINBONUS_CHECK", "ONLINE_CHECK....") ? 1 : 0;
    stringPatches += PatchMainModuleString("PLAYERGUIDE_CHECK", "ONLINE_CHECK.....") ? 1 : 0;
    stringPatches += PatchMainModuleString("IsDisconnected()", "IsConnectedOK() ") ? 1 : 0;
    stringPatches += PatchMainModuleString("IsDisconnectedFix()", "IsConnectedFixOK() ") ? 1 : 0;

    // Confirmed by IDA xrefs to .rdata OnlineCheck:
    // sub_141090FE0 + 0x9D and sub_141091140 + 0x9E.
    // Force these state handlers to report success immediately instead of entering NetError.
    const bool onlineCheckA = PatchFunctionReturnInt(kStateOnlineCheckA_VA, 1);
    const bool onlineCheckB = PatchFunctionReturnInt(kStateOnlineCheckB_VA, 1);

    OnlineStorageBypass::Init();
    NetworkStateBypass::Init();

    std::ostringstream ss;
    ss << "OnlineCheckBypass v20 enabled, string patches=" << stringPatches
       << " sub_141090FE0=" << (onlineCheckA ? "patched" : "miss")
       << " sub_141091140=" << (onlineCheckB ? "patched" : "miss")
       << "; storage=" << OnlineStorageBypass::Report()
       << "; networkState=" << NetworkStateBypass::Report();
    g_Report = ss.str();
    Logger::Info(g_Report);

    g_Thread = CreateThread(nullptr, 0, WatchThread, nullptr, 0, nullptr);
    return true;
}

void OnlineCheckBypass::RevalidateSignatures()
{
    ForceConnectedState();
}

void OnlineCheckBypass::ForceConnectedState()
{
    PatchMainModuleString("ONLINE_ERROR", "ONLINE_CHECK");
    PatchMainModuleString("OnlineError", "OnlineCheck");
    PatchMainModuleString("NetError", "NetOpen ");
}

const char* OnlineCheckBypass::SignatureReport()
{
    return g_Report.c_str();
}

void OnlineCheckBypass::Shutdown()
{
    if (!g_Running.exchange(false))
        return;

    if (g_Thread)
    {
        WaitForSingleObject(g_Thread, 1500);
        CloseHandle(g_Thread);
        g_Thread = nullptr;
    }

    NetworkStateBypass::Shutdown();
    OnlineStorageBypass::Shutdown();
}
