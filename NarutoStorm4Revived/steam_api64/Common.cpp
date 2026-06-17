
#include <iostream>
#include <Windows.h>
#include "Common.h"
#include "PatternScan.h"
using namespace std;
#include <array>
//sub_1412528C0
#include <windows.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "PlAnmList.h"
#include "Utilities.h"
#include "imgui.h"
#define LODWORD(x) (*reinterpret_cast<uint32_t*>(&x))
#define LOBYTE(x)  (*reinterpret_cast<uint8_t*>(&x))
__int64 Common::hudon_address = 0;

//Common::Sub1413268E0_t Common::Original_sub_1413268E0 = nullptr;
void __fastcall Common::DebugString(const char* Format, ...)
{
    if (!Format) return;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) hOut = NULL;

    const WORD COLOR_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const WORD COLOR_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const WORD COLOR_RESET = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    va_list args;
    va_start(args, Format);

    const char* p = Format;
    const char* segStart = p;

    // temporary buffers
    char argBuf[1024];
    wchar_t wideBuf[2048];

    while (*p)
    {
        if (*p == '%')
        {
            // print literal segment before '%'
            if (p > segStart)
            {
                int litLen = (int)(p - segStart);
                // convert literal to wide and print in yellow
                if (hOut) SetConsoleTextAttribute(hOut, COLOR_YELLOW);
                int needed = MultiByteToWideChar(CP_UTF8, 0, segStart, litLen, wideBuf, _countof(wideBuf));
                if (needed > 0)
                {
                    wideBuf[needed] = 0;
                    fputws(wideBuf, stdout);
                }
            }

            p++; // skip '%'
            if (*p == '%') // escaped percent "%%"
            {
                if (hOut) SetConsoleTextAttribute(hOut, COLOR_YELLOW);
                fputwc(L'%', stdout);
                p++;
                segStart = p;
                continue;
            }

            // parse flags/width/precision (we'll skip complex parsing; copy minimal into fmt)
            const char* fmtStart = p - 1; // include '%'
            // advance until conversion specifier letter
            // allowed letters: diuoxXpcsfeEgG
            while (*p && !strchr("diuoxXpcsfeEgG", *p))
            {
                p++;
            }
            if (!*p)
            {
                // malformed format, print rest as literal
                if (p > segStart)
                {
                    if (hOut) SetConsoleTextAttribute(hOut, COLOR_YELLOW);
                    int needed = MultiByteToWideChar(CP_UTF8, 0, segStart, (int)(p - segStart), wideBuf, _countof(wideBuf));
                    if (needed > 0) { wideBuf[needed] = 0; fputws(wideBuf, stdout); }
                }
                break;
            }

            char spec = *p;
            // determine length modifier by scanning between '%' and spec
            bool is_long = false;
            bool is_ll = false;
            bool is_short = false;

            // look backwards from spec-1 to fmtStart+1 for 'l' or 'h'
            const char* q = p - 1;
            while (q > fmtStart)
            {
                if (*q == 'l') { if (is_long) is_ll = true; else is_long = true; }
                else if (*q == 'h') is_short = true;
                q--;
            }

            // Format the argument into argBuf based on spec and length
            argBuf[0] = 0;
            switch (spec)
            {
            case 'd':
            case 'i':
            {
                if (is_ll) { long long v = va_arg(args, long long); snprintf(argBuf, sizeof(argBuf), "%lld", v); }
                else if (is_long) { long v = va_arg(args, long); snprintf(argBuf, sizeof(argBuf), "%ld", v); }
                else if (is_short) { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%hd", (short)v); }
                else { int v = va_arg(args, int); snprintf(argBuf, sizeof(argBuf), "%d", v); }
                break;
            }
            case 'u':
            case 'o':
            case 'x':
            case 'X':
            {
                if (is_ll) { unsigned long long v = va_arg(args, unsigned long long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%llu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%llo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%llx", v); else snprintf(argBuf, sizeof(argBuf), "%llX", v); }
                else if (is_long) { unsigned long v = va_arg(args, unsigned long); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%lu", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%lo", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%lx", v); else snprintf(argBuf, sizeof(argBuf), "%lX", v); }
                else { unsigned int v = va_arg(args, unsigned int); if (spec == 'u') snprintf(argBuf, sizeof(argBuf), "%u", v); else if (spec == 'o') snprintf(argBuf, sizeof(argBuf), "%o", v); else if (spec == 'x') snprintf(argBuf, sizeof(argBuf), "%x", v); else snprintf(argBuf, sizeof(argBuf), "%X", v); }
                break;
            }
            case 'p':
            {
                void* ptr = va_arg(args, void*);
                snprintf(argBuf, sizeof(argBuf), "%p", ptr);
                break;
            }
            case 's':
            {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                snprintf(argBuf, sizeof(argBuf), "%s", s);
                break;
            }
            case 'c':
            {
                int ch = va_arg(args, int);
                snprintf(argBuf, sizeof(argBuf), "%c", ch);
                break;
            }
            case 'f':
            case 'F':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
            {
                double dv = va_arg(args, double);
                // default formatting with %f
                snprintf(argBuf, sizeof(argBuf), "%f", dv);
                break;
            }
            default:
            {
                // unknown specifier — print it raw
                char tmpSpec[4] = { '%', spec, 0, 0 };
                snprintf(argBuf, sizeof(argBuf), "%s", tmpSpec);
                break;
            }
            }

            // print argument in cyan
            if (hOut) SetConsoleTextAttribute(hOut, COLOR_CYAN);
            if (argBuf[0] != 0)
            {
                int needed = MultiByteToWideChar(CP_UTF8, 0, argBuf, -1, wideBuf, _countof(wideBuf));
                if (needed > 0) fputws(wideBuf, stdout);
            }
            // reset to yellow for following literals
            if (hOut) SetConsoleTextAttribute(hOut, COLOR_YELLOW);

            p++; // move past spec
            segStart = p;
        }
        else
        {
            p++;
        }
    }

    // print any trailing literal
    if (*segStart)
    {
        if (hOut) SetConsoleTextAttribute(hOut, COLOR_YELLOW);
        int needed = MultiByteToWideChar(CP_UTF8, 0, segStart, -1, wideBuf, _countof(wideBuf));
        if (needed > 0) fputws(wideBuf, stdout);
    }

    // finish line and reset color
    fflush(stdout);
    if (hOut) SetConsoleTextAttribute(hOut, COLOR_RESET);

    va_end(args);

    // Also send to debugger
    // Recreate full formatted ANSI string to output via OutputDebugStringA
    // (simple approach uses vsnprintf again)
    {
        char fullBuf[2048] = { 0 };
        va_list args2;
        va_start(args2, Format);
        // we cannot re-use args; produce full with vsnprintf using a fresh va_list not possible here
        // so call vsnprintf once at start would be needed to fill fullBuf; skip for safety.
        va_end(args2);
    }
}

__int64 __fastcall Common::sub_14132B8B0_SC(__int64 a1, int a2)
{
    __int64 v2; // rbx
    __int64 v5; // rcx
    unsigned int v6; // edx

    typedef void(__fastcall* sub_14127DE40_t)(__int64 a1);
    sub_14127DE40_t sub_14127DE40 = reinterpret_cast<sub_14127DE40_t>(moduleBase + 0x127D240);
    typedef void(__fastcall* sub_14127DEB0_t)(__int64 a1);
    sub_14127DEB0_t sub_14127DEB0 = reinterpret_cast<sub_14127DEB0_t>(moduleBase + 0x127D2B0);
    v2 = 0i64;
    if (*(__int64*)a1)
    {
        sub_14127DE40(a1 + 24);
        v5 = *(unsigned int*)(a1 + 16);
        v6 = v5 + ((a2 + 15) & 0xFFFFFFF0);
        if (v6 <= *(int*)(a1 + 8))
        {
            *(int*)(a1 + 16) = v6;
            v2 = *(__int64*)a1 + v5;
        }
        /*else
        {
            ccDebugMessage("============================================================\n");
            ccDebugMessage("ERROR : %s(%d)\n");
            ccDebugMessage(byte_141B6F9F8);
        }*/
        sub_14127DEB0(a1 + 24);
    }
    return v2;
}




#include <filesystem>
#include <string>
#include <algorithm>
#include <cctype>
#include <initializer_list>
#include "MovesetPlus.h"
#include "Offsets.h"

// lower-case helper (ASCII-safe)
std::string Common::to_lower_ascii(const std::string& s) {
    std::string out; out.reserve(s.size());
    for (unsigned char c : s) out.push_back(static_cast<char>(std::tolower(c)));
    return out;
}

bool Common::MatchesFileName(const std::string& pathOrName, const std::string& targetName, bool caseInsensitive) {
    std::string name = std::filesystem::path(pathOrName).filename().string();
    if (caseInsensitive) {
        return Common::to_lower_ascii(name) == Common::to_lower_ascii(targetName);
    }
    else {
        return name == targetName;
    }
}

bool Common::MatchesAnyFileName(const std::string& pathOrName, std::initializer_list<std::string> targets, bool caseInsensitive) {
    for (const auto& t : targets) {
        if (Common::MatchesFileName(pathOrName, t, caseInsensitive)) return true;
    }
    return false;
}

const char*  GameVersion = "1.00";
const char* Common::GetVersion()
{
    const char* version = "Unknown Version";
    __int64 NSCVersionAddress = PatternScan::Scan("4Cxxxx48xxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxx48xxxxxxxxxxxx48xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx");
    __int64 NS4VersionAddress = PatternScan::Scan("48xxxxxxxxxxxxC348xxxxxxxx48xxxxxxxx48xxxxxxxx5541xx41xx48xxxx48xxxxxx48xxxx48xxxxxx48xxxxE8xxxxxxxx48xxxxxx8BxxE8xxxxxxxx48xxxxxx48xxxxxxxxxxxx");
    __int64 NS4DebugVersionAddress = PatternScan::Scan("4Cxxxx48xxxxxx48xxxxxxxxxxxx48xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx");

    if (NSCVersionAddress > 1) {
        __int64 NSCVersionAddress2 = PatternScan::Scan("4Cxxxx48xxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxx48xxxxxxxxxxxx48xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx48xxxxxxxxxxxx49xxxxxx", NSCVersionAddress + 1);
        //cout << "Naruto Storm Connections" << endl;
        version = (const char*)Common::GetVersionString(NSCVersionAddress2);
    }
    else if (NS4VersionAddress > 1) {

        //cout << "Naruto Storm 4" << endl;
        version = (const char*)Common::GetVersionString(NS4VersionAddress);
    }
    else if (NS4DebugVersionAddress > 1) {

        //cout << "Naruto Storm 4 Debug" << endl;
        version = (const char*)Common::GetVersionString(NS4DebugVersionAddress);
    }
    else {
        cout << "UltimateStormAPI couldn't get version of game." << endl;
    }
    return version;
}
__int64 __fastcall Common::GetVersionString(std::uintptr_t address)
{
    typedef __int64(__fastcall* funct)();
    funct fc = (funct)(address);
    return fc();
}
int __fastcall Common::NoClipCursor(__int64 a1) //ClipCursor
{
    return 0;
}
bool Common::WallRun()
{
    return true;


}
__int64 Common::RecalculateAddress(__int64 a)
{
    uintptr_t recalc = moduleBase + a;

    if (a > 0x13A38AD) recalc += 0x400;
    else if (a > 0xEA7420) recalc += 0x400;

    return recalc;
}

Common::orig_sub_140868D60_t Common::orig_sub_140868D60 = nullptr;
__int64 __fastcall Common::sub_140868D60(__int64 a1)
{
    __int64 result = Common::orig_sub_140868D60(a1);

    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        using fn_BlockAllocator = __int64(__fastcall*)(__int64);
        auto Nucc_BlockAllocator = reinterpret_cast<fn_BlockAllocator>(moduleBase + 0x124B290); // проверьте оффсет

        if (!Nucc_BlockAllocator) return result;
        Console::PrintErr("Memory Allocated\n");

        const uint64_t vftable_ptr = static_cast<uint64_t>(moduleBase + 0x1735DC8);

        Nucc_BlockAllocator(result + 6736);
        *reinterpret_cast<uint64_t*>(result + 6736) = vftable_ptr; // &nuccStlAllocator<char>::`vftable'
        *reinterpret_cast<uint64_t*>(result + 6760) = 0;
        *reinterpret_cast<uint64_t*>(result + 6776) = 0;
        *reinterpret_cast<uint64_t*>(result + 6784) = 15;
        *reinterpret_cast<unsigned char*>(result + 6760) = 0;
        Nucc_BlockAllocator(result + 6792);

    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        using fn_sub_1401CA8F8 = __int64(__fastcall*)(__int64);
        auto sub_1401CA8F8 = reinterpret_cast<fn_sub_1401CA8F8>(moduleBase + 0x1C9CF8); // проверьте оффсет

        Console::PrintErr("Memory Allocated\n");
        sub_1401CA8F8(a1 + 5040);

    }
   
    return result;
}
// Fixed hook
Common::orig_sub_14086B520_t Common::orig_sub_14086B520 = nullptr;
//ccSceneFreeBattle
static char* g_advHeapStr = nullptr;
//ccSceneFreeBattle::Initialize();
__int64 __fastcall Common::Hooked_sub_14086B520(__int64 a1) {

    MovesetPlus::BGM_ID = 0;
    render::hudon = 2;
    render::pause = 0;
    __int64 result = Common::orig_sub_14086B520(a1);
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        __int64* xmm_ptr = reinterpret_cast<__int64*>(moduleBase + offsetSC::VTableXmmwordOffset - 0xC00);
        if (!xmm_ptr) return Common::orig_sub_14086B520 ? Common::orig_sub_14086B520(a1) : 0;
        __int64* manager = reinterpret_cast<__int64*>(xmm_ptr[1]);
        if (!manager) return Common::orig_sub_14086B520 ? Common::orig_sub_14086B520(a1) : 0;

        // вызвать SetProperty с valuePtr = a1 + 6736 (адрес, где лежит указатель)
        using fn_ccGameProperty_SetProperty = void(__fastcall*)(__int64* manager, int* propIndex, __int64 name, __int64 valuePtr);
        auto ccGameProperty_SetProperty = reinterpret_cast<fn_ccGameProperty_SetProperty>(moduleBase + 0x4DECE0);
        Console::PrintErr("advDemoID Property Created\n");
        Console::PrintErr("Pointer: %p\n", a1);
        if (ccGameProperty_SetProperty) {
            ccGameProperty_SetProperty(manager,
                reinterpret_cast<int*>(a1 + 80),
                reinterpret_cast<__int64>("advDemoId"),
                a1 + 6736);
        }
        


    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        __int64* xmm_ptr = reinterpret_cast<__int64*>(moduleBase + offsetS4::VTableXmmwordOffset - 0xC00);
        if (!xmm_ptr) return Common::orig_sub_14086B520 ? Common::orig_sub_14086B520(a1) : 0;
        __int64* manager = reinterpret_cast<__int64*>(xmm_ptr[1]);
        if (!manager) return Common::orig_sub_14086B520 ? Common::orig_sub_14086B520(a1) : 0;

        // вызвать SetProperty с valuePtr = a1 + 6736 (адрес, где лежит указатель)
        using fn_ccGameProperty_SetProperty = void(__fastcall*)(__int64* manager, int* propIndex, __int64 name, __int64 valuePtr);
        auto ccGameProperty_SetProperty = reinterpret_cast<fn_ccGameProperty_SetProperty>(moduleBase + 0x46FDD0);
        Console::PrintErr("advDemoID Property Created\n");
        Console::PrintErr("Pointer: %p\n", a1);


        if (ccGameProperty_SetProperty) {
            ccGameProperty_SetProperty(manager,
                reinterpret_cast<int*>(a1 + 80),
                reinterpret_cast<__int64>("advDemoId"),
                a1 + 5040);
        }

    }

    return result;
    // получить manager как раньше
    
}

Common::orig_sub_140AB6F80_t Common::orig_sub_140AB6F80 = nullptr;
//ns2::ccTaskCameraJudge::ChangeAlgorithm
__int64 __fastcall Common::Hooked_sub_140AB6F80(__int64 a1, __int64 a2)
{
    //Console::PrintErr("A1 = %p, A2 = %p\n", a1, a2);
    __int64 result = Common::orig_sub_140AB6F80(a1, a2);

    return result;
}

//Timer code
Common::orig_sub_14093C7D0_t Common::orig_sub_14093C7D0 = nullptr;
__int64 __fastcall Common::sub_14093C7D0(__int64 a1)
{
    

    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        int v1 = *(int*)(a1 + 120);
        if (v1 < 0)
            return 0xFFFFFFFFi64;
        int v2 = *(int*)(a1 + 128);
        if (v2 < 1)
            return 0xFFFFFFFFi64;

        unsigned long long base = (unsigned long long)v2
            * (unsigned int)*((unsigned __int8*)Common::GetQword(0x1496CF1C8) + 2386);
        /* увеличить знаменатель в 2 раза, чтобы таймер шел в 2 раза быстрее */
        unsigned long long denom = base * render::timer_speed;
        if (denom == 0ULL)
            return 0xFFFFFFFFi64;

        return (unsigned int)((denom + (unsigned long long)v1 - 1ULL) / denom);
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        int v1 = *(int*)(a1 + 120);
        if (v1 < 0)
            return 0xFFFFFFFFi64;
        int v2 = *(int*)(a1 + 128);
        if (v2 < 1)
            return 0xFFFFFFFFi64;

        unsigned long long base = (unsigned long long)v2
            * (unsigned int)*((unsigned __int8*)Common::GetQword(0x1416663C8) + 2370);
        /* увеличить знаменатель в 2 раза, чтобы таймер шел в 2 раза быстрее */
        unsigned long long denom = base * render::timer_speed;
        if (denom == 0ULL)
            return 0xFFFFFFFFi64;

        return (unsigned int)((denom + (unsigned long long)v1 - 1ULL) / denom);
    }
}

