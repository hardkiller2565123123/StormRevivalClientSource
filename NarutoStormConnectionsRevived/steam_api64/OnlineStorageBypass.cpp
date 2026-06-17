#include "StdInc.h"
#include "OnlineStorageBypass.h"
#include "Logger.h"

namespace
{
    std::atomic<bool> g_Initialized{ false };
    std::string g_Report = "OnlineStorageBypass not initialized";

    constexpr uintptr_t kNSCDefaultImageBase = 0x140000000ull;
    constexpr uintptr_t kDownloadUserDataTargetBattleEndVA = 0x1400D8D20ull;
    constexpr uintptr_t kDownloadUserDataNetworkStorageVA = 0x1408BA540ull;

    struct ReplaceRule
    {
        const char* from;
        const char* to;
        bool exactSize;
    };

    uintptr_t RvaFromVA(uintptr_t va)
    {
        return va - kNSCDefaultImageBase;
    }

    bool IsReadableProtect(DWORD protect)
    {
        protect &= 0xff;
        return protect != PAGE_NOACCESS;
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

    bool PatchBytes(void* address, const char* to, size_t fromLen, bool exactSize)
    {
        if (!address || !to || fromLen == 0)
            return false;

        const size_t toLen = strlen(to);
        if (exactSize && toLen != fromLen)
            return false;
        if (toLen > fromLen)
            return false;

        DWORD oldProtect = 0;
        if (!VirtualProtect(address, fromLen, PAGE_EXECUTE_READWRITE, &oldProtect))
            return false;

        memcpy(address, to, toLen);
        if (toLen < fromLen)
            memset(static_cast<unsigned char*>(address) + toLen, 0x20, fromLen - toLen);

        FlushInstructionCache(GetCurrentProcess(), address, fromLen);
        DWORD ignored = 0;
        VirtualProtect(address, fromLen, oldProtect, &ignored);
        return true;
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

    size_t PatchAsciiInMainModule(const ReplaceRule* rules, size_t count)
    {
        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
            return 0;

        size_t patched = 0;
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
                for (size_t i = 0; i < regionSize; ++i)
                {
                    for (size_t r = 0; r < count; ++r)
                    {
                        const size_t fromLen = strlen(rules[r].from);
                        if (fromLen == 0 || i + fromLen > regionSize)
                            continue;

                        if (memcmp(regionBase + i, rules[r].from, fromLen) == 0)
                        {
                            if (PatchBytes(regionBase + i, rules[r].to, fromLen, rules[r].exactSize))
                                ++patched;
                        }
                    }
                }
            }

            offset = static_cast<size_t>((regionBase + regionSize) - base);
        }

        return patched;
    }

    bool PatchStatusBranch(unsigned char* func, size_t scanSize)
    {
        if (!func || scanSize < 8)
            return false;

        // Most important NSC online-storage callbacks begin by testing the result/status arg:
        //   test edx, edx
        //   jz   failed_path
        // Force the branch to fall through into the success path.
        for (size_t i = 0; i + 8 <= scanSize; ++i)
        {
            // test edx, edx ; jz near rel32
            if (func[i] == 0x85 && func[i + 1] == 0xD2 && func[i + 2] == 0x0F && func[i + 3] == 0x84)
            {
                const unsigned char patch[] = { 0x85, 0xD2, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
                return WriteMemory(func + i, patch, sizeof(patch));
            }

            // test edx, edx ; jnz near rel32
            // If the compiler inverted the logic, force status to true before the test.
            if (func[i] == 0x85 && func[i + 1] == 0xD2 && func[i + 2] == 0x0F && func[i + 3] == 0x85)
            {
                const unsigned char patch[] = { 0xBA, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90 };
                return WriteMemory(func + i, patch, sizeof(patch));
            }

            // test edx, edx ; jz short rel8
            if (i + 4 <= scanSize && func[i] == 0x85 && func[i + 1] == 0xD2 && func[i + 2] == 0x74)
            {
                const unsigned char patch[] = { 0x85, 0xD2, 0x90, 0x90 };
                return WriteMemory(func + i, patch, sizeof(patch));
            }

            // cmp edx, 1 ; jz/jnz near rel32
            if (i + 9 <= scanSize && func[i] == 0x83 && func[i + 1] == 0xFA && func[i + 2] == 0x01 && func[i + 3] == 0x0F &&
                (func[i + 4] == 0x84 || func[i + 4] == 0x85))
            {
                const unsigned char patch[] = { 0xBA, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90 };
                return WriteMemory(func + i, patch, sizeof(patch));
            }
        }

        return false;
    }

    bool PatchFunctionEntryReturnTrue(unsigned char* func)
    {
        // Last-resort fallback. Return TRUE immediately from the two tiny async result handlers.
        // x64 caller cleans args, so this is safe for bool/int style callbacks.
        const unsigned char patch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };
        return WriteMemory(func, patch, sizeof(patch));
    }

