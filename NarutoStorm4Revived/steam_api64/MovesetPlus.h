#ifndef MovesetPlus_H 
#define MovesetPlus_H
#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "PatternScan.h"

inline __int64 BgmOffFunctionAdress;
inline __int64 BgmOnFunctionAdress;
inline __int64 BgmOff2FunctionAdress;
inline __int64 SlowTimeAddress;
inline __int64 SlowTimeAddress1;
inline __int64 SlowTimeAddress2;
inline int cancelUpgradeFunctionState[2];
inline __int64 sub_14097F1E0Adress;
inline __int64 sub_1405C3970Adress;
inline __int64 sub_1405C7EC0Adress;
inline __int64 sub_1405C8F00Adress;
inline __int64 sub_140978B00Adress;


inline __int64 EffectHandlerAddress;
inline __int64 ResolveEffectAddress;
inline __int64 ExecuteEffectAddress;
class MovesetPlus
{
public:
	static __int64 BgmOffFunctionAdress;
	static __int64 BgmOnFunctionAdress;
	static __int64 BgmOff2FunctionAdress;

	static __int64 InitializeHandlerAddress;
	static __int64 ResolveEffectAddress;
	static __int64 ExecuteEffectAddress;

	static __int64 HandleStageChangeAddress;
	static __int64 DefaultStageHandlerAddress;
	static __int64 SpecificStageHandlerAddress;
	static __int64 CharacterCondition_funcAddress;
	static __int64 FixCharPositionAddress;
	static __int64 VTableAddress;

	static int cancelUpgradeFunctionState[2];
	static __int64 sub_14097F1E0Adress;
	static __int64 sub_1405C3970Adress;
	static __int64 sub_1405C7EC0Adress;
	static __int64 sub_1405C8F00Adress;
	static __int64 sub_140978B00Adress;

	typedef __int64(__fastcall* orig_EnableUpgradeCancel_t)(__int64 a1);
	static orig_EnableUpgradeCancel_t orig_EnableUpgradeCancel;
	static int __fastcall EnableUpgradeCancel(__int64 a1);


	typedef __int64(__fastcall* orig_ME_CAMERA_LOOKAT_SET_t)(__int64 a1, char* a2);
	static orig_ME_CAMERA_LOOKAT_SET_t orig_ME_CAMERA_LOOKAT_SET;
	static __int64 __fastcall ME_CAMERA_LOOKAT_SET(__int64 a1, char* a2);


	typedef __int64(__fastcall* orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2_t)(__int64 a1, char* a2);
	static orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2_t orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2;
	static __int64 __fastcall ME_CAMERA_LOOKAT_SET_HUGEAWAKE2(__int64 a1, char* a2);

	typedef __int64(__fastcall* orig_ME_DRAWOBJ_DISABLE_t)(__int64 a1, __int64 a2);
	static orig_ME_DRAWOBJ_DISABLE_t orig_ME_DRAWOBJ_DISABLE;
	static __int64 __fastcall ME_DRAWOBJ_DISABLE(__int64 a1, __int64 a2);

	typedef __int64(__fastcall* orig_ME_DRAWOBJ_ENABLE_t)(__int64 a1, __int64 a2);
	static orig_ME_DRAWOBJ_ENABLE_t orig_ME_DRAWOBJ_ENABLE;
	static __int64 __fastcall ME_DRAWOBJ_ENABLE(__int64 a1, __int64 a2);

	static void me_hud_control(int mode);
	static void me_play_action(__int64 p, int enemy, int action, const std::string& str_param);
	static int findPlAnmIndex(const char* const* arr, size_t N, const std::string& param);
	static int findSoundIndex(const char* const* arr, size_t N, const std::string& param);
	static uintptr_t me_FindHealthPointer(int characterId, int playerSide);
	static void me_SetPlayerParam(__int64 s, int param2, float value);
	static void me_ChangePlayerParam(__int64 s, int param2, float value);

	static int PUCCI_AWA_COUNT[2];
	static const char* CHARACODE[2];

	typedef __int64(__fastcall* orig_UpgradeVerUnlocker_t)(__int64 a1, unsigned int a2);
	static orig_UpgradeVerUnlocker_t orig_UpgradeVerUnlocker;
	static __int64 __fastcall UpgradeVerUnlocker(__int64 a1, unsigned int a2);
	static __int64 Motion_cancel_function(int* a1);
	static __int64 __fastcall meTest(__int64 a1, __int64 a2);
	static __int64 __fastcall meTest2(__int64 a1, __int64 a2);
	static __int64 __fastcall InitializeEffectHandler_f(__int64 a1);
	static __int64 __fastcall CancelActionFunction(__int64 a1, __int64 a2);
	static __int64 __fastcall ApplyStatusEffect(__int64 a1, __int64 a2);
	static void __fastcall ccSndBgmCtrl(__int64 a1, int snd)
	{
		__int64 BgmOnFunctionAdressHeader = PatternScan::Scan("45xxxx48xxxxxxxxxxxx66xxxxxxxxxx39xx74xx49xxxx48xxxxxx49xxxxxx7Cxx33xxC3B8xxxxxxxxC3");
		typedef void(__fastcall* funct)(__int64 a1, int snd);
		funct fc = (funct)(BgmOnFunctionAdressHeader);
		return fc(a1, snd);
	}
	static int BGM_ID;
	static int STAGE_ID;
	static int stage_switcher;

	typedef __int64(__fastcall* orig_sub_14084E110_S4_t)(__int64* a1, int a2);
	//    (  cpp)
	static orig_sub_14084E110_S4_t orig_sub_14084E110_S4;
	static __int64 __fastcall Hooked_sub_14084E110_S4(__int64* a1, int a2);


};

#endif