//ccSceneFreeBattle::Finalize();
Common::orig_sub_14086ACA0_t Common::orig_sub_14086ACA0 = nullptr;
__int64 __fastcall Common::Hooked_sub_14086ACA0(__int64 a1) {
    __int64 result = Common::orig_sub_14086ACA0(a1);


    

    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        __int64* xmm_ptr = reinterpret_cast<__int64*>(moduleBase + offsetSC::VTableXmmwordOffset - 0xC00);
        if (!xmm_ptr) return result ? result : 0;
        __int64* manager = reinterpret_cast<__int64*>(xmm_ptr[1]);
        if (!manager) return result ? result : 0;

        // 3) вызвать SetProperty (как оригинал)
        using fn_ccGameProperty_EraseProperty = void(__fastcall*)(__int64* manager, int* propIndex, __int64 name);

        Console::PrintErr("advDemoID Property Erased\n");
        auto ccGameProperty_EraseProperty = reinterpret_cast<fn_ccGameProperty_EraseProperty>(moduleBase + 0x1086140);
        ccGameProperty_EraseProperty(manager,
            reinterpret_cast<int*>(a1 + 80),
            reinterpret_cast<__int64>("advDemoId"));
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        __int64* xmm_ptr = reinterpret_cast<__int64*>(moduleBase + offsetS4::VTableXmmwordOffset - 0xC00);
        if (!xmm_ptr) return result ? result : 0;
        __int64* manager = reinterpret_cast<__int64*>(xmm_ptr[1]);
        if (!manager) return result ? result : 0;

        // 3) вызвать SetProperty (как оригинал)
        using fn_ccGameProperty_EraseProperty = void(__fastcall*)(__int64* manager, int* propIndex, __int64 name);

        Console::PrintErr("advDemoID Property Erased\n");
        auto ccGameProperty_EraseProperty = reinterpret_cast<fn_ccGameProperty_EraseProperty>(moduleBase + 0xAB6B40);
        ccGameProperty_EraseProperty(manager,
            reinterpret_cast<int*>(a1 + 80),
            reinterpret_cast<__int64>("advDemoId"));
    }


    return result;
}

