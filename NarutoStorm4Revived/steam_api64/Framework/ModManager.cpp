
#include <iostream>
#include <Windows.h>
#include "Common.h"
#include "ModManager.h"
#include "PatternScan.h"
using namespace std;
#include <array>
//sub_1412528C0
#include <windows.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Utilities.h"
#include "imgui.h"
#include "UltimateStormAPI.h"
ModManager::orig_sub_140695424_t ModManager::orig_sub_140695424 = nullptr;
__int64 __fastcall ModManager::sub_140695424_S4(__int64 a1, __int64 a2)
{
    __int64 result = ModManager::orig_sub_140695424(a1, a2);

    if (g_IsUpdateAvailable.load()) {
        typedef void(__fastcall* funct_sub_140607B5C)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
        funct_sub_140607B5C sub_140607B5C = (funct_sub_140607B5C)(moduleBase + 0x606f5C);
        sub_140607B5C(
            a1,
            (__int64)"data/ui/flash/FLASH_PLAT/gametitle/gametitle.swf",
            (__int64)"_root.all_nut",
            (__int64)"EnableModManagerUpdateText");
    }

    return result;
}

ModManager::orig_sub_1407E8050_t ModManager::orig_sub_1407E8050 = nullptr;
__int64 __fastcall ModManager::sub_1407E8050_SC(__int64 a1, __int64 a2)
{
    __int64 result = ModManager::orig_sub_1407E8050(a1, a2);

    if (g_IsUpdateAvailable.load()) {
        typedef void(__fastcall* funct_sub_14071F110)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
        funct_sub_14071F110 sub_14071F110 = (funct_sub_14071F110)(moduleBase + 0x71E510);
        sub_14071F110(
            a1,
            (__int64)"data/ui/flash/FLASH_PLAT/gametitle/gametitle.swf",
            (__int64)"_root.all_nut",
            (__int64)"EnableModManagerUpdateText");
    }

    return result;
}