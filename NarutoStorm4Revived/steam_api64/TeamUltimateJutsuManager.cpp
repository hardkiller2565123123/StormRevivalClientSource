#include "TeamUltimateJutsuManager.h"
#include <windows.h>
#include <cstdint>
#include <cstring>
#include "Common.h"
#include "Offsets.h"
#include "PatternScan.h"
#include <iostream>
#include <cstdio>
#include <Psapi.h>
#include "mem.h"
#include <sstream>
#include <iomanip>
#include "Console.h"
#include "FileParser.h"
using namespace std;

//------------------------------------------------------------------------------
//    Team Ultimate Jutsu (TUJ) :
// 8    () + 4   unlockVal + 4  .
struct TeamUltimateEntry {
    char* name;      //  
    int   unlockVal; //  
    int   reserved;  //  ( 0)
};

int g_NewTUJCount = 0;
//------------------------------------------------------------------------------

uintptr_t OFFSET_TEAM_ULT_ARRAY = offsetSC::OFFSET_TEAM_ULT_ARRAY; //     off_1418B2470
int ORIGINAL_COUNT = offsetSC::ORIGINAL_COUNT_TEAM_ULT_ARRAY;
//constexpr int NEW_COUNT = 58;

//      () TUJ .
TeamUltimateEntry* g_pNewTeamUltimateArray = nullptr;

//------------------------------------------------------------------------------
//      size   2  baseAddr.
//         ,  nullptr.
LPVOID AllocNearModule(LPVOID base, SIZE_T size) {
    const uintptr_t TWO_GB = 0x80000000; // 2 
    uintptr_t baseAddr = reinterpret_cast<uintptr_t>(base);
    const uintptr_t PAGE_SIZE = 0x1000;

    //     base.
    for (int i = 0; i < 1000; i++) {
        uintptr_t candidate = baseAddr + i * PAGE_SIZE;
        if (candidate - baseAddr > TWO_GB)
            break;
        LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (addr)
            return addr;
    }
    //     base.
    for (int i = 1; i < 1000; i++) {
        if (baseAddr < i * PAGE_SIZE)
            break;
        uintptr_t candidate = baseAddr - i * PAGE_SIZE;
        if (baseAddr - candidate > TWO_GB)
            break;
        LPVOID addr = VirtualAlloc(reinterpret_cast<LPVOID>(candidate), size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
        if (addr)
            return addr;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
//    TUJ ,     (   ),
//          ORIGINAL_COUNT.
//void ExpandTeamUltimateArray_New() {
//    //     : plugin::moduleBase + OFFSET_TEAM_ULT_ARRAY.
//    TeamUltimateEntry* pOriginal = reinterpret_cast<TeamUltimateEntry*>(plugin::moduleBase + OFFSET_TEAM_ULT_ARRAY);
//
//    //    .
//    size_t newSize = NEW_COUNT * sizeof(TeamUltimateEntry);
//    //     plugin::moduleBase,     RIP-relative .
//    g_pNewTeamUltimateArray = reinterpret_cast<TeamUltimateEntry*>(
//        AllocNearModule(reinterpret_cast<LPVOID>(plugin::moduleBase), newSize)
//        );
//    if (!g_pNewTeamUltimateArray) {
//        condition::sub_1412528C0("Failed to allocate new TUJ array.\n");
//        return;
//    }
//
//    // Copy original 55 entries (indices 0..54)
//    memcpy(g_pNewTeamUltimateArray, pOriginal, ORIGINAL_COUNT * sizeof(TeamUltimateEntry));
//
//    // Clear the rest
//    memset(g_pNewTeamUltimateArray + ORIGINAL_COUNT, 0, (NEW_COUNT - ORIGINAL_COUNT) * sizeof(TeamUltimateEntry));
//
//    // Do NOT fill indices 55 and 56 (vanilla load will use count==55)
//    // Instead, only fill your custom entry at index 57:
//    g_pNewTeamUltimateArray[55].name = const_cast<char*>("skip");
//    g_pNewTeamUltimateArray[55].unlockVal = -1;
//    g_pNewTeamUltimateArray[55].reserved = 0;
//    g_pNewTeamUltimateArray[56].name = const_cast<char*>("skip");
//    g_pNewTeamUltimateArray[56].unlockVal = -1;
//    g_pNewTeamUltimateArray[56].reserved = 0;
//    g_pNewTeamUltimateArray[57].name = const_cast<char*>("test");
//    g_pNewTeamUltimateArray[57].unlockVal = -1;
//    g_pNewTeamUltimateArray[57].reserved = 0;
//
//
//    
//
//}

//------------------------------------------------------------------------------
// Helper:    [start, end)          .
//     condition::sub_1412528C0.
void PatchAllOccurrencesInRange(uintptr_t start, uintptr_t end, uintptr_t oldValue, uintptr_t newValue) {
    for (uintptr_t addr = start; addr < end - sizeof(uintptr_t); addr++) {
        if (*reinterpret_cast<uintptr_t*>(addr) == oldValue) {
            DWORD oldProtect;
            if (VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                *reinterpret_cast<uintptr_t*>(addr) = newValue;
                VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), oldProtect, &oldProtect);
                Console::PrintOut("Patched address: 0x%p, exe: 0x%p\n", (void*)addr, (void*)(addr - moduleBase));
            }
            else {
                Console::PrintErr("Failed to change protection for patch at 0x%p, exe: 0x%p\n", (void*)addr, (void*)(addr - moduleBase));
            }
        }
    }
}

//------------------------------------------------------------------------------
//      [start, end).
void PatchAbsoluteReferencesInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
    for (uintptr_t addr = start; addr <= end - sizeof(uintptr_t); addr++) {
        if (*reinterpret_cast<uintptr_t*>(addr) == oldArrayAddr) {
            DWORD oldProtect;
            if (VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                *reinterpret_cast<uintptr_t*>(addr) = newArrayAddr;
                VirtualProtect(reinterpret_cast<LPVOID>(addr), sizeof(uintptr_t), oldProtect, &oldProtect);
                Console::PrintOut("Patched absolute ref at: 0x%p, exe: 0x%p\n", (void*)addr, (void*)(addr-moduleBase));
            }
            else {
                Console::PrintErr("Failed to change protection at: 0x%p, exe: 0x%p\n", (void*)addr, (void*)(addr - moduleBase));
            }
        }
    }
}