//Character Controls
Common::orig_CtrlInputPad_t Common::orig_CtrlInputPad = nullptr;
__int64 __fastcall Common::CtrlInputPad(__int64 a1) {
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


        using fn_IsRequestedCommand = __int64(__fastcall*)(__int64 a1, int a2);
        auto IsRequestedCommand = reinterpret_cast<fn_IsRequestedCommand>(moduleBase + 0x9EECE0);
        using fn_isUnpressATK = bool(__fastcall*)(__int64 a1);
        auto isUnpressATK = reinterpret_cast<fn_isUnpressATK>(moduleBase + 0x9EE610);
        using fn_IsAttack = bool(__fastcall*)(__int64 a1);
        auto IsAttack_f = reinterpret_cast<fn_IsAttack>(moduleBase + 0x9EE5D0);
        using fn_IsGuardOn = bool(__fastcall*)(__int64 a1);
        auto IsGuardOn = reinterpret_cast<fn_IsGuardOn>(moduleBase + 0x9EE970);
        using fn_isAttackFar = bool(__fastcall*)(__int64 a1, int a2);
        auto isAttackFar = reinterpret_cast<fn_isAttackFar>(moduleBase + 0x9EEB60);
        using fn_IsFireArm = bool(__fastcall*)(__int64 a1);
        auto IsFireArm = reinterpret_cast<fn_IsFireArm>(moduleBase + 0x9EE8B0);
        using fn_IsRequestActSkillOkForNeutral = bool(__fastcall*)(__int64 a1);
        auto IsRequestActSkillOkForNeutral = reinterpret_cast<fn_IsRequestActSkillOkForNeutral>(moduleBase + 0x9D28E0);
        using fn_RequestSoundId_2D = void(__fastcall*)(__int64* a1, int a2);
        auto RequestSoundId_2D = reinterpret_cast<fn_RequestSoundId_2D>(moduleBase + 0x9B56B0);
        using fn_GetAnmChunk = __int64(__fastcall*)(__int64 a1, unsigned int a2, __int64 a3);
        auto GetAnmChunk = reinterpret_cast<fn_GetAnmChunk>(moduleBase + 0x98E910);
        bool v2; // requested command (pad)
        bool IsAttack; // attack button
        bool v4; // alias IsAttack
        int v5; // flag at a1+0x12000 & 0x10
        void(__fastcall * v6)(__int64, __int64, __int64, __int64); // action setter (vtable + 0xE10)
        void(__fastcall * v7)(__int64, __int64, __int64, __int64); // action setter (vtable + 0xE10)


        __int64 v1 = a1 + 536;
      
        int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
        const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

        bool isPucci = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6pci01") == 0);
        if (isPucci) {
            int characterSide = *((int*)(a1 + 0xE60));
            int charState = ccPlayer::GetCharacterState((ccPlayerMain*)a1);
            if (IsFireArm((__int64)v1) && *(int*)(a1 + 0xC978) == 2 && charState == 2) {
                __int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
                float player_chakra = *(float*)(gauge_pointer + 0x08);
                if (player_chakra > 67.0f) {
                    *(int*)(a1 + 0xC978) = 0;
                    MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -66.0f);
                    MovesetPlus::me_play_action(a1, 0, 63, "BOSS_ACT_01");

                    return 1;

                }
                else {
                    RequestSoundId_2D((__int64*)a1, 4141);
                    int action_6pci_id = 70;
                    if (*(int*)(a1 + 0x10DBC) == 0)
                        action_6pci_id = 71;
                    return (*(__int64(__fastcall**)(__int64, __int64, __int64, __int64))(*(__int64*)a1 + 3600i64))(
                        a1,
                        action_6pci_id,
                        0i64,
                        1i64);
                }
            }

        }


        int Jutsu1Index = *(int*)(a1 + 0xE78);
        int Jutsu2Index = *(int*)(a1 + 0xE7C);

        int isAwakened = (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1);


        if (*(int*)(a1 + 0xEA4) != 0x5E && *(int*)(a1 + 0xE64) != 0x7C && *(int*)(a1 + 0xE64) != 0x74)
        {
            v2 = IsRequestedCommand(a1 + 536, 9) != 0;
            isUnpressATK(a1 + 536);
            IsAttack = IsAttack_f(a1 + 536);
            v4 = IsAttack;
            v5 = *(int*)(a1 + 0x12000) & 0x10;
            if (*(int*)(a1 + 0x12A34 + 0x04) == 1) {
                //Tilt code
                if ((unsigned int)isAttackFar(v1, 0)) {
                    if (IsAttack)
                    {

                        if ((*(unsigned int(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 0xEF0i64))(a1, 1i64))
                        {
                            ccPlayer::SetActionImmediate((ccPlayer*)a1, 66);
                        }
                        
                    }
                    if (IsFireArm((__int64)v1) && ccPlayer::GetActionID((ccPlayerMain*)a1) != 66)
                    {
                        if ((*(unsigned int(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 0xEF0i64))(a1, 1i64))
                        {
                            MovesetPlus::me_play_action(a1, 0, 66, "ATK_FAR00_ANOTHER");
                        }

                    }
                }

            }
            //Blockstun cancel for tilts
            if (ccPlayer::GetActionID((ccPlayerMain*)a1) == 74 || ccPlayer::GetActionID((ccPlayerMain*)a1) == 75) {
                if ((unsigned int)isAttackFar(v1, 0) || IsAttack)
                {
                    ccPlayer::SetActionImmediate((ccPlayer*)a1, 66);

                }
            }
            
            
        }

        //Chakra Syuriken code
        if (*(int*)(a1 + 0x12A34 + 0x1C) == 1) {
            __int64 AnmChunk = 0;
            int isAirJutsuExist = 0;
            if (IsRequestActSkillOkForNeutral(a1))
            {
                int air_skl_chunk = 466;
                switch (Jutsu2Index)
                {
                case 1:
                    air_skl_chunk = 508;
                    break;
                case 2:
                    air_skl_chunk = 550;
                    break;
                case 3:
                    air_skl_chunk = 592;
                    break;
                case 4:
                    air_skl_chunk = 634;
                    break;
                case 5:
                    air_skl_chunk = 676;
                    break;
                default:
                    break;
                }
                AnmChunk = GetAnmChunk(a1, air_skl_chunk, 1i64);
                isAirJutsuExist = 0;
                if (AnmChunk)
                    isAirJutsuExist = 1;

            }
            if (Jutsu1Index != Jutsu2Index || (Jutsu1Index == Jutsu2Index && isAwakened)) {

                if (IsFireArm((__int64)v1) && (*(unsigned int(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 0xF28i64))(a1, 1i64) && isAirJutsuExist == 0)
                {
                    if (*(int*)(a1 + 0x10DBC) == 0) {
                        return (*(__int64(__fastcall**)(__int64, __int64, __int64, __int64))(*(__int64*)a1 + 3600i64))(
                            a1,
                            71,
                            0i64,
                            1i64);
                    }


                }
            }


            if (Jutsu1Index == Jutsu2Index && !isAwakened) {

                if (IsFireArm((__int64)v1) && *(int*)(a1 + 0xC978))
                {
                    int action_id = 70;
                    if (*(int*)(a1 + 0x10DBC) == 0)
                        action_id = 71;

                    return (*(__int64(__fastcall**)(__int64, __int64, __int64, __int64))(*(__int64*)a1 + 3600i64))(
                        a1,
                        action_id,
                        0i64,
                        1i64);
                }
            }
        }
        __int64 result = Common::orig_CtrlInputPad(a1);
        /*if (IsFireArm(a1 + 536)) {
            Console::PrintErr("isFireArm worked\n");
        }*/
        

        return result;
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


        using fn_RequestSoundId_2D = void(__fastcall*)(__int64* a1, int a2);
        auto RequestSoundId_2D = reinterpret_cast<fn_RequestSoundId_2D>(moduleBase + 0x797A68);

        using fn_IsFireArm = bool(__fastcall*)(__int64 a1);
        //auto IsFireArm = reinterpret_cast<fn_IsFireArm>(moduleBase + 0x7BFF10);
        auto IsFireArm = reinterpret_cast<fn_IsFireArm>(moduleBase + 0x7BFEF8);



        using fn_IsAttackFar = __int64(__fastcall*)(__int64 a1, int a2);
        auto IsAttackFar = reinterpret_cast<fn_IsAttackFar>(moduleBase + 0x7C00E8);

        int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
        const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

        __int64 v1 = a1 + 536;
        bool isPucci = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6pci01") == 0);
        if (isPucci) {
            int characterSide = *((int*)(a1 + 0xC88));
            int charState = ccPlayer::GetCharacterState((ccPlayerMain*)a1);
            //If chakra load = 2, character state = 2 and pressed syuriken - plays 2nd ultimate
            if (IsFireArm((__int64)v1) && *(int*)(a1 + 0xFE74) == 2 && charState == 2) {
                __int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
                float player_chakra = *(float*)(gauge_pointer + 0x08);

                if (player_chakra > 67.0f) {
                    *(int*)(a1 + 0xFE74) = 0;
                    MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -66.0f);
                    MovesetPlus::me_play_action(a1, 0, 63, "BOSS_ACT_01");
                    return 1;

                }
                else {
                    RequestSoundId_2D((__int64*)a1, 4141);
                    int action_6pci_id2 = 70;
                    if (*(int*)(a1 + 0x141EC) == 0)
                        action_6pci_id2 = 71;
                    return (*(__int64(__fastcall**)(__int64, __int64, __int64, __int64))(*(__int64*)a1 + 3552i64))(
                        a1,
                        action_6pci_id2,
                        0i64,
                        1i64);
                }
            }

        }


        //Syuriken Tilt
        if ((*(unsigned int(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 0x1398i64))(a1, 1i64)
            && ((unsigned int)IsAttackFar(v1, 0) && IsFireArm(v1))
            && (*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0xEC8i64))(a1))
        {
            if (*(int*)(a1 + 0x141EC) != 0 && ccPlayer::GetActionID((ccPlayerMain*)a1) != 66 ) {
                MovesetPlus::me_play_action(a1, 0, 66, "ATK_FAR00_ANOTHER");
                return 1;
            }
        }


         //Syuriken Tilt
        //if ((unsigned int)IsAttackFar(v1, 0))
        //{

        //    if (IsFireArm((__int64)v1) && (*(unsigned int(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 0xE90i64))(a1, 1i64))
        //    {
        //        if (*(int*)(a1 + 0x141EC) != 0) {

        //            MovesetPlus::me_play_action(a1, 0, 66, "ATK_FAR00_ANOTHER");
        //            return 1;
        //        }
        //    }


        //}

        __int64 result = Common::orig_CtrlInputPad(a1);
        return result;
    }
    
}



char* CutAtLastUnderscore(const char* str)
{
    if (!str) return nullptr;

    static char buffer[16]; // adjust size if needed
    strncpy(buffer, str, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char* last = strrchr(buffer, '_');
    if (last)
        *last = '\0';

    return buffer;
}
void ReplaceIAString_NSC(__int64 a1, const char* newStr)
{
    size_t len = strlen(newStr);
    void* dest;

    if (*(uint64_t*)(a1 + 48) >= 0x10) // heap
        dest = *(void**)(a1 + 24);
    else // inline
        dest = (void*)(a1 + 24);

    memcpy(dest, newStr, len + 1);
    *(uint64_t*)(a1 + 40) = len; // update length
}
void ReplaceIAString_NS4(uintptr_t a1, const char* newStr)
{
    if (!newStr || a1 == 0) return;

    size_t newLen = std::strlen(newStr);

    // В S4: длина хранится по offset +16, "флаг/cap" — по +24,
    // а сам буфер находится inline по адресу a1 или в куче по *(char**)a1
    const uintptr_t OFF_LEN = 16;
    const uintptr_t OFF_FLAG = 24;
    const size_t INLINE_CAP = 15; // inline buffer capacity (0..15)

    uint64_t flag = *reinterpret_cast<uint64_t*>(a1 + OFF_FLAG);

    if (flag >= 0x10) // heap mode: pointer to buffer stored at a1
    {
        char* dest = *reinterpret_cast<char**>(a1);
        if (!dest) // защитный fallback на inline буфер
            dest = reinterpret_cast<char*>(a1);

        // Внимание: предполагается, что heap-буфер достаточно велик.
        // Если он меньше newLen, возможен overflow — в этом случае
        // нужно использовать аллокатор игры или выделять память корректно.
        std::memcpy(dest, newStr, newLen + 1);
        *reinterpret_cast<uint64_t*>(a1 + OFF_LEN) = static_cast<uint64_t>(newLen);
    }
    else // inline buffer at a1 (size = INLINE_CAP)
    {
        size_t copyLen = newLen;
        if (copyLen > INLINE_CAP) copyLen = INLINE_CAP; // усечение, чтобы не переписать структуру
        std::memcpy(reinterpret_cast<void*>(a1), newStr, copyLen);
        reinterpret_cast<char*>(a1)[copyLen] = '\0';
        *reinterpret_cast<uint64_t*>(a1 + OFF_LEN) = static_cast<uint64_t>(copyLen);
        *reinterpret_cast<uint64_t*>(a1 + OFF_FLAG) = INLINE_CAP; // сохранить отметку inline
    }
}
bool HasTwoOrMoreUnderscores(const char* str)
{
    if (!str) return false;

    int count = 0;
    for (const char* p = str; *p; ++p)
    {
        if (*p == '_')
        {
            count++;
            if (count > 1)
                return true;
        }
    }
    return false;
}
Common::orig_Hooked_IASceneName_CutSymbol_t Common::orig_Hooked_IASceneName_CutSymbol = nullptr;
__int64 __fastcall Common::Hooked_IASceneName_CutSymbol(__int64 a1, char* a2)
{
    __int64 result = Common::orig_Hooked_IASceneName_CutSymbol(a1, a2);
    bool found = HasTwoOrMoreUnderscores(a2);
    if (found) {
        char* newStr = CutAtLastUnderscore(a2);
        if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


            ReplaceIAString_NSC(result, newStr);
        }
        else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

            ReplaceIAString_NS4(result, newStr);
        }

    }
    return result;
}

