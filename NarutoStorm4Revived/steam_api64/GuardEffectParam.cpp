#include <cstdint>
#include "GuardEffectParam.h"
#include "Common.h"
#include "Console.h"
#include "mem.h"
#include "FileParser.h"

GuardEffectParam::orig_sub_1409D6220_t GuardEffectParam::orig_sub_1409D6220 = nullptr;
GuardEffectParam::t_sub_1409D5040 GuardEffectParam::orig_sub_1409D5040 = nullptr;

std::vector<GuardEffectParamEntry> g_GuardEffectEntries;
// ----  packed struct    ----
#pragma pack(push,1)
struct GuardEffectParamRaw {
    uint32_t CharacodeID;      // 0x00
    uint32_t Mode;             // 0x04
    char EffectPath[0x30];     // 0x08
    char StartEffect[0x30];    // 0x38
    char LoopEffect[0x30];     // 0x68
    char EndEffect[0x30];      // 0x98
    char Coord[0x30];          // 0xC8
};
static_assert(sizeof(GuardEffectParamRaw) == 0xF8, "GuardEffectParamRaw must be 0xF8 bytes");
#pragma pack(pop)

// helper: make std::string from fixed buffer, stop at first NUL or at maxlen
static inline std::string MakeStringFromFixedBuffer(const char* buf, size_t maxlen) {
    const void* p = std::memchr(buf, '\0', maxlen);
    size_t len = p ? static_cast<const char*>(p) - buf : maxlen;
    return std::string(buf, buf + len);
}


void GuardEffectParam::ReadGuardEffectParam(const std::string& filename)
{
    std::ifstream f(filename, std::ios::binary);
    if (!f) {
        std::cerr << "ReadGuardEffectParam: failed to open " << filename << "\n";
        return;
    }

    f.seekg(0, std::ios::end);
    std::streamoff fileSize = f.tellg();
    if (fileSize <= 0) {
        std::cerr << "ReadGuardEffectParam: empty file or tellg failed\n";
        return;
    }
    const size_t entrySize = sizeof(GuardEffectParamRaw);
    if (static_cast<size_t>(fileSize) % entrySize != 0) {
        std::cerr << "ReadGuardEffectParam: file size not multiple of entry size\n";
        return;
    }
    size_t count = static_cast<size_t>(fileSize) / entrySize;
    f.seekg(0, std::ios::beg);

    g_GuardEffectEntries.clear();
    g_GuardEffectEntries.reserve(count);

    for (size_t i = 0; i < count; ++i) {
        GuardEffectParamRaw raw;
        std::memset(&raw, 0, sizeof(raw));
        f.read(reinterpret_cast<char*>(&raw), entrySize);
        if (!f) {
            std::cerr << "ReadGuardEffectParam: read failed at entry " << i << "\n";
            break;
        }

        GuardEffectParamEntry entry;
        entry.CharacodeID = raw.CharacodeID;
        entry.Mode = raw.Mode;

        entry.EffectPath = MakeStringFromFixedBuffer(raw.EffectPath, sizeof(raw.EffectPath));
        entry.StartEffect = MakeStringFromFixedBuffer(raw.StartEffect, sizeof(raw.StartEffect));
        entry.LoopEffect = MakeStringFromFixedBuffer(raw.LoopEffect, sizeof(raw.LoopEffect));
        entry.EndEffect = MakeStringFromFixedBuffer(raw.EndEffect, sizeof(raw.EndEffect));
        entry.Coord = MakeStringFromFixedBuffer(raw.Coord, sizeof(raw.Coord));

        g_GuardEffectEntries.push_back(std::move(entry));
    }
}

//    CharacodeID (nullptr  )
GuardEffectParamEntry* GetGuardEffectEntry(uint32_t charID, uint32_t mode)
{
    //   0  1     mode==2      .
    if (mode == 0 || mode == 1) {
        for (auto& e : g_GuardEffectEntries) {
            if (e.CharacodeID == charID && e.Mode == 2) {
                return &e;
            }
        }
        //          .
        for (auto& e : g_GuardEffectEntries) {
            if (e.CharacodeID == charID && e.Mode == mode) {
                return &e;
            }
        }
        return nullptr;
    }

    //       .
    for (auto& e : g_GuardEffectEntries) {
        if (e.CharacodeID == charID && e.Mode == mode) return &e;
    }
    return nullptr;
}
__int64 __fastcall GuardEffectParam::sub_1409D6220_SC(__int64 a1, int a2)
{
    __int64 result;
    char* v8; // rdx
    __int64 v4; // rcx
    const char* startEffect; // rcx
    const char* loopEffect; // rcx
    const char* endEffect; // rcx
    const char* currentEffect; // rcx
    char* LoadEffectFile; // rsi
    int CharacodeID = *(int*)(a1 + 0xE64);
    void* ccPlayerActionGuard; // rax
    __int64 ccPlayerActionGuardAddress; // rbx
    __int64 v66[3]; // [rsp+48h] [rbp-E0h] BYREF
    __int64 CoordByFullName; // rbp
    __int64 v54; // rcx
    int v55; // eax
    __int64 v70_unknown[8]; //  __int128 v70_unknown[4]
    typedef const int* (__fastcall* t_sub_1405F7E10)(__int64 a1, int a2);
    static t_sub_1405F7E10 sub_1405F7E10_f = (t_sub_1405F7E10)(moduleBase + 0x5F7210);

    typedef char* (__fastcall* t_sub_1409BAF60)(__int64 a1, const char* a2); //  handle/ptr (v5)
    t_sub_1409BAF60 sub_1409BAF60_f = (t_sub_1409BAF60)(moduleBase + 0x9BA360);

    typedef void* (__fastcall* t_sub_14124AE70)(size_t a1, const char* a2, int a3);
    t_sub_14124AE70 sub_14124AE70_f = (t_sub_14124AE70)(moduleBase + 0x124A270);

    typedef __int64(__fastcall* t_sub_1409DCC60)(void* a1); //  v52
    t_sub_1409DCC60 sub_1409DCC60_f = (t_sub_1409DCC60)(moduleBase + 0x9DC060);

    typedef void(__fastcall* t_sub_1409DCDB0)(__int64* dstStruct, __int64 v5, const char* locale);
    t_sub_1409DCDB0 sub_1409DCDB0_f = (t_sub_1409DCDB0)(moduleBase + 0x9DC1B0);

    typedef __int64* (__fastcall* sub_1409D4DE0)(__int64* a1, char* a2, __int64* a3);
    sub_1409D4DE0 sub_1409D4DE0_f = (sub_1409D4DE0)(moduleBase + 0x9D41E0);

    typedef __int64(__fastcall* sub_14050C520)(__int64 a1);
    sub_14050C520 sub_14050C520_f = (sub_14050C520)(moduleBase + 0x50B920);

    typedef __int64(__fastcall* t_sub_1405F0800)(__int64 pool, __int64 name, unsigned int a3);
    t_sub_1405F0800 GetCoordByFullName_f = (t_sub_1405F0800)(moduleBase + 0x5EFC00);

    typedef void(__fastcall* sub_141256F40)(__int64* a1);
    sub_141256F40 sub_141256F40_f = (sub_141256F40)(moduleBase + 0x1256340);

    typedef __int64* (__fastcall* sub_141256F80)(__int64* a1, __int64* a2);
    sub_141256F80 sub_141256F80_f = (sub_141256F80)(moduleBase + 0x1256380);

    typedef void(__fastcall* t_sub_1409D6FC0)(__int64*);
    t_sub_1409D6FC0 sub_1409D6FC0_f = (t_sub_1409D6FC0)(moduleBase + 0x9D63C0);

    typedef void(__fastcall* t_sub_1400B6920)(char* a1, __int64* a2);
    static t_sub_1400B6920 sub_1400B6920_f = (t_sub_1400B6920)(moduleBase + 0x0B5D20);

    typedef __int64* (__fastcall* t_sub_1400B3830)(__int64* a1, const void* a2, size_t a3);
    static t_sub_1400B3830 sub_1400B3830_f = (t_sub_1400B3830)(moduleBase + 0xB2C30);

    typedef __int64(__fastcall* t_sub_14124BFE0)(__int64 a);
    static t_sub_14124BFE0 sub_14124BFE0 = (t_sub_14124BFE0)(moduleBase + 0x124B3E0);

    typedef __int64(__fastcall* t_sub_14124C1D0)(int a);
    static t_sub_14124C1D0 sub_14124C1D0 = (t_sub_14124C1D0)(moduleBase + 0x124B5D0);

    typedef void(__fastcall* t_sub_14124BB20)(void* Block);
    static t_sub_14124BB20 sub_14124BB20 = (t_sub_14124BB20)(moduleBase + 0x124AF20);

    typedef void(__fastcall* t_sub_14124C170)();
    static t_sub_14124C170 sub_14124C170 = (t_sub_14124C170)(moduleBase + 0x124B570);
    __int64 v50; // rcx
    void** v46; // rdx
    void* Block[3]; // [rsp+78h] [rbp-B0h] BYREF
    __int64 v67[3]; // [rsp+60h] [rbp-C8h] BYREF
    unsigned __int64 v69; // [rsp+90h] [rbp-98h]
    void* v47; // rbx
    int v48; // eax
    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1);
    //Console::PrintErr("CharacodeID 0x%X\n", CharacodeID);
    GuardEffectParamEntry* entry = GetGuardEffectEntry(CharacodeID, isAwakened);

    if (entry) {
        v66[1] = a1;
        (*(void(__fastcall**)(__int64))(*(__int64*)a1 + 8i64))(a1);

        v4 = *(__int64*)(a1 + 0x12040);
        if (v4)
            sub_1405F7E10_f(v4, a2);
        __int64 pool = *(__int64*)(a1 + 520);
        //Console::PrintErr("Code Executed\n");
        startEffect = entry->StartEffect.c_str();
        loopEffect = entry->LoopEffect.c_str();
        endEffect = entry->EndEffect.c_str();
        if (a2 == 1)
            currentEffect = loopEffect;
        else if (a2 == 2)
            currentEffect = endEffect;
        else
            currentEffect = startEffect;

        //Console::PrintErr("Current Effect = %d - %s\n", a2, currentEffect);
        sub_141256F40_f(v70_unknown);
        CoordByFullName = GetCoordByFullName_f(*(__int64*)(a1 + 520), (__int64)entry->Coord.c_str(), 0i64);


       

        if (!CoordByFullName)
            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);

        sub_141256F80_f(
            v70_unknown,
            (__int64*)(CoordByFullName + ((unsigned __int64)*(unsigned __int8*)(CoordByFullName + 288) << 6) + 124));
        v50 = *(__int64*)(a1 + 0x11618);
        if (v50)
        {
            sub_141256F80_f((__int64*)(v50 + 40), v70_unknown);
            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
        }

        //v8 = *(char**)(a1 + 0x12040);
        sub_1409D6FC0_f((__int64*)a1);
        ccPlayerActionGuard = sub_14124AE70_f(
            0x70ui64,
            "D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ccPlayerActionGuard.cpp",
            784);
        v66[2] = (__int64)ccPlayerActionGuard;
        if (ccPlayerActionGuard)
            ccPlayerActionGuardAddress = sub_1409DCC60_f(ccPlayerActionGuard);
        else
            ccPlayerActionGuardAddress = 0;


        LoadEffectFile = sub_1409BAF60_f(a1, entry->EffectPath.c_str());

        //Console::PrintErr("LoadEffectFile= %s\n", LoadEffectFile);
        sub_1409DCDB0_f((__int64*)ccPlayerActionGuardAddress, (__int64)LoadEffectFile, currentEffect);

        sub_141256F80_f((__int64*)(ccPlayerActionGuardAddress + 40), v70_unknown);
        v66[0] = ccPlayerActionGuardAddress;
        v8 = *(char**)(a1 + 0x11608);
        if (v8 == *(char**)(a1 + 0x11610))
        {
            sub_1409D4DE0_f((__int64*)(a1 + 0x115E8), v8, v66);
        }
        else
        {
            *(__int64*)v8 = ccPlayerActionGuardAddress;
            *(__int64*)(a1 + 0x11608) += 8i64;
        }
        v54 = *(__int64*)(ccPlayerActionGuardAddress + 32);
        if (!v54 || a2)
        {
            //Console::PrintErr("Loop\n");
            if (a2 == 1)
                *(__int64*)(a1 + 0x11618) = ccPlayerActionGuardAddress;
        }
        else
        {

            //Console::PrintErr("Not Loop\n");
            v55 = sub_14050C520_f(v54);
            v8 = (char*)((unsigned int)*((unsigned __int8*)Common::GetQword(0x1496CF1C8) + 0x952) * v55 % 0xBB8);
            *(int*)(a1 + 0x11620) = (unsigned int)*((unsigned __int8*)Common::GetQword(0x1496CF1C8) + 0x952) * v55 / 0xBB8;
        }
        //Console::PrintErr("Code Finished\n");
        return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
    }
    else {
        result = GuardEffectParam::orig_sub_1409D6220(a1, a2);
        return result;
    }
}

