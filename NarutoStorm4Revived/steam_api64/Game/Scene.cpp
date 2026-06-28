#include <cstdint>
#include "Scene.h"
#include "Common.h"
#include "Console.h"
#include "mem.h"
#include "FileParser.h"
#include <Psapi.h>
#include "Offsets.h"
#include <string>
#include <cstdio>

class SceneExpander {
public:
    static inline int ORIGINAL_COUNT;
    static inline SceneEntry* g_pNewSceneArray;
    static inline int g_NewSceneCountAllocated;
    static inline int SCENE_SLOT_COUNT = 512;
    static inline uintptr_t g_SceneCountPatchAddress;

    // Allocates memory within 2GB of the given base address.
    static LPVOID AllocNearModule(LPVOID base, SIZE_T size) {
        const uintptr_t TWO_GB = 0x80000000ULL;
        uintptr_t baseAddr = reinterpret_cast<uintptr_t>(base);
        const uintptr_t PAGE_SIZE = 0x1000ULL;
        for (int i = 0; i < 1000; ++i) {
            uintptr_t candidate = baseAddr + i * PAGE_SIZE;
            if (candidate - baseAddr > TWO_GB) break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr) return addr;
        }
        for (int i = 1; i < 1000; ++i) {
            if (baseAddr < i * PAGE_SIZE) break;
            uintptr_t candidate = baseAddr - i * PAGE_SIZE;
            if (baseAddr - candidate > TWO_GB) break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr) return addr;
        }
        return nullptr;
    }

    // Patches absolute references in the specified range.
    static void PatchAbsoluteReferencesInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        for (uintptr_t addr = start; addr <= end - sizeof(uintptr_t); ++addr) {
            if (*reinterpret_cast<uintptr_t*>(addr) == oldArrayAddr) {
                DWORD oldProtect;
                if (VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                    *reinterpret_cast<uintptr_t*>(addr) = newArrayAddr;
                    VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), oldProtect, &oldProtect);
                    Console::PrintOut("Patched SCENE absolute ref at: 0x%p\n", (void*)addr);
                }
                else {
                    Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                }
            }
        }
    }

    // Patches RIP-relative instructions (LEA/MOV) in the specified range.
    static void PatchRelativeInstrInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr, uint8_t opcode) {
        DWORD oldProtect;
        // Without REX (6-byte)
        for (uintptr_t addr = start; addr <= end - 6; ++addr) {
            if (*(uint8_t*)addr == opcode) {
                uint8_t modrm = *(uint8_t*)(addr + 1);
                if ((modrm & 0xC7) == 0x05) {
                    int32_t disp = *reinterpret_cast<int32_t*>(addr + 2);
                    uintptr_t instrEnd = addr + 6;
                    if (instrEnd + disp == oldArrayAddr) {
                        int32_t newDisp = static_cast<int32_t>(newArrayAddr - instrEnd);
                        if (VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                            *reinterpret_cast<int32_t*>(addr + 2) = newDisp;
                            VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t), oldProtect, &oldProtect);
                            Console::PrintOut("Patched RIP-relative SCENE (no REX, opcode 0x%X) at: 0x%p\n", opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
        // With REX (7-byte)
        for (uintptr_t addr = start; addr <= end - 7; ++addr) {
            uint8_t rex = *(uint8_t*)addr;
            if (rex >= 0x40 && rex <= 0x4F && *(uint8_t*)(addr + 1) == opcode) {
                uint8_t modrm = *(uint8_t*)(addr + 2);
                if ((modrm & 0xC7) == 0x05) {
                    int32_t disp = *reinterpret_cast<int32_t*>(addr + 3);
                    uintptr_t instrEnd = addr + 7;
                    if (instrEnd + disp == oldArrayAddr) {
                        int32_t newDisp = static_cast<int32_t>(newArrayAddr - instrEnd);
                        if (VirtualProtect((LPVOID)(addr + 3), sizeof(int32_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                            *reinterpret_cast<int32_t*>(addr + 3) = newDisp;
                            VirtualProtect((LPVOID)(addr + 3), sizeof(int32_t), oldProtect, &oldProtect);
                            Console::PrintOut("Patched RIP-relative SCENE (with REX, opcode 0x%X) at: 0x%p\n", opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
    }

    // Scans executable sections to patch all references to the old Scene list address.
    static void AutoPatchSceneListReferences(uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        HMODULE hModule = GetModuleHandle(nullptr);
        MODULEINFO modInfo = { 0 };
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
            Console::PrintErr("GetModuleInformation failed in AutoPatchSceneListReferences.\n");
            return;
        }
        PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
        PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uint8_t*>(hModule) + dosHeader->e_lfanew);
        PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeaders);
        for (unsigned i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i, ++section) {
            if (section->Characteristics & IMAGE_SCN_MEM_EXECUTE) {
                uintptr_t secStart = reinterpret_cast<uintptr_t>(hModule) + section->VirtualAddress;
                uintptr_t secEnd = secStart + section->Misc.VirtualSize;
                Console::PrintOut("Scanning section %.8s: 0x%p - 0x%p\n", section->Name, (void*)secStart, (void*)secEnd);
                PatchAbsoluteReferencesInRange(secStart, secEnd, oldArrayAddr, newArrayAddr);
                PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8D); // LEA
                PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8B); // MOV
            }
        }
    }

    // Return current number of scene entries by scanning until a termination marker (id == 0 or empty name).
    static int GetCurrentSceneCount() {
        if (!SceneExpander::g_pNewSceneArray) return 0;
        int count = 0;
        const int safety = SceneExpander::g_NewSceneCountAllocated;
        for (; count < safety; ++count) {
            if (SceneExpander::g_pNewSceneArray[count].id == -1)
                break;
        }
        return count;
    }
    static bool PatchCountVar(uintptr_t addr, uint32_t newCount)
    {
        if (addr == 0) return false;
        DWORD oldProtect;
        uintptr_t page = addr & ~static_cast<uintptr_t>(0xFFF);
        if (!VirtualProtect(reinterpret_cast<LPVOID>(page), 0x1000, PAGE_READWRITE, &oldProtect)) {
            Console::PrintErr("VirtualProtect failed for 0x%p\n", (void*)addr);
            return false;
        }
        *reinterpret_cast<uint32_t*>(addr) = newCount;
        //  
        DWORD tmp;
        VirtualProtect(reinterpret_cast<LPVOID>(page), 0x1000, oldProtect, &tmp);
        Console::PrintOut("Patched count at 0x%p -> %u\n", (void*)addr, newCount);
        return true;
    }

    static bool TryReadSceneCount(SceneEntry* sceneArray, int& outCount)
    {
        outCount = 0;
        if (!sceneArray)
            return false;

        __try
        {
            const int safetyLimit = 465;
            for (int i = 0; i < safetyLimit; ++i)
            {
                if (sceneArray[i].id == static_cast<uint32_t>(-1))
                {
                    outCount = i;
                    return i > 0;
                }

            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }

        return false;
    }

    static bool TryResolveSceneArray(uintptr_t& outSceneArrayOffset, int& outOriginalCount, const char*& outVersionName)
    {
        struct Candidate
        {
            const char* version;
            const char* label;
            uintptr_t offset;
            uintptr_t countPatchOffset;
        };

        const Candidate candidates[] = {
            {"1.09", "Storm 4", offsetS4::OFF_SCENEARRAY, 0x6E43D2},
            {"1.60", "Storm Connections", offsetSC::OFF_SCENEARRAY, 0x87AA71},
        };

        if (GameVersion)
        {
            for (const Candidate& candidate : candidates)
            {
                if (std::strcmp(GameVersion, candidate.version) == 0)
                {
                    SceneEntry* sceneArray = reinterpret_cast<SceneEntry*>(moduleBase + candidate.offset - 0xC00);
                    if (TryReadSceneCount(sceneArray, outOriginalCount))
                    {
                        outSceneArrayOffset = candidate.offset;
                        outVersionName = candidate.label;
                        g_SceneCountPatchAddress = moduleBase + candidate.countPatchOffset;
                        return true;
                    }

                    Console::PrintErr("Scene table for GameVersion %s was not readable.\n", GameVersion);
                    return false;
                }
            }
        }

        for (const Candidate& candidate : candidates)
        {
            SceneEntry* sceneArray = reinterpret_cast<SceneEntry*>(moduleBase + candidate.offset - 0xC00);
            if (TryReadSceneCount(sceneArray, outOriginalCount))
            {
                outSceneArrayOffset = candidate.offset;
                outVersionName = candidate.label;
                g_SceneCountPatchAddress = moduleBase + candidate.countPatchOffset;
                Console::PrintOut("Scene table auto-detected as %s because GameVersion was %s.\n",
                    candidate.label, GameVersion ? GameVersion : "(null)");
                return true;
            }
        }

        return false;
    }

    // Expands the vanilla Scene list by copying all entries until termination, allocating new array and patching code references.
    static void ExpandSceneList() {
        if (SceneExpander::g_pNewSceneArray)
        {
            Console::PrintOut("Scene list is already expanded: current=%d, capacity=%d\n",
                GetCurrentSceneCount(), SceneExpander::g_NewSceneCountAllocated);
            return;
        }

        uintptr_t SceneArrayOffset = 0;
        int originalCount = 0;
        const char* resolvedVersionName = "Unknown";

        if (!TryResolveSceneArray(SceneArrayOffset, originalCount, resolvedVersionName))
        {
            Console::PrintErr("Unable to resolve scene table for GameVersion %s.\n", GameVersion ? GameVersion : "(null)");
            return;
        }

        SceneEntry* pOriginal = reinterpret_cast<SceneEntry*>(moduleBase + SceneArrayOffset - 0xC00);
        Console::PrintOut("Expanded Scene list: %s table at 0x%p\n", resolvedVersionName, pOriginal);
        SceneExpander::ORIGINAL_COUNT = originalCount;
        SceneExpander::g_NewSceneCountAllocated = originalCount + SCENE_SLOT_COUNT;
        size_t newSize = SceneExpander::g_NewSceneCountAllocated * sizeof(SceneEntry);
        SceneExpander::g_pNewSceneArray = reinterpret_cast<SceneEntry*>(AllocNearModule(reinterpret_cast<LPVOID>(moduleBase), newSize));
        if (!SceneExpander::g_pNewSceneArray) {
            Console::PrintErr("Failed to allocate new scene list array.\n");
            return;
        }
        // copy original
        for (int i = 0; i < originalCount; ++i) {
            SceneExpander::g_pNewSceneArray[i] = pOriginal[i];
            Console::PrintOut("Copied scene entry %d: id=%u, name=%s\n", i, pOriginal[i].id, pOriginal[i].name);
        }
        // termination entry
        SceneExpander::g_pNewSceneArray[originalCount].id = -1;
        SceneExpander::g_pNewSceneArray[originalCount].start_func_ptr = 0;
        SceneExpander::g_pNewSceneArray[originalCount].name[0] = '\0';

        // patch references from old array location to new location
        AutoPatchSceneListReferences(reinterpret_cast<uintptr_t>(pOriginal)+8, reinterpret_cast<uintptr_t>(SceneExpander::g_pNewSceneArray) + 8);
        Console::PrintOut("Expanded Scene list: new array at 0x%p, vanilla count = %d (allocated %d slots)\n",
            SceneExpander::g_pNewSceneArray, originalCount, SceneExpander::g_NewSceneCountAllocated);
    }

    // Adds one custom scene by name + function pointer (no file I/O).
    // Returns index of added/updated entry, -1 on error.
    static int AddCustomScene(uint32_t newId, const char* sceneName, uint64_t sceneFuncPtr) {
        if (!SceneExpander::g_pNewSceneArray) {
            Console::PrintErr("Scene array not allocated.\n");
            return -1;
        }
        std::string sname(sceneName ? sceneName : "");
        // find current count (index of termination)
        int index = SceneExpander::GetCurrentSceneCount();
        if (index < 0) {
            Console::PrintErr("Failed to determine current scene count.\n");
            return -1;
        }
        if (index >= SceneExpander::g_NewSceneCountAllocated - 1) {
            Console::PrintErr("Not enough capacity to add custom scene (index=%d, allocated=%d)\n", index, SceneExpander::g_NewSceneCountAllocated);
            return -1;
        }
        // prepare entry
        SceneEntry newEntry{};
        newEntry.id = newId;
        memset(newEntry.pad0, 0, sizeof(newEntry.pad0));
        newEntry.start_func_ptr = sceneFuncPtr;
        memset(newEntry.name, 0, sizeof(newEntry.name));
        strncpy(newEntry.name, sname.c_str(), sizeof(newEntry.name) - 1);

        // try replace by name or id
        for (int i = 0; i < index; ++i) {
            if (SceneExpander::g_pNewSceneArray[i].id == newEntry.id ||
                (SceneExpander::g_pNewSceneArray[i].name[0] != '\0' && strcmp(SceneExpander::g_pNewSceneArray[i].name, newEntry.name) == 0)) {
                SceneExpander::g_pNewSceneArray[i] = newEntry;
                Console::PrintOut("Replaced scene entry at index %d: id=%u, name=%s, func=0x%p\n", i, newEntry.id, newEntry.name, (void*)newEntry.start_func_ptr);
                return i;
            }
        }

        // append
        SceneExpander::g_pNewSceneArray[index] = newEntry;
        // set termination after appended
        int nextIdx = index + 1;
        if (nextIdx < SceneExpander::g_NewSceneCountAllocated) {
            SceneExpander::g_pNewSceneArray[nextIdx].id = -1;
            SceneExpander::g_pNewSceneArray[nextIdx].start_func_ptr = 0;
            SceneExpander::g_pNewSceneArray[nextIdx].name[0] = '\0';
        }
        Console::PrintOut("Added custom scene at index %d: id=%u, name=%s, func=0x%p\n", index, newEntry.id, newEntry.name, (void*)newEntry.start_func_ptr);
        int new_count = GetCurrentSceneCount();
        if (g_SceneCountPatchAddress)
            PatchCountVar(g_SceneCountPatchAddress, new_count);
        

        return index;
    }
    static __int64 __fastcall ccSceneTestStart_Init(__int64 a1)
    {
        using fn_sub_1404DFAD0 = __int64* (__fastcall*)(__int64 a1, const char* a2, const char* a3, const char* a4, int a5);
        auto sub_1404DFAD0 = reinterpret_cast<fn_sub_1404DFAD0>(moduleBase + 0x4DEED0);
        using fn_sub_140B02B70 = __int64(__fastcall*)(__int64 a1);
        auto sub_140B02B70 = reinterpret_cast<fn_sub_140B02B70>(moduleBase + 0xB01F70);


        sub_1404DFAD0(a1, "d200_010", "data/ia/d200/d200_script.xfbin", "data/ia/d200/d200_010.lua", 0);
        sub_140B02B70((__int64)"BOSS_BATTLE_23");
        return a1;
    }
    static __int64 __fastcall ccSceneTestStart(uint8_t* a1) {

        Console::PrintErr("SCENE WORKED\n");

        using fn_sub_14124AE70 = void*(__fastcall*)(size_t a1, __int64 a2, int a3);
        auto sub_14124AE70 = reinterpret_cast<fn_sub_14124AE70>(moduleBase + 0x124A270);

        using fn_sub_1406A6EB0 = __int64(__fastcall*)(__int64 a1);
        auto sub_1406A6EB0 = reinterpret_cast<fn_sub_1406A6EB0>(moduleBase + 0x6A62B0);
        using fn_sub_14106C890 = __int64* (__fastcall*)(__int64 a1, uint8_t* a2);
        auto sub_14106C890 = reinterpret_cast<fn_sub_14106C890>(moduleBase + 0x106BC90);

        void* v2; // rax
        __int64 v3; // rbx

        v2 = sub_14124AE70(
            0x198ui64,
            (__int64)"D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ccSceneFactory.cpp",
            797);
        if (v2)
            v3 = ccSceneTestStart_Init((__int64)v2);
        else
            v3 = 0i64;
        sub_14106C890(v3, a1);
        return v3;
    }
};

namespace
{
    const char* g_SceneExpansionStatus = "Scene expansion has not been requested.";
    char g_SceneExpansionStatusBuffer[256] = {};
}

namespace StageSlotExpansion
{
    void SetExtraCapacity(int extraSlots)
    {
        if (SceneExpander::g_pNewSceneArray)
            return;

        if (extraSlots < 0)
            extraSlots = 0;

        if (extraSlots > 4096)
            extraSlots = 4096;

        SceneExpander::SCENE_SLOT_COUNT = extraSlots;
    }

    bool ExpandSceneList()
    {
        SceneExpander::ExpandSceneList();

        if (SceneExpander::g_pNewSceneArray)
        {
            std::snprintf(g_SceneExpansionStatusBuffer, sizeof(g_SceneExpansionStatusBuffer),
                "Scene list expanded: current=%d, capacity=%d.",
                SceneExpander::GetCurrentSceneCount(),
                SceneExpander::g_NewSceneCountAllocated);
            g_SceneExpansionStatus = g_SceneExpansionStatusBuffer;
            return true;
        }

        g_SceneExpansionStatus = "Scene expansion failed or game version was not detected.";
        return false;
    }

    int CurrentCount()
    {
        return SceneExpander::GetCurrentSceneCount();
    }

    int Capacity()
    {
        return SceneExpander::g_NewSceneCountAllocated;
    }

    const char* LastStatus()
    {
        return g_SceneExpansionStatus;
    }
}
