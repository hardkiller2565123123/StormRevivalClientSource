#include <windows.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <Psapi.h>
#include <fstream>
#include "Offsets.h"
#include <iostream>
#include "Common.h"
#include "FileParser.h"
#include "Console.h"
#include <mutex>
using namespace std;

// Structure for a BGM list entry.
struct ProjectileEntry {
    uint64_t ProjectileName; // Address to stage sound string (8 bytes)
};
namespace ProjectileNames {
    static std::vector<std::string> gNames;
    static std::mutex gNamesMutex;

    static void InitializeDefaults()
    {
        std::lock_guard<std::mutex> lk(gNamesMutex);
        if (!gNames.empty()) return;
        gNames.push_back("SYURIKEN");
        gNames.push_back("KUNAI");
        gNames.push_back("KIBAKUKUNAI");
        gNames.push_back("DEF_DOWN");
        gNames.push_back("POW_DOWN");
        gNames.push_back("SPD_DOWN");
        gNames.push_back("POISON");
        gNames.push_back("MADOROMI");
        gNames.push_back("CHAKRA_SEAL");
        gNames.push_back("RAKUSHIKI");
        gNames.push_back("SAKURETSU");
        gNames.push_back("KIBAKUFUDA");
        gNames.push_back("KIBAKUDAMA");
        gNames.push_back("JINRAI");
        gNames.push_back("ITEM_CHAKRA_DRAIN");
        gNames.push_back("ITEM_CHAKRA_DRAIN_EX");
        gNames.push_back("CHAKRA_BALL_GET");
        gNames.push_back("TEST00");
        gNames.push_back("TEST01");
    }

    //    ()
    static void AddName(const std::string& name)
    {
        std::lock_guard<std::mutex> lk(gNamesMutex);
        gNames.push_back(name);
        Console::PrintOut("ProjectileNames: added \"%s\"\n", name.c_str());
    }

    //        ,   :   recordSize (0x40)
    static void LoadFromFile(const std::string& filename)
    {
        std::vector<BYTE> bytes = FileParser::ReadAllBytes(filename);
        if (bytes.empty()) {
            Console::PrintErr("ProjectileNames: failed read %s\n", filename.c_str());
            return;
        }
        const size_t recordSize = 0x40;
        if (bytes.size() < recordSize) {
            Console::PrintErr("ProjectileNames: file %s too small\n", filename.c_str());
            return;
        }
        InitializeDefaults();
        int count = static_cast<int>(bytes.size() / recordSize);
        std::lock_guard<std::mutex> lk(gNamesMutex);
        for (int i = 0; i < count; ++i) {
            size_t off = static_cast<size_t>(i) * recordSize;
            char buf[0x41] = { 0 };
            memcpy(buf, &bytes[off], 0x40);
            buf[0x40] = '\0';
            gNames.emplace_back(buf);
            Console::PrintOut("ProjectileNames: file added \"%s\"\n", buf);
        }
    }

}