//__int64 __fastcall GuardEffectParam::sub_1409D6220_SC(__int64 a1, int a2)
//{
//    __int64 result;
//    char* v8; // rdx
//    __int64 v4; // rcx
//    const char* startEffect; // rcx
//    const char* loopEffect; // rcx
//    const char* endEffect; // rcx
//    const char* currentEffect; // rcx
//    char* LoadEffectFile; // rsi
//    int CharacodeID = *(int*)(a1 + 0xE64);
//    void* ccPlayerActionGuard; // rax
//    __int64 ccPlayerActionGuardAddress; // rbx
//    __int64 v66[3]; // [rsp+48h] [rbp-E0h] BYREF
//    __int64 CoordByFullName; // rbp
//    __int64 v54; // rcx
//    int v55; // eax
//    __int64 v70_unknown[8]; //  __int128 v70_unknown[4]
//    typedef const int* (__fastcall* t_sub_1405F7E10)(__int64 a1, int a2);
//    static t_sub_1405F7E10 sub_1405F7E10_f = (t_sub_1405F7E10)(moduleBase + 0x5F7210);
//
//    typedef char* (__fastcall* t_sub_1409BAF60)(__int64 a1, const char* a2); //  handle/ptr (v5)
//    t_sub_1409BAF60 sub_1409BAF60_f = (t_sub_1409BAF60)(moduleBase + 0x9BA360);
//
//    typedef void* (__fastcall* t_sub_14124AE70)(size_t a1, const char* a2, int a3);
//    t_sub_14124AE70 sub_14124AE70_f = (t_sub_14124AE70)(moduleBase + 0x124A270);
//
//    typedef __int64(__fastcall* t_sub_1409DCC60)(void* a1); //  v52
//    t_sub_1409DCC60 sub_1409DCC60_f = (t_sub_1409DCC60)(moduleBase + 0x9DC060);
//
//    typedef void(__fastcall* t_sub_1409DCDB0)(__int64* dstStruct, __int64 v5, const char* locale);
//    t_sub_1409DCDB0 sub_1409DCDB0_f = (t_sub_1409DCDB0)(moduleBase + 0x9DC1B0);
//
//    typedef __int64* (__fastcall* sub_1409D4DE0)(__int64* a1, char* a2, __int64* a3);
//    sub_1409D4DE0 sub_1409D4DE0_f = (sub_1409D4DE0)(moduleBase + 0x9D41E0);
//
//    typedef __int64(__fastcall* sub_14050C520)(__int64 a1);
//    sub_14050C520 sub_14050C520_f = (sub_14050C520)(moduleBase + 0x50B920);
//
//    typedef __int64(__fastcall* t_sub_1405F0800)(__int64 pool, __int64 name, unsigned int a3);
//    t_sub_1405F0800 GetCoordByFullName_f = (t_sub_1405F0800)(moduleBase + 0x5EFC00);
//
//    typedef void(__fastcall* sub_141256F40)(__int64* a1);
//    sub_141256F40 sub_141256F40_f = (sub_141256F40)(moduleBase + 0x1256340);
//
//    typedef __int64* (__fastcall* sub_141256F80)(__int64* a1, __int64* a2);
//    sub_141256F80 sub_141256F80_f = (sub_141256F80)(moduleBase + 0x1256380);
//
//    typedef void(__fastcall* t_sub_1409D6FC0)(__int64*);
//    t_sub_1409D6FC0 sub_1409D6FC0_f = (t_sub_1409D6FC0)(moduleBase + 0x9D63C0);
//
//    typedef void(__fastcall* t_sub_1400B6920)(char* a1, __int64* a2);
//    static t_sub_1400B6920 sub_1400B6920_f = (t_sub_1400B6920)(moduleBase + 0x0B5D20);
//
//    typedef __int64* (__fastcall* t_sub_1400B3830)(__int64* a1, const void* a2, size_t a3);
//    static t_sub_1400B3830 sub_1400B3830_f = (t_sub_1400B3830)(moduleBase + 0xB2C30);
//
//    typedef __int64(__fastcall* t_sub_14124BFE0)(__int64 a);
//    static t_sub_14124BFE0 sub_14124BFE0 = (t_sub_14124BFE0)(moduleBase + 0x124B3E0);
//
//    typedef __int64(__fastcall* t_sub_14124C1D0)(int a);
//    static t_sub_14124C1D0 sub_14124C1D0 = (t_sub_14124C1D0)(moduleBase + 0x124B5D0);
//
//    typedef void(__fastcall* t_sub_14124BB20)(void* Block);
//    static t_sub_14124BB20 sub_14124BB20 = (t_sub_14124BB20)(moduleBase + 0x124AF20);
//
//    typedef void(__fastcall* t_sub_14124C170)();
//    static t_sub_14124C170 sub_14124C170 = (t_sub_14124C170)(moduleBase + 0x124B570);
//    __int64 v50; // rcx
//    void** v46; // rdx
//    void* Block[3]; // [rsp+78h] [rbp-B0h] BYREF
//    __int64 v67[3]; // [rsp+60h] [rbp-C8h] BYREF
//    unsigned __int64 v69; // [rsp+90h] [rbp-98h]
//    void* v47; // rbx
//    int v48; // eax
//    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1);
//    Console::PrintErr("CharacodeID 0x%X\n", CharacodeID);
//
//
//    GuardEffectParamEntry* entry = GetGuardEffectEntry(CharacodeID, isAwakened);
//
//    if (entry) {
//        v66[1] = a1;
//        (*(void(__fastcall**)(__int64))(*(__int64*)a1 + 8i64))(a1);
//
//        v4 = *(__int64*)(a1 + 0x12040);
//        if (v4)
//            sub_1405F7E10_f(v4, a2);
//        __int64 pool = *(__int64*)(a1 + 520);
//        Console::PrintErr("Code Executed\n");
//        startEffect = (entry->StartEffect).c_str();
//        loopEffect = (entry->LoopEffect).c_str();
//        endEffect = (entry->EndEffect).c_str();
//        if (a2 == 1)
//            currentEffect = loopEffect;
//        else if (a2 == 2)
//            currentEffect = endEffect;
//        else
//            currentEffect = startEffect;
//
//        Console::PrintErr("Current Effect = %d - %s\n", a2, currentEffect);
//        sub_141256F40_f(v70_unknown);
//        CoordByFullName = GetCoordByFullName_f(*(__int64*)(a1 + 520), (__int64)(entry->Coord).c_str(), 0i64);
//
//
//        sub_1400B6920_f((char*)v67, (__int64*)(*(__int64*)(a1 + 520) + 0x35E0i64));
//        sub_1400B3830_f(v67, "00t0 trall", 0xAui64);
//        v46 = Block;
//        if (v69 >= 0x10)
//            v46 = (void**)Block[0];
//        //CoordByFullName = GetCoordByFullName_f(*(__int64*)(a1 + 520), (__int64)v46, 0);
//        if (v69 >= 0x10)
//        {
//            v47 = Block[0];
//            v48 = sub_14124BFE0((__int64)v67);
//            sub_14124C1D0(v48);
//            sub_14124BB20(v47);
//            sub_14124C170();
//        }
//        Block[2] = 0i64;
//        v69 = 15i64;
//        *reinterpret_cast<unsigned char*>(&Block[0]) = 0;
//        v67[0] = *reinterpret_cast<__int64*>(moduleBase + 0x1735AF8);
//
//
//        if (!CoordByFullName) {
//            // try to use a predictable fallback pointer if possible
//            char* fallback = nullptr;
//            if ((char*)(*(__int64*)(a1 + 0x11608)) != nullptr)
//                fallback = *reinterpret_cast<char**>(a1 + 0x11608);
//            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, fallback);
//        }
//
//        sub_141256F80_f(
//            v70_unknown,
//            (__int64*)(CoordByFullName + ((unsigned __int64)*(unsigned __int8*)(CoordByFullName + 288) << 6) + 124));
//        v50 = *(__int64*)(a1 + 0x11618);
//        if (v50)
//        {
//            sub_141256F80_f((__int64*)(v50 + 40), v70_unknown);
//            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
//        }
//
//        //v8 = *(char**)(a1 + 0x12040);
//        sub_1409D6FC0_f((__int64*)a1);
//        ccPlayerActionGuard = sub_14124AE70_f(
//            0x70ui64,
//            "D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ccPlayerActionGuard.cpp",
//            784);
//        v66[2] = (__int64)ccPlayerActionGuard;
//        if (ccPlayerActionGuard)
//            ccPlayerActionGuardAddress = sub_1409DCC60_f(ccPlayerActionGuard);
//        else
//            ccPlayerActionGuardAddress = 0;
//
//
//        LoadEffectFile = sub_1409BAF60_f(a1, (entry->EffectPath).c_str());
//
//        Console::PrintErr("LoadEffectFile= %s\n", LoadEffectFile);
//        sub_1409DCDB0_f((__int64*)ccPlayerActionGuardAddress, (__int64)LoadEffectFile, currentEffect);
//
//        sub_141256F80_f((__int64*)(ccPlayerActionGuardAddress + 40), v70_unknown);
//        v66[0] = ccPlayerActionGuardAddress;
//        v8 = *(char**)(a1 + 0x11608);
//        if (v8 == *(char**)(a1 + 0x11610))
//        {
//            sub_1409D4DE0_f((__int64*)(a1 + 0x115E8), v8, v66);
//        }
//        else
//        {
//            *(__int64*)v8 = ccPlayerActionGuardAddress;
//            *(__int64*)(a1 + 0x11608) += 8i64;
//        }
//        v54 = *(__int64*)(ccPlayerActionGuardAddress + 32);
//        if (!v54 || a2)
//        {
//            Console::PrintErr("Loop\n");
//            if (a2 == 1)
//                *(__int64*)(a1 + 0x11618) = ccPlayerActionGuardAddress;
//        }
//        else
//        {
//
//            Console::PrintErr("Not Loop\n");
//            v55 = sub_14050C520_f(v54);
//            v8 = (char*)((unsigned int)*((unsigned __int8*)Common::GetQword(0x1496CF1C8) + 0x952) * v55 % 0xBB8);
//            *(int*)(a1 + 0x11620) = (unsigned int)*((unsigned __int8*)Common::GetQword(0x1496CF1C8) + 0x952) * v55 / 0xBB8;
//        }
//        Console::PrintErr("Code Finished\n");
//        return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
//    }
//    else {
//        result = GuardEffectParam::orig_sub_1409D6220(a1, a2);
//        return result;
//    }
//
//}
//__int64 __fastcall GuardEffectParam::sub_1409D6220_SC(__int64 a1, __int64 a2) {
//
//    //   
//    constexpr std::uintptr_t BASE_SUB = 0x140000C00ULL;
//
//    // typedef + OFF  
//    typedef void(__fastcall* fn_1405F7E10_t)(__int64, int);
//    constexpr std::uintptr_t OFF_1405F7E10 = 0x1405F7E10ULL;
//    fn_1405F7E10_t sub_1405F7E10 = reinterpret_cast<fn_1405F7E10_t>(moduleBase + (OFF_1405F7E10 - BASE_SUB));
//
//    typedef void(__fastcall* fn_141256F40_t)(__int64*);
//    constexpr std::uintptr_t OFF_141256F40 = 0x141256F40ULL;
//    fn_141256F40_t sub_141256F40 = reinterpret_cast<fn_141256F40_t>(moduleBase + (OFF_141256F40 - BASE_SUB));
//
//    typedef void(__fastcall* fn_141256F80_t)(__int64*, void*);
//    constexpr std::uintptr_t OFF_141256F80 = 0x141256F80ULL;
//    fn_141256F80_t sub_141256F80 = reinterpret_cast<fn_141256F80_t>(moduleBase + (OFF_141256F80 - BASE_SUB));
//
//    typedef signed __int64(__fastcall* fn_GetCoordByFullName_t)(__int64, __int64, unsigned int);
//    fn_GetCoordByFullName_t ccGameObjSubDraw_GetCoordByFullName = reinterpret_cast<fn_GetCoordByFullName_t>(moduleBase + 0x5EFC00);
//
//    typedef void(__fastcall* fn_1400B6920_t)(char*, __int64*);
//    constexpr std::uintptr_t OFF_1400B6920 = 0x1400B6920ULL;
//    fn_1400B6920_t sub_1400B6920 = reinterpret_cast<fn_1400B6920_t>(moduleBase + (OFF_1400B6920 - BASE_SUB));
//
//    typedef __int64*(__fastcall* fn_1400B3830_t)(__int64*, const void*, size_t);
//    constexpr std::uintptr_t OFF_1400B3830 = 0x1400B3830ULL;
//    fn_1400B3830_t sub_1400B3830 = reinterpret_cast<fn_1400B3830_t>(moduleBase + (OFF_1400B3830 - BASE_SUB));
//
//    typedef char* (__fastcall* fn_1409BAF60_t)(__int64, const char*);
//    constexpr std::uintptr_t OFF_1409BAF60 = 0x1409BAF60ULL;
//    fn_1409BAF60_t sub_1409BAF60 = reinterpret_cast<fn_1409BAF60_t>(moduleBase + (OFF_1409BAF60 - BASE_SUB));
//
//    typedef void(__fastcall* fn_1409D6FC0_t)(__int64);
//    constexpr std::uintptr_t OFF_1409D6FC0 = 0x1409D6FC0ULL;
//    fn_1409D6FC0_t sub_1409D6FC0 = reinterpret_cast<fn_1409D6FC0_t>(moduleBase + (OFF_1409D6FC0 - BASE_SUB));
//
//    typedef void* (__fastcall* fn_14124AE70_t)(__int64, __int64, int);
//    constexpr std::uintptr_t OFF_14124AE70 = 0x14124AE70ULL;
//    fn_14124AE70_t sub_14124AE70 = reinterpret_cast<fn_14124AE70_t>(moduleBase + (OFF_14124AE70 - BASE_SUB));
//
//    typedef __int64(__fastcall* fn_1409DCC60_t)(__int64);
//    constexpr std::uintptr_t OFF_1409DCC60 = 0x1409DCC60ULL;
//    fn_1409DCC60_t sub_1409DCC60 = reinterpret_cast<fn_1409DCC60_t>(moduleBase + (OFF_1409DCC60 - BASE_SUB));
//
//    typedef void(__fastcall* fn_1409DCDB0_t)(__int64*, __int64, __int64);
//    constexpr std::uintptr_t OFF_1409DCDB0 = 0x1409DCDB0ULL;
//    fn_1409DCDB0_t sub_1409DCDB0 = reinterpret_cast<fn_1409DCDB0_t>(moduleBase + (OFF_1409DCDB0 - BASE_SUB));
//
//    typedef void(__fastcall* fn_1409D4DE0_t)(__int64*, char*, __int64*);
//    constexpr std::uintptr_t OFF_1409D4DE0 = 0x1409D4DE0ULL;
//    fn_1409D4DE0_t sub_1409D4DE0 = reinterpret_cast<fn_1409D4DE0_t>(moduleBase + (OFF_1409D4DE0 - BASE_SUB));
//
//    typedef int(__fastcall* fn_14050C520_t)(__int64);
//    constexpr std::uintptr_t OFF_14050C520 = 0x14050C520ULL;
//    fn_14050C520_t sub_14050C520 = reinterpret_cast<fn_14050C520_t>(moduleBase + (OFF_14050C520 - BASE_SUB));
//
//    typedef int(__fastcall* fn_14124BFE0_t)(__int64);
//    constexpr std::uintptr_t OFF_14124BFE0 = 0x14124BFE0ULL;
//    fn_14124BFE0_t sub_14124BFE0 = reinterpret_cast<fn_14124BFE0_t>(moduleBase + (OFF_14124BFE0 - BASE_SUB));
//
//    typedef __int64(__fastcall* fn_14124C1D0_t)(int);
//    constexpr std::uintptr_t OFF_14124C1D0 = 0x14124C1D0ULL;
//    fn_14124C1D0_t sub_14124C1D0 = reinterpret_cast<fn_14124C1D0_t>(moduleBase + (OFF_14124C1D0 - BASE_SUB));
//
//    typedef void(__fastcall* fn_14124BB20_t)(void* Block);
//    constexpr std::uintptr_t OFF_14124BB20 = 0x14124BB20ULL;
//    fn_14124BB20_t sub_14124BB20 = reinterpret_cast<fn_14124BB20_t>(moduleBase + (OFF_14124BB20 - BASE_SUB));
//
//    typedef void(__fastcall* fn_14124C170_t)();
//    constexpr std::uintptr_t OFF_14124C170 = 0x14124C170ULL;
//    fn_14124C170_t sub_14124C170 = reinterpret_cast<fn_14124C170_t>(moduleBase + (OFF_14124C170 - BASE_SUB));
//
//    typedef unsigned int(__fastcall* fn_140B533A0_t)(__int64);
//    constexpr std::uintptr_t OFF_140B533A0 = 0x140B533A0ULL;
//    fn_140B533A0_t sub_140B533A0 = reinterpret_cast<fn_140B533A0_t>(moduleBase + (OFF_140B533A0 - BASE_SUB));
//
//    //  __int128 v70_unknown[4]  __int64 v70_unknown[8]
//    __int64 v70_unknown[8];
//    void** v46;
//    void* v47;
//    //   (  )
//    __int64 v66[3];
//    __int64 v67[3];
//    void* Block[3];
//    unsigned __int64 v69 = 0;
//    const char* Locale = reinterpret_cast<const char*>(moduleBase + (0x1417373A9 - BASE_SUB));
//
//    v66[1] = a1;
//    //  a1->vtable[1] (call at +8)
//    {
//        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//        auto fn = *reinterpret_cast<std::uintptr_t*>(vtbl + 8);
//        using fn_t = void(__fastcall*)(__int64);
//        reinterpret_cast<fn_t>(fn)(a1);
//    }
//
//    __int64 v4 = *reinterpret_cast<__int64*>(a1 + 0x12040);
//    if (v4)
//        sub_1405F7E10(v4, a2);
//
//    char* v5 = nullptr;
//    int v6 = 0;
//    int v7 = *reinterpret_cast<int*>(a1 + 0xE64);
//    char* v8 = *reinterpret_cast<char**>(a1 + 0x12040);
//
//    switch (v7)
//    {
//    case 56: case 0x55: case 0x82: case 0xC1: case 0xC9: case 0xE7: case 0xF1:
//    {
//        // call a1->vtable+0x1260
//        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//        auto fn1260 = *reinterpret_cast<std::uintptr_t*>(vtbl + 0x1260);
//        using fn1260_t = unsigned int(__fastcall*)(__int64);
//        unsigned int r = reinterpret_cast<fn1260_t>(fn1260)(a1);
//        if (!r || *reinterpret_cast<int*>(a1 + 0xE84) == 1)
//            goto LABEL_8;
//    }
//    break;
//    case 99:  case 0x46:
//    case 0x6F:
//        goto LABEL_8;
//    case 0x56:
//    case 0xCB:
//    {
//        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//        auto fn1260 = *reinterpret_cast<std::uintptr_t*>(vtbl + 0x1260);
//        using fn1260_t = unsigned int(__fastcall*)(__int64);
//        if (reinterpret_cast<fn1260_t>(fn1260)(a1))
//            goto LABEL_8;
//    }
//    break;
//    default:
//        break;
//    }
//
//LABEL_8:
//    if (v8 || (v6 = 1, 1))
//    {
//        int v9 = 0;
//        v66[0] = 0;
//        int v10 = 0, v11 = 0, v12 = 0, v13 = 0, v14 = 0;
//        int v57 = 0, v58 = 0, v59 = 0, v60 = 0, v61 = 0;
//        int v62 = 0, v63 = 0, v64 = 0, v65 = 0;
//
//        switch (v7)
//        {
//        case 56: case 99:  v9 = 1; v66[0] = 1; v14 = 0; break;
//        case 0x46: v12 = 1; v64 = 1; break;
//        case 0x55: v10 = 1; v62 = 1; break;
//        case 0x56: v11 = 1; v63 = 1; break;
//        case 0x6F: v13 = 1; v65 = 1; break;
//        case 0x82: v14 = 1; v57 = 1; break;
//        case 0xC9: v58 = 1; break;
//        case 0xCB: v60 = 1; break;
//        case 0xE7: v61 = 1; break;
//        case 0xF1: v59 = 1; break;
//        default: v14 = 0; break;
//        }
//
//        bool v15 = (v8 != nullptr);
//        const char* v16 = Locale;
//
//        if (a2)
//        {
//            if (a2 == 1)
//            {
//                const char* v26 = v9 ? "2sszeff1_grdl" : Locale;
//                const char* v27 = v10 ? "3sskeff1_grdl" : v26;
//                const char* v29 = v11 ? "2gareff1_awa_grd00_l" : v27;
//                const char* v30 = v12 ? "3mdreff1_grd00_l" : v29;
//                const char* v31 = v13 ? "3mdreff1_2_grd00_l" : v30;
//                const char* v32 = v14 ? "5sskeff1_grdl" : v31;
//                const char* v34 = v58 ? "7ssxeff1_grd_eff00_l" : v32;
//                const char* v33 = v59 ? "7ssxeff1_grd_eff00_l" : v34;
//                const char* v28 = v60 ? v33 : v27; // <- : fallback   v27 (),   literal "2gareff1..."
//                v16 = v61 ? "9indeff1_grd_eff00_l" : v28;
//                if (v15)
//                {
//                    if (v7 == 113) v16 = "5obteff1_gd01_ptc01";
//                    else if (v7 == 114) v16 = "5mdreff1_gd01_ptc01";
//                }
//            }
//            else if (a2 == 2)
//            {
//                const char* v17 = v9 ? "2sszeff1_grde" : Locale;
//                const char* v18 = v10 ? "3sskeff1_grde" : v17;
//                const char* v20 = v11 ? "2gareff1_awa_grd00_e" : v18;
//                const char* v21 = v12 ? "3mdreff1_grd00_e" : v20;
//                const char* v22 = v13 ? "3mdreff1_2_grd00_e" : v21;
//                const char* v23 = v14 ? "5sskeff1_grde" : v22;
//                const char* v25 = v58 ? "7ssxeff1_grd_eff00_e" : v23;
//                const char* v24 = v59 ? "7ssxeff1_grd_eff00_e" : v25;
//                const char* v19 = v60 ? v24 : v18; // <- fallback to v18
//                v16 = v61 ? "9indeff1_grd_eff00_e" : v19;
//                if (v15)
//                {
//                    if (v7 == 113) v16 = "5obteff1_gd01_ptc02";
//                    else if (v7 == 114) v16 = "5mdreff1_gd01_ptc02";
//                }
//            }
//        }
//        else
//        {
//            const char* v35 = v9 ? "2sszeff1_grds" : Locale;
//            const char* v36 = v10 ? "3sskeff1_grds" : v35;
//            const char* v38 = v11 ? "2gareff1_awa_grd00_s" : v36;
//            const char* v39 = v12 ? "3mdreff1_grd00_s" : v38;
//            const char* v40 = v13 ? "3mdreff1_2_grd00_s" : v39;
//            const char* v41 = v14 ? "5sskeff1_grds" : v40;
//            const char* v43 = v58 ? "7ssxeff1_grd_eff00_s" : v41;
//            const char* v42 = v59 ? "7ssxeff1_grd_eff00_s" : v43;
//            const char* v37 = v60 ? v42 : v36; // <- fallback to v36
//            v16 = v61 ? "9indeff1_grd_eff00_s" : v37;
//            if (v15)
//            {
//                if (v7 == 113) v16 = "5obteff1_gd01_ptc00";
//                else if (v7 == 114) v16 = "5mdreff1_gd01_ptc00";
//            }
//        }
//
//        // sub_141256F40(v70_unknown);
//        sub_141256F40(reinterpret_cast<__int64*>(v70_unknown));
//
//        __int64 CoordByFullName = 0;
//
//        if (v63) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("2gar00t0 trall"), 0);
//        if (v64) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("3mdr00t0 trall"), 0);
//        if (v65) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("3mdr00t0 trall"), 0);
//        if (v57) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("5ssk00t0 trall"), 0);
//        if (v58) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("7ssk00t0 trall"), 0);
//        if (v59) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("8ssf00t0 trall"), 0);
//        if (v60) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("7gar00t0 trall"), 0);
//        if (v61) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>("9ind00t0 trall"), 0);
//
//        if (v62 || v9)
//        {
//            sub_1400B6920((char*)v67, (__int64*)(*(__int64*)(a1 + 520) + 0x35E0i64));
//            sub_1400B3830(v67, "00t0 trall", 0xAui64);
//            v46 = Block;
//            if (v69 >= 0x10) v46 = (void**)Block[0];
//            CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*(__int64*)(a1 + 520), reinterpret_cast<__int64>("trall"), 0);
//            if (v69 >= 0x10)
//            {
//                v47 = Block[0];
//                int v48 = sub_14124BFE0((__int64)v67);
//                sub_14124C1D0(v48);
//                sub_14124BB20(v47);
//                sub_14124C170();
//            }
//            Block[2] = 0i64;
//            v69 = 15i64;
//            reinterpret_cast<char&>(Block[0]) = 0;
//            v67[0] = *reinterpret_cast<__int64*>(moduleBase + 0x1735AF8);
//        }
//
//        if (!v15) goto LABEL_131;
//        const char* v49 = nullptr;
//        if (v7 == 113) v49 = "5obt00t0 trall";
//        else if (v7 == 114) v49 = "5mdr00t0 trall";
//        if (v49) CoordByFullName = ccGameObjSubDraw_GetCoordByFullName(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<__int64>(v49), 0);
//
//    LABEL_131:
//        if (!CoordByFullName)
//        {
//            // return a1->vtable[2](a1, v8)     +16
//            std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//            auto fn16 = *reinterpret_cast<std::uintptr_t*>(vtbl + 16);
//            using fn16_t = __int64(__fastcall*)(__int64, char*);
//            return reinterpret_cast<fn16_t>(fn16)(a1, v8);
//        }
//
//        // sub_141256F80(v70_unknown, (_OWORD *)(CoordByFullName + ((unsigned __int64)*(unsigned __int8 *)(CoordByFullName + 288) << 6) + 124));
//        {
//            //    v70_unknown     
//            __int64 offset = (static_cast<unsigned __int64>(*reinterpret_cast<unsigned char*>(CoordByFullName + 288)) << 6) + 124;
//            sub_141256F80(reinterpret_cast<__int64*>(v70_unknown), reinterpret_cast<void*>(CoordByFullName + offset));
//        }
//
//        __int64 v50 = *reinterpret_cast<__int64*>(a1 + 0x11618);
//        if (v50)
//        {
//            // sub_141256F80((_OWORD *)(v50 + 40), v70_unknown);
//            sub_141256F80(reinterpret_cast<__int64*>(v50 + 40), reinterpret_cast<void*>(v70_unknown));
//            // return a1->vtable[2](a1, v8)
//            std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//            auto fn16 = *reinterpret_cast<std::uintptr_t*>(vtbl + 16);
//            using fn16_t = __int64(__fastcall*)(__int64, char*);
//            return reinterpret_cast<fn16_t>(fn16)(a1, v8);
//        }
//
//        sub_1409D6FC0(a1);
//
//        void* v51 = sub_14124AE70(0x70ULL, reinterpret_cast<__int64>("D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ccPlayerActionGuard.cpp"), 784);
//        v66[2] = reinterpret_cast<__int64>(v51);
//        __int64 v52 = v51 ? sub_1409DCC60(reinterpret_cast<__int64>(v51)) : 0;
//
//        if (static_cast<int>(v66[0]))
//            v5 = sub_1409BAF60(a1, "2sszeff1.xfbin");
//        if (v62) v5 = sub_1409BAF60(a1, "3sskeff1.xfbin");
//        if (v63) v5 = sub_1409BAF60(a1, "3gareff1.xfbin");
//        if (v64) v5 = sub_1409BAF60(a1, "3mdreff1.xfbin");
//        if (v65) v5 = sub_1409BAF60(a1, "3mdreff1_2.xfbin");
//        if (v57) v5 = sub_1409BAF60(a1, "5sskeff1.xfbin");
//        if (v58) v5 = sub_1409BAF60(a1, "7ssxeff1.xfbin");
//        if (v59) v5 = sub_1409BAF60(a1, "7ssxeff1.xfbin");
//        if (v60) v5 = sub_1409BAF60(a1, "3gareff1.xfbin");
//        if (v61) v5 = sub_1409BAF60(a1, "9indeff1.xfbin");
//
//        if (v15)
//        {
//            const char* v53 = nullptr;
//            if (v7 == 113) v53 = "5obteff1.xfbin";
//            else if (v7 == 114) v53 = "5mdreff1.xfbin";
//            if (v53) v5 = sub_1409BAF60(a1, v53);
//        }
//
//    LABEL_162:
//        sub_1409DCDB0(reinterpret_cast<__int64*>(v52), reinterpret_cast<__int64>(v5), reinterpret_cast<__int64>(v16));
//        sub_141256F80(reinterpret_cast<__int64*>(v52 + 40), reinterpret_cast<void*>(v70_unknown));
//        v66[0] = v52;
//        v8 = *reinterpret_cast<char**>(a1 + 0x11608);
//        if (v8 == *reinterpret_cast<char**>(a1 + 0x11610))
//        {
//            sub_1409D4DE0(reinterpret_cast<__int64*>(a1 + 0x115E8), v8, reinterpret_cast<__int64*>(v66));
//        }
//        else
//        {
//            *reinterpret_cast<__int64*>(v8) = v52;
//            *reinterpret_cast<__int64*>(a1 + 0x11608) += 8;
//        }
//        __int64 v54 = *reinterpret_cast<__int64*>(v52 + 32);
//        if (!v54 || a2)
//        {
//            if (a2 == 1)
//                *reinterpret_cast<__int64*>(a1 + 0x11618) = v52;
//        }
//        else
//        {
//            int v55 = sub_14050C520(v54);
//            // v8 = (char *)((unsigned int)*((unsigned __int8 *)qword_1496CF1C8 + 0x952) * v55 % 0xBB8);
//            unsigned int mul = static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 0x952)) * static_cast<unsigned int>(v55);
//            v8 = reinterpret_cast<char*>(static_cast<std::uintptr_t>(mul % 0xBB8));
//            *reinterpret_cast<uint32_t*>(a1 + 0x11620) = mul / 0xBB8;
//        }
//    }
//
//    // return a1->vtable[2](a1, v8)
//    {
//        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
//        auto fn16 = *reinterpret_cast<std::uintptr_t*>(vtbl + 16);
//        using fn16_t = __int64(__fastcall*)(__int64, char*);
//        return reinterpret_cast<fn16_t>(fn16)(a1, v8);
//    }
//}