//------------------------------------------------------------------------------
//     RIP-relative  (LEA  MOV),  32- .
//    REX (6 )   REX (7 ). 'opcode'   0x8D (LEA)  0x8B (MOV).
void PatchRelativeInstrInRange(uintptr_t start, uintptr_t end, uintptr_t oldArrayAddr, uintptr_t newArrayAddr, uint8_t opcode) {
    DWORD oldProtect;
    // ---  1:  REX (  = 6 ) ---
    for (uintptr_t addr = start; addr <= end - 6; addr++) {
        if (*(uint8_t*)addr == opcode) {
            uint8_t modrm = *(uint8_t*)(addr + 1);
            //  RIP-relative : mod == 00  r/m == 101.
            if ((modrm & 0xC7) == 0x05) {
                int32_t disp = *reinterpret_cast<int32_t*>(addr + 2);
                uintptr_t instrEnd = addr + 6;
                if (instrEnd + disp == oldArrayAddr) {
                    int32_t newDisp = static_cast<int32_t>(newArrayAddr - instrEnd);
                    if (VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                        *reinterpret_cast<int32_t*>(addr + 2) = newDisp;
                        VirtualProtect((LPVOID)(addr + 2), sizeof(int32_t), oldProtect, &oldProtect);
                        Console::PrintOut("Patched RIP-relative (no REX, opcode 0x%X) at: 0x%p, exe: 0x%p\n", opcode, (void*)addr, (void*)(addr - moduleBase));
                    }
                    else {
                        Console::PrintErr("Failed to change protection at: 0x%p, exe: 0x%p\n", (void*)addr, (void*)(addr - moduleBase));
                    }
                }
            }
        }
    }
    // ---  2:  REX (  = 7 ) ---
    for (uintptr_t addr = start; addr <= end - 7; addr++) {
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

                        Console::PrintOut("Old array address: 0x%p, New array address: 0x%p\n",
                            (void*)oldArrayAddr, (void*)newArrayAddr);

                    }
                    else {
                        Console::PrintErr("Failed to change protection at: 0x%p\n", (void*)addr);
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
//            .
void AutoPatchTUJReferences(uintptr_t oldArrayAddr, uintptr_t newArrayAddr) {
    HMODULE hModule = GetModuleHandle(nullptr); //  EXE
    MODULEINFO modInfo = { 0 };
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
        Console::PrintErr("GetModuleInformation failed.\n");
        return;
    }
    //    PE.
    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
    PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(
        reinterpret_cast<uint8_t*>(hModule) + dosHeader->e_lfanew);
    PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(ntHeaders);
    for (unsigned i = 0; i < ntHeaders->FileHeader.NumberOfSections; i++, section++) {
        if (section->Characteristics & IMAGE_SCN_MEM_EXECUTE) {
            uintptr_t secStart = reinterpret_cast<uintptr_t>(hModule) + section->VirtualAddress;
            uintptr_t secEnd = secStart + section->Misc.VirtualSize;
            Console::PrintOutW("Scanning section %.8s: 0x%p - 0x%p\n", section->Name, (void*)secStart, (void*)secEnd);
            PatchAbsoluteReferencesInRange(secStart, secEnd, oldArrayAddr, newArrayAddr);
            PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8D); // LEA
            PatchRelativeInstrInRange(secStart, secEnd, oldArrayAddr, newArrayAddr, 0x8B); // MOV
        }
    }
}