    bool PatchStorageFunctionByVA(uintptr_t va, const char* name, bool allowEntryFallback, std::ostringstream& report)
    {
        unsigned char* base = nullptr;
        size_t imageSize = 0;
        if (!GetMainImage(base, imageSize))
        {
            report << " " << name << "=noimage";
            return false;
        }

        const uintptr_t rva = RvaFromVA(va);
        if (rva >= imageSize)
        {
            report << " " << name << "=bad_rva";
            return false;
        }

        unsigned char* func = base + rva;
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(func, &mbi, sizeof(mbi)) || mbi.State != MEM_COMMIT || !IsReadableProtect(mbi.Protect))
        {
            report << " " << name << "=not_readable";
            return false;
        }

        bool ok = PatchStatusBranch(func, 0x140);
        if (!ok && allowEntryFallback)
            ok = PatchFunctionEntryReturnTrue(func);

        report << " " << name << "=" << (ok ? "patched" : "miss");
        return ok;
    }
}

bool OnlineStorageBypass::Init()
{
    if (g_Initialized.exchange(true))
        return true;

    const ReplaceRule rules[] =
    {
        // Same-length/state-name patches. These stop UI/state scripts from resolving the storage-error route.
        { "OnlineStorageRequestDownloadUserData Failed", "OnlineStorageRequestDownloadUserData OK    ", true },
        { "ccSceneNetwork::StateOnlineStorageError.", "ccSceneNetwork::StateOnlineCheck.........", true },
        { "StateOnlineStorageError", "StateOnlineCheck.......", true },
        { "OnlineStorageError", "OnlineStorageReady", true },
        { "ONLINE_ERROR", "ONLINE_CHECK", true },
        { "OnlineError", "OnlineCheck", true },
        { "Network_Error", "Network_Check", true },
        { "NetError", "NetOpen ", true }
    };

    const size_t stringPatches = PatchAsciiInMainModule(rules, ARRAYSIZE(rules));

    std::ostringstream ss;
    ss << "OnlineStorageBypass initialized, string aliases patched=" << stringPatches;

    // Confirmed from IDA xrefs to OnlineStorageRequestDownloadUserData Failed:
    //   sub_1400D8D20+13A
    //   sub_1408BA540+13A
    // The failure branch is selected by the async download result/status parameter.
    PatchStorageFunctionByVA(kDownloadUserDataTargetBattleEndVA, "sub_1400D8D20", false, ss);
    PatchStorageFunctionByVA(kDownloadUserDataNetworkStorageVA, "sub_1408BA540", false, ss);

    g_Report = ss.str();
    Logger::Info(g_Report);
    return true;
}

void OnlineStorageBypass::Tick()
{
    // Keep the string/state aliases sticky in case the game copies state names during scene changes.
    const ReplaceRule rules[] =
    {
        { "ONLINE_ERROR", "ONLINE_CHECK", true },
        { "OnlineError", "OnlineCheck", true },
        { "Network_Error", "Network_Check", true },
        { "NetError", "NetOpen ", true }
    };
    PatchAsciiInMainModule(rules, ARRAYSIZE(rules));
}

const char* OnlineStorageBypass::Report()
{
    return g_Report.c_str();
}

void OnlineStorageBypass::Shutdown()
{
    g_Initialized = false;
}
