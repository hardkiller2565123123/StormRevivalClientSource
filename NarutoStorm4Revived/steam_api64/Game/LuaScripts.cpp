#include <iostream>
#include <Windows.h>
#include "Common.h"
#include "PatternScan.h"
#include "LuaScripts.h"
#include <thread>
#include "ccPlayerMain.h"
#include "Utilities.h"
#include "Offsets.h"
#include "MovesetPlus.h"
#include "Console.h"

using fn_tolua_isnumber = __int64(__fastcall*)(__int64 a1, int a2, int a3, __int64 a4);
using fn_tolua_isnoobj = __int64(__fastcall*)(__int64 a1, int a2, __int64 a3);
using fn_tolua_error = const char* (__fastcall*)(__int64 a1, __int64 a2, unsigned int* a); 
using fn_tolua_function_NSC = __int64(__fastcall*)(__int64* a1, const char* name, __int64 funcptr);
using fn_tolua_function_NS4 = __int64(__fastcall*)(__int64 a1, __int64 name, __int64 funcptr);
using fn_tolua_open = __int64(__fastcall*)(__int64* a1);
using fn_tolua_endmodule = __int64(__fastcall*)(__int64 a1);

using lua_CFunction = int(__cdecl*)(__int64* L);
// get pointer (replace offset with verified one)
__int64 __fastcall ccFreeBattleIa_RestoreFreeBattleCamera_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_RestoreFreeBattleCamera();



__int64 __fastcall ccFreeBattleIa_AllDispOff_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_AllDispOff();


__int64 __fastcall ccFreeBattleIa_AllDispOn_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_AllDispOn();

__int64 __fastcall ccFreeBattleIa_BackgroundDrawOff_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_BackgroundDrawOff();
__int64 __fastcall ccFreeBattleIa_BackgroundDrawOn_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_BackgroundDrawOn();


__int64 __fastcall ccFreeBattleIa_HudOn_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_HudOn();


__int64 __fastcall ccFreeBattleIa_HudOff_Initialize(__int64 a1);
void __fastcall ccFreeBattleIa_HudOff();


LuaScript::orig_ns2_tolua_ccRegistScript_open_t LuaScript::orig_ns2_tolua_ccRegistScript_open = nullptr;
__int64 __fastcall LuaScript::Hooked_ns2_tolua_ccRegistScript_open(__int64* a1) {
	__int64 result = LuaScript::orig_ns2_tolua_ccRegistScript_open(a1);
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		auto tolua_function = reinterpret_cast<fn_tolua_function_NSC>(moduleBase + 0x1054230);
		auto tolua_endmodule = reinterpret_cast<fn_tolua_endmodule>(moduleBase + 0x1054220);

		tolua_function(a1, "ccFreeBattleIa_RestoreFreeBattleCamera", (__int64)ccFreeBattleIa_RestoreFreeBattleCamera_Initialize);
		tolua_function(a1, "ccFreeBattleIa_AllDispOff", (__int64)ccFreeBattleIa_AllDispOff_Initialize);
		tolua_function(a1, "ccFreeBattleIa_AllDispOn", (__int64)ccFreeBattleIa_AllDispOn_Initialize);
		tolua_function(a1, "ccFreeBattleIa_BackgroundDrawOff", (__int64)ccFreeBattleIa_BackgroundDrawOff_Initialize);
		tolua_function(a1, "ccFreeBattleIa_BackgroundDrawOn", (__int64)ccFreeBattleIa_BackgroundDrawOn_Initialize);
		tolua_function(a1, "ccFreeBattleIa_HudOn", (__int64)ccFreeBattleIa_HudOn_Initialize);
		tolua_function(a1, "ccFreeBattleIa_HudOff", (__int64)ccFreeBattleIa_HudOff_Initialize);
		tolua_endmodule((__int64)a1);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


		auto tolua_function = reinterpret_cast<fn_tolua_function_NS4>(moduleBase + 0x9AA9C0);
		auto tolua_endmodule = reinterpret_cast<fn_tolua_endmodule>(moduleBase + 0x9AA9B0);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_RestoreFreeBattleCamera", (__int64)ccFreeBattleIa_RestoreFreeBattleCamera_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_AllDispOff", (__int64)ccFreeBattleIa_AllDispOff_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_AllDispOn", (__int64)ccFreeBattleIa_AllDispOn_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_BackgroundDrawOff", (__int64)ccFreeBattleIa_BackgroundDrawOff_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_BackgroundDrawOn", (__int64)ccFreeBattleIa_BackgroundDrawOn_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_HudOn", (__int64)ccFreeBattleIa_HudOn_Initialize);
		tolua_function((__int64)a1, (__int64)"ccFreeBattleIa_HudOff", (__int64)ccFreeBattleIa_HudOff_Initialize);
		tolua_endmodule((__int64)a1);
	}
	return result;
}