void Patch8BitImmediateConstant(uint8_t oldVal, uint8_t newVal) {
    HMODULE hModule = GetModuleHandle(nullptr);
    if (!hModule) {
        Console::PrintErr("Patch8BitImmediateConstant: GetModuleHandle returned NULL\n");
        return;
    }

    MODULEINFO modInfo = { 0 };
    if (!GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(modInfo))) {
        Console::PrintErr("GetModuleInformation failed (Patch8BitImmediateConstant).\n");
        return;
    }

    uintptr_t moduleStart = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
    uintptr_t moduleEnd = moduleStart + static_cast<uintptr_t>(modInfo.SizeOfImage);

    // Scan the module for either pattern:
    // 41 83 FF <imm>  OR   41 83 FE <imm>
    bool patched = false;
    for (uintptr_t addr = moduleStart; addr + 3 < moduleEnd; ++addr) {
        uint8_t b0 = *(uint8_t*)(addr);
        uint8_t b1 = *(uint8_t*)(addr + 1);
        uint8_t b2 = *(uint8_t*)(addr + 2);
        uint8_t b3 = *(uint8_t*)(addr + 3);

        if (b0 == 0x41 && b1 == 0x83 && (b2 == 0xFF || b2 == 0xFE) && b3 == oldVal) {
            DWORD oldProtect;
            if (VirtualProtect(reinterpret_cast<LPVOID>(addr + 3), 1, PAGE_EXECUTE_READWRITE, &oldProtect)) {
                *(uint8_t*)(addr + 3) = newVal;
                // restore protection
                VirtualProtect(reinterpret_cast<LPVOID>(addr + 3), 1, oldProtect, &oldProtect);
                // ensure CPU sees the updated instruction
                FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<LPCVOID>(addr + 3), 1);

                Console::PrintOut("Patched 8-bit immediate at: 0x%p: 0x%02X -> 0x%02X\n",
                    (void*)(addr + 3), oldVal, newVal);
                patched = true;
                break; // keep behavior: patch first match only
            }
            else {
                Console::PrintErr("VirtualProtect failed at 0x%p\n", (void*)(addr + 3));
            }
        }
    }

    if (!patched) {
        Console::PrintErr("Patch8BitImmediateConstant: no matching pattern found for 0x%02X\n", oldVal);
    }
}


