#include "GudoBallParam.h"
#include "MinHook.h"   // MinHook headers ( include path )
#include <cstring>
#include "Console.h"
#include "Common.h"
#include <unordered_set>
#include <mutex>
#include "FileParser.h"

GudoBallParam::orig_t GudoBallParam::orig_sub_14097E4C0 = nullptr;
GudoBallParam::orig_s4_t GudoBallParam::orig_sub_14097E4C0_S4 = nullptr;

void GudoBallParam::handle_new_case(__int64 a1, unsigned int val)
{
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        typedef void* (__fastcall* sub_14124AE70)(size_t a1, __int64 a2, int a3);
        sub_14124AE70 sub_14124AE70_f = (sub_14124AE70)(moduleBase + 0x124A270);

        typedef signed __int64(__fastcall* sub_1405F6930)(__int64 a1);
        sub_1405F6930 sub_1405F6930_f = (sub_1405F6930)(moduleBase + 0x5F5D30);

        typedef signed __int64(__fastcall* sub_1405F72D0)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
        sub_1405F72D0 sub_1405F72D0_f = (sub_1405F72D0)(moduleBase + 0x5F66D0);

        Console::PrintOut("It worked\n");
        void* v75;
        __int64 v74 = *(__int64*)(a1 + 0x12040);
        void** v76; // r9
        void* v77; // r8
        void* v84[2]; // [rsp+50h] [rbp-29h] BYREF
        unsigned __int64 v86; // [rsp+68h] [rbp-11h]
        void* v89; // [rsp+88h] [rbp+Fh] BYREF
        unsigned __int64 v91; // [rsp+A0h] [rbp+27h]

        v84[0] = 0i64;
        v86 = 15i64;
        v89 = 0i64;
        v91 = 15i64;
        if (!v74)
        {
            v75 = sub_14124AE70_f(
                0x40ui64,
                (__int64)"D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ccPlayer.cpp",
                6468);
            if (v75)
                v74 = sub_1405F6930_f((__int64)v75);
            else
                v74 = 0i64;
            *(__int64*)(a1 + 0x12040) = v74;
        }
        v76 = v84;
        if (v86 >= 0x10)
            v76 = (void**)v84[0];
        v77 = &v89;
        if (v91 >= 0x10)
            v77 = v89;
        sub_1405F72D0_f(v74, a1, (__int64)v77, (__int64)v76);
        return;
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        typedef void* (__fastcall* sub_14124AE70)(size_t a1, __int64 a2, int a3);
        sub_14124AE70 sub_14124AE70_f = (sub_14124AE70)(moduleBase + 0xA00BF0);

        typedef signed __int64(__fastcall* sub_1405F6930)(__int64 a1);
        sub_1405F6930 sub_1405F6930_f = (sub_1405F6930)(moduleBase + 0x55B2F0);

        typedef signed __int64(__fastcall* sub_1405F72D0)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
        sub_1405F72D0 sub_1405F72D0_f = (sub_1405F72D0)(moduleBase + 0x55BA30);

        Console::PrintOut("It worked\n");
        void* v75;
        __int64 v74 = *(__int64*)(a1 + 0x14E18);
        void** v76; // r9
        void* v77; // r8
        void* v84[2]; // [rsp+50h] [rbp-29h] BYREF
        unsigned __int64 v86; // [rsp+68h] [rbp-11h]
        void* v89; // [rsp+88h] [rbp+Fh] BYREF
        unsigned __int64 v91; // [rsp+A0h] [rbp+27h]

        v84[0] = 0i64;
        v86 = 15i64;
        v89 = 0i64;
        v91 = 15i64;
        if (!v74)
        {
            v75 = sub_14124AE70_f(
                0x40ui64,
                (__int64)"D:\\Jenkins\\workspace\\Update_SVN\\narutoNext4_trunk\\narutoNext4\\prog\\source\\ccPlayer.cpp",
                1744);
            if (v75)
                v74 = sub_1405F6930_f((__int64)v75);
            else
                v74 = 0i64;
            *(__int64*)(a1 + 0x14E18) = v74;
        }
        v76 = v84;
        if (v86 >= 0x10)
            v76 = (void**)v84[0];
        v77 = &v89;
        if (v91 >= 0x10)
            v77 = v89;
        sub_1405F72D0_f(v74, a1, (__int64)v77, (__int64)v76);
        return;
    }
    
}