class ProjectileExpander {
public:
    // ORIGINAL_COUNT is determined by scanning the vanilla array.
    static inline int ORIGINAL_COUNT;
    static inline ProjectileEntry* g_pNewProjectileArray;
    static inline int g_NewProjectileCountAllocated; // Total allocated slots
    static inline int PROJECTILE_SLOT_COUNT = 200;
    static __int64 __fastcall ProjectileExpander::sub_1409F0730(__int64 a1, __int64 a2)
    {
        //ProjectileNames::InitializeDefaults();

        const unsigned char* target = reinterpret_cast<const unsigned char*>(a2);
        if (!target) return 0xFFFFFFFFi64;

        std::lock_guard<std::mutex> lk(ProjectileNames::gNamesMutex);

        size_t index = 0;
        for (const std::string& candStr : ProjectileNames::gNames)
        {
            const unsigned char* cand = reinterpret_cast<const unsigned char*>(candStr.c_str());
            size_t i = 0;
            int diff = 0;
            //   :  ,
            //  diff = cand[i] - target[i],     target (while target[i])
            while (true)
            {
                unsigned char t = target[i];
                unsigned char c = cand[i];
                diff = static_cast<int>(c) - static_cast<int>(t);
                if (diff != 0) break;
                if (t == 0) break; //  target
                ++i;
            }
            if (diff == 0)
            {
                return static_cast<__int64>(index); //     (0-based)
            }
            ++index;
            //        (  )
            if (index >= 0x1000000) break;
        }

        return 0xFFFFFFFFi64; //  
    }
    // Allocates memory within 2GB of the given base address.
    static LPVOID AllocNearModule(LPVOID base, SIZE_T size) {
        const uintptr_t TWO_GB = 0x80000000;
        uintptr_t baseAddr = reinterpret_cast<uintptr_t>(base);
        const uintptr_t PAGE_SIZE = 0x1000;
        // Try addresses above base.
        for (int i = 0; i < 1000; i++) {
            uintptr_t candidate = baseAddr + i * PAGE_SIZE;
            if (candidate - baseAddr > TWO_GB)
                break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size,
                MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr)
                return addr;
        }
        // Then try addresses below base.
        for (int i = 1; i < 1000; i++) {
            if (baseAddr < i * PAGE_SIZE)
                break;
            uintptr_t candidate = baseAddr - i * PAGE_SIZE;
            if (baseAddr - candidate > TWO_GB)
                break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size,
                MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr)
                return addr;
        }
        return nullptr;
    }

    // Patches absolute references in the specified range.
    static void PatchAbsoluteReferencesInRange(uintptr_t start, uintptr_t end,
        uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        for (uintptr_t addr = start; addr <= end - sizeof(uintptr_t); addr++) {
            if (*reinterpret_cast<uintptr_t*>(addr) == oldArrayAddr) {
                DWORD oldProtect;
                if (VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t),
                    PAGE_EXECUTE_READWRITE, &oldProtect)) {
                    *reinterpret_cast<uintptr_t*>(addr) = newArrayAddr;
                    VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), oldProtect, &oldProtect);
                    Console::PrintOut("Patched absolute ref at: 0x%p\n", (void*)addr);
                }
                else {
                    Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                }
            }
        }
    }

    // Patches RIP-relative instructions (LEA/MOV) in the specified range.
    static void PatchRelativeInstrInRange(uintptr_t start, uintptr_t end,
        uintptr_t oldArrayAddr, uintptr_t newArrayAddr, uint8_t opcode) {
        DWORD oldProtect;
        // Without REX (6-byte instructions)
        for (uintptr_t addr = start; addr <= end - 6; addr++) {
            if (*(uint8_t*)addr == opcode) {
                uint8_t modrm = *(uint8_t*)(addr + 1);
                if ((modrm & 0xC7) == 0x05) {
                    int32_t disp = *reinterpret_cast<int32_t*>(addr + 2);
                    uintptr_t instrEnd = addr + 6;
                    if (instrEnd + disp == oldArrayAddr) {
                        int32_t newDisp = static_cast<int32_t>(newArrayAddr - instrEnd);
                        if (VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t),
                            PAGE_EXECUTE_READWRITE, &oldProtect)) {
                            *reinterpret_cast<int32_t*>(addr + 2) = newDisp;
                            VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t), oldProtect, &oldProtect);
                            Console::PrintOut("Patched RIP-relative (no REX, opcode 0x%X) at: 0x%p\n",
                                opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
        // With REX (7-byte instructions)
        for (uintptr_t addr = start; addr <= end - 7; addr++) {
            uint8_t rex = *(uint8_t*)addr;
            if (rex >= 0x40 && rex <= 0x4F && *(uint8_t*)(addr + 1) == opcode) {
                uint8_t modrm = *(uint8_t*)(addr + 2);
                if ((modrm & 0xC7) == 0x05) {
                    int32_t disp = *reinterpret_cast<int32_t*>(addr + 3);
                    uintptr_t instrEnd = addr + 7;
                    if (instrEnd + disp == oldArrayAddr) {
                        int32_t newDisp = static_cast<int32_t>(newArrayAddr - instrEnd);
                        if (VirtualProtect((LPVOID)(addr + 3), sizeof(int32_t),
                            PAGE_EXECUTE_READWRITE, &oldProtect)) {
                            *reinterpret_cast<int32_t*>(addr + 3) = newDisp;
                            VirtualProtect((LPVOID)(addr + 3), sizeof(int32_t), oldProtect, &oldProtect);
                            Console::PrintOut("Patched RIP-relative (with REX, opcode 0x%X) at: 0x%p\n",
                                opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
    }

    // Scans executable sections to patch all references to the old BGM list address.
    static void AutoPatchListReferences(uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        HMODULE hModule = GetModuleHandle(nullptr);
        MODULEINFO modInfo = { 0 };
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
            Console::PrintErr("GetModuleInformation failed in AutoPatchListReferences.\n");
            return;
        }
        PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
        PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
            reinterpret_cast<uint8_t*>(hModule) + dosHeader->e_lfanew);
        PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeaders);
        for (unsigned i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++, section++) {
            if (section->Characteristics & IMAGE_SCN_MEM_EXECUTE) {
                uintptr_t secStart = reinterpret_cast<uintptr_t>(hModule) + section->VirtualAddress;
                uintptr_t secEnd = secStart + section->Misc.VirtualSize;
                Console::PrintOut("Scanning section %.8s: 0x%p - 0x%p\n",
                    section->Name, (void*)secStart, (void*)secEnd);
                PatchAbsoluteReferencesInRange(secStart, secEnd, oldArrayAddr, newArrayAddr);
                PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8D); // LEA
                PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8B); // MOV
            }
        }
    }

    // Expands the vanilla BGM list by copying all entries until the termination marker,
    // then allocating a new array and patching code references.
    static void ExpandProjectileList() {

        uintptr_t ProjectileArrayOffset = 0;
        int originalCount = 0;
        if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
        {
            ProjectileArrayOffset = offsetSC::OFF_PROJECTILEARRAY;
        }
        else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto Storm 4
        {
            ProjectileArrayOffset = offsetS4::OFF_PROJECTILEARRAY;
        }

        // Compute pointer to original array using byte-pointer arithmetic to avoid void* +/- int errors.
        ProjectileEntry* pOriginal = reinterpret_cast<ProjectileEntry*>(
            reinterpret_cast<uint8_t*>(moduleBase) + ProjectileArrayOffset - 0xC00);

        if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
            originalCount = 0x99;
        }
        else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
            originalCount = 0x99;
        }

        ProjectileExpander::ORIGINAL_COUNT = originalCount;
        ProjectileExpander::g_NewProjectileCountAllocated = originalCount + PROJECTILE_SLOT_COUNT;
        size_t newSize = static_cast<size_t>(ProjectileExpander::g_NewProjectileCountAllocated) * sizeof(ProjectileEntry);
        ProjectileExpander::g_pNewProjectileArray = reinterpret_cast<ProjectileEntry*>(
            AllocNearModule(reinterpret_cast<LPVOID>(moduleBase), newSize));
        if (!ProjectileExpander::g_pNewProjectileArray) {
            Console::PrintErr("Failed to allocate new Projectile list array.\n");
            return;
        }
        for (int i = 0; i < originalCount; i++) {
            ProjectileExpander::g_pNewProjectileArray[i] = pOriginal[i];
            Console::PrintOut("Copied Projectile entry %d: Name=%s\n", i, pOriginal[i].ProjectileName);
        }
        // Append termination entry.
        ProjectileExpander::g_pNewProjectileArray[originalCount].ProjectileName = 0;

        AutoPatchListReferences(reinterpret_cast<uintptr_t>(reinterpret_cast<uint8_t*>(moduleBase) + ProjectileArrayOffset - 0xC00),
            reinterpret_cast<uintptr_t>(ProjectileExpander::g_pNewProjectileArray));
        Console::PrintOut("Expanded Projectile list: new array at 0x%p, vanilla count = %d (allocated %d slots)\n",
            (void*)ProjectileExpander::g_pNewProjectileArray, originalCount, ProjectileExpander::g_NewProjectileCountAllocated);
    }

    static int GetCurrentProjectileCount() {
        int count = 0;
        if (!ProjectileExpander::g_pNewProjectileArray)
            return 0;
        while (count < ProjectileExpander::g_NewProjectileCountAllocated) {
            if (ProjectileExpander::g_pNewProjectileArray[count].ProjectileName == 0)
                break;
            count++;
        }
        return count;
    }

    // Reads custom Projectile entries from a file and appends them.
    // Each record is 0x40 bytes (as used below).
    static void ReadProjectileFile(const std::string& filename) {
        std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(filename);
        if (fileBytes.empty()) {
            Console::PrintErr("Failed to read file: %s\n", filename.c_str());
            return;
        }
        const size_t recordSize = 0x40;
        if (fileBytes.size() < recordSize) {
            Console::PrintErr("Invalid file size: 0x%X, expected at least 0x%X bytes for %s\n",
                static_cast<unsigned int>(fileBytes.size()), static_cast<unsigned int>(recordSize), filename.c_str());
            return;
        }

        int numEntries = static_cast<int>(fileBytes.size() / recordSize);
        if (!ProjectileExpander::g_pNewProjectileArray) {
            Console::PrintErr("Custom Projectile list array not allocated.\n");
            return;
        }

        //     (   )
        int currentCount = ProjectileExpander::GetCurrentProjectileCount();

        for (int i = 0; i < numEntries; ++i) {
            size_t offset = static_cast<size_t>(i) * recordSize;

            char projectileNameBuffer[0x41] = { 0 };
            memcpy(projectileNameBuffer, &fileBytes[offset], 0x40);
            projectileNameBuffer[0x40] = '\0';

            std::string projectileName(projectileNameBuffer);

            ProjectileEntry newEntry{};
            // allocate a C-string and store its address (uint64_t)
            char* stored = _strdup(projectileName.c_str());
            if (!stored) {
                Console::PrintErr("Failed to allocate memory for projectile name string.\n");
                break;
            }
            newEntry.ProjectileName = reinterpret_cast<uint64_t>(stored);

            // ensure capacity
            if (currentCount >= ProjectileExpander::g_NewProjectileCountAllocated - 1) {
                Console::PrintErr("Not enough space for custom Projectile entry at index %d\n", currentCount);
                // free allocated string to avoid leak
                free(stored);
                break;
            }
            ProjectileExpander::g_pNewProjectileArray[currentCount] = newEntry;
            Console::PrintOut("Added custom Projectile entry %d: %s\n", currentCount, (char*)newEntry.ProjectileName);
            ++currentCount;
        }

        // Append termination marker at currentCount
        int finalCount = currentCount;
        if (finalCount < ProjectileExpander::g_NewProjectileCountAllocated) {
            ProjectileExpander::g_pNewProjectileArray[finalCount].ProjectileName = 0;
        }

        Console::PrintOut("Custom Projectile entries appended. New total entries: %d\n", finalCount);
    }
};