std::string GetAllocationString() {
    // Calculate allocation value, e.g. 55 * 0x48 = 0xF78
    unsigned int allocValue = ORIGINAL_COUNT * 0x48;
    char buf[9] = { 0 };
    // Format each byte as two hex digits in little-endian order.
    sprintf(buf, "%02X%02X%02X%02X",
        allocValue & 0xFF,
        (allocValue >> 8) & 0xFF,
        (allocValue >> 16) & 0xFF,
        (allocValue >> 24) & 0xFF);
    return std::string(buf);
}
std::string DecimalToHex(int value) {
    std::stringstream stream;
    stream << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << value;
    return stream.str();
}

//------------------------------------------------------------------------------
// TUJManager::ExpandTeamUltimateArray:
// 1.      .
// 2.         .
// 3.   .



void TUJManager::ExpandTeamUltimateArray() {
    //ExpandTeamUltimateArray_New();
    if (!g_pNewTeamUltimateArray) {
        Console::PrintErr("New TUJ array not allocated; aborting patch.\n");
        return;
    }
    uintptr_t TUJ_Address = 0;
    int originalCount = 0;
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
    {
        __int64 TUJ_Address = PatternScan::Scan("48xxxxxxxx48xxxxxxxx48xxxxxxxx5541xx41xx41xx41xx48xxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxx4Cxxxx48xxxxxxxx48xxxxFFxxxx9041xxxxxxxxxx48xxxxxxxxxxxxb9xxxxxxxx");

        OFFSET_TEAM_ULT_ARRAY = offsetSC::OFFSET_TEAM_ULT_ARRAY;
        ORIGINAL_COUNT = offsetSC::ORIGINAL_COUNT_TEAM_ULT_ARRAY;
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
    {
        __int64 TUJ_Address = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx48xxxxxx5541xx41xx41xx41xx48xxxxxx48xxxxxxxxxxxx48xxxx48xxxxFFxxxxBBxxxxxxxx48xxxxxxxxxxxx8Bxx41xxxxxxxxxxE8xxxxxxxx");

        OFFSET_TEAM_ULT_ARRAY = offsetS4::OFFSET_TEAM_ULT_ARRAY;
        ORIGINAL_COUNT = offsetS4::ORIGINAL_COUNT_TEAM_ULT_ARRAY;
    }


    uintptr_t oldArrayAddr = moduleBase + OFFSET_TEAM_ULT_ARRAY - 0xC00;
    uintptr_t newArrayAddr = reinterpret_cast<uintptr_t>(g_pNewTeamUltimateArray);
    AutoPatchTUJReferences(oldArrayAddr, newArrayAddr);
    Patch8BitImmediateConstant(ORIGINAL_COUNT, g_NewTUJCount);
    //Patch8BitImmediateConstant(ORIGINAL_COUNT-1, g_NewTUJCount-1);

    __int64 MemoryAlloc_Address_1 = 0x660DEF + moduleBase;
    __int64 MemoryAlloc_Address_2 = 0x660E03 + moduleBase;

    const std::array<std::uint8_t, 4> NewMemoryAllocationBytes{
        static_cast<std::uint8_t>((g_NewTUJCount * 0x48) & 0xFF),
        static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 8) & 0xFF),
        static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 16) & 0xFF),
        static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 24) & 0xFF)
    };

    util::memory::mem::write_bytes(MemoryAlloc_Address_1, NewMemoryAllocationBytes);
    util::memory::mem::write_bytes(MemoryAlloc_Address_2, NewMemoryAllocationBytes);


    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
        std::string hexTUJCountStr = DecimalToHex(ORIGINAL_COUNT - 1);
        std::string hexTUJCountStr2 = DecimalToHex(ORIGINAL_COUNT);
        const char* hexTUJCount = hexTUJCountStr.c_str();
        const char* hexTUJCount2 = hexTUJCountStr2.c_str();

        const std::array<std::uint8_t, 1> TUJCountByte{ g_NewTUJCount - 1 };
        const std::array<std::uint8_t, 1> TUJCountByte2{ g_NewTUJCount };
        __int64 MemoryAlloc_Address_1 = 0x660DEF + moduleBase;
        __int64 MemoryAlloc_Address_2 = 0x660E03 + moduleBase;

        const std::array<std::uint8_t, 4> NewMemoryAllocationBytes{
            static_cast<std::uint8_t>((g_NewTUJCount * 0x48) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 8) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 16) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 24) & 0xFF)
        };

        util::memory::mem::write_bytes(MemoryAlloc_Address_1, NewMemoryAllocationBytes);
        util::memory::mem::write_bytes(MemoryAlloc_Address_2, NewMemoryAllocationBytes);
        __int64 TUJ_Address2 = PatternScan::Scan("48xxxxxx4Cxxxxxx48xxxxxx49xxxx74xx39xxxx74xx48xxxxxx49xxxx75xx33xx48xxxxxxC348xxxxxx48xxxxxxxx48xxxxxxxx83xxxx77xx48xxxx48xxxxxxxxxxxx48xxxx8Bxxxxxx8Bxxxxxx83xxxx74xxE8xxxxxxxx3Bxx7Cxx48xxxxxxxxxxxx");
        //Console::PrintErr("TUJ_Address2 offset: %lld\n", TUJ_Address2 - moduleBase);

        __int64 TUJ_CountAddress2 = PatternScan::Scan("83xx" + std::string(hexTUJCount) + "77xx49xxxx", TUJ_Address2) + 2;
        util::memory::mem::write_bytes(TUJ_CountAddress2, TUJCountByte);
        //std::cout << "0x" << std::hex << TUJ_CountAddress2 << std::dec << std::endl;
        //Console::PrintErr("TUJ_CountAddress2 offset: %lld\n", TUJ_CountAddress2 - moduleBase);

        __int64 TUJ_Address3 = PatternScan::Scan("48xxxxxxxx48xxxxxxxx5748xxxxxx4Cxxxx48xxxx74xx33xx48xxxxxxxxxxxx44xxxx48xxxxxxxxxxxx4Cxxxx0Fxxxx4Dxxxx49xxxx4Dxxxx0Fxxxxxxxxxxxx0Fxxxx");
        __int64 TUJ_CountAddress3 = PatternScan::Scan("41xxxx" + std::string(hexTUJCount) + "77xx49xxxx", TUJ_Address3) + 3;
        util::memory::mem::write_bytes(TUJ_CountAddress3, TUJCountByte);
        //std::cout << "0x" << std::hex << TUJ_CountAddress3 << std::dec << std::endl;
        //Console::PrintErr("TUJ_CountAddress3 offset: %lld\n", TUJ_CountAddress3 - moduleBase);

        __int64 TUJ_Address4 = PatternScan::Scan("48xxxxxxxx5748xxxxxx83xxxx77xx48xxxxxxxxxxxx48xxxx48xxxx8Bxxxxxx8Bxxxxxx83xxxx74xxE8xxxxxxxx3Bxx7Cxx48xxxxxxxxxxxx8BxxE8xxxxxxxx85xx74xx");
        __int64 TUJ_CountAddress4 = PatternScan::Scan("83xx" + std::string(hexTUJCount) + "77xx48xxxxxxxxxxxx48xxxx", TUJ_Address4) + 2;
        util::memory::mem::write_bytes(TUJ_CountAddress4, TUJCountByte);
        //Console::PrintErr("TUJ_CountAddress4 offset: %lld\n", TUJ_CountAddress4 - moduleBase);
        //std::cout << "0x" << std::hex << TUJ_CountAddress4 << std::dec << std::endl;

        __int64 TUJ_Address5 = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxxxx48xxxxxxxxxxxxxx48xxxxxxxx49xxxx48xxxx72xx48xxxx48xxxxxxxxxxxxC6xxxx48xxxxE8xxxxxxxx49xxxxxxxxxxxx9049xxxx");
        __int64 TUJ_CountAddress5 = PatternScan::Scan("B8" + std::string(hexTUJCount2) + "000000C3", TUJ_Address5) + 1;
        util::memory::mem::write_bytes(TUJ_CountAddress5, TUJCountByte2);
        //Console::PrintErr("TUJ_CountAddress5 offset: %lld\n", TUJ_CountAddress5 - moduleBase);
        //::cout << "0x" << std::hex << TUJ_CountAddress5 << std::dec << std::endl;

    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        __int64 MemoryAlloc_Address_3 = 0x58F90D + moduleBase;

        const std::array<std::uint8_t, 4> NewMemoryAllocationBytes2{
            static_cast<std::uint8_t>((g_NewTUJCount * 0x48) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 8) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 16) & 0xFF),
            static_cast<std::uint8_t>(((g_NewTUJCount * 0x48) >> 24) & 0xFF)
        };

        util::memory::mem::write_bytes(MemoryAlloc_Address_3, NewMemoryAllocationBytes2);
        const std::array<std::uint8_t, 1> TUJCountByte{ g_NewTUJCount - 1 };
        const std::array<std::uint8_t, 1> TUJCountByte2{ g_NewTUJCount };
        //util::memory::mem::write_bytes(moduleBase + 0x516AC9, TUJCountByte2);

        std::string hexTUJCountStr = DecimalToHex(ORIGINAL_COUNT - 1);
        std::string hexTUJCountStr2 = DecimalToHex(ORIGINAL_COUNT);
        const char* hexTUJCount = hexTUJCountStr.c_str();
        const char* hexTUJCount2 = hexTUJCountStr2.c_str();


        __int64 TUJ_Address5 = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxxxx48xxxxxxxxxxxxxx48xxxxxxxx49xxxx48xxxx72xx48xxxx48xxxxxxxxxxxxC6xxxx48xxxxE8xxxxxxxx49xxxxxxxxxxxx9049xxxx");
        __int64 TUJ_CountAddress5 = PatternScan::Scan("B8" + std::string(hexTUJCount2) + "000000C3", TUJ_Address5) + 1;
        util::memory::mem::write_bytes(TUJ_CountAddress5, TUJCountByte2);
        Console::PrintErr("TUJ_CountAddress5 offset: %lld\n", TUJ_CountAddress5 - moduleBase);
    }



    Console::PrintOut("AutoPatch: New TUJ array at 0x%p, count = %d\n", g_pNewTeamUltimateArray, g_NewTUJCount);
    Console::PrintOut("AutoPatch: Old TUJ array at 0x%p\n", oldArrayAddr);
}