void hud_control(int mode) {
	typedef __int64(__fastcall* Sub_141086E40Type)(__int64, __int64);
	Sub_141086E40Type sub_141086E40_f = reinterpret_cast<Sub_141086E40Type>(MovesetPlus::VTableAddress);


	typedef __int64(__fastcall* Fn_t)(void*);
	typedef Fn_t* FnPtrArray;                    //      
	typedef FnPtrArray* TripleFn;
	typedef TripleFn(__fastcall* Sub_141086E40Type2)(__int64, __int64);
	Sub_141086E40Type2 sub_141086E40_f2 = reinterpret_cast<Sub_141086E40Type2>(MovesetPlus::VTableAddress);



	typedef __int64* (__fastcall* sub_140AB7930Type)(__int64, __int64);
	sub_140AB7930Type sub_140AB7930_f = reinterpret_cast<sub_140AB7930Type>(MovesetPlus::VTableAddress);
	__int64* pXmmword = nullptr;
	__int64 sub_1404BF150_address = 0;




	if ((render::hudon == 2 && mode == 0) || (mode == 1 && render::hudon != 1)) {
		//std::cout << "HUD Disabled!" << std::endl;


		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetSC::VTableXmmwordOffset - 0xC00);

			if (!pXmmword)
				return;
			typedef __int64(__fastcall* sub_1404BF150_t)(__int64 a1);
			sub_1404BF150_t sub_1404BF150 = reinterpret_cast<sub_1404BF150_t>(moduleBase + 0x4BE550);
			__int64 highPart = pXmmword[1];

			__int64 v14 = sub_141086E40_f(highPart, reinterpret_cast<__int64>("scene_battle"));

			__int64 BattleUIPointer = sub_1404BF150(v14);
			if (BattleUIPointer && *(__int64*)(BattleUIPointer + 552)) {


				typedef __int64(__fastcall* sub_14086C080_t)(__int64 a1);
				sub_14086C080_t sub_14086C080 = reinterpret_cast<sub_14086C080_t>(moduleBase + 0x86B480);
				sub_14086C080(BattleUIPointer);


			}


		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetS4::VTableXmmwordOffset - 0xC00);

			if (!pXmmword)
				return;
			__int64 highPart = pXmmword[1];


			TripleFn v2 = sub_141086E40_f2(highPart, reinterpret_cast<__int64>("scene_battle"));

			FnPtrArray v3 = v2 ? v2[1] : nullptr; // v3 == v2[1]


			typedef __int64(__fastcall* sub_1406D9230_t)(__int64 a1);
			sub_1406D9230_t sub_1406D9230 = reinterpret_cast<sub_1406D9230_t>(moduleBase + 0x6D8630);
			if (v3)
			{
				__int64 v4 = *reinterpret_cast<__int64*>(reinterpret_cast<char*>(v3) + 16);
				if (v4)
					sub_1406D9230(v4);
			}
		}


		render::hudon = 1;
	}
	else if ((render::hudon == 1 && mode == 0) || (mode == 2 && render::hudon != 2)) {
		//std::cout << "HUD Enabled!" << std::endl;



		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetSC::VTableXmmwordOffset - 0xC00);

			if (!pXmmword)
				return;
			typedef __int64(__fastcall* sub_1404BF150_t)(__int64 a1);
			sub_1404BF150_t sub_1404BF150 = reinterpret_cast<sub_1404BF150_t>(moduleBase + 0x4BE550);
			__int64 highPart = pXmmword[1];


			TripleFn v2 = sub_141086E40_f2(highPart, reinterpret_cast<__int64>("scene_battle"));

			FnPtrArray v3 = v2 ? v2[1] : nullptr; // v3 == v2[1]


			typedef void(__fastcall* sub_14086C0A0_t)(__int64 a1);
			sub_14086C0A0_t sub_14086C0A0 = reinterpret_cast<sub_14086C0A0_t>(moduleBase + 0x86B4A0);
			if (v3)
			{
				__int64 v4 = *reinterpret_cast<__int64*>(reinterpret_cast<char*>(v3) + 16);
				if (v4)
					sub_14086C0A0(v4);
			}


		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetS4::VTableXmmwordOffset - 0xC00);

			if (!pXmmword)
				return;
			__int64 highPart = pXmmword[1];


			TripleFn v2 = sub_141086E40_f2(highPart, reinterpret_cast<__int64>("scene_battle"));

			FnPtrArray v3 = v2 ? v2[1] : nullptr; // v3 == v2[1]


			typedef void(__fastcall* sub_14086C0A0_t)(__int64 a1);
			sub_14086C0A0_t sub_14086C0A0 = reinterpret_cast<sub_14086C0A0_t>(moduleBase + 0x6D864C);
			if (v3)
			{
				__int64 v4 = *reinterpret_cast<__int64*>(reinterpret_cast<char*>(v3) + 16);
				if (v4)
					sub_14086C0A0(v4);
			}

		}

		render::hudon = 2;
	}
}