//Kaguya's Condition to enable D-Pad animation by default
Common::orig_sub_140643E70_t Common::orig_sub_140643E70 = nullptr;
__int64 __fastcall Common::sub_140643E70(__int64 a1)
{
    __int64 result = Common::orig_sub_140643E70(a1);
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {



        *(int*)(a1 + 0xF30) = 1;
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {



        *(int*)(a1 + 0xD38) = 1;
    }
    return a1;
}



Common::orig_sub_14063F338_t Common::orig_sub_14063F338 = nullptr;
__int64 __fastcall Common::sub_14063F338(__int64 a1, int a2, int a3, int a4, int a5)
{

    int enable_duel_break = a3;

    if (render::hudon == 2) {
        enable_duel_break = a3;
    }
    else {
        enable_duel_break = 2;
    }



    return orig_sub_14063F338(a1, a2, enable_duel_break, a4, a5);


}

//Common::orig_addSkillInfoFunc_t Common::orig_addSkillInfoFunc = nullptr;
//__int64 __fastcall Common::addSkillInfoFunc(__int64 a1, int a2, unsigned int a3, __int64* a4, int a5)
//{
//    Console::PrintErr("Test 6 %d %p\n", a3, a4);
//    return Common::orig_addSkillInfoFunc(a1, a2, a3, a4,a5);
//
//}
//
//Common::orig_addSpAtkInfoFunc_t Common::orig_addSpAtkInfoFunc = nullptr;
//__int64 __fastcall Common::addSpAtkInfoFunc(__int64 a1, int a2, int a3, __int64* a4)
//{
//    render::jutsu_ptr = a4;
//
//    Console::PrintErr("Test 5 %d %p\n", a3, render::jutsu_ptr);
//    return Common::orig_addSpAtkInfoFunc(a1, a2, a3, a4);
//}

using VtblFn_t = void(__fastcall*)(std::int64_t* thisptr, std::int64_t** elemPtr, std::int64_t* extraPtr);

using fn_sub_1400FEC40 = void(__fastcall*)(__int64* a1);
auto sub_1400FEC40 = reinterpret_cast<fn_sub_1400FEC40>(moduleBase + 0xFE040);
using fn_sub_1400FECE0 = void(__fastcall*)(__int64** a1);
auto sub_1400FECE0 = reinterpret_cast<fn_sub_1400FEC40>(moduleBase + 0xFE0E0);

// ----- helpers -----
static bool MemProtReadable(DWORD protect) {
    protect &= ~PAGE_GUARD;
    return protect == PAGE_READONLY || protect == PAGE_READWRITE ||
        protect == PAGE_WRITECOPY || protect == PAGE_EXECUTE_READ ||
        protect == PAGE_EXECUTE_READWRITE || protect == PAGE_EXECUTE_WRITECOPY;
}

// Проверяет, что [addr, addr+size) доступна для чтения (может проходить через несколько регионов)
static bool IsReadable(const void* addr, size_t size) {
    if (!addr || size == 0) return false;
    const uint8_t* cur = reinterpret_cast<const uint8_t*>(addr);
    const uint8_t* end = cur + size;
    while (cur < end) {
        MEMORY_BASIC_INFORMATION mbi{};
        if (!VirtualQuery(cur, &mbi, sizeof(mbi))) return false;
        if (mbi.State != MEM_COMMIT) return false;
        if (!MemProtReadable(mbi.Protect)) return false;
        uintptr_t regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        uintptr_t needEnd = reinterpret_cast<uintptr_t>(end);
        if (regionEnd >= needEnd) return true;
        // advance to next region
        cur = reinterpret_cast<const uint8_t*>(regionEnd);
    }
    return true;
}

static bool IsExecutableAddress(void* addr) {
    if (!addr) return false;
    MEMORY_BASIC_INFORMATION mbi{};
    if (!VirtualQuery(addr, &mbi, sizeof(mbi))) return false;
    DWORD prot = mbi.Protect & ~PAGE_GUARD;
    return prot == PAGE_EXECUTE || prot == PAGE_EXECUTE_READ ||
        prot == PAGE_EXECUTE_READWRITE || prot == PAGE_EXECUTE_WRITECOPY;
}

static bool SafeRead64(const void* addr, uint64_t& out) {
    if (!IsReadable(addr, sizeof(uint64_t))) return false;
    out = *reinterpret_cast<const uint64_t*>(addr);
    return true;
}
static bool SafeRead32(const void* addr, uint32_t& out) {
    if (!IsReadable(addr, sizeof(uint32_t))) return false;
    out = *reinterpret_cast<const uint32_t*>(addr);
    return true;
}

static bool LooksLikeString(const char* s, size_t maxLen = 256) {
    if (!s) return false;
    if (!IsReadable(s, 1)) return false;
    size_t i = 0;
    for (; i < maxLen; ++i) {
        if (!IsReadable(s + i, 1)) return false;
        char c = s[i];
        if (c == '\0') return true;
        unsigned char uc = static_cast<unsigned char>(c);
        // allow printable ASCII and common extended chars, reject control bytes
        if (uc < 0x09) return false;
        if (uc > 0x0D && uc < 0x20) return false;
    }
    return false;
}

// Destructor signature from disasm
using DestructorFn = void(__fastcall*)(int64_t obj, char* meta, int64_t variable);

// Структура слота — ровно 48 байт как в дизасме
#pragma pack(push,1)
struct Slot {
    char meta[16];     // передаётся вторым аргументом в деструктор
    uint64_t obj;      // указатель на объект (или 0)
    int64_t  var_type; // тип (3=int,6=string,2=bool и т.д.)
    uint64_t variable; // значение или указатель на строку
    uint64_t  pad2;
};
#pragma pack(pop)
static_assert(sizeof(Slot) == 48, "Slot must be 48 bytes");


__int64 __fastcall NSC_MemoryAllocationStorm4(__int64 a1)
{
    int v2; // eax
    __int64 v4[5]; // [rsp+20h] [rbp-28h] BYREF

    using fn_BlockAllocator = __int64(__fastcall*)(__int64);
    auto Nucc_BlockAllocator = reinterpret_cast<fn_BlockAllocator>(moduleBase + 0x124B290); // проверьте оффсет


    using fn_sub_14124BFE0 = __int64(__fastcall*)(__int64);
    auto sub_14124BFE0 = reinterpret_cast<fn_sub_14124BFE0>(moduleBase + 0x124B3E0); // проверьте оффсет
    using fn_sub_14124BE40 = __int64(__fastcall*)(__int64 a1, unsigned int a2);
    auto sub_14124BE40 = reinterpret_cast<fn_sub_14124BE40>(moduleBase + 0x124B240); // проверьте оффсет

    const uint64_t vftable_ptr = static_cast<uint64_t>(moduleBase + 0x1735DC8);
    Nucc_BlockAllocator((__int64)v4);
    *(__int64*)(a1 + 16) = 0i64;
    *(__int64*)(a1 + 24) = 0i64;
    v4[0] = (__int64)vftable_ptr;
    v2 = sub_14124BFE0((__int64)v4);
    sub_14124BE40(a1 + 32, v2);
    *(__int64*)(a1 + 32) = vftable_ptr;
    *(__int64*)(a1 + 16) = 0i64;
    *(__int64*)(a1 + 24) = 15i64;
    *(char*)a1 = 0;
    return a1;
}
#pragma pack(push,1)
struct Element
{
    std::int64_t q0;      // 0
    std::int64_t q1;      // 8
    std::int64_t obj;     // 16
    std::int64_t flags_q; // 24 (low 32 bits = var_type/flags)
    std::int64_t extra;   // 32 (variable value / pointer / bool in LOBYTE)
    char padding[8];      // 40..47
};
static_assert(sizeof(Element) == 48, "Element must be 48 bytes");
inline int& flags_ref(Element& e) { return *reinterpret_cast<int*>(&e.flags_q); }
//Safe vtable call helper if needed(kept from your earlier code)
using VtblFn_t = void(__fastcall*)(std::int64_t* /*thisptr*/, std::int64_t** /*elemPtr*/, std::int64_t* /*extraPtr*/);
static void call_vtable_offset_16_safe(Element & e)
{
    if (e.obj == 0) return;
    void** vptr = nullptr;
    std::memcpy(&vptr, reinterpret_cast<void**>(&e.obj), sizeof(void*));
    if (!vptr) return;
    if (vptr[0] == nullptr && vptr[1] == nullptr) return;
    VtblFn_t fn = reinterpret_cast<VtblFn_t>(vptr[2]);
    if (!fn) return;
    fn(reinterpret_cast<std::int64_t*>(e.obj), reinterpret_cast<std::int64_t**>(&e), &e.extra);
}

using DestructorFn = void(__fastcall*)(int64_t /*obj*/, char* /*slotMeta*/, int64_t /*variable*/);
Common::orig_sub_140749840_t Common::orig_sub_140749840 = nullptr;
__int64 __fastcall Common::hook_sub_140749840(__int64 a1, unsigned int a2, int a3, int a4)
{
    __int64 result = Common::orig_sub_140749840(a1, a2, a3, a4);
    __int64 v23[3]; // [rsp+80h] [rbp-80h] BYREF
    unsigned __int64 v25; // [rsp+B0h] [rbp-50h]
    // imports from module (adjust moduleBase if needed)
    using fn_sub_14071EF30_t = void(__fastcall*)(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        __int64 a4,
        __int64 a5,
        __int64 a6,
        __int64 a7,
        unsigned int a8);
    auto sub_14071EF30 = reinterpret_cast<fn_sub_14071EF30_t>(moduleBase + 0x71E330);

    using fn_sub_14071EE00_t = void(__fastcall*)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5);
    auto sub_14071EE00 = reinterpret_cast<fn_sub_14071EE00_t>(moduleBase + 0x71E200);
    using fn_sub_14051E8F0 = unsigned __int8** (__fastcall*)(__int64, __int64);
    auto sub_14051E8F0 = reinterpret_cast<fn_sub_14051E8F0>(moduleBase + 0x51DCF0);

    using fn_sub_1408575E0 = __int64* (__fastcall*)(__int64, __int64);
    auto sub_1408575E0 = reinterpret_cast<fn_sub_1408575E0>(moduleBase + 0x8569E0);

    using fn_Nucc_Memory_BlockAllocator = __int64(__fastcall*)(__int64);
    auto Nucc_Memory_BlockAllocator = reinterpret_cast<fn_Nucc_Memory_BlockAllocator>(moduleBase + 0x124B290);

    using fn_vect_const = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* ctor)(void*));
    auto vect_const = reinterpret_cast<fn_vect_const>(moduleBase + 0x1419780);

    using fn_vect_destruct = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* dtor)(void*));
    auto vect_destruct = reinterpret_cast<fn_vect_destruct>(moduleBase + 0x1418DCC);

    auto ctor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0xFE040);
    auto dtor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0xFE0E0);

    using fn_sub_1400B0F40_t = int*(__fastcall*)(__int64* a1, char* a2, int* a3);
    auto sub_1400B0F40 = reinterpret_cast<fn_sub_1400B0F40_t>(moduleBase + 0xB0340);

    using fn_sub_14071F020 = void(__fastcall*)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5);
    auto sub_14071F020 = reinterpret_cast<fn_sub_14071F020>(moduleBase + 0x71E420);

    using fn_sub_141073930 = __int64(__fastcall*)(char*);
    auto sub_141073930 = reinterpret_cast<fn_sub_141073930>(moduleBase + 0x1072D30);
    // original locals (trimmed)
    __m128i v157 = _mm_load_si128(reinterpret_cast<const __m128i*>(Common::GetQwordPtr(0x14174F4D0)));
    __int64* v152 = reinterpret_cast<__int64*>(a1 + 1024 + 8i64 * static_cast<int>(a2));
    __int64 v7 = *v152;
    uint64_t* off_table = reinterpret_cast<uint64_t*>(Common::GetOffset(0x141FD4C60));
    uint64_t off_entry = 0;
    if (off_table && *(int*)(v7 + 0x3EC) >= 0) off_entry = off_table[*(int*)(v7 + 0x3EC)];

    unsigned __int8** v16 = sub_14051E8F0(Common::GetQword(0x14219D888), *(__int64*)(*(__int64*)(v7 + 32) - 8i64));
    __int64 v137 = a1;
    __int64 v17 = *reinterpret_cast<__int64*>(Common::GetQwordPtr(0x14219D7E0));
    __int64 v4 = *reinterpret_cast<uint64_t*>(Common::GetQword(0x14219D7E0) + 0x178);
    int v135 = 0;
    std::vector<uint8_t> buf(0x30 * 4);
    void* Block2[3];

    __int64 v6 = a1;
    __int64 v10 = (__int64)(*(__int64*)(v7 + 32) - *(__int64*)(v7 + 24)) >> 3;
    *(int*)(v6 + 0x7C) = 1;
    unsigned __int64 v18 = static_cast<unsigned __int64>(v10 - 1);
    if (!*(int*)(v7 + 0x420))
    {
        int v57 = 0;
        if (v16) {
            __int64 v58 = reinterpret_cast<__int64>(sub_1408575E0(*(__int64*)(v17 + 304), (__int64)*v16));
            if (v58) v57 = *reinterpret_cast<int*>(v58 + 28);
        }

        unsigned int v59 = 0;
        int Jutsu1_Index = 0;
        int Jutsu2_Index = 0;
        __int64 v61 = 0x70 * v18;
        __int64 v62 = v137;
        bool isSelected1 = false;
        bool isSelected2 = false;
        do {
            void* Block = _aligned_malloc(0x40, 16);
            if (!Block) break;
            memset(Block, 0, 0x40);

            using fn_BlockAllocator = __int64(__fastcall*)(__int64);
            auto Nucc_BlockAllocator = reinterpret_cast<fn_BlockAllocator>(moduleBase + 0x124B290); // проверьте оффсет
            Nucc_BlockAllocator((__int64)Block);


            // подготовим аргументы и валидируем
            uint64_t targetPtr = 0;
            SafeRead64(reinterpret_cast<void*>(Common::GetQword(0x14219D7E0) + 0x178), targetPtr);
            int arg2 = 0;
            SafeRead32(reinterpret_cast<void*>(v61 + v7 + 0x30), reinterpret_cast<uint32_t&>(arg2));
            unsigned int arg3 = v59;

            // проверяем корректность Block перед вызовом
            bool blockOK = IsReadable(Block, 0x20); // минимум доступ на чтение первых 0x20 байт
            // если в коде ожидается Block[0] табличка, проверим и её при необходимости
            uint64_t block0 = 0;
            if (blockOK && IsReadable(Block, sizeof(void*))) {
                SafeRead64(Block, block0);
            }

            // проверяем, что целевой объект (targetPtr) читаем
            bool targetOK = IsReadable(reinterpret_cast<void*>(targetPtr), 8);

            // ПРОВЕРКИ ПЕРЕД ВЫЗОВОМ
            if (blockOK && targetOK) {
                using fn_addSkillInfoFunc = __int64(__fastcall*)(__int64 a1, int a2, unsigned int a3, __int64* a4, int a5);
                auto addSkillInfoFunc = reinterpret_cast<fn_addSkillInfoFunc>(moduleBase + 0x6F3970);
                using fn_addSpAtkInfoFunc = __int64(__fastcall*)(__int64 a1, int a2, unsigned int a3, __int64* a4);
                auto addSpAtkInfoFunc = reinterpret_cast<fn_addSpAtkInfoFunc>(moduleBase + 0x6F47C0);
                // проверим, что функция находится в исполняемой секции
                if (IsExecutableAddress(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(addSkillInfoFunc)))) {
                    // вызов без SEH — если всё ещё падает, нужно дебагером смотреть где и почему
                    __int64 res = addSkillInfoFunc((__int64)targetPtr, arg2, arg3, (__int64*)Block, 0);
                    //Console::PrintErr("DBG addSkillInfoFunc returned %llu\n", (unsigned long long)res);

                    if (res) {
                        isSelected1 = Jutsu1_Index == *(int*)(v61 + v7 + 0x48);
                        isSelected2 = Jutsu2_Index == *(int*)(v61 + v7 + 0x4C);
                        // читать 8 байт с оффсета 0x18 только если доступно
                        uint64_t rawValue = 0;
                        if (IsReadable(reinterpret_cast<char*>(Block) + 0x18, sizeof(uint64_t))) {
                            SafeRead64(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(Block) + 0x18), rawValue);
                            char* possibleStr = reinterpret_cast<char*>(rawValue);
                            if (LooksLikeString(possibleStr, 64)) {
                                // безопасно вызываем GetTextFromCRC32Code только если чувствительны к типу
                                uint64_t jutsu_name_address = 0;
                                // проверяем, что функция GetTextFromCRC32Code безопасна (предполагаем)
                                jutsu_name_address = static_cast<uint64_t>(Common::GetTextFromCRC32Code(possibleStr));

                                alignas(8) char buffer[48 * 4];

                                vect_const(buffer, /*elemSize=*/48, /*count=*/4, ctor_fn);
                                Element* arr = reinterpret_cast<Element*>(buffer);
                                for (int i = 0; i < 4; ++i) {
                                    if ((flags_ref(arr[i]) & 0x40) != 0) {
                                        call_vtable_offset_16_safe(arr[i]);
                                        arr[i].q0 = -1;
                                        arr[i].q1 = -1;
                                        arr[i].q1 = -1;
                                    }
                                }

                                flags_ref(arr[0]) = 3;
                                arr[0].extra = (__int64)Jutsu1_Index;

                                flags_ref(arr[1]) = 6;
                                arr[1].extra = jutsu_name_address;

                                flags_ref(arr[2]) = 2;
                                arr[2].extra = (__int64)isSelected1;
                                flags_ref(arr[3]) = 2;
                                arr[3].extra = 1i64;


                                int idx = *reinterpret_cast<int*>(v7 + 0x3EC);
                                int64_t secondArg = 48LL * idx + v62 + 0x2E0;
                                sub_14071EF30(v62, secondArg, reinterpret_cast<__int64>("charsel"), off_entry,
                                    reinterpret_cast<__int64>("AddSkill1Info"), 0, (__int64)buffer, 4u);
                                vect_destruct(buffer, 48i64, 4i64, dtor_fn);

                                vect_const(buffer, /*elemSize=*/48, /*count=*/4, ctor_fn);
                                Element* arr2 = reinterpret_cast<Element*>(buffer);
                                for (int i = 0; i < 4; ++i) {
                                    if ((flags_ref(arr[i]) & 0x40) != 0) {
                                        call_vtable_offset_16_safe(arr2[i]);
                                        arr2[i].q0 = -1;
                                        arr2[i].q1 = -1;
                                        arr2[i].q1 = -1;
                                    }
                                }

                                // Set first element: type = 3, variable = a2 (32-bit)
                                flags_ref(arr2[0]) = 3;
                                arr2[0].extra = (__int64)Jutsu2_Index;

                                flags_ref(arr2[1]) = 6;
                                arr2[1].extra = jutsu_name_address;

                                flags_ref(arr2[2]) = 2;
                                arr2[2].extra = (__int64)isSelected2;
                                flags_ref(arr2[3]) = 2;
                                arr2[3].extra = 1i64;


                                idx = *reinterpret_cast<int*>(v7 + 0x3EC);
                                secondArg = 48LL * idx + v62 + 0x2E0;
                                sub_14071EF30(v62, secondArg, reinterpret_cast<__int64>("charsel"), off_entry,
                                    reinterpret_cast<__int64>("AddSkill2Info"), 0, (__int64)buffer, 4u);
                                vect_destruct(buffer, 48i64, 4i64, dtor_fn);

                            }
                        } // end if readable
                    } // end if res
                } // end if addSkillInfoFunc executable
                else {
                    Console::PrintErr("addSkillInfoFunc ptr not executable\n");
                }
            }
            else {
                Console::PrintErr("Skipping call: invalid Block or target\n");
            }



            using fn_sub_14124BFE0 =__int64(__fastcall*)(__int64 a1);
            auto sub_14124BFE0 = reinterpret_cast<fn_sub_14124BFE0>(moduleBase + 0x124B3E0);
            using fn_Nucc_Memory_PushBlock = __int64(__fastcall*)(int a1);
            auto Nucc_Memory_PushBlock = reinterpret_cast<fn_Nucc_Memory_PushBlock>(moduleBase + 0x124B5D0);
            using fn_sub_14124BB20 = void(__fastcall*)(void* Block);
            auto sub_14124BB20 = reinterpret_cast<fn_sub_14124BB20>(moduleBase + 0x124AF20);
            using fn_Nucc_Memory_PopBlock = void(__fastcall*)();
            auto Nucc_Memory_PopBlock = reinterpret_cast<fn_Nucc_Memory_PopBlock>(moduleBase + 0x124B570);

            int v68 = sub_14124BFE0((__int64)Block);
            Nucc_Memory_PushBlock(v68);
            sub_14124BB20(Block);
            Nucc_Memory_PopBlock();
            _aligned_free(Block);      
            v135 = ++v59;
            Jutsu1_Index = v59;
            Jutsu2_Index = v59;
        } while (v59 < 6);
    } // if not locked


    using fn_sub_14073AAF0 = __int64(__fastcall*)(__int64 a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
    auto sub_14073AAF0 = reinterpret_cast<fn_sub_14073AAF0>(moduleBase + 0x739EF0);
    sub_14073AAF0(
        a1,
        a2,
        v10 - 1,
        *(int*)(v7 + 0x30),
        *(int*)(v7 + 0x34),
        *(int*)(v7 + 0xA0),
        *(int*)(v7 + 0xA4),
        *(int*)(v7 + 0x110),
        *(int*)(v7 + 0x114));


    sub_14071F020(
        v137,
        48i64 * *(int*)(v7 + 0x3EC) + v137 + 736,
        (__int64)"charsel",
        off_entry,
        (__int64)"OpenCostumeSkillSelect");
    return result;
}