void __fastcall GuardEffectParam::hk_sub_1409D5040_SC(__int64 a1, int a2, int a3)
{
    {
        int i; // ebx
        __int64 v27 = 0;
        std::uintptr_t fn3480 = 0;
        int v34 = 0;
        int v35 = 0;
        __int64 v36 = 0;
        __int64 v37 = 0;
        __int64 v39 = 0;
        int v40 = 0;
        unsigned int curState = 0;
        uint32_t e64val = 0;
        __int64 v47 = 0;
        //   
        constexpr std::uintptr_t BASE_SUB = 0x140000C00ULL;

        // typedef' + OFF  
        typedef void(__fastcall* fn_140991940_t)(__int64, __int64, __int64, __int64, int, int);
        constexpr std::uintptr_t OFF_140991940 = 0x140991940ULL;
        fn_140991940_t sub_140991940 = reinterpret_cast<fn_140991940_t>(moduleBase + (OFF_140991940 - BASE_SUB));

        typedef void(__fastcall* fn_1408394E0_t)(void*, int, int);
        constexpr std::uintptr_t OFF_1408394E0 = 0x1408394E0ULL;
        fn_1408394E0_t sub_1408394E0 = reinterpret_cast<fn_1408394E0_t>(moduleBase + (OFF_1408394E0 - BASE_SUB));

        typedef void(__fastcall* fn_1409D6FC0_t)(__int64);
        constexpr std::uintptr_t OFF_1409D6FC0 = 0x1409D6FC0ULL;
        fn_1409D6FC0_t sub_1409D6FC0 = reinterpret_cast<fn_1409D6FC0_t>(moduleBase + (OFF_1409D6FC0 - BASE_SUB));

        typedef void(__fastcall* fn_1409D6220_t)(__int64, int);
        constexpr std::uintptr_t OFF_1409D6220 = 0x1409D6220ULL;
        fn_1409D6220_t sub_1409D6220 = reinterpret_cast<fn_1409D6220_t>(moduleBase + (OFF_1409D6220 - BASE_SUB));

        typedef unsigned int(__fastcall* fn_14098F8E0_t)(__int64);
        constexpr std::uintptr_t OFF_14098F8E0 = 0x14098F8E0ULL;
        fn_14098F8E0_t sub_14098F8E0 = reinterpret_cast<fn_14098F8E0_t>(moduleBase + (OFF_14098F8E0 - BASE_SUB));

        typedef unsigned int(__fastcall* fn_14098FD20_t)(__int64);
        constexpr std::uintptr_t OFF_14098FD20 = 0x14098FD20ULL;
        fn_14098FD20_t sub_14098FD20 = reinterpret_cast<fn_14098FD20_t>(moduleBase + (OFF_14098FD20 - BASE_SUB));

        typedef int(__fastcall* fn_1409BCC50_t)(uint32_t*);
        constexpr std::uintptr_t OFF_1409BCC50 = 0x1409BCC50ULL;
        fn_1409BCC50_t sub_1409BCC50 = reinterpret_cast<fn_1409BCC50_t>(moduleBase + (OFF_1409BCC50 - BASE_SUB));

        typedef unsigned int(__fastcall* fn_140A33210_t)(__int64);
        constexpr std::uintptr_t OFF_140A33210 = 0x140A33210ULL;
        fn_140A33210_t sub_140A33210 = reinterpret_cast<fn_140A33210_t>(moduleBase + (OFF_140A33210 - BASE_SUB));

        typedef int(__fastcall* fn_1409EF570_t)(__int64);
        constexpr std::uintptr_t OFF_1409EF570 = 0x1409EF570ULL;
        fn_1409EF570_t sub_1409EF570 = reinterpret_cast<fn_1409EF570_t>(moduleBase + (OFF_1409EF570 - BASE_SUB));

        typedef void(__fastcall* fn_1409D6C40_t)(char*);
        constexpr std::uintptr_t OFF_1409D6C40 = 0x1409D6C40ULL;
        fn_1409D6C40_t sub_1409D6C40 = reinterpret_cast<fn_1409D6C40_t>(moduleBase + (OFF_1409D6C40 - BASE_SUB));

        typedef void(__fastcall* fn_140A3C2D0_t)(__int64);
        constexpr std::uintptr_t OFF_140A3C2D0 = 0x140A3C2D0ULL;
        fn_140A3C2D0_t sub_140A3C2D0 = reinterpret_cast<fn_140A3C2D0_t>(moduleBase + (OFF_140A3C2D0 - BASE_SUB));

        typedef void(__fastcall* fn_1409BD3B0_t)(__int64, unsigned int);
        constexpr std::uintptr_t OFF_1409BD3B0 = 0x1409BD3B0ULL;
        fn_1409BD3B0_t sub_1409BD3B0 = reinterpret_cast<fn_1409BD3B0_t>(moduleBase + (OFF_1409BD3B0 - BASE_SUB));

        typedef void(__fastcall* fn_1409A34B0_t)(__int64, void*);
        constexpr std::uintptr_t OFF_1409A34B0 = 0x1409A34B0ULL;
        fn_1409A34B0_t sub_1409A34B0 = reinterpret_cast<fn_1409A34B0_t>(moduleBase + (OFF_1409A34B0 - BASE_SUB));

        typedef void(__fastcall* fn_1405F42F0_t)(__int64, void*);
        constexpr std::uintptr_t OFF_1405F42F0 = 0x1405F42F0ULL;
        fn_1405F42F0_t sub_1405F42F0 = reinterpret_cast<fn_1405F42F0_t>(moduleBase + (OFF_1405F42F0 - BASE_SUB));

        typedef void(__fastcall* fn_1405E9580_t)(__int64);
        constexpr std::uintptr_t OFF_1405E9580 = 0x1405E9580ULL;
        fn_1405E9580_t sub_1405E9580 = reinterpret_cast<fn_1405E9580_t>(moduleBase + (OFF_1405E9580 - BASE_SUB));

        typedef __int64(__fastcall* fn_14098F510_t)(__int64, unsigned int, __int64);
        constexpr std::uintptr_t OFF_14098F510 = 0x14098F510ULL;
        fn_14098F510_t sub_14098F510 = reinterpret_cast<fn_14098F510_t>(moduleBase + (OFF_14098F510 - BASE_SUB));

        typedef int(__fastcall* fn_14098F8A0_t)(__int64);
        constexpr std::uintptr_t OFF_14098F8A0 = 0x14098F8A0ULL;
        fn_14098F8A0_t sub_14098F8A0 = reinterpret_cast<fn_14098F8A0_t>(moduleBase + (OFF_14098F8A0 - BASE_SUB));

        typedef void* (__fastcall* fn_140AC4880_t)(__int64, unsigned int);
        constexpr std::uintptr_t OFF_140AC4880 = 0x140AC4880ULL;
        fn_140AC4880_t sub_140AC4880 = reinterpret_cast<fn_140AC4880_t>(moduleBase + (OFF_140AC4880 - BASE_SUB));

        typedef void* (__fastcall* fn_140AC49D0_t)(__int64, unsigned int);
        constexpr std::uintptr_t OFF_140AC49D0 = 0x140AC49D0ULL;
        fn_140AC49D0_t sub_140AC49D0 = reinterpret_cast<fn_140AC49D0_t>(moduleBase + (OFF_140AC49D0 - BASE_SUB));

        typedef void(__fastcall* fn_140A31210_t)(void*);
        constexpr std::uintptr_t OFF_140A31210 = 0x140A31210ULL;
        fn_140A31210_t sub_140A31210 = reinterpret_cast<fn_140A31210_t>(moduleBase + (OFF_140A31210 - BASE_SUB));

        typedef __int64(__fastcall* fn_1409BB050_t)(__int64);
        constexpr std::uintptr_t OFF_1409BB050 = 0x1409BB050ULL;
        fn_1409BB050_t sub_1409BB050 = reinterpret_cast<fn_1409BB050_t>(moduleBase + (OFF_1409BB050 - BASE_SUB));

        typedef unsigned int(__fastcall* fn_1409CF930_t)(__int64);
        constexpr std::uintptr_t OFF_1409CF930 = 0x1409CF930ULL;
        fn_1409CF930_t sub_1409CF930 = reinterpret_cast<fn_1409CF930_t>(moduleBase + (OFF_1409CF930 - BASE_SUB));

        typedef void(__fastcall* fn_1409DCEE0_t)(__int64);
        constexpr std::uintptr_t OFF_1409DCEE0 = 0x1409DCEE0ULL;
        fn_1409DCEE0_t sub_1409DCEE0 = reinterpret_cast<fn_1409DCEE0_t>(moduleBase + (OFF_1409DCEE0 - BASE_SUB));

        typedef unsigned int(__fastcall* fn_140B533A0_t)(__int64);
        constexpr std::uintptr_t OFF_140B533A0 = 0x140B533A0ULL;
        fn_140B533A0_t sub_140B533A0 = reinterpret_cast<fn_140B533A0_t>(moduleBase + (OFF_140B533A0 - BASE_SUB));

        typedef void(__fastcall* fn_140B53940_t)(__int64, int, int);
        constexpr std::uintptr_t OFF_140B53940 = 0x140B53940ULL;
        fn_140B53940_t sub_140B53940 = reinterpret_cast<fn_140B53940_t>(moduleBase + (OFF_140B53940 - BASE_SUB));

        uint32_t valE64 = *reinterpret_cast<uint32_t*>(a1 + 0xE64);
        __int64 v51; // rax
        __int64 v52; // r8
        int v53; // edx
        unsigned int v54; // ebx
        int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1);
        GuardEffectParamEntry* entry = GetGuardEffectEntry(valE64, isAwakened);
        // ----   ( ) ----
        if (!entry) {

            GuardEffectParam::orig_sub_1409D5040(a1, a2, a3);
            return;
        }

        if (a2)
        {
            int v4 = a2 - 1;
            if (v4)
            {
                int v5 = v4 - 1;
                if (v5)
                {
                    if (v5 == 6)
                    {
                        sub_140991940(a1, 102, a3, 0xFFFFFFFF, 0, 0);
                    }
                }
                else
                {
                    uint32_t PlAnmID = *reinterpret_cast<uint32_t*>(a1 + 0xEAC);
                    if (PlAnmID != 74)
                    {
                        void** pC898 = *reinterpret_cast<void***>(a1 + 0xC898);
                        sub_1408394E0(pC898, 4, 6);
                        PlAnmID = *reinterpret_cast<uint32_t*>(a1 + 0xEAC);
                    }

                    bool pass = false;
                    if (entry->Mode == 0 && !isAwakened)
                        pass = true;
                    else if (entry->Mode == 1 && isAwakened)
                        pass = true;
                    else if (entry->Mode == 2)
                        pass = true;

                    if (PlAnmID != 74 && entry && pass)
                    {
                        __int64 v8 = *reinterpret_cast<__int64*>(a1 + 0x11618);
                        if (v8)
                        {
                            *reinterpret_cast<uint32_t*>(v8 + 104) = 1;
                            *reinterpret_cast<__int64*>(a1 + 0x11618) = 0;
                            *reinterpret_cast<uint32_t*>(a1 + 0x11620) = 0;
                            sub_1409D6FC0(a1);
                            for (i = 0; i < 3; ++i)
                                (*(void(__fastcall**)(__int64, __int64))(*(__int64*)(a1 + 0xC1D8) + 8i64))(a1 + 0xC1D8, (unsigned int)i);
                        }
                        GuardEffectParam::sub_1409D6220_SC(a1, 2);
                    }

                    if (*reinterpret_cast<uint32_t*>(a1 + 0xEAC) != 74 && *reinterpret_cast<std::uintptr_t*>(a1 + 0x12040))
                    {
                        __int64 v10 = *reinterpret_cast<__int64*>(a1 + 71192);
                        if (v10)
                        {
                            *reinterpret_cast<uint32_t*>(v10 + 104) = 1;
                            *reinterpret_cast<__int64*>(a1 + 71192) = 0;
                            *reinterpret_cast<uint32_t*>(a1 + 71200) = 0;
                        }
                        GuardEffectParam::sub_1409D6220_SC(a1, 2);
                    }

                    // if (!a1->vfunc_C38(a1, PlAnmID) && a1->vfunc_1538(a1) == 4)
                    {
                        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                        std::uintptr_t fnC38 = *reinterpret_cast<std::uintptr_t*>(vtbl + 0xC38);
                        using vfuncC38_t = unsigned int(__fastcall*)(__int64, __int64);
                        unsigned int resC38 = reinterpret_cast<vfuncC38_t>(fnC38)(a1, PlAnmID);

                        std::uintptr_t fn1538 = *reinterpret_cast<std::uintptr_t*>(vtbl + 0x1538);
                        using vfunc1538_t = unsigned int(__fastcall*)(__int64);
                        unsigned int res1538 = reinterpret_cast<vfunc1538_t>(fn1538)(a1);

                        if (!resC38 && res1538 == 4)
                        {
                            __int64* v11 = *reinterpret_cast<__int64**>(a1 + 0x12598);
                            int v12 = 60;
                            if (v11)
                            {
                                __int64* v13 = *reinterpret_cast<__int64**>(a1 + 0x125A0);
                                if (v13)
                                {
                                    __int64 v14;
                                    if (*reinterpret_cast<uint32_t*>(a1 + 0xEAC) == 28)
                                    {
                                        v14 = *v11;
                                    }
                                    else
                                    {
                                        v14 = *v13;
                                        v11 = *reinterpret_cast<__int64**>(a1 + 0x125A0);
                                    }
                                    using getLen_t = int(__fastcall*)(__int64*);
                                    getLen_t getLen = reinterpret_cast<getLen_t>(v14 + 24);
                                    v12 = getLen(v11);
                                }
                            }
                            unsigned int v15 = (*(__int64(__fastcall**)(__int64))(*(__int64*)(a1 + 3272) + 16i64))(a1 + 3272); // : call into a1+3272 vtable+16
                            // : v15 = (*(somefunc*)(a1+3272)->+16)(a1+3272)
                            unsigned int v16;
                            {
                                std::uintptr_t vtblA1 = *reinterpret_cast<std::uintptr_t*>(a1);
                                auto fn64 = *reinterpret_cast<std::uintptr_t*>(vtblA1 + 64);
                                using fn64_t = unsigned int(__fastcall*)(__int64);
                                v16 = reinterpret_cast<fn64_t>(fn64)(a1);
                            }
                            void* v17 = sub_140AC4880(v16, v15);
                            if (v17)
                            {
                                // *((_DWORD *)v17 + 0x4A86) = (int)(float)((float)v12 / (float)(30.0 / (float)*((unsigned __int8 *)qword_1496CF1C8 + 0x952)));
                                float denom = 30.0f / static_cast<float>(*reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 0x952));
                                int value = static_cast<int>(static_cast<float>(v12) / denom);
                                *reinterpret_cast<int*>(reinterpret_cast<char*>(v17) + (0x4A86 * 4)) = value;
                            }
                        }
                    }
                }
                return;
            }

            // v4 == 1 branch (a2 == 2)
            if ((unsigned int)sub_14098F8E0(a1) == 101 && (unsigned int)sub_14098FD20(a1))
                sub_140991940(a1, 102, /*v18*/ 0, 0xFFFFFFFF, 0, 0);

            int v19 = 1;
            if (sub_1409BCC50(reinterpret_cast<uint32_t*>(a1)))
            {
                __int64 v20 = *reinterpret_cast<__int64*>(a1 + 4680);
                int v21 = 1;
                if (v20 && (unsigned int)sub_140A33210(v20))
                    v21 = 0;
                if (sub_1409EF570(a1 + 536) && v21)
                    sub_1409D6C40(reinterpret_cast<char*>(a1));
            }

            int v22 = 0;
            {
                std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                auto fn5432 = *reinterpret_cast<std::uintptr_t*>(vtbl + 5432);
                using fn5432_t = unsigned int(__fastcall*)(__int64);
                unsigned int r = reinterpret_cast<fn5432_t>(fn5432)(a1);
                if (r == 6 || r == 4 || r == 11) v22 = 1;
            }

            {
                std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                auto fn3128 = *reinterpret_cast<std::uintptr_t*>(vtbl + 3128);
                using fn3128_t = unsigned int(__fastcall*)(__int64);
                if (!reinterpret_cast<fn3128_t>(fn3128)(a1) && !v22)
                {
                    auto fn3544 = *reinterpret_cast<std::uintptr_t*>(vtbl + 3544);
                    using fn3544_t = void(__fastcall*)(__int64, __int64);
                    reinterpret_cast<fn3544_t>(fn3544)(a1, 215);
                }
            }

            {
                std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                auto fn3136 = *reinterpret_cast<std::uintptr_t*>(vtbl + 3136);
                using fn3136_t = unsigned int(__fastcall*)(__int64);
                if (reinterpret_cast<fn3136_t>(fn3136)(a1))
                    goto LABEL_116;
            }

            if (!(*reinterpret_cast<unsigned int(__fastcall**)(__int64)>(*reinterpret_cast<std::uintptr_t*>(a1) + 3128))(a1) && v22)
            {
                if (!(*reinterpret_cast<unsigned int(__fastcall**)(__int64)>(*reinterpret_cast<std::uintptr_t*>(a1) + 3128))(a1))
                {
                    // v23 = (*(a1+3272)->+16)(a1+3272)
                    std::uintptr_t ptr3272_vtbl = *reinterpret_cast<std::uintptr_t*>(a1 + 3272);
                    auto fn16 = *reinterpret_cast<std::uintptr_t*>(ptr3272_vtbl + 16);
                    using fn16_t = int(__fastcall*)(__int64);
                    int v23 = reinterpret_cast<fn16_t>(fn16)(a1 + 3272);

                    unsigned int v24;
                    {
                        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                        auto fn64 = *reinterpret_cast<std::uintptr_t*>(vtbl + 64);
                        using fn64_t = unsigned int(__fastcall*)(__int64);
                        v24 = reinterpret_cast<fn64_t>(fn64)(a1);
                    }
                    void* v25 = sub_140AC49D0(v24, static_cast<unsigned int>(v23 - 1));
                    if (v25) sub_140A31210(v25);

                    __int64 v26 = sub_1409BB050(a1);
                    if (!v26) goto LABEL_77;

                    {
                        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                        auto fn5432 = *reinterpret_cast<std::uintptr_t*>(vtbl + 5432);
                        using fn5432_t = unsigned int(__fastcall*)(__int64);
                        unsigned int r = reinterpret_cast<fn5432_t>(fn5432)(a1);
                        if (r == 6)
                        {
                            if ((unsigned int)(*reinterpret_cast<int*>(v26 + 0xEA4) - 132) <= 1)
                                v19 = 0;
                        }
                        else if (r == 11)
                        {
                            if ((unsigned int)sub_1409CF930(v26))
                                v19 = 0;
                        }
                        else
                        {
                            __int64 v28 = (*reinterpret_cast<__int64(__fastcall**)(__int64)>(*reinterpret_cast<std::uintptr_t*>(a1) + 3512))(a1);
                            if (v28)
                            {
                                unsigned int v29 = *reinterpret_cast<uint32_t*>(v28 + 0xEA4);
                                if (v29 <= 0x12)
                                {
                                    int v30 = 335872;
                                    // _bittest(&v30, v29)
                                    if (v30 & (1 << (v29 & 31)))
                                        v19 = 0;
                                }
                            }
                            __int64 v31 = *reinterpret_cast<__int64*>(a1 + 75176);
                            if (v31)
                            {
                                auto fn24 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(v31) + 24);
                                using fn24_t = int(__fastcall*)(__int64);
                                int v32 = reinterpret_cast<fn24_t>(fn24)(v31);
                                int v33 = 0xBB8u / *reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 2386);
                                std::uint32_t mod = *reinterpret_cast<int*>(a1 + 3764) % v33;
                                int div = *reinterpret_cast<int*>(a1 + 3764) / v33;
                                float threshold = static_cast<float>(v32) / (30.0f / static_cast<float>(*reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 2386)));
                                if (div < static_cast<int>(threshold))
                                    v19 = 0;
                                // v27 stored as LODWORD trick in asm; here we reuse mod
                                v27 = static_cast<__int64>(mod);
                            }
                        }
                    }

                    {
                        // if ((*(float (__fastcall **)(__int64, __int64))(*(_QWORD *)v26 + 3480i64))(v26, v27) < 49.0 || v19)
                        fn3480 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(v26) + 3480);
                        using fn3480_t = float(__fastcall*)(__int64, __int64);
                        v27 = 0; // approximate - exact mod computed above if needed
                        if (reinterpret_cast<fn3480_t>(fn3480)(v26, v27) < 49.0f || v19)
                        {
                        LABEL_77:
                            auto fn3544 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(a1) + 3544);
                            using fn3544_t = void(__fastcall*)(__int64, __int64);
                            reinterpret_cast<fn3544_t>(fn3544)(a1, 215);
                            sub_1409DCEE0(a1);
                            return;
                        }
                        sub_1409BD3B0(a1, 0);
                        int computed = *reinterpret_cast<int*>(a1 + 3764) / (0xBB8u / *reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 2386));
                        int modulo = computed % static_cast<int>(10.0f / (30.0f / static_cast<float>(*reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 2386))));
                        if (modulo == 1)
                        {
                            auto fn5088 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(a1) + 5088);
                            using fn5088_t = void(__fastcall*)(__int64);
                            reinterpret_cast<fn5088_t>(fn5088)(a1);
                            sub_1409DCEE0(a1);
                            return;
                        }
                    }
                }
                goto LABEL_116;
            }

            if (!sub_1409EF570(a1 + 536) && !(unsigned int)(/*sub_1409EF8E0(a1+536,19)*/0))
            {
                v34 = *reinterpret_cast<int*>(a1 + 3684);
                if (v34 == 143)
                {
                    v35 = sub_14098F8E0(a1);
                    v36 = a1;
                    if (v35 != 950)
                    {
                        curState = sub_14098F8E0(a1);
                        if (curState == 102 || (curState == 101 && (unsigned int)sub_14098FD20(a1)))
                        {
                            v37 = sub_14098F510(a1, 0x1B8u, 1);
                            v39 = a1;
                            if (v37)
                            {
                                sub_140991940(a1, 950, /*v38*/0, 0xFFFFFFFF, 0, 0);
                                sub_1409DCEE0(a1);
                                return;
                            }
                        LABEL_107:
                            {
                                auto fn3552 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(a1) + 3552);
                                using fn3552_t = void(__fastcall*)(__int64);
                                reinterpret_cast<fn3552_t>(fn3552)(a1);
                            }
                            sub_1409DCEE0(a1);
                            return;
                        }
                        goto LABEL_116;
                    }
                }
                else if ((unsigned int)(v34 - 140) <= 1 || v34 == 262)
                {
                    unsigned int v43 = 947;
                    if (*reinterpret_cast<uint32_t*>(a1 + 3744) != 5) v43 = 939;
                    int v44 = sub_14098F8E0(a1);
                    v36 = a1;
                    if (v44 != static_cast<int>(v43))
                    {
                        curState = sub_14098F8E0(a1);
                        if (curState == 102 || (curState == 101 && (unsigned int)sub_14098FD20(a1)))
                        {
                            __int64 v45 = sub_14098F510(a1, v43, 1);
                            v39 = a1;
                            if (v45)
                            {
                                sub_140991940(a1, v43, /*v46*/0, 0xFFFFFFFF, 0, 0);
                                sub_1409DCEE0(a1);
                                return;
                            }
                            goto LABEL_107;
                        }
                        goto LABEL_116;
                    }
                }
                else
                {
                    if ((unsigned int)(v34 - 178) > 1 || *reinterpret_cast<uint32_t*>(a1 + 71576) != 1)
                        goto LABEL_93;
                    v40 = sub_14098F8E0(a1);
                    v36 = a1;
                    if (v40 != 936)
                    {
                        curState = sub_14098F8E0(a1);
                        if (curState == 102 || (curState == 101 && (unsigned int)sub_14098FD20(a1)))
                        {
                            __int64 v41 = sub_14098F510(a1, 0x3A8u, 1);
                            v39 = a1;
                            if (v41)
                            {
                                sub_140991940(a1, 936, /*v42*/0, 0xFFFFFFFF, 0, 0);
                                sub_1409DCEE0(a1);
                                return;
                            }
                            goto LABEL_107;
                        }
                    LABEL_116:
                        sub_1409DCEE0(a1);
                        return;
                    }
                }
                if (!(unsigned int)sub_14098FD20(a1))
                    goto LABEL_116;
            LABEL_93:
                {
                    auto fnDE0 = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(a1) + 0xDE0);
                    using fnDE0_t = void(__fastcall*)(__int64);
                    reinterpret_cast<fnDE0_t>(fnDE0)(a1);
                }
                sub_1409DCEE0(a1);
                return;
            }

            if (*reinterpret_cast<uint32_t*>(a1 + 0xE64) != 86)
            {
                e64val = *reinterpret_cast<uint32_t*>(a1 + 0xE64);
                if (e64val == 140 || e64val == 141)
                    goto LABEL_117;
                if (e64val != 203)
                {
                    if (e64val != 262)
                    {
                        v47 = *reinterpret_cast<__int64*>(a1 + 0x11600);
                        if (v47 == *reinterpret_cast<__int64*>(a1 + 0x11608))
                            goto LABEL_116;
                        while ((int)sub_14098F8A0(a1) < *reinterpret_cast<int*>(a1 + 0x11620))
                        {
                            v47 += 8;
                            if (v47 == *reinterpret_cast<__int64*>(a1 + 0x11608))
                                goto LABEL_116;
                        }
                    LABEL_124:
                        GuardEffectParam::sub_1409D6220_SC(a1, 1);
                        goto LABEL_116;
                    }
                LABEL_117:
                    {
                        unsigned int st = sub_14098F8E0(a1);
                        if (st != 101 && st != 102)
                        {
                            if (sub_14098F510(a1, 0x65u, 1))
                                sub_140991940(a1, 101, /*v48*/0, 0xFFFFFFFF, 0, 0);
                            else
                                sub_140991940(a1, 102, /*v48*/0, 0xFFFFFFFF, 0, 0);
                        }
                    }
                    goto LABEL_116;
                }
            }
            {
                std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(a1);
                auto fn4704 = *reinterpret_cast<std::uintptr_t*>(vtbl + 4704);
                using fn4704_t = unsigned int(__fastcall*)(__int64);
                if (!reinterpret_cast<fn4704_t>(fn4704)(a1)) goto LABEL_116;
            }
            int v49 = static_cast<int>(std::floor(20.0f / (30.0f / static_cast<float>(*reinterpret_cast<unsigned char*>(reinterpret_cast<std::uintptr_t>(Common::GetQwordPtr(0x1496CF1C8)) + 2386)))));
            if ((int)sub_14098F8A0(a1) < v49) goto LABEL_116;
            goto LABEL_124;
        }

        // a2 == 0 branch
        sub_140A3C2D0(a1 + 50544);
        int v50 = 0;
        *reinterpret_cast<uint32_t*>(a1 + 340) = 0;
        sub_1409BD3B0(a1, 1u);
        sub_1409A34B0(a1, reinterpret_cast<void*>(a1 + 264));
        sub_1405F42F0(*reinterpret_cast<__int64*>(a1 + 520), reinterpret_cast<void*>(a1 + 264));
        sub_1405E9580(*reinterpret_cast<__int64*>(a1 + 520));
        if (!(*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0xC38i64))(a1))
        {
            v54 = 440;
            if (!sub_14098F510(a1, 0x1B8u, 1i64))
            {
                if (*(int*)(a1 + 69052))
                    v54 = 102 - (sub_14098F510(a1, 0x65u, 1i64) != 0);
                else
                    v54 = 111;
            }
            sub_140991940(a1, v54, 0, 0xFFFFFFFFi64, 0, 0);
            v53 = 1;
            goto LABEL_135;
        }
        v51 = sub_14098F510(a1, 0x65u, 1i64);
        sub_140991940(a1, 102 - (unsigned int)(v51 != 0), 0, 0xFFFFFFFFi64, 0, 0);
        if (*(int*)(a1 + 3684) != 114 || *(int*)(a1 + 3752) != 74)
        {
            v53 = 0;
        LABEL_135:
            GuardEffectParam::sub_1409D6220_SC(a1, v53);
        }
        __int64 v56 = *reinterpret_cast<__int64*>(*reinterpret_cast<__int64*>(Common::GetQwordPtr(0x14219D7E0)) + 472);
        if (sub_140B533A0(v56) && (*(unsigned int(__fastcall**)(__int64))(*reinterpret_cast<std::uintptr_t*>(a1) + 3128))(a1))
        {
            int v57 = (*reinterpret_cast<int(__fastcall**)(__int64)>(*reinterpret_cast<std::uintptr_t*>(a1) + 64))(a1);
            sub_140B53940(v56, v57, 18);
            v50 = ((*reinterpret_cast<unsigned int(__fastcall**)(__int64)>(*reinterpret_cast<std::uintptr_t*>(a1) + 64))(a1) == 0) ? 1 : 0;
            sub_140B53940(v56, v50, 19);
        }

        return;
    }
}