//  
static std::unordered_set<uint32_t> g_CustomCharIDs;
static std::mutex g_CustomCharIDsMutex;

//  ,   32- ID (little-endian).
void GudoBallParam::ReadGudoBallParamFile(const std::string& filename) {
    std::vector<uint8_t> bytes = FileParser::ReadAllBytes(filename);
    if (bytes.empty()) {
        Console::PrintErr("Failed to read file: %s\n", filename.c_str());
        return;
    }
    if (bytes.size() % sizeof(uint32_t) != 0) {
        Console::PrintErr("Malformed file: size not multiple of 4 bytes: %zu\n", bytes.size());
        return;
    }

    size_t count = bytes.size() / sizeof(uint32_t);
    {
        std::lock_guard<std::mutex> lock(g_CustomCharIDsMutex);
        g_CustomCharIDs.clear();
        for (size_t i = 0; i < count; ++i) {
            uint32_t id = *reinterpret_cast<const uint32_t*>(&bytes[i * 4]);
            g_CustomCharIDs.insert(id);
        }
    }
    Console::PrintOut("Loaded %zu character IDs from %s\n", count, filename.c_str());
}

//  
bool GudoBallParam::IsCustomCharID(uint32_t id) {
    std::lock_guard<std::mutex> lock(g_CustomCharIDsMutex);
    return g_CustomCharIDs.find(id) != g_CustomCharIDs.end();
}

//  Hooked_sub_14097E4C0
void __fastcall GudoBallParam::Hooked_sub_14097E4C0(__int64 a1)
{
    unsigned int switchVal = *reinterpret_cast<unsigned int*>(a1 + 0xE64);

    //  ID           
    if (IsCustomCharID(switchVal) && 
        (switchVal != 0x71 &&
        switchVal != 0x72 &&
        switchVal != 0x76 &&
        switchVal != 0x81 &&
        switchVal != 0x8E &&
        switchVal != 0xA4 &&
        switchVal != 0xBB &&
        switchVal != 0xE8 &&
        switchVal != 0x113)) {
        GudoBallParam::handle_new_case(a1, switchVal);
        //Console::PrintErr("Characode 0x%X (custom)\n", switchVal);
        return;
    }

    ////      
    //if (switchVal != 0x71 &&
    //    switchVal != 0x72 &&
    //    switchVal != 0x76 &&
    //    switchVal != 0x81 &&
    //    switchVal != 0x8E &&
    //    switchVal != 0xA4 &&
    //    switchVal != 0xBB &&
    //    switchVal != 0xE8 &&
    //    switchVal != 0x113)
    //{
    //    GudoBallParam::handle_new_case(a1, switchVal);
    //    Console::PrintErr("Characode 0x%X\n", switchVal);
    //    return; //    
    //}

    //     ,   
    if (GudoBallParam::orig_sub_14097E4C0)
        GudoBallParam::orig_sub_14097E4C0(a1);
}

//  Hooked_sub_14097E4C0_S4
void __fastcall GudoBallParam::Hooked_sub_14097E4C0_S4(__int64 a1, int a2, int a3, int a4, int a5, int* a6)
{
    //       
    if (GudoBallParam::orig_sub_14097E4C0_S4)
        GudoBallParam::orig_sub_14097E4C0_S4(a1, a2, a3, a4, a5, a6);

    unsigned int switchVal = *reinterpret_cast<unsigned int*>(a1 + 0xC8C);

    //Console::PrintErr("Character Class %p\n", a1);
    //Console::PrintErr("Characode 0x%X\n", switchVal);
    
    //  ID      
    if (IsCustomCharID(switchVal) && 
        (switchVal != 0x71 &&
        switchVal != 0x72 &&
        switchVal != 0x76 &&
        switchVal != 0x81 &&
        switchVal != 0x8E &&
        switchVal != 0xA4 &&
        switchVal != 0xBB &&
        switchVal != 0xE8 &&
        switchVal != 0x113)) {
        GudoBallParam::handle_new_case(a1, switchVal);
        return;
    }

    ////      
    //if (switchVal != 0x71 &&
    //    switchVal != 0x72 &&
    //    switchVal != 0x76 &&
    //    switchVal != 0x81 &&
    //    switchVal != 0x8E &&
    //    switchVal != 0xA4 &&
    //    switchVal != 0xBB &&
    //    switchVal != 0xE8 &&
    //    switchVal != 0x113)
    //{
    //    GudoBallParam::handle_new_case(a1, switchVal);
    //}
}