Common::orig_sub_140747120_t Common::orig_sub_140747120 = nullptr;
void __fastcall Common::sub_140747120(__int64 a1, unsigned int a2) {
    Common::orig_sub_140747120(a1, a2);

    __int64 v91 = a2;
    __int64 v3 = *(__int64*)(a1 + 8i64 * (int)a2 + 0x400);
    __int64 v6 = *reinterpret_cast<uint64_t*>(Common::GetQword(0x14219D7E0) + 0x178);
    __int64 v7 = *(__int64*)(v3 + 24);
    unsigned __int64 v8 = (*(__int64*)(v3 + 32) - v7) >> 3;
    int v9 = v8 - 1;

    uint64_t* off_table = reinterpret_cast<uint64_t*>(Common::GetOffset(0x141FD4C60));
    uint64_t off_entry = 0;
    if (off_table && v91 >= 0) off_entry = off_table[v91];

    using fn_sub_14071EE40 = void(__fastcall*)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6);
    auto sub_14071EE40 = reinterpret_cast<fn_sub_14071EE40>(moduleBase + 0x71E240);

    using fn_BlockAllocator = __int64(__fastcall*)(__int64);
    auto Nucc_BlockAllocator = reinterpret_cast<fn_BlockAllocator>(moduleBase + 0x124B290);

    using fn_addSkillInfoFunc = __int64(__fastcall*)(__int64 a1, int a2, unsigned int a3, __int64* a4, int a5);
    auto addSkillInfoFunc = reinterpret_cast<fn_addSkillInfoFunc>(moduleBase + 0x6F3970);
    using fn_sub_140744E10 = __int64(__fastcall*)(__int64 a1, int a2, __int64 a3, __int64 a4);
    auto sub_140744E10 = reinterpret_cast<fn_sub_140744E10>(moduleBase + 0x744210);

    // ── Block for sub_14071EE40 (get skill indices) ──────────────────────────
    // Must be heap-allocated, 0x40 bytes, aligned to 16 — same as add function
    void* Block = _aligned_malloc(0x40, 16);
    if (!Block) return;
    memset(Block, 0, 0x40);

    __int64 v64 = v3 + 0x70i64 * v9;

    //Console::PrintErr("jutsu 1 offset: %p\n", v64 + 0x48);
    //Console::PrintErr("jutsu 2 offset: %p\n", v64 + 0x4C);

    sub_14071EE40(
        a1,
        0x30 * v91 + a1 + 0x2E0,
        (__int64)"charsel",
        (__int64)off_entry,
        (__int64)"GetSelectSkill1Index",
        (__int64)Block);
    *reinterpret_cast<int*>(v64 + 0x48) = *reinterpret_cast<int*>(reinterpret_cast<char*>(Block) + 0x20);

    // Reuse the same block for second call — re-zero between calls
    memset(Block, 0, 0x40);

    sub_14071EE40(
        a1,
        0x30 * v91 + a1 + 0x2E0,
        (__int64)"charsel",
        (__int64)off_entry,
        (__int64)"GetSelectSkill2Index",
        (__int64)Block);
    *reinterpret_cast<int*>(v64 + 0x4C) = *reinterpret_cast<int*>(reinterpret_cast<char*>(Block) + 0x20);

    _aligned_free(Block); // ← was leaking before

    /*// ── Block for addSkillInfoFunc — mirror the working pattern exactly ───────
    void* Block2 = _aligned_malloc(0x40, 16);
    if (!Block2) return;
    memset(Block2, 0, 0x40);

    const uint64_t vftable_ptr = static_cast<uint64_t>(moduleBase + 0x1735DC8);

    // Initialize via allocator first, THEN set vftable over whatever it wrote
    Nucc_BlockAllocator((__int64)Block2);
    *reinterpret_cast<uint64_t*>(Block2) = vftable_ptr; // &nuccStlAllocator<char>::`vftable'

    addSkillInfoFunc(v6, *(int*)(v64 + 0x30), *(int*)(v64 + 0x4C), (__int64*)Block2, 0);
    sub_140744E10(a1, v91, (__int64)"c_juy_001", (__int64)"c_juy_001");
    _aligned_free(Block2);*/
}