GuardEffectParam::sub_140981280_t GuardEffectParam::orig_sub_140981280 = nullptr;
void** __fastcall GuardEffectParam::hk_sub_140981280_SC(__int64 a1)
{
    // call original first
    void** result = GuardEffectParam::orig_sub_140981280(a1);

    // minimal base offset rule (if you use moduleBase offsets anywhere later)
    constexpr std::uintptr_t BASE_SUB = 0x140000C00ULL;

    // typedef  sub_1409DCEB0 (    ) 
    typedef __int64(__fastcall* fn_1409DCEB0_t)(int* ptr);
    constexpr std::uintptr_t OFF_1409DCEB0 = 0x1409DCEB0;
    //   
    fn_1409DCEB0_t sub_1409DCEB0 = reinterpret_cast<fn_1409DCEB0_t>(moduleBase + (OFF_1409DCEB0 - BASE_SUB));

    // read char id and awakened flag
    uint32_t charID = *reinterpret_cast<uint32_t*>(a1 + 0xE64);
    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1);

    // lookup entry in your file-based table
    GuardEffectParamEntry* entry = GetGuardEffectEntry(charID, isAwakened);

    if (!entry) {
        // not present in file -> keep original behaviour only
        return result;
    }

    // mode check: 0 = base-only, 1 = awakened-only, 2 = both
    if (entry->Mode == 0 && isAwakened) {
        // base-only but object is awakened -> do nothing extra
        return result;
    }
    if (entry->Mode == 1 && !isAwakened) {
        // awaken-only but object not awakened -> do nothing extra
        return result;
    }

    // At this point: entry exists AND Mode permits current awakened state.
    // Perform the same cleanup loop as in original: iterate [a1+0x11600 .. a1+0x11608) and call sub_1409DCEB0(*i)
    void** start = *reinterpret_cast<void***>(a1 + 0x11600);
    void** end = *reinterpret_cast<void***>(a1 + 0x11608);

    if (start && end) {
        // Minimal safety: make sure end >= start (in pointer terms)
        if (end >= start) {
            for (void** it = start; it != end; ++it) {
                void* p = *it;
                if (p) {
                    // many disassemblies show int* but any pointer works
                    sub_1409DCEB0(reinterpret_cast<int*>(p));
                }
            }
        }
    }

   

    // You can also load loop/end here depending on other conditions  e.g.
    // if (needLoop) GuardEffectParam::sub_1409D6220_SC(a1, 1);
    // if (needEnd)  GuardEffectParam::sub_1409D6220_SC(a1, 2);

    return result;
}


