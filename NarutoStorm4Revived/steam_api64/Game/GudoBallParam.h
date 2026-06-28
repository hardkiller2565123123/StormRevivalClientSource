#pragma once
#include <windows.h>
#include <cstdint>
#include <string>

class GudoBallParam {
public:
    //    (__fastcall: RCX = a1)
    typedef void(__fastcall* orig_t)(__int64 a1);

    typedef __int64(__fastcall* orig_s4_t)(__int64 a1, int a2, int a3, int a4, int a5, int* a6);

    //    (  cpp)
    static orig_t orig_sub_14097E4C0;

    //    (  cpp)
    static orig_s4_t orig_sub_14097E4C0_S4;

    //   (  MinHook)
    static void __fastcall Hooked_sub_14097E4C0(__int64 a1);
    static void __fastcall Hooked_sub_14097E4C0_S4(__int64 a1, int a2, int a3, int a4, int a5, int* a6);
    static void ReadGudoBallParamFile(const std::string& filename);
    static bool IsCustomCharID(uint32_t id);

private:
    //     case'
    static void handle_new_case(__int64 a1, unsigned int val);
};