Common::orig_sub_140739220_t Common::orig_sub_140739220 = nullptr;
void __fastcall Common::sub_140739220(__int64 a1, __int64 a2) {
    using fnBlock = __int64(__fastcall*)(void* Block);

    // тип функции GetProperty: возвращает fnBlock*** и принимает ( __int64, __int64 )
    using fn_ccGameProperty_GetProperty = fnBlock **(__fastcall*)(__int64 a1, __int64 a2);

    // привязка по адресу
    auto ccGameProperty_GetProperty = reinterpret_cast<fn_ccGameProperty_GetProperty>(moduleBase + 0x1086240);

    Common::orig_sub_140739220(a1, a2);
    int v40; // ecx
    __int64 v41; // rax
    __int64(__fastcall * **v42)(void*); // rbx
    __int64(__fastcall * *v43)(void*); // rcx
    switch (*(__int64*)(a2 + 48)) {
    case 4i64:
        v40 = *(int*)(*(__int64*)(a2 + 32) + 32i64);
        v41 = *(__int64*)(a1 + 24);

        Console::PrintErr("v40 offset: %p\n", v40);
        Console::PrintErr("v41 offset: %p\n", v41);
        Console::PrintErr("*(int*)(v41 + 0x40C): %p\n", *(int*)(v41 + 0x40C));
        if (v40 != *(int*)(v41 + 0x40C))
        {
            *(int*)(v41 + 0x40C) = v40;
            
        }
        break;
    }

}


Common::orig_sub_140744AF0_t Common::orig_sub_140744AF0 = nullptr;
__int64 __fastcall Common::sub_140744AF0(__int64 a1, int a2)
{

    return 1;
}

static bool HexDumpToFile(const void* ptr, size_t size, const char* path) {
    FILE* f = nullptr;
    if (fopen_s(&f, path, "w") != 0 || !f) return false;
    const uint8_t* p = reinterpret_cast<const uint8_t*>(ptr);
    char line[256];
    for (size_t off = 0; off < size; off += 16) {
        int n = snprintf(line, sizeof(line), "%08zx: ", off);
        for (size_t i = 0; i < 16; ++i) {
            if (off + i < size) n += snprintf(line + n, sizeof(line) - n, "%02X ", p[off + i]);
            else n += snprintf(line + n, sizeof(line) - n, "   ");
        }
        n += snprintf(line + n, sizeof(line) - n, " |");
        for (size_t i = 0; i < 16 && off + i < size; ++i) {
            unsigned char c = p[off + i];
            line[n++] = (c >= 0x20 && c < 0x7F) ? (char)c : '.';
        }
        line[n++] = '|';
        line[n] = '\0';
        fprintf(f, "%s\n", line);
    }
    fclose(f);
    return true;
}


Common::orig_GetTextFromCRC32Code_t Common::orig_GetTextFromCRC32Code = nullptr;
__int64 __fastcall Common::GetTextFromCRC32Code(char* a1)
{
    if (!render::skip_crc32_conv)
        return Common::orig_GetTextFromCRC32Code(a1);
    else
        return  reinterpret_cast<__int64>(a1);
}

std::vector<int> Common::crc32_table() {
    std::vector<int> table(256);
    for (int i = 0; i < 256; ++i) {
        int crc = i << 24;
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x80000000) {
                crc = (crc << 1) ^ 0x04C11DB7;
            }
            else {
                crc <<= 1;
            }
        }
        table[i] = crc;
    }
    return table;
}