// Reads pairSpSkillManagerParam.xfbin and builds a new TUJ array.
void TUJManager::ReadPairSpSkillManagerParam(std::string _file)
{
    std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(_file);
    if (fileBytes.empty())
    {
        Console::PrintErr("Failed to read file: %s\n", _file.c_str());
        return;
    }
    // If file size is off by one, remove the extra byte.
    if (fileBytes.size() % 0x18 != 0)
    {
        if ((fileBytes.size() - 1) % 0x18 == 0)
        {
            fileBytes.pop_back();
        }
        else
        {
            Console::PrintErr("Invalid file size: %d for %s\n", fileBytes.size(), _file.c_str());
            return;
        }
    }

    g_NewTUJCount = static_cast<int>(fileBytes.size() / 0x18);
    size_t newSize = g_NewTUJCount * sizeof(TeamUltimateEntry);
    g_pNewTeamUltimateArray = reinterpret_cast<TeamUltimateEntry*>(
        AllocNearModule(reinterpret_cast<LPVOID>(moduleBase), newSize)
        );
    if (!g_pNewTeamUltimateArray)
    {
        Console::PrintErr("Failed to allocate new TUJ array from file.\n");
        return;
    }
    for (int i = 0; i < g_NewTUJCount; i++)
    {
        int offset = i * 0x18;
        char nameBuffer[0x11] = { 0 };
        memcpy(nameBuffer, &fileBytes[offset], 0x10);
        // Allocate and copy the name string (ensuring null termination)
        size_t nameLen = strnlen(nameBuffer, 0x10);
        char* nameStr = new char[nameLen + 1];
        memcpy(nameStr, nameBuffer, nameLen);
        nameStr[nameLen] = '\0';
        g_pNewTeamUltimateArray[i].name = nameStr;
        g_pNewTeamUltimateArray[i].unlockVal = *reinterpret_cast<int*>(&fileBytes[offset + 0x10]);
        g_pNewTeamUltimateArray[i].reserved = *reinterpret_cast<int*>(&fileBytes[offset + 0x14]);
        Console::PrintOutW("Entry at index %d: { name = %s, unlockVal = %d, reserved = %d }\n",
            i,
            g_pNewTeamUltimateArray[i].name,
            g_pNewTeamUltimateArray[i].unlockVal,
            g_pNewTeamUltimateArray[i].reserved);

    }

    Console::PrintOut("Loaded %d TUJ entries from %s\n", g_NewTUJCount, _file.c_str());
}