GuardEffectParam::orig_sub_1407AFADC_t GuardEffectParam::orig_sub_1407AFADC = nullptr;
__int64 __fastcall GuardEffectParam::sub_1407AFADC_S4(__int64 a1, __int64 a2)
{
    __int64 result;
    char* v8; // rdx
    __int64 v4; // rcx
    const char* startEffect; // rcx
    const char* loopEffect; // rcx
    const char* endEffect; // rcx
    const char* currentEffect; // rcx
    char* LoadEffectFile; // rsi
    int CharacodeID = *(int*)(a1 + 0xC8C);
    void* ccPlayerActionGuard; // rax
    __int64 ccPlayerActionGuardAddress; // rbx
    __int64 v66[3]; // [rsp+48h] [rbp-E0h] BYREF
    __int64 CoordByFullName; // rbp
    __int64 v54; // rcx
    int v55; // eax
    __int64 v70_unknown[16]; //  __int128 v70_unknown[4]
    typedef __int64(__fastcall* t_sub_14055D040)(__int64 a1, int a2);
    static t_sub_14055D040 sub_14055D040 = (t_sub_14055D040)(moduleBase + 0x55C440);

    typedef __int64* (__fastcall* t_sub_140A0D810)(__int64* a1);
    static t_sub_140A0D810 sub_140A0D810 = (t_sub_140A0D810)(moduleBase + 0xA0CC10);

    typedef __int64(__fastcall* t_sub_1405583A8)(__int64 a1, __int64 a2);
    static t_sub_1405583A8 sub_1405583A8 = (t_sub_1405583A8)(moduleBase + 0x5577A8);

    typedef __int64* (__fastcall* t_sub_140A0D850)(__int64* a1, __int64* a2);
    static t_sub_140A0D850 sub_140A0D850 = (t_sub_140A0D850)(moduleBase + 0xA0CC50);

    typedef __int64(__fastcall* t_sub_1407B03B4)(__int64* a1);
    static t_sub_1407B03B4 sub_1407B03B4 = (t_sub_1407B03B4)(moduleBase + 0x7AF7B4);

    typedef void* (__fastcall* t_sub_140A017F0)(size_t a1, __int64 a2, int a3);
    static t_sub_140A017F0 sub_140A017F0 = (t_sub_140A017F0)(moduleBase + 0xA00BF0);

    typedef __int64(__fastcall* t_sub_1407B5664)(__int64 a1);
    static t_sub_1407B5664 sub_1407B5664 = (t_sub_1407B5664)(moduleBase + 0x7B4A64);

    typedef char* (__fastcall* t_sub_14079B88C)(__int64 a1, __int64 a2);
    static t_sub_14079B88C sub_14079B88C = (t_sub_14079B88C)(moduleBase + 0x79AC8C);

    typedef __int64(__fastcall* t_sub_1407B5714)(__int64* a1, char* a2, __int64 a3);
    static t_sub_1407B5714 sub_1407B5714 = (t_sub_1407B5714)(moduleBase + 0x7B4B14);

    typedef __int64(__fastcall* t_sub_14047ED14)(__int64 a1);
    static t_sub_14047ED14 sub_14047ED14 = (t_sub_14047ED14)(moduleBase + 0x47E114);

    typedef unsigned __int64(__fastcall* t_sub_1407B05BC)(unsigned __int64* a1, unsigned __int64* a2);
    static t_sub_1407B05BC sub_1407B05BC = (t_sub_1407B05BC)(moduleBase + 0x7AF9BC);

    __int64 v50; // rcx
    void** v46; // rdx
    void* Block[3]; // [rsp+78h] [rbp-B0h] BYREF
    __int64 v67[3]; // [rsp+60h] [rbp-C8h] BYREF
    unsigned __int64 v69; // [rsp+90h] [rbp-98h]
    void* v47; // rbx
    int v48; // eax
    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1);
    //Console::PrintErr("CharacodeID 0x%X\n", CharacodeID);


    GuardEffectParamEntry* entry = GetGuardEffectEntry(CharacodeID, isAwakened);

    //Console::PrintErr("State = %d\n", a2);
    if (entry) {
        v66[1] = a1;
        (*(void(__fastcall**)(__int64))(*(__int64*)a1 + 8i64))(a1);

        v4 = *(__int64*)(a1 + 0x14E18);
        if (v4)
            sub_14055D040(v4, a2);
        __int64 pool = *(__int64*)(a1 + 520);
        //Console::PrintErr("Code Executed\n");
        startEffect = (entry->StartEffect).c_str();
        loopEffect = (entry->LoopEffect).c_str();
        endEffect = (entry->EndEffect).c_str();
        if (a2 == 1)
            currentEffect = loopEffect;
        else if (a2 == 2)
            currentEffect = endEffect;
        else
            currentEffect = startEffect;

        //Console::PrintErr("Current Effect = %d - %s\n", a2, currentEffect);
        sub_140A0D810(v70_unknown);
        CoordByFullName = sub_1405583A8(*(__int64*)(a1 + 520), (__int64)(entry->Coord).c_str());


        /* sub_1400B6920_f((char*)v67, (__int64*)(*(__int64*)(a1 + 520) + 0x35E0i64));
         sub_1400B3830_f(v67, "00t0 trall", 0xAui64);
         v46 = Block;
         if (v69 >= 0x10)
             v46 = (void**)Block[0];
         if (v69 >= 0x10)
         {
             v47 = Block[0];
             v48 = sub_14124BFE0((__int64)v67);
             sub_14124C1D0(v48);
             sub_14124BB20(v47);
             sub_14124C170();
         }
         Block[2] = 0i64;
         v69 = 15i64;
         *reinterpret_cast<unsigned char*>(&Block[0]) = 0;
         v67[0] = *reinterpret_cast<__int64*>(moduleBase + 0x1735AF8);*/


        if (!CoordByFullName)
            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);

        sub_140A0D850(
            v70_unknown,
            (__int64*)(CoordByFullName + ((unsigned __int64)*(unsigned __int8*)(CoordByFullName + 288) << 6) + 124));
        v50 = *(__int64*)(a1 + 0x14A48);
        if (v50)
        {
            sub_140A0D850((__int64*)(v50 + 40), v70_unknown);
            return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
        }

        //v8 = *(char**)(a1 + 0x12040);
        sub_1407B03B4((__int64*)a1);
        ccPlayerActionGuard = sub_140A017F0(
            0x70ui64,
            (__int64)"D:\\Jenkins\\workspace\\Update_SVN\\narutoNext4_trunk\\narutoNext4\\prog\\source\\ccPlayerActionGuard.cpp",
            745);
        v66[2] = (__int64)ccPlayerActionGuard;
        if (ccPlayerActionGuard)
            ccPlayerActionGuardAddress = sub_1407B5664((__int64)ccPlayerActionGuard);
        else
            ccPlayerActionGuardAddress = 0;


        LoadEffectFile = sub_14079B88C(a1, (__int64)(entry->EffectPath).c_str());

        //Console::PrintErr("LoadEffectFile= %s\n", LoadEffectFile);
        sub_1407B5714((__int64*)ccPlayerActionGuardAddress, LoadEffectFile, (__int64)currentEffect);

        sub_140A0D850((__int64*)(ccPlayerActionGuardAddress + 40), v70_unknown);
        v66[0] = ccPlayerActionGuardAddress;
        v8 = *(char**)(a1 + 0x14A18);
        if (v8 == *(char**)(a1 + 0x14A20))
        {
            sub_1407B05BC((unsigned __int64*)(a1 + 0x14A18), (unsigned __int64*)v66);
        }
        else
        {
            *(__int64*)v8 = ccPlayerActionGuardAddress;
            *(__int64*)(a1 + 0x14A18) += 8i64;
        }
        v54 = *(__int64*)(ccPlayerActionGuardAddress + 32);
        if (!v54 || a2)
        {
            //Console::PrintErr("Loop\n");
            if (a2 == 1)
                *(__int64*)(a1 + 0x14A48) = ccPlayerActionGuardAddress;
        }
        else
        {

            //Console::PrintErr("Not Loop\n");
            v55 = sub_14047ED14(v54);
            v8 = (char*)((unsigned int)*((unsigned __int8*)Common::GetQword(0x1416663C8) + 0x942) * v55 % 0xBB8);
            *(int*)(a1 + 0x14A50) = (unsigned int)*((unsigned __int8*)Common::GetQword(0x1416663C8) + 0x942) * v55 / 0xBB8;
        }
        //Console::PrintErr("Code Finished\n");
        return (*(__int64(__fastcall**)(__int64, char*))(*(__int64*)a1 + 16i64))(a1, v8);
    }
    else {

        //Console::PrintErr("State = %d\n", a2);
        result = GuardEffectParam::orig_sub_1407AFADC(a1, a2);
        return result;
    }


}