__int64 __fastcall ccFreeBattleIa_HudOn_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_HudOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_HudOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_HudOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_HudOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}
__int64 __fastcall ccFreeBattleIa_HudOff_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_HudOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_HudOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_HudOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_HudOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}

__int64 __fastcall ccFreeBattleIa_BackgroundDrawOff_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_BackgroundDrawOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_BackgroundDrawOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_BackgroundDrawOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_BackgroundDrawOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}

__int64 __fastcall ccFreeBattleIa_BackgroundDrawOn_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_BackgroundDrawOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_BackgroundDrawOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_BackgroundDrawOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_BackgroundDrawOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}

__int64 __fastcall ccFreeBattleIa_AllDispOff_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_AllDispOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_AllDispOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_AllDispOff();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_AllDispOff'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}

__int64 __fastcall ccFreeBattleIa_AllDispOn_Initialize(__int64 a1)
{
	unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_AllDispOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_AllDispOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
		auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			ccFreeBattleIa_AllDispOn();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_AllDispOn'.", (unsigned int*)v3);
			return 0i64;
		}
	}
	return 0i64;

}


__int64 __fastcall ccFreeBattleIa_RestoreFreeBattleCamera_Initialize(__int64 a1)
{
    unsigned int v3[6]; // [rsp+20h] [rbp-18h] BYREF
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

        auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x1052A90);
        auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x1052680);
        if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
        {
			std::thread([]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // delay
				ccFreeBattleIa_RestoreFreeBattleCamera();
				}).detach();
            return 0i64;
        }
        else
        {
            tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_RestoreFreeBattleCamera'.", (unsigned int*)v3);
            return 0i64;
        }
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

        auto tolua_isnoobj = reinterpret_cast<fn_tolua_isnoobj>(moduleBase + 0x9A9C90);
        auto tolua_error = reinterpret_cast<fn_tolua_error>(moduleBase + 0x9a9a60);
		if ((unsigned int)tolua_isnoobj((__int64)a1, 1, (__int64)v3))
		{
			std::thread([]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(50)); // delay
				ccFreeBattleIa_RestoreFreeBattleCamera();
				}).detach();
			return 0i64;
		}
		else
		{
			tolua_error(a1, (__int64)"#ferror in function 'ccFreeBattleIa_RestoreFreeBattleCamera'.", (unsigned int*)v3);
			return 0i64;
		}
    }  
    return 0i64;
    
}
void ccFreeBattleIa_HudOn()
{
	hud_control(2);



}
void ccFreeBattleIa_HudOff()
{
	hud_control(1);



}
void ccFreeBattleIa_BackgroundDrawOff()
{
	__int64 pl1 = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		typedef __int64(__fastcall* funct)(__int64 a1);
		funct sub_140A3F4A0 = (funct)(moduleBase + 0xA3E840);
		sub_140A3F4A0(pl1);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		typedef __int64(__fastcall* funct)(__int64 a1);
		funct sub_1407F5B18 = (funct)(moduleBase + 0x7F4ECC);
		sub_1407F5B18(pl1);
	}



}
void ccFreeBattleIa_BackgroundDrawOn()
{
	__int64 pl1 = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		typedef __int64(__fastcall* funct)(__int64 a1);
		funct sub_140A3F4A0 = (funct)(moduleBase + 0xA3E8A0);
		sub_140A3F4A0(pl1);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		typedef __int64(__fastcall* funct)(__int64 a1);
		funct sub_1407F5B18 = (funct)(moduleBase + 0x7F4F18);
		sub_1407F5B18(pl1);
	}


}

void ccFreeBattleIa_AllDispOff()
{
	__int64 pl1 = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
	__int64 pl2 = (__int64)BattleUtils::ccGame_GetPlayerLeader(1);


	__int64 v1; // rax  
	__int64 v2; // rax  
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl1 + 3512i64))(pl1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 3000i64))(v1);
		v2 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl2 + 3512i64))(pl2);
		if (v2)
			(*(void(__fastcall**)(__int64))(*(__int64*)v2 + 3000i64))(v2);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl1 + 3464i64))(pl1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 2968i64))(v1);
		v2 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl2 + 3464i64))(pl2);
		if (v2)
			(*(void(__fastcall**)(__int64))(*(__int64*)v2 + 2968i64))(v2);
	}



}

void ccFreeBattleIa_AllDispOn()
{
	__int64 pl1 = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
	__int64 pl2 = (__int64)BattleUtils::ccGame_GetPlayerLeader(1);


	__int64 v1; // rax  
	__int64 v2; // rax  
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl1 + 2992i64))(pl1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 3000i64))(v1);
		v2 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl2 + 2992i64))(pl2);
		if (v2)
			(*(void(__fastcall**)(__int64))(*(__int64*)v2 + 3000i64))(v2);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl1 + 3464i64))(pl1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 2960i64))(v1);
		v2 = (*(__int64(__fastcall**)(__int64))(*(__int64*)pl2 + 3464i64))(pl2);
		if (v2)
			(*(void(__fastcall**)(__int64))(*(__int64*)v2 + 2960i64))(v2);
	}



}


void __fastcall ccFreeBattleIa_RestoreFreeBattleCamera()
{
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		using fn_sub_140AB7020 = __int64(__fastcall*)(__int64 a1);
		auto sub_140AB7020 = reinterpret_cast<fn_sub_140AB7020>(moduleBase + 0xAB6420);
		using fn_ChangeAlgorithm = __int64(__fastcall*)(__int64 a1, __int64 a2);
		auto ChangeAlgorithm = reinterpret_cast<fn_ChangeAlgorithm>(moduleBase + 0xAB6380);
		using fn_ccCameraJudgeDuel = __int64* (__fastcall*)(__int64* a1);
		auto ccCameraJudgeDuel = reinterpret_cast<fn_ccCameraJudgeDuel>(moduleBase + 0x4B9D40);
		using fn_operator_func = __int64* (__fastcall*)(size_t a1, __int64 a2, int a3);
		auto operator_func = reinterpret_cast<fn_operator_func>(moduleBase + 0x124A270);
		sub_140AB7020(Common::GetQword(0x14219D8A0));
		__int64* v6 = operator_func(
			0x10ui64,
			(__int64)"D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ReminisceneBattle\\ccStateReminisceneBattle.cpp",
			1359);
		if (v6)
			v6 = ccCameraJudgeDuel(v6);
		ChangeAlgorithm(Common::GetQword(0x14219D8A0), (__int64)v6);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		using fn_sub_14085526C = __int64(__fastcall*)(__int64 a1);
		auto sub_14085526C = reinterpret_cast<fn_sub_14085526C>(moduleBase + 0x85466C);
		using fn_ChangeAlgorithm = __int64(__fastcall*)(__int64 a1, __int64 a2);
		auto ChangeAlgorithm = reinterpret_cast<fn_ChangeAlgorithm>(moduleBase + 0x854620);
		using fn_ccCameraJudgeDuel = __int64* (__fastcall*)(__int64* a1);
		auto ccCameraJudgeDuel = reinterpret_cast<fn_ccCameraJudgeDuel>(moduleBase + 0x411B5C);
		using fn_operator_func = __int64* (__fastcall*)(size_t a1, __int64 a2, int a3);
		auto operator_func = reinterpret_cast<fn_operator_func>(moduleBase + 0xA00BF0);
		sub_14085526C(Common::GetQword(0x14161C940));
		__int64* v6 = operator_func(
			0x10ui64,
			(__int64)"D:\\next5\\branches\\MasterV160\\trunk\\narutoNext4\\prog\\source\\ReminisceneBattle\\ccStateReminisceneBattle.cpp",
			1359);
		if (v6)
			v6 = ccCameraJudgeDuel(v6);
		ChangeAlgorithm(Common::GetQword(0x14161C940), (__int64)v6);
	}


}