//Unlock code NSC
TUJManager::orig_sub_140661ED0_t TUJManager::orig_sub_140661ED0 = nullptr;
bool __fastcall TUJManager::sub_140661ED0(__int64 a1, __int64* a2, int a3)
{
    __int64 v3; // rbx
    char* v6; // rax
    __int64 v7; // r9
    bool result; // rax

    typedef  char* (__fastcall* sub_140662100_f)(__int64 a1, int a2);
    sub_140662100_f sub_140662100 = (sub_140662100_f)(moduleBase+0x661500);
    typedef  __int64* (__fastcall* sub_140661F60_f)(__int64 a1, __int64* a2, char* a3);
    sub_140661F60_f sub_140661F60 = (sub_140661F60_f)(moduleBase + 0x661360);
    typedef  __int64(__fastcall* sub_140586480_f)();
    sub_140586480_f sub_140586480 = (sub_140586480_f)(moduleBase + 0x585880);
    v3 = a3;
    v6 = sub_140662100(a1, a3);
    v7 = -1i64;
    do
        ++v7;
    while (v6[v7]);

    //Console::PrintErr("Ult String %s\n", v6);
    result = 0;
    if ((int)v7)
    {
        sub_140661F60(a1, a2, v6);
        if ((int)sub_140586480() >= g_pNewTeamUltimateArray[v3].unlockVal)
            return 1;
    }
    return result;
}

