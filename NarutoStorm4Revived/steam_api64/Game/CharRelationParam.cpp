#pragma once
#include <windows.h>
#include <cstdint>
#include <vector>
#include <cstring>
#include <Psapi.h>
#include "Console.h"
#include "FileParser.h"
#include "Common.h"
#include "PatternScan.h"
#include "mem.h"

//      CharRelation   (16 ).
// [0..7] =    uint32_t ( ID)
// [8..15] =   (uint64_t;  32    count)
struct CharRelationEntryMem {
    uint64_t idListPointer;
    uint64_t idCount;
};

class CharRelationExpander {
public:
    static inline CharRelationEntryMem* g_pNewCharRelationArray = nullptr;
    static inline int ORIGINAL_COUNT = 0;
    static inline int g_NewCharRelationCountAllocated = 0;
    static inline int CharRelation_SLOT_COUNT = 1000;

    //      2GB  base ( RIP-relative   ).
    static LPVOID AllocNearModule(LPVOID base, SIZE_T size) {
        const uintptr_t TWO_GB = 0x80000000u;
        uintptr_t baseAddr = reinterpret_cast<uintptr_t>(base);
        const uintptr_t PAGE_SIZE = 0x1000;
        //  
        for (int i = 0; i < 1000; ++i) {
            uintptr_t candidate = baseAddr + i * PAGE_SIZE;
            if (candidate - baseAddr > TWO_GB) break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr) return addr;
        }
        //  
        for (int i = 1; i < 1000; ++i) {
            if (baseAddr < i * PAGE_SIZE) break;
            uintptr_t candidate = baseAddr - i * PAGE_SIZE;
            if (baseAddr - candidate > TWO_GB) break;
            LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
            if (addr) return addr;
        }
        return nullptr;
    }

    //    ( mov imm64 / data pointers)
    static void PatchAbsoluteReferencesInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        for (uintptr_t addr = start; addr <= end - sizeof(uintptr_t); ++addr) {
            if (*reinterpret_cast<uintptr_t*>(addr) == oldArrayAddr) {
                DWORD oldProtect;
                if (VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
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

    //  RIP-relative LEA/MOV (: LEA=0x8D, MOV=0x8B)      BGM-.
    static void PatchRelativeInstrInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr, uint8_t opcode) {
        DWORD oldProtect;
        //  REX (6-)
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
                            Console::PrintOut("Patched RIP-relative (no REX, opcode 0x%X) at: 0x%p\n", opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
        //  REX (7-)
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
                            Console::PrintOut("Patched RIP-relative (with REX, opcode 0x%X) at: 0x%p\n", opcode, (void*)addr);
                        }
                        else {
                            Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                        }
                    }
                }
            }
        }
    }

    //           .
    static void AutoPatchCharRelationReferences(uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
        HMODULE hModule = GetModuleHandle(nullptr);
        MODULEINFO modInfo = { 0 };
        if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
            Console::PrintErr("GetModuleInformation failed in AutoPatchCharRelationReferences.\n");
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

    //     (:   idListPointer==0  idCount==0).
    static int GetCurrentCharRelationCount(CharRelationEntryMem* sourceArray, int maxScan = 10000) {
        int count = 0;

        MODULEINFO mi = { 0 };
        HMODULE h = GetModuleHandle(nullptr);
        GetModuleInformation(GetCurrentProcess(), h, &mi, sizeof(mi));
        uintptr_t modStart = reinterpret_cast<uintptr_t>(h);
        uintptr_t modEnd = modStart + mi.SizeOfImage;

        while (count < maxScan) {
            uint64_t ptr = sourceArray[count].idListPointer;
            uint64_t c = sourceArray[count].idCount;

            // :  qword == 0
            if (ptr == 0 && c == 0) break;

            // sanity:  ptr          
            if (ptr != 0) {
                if ((ptr & 0x3) != 0) break;                      //    
                if (ptr < modStart || ptr >= modEnd + 0x1000000) break; //   
            }

            // sanity:  c     
            if (c > 10000) break;

            ++count;
        }
        return count;
    }

    //      ID    ,  .
    //  `OFF_CHARRELATION`    RVA/offset',     BGM.
    static void ExpandCharRelationList(uintptr_t OFF_CHARRELATION) {
        if (g_pNewCharRelationArray != nullptr) {
            Console::PrintOut("CharRelation array already expanded.\n");
            return;
        }

        //    (     -0xC00,   BGM).
        CharRelationEntryMem* pOriginal = reinterpret_cast<CharRelationEntryMem*>(moduleBase + OFF_CHARRELATION - 0xC00);

        //   
        int originalCount = GetCurrentCharRelationCount(pOriginal, 10000);
        if (originalCount <= 0) {
            Console::PrintErr("Failed to determine original CharRelation count or zero entries.\n");
            return;
        }
        ORIGINAL_COUNT = originalCount;
        g_NewCharRelationCountAllocated = originalCount + CharRelation_SLOT_COUNT;
        size_t newArraySize = static_cast<size_t>(g_NewCharRelationCountAllocated) * sizeof(CharRelationEntryMem);
        g_pNewCharRelationArray = reinterpret_cast<CharRelationEntryMem*>(AllocNearModule(reinterpret_cast<LPVOID>(moduleBase), newArraySize));
        if (!g_pNewCharRelationArray) {
            Console::PrintErr("Failed to allocate new CharRelation array.\n");
            return;
        }

        //        ID       exe.
        for (int i = 0; i < originalCount; ++i) {
            g_pNewCharRelationArray[i].idCount = pOriginal[i].idCount;
            uint64_t origListPtr = pOriginal[i].idListPointer;
            uint64_t count = pOriginal[i].idCount;
            if (origListPtr != 0 && count > 0) {
                //   ID (count * 4 )
                uint32_t* newIdList = reinterpret_cast<uint32_t*>(VirtualAlloc(nullptr, static_cast<SIZE_T>(count) * sizeof(uint32_t), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
                if (newIdList == nullptr) {
                    Console::PrintErr("Failed to allocate id list for index %d (count=%llu)\n", i, (unsigned long long)count);
                    //    
                    g_pNewCharRelationArray[i].idListPointer = 0;
                    g_pNewCharRelationArray[i].idCount = 0;
                    continue;
                }
                //     (,     uint32_t )
                memcpy(newIdList, reinterpret_cast<void*>(static_cast<uintptr_t>(origListPtr)), static_cast<SIZE_T>(count) * sizeof(uint32_t));
                g_pNewCharRelationArray[i].idListPointer = reinterpret_cast<uint64_t>(newIdList);
            }
            else {
                g_pNewCharRelationArray[i].idListPointer = 0;
            }
            Console::PrintOut("Copied CharRelation entry %d: list=0x%p count=%llu\n", i, (void*)g_pNewCharRelationArray[i].idListPointer, (unsigned long long)g_pNewCharRelationArray[i].idCount);
        }

        //  
        int terminatorIndex = originalCount;
        if (terminatorIndex < g_NewCharRelationCountAllocated) {
            g_pNewCharRelationArray[terminatorIndex].idListPointer = 0;
            g_pNewCharRelationArray[terminatorIndex].idCount = 0;
        }



        //     ,     .
        uintptr_t oldArrayAddr = reinterpret_cast<uintptr_t>(pOriginal);
        uintptr_t newArrayAddr = reinterpret_cast<uintptr_t>(g_pNewCharRelationArray);
        AutoPatchCharRelationReferences(oldArrayAddr, newArrayAddr);

        Console::PrintOut("Expanded CharRelation list: new array at 0x%p, vanilla count = %d (allocated %d slots)\n",
            g_pNewCharRelationArray, originalCount, g_NewCharRelationCountAllocated);
    }

    //           .
    //  :
    // [record0] [record1] ...
    // record: uint32_t count, then count * uint32_t ids
    static void ReadCharRelationFile(const std::string& filename) {
        if (!g_pNewCharRelationArray) {
            Console::PrintErr("Custom CharRelation array not allocated. Call ExpandCharRelationList first.\n");
            return;
        }
        std::vector<uint8_t> bytes = FileParser::ReadAllBytes(filename);
        if (bytes.empty()) {
            Console::PrintErr("Failed to read file: %s\n", filename.c_str());
            return;
        }
        size_t offset = 0;
        int currentCount = GetCurrentCharRelationCount(g_pNewCharRelationArray, g_NewCharRelationCountAllocated);
        while (offset + sizeof(uint32_t) <= bytes.size()) {
            if (currentCount >= g_NewCharRelationCountAllocated - 1) {
                Console::PrintErr("No more space to add custom CharRelation entries.\n");
                break;
            }
            uint32_t count = *reinterpret_cast<uint32_t*>(&bytes[offset]);
            offset += sizeof(uint32_t);
            if (count == 0) {
                //    
                g_pNewCharRelationArray[currentCount].idCount = 0;
                g_pNewCharRelationArray[currentCount].idListPointer = 0;
                Console::PrintOut("Added custom empty entry at index %d\n", currentCount);
                ++currentCount;
                continue;
            }
            size_t needed = static_cast<size_t>(count) * sizeof(uint32_t);
            if (offset + needed > bytes.size()) {
                Console::PrintErr("Malformed file: not enough bytes for %u ids at offset 0x%zX\n", count, offset);
                break;
            }
            uint32_t* newIdList = reinterpret_cast<uint32_t*>(VirtualAlloc(nullptr, needed, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
            if (!newIdList) {
                Console::PrintErr("Failed to allocate id list for custom entry (count=%u)\n", count);
                break;
            }
            memcpy(newIdList, &bytes[offset], needed);
            offset += needed;
            g_pNewCharRelationArray[currentCount].idListPointer = reinterpret_cast<uint64_t>(newIdList);
            g_pNewCharRelationArray[currentCount].idCount = count;
            Console::PrintOut("Added custom CharRelation entry %d: list=0x%p count=%u\n", currentCount, (void*)newIdList, count);
            ++currentCount;
        }
        const std::array<std::uint8_t, 1> CountByte{ static_cast<std::uint8_t>(currentCount) };
        if (GameVersion && (std::strcmp(GameVersion, "1.60") == 0)) {
            util::memory::mem::write_bytes(moduleBase + 0x592356, CountByte);
            util::memory::mem::write_bytes(moduleBase + 0x5916E8, CountByte);
        }
        /*else if (GameVersion && (std::strcmp(GameVersion, "1.09") == 0)) {

            util::memory::mem::write_bytes(moduleBase + 0x592356, CountByte);
            util::memory::mem::write_bytes(moduleBase + 0x5916E8, CountByte);
        }*/
        //  
        if (currentCount < g_NewCharRelationCountAllocated) {
            g_pNewCharRelationArray[currentCount].idListPointer = 0;
            g_pNewCharRelationArray[currentCount].idCount = 0;
        }
        Console::PrintOut("Finished reading custom CharRelation file. New total entries (before terminator): %d\n", currentCount);
    }
};