GuardEffectParam::t_sub_1407AEBF8 GuardEffectParam::orig_sub_1407AEBF8 = nullptr;
// corrected and cleaned translation of sub_1407AEBF8 in your style
void** __fastcall GuardEffectParam::hk_sub_1407AEBF8_S4(__int64 a1, int a2, __int64 a3)
{
    void* retaddr_local = nullptr;
    void** result = reinterpret_cast<void**>(&retaddr_local);
    __int64 v36 = 0;
    __int64 v39 = 0;
    int modVal = 0;
    unsigned char* globalPtr = nullptr;
    int v55 = 0;
    __int64 found = 0;
    int curState = 0;

    constexpr std::uintptr_t BASE_SUB = 0x140000C00ULL;

    // typedefs (keep these - they match your previous guesses)
    typedef __int64(__fastcall* t_sub_14077E64C)(__int64, __int64, __int64, __int64, int, int);
    static t_sub_14077E64C sub_14077E64C = reinterpret_cast<t_sub_14077E64C>(moduleBase + (0x14077E64CULL - BASE_SUB));

    typedef void(__fastcall* t_sub_1406B5D14)(__int64*, int, int);
    static t_sub_1406B5D14 sub_1406B5D14 = reinterpret_cast<t_sub_1406B5D14>(moduleBase + (0x1406B5D14ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407B03B4)(__int64*);
    static t_sub_1407B03B4 sub_1407B03B4 = reinterpret_cast<t_sub_1407B03B4>(moduleBase + (0x1407B03B4ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_14077DB38)(__int64);
    static t_sub_14077DB38 sub_14077DB38 = reinterpret_cast<t_sub_14077DB38>(moduleBase + (0x14077DB38ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_14077DD4C)(__int64);
    static t_sub_14077DD4C sub_14077DD4C = reinterpret_cast<t_sub_14077DD4C>(moduleBase + (0x14077DD4CULL - BASE_SUB));

    typedef bool(__fastcall* t_sub_14079C53C)(__int64);
    static t_sub_14079C53C sub_14079C53C = reinterpret_cast<t_sub_14079C53C>(moduleBase + (0x14079C53CULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407ED2B4)(__int64);
    static t_sub_1407ED2B4 sub_1407ED2B4 = reinterpret_cast<t_sub_1407ED2B4>(moduleBase + (0x1407ED2B4ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407C0B7C)(__int64);
    static t_sub_1407C0B7C sub_1407C0B7C = reinterpret_cast<t_sub_1407C0B7C>(moduleBase + (0x1407C0B7CULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407B0190)(__int64);
    static t_sub_1407B0190 sub_1407B0190 = reinterpret_cast<t_sub_1407B0190>(moduleBase + (0x1407B0190ULL - BASE_SUB));

    typedef void* (__fastcall* t_sub_14085B488)(unsigned int, unsigned int);
    static t_sub_14085B488 sub_14085B488 = reinterpret_cast<t_sub_14085B488>(moduleBase + (0x14085B488ULL - BASE_SUB));

    typedef int* (__fastcall* t_sub_14085B588)(unsigned int, unsigned int);
    static t_sub_14085B588 sub_14085B588 = reinterpret_cast<t_sub_14085B588>(moduleBase + (0x14085B588ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407EBEC8)(int*);
    static t_sub_1407EBEC8 sub_1407EBEC8 = reinterpret_cast<t_sub_1407EBEC8>(moduleBase + (0x1407EBEC8ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_14079B950)(__int64);
    static t_sub_14079B950 sub_14079B950 = reinterpret_cast<t_sub_14079B950>(moduleBase + (0x14079B950ULL - BASE_SUB));

    typedef bool(__fastcall* t_sub_1407ABFB4)(__int64);
    static t_sub_1407ABFB4 sub_1407ABFB4 = reinterpret_cast<t_sub_1407ABFB4>(moduleBase + (0x1407ABFB4ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407B581C)(__int64);
    static t_sub_1407B581C sub_1407B581C = reinterpret_cast<t_sub_1407B581C>(moduleBase + (0x1407B581CULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_14077DA68)(__int64, unsigned int, __int64);
    static t_sub_14077DA68 sub_14077DA68 = reinterpret_cast<t_sub_14077DA68>(moduleBase + (0x14077DA68ULL - BASE_SUB));

    typedef int(__fastcall* t_sub_14077DAF8)(__int64);
    static t_sub_14077DAF8 sub_14077DAF8 = reinterpret_cast<t_sub_14077DAF8>(moduleBase + (0x14077DAF8ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_1407F3FFC)(__int64);
    static t_sub_1407F3FFC sub_1407F3FFC = reinterpret_cast<t_sub_1407F3FFC>(moduleBase + (0x1407F3FFCULL - BASE_SUB));

    typedef __int64* (__fastcall* t_sub_14078B070)(__int64, void*);
    static t_sub_14078B070 sub_14078B070 = reinterpret_cast<t_sub_14078B070>(moduleBase + (0x14078B070ULL - BASE_SUB));

    typedef __int64(__fastcall* t_sub_14055A48C)(__int64, __int64);
    static t_sub_14055A48C sub_14055A48C = reinterpret_cast<t_sub_14055A48C>(moduleBase + (0x14055A48CULL - BASE_SUB));

    typedef unsigned __int64(__fastcall* t_sub_140554764)(__int64);
    static t_sub_140554764 sub_140554764 = reinterpret_cast<t_sub_140554764>(moduleBase + (0x140554764ULL - BASE_SUB));

    typedef void(__fastcall* t_DeleteExceptionPtr)(__int64, __int64);
    static t_DeleteExceptionPtr DeleteExceptionPtr = reinterpret_cast<t_DeleteExceptionPtr>(moduleBase + 0x79BD94);

    typedef unsigned int(__fastcall* t_sub_1407C0DD8)(__int64, int);
    static t_sub_1407C0DD8 sub_1407C0DD8 = reinterpret_cast<t_sub_1407C0DD8>(moduleBase + (0x1407C0DD8ULL - BASE_SUB));

    // --- CORRECT vtable helper (was the crash origin) ---
    auto get_vfunc_ptr = [&](std::uintptr_t obj, std::size_t vfuncOffset) -> std::uintptr_t {
        // obj is the `this` pointer (a1)
        std::uintptr_t vtbl = *reinterpret_cast<std::uintptr_t*>(obj);            // read vtable pointer
        return *reinterpret_cast<std::uintptr_t*>(vtbl + vfuncOffset);           // read function ptr from vtable
        };

    auto call_vfunc_uint_noargs = [&](std::uintptr_t obj, std::size_t vfuncOffset) -> unsigned int {
        std::uintptr_t fnptr = get_vfunc_ptr(obj, vfuncOffset);
        using fn_t = unsigned int(__fastcall*)(__int64);
        return reinterpret_cast<fn_t>(fnptr)(obj);
        };

    auto call_vfunc_uint_3args = [&](std::uintptr_t obj, std::size_t vfuncOffset, std::int64_t p1, std::int64_t p2) -> unsigned int {
        std::uintptr_t fnptr = get_vfunc_ptr(obj, vfuncOffset);
        using fn_t = unsigned int(__fastcall*)(__int64, __int64, __int64);
        return reinterpret_cast<fn_t>(fnptr)(obj, p1, p2);
        };

    auto call_vfunc_void_1arg = [&](std::uintptr_t obj, std::size_t vfuncOffset, std::int64_t arg) -> void {
        std::uintptr_t fnptr = get_vfunc_ptr(obj, vfuncOffset);
        using fn_t = void(__fastcall*)(__int64, __int64);
        reinterpret_cast<fn_t>(fnptr)(obj, arg);
        };

    // --- preserve original logic but fixed vtable usage ---
    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1);
    GuardEffectParamEntry* entry = GetGuardEffectEntry(*reinterpret_cast<int*>(a1 + 0xC8C), isAwakened);
    if (!entry)
        return GuardEffectParam::orig_sub_1407AEBF8(a1, a2, a3);

    if (a2)
    {
        int v5 = a2 - 1;
        if (v5)
        {
            unsigned int v6 = static_cast<unsigned int>(v5 - 1);
            if (v6)
            {
                if (v6 == 5)
                {
                    sub_14077E64C(a1, 102, a3, 0xFFFFFFFF, 0, 0);
                    return result;
                }
                return result;
            }

            // a2 == 2 path
            if (*reinterpret_cast<int*>(a1 + 0xCC8) != 74)
            {
                __int64* ptr = *reinterpret_cast<__int64**>(a1 + 0xFD90);
                sub_1406B5D14(ptr, 4, 6);
            }

            bool pass = false;
            if (entry->Mode == 0 && !isAwakened) pass = true;
            else if (entry->Mode == 1 && isAwakened) pass = true;
            else if (entry->Mode == 2) pass = true;

            if (*reinterpret_cast<int*>(a1 + 0xCC8) != 74 && entry && pass)
            {
                __int64 cur = *reinterpret_cast<__int64*>(a1 + 0x14A48);
                if (cur)
                {
                    *reinterpret_cast<int*>(cur + 104) = 1;
                    *reinterpret_cast<__int64*>(a1 + 0x14A48) = 0;
                    *reinterpret_cast<int*>(a1 + 0x14A50) = 0;
                    sub_1407B03B4(reinterpret_cast<__int64*>(a1));
                }
                GuardEffectParam::sub_1407AFADC_S4(a1, 2);
            }

        LABEL_33:
            if (*reinterpret_cast<int*>(a1 + 0xCC8) != 74 && *reinterpret_cast<__int64*>(a1 + 0x14E18))
            {
                __int64 cur2 = *reinterpret_cast<__int64*>(a1 + 0x14A48);
                if (cur2)
                {
                    *reinterpret_cast<int*>(cur2 + 104) = 1;
                    *reinterpret_cast<__int64*>(a1 + 0x14A48) = 0;
                    *reinterpret_cast<int*>(a1 + 0x14A50) = 0;
                }

                for (int i = 0; i < 3; ++i)
                {
                    // call vfunc at a1->someptr + 8 (original)
                    std::uintptr_t fnptr = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(a1 + 0xF7E0) + 8);
                    using fn_t = void(__fastcall*)(__int64, std::uint64_t, __int64);
                    reinterpret_cast<fn_t>(fnptr)(a1 + 0xF7E0, (unsigned int)i, a3);
                }
                GuardEffectParam::sub_1407AFADC_S4(a1, 2);
            }

            // call vfunc@0xC08(a1, v6, a3)
            {
                std::uintptr_t fnptr = get_vfunc_ptr(a1, 0xC08);
                using fnC08_t = int(__fastcall*)(__int64, __int64, __int64);
                int callRes = reinterpret_cast<fnC08_t>(fnptr)(a1, v6, a3);
                if (!callRes)
                {
                    unsigned int st = call_vfunc_uint_noargs(a1, 0x1418);
                    if (st == 4)
                    {
                        __int64* v20 = *reinterpret_cast<__int64**>(a1 + 0x151A8);
                        int v21 = 60;
                        if (v20)
                        {
                            __int64* v22 = *reinterpret_cast<__int64**>(a1 + 0x151B0);
                            if (v22)
                            {
                                std::uintptr_t which = (*reinterpret_cast<int*>(a1 + 0xCC8) == 28) ? *reinterpret_cast<std::uintptr_t*>(v20[0]) : *reinterpret_cast<std::uintptr_t*>(v22[0]);
                                __int64* target = (*reinterpret_cast<int*>(a1 + 0xCC8) == 28) ? v20 : *reinterpret_cast<__int64**>(a1 + 0x151B0);
                                std::uintptr_t fn24 = *reinterpret_cast<std::uintptr_t*>(which + 24);
                                using fn24_t = int(__fastcall*)(__int64*);
                                v21 = reinterpret_cast<fn24_t>(fn24)(target);
                            }
                        }

                        unsigned int v24 = (*(__int64(__fastcall**)(__int64))(*(__int64*)(a1 + 0xB00) + 16i64))(a1 + 0xB00);
                        unsigned int v25 = call_vfunc_uint_noargs(a1, 64);
                        void* resultObj = sub_14085B488(v25, v24);
                        if (resultObj)
                        {
                            unsigned char* globalPtr = reinterpret_cast<unsigned char*>(Common::GetQwordPtr(0x1416663C8));
                            unsigned char speedByte = *(globalPtr + 0x942);
                            *reinterpret_cast<int*>(reinterpret_cast<char*>(resultObj) + 0x554D) =
                                static_cast<int>(static_cast<float>(v21) / (30.0f / static_cast<float>(speedByte)));
                        }
                    }
                }
            }
            return result;
        }

        // a2 == 1 branch
        if ((unsigned int)sub_14077DB38(a1) == 101 && (unsigned int)sub_14077DD4C(a1))
            sub_14077E64C(a1, 102, 0, 0xFFFFFFFF, 0, 0);

        if (sub_14079C53C(a1))
        {
            __int64 v27 = *reinterpret_cast<__int64*>(a1 + 4176);
            int v28 = 1;
            if (v27 && (unsigned int)sub_1407ED2B4(v27))
                v28 = 0;
            if ((unsigned int)sub_1407C0B7C(a1 + 536) && v28)
                sub_1407B0190(a1);
        }

        int v29 = 0;
        unsigned int state = call_vfunc_uint_noargs(a1, 0x1418);
        if (state == 6 || state == 4 || state == 11)
            v29 = 1;

        // if (!vfunc@0xC08 && !v29) call vfunc@0xDA8(a1,215)
        {
            unsigned int resC08 = call_vfunc_uint_noargs(a1, 0xC08);
            if (!resC08 && !v29)
                call_vfunc_void_1arg(a1, 0xDA8, 215);
        }

        // if vfunc@0xC10 returns true -> sub_1407B581C
        {
            unsigned int resC10 = call_vfunc_uint_noargs(a1, 0xC10);
            if (resC10)
                return reinterpret_cast<void**>(sub_1407B581C(a1));
        }

        // big block: if (!vfunc@3080(a1) && v29) { ... }
        {
            unsigned int res3080 = call_vfunc_uint_noargs(a1, 3080);
            if (!res3080 && v29)
            {
                unsigned int v30 = (*(__int64(__fastcall**)(__int64))(*(__int64*)(a1 + 2816) + 16i64))(a1 + 2816);
                if (v30) --v30;
                unsigned int v31 = call_vfunc_uint_noargs(a1, 64);
                int* v32 = reinterpret_cast<int*>(sub_14085B588(v31, v30));
                if (v32) sub_1407EBEC8(v32);

                int v33 = 1;
                __int64 v34 = sub_14079B950(a1);
                if (!v34)
                {
                    call_vfunc_void_1arg(a1, 3496, 215);
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }

                unsigned int v5144 = call_vfunc_uint_noargs(a1, 5144);
                if (v5144 == 6)
                {
                    if ((unsigned int)(*reinterpret_cast<int*>(v34 + 3264) - 132) > 1)
                        goto LABEL_85;
                }
                else
                {
                    if (v5144 != 11)
                    {
                        v36 = (*reinterpret_cast<__int64(__fastcall**)(__int64)>(*reinterpret_cast<__int64*>(a1) + 3464))(a1);
                        if (v36)
                        {
                            unsigned int v37 = *reinterpret_cast<unsigned int*>(v36 + 0xCC0);
                            if (v37 <= 0x12)
                            {
                                unsigned int mask = 335872u;
                                if (mask & (1u << v37))
                                    v33 = 0;
                            }
                        }

                        v39 = *reinterpret_cast<__int64*>(a1 + 0x151B8);
                        modVal = 0;
                        if (v39)
                        {
                            // call v39->vtable+24  : int fn(__int64)
                            std::uintptr_t fnptr = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uintptr_t*>(v39) + 24);
                            using fn24_t = int(__fastcall*)(__int64);
                            int v40 = reinterpret_cast<fn24_t>(fnptr)(v39);

                            globalPtr = reinterpret_cast<unsigned char*>(Common::GetQwordPtr(0x1416663C8));
                            int divider = 0xBB8u / *(globalPtr + 2370);
                            int value = *reinterpret_cast<int*>(a1 + 3280);
                            int mod = value % divider;
                            int div = value / divider;
                            float threshold = static_cast<float>(v40) / (30.0f / static_cast<float>(*(globalPtr + 2370)));
                            if (div < static_cast<int>(threshold))
                                v33 = 0;
                            modVal = mod;
                        }

                    LABEL_85:
                        std::uintptr_t fn3432 = *reinterpret_cast<std::uintptr_t*>(v34 + 3432);
                        using fn3432_t = float(__fastcall*)(__int64, __int64);
                        float fval = reinterpret_cast<fn3432_t>(fn3432)(v34, static_cast<__int64>(modVal));
                        if (fval < 49.0f)
                            v33 = 1;

                        if (!v33)
                        {
                            DeleteExceptionPtr(a1, 0);
                            globalPtr = reinterpret_cast<unsigned char*>(Common::GetQwordPtr(0x1416663C8));
                            int denom = 0xBB8u / *(globalPtr + 0x942);
                            int computedVal = *reinterpret_cast<int*>(a1 + 3280) / denom;
                            int modulo = computedVal % static_cast<int>(10.0f / (30.0f / static_cast<float>(*(globalPtr + 0x942))));
                            if (modulo == 1)
                            {
                                std::uintptr_t fn4832 = get_vfunc_ptr(a1, 4832);
                                using fn4832_t = void(__fastcall*)(__int64);
                                reinterpret_cast<fn4832_t>(fn4832)(a1);
                            }
                            return reinterpret_cast<void**>(sub_1407B581C(a1));
                        }
                        goto LABEL_90;
                    }
                    else
                    {
                        if (!sub_1407ABFB4(v34))
                            goto LABEL_85;
                    }
                    v33 = 0;
                    goto LABEL_85;
                }
            LABEL_90:
                ;
            }
        }

        // sub_1407C0B7C(a1 + 536) || sub_1407C0DD8(a1+536,18)
        if ((unsigned int)sub_1407C0B7C(a1 + 536) || (unsigned int)sub_1407C0DD8(a1 + 536, 18))
        {
            int v51 = *reinterpret_cast<int*>(a1 + 0xC8C);
            if (v51 != 86)
            {
                if (v51 <= 139)
                    goto LABEL_120;
                if (v51 <= 141)
                {
                    if ((unsigned int)sub_14077DB38(a1) != 101 && (unsigned int)sub_14077DB38(a1) != 102)
                    {
                        if (sub_14077DA68(a1, 0x65u, 1))
                            sub_14077E64C(a1, 101, 0, 0xFFFFFFFF, 0, 0);
                        else
                            sub_14077E64C(a1, 102, 0, 0xFFFFFFFF, 0, 0);
                    }
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }
                if (v51 != 203)
                {
                LABEL_120:
                    for (__int64 j = *reinterpret_cast<__int64*>(a1 + 0x14A18); j != *reinterpret_cast<__int64*>(a1 + 0x14A20); j += 8)
                    {
                        if ((int)sub_14077DAF8(a1) >= *reinterpret_cast<int*>(a1 + 0x14A50))
                            goto LABEL_134;
                    }
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }
            }

            if ((*(unsigned int(__fastcall**)(__int64))(*reinterpret_cast<__int64*>(a1) + 4536))(a1))
            {
                globalPtr = reinterpret_cast<unsigned char*>(Common::GetQwordPtr(0x1416663C8));
                v55 = *(globalPtr + 2370);
                if ((int)sub_14077DAF8(a1) >= static_cast<int>(20.0f / (30.0f / (float)v55)))
                    LABEL_134:
                GuardEffectParam::sub_1407AFADC_S4(a1, 1);
            }
            return reinterpret_cast<void**>(sub_1407B581C(a1));
        }

        // remaining state-selection branch
        {
            int v42 = *reinterpret_cast<int*>(a1 + 3212);
            if (v42 == 143)
            {
                int cur = (int)sub_14077DB38(a1);
                if (cur == 950) goto LABEL_95;
                if ((unsigned int)sub_14077DB38(a1) != 102 && ((unsigned int)sub_14077DB38(a1) != 101 || !(unsigned int)sub_14077DD4C(a1)))
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                found = sub_14077DA68(a1, 440, 1);
                if (found)
                {
                    sub_14077E64C(a1, 440, 0, 0xFFFFFFFF, 0, 0);
                LABEL_95:
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }
                call_vfunc_void_1arg(a1, 0xDB0, 0);
                return reinterpret_cast<void**>(sub_1407B581C(a1));
            }
            else
            {
                if ((unsigned int)(v42 - 140) <= 1)
                {
                    unsigned int want = 939;
                    if (*reinterpret_cast<int*>(a1 + 0xCBC) == 5) want = 947;
                    int cur = (int)sub_14077DB38(a1);
                    if (cur == (int)want) { call_vfunc_void_1arg(a1, 0xDB0, 0); return reinterpret_cast<void**>(sub_1407B581C(a1)); }
                    if ((unsigned int)sub_14077DB38(a1) != 102 && ((unsigned int)sub_14077DB38(a1) != 101 || !(unsigned int)sub_14077DD4C(a1)))
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    found = sub_14077DA68(a1, want, 1);
                    if (found)
                    {
                        sub_14077E64C(a1, want, 0, 0xFFFFFFFF, 0, 0);
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    }
                    call_vfunc_void_1arg(a1, 0xDB0, 0);
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }
                else
                {
                    if ((unsigned int)(v42 - 178) > 1 || *reinterpret_cast<int*>(a1 + 0x14BA8) != 1)
                    {
                        call_vfunc_void_1arg(a1, 0xDB0, 0);
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    }
                    curState = (int)sub_14077DB38(a1);
                    if (curState == 936)
                    {
                        if (!(unsigned int)sub_14077DD4C(a1))
                            return reinterpret_cast<void**>(sub_1407B581C(a1));
                        call_vfunc_void_1arg(a1, 0xDB0, 0);
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    }
                    if ((unsigned int)sub_14077DB38(a1) != 102 && ((unsigned int)sub_14077DB38(a1) != 101 || !(unsigned int)sub_14077DD4C(a1)))
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    found = sub_14077DA68(a1, 936, 1);
                    if (found)
                    {
                        sub_14077E64C(a1, 936, 0, 0xFFFFFFFF, 0, 0);
                        return reinterpret_cast<void**>(sub_1407B581C(a1));
                    }
                    call_vfunc_void_1arg(a1, 0xDB0, 0);
                    return reinterpret_cast<void**>(sub_1407B581C(a1));
                }
            }
        }
    }

    // a2 == 0 branch
    sub_1407F3FFC(a1 + 64360);
    *reinterpret_cast<int*>(a1 + 340) = 0;
    DeleteExceptionPtr(a1, 1);
    sub_14078B070(a1, reinterpret_cast<void*>(a1 + 264));
    sub_14055A48C(*reinterpret_cast<__int64*>(a1 + 520), a1 + 264);
    sub_140554764(*reinterpret_cast<__int64*>(a1 + 520));

    // if (!vfunc@0xC08(a1))
    if (!call_vfunc_uint_noargs(a1, 0xC08))
    {
        if (sub_14077DA68(a1, 0x1B8u, 1))
        {
            sub_14077E64C(a1, 440, 0, 0xFFFFFFFF, 0, 0);
            GuardEffectParam::sub_1407AFADC_S4(a1, 1);
            return result;
        }
        if (!*reinterpret_cast<int*>(a1 + 0x141EC))
        {
            sub_14077E64C(a1, 111, 0, 0xFFFFFFFF, 0, 0);
            GuardEffectParam::sub_1407AFADC_S4(a1, 1);
            return result;
        }
        __int64 v63 = sub_14077DA68(a1, 0x65u, 1);
        sub_14077E64C(a1, v63 ? 101 : 102, 0, 0xFFFFFFFF, 0, 0);
        GuardEffectParam::sub_1407AFADC_S4(a1, 1);
        return result;
    }

    {
        __int64 v56 = sub_14077DA68(a1, 0x65u, 1);
        __int64 state = v56 ? 101 : 102;
        sub_14077E64C(a1, state, 0, 0xFFFFFFFF, 0, 0);
        if (*reinterpret_cast<int*>(a1 + 0xC8C) != 114 || *reinterpret_cast<int*>(a1 + 0xCC4) != 74)
        {
            GuardEffectParam::sub_1407AFADC_S4(a1, 0);
            return result;
        }
        return result;
    }
}

GuardEffectParam::sub_140775D8C_t GuardEffectParam::orig_sub_140775D8C = nullptr;
__int64 __fastcall GuardEffectParam::hk_sub_140775D8C_S4(__int64 a1)
{
    // call original first
    __int64 result = GuardEffectParam::orig_sub_140775D8C(a1);

    // minimal base offset rule (if you use moduleBase offsets anywhere later)
    constexpr std::uintptr_t BASE_SUB = 0x140000C00ULL;

    // typedef  sub_1409DCEB0 (    ) 
    typedef __int64(__fastcall* fn_sub_1407B57EC_t)(int* ptr);
    constexpr std::uintptr_t OFF_sub_1407B57EC = 0x1407B57EC;
    //   
    fn_sub_1407B57EC_t sub_1407B57EC = reinterpret_cast<fn_sub_1407B57EC_t>(moduleBase + (OFF_sub_1407B57EC - BASE_SUB));

    // read char id and awakened flag
    uint32_t charID = *reinterpret_cast<uint32_t*>(a1 + 0xC8C);
    int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1);

    // lookup entry in your file-based table
    GuardEffectParamEntry* entry = GetGuardEffectEntry(charID, isAwakened);

    if (!entry) {
        // not present in file -> keep original behaviour only
        return result;
    }

    // mode check: 0 = base-only, 1 = awakened-only, 2 = both
    if (entry->Mode == 0 && isAwakened) {
        // base-only but object is awakened -> do nothing extra
        return result;
    }
    if (entry->Mode == 1 && !isAwakened) {
        // awaken-only but object not awakened -> do nothing extra
        return result;
    }

    // At this point: entry exists AND Mode permits current awakened state.
    // Perform the same cleanup loop as in original: iterate [a1+0x11600 .. a1+0x11608) and call sub_1409DCEB0(*i)
    void** start = *reinterpret_cast<void***>(a1 + 0x14A18);
    void** end = *reinterpret_cast<void***>(a1 + 0x14A20);

    if (start && end) {
        // Minimal safety: make sure end >= start (in pointer terms)
        if (end >= start) {
            for (void** it = start; it != end; ++it) {
                void* p = *it;
                if (p) {
                    // many disassemblies show int* but any pointer works
                    sub_1407B57EC(reinterpret_cast<int*>(p));
                }
            }
        }
    }



    // You can also load loop/end here depending on other conditions  e.g.
    // if (needLoop) GuardEffectParam::sub_1409D6220_SC(a1, 1);
    // if (needEnd)  GuardEffectParam::sub_1409D6220_SC(a1, 2);

    return result;
}