//Unlock code NS4
TUJManager::orig_sub_140590818_t TUJManager::orig_sub_140590818 = nullptr;
bool __fastcall TUJManager::sub_140590818(__int64 a1, __int64* a2, int a3)
{
    __int64 v3; // rbx
    char* v6; // rax
    __int64 v7; // r9
    bool result; // rax

    typedef  char* (__fastcall* sub_140662100_f)(__int64 a1, int a2);
    sub_140662100_f sub_140662100 = (sub_140662100_f)(moduleBase + 0x58F6E0);
    typedef  __int64* (__fastcall* sub_140661F60_f)(__int64 a1, __int64* a2, char* a3);
    sub_140661F60_f sub_140661F60 = (sub_140661F60_f)(moduleBase + 0x58FC9C);
    typedef  __int64(__fastcall* sub_140586480_f)();
    sub_140586480_f sub_140586480 = (sub_140586480_f)(moduleBase + 0x861AC0);
    v3 = a3;
    v6 = sub_140662100(a1, a3);
    v7 = -1i64;
    do
        ++v7;
    while (v6[v7]);

    //Console::PrintErr("Ult String %s\n", v6);
    result = 0;
    if ((int)v7)
    {
        sub_140661F60(a1, a2, v6);
        if ((int)sub_140586480() >= g_pNewTeamUltimateArray[v3].unlockVal)
            return 1;
    }
    return result;
}