int Common::crc32(const std::string& input) {
    const auto table = Common::crc32_table();
    int crc = 0xFFFFFFFF;
    for (unsigned char byte : input) {
        int lookup_index = ((crc >> 24) ^ byte) & 0xFF;
        crc = (crc << 8) ^ table[lookup_index];
    }
    crc = ~crc;
    return crc;
}
bool Common::PatchWithNops(uintptr_t offset, size_t length)
{
    if (length == 0) return false;

    void* addr = reinterpret_cast<void*>(moduleBase + offset);

    DWORD oldProtect;
    if (!VirtualProtect(addr, length, PAGE_EXECUTE_READWRITE, &oldProtect))
        return false;

    memset(addr, 0x90, length);
    FlushInstructionCache(GetCurrentProcess(), addr, length);

    DWORD tmp;
    VirtualProtect(addr, length, oldProtect, &tmp);

    return true;
}
bool Common::PatchMemoryAtOffsetInt64(uint64_t offset, uint64_t newValue)
{
    uint8_t* target = reinterpret_cast<uint8_t*>(moduleBase) + offset;

    // Log the actual runtime address so you can verify it in debugger
    std::printf("Attempting patch at: 0x%llx\n", (unsigned long long)target);

    DWORD oldProtect;
    if (!VirtualProtect(target, 8, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        std::printf("VirtualProtect failed: %u\n", GetLastError());

        // Fallback: try WriteProcessMemory, bypasses some protections
        SIZE_T written = 0;
        if (!WriteProcessMemory(GetCurrentProcess(), target, &newValue, 8, &written) || written != 8)
        {
            std::printf("WriteProcessMemory also failed: %u\n", GetLastError());
            return false;
        }
        std::printf("WriteProcessMemory succeeded\n");
        return true;
    }

    memcpy(target, &newValue, 8);
    FlushInstructionCache(GetCurrentProcess(), target, 8);
    DWORD tmp;
    VirtualProtect(target, 8, oldProtect, &tmp);
    std::printf("Patched successfully\n");
    return true;
}
uint64_t Common::ReadInt64AtOffset(uint64_t offset)
{
    uint8_t* source = reinterpret_cast<uint8_t*>(moduleBase) + offset;
    uint64_t value = 0;
    memcpy(&value, source, 8);
    return value;
}

bool Common::CopyInt64(uint64_t sourceOffset, uint64_t destOffset)
{
    uint64_t value = ReadInt64AtOffset(sourceOffset);
    return PatchMemoryAtOffsetInt64(destOffset, value);
}
bool Common::PatchMemoryAtOffsetInt32(uint64_t offset, uint32_t newValue)
{
    uint8_t* target = reinterpret_cast<uint8_t*>(moduleBase) + offset;

    DWORD oldProtect;
    if (!VirtualProtect(target, 4, PAGE_EXECUTE_READWRITE, &oldProtect)) return false;

    uint8_t bytes[4];
    bytes[0] = static_cast<uint8_t>(newValue & 0xFF);
    bytes[1] = static_cast<uint8_t>((newValue >> 8) & 0xFF);
    bytes[2] = static_cast<uint8_t>((newValue >> 16) & 0xFF);
    bytes[3] = static_cast<uint8_t>((newValue >> 24) & 0xFF);

    memcpy(target, bytes, 4);
    FlushInstructionCache(GetCurrentProcess(), target, 4);

    DWORD tmp;
    VirtualProtect(target, 4, oldProtect, &tmp);
    return true;
}
bool Common::PatchMemoryAtOffsetInt16(uint64_t offset, uint16_t newValue)
{
    uint8_t* target = reinterpret_cast<uint8_t*>(moduleBase) + offset;

    DWORD oldProtect;
    if (!VirtualProtect(target, 2, PAGE_EXECUTE_READWRITE, &oldProtect)) return false;

    uint8_t bytes[2];
    bytes[0] = static_cast<uint8_t>(newValue & 0xFF);
    bytes[1] = static_cast<uint8_t>((newValue >> 8) & 0xFF);

    memcpy(target, bytes, 2);
    FlushInstructionCache(GetCurrentProcess(), target, 2);

    DWORD tmp;
    VirtualProtect(target, 2, oldProtect, &tmp);
    return true;
}
bool Common::PatchMemoryAtOffsetInt8(uint64_t offset, uint8_t newValue)
{
    uint8_t* target = reinterpret_cast<uint8_t*>(moduleBase) + offset;

    DWORD oldProtect;
    if (!VirtualProtect(target, 1, PAGE_EXECUTE_READWRITE, &oldProtect)) return false;

    uint8_t bytes[1];
    bytes[0] = static_cast<uint8_t>(newValue & 0xFF);

    memcpy(target, bytes, 1);
    FlushInstructionCache(GetCurrentProcess(), target, 1);

    DWORD tmp;
    VirtualProtect(target, 1, oldProtect, &tmp);
    return true;
}


//Gauge Bar Initialize Code
Common::orig_sub_14072B7A0_NSC_t Common::orig_sub_14072B7A0_NSC = nullptr;
__int64 __fastcall Common::sub_14072B7A0_NSC(__int64 a1, unsigned int a2) {

    __int64 result = Common::orig_sub_14072B7A0_NSC(a1, a2);
    


    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        for (int i = 1; i <= 2; i++) {
            char path[128];
            snprintf(path, sizeof(path), "_root.all_nut.all_gauge_%dp.mc_6pci_bar", i);


            typedef void(__fastcall* funct_sub_14071F110)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
            funct_sub_14071F110 sub_14071F110 = (funct_sub_14071F110)(moduleBase + 0x71E510);

            sub_14071F110((__int64)a1, (__int64)"battleGauge", (__int64)path, (__int64)"Initialize");
        }
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        for (int i = 1; i <= 2; i++) {
            char path[128];
            snprintf(path, sizeof(path), "_root.all_nut.all_gauge_%dp.mc_6pci_bar", i);


            typedef void(__fastcall* funct_sub_140607B5C)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
            funct_sub_140607B5C sub_140607B5C = (funct_sub_140607B5C)(moduleBase + 0x606F5C);

            sub_140607B5C((__int64)a1, (__int64)"battleGauge", (__int64)path, (__int64)"Initialize");
        }
    }
    return result;
}

//Gauge Bar Set function
Common::orig_sub_14072D5B0_NSC_t Common::orig_sub_14072D5B0_NSC = nullptr;
void __fastcall Common::sub_14072D5B0_NSC(__int64 a1) {
    Common::orig_sub_14072D5B0_NSC(a1);
    __int64 v1; // rsi


    using fn_sub_14071F390 = void(__fastcall*)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, unsigned int a7);
    auto sub_14071F390 = reinterpret_cast<fn_sub_14071F390>(moduleBase + 0x71E790);

    using fn_vect_const = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* ctor)(void*));
    auto vect_const = reinterpret_cast<fn_vect_const>(moduleBase + 0x1419780);

    using fn_vect_destruct = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* dtor)(void*));
    auto vect_destruct = reinterpret_cast<fn_vect_destruct>(moduleBase + 0x1418DCC);

    auto ctor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0xFE040);
    auto dtor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0xFE0E0);
    v1 = a1;
    for (int i = 1; i <= 2; i++) {
        alignas(8) char buffer[48 * 1];

        vect_const(buffer, /*elemSize=*/48, /*count=*/1, ctor_fn);
        Element* arr = reinterpret_cast<Element*>(buffer);
        for (int i = 0; i < 1; ++i) {
            if ((flags_ref(arr[i]) & 0x40) != 0) {
                call_vtable_offset_16_safe(arr[i]);
                arr[i].q0 = -1;
                arr[i].q1 = -1;
                arr[i].q1 = -1;
            }
        }
        //Console::PrintErr("Pucci player: %dp, val: %d", i, (__int64)MovesetPlus::PUCCI_AWA_COUNT[i - 1]);
        flags_ref(arr[0]) = 3;
        arr[0].extra = (__int64)MovesetPlus::PUCCI_AWA_COUNT[i-1];

        char path[128];
        snprintf(path, sizeof(path), "_root.all_nut.all_gauge_%dp.mc_6pci_bar", i);

        sub_14071F390(v1, reinterpret_cast<__int64>("battleGauge"), reinterpret_cast<__int64>(path),
            reinterpret_cast<__int64>("SetPucciRate"), 0, (__int64)buffer, 1u);
        vect_destruct(buffer, 48i64, 1i64, dtor_fn);



        vect_const(buffer, /*elemSize=*/48, /*count=*/1, ctor_fn);
        Element* arr2 = reinterpret_cast<Element*>(buffer);
        for (int i = 0; i < 1; ++i) {
            if ((flags_ref(arr2[i]) & 0x40) != 0) {
                call_vtable_offset_16_safe(arr2[i]);
                arr2[i].q0 = -1;
                arr2[i].q1 = -1;
            }
        }
        //Console::PrintErr("Pucci player: %dp, val: %d", i, (__int64)MovesetPlus::PUCCI_AWA_COUNT[i - 1]);
        flags_ref(arr2[0]) = 2;
        char* code = MovesetPlus::CHARACODE[i - 1];
        bool visible = (code != nullptr && std::strcmp(code, "6pci01") == 0);
        arr2[0].extra = (__int64)visible;
        sub_14071F390(v1, reinterpret_cast<__int64>("battleGauge"), reinterpret_cast<__int64>(path),
            reinterpret_cast<__int64>("SetVisible"), 0, (__int64)buffer, 1u);
        vect_destruct(buffer, 48i64, 1i64, dtor_fn);
    }
}
//vect_const function
void __fastcall Common::sub_1400FEC40(__int64* a1)
{
    *a1 = -1i64;
    a1[2] = 0i64;
    *((int*)a1 + 6) = 0;
    a1[1] = -1i64;
}
//vect_destruct function
void __fastcall Common::sub_1400FECE0(__int64** a1)
{
    if (((int)a1[3] & 0x40) != 0)
    {
        (*(void(__fastcall**)(__int64*, __int64**, __int64*))(*a1[2] + 16i64))(a1[2], a1, a1[4]);
        a1[2] = 0i64;
        *((int*)a1 + 6) = 0;
    }
    else
    {
        *((int*)a1 + 6) = 0;
    }
}
Common::orig_sub_140641A90_NS4_t Common::orig_sub_140641A90_NS4 = nullptr;
__int64 __fastcall Common::sub_140641A90_NS4(int* a1) {
    __int64 result = Common::orig_sub_140641A90_NS4(a1);

    int* v1; // rsi


    using fn_sub_14071F390 = void(__fastcall*)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, unsigned int a7);
    auto sub_14071F390 = reinterpret_cast<fn_sub_14071F390>(moduleBase + 0x606FA0);

    using fn_vect_const = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* ctor)(void*));
    auto vect_const = reinterpret_cast<fn_vect_const>(moduleBase + 0xB3F3D8);

    using fn_vect_destruct = void(__fastcall*)(char* dest, __int64 elemSize, __int64 count, void(__fastcall* dtor)(void*));
    auto vect_destruct = reinterpret_cast<fn_vect_destruct>(moduleBase + 0xB3F440);

    auto ctor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0x9E1820);
    auto dtor_fn = reinterpret_cast<void(__fastcall*)(void*)>(moduleBase + 0x9E65C0);
    v1 = a1;
    for (int i = 1; i <= 2; i++) {
        alignas(8) char buffer[48 * 1];

        vect_const(buffer, /*elemSize=*/48, /*count=*/1, (void(__fastcall*)(void*))Common::sub_1400FEC40);
        Element* arr = reinterpret_cast<Element*>(buffer);
        for (int i = 0; i < 1; ++i) {
            if ((flags_ref(arr[i]) & 0x40) != 0) {
                call_vtable_offset_16_safe(arr[i]);
                arr[i].q0 = -1;
                arr[i].q1 = -1;
                arr[i].q1 = -1;
            }
        }
        //Console::PrintErr("Pucci player: %dp, val: %d", i, (__int64)MovesetPlus::PUCCI_AWA_COUNT[i - 1]);
        flags_ref(arr[0]) = 3;
        arr[0].extra = (__int64)MovesetPlus::PUCCI_AWA_COUNT[i - 1];

        char path[128];
        snprintf(path, sizeof(path), "_root.all_nut.all_gauge_%dp.mc_6pci_bar", i);

        sub_14071F390(reinterpret_cast<__int64>(v1), reinterpret_cast<__int64>("battleGauge"), reinterpret_cast<__int64>(path),
            reinterpret_cast<__int64>("SetPucciRate"), 0, (__int64)buffer, 1u);
        vect_destruct(buffer, 48i64, 1i64, (void(__fastcall*)(void*))Common::sub_1400FECE0);



        vect_const(buffer, /*elemSize=*/48, /*count=*/1, (void(__fastcall*)(void*))Common::sub_1400FEC40);
        Element* arr2 = reinterpret_cast<Element*>(buffer);
        for (int i = 0; i < 1; ++i) {
            if ((flags_ref(arr2[i]) & 0x40) != 0) {
                call_vtable_offset_16_safe(arr2[i]);
                arr2[i].q0 = -1;
                arr2[i].q1 = -1;
            }
        }
        //Console::PrintErr("Pucci player: %dp, val: %d", i, (__int64)MovesetPlus::PUCCI_AWA_COUNT[i - 1]);
        flags_ref(arr2[0]) = 2;
        char* code = MovesetPlus::CHARACODE[i - 1];
        bool visible = (code != nullptr && std::strcmp(code, "6pci01") == 0);
        arr2[0].extra = (__int64)visible;
        sub_14071F390(reinterpret_cast<__int64>(v1), reinterpret_cast<__int64>("battleGauge"), reinterpret_cast<__int64>(path),
            reinterpret_cast<__int64>("SetVisible"), 0, (__int64)buffer, 1u);
        vect_destruct(buffer, 48i64, 1i64, (void(__fastcall*)(void*))Common::sub_1400FECE0);
    }

    return result;

}

