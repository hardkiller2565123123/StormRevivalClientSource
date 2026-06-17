#include <cstdint>
#include "OugiAwakeningParam.h"
#include "Common.h"
#include "Console.h"
#include "mem.h"
#include "FileParser.h"

OugiAwakeningParam::orig_sub_1407D3A64_S4_t OugiAwakeningParam::orig_sub_1407D3A64_S4 = nullptr;
OugiAwakeningParam::orig_sub_140A0E010_SC_t OugiAwakeningParam::orig_sub_140A0E010_SC = nullptr;

std::unordered_set<uint32_t> OugiAwakeningParam::s_ougiCharIDs;
std::vector<uint32_t> OugiAwakeningParam::s_ougiCharIDList;
std::mutex OugiAwakeningParam::s_ougiCharIDsMutex;

static bool PatchBytes(uintptr_t address, const uint8_t* bytes, size_t len, std::uint8_t* out_original = nullptr)
{
    if (len == 0) return false;
    BYTE* dest = reinterpret_cast<BYTE*>(address);
    DWORD oldProt = 0;
    if (!VirtualProtect(dest, len, PAGE_EXECUTE_READWRITE, &oldProt))
        return false;

    if (out_original)
        memcpy(out_original, dest, len);

    memcpy(dest, bytes, len);

    // restore protection
    DWORD tmp;
    VirtualProtect(dest, len, oldProt, &tmp);

    // ensure CPU instruction cache is updated
    FlushInstructionCache(GetCurrentProcess(), dest, len);
    return true;
}

void OugiAwakeningParam::ReadOugiAwakeningParamFile(const std::string& filename)
{
    std::vector<uint8_t> bytes = FileParser::ReadAllBytes(filename);
    if (bytes.empty()) {
        Console::PrintErr("OugiAwakeningParam: Failed to read file: %s\n", filename.c_str());
        return;
    }

    if (bytes.size() % sizeof(uint32_t) != 0) {
        Console::PrintErr("OugiAwakeningParam: Malformed file (size not multiple of 4): %zu\n", bytes.size());
        return;
    }

    const size_t count = bytes.size() / sizeof(uint32_t);
    std::unordered_set<uint32_t> tmpSet;
    std::vector<uint32_t> tmpList;
    tmpSet.reserve(count);
    tmpList.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        //  little-endian 32-bit
        uint32_t val = 0;
        //   4 
        std::memcpy(&val, &bytes[i * 4], sizeof(uint32_t));
        //   little-endian   .   .
        tmpSet.insert(val);
        tmpList.push_back(val);
    }

    {
        std::lock_guard<std::mutex> lock(s_ougiCharIDsMutex);
        s_ougiCharIDs.swap(tmpSet);
        s_ougiCharIDList.swap(tmpList);
    }

    Console::PrintOut("OugiAwakeningParam: Loaded %zu character IDs from %s\n", s_ougiCharIDList.size(), filename.c_str());
}

bool OugiAwakeningParam::IsOugiAwakeningCharID(uint32_t id)
{
    std::lock_guard<std::mutex> lock(s_ougiCharIDsMutex);
    return s_ougiCharIDs.find(id) != s_ougiCharIDs.end();
}


//This function unlock chakra load action
__int64 __fastcall OugiAwakeningParam::sub_1407D3A64_S4(__int64 a1, __int64 a2)
{
    unsigned int v2 = 1;


    if (OugiAwakeningParam::orig_sub_1407D3A64_S4)
        v2 = OugiAwakeningParam::orig_sub_1407D3A64_S4(a1, a2);

    // Patch once per process run
    static bool patched = false;
    static std::array<uint8_t, 6> originalBytes{}; // save 6 original bytes (for possible restore)
    if (!patched && GameVersion && std::strcmp(GameVersion, "1.09") == 0)
    {
        //This code let you use ultimate jutsu in awakening
        const std::array<uint8_t, 6> nops = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
        uintptr_t target = moduleBase + 0x7DF795;

        if (PatchBytes(target, nops.data(), nops.size(), originalBytes.data()))
        {
            patched = true;
            //Console::PrintErr("Patched jnz -> NOPs at %p\n", (void*)target);
        }
        else
        {
            //Console::PrintErr("Patch failed at %p\n", (void*)target);
        }
    }

    unsigned int characodeID = *reinterpret_cast<unsigned int*>(a1 + 0xC8C);
    //Console::PrintErr("Characode ID: %u\n", characodeID);
    //Console::PrintErr("Value: %u\n", v2);
    if (OugiAwakeningParam::IsOugiAwakeningCharID(characodeID)) {
        return 1;
    }

    return static_cast<__int64>(v2);
}


//This function unlock chakra load action
__int64 __fastcall OugiAwakeningParam::sub_14079BB7C_SC(__int64 a1)
{
    unsigned int v2 = 1;

    if (OugiAwakeningParam::orig_sub_140A0E010_SC)
        v2 = OugiAwakeningParam::orig_sub_140A0E010_SC(a1);
    static bool patched2 = false;
    static std::array<uint8_t, 6> originalBytes2{};
    if (!patched2 && GameVersion && std::strcmp(GameVersion, "1.60") == 0)
    {
        //This code let you use ultimate jutsu in awakening
        const std::array<uint8_t, 6> nops = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
        uintptr_t target = moduleBase + 0xA20340;

        if (PatchBytes(target, nops.data(), nops.size(), originalBytes2.data()))
        {
            patched2 = true;
            //Console::PrintErr("Patched target -> NOPs at %p\n", (void*)target);
        }
        else
        {
            //Console::PrintErr("Patch failed at %p\n", (void*)target);
        }
    }

    unsigned int characodeID = *reinterpret_cast<unsigned int*>(a1 + 0xE64);
    //Console::PrintErr("Characode ID: %u\n", characodeID);
    //Console::PrintErr("Value: %u\n", v2);
    if (OugiAwakeningParam::IsOugiAwakeningCharID(characodeID)) {
        return 1;
    }

    return static_cast<__int64>(v2);
}