Common::orig_IsInFrontOfOwner_t Common::orig_IsInFrontOfOwner = nullptr;
bool __fastcall Common::IsInFrontOfOwner(__int64 a1, float a2, float a3, float a4)
{
    int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
    const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

    bool isStand = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6whs01") == 0);
    float new_a2 = a2;
    float new_a3 = a3;
    float new_a4 = a4;
    if (isStand) {
        new_a2 = 1.0f;
        new_a3 = 300000.0f;
        new_a4 = 360.0f;
    }

    return Common::orig_IsInFrontOfOwner(a1, new_a2, new_a3, new_a4);
}

Common::orig_ccPlayerPartner2AKM_OnThroughDamage_t Common::orig_ccPlayerPartner2AKM_OnThroughDamage = nullptr;
void __fastcall Common::ccPlayerPartner2AKM_OnThroughDamage(__int64* a1)
{
    int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
    const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

    bool isStand = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6whs01") == 0);
    if (!isStand) {
        Common::orig_ccPlayerPartner2AKM_OnThroughDamage(a1);
    }
}


Common::orig_EntrySmokeAtPartnerPos_t Common::orig_EntrySmokeAtPartnerPos = nullptr;
void __fastcall Common::EntrySmokeAtPartnerPos(__int64 a1)
{
    __int64 partner_ptr = (__int64)ccPlayer::GetPartnerPointer((ccPlayerMain*)a1);
    if (partner_ptr) {
        int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)partner_ptr);
        const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

        bool isStand = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6whs01") == 0);
        if (!isStand) {
            Console::PrintErr("Partner code: %s\n", charCodeCostume);
            Common::orig_EntrySmokeAtPartnerPos(a1);
        }
    }
}



Common::orig_CharacterManager_1CMN_t Common::orig_CharacterManager_1CMN = nullptr;
__int64* __fastcall Common::CharacterManager_1CMN(__int64 a1)
{
    __int64* result = Common::orig_CharacterManager_1CMN(a1);
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {



        *(int*)(a1 + 0x12D30) = 0;
        *(__int64*)(a1 + 0x12D40) = 0i64;
        *(__int64*)(a1 + 0x12D48) = 0i64;
        *(__int64*)(a1 + 0x12D50) = 0i64;
        *(__int64*)(a1 + 0x12D58) = 0i64;
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        *(int*)(a1 + 0x15750) = 0;
        *(__int64*)(a1 + 0x15760) = 0i64;
        *(__int64*)(a1 + 0x15778) = 0i64;
        *(__int64*)(a1 + 0x15768) = 0i64;
        *(__int64*)(a1 + 0x15770) = 0i64;
    }


    return result;
}

//2KIB CONDITION - SCREEN EFFECT
Common::orig_sub_1409FF490_t Common::orig_sub_1409FF490 = nullptr;
__int64 __fastcall Common::sub_1409FF490(__int64 a1)
{
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
        const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

        bool isStand = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6pci01") == 0);
        if (isStand) {

            using fn_sub_140645960 = void(__fastcall*)(__int64 a1);
            auto sub_140645960 = reinterpret_cast<fn_sub_140645960>(moduleBase + 0x644D60);
            sub_140645960(a1);
        }

    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
        int characode_id = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
        const char* charCodeCostume = ccPlayer::GetCharCode(characode_id);

        bool isStand = (charCodeCostume != nullptr && std::strcmp(charCodeCostume, "6pci01") == 0);
        if (isStand) {

            using fn_sub_140645960 = void(__fastcall*)(__int64 a1);
            auto sub_140645960 = reinterpret_cast<fn_sub_140645960>(moduleBase + 0x580390);
            sub_140645960(a1);
        }
    }
   
    __int64 result = Common::orig_sub_1409FF490((__int64*)a1);
    return result;
}

Common::orig_nullsub_3187_t Common::orig_nullsub_3187 = nullptr;
__int64 __fastcall Common::sub_14083B360(__int64 a1)
{
    using fn_sub_140A01E20 = __int64(__fastcall*)(__int64 a1);
    auto sub_140A01E20 = reinterpret_cast<fn_sub_140A01E20>(moduleBase + 0xA01220);
    return sub_140A01E20(a1);
}


int Common::PatchAddress(uintptr_t slotAddress, uintptr_t newFunctionAddress) {

    // сохранение старого значения
    uintptr_t oldValue = 0;

    DWORD oldProtect;
    if (!VirtualProtect(reinterpret_cast<LPVOID>(slotAddress), sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        std::printf("VirtualProtect fail: %u\n", GetLastError());
        return 1;
    }

    // прочитать и заменить
    oldValue = *reinterpret_cast<uintptr_t*>(slotAddress);
    *reinterpret_cast<uintptr_t*>(slotAddress) = newFunctionAddress;

    // восстановить защиты страницы
    DWORD tmp;
    VirtualProtect(reinterpret_cast<LPVOID>(slotAddress), sizeof(uintptr_t), oldProtect, &tmp);

    // сброс кэша инструкций (безопасно)
    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<LPCVOID>(slotAddress), sizeof(uintptr_t));

    std::printf("Patched: slot=0x%llx -> 0x%llx (old=0x%llx)\n",
        (unsigned long long)slotAddress,
        (unsigned long long)newFunctionAddress,
        (unsigned long long)oldValue);

    return 0;
}

Common::orig_GetDamageReactionAction_t Common::orig_GetDamageReactionAction = nullptr;
__int64 __fastcall Common::GetDamageReactionAction(int* a1, int a2, __int64 a3)
{
    if (a2 > 37) {
        switch (a2) {
        case 38:
            return 8i64; //PL_ACT_LAND
            break;
        default:
            return Common::orig_GetDamageReactionAction(a1, a2, a3);
            break;
        }
    }
    else {
        return Common::orig_GetDamageReactionAction(a1, a2, a3);
    }
}
//Function for enabling hit during down slow action
void __fastcall sub_1407A8A58(__int64 a1)
{
    __int64 v2; // rax
    __int64 v3; // rdx
    int v4; // r8d

    using fn_sub_14052A414 = __int64(__fastcall*)(__int16 a1);
    auto sub_14052A414 = reinterpret_cast<fn_sub_14052A414>(moduleBase + 0x529814);

    using fn_SetInvincibleBase = void(__fastcall*)(__int64 a1, int a2, int a3);
    auto SetInvincibleBase = reinterpret_cast<fn_SetInvincibleBase>(moduleBase + 0x79C15C);

    // Исправленный прототип: функция возвращает 16-битный ID по строке
    using fn_sub_140529BEC = unsigned __int16(__fastcall*)(const char* a1);
    auto sub_140529BEC = reinterpret_cast<fn_sub_140529BEC>(moduleBase + 0x528FEC);

    v2 = sub_14052A414(*(uint8_t*)(a1 + 64380));
    v3 = 0i64;
    if (v2)
        v3 = *(__int64*)(v2 + 72) | *(__int64*)(a1 + 64464);
    if (*(uint8_t*)(a1 + 64380) == sub_140529BEC("DAMAGE_ID_DOWN_SLOW"))
    {
        v4 = *(int*)(a1 + 3276) > 0
            || *(int*)(a1 + 3280) / (int)(0xBB8u / *((unsigned __int8*)Common::GetQword(0x1416663C8) + 2370));
        SetInvincibleBase(a1, 1, v4);
    }
}


Common::orig_CtrlAct_PL_ACT_DMG_TO_DOWN_t Common::orig_CtrlAct_PL_ACT_DMG_TO_DOWN = nullptr;
void __fastcall Common::CtrlAct_PL_ACT_DMG_TO_DOWN(__int64 a1, int a2) {
    unsigned __int8 v3; // al
    __int64 v4; // rdx
    __int64 v5; // rcx
    __int64 v6; // rax
    float* v7; // rsi
    int v8; // eax
    __int64 v9; // r8
    int v10; // eax
    float v11; // xmm1_4
    char v12[40]; // [rsp+50h] [rbp-28h] BYREF
    unsigned int v13; // [rsp+88h] [rbp+10h] BYREF
    char v14; // [rsp+90h] [rbp+18h] BYREF
    char v15; // [rsp+98h] [rbp+20h] BYREF


    using fn_IsAnmTimingCome = __int64(__fastcall*)(__int64 a1, int a2);
    auto IsAnmTimingCome = reinterpret_cast<fn_IsAnmTimingCome>(moduleBase + 0x77D00C);
    using fn_sub_1407BF574 = __int64(__fastcall*)(__int64 a1, unsigned int a2);
    auto sub_1407BF574 = reinterpret_cast<fn_sub_1407BF574>(moduleBase + 0x7BE974);
    using fn_sub_1407A87BC = __int64(__fastcall*)(__int64 a1);
    auto sub_1407A87BC = reinterpret_cast<fn_sub_1407A87BC>(moduleBase + 0x7A7BBC);
    using fn_IsEndAnm = __int64(__fastcall*)(__int64 a1);
    auto IsEndAnm = reinterpret_cast<fn_IsEndAnm>(moduleBase + 0x77D14C);
    //using fn_sub_1407A8A58 = __int64(__fastcall*)(__int64 a1);
    //auto sub_1407A8A58 = reinterpret_cast<fn_sub_1407A8A58>(moduleBase + 0x7A7E58);

    if (a2) {
        if (a2 == 1) {
            if ((unsigned int)ccPlayer::GetAnmId((ccPlayerMain*)a1) == 2)
            {
                v3 = Game::GetFPS();
                if ((unsigned int)IsAnmTimingCome(a1, 0xBB8u / v3))
                    sub_1407BF574(a1, 1i64);
            }
            else if ((unsigned int)ccPlayer::GetAnmId((ccPlayerMain*)a1) == 1)
            {
                sub_1407A87BC(a1);
            }
            sub_1407A8A58(a1);
            if ((unsigned int)IsEndAnm(a1))
            {
                *(int*)(a1 + 4268) = 1;
                v4 = 32i64;
                v5 = a1;
                (*(void(__fastcall**)(__int64, __int64))(*(__int64*)a1 + 3496i64))(v5, v4);
            }
        }
    }
    else {
        Common::orig_CtrlAct_PL_ACT_DMG_TO_DOWN(a1, a2);
    }
}

