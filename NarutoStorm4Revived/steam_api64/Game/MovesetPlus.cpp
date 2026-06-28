#include "MovesetPlus.h"
#include <iostream>
#include <vector>

#include <WinSock2.h>
#include <windows.h>
#include <future>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <format>
#include <cctype>

#include "Common.h"
#include "PlAnmList.h"
#include "Offsets.h"
#include "PatternScan.h"

#include <cmath> // For fabs (absolute value for floats)
#include <cstdint>
#include <thread>
#include <chrono>
#include "mem.h"
#include "Utilities.h"
#include "Console.h"
#include "CommonRender.h"
using namespace std;


#define CHECK_BIT(var,pos) (((var)>>(pos)) & 1)
int prevFrame = 0;
int prevBattle = 0;

void me_EnemyDispOff(__int64 p);
void me_EnemyDispOn(__int64 p);
void me_PlayBGM(int snd);
void me_PucciAwakeFunc(__int64 player_ptr, int side, int count, int action, const std::string& str_param);
void me_test_switch_stage(__int64 function_param, __int64 a2, char* string_param, __int64 a1);
void me_character_param(__int64 p, const std::string& str_param, int param2);
void me_change_skill(__int64 p, int jutsu, int index);
void me_change_speed(__int64 p, int enemy, float speed);
void me_change_speed_timed(__int64 char_p, int enemy, float speed, int duration_ms);
void me_play_blur(__int64 p);
void me_change_fov(__int64 p, float fov);
void me_change_walk_speed(__int64 p, float speed);
void me_change_jump_height(__int64 p, float jump_h);
void me_SetPlayerVisibility(__int64 p, int cansee);
void me_enable_dpad_animation(__int64 a1, int param2);
void me_enable_control(__int64 a1, int enemy, int control);
void me_disable_control(__int64 a1, int enemy, int control);
void me_change_dpad_charge(__int64 a1, int enemy, int arrow, float charge);
void me_change_control_timed(__int64 a1, int enemy, int control, float time);
void me_play_gray(__int64 p, bool enable, int mode, float opacity, const std::string& color);
void me_play_movie(int param2);
void me_play_IA(const std::string& str_param);
void me_play_scene(int param2);
void me_control_timer(__int64 p, float speed);
void me_play_face_anm(__int64 p, int enemy, const std::string& str_param);
void me_play_face_anm_timed(__int64 p, int enemy, int duration_ms, const std::string& str_param);
void me_play_screen_effect(__int64 a1);
void me_change_camera_algorithm();
void me_play_voice_string(__int64 p, int enemy, const std::string& str_param);
void me_play_pl_anm(__int64 p, int enemy, const std::string& str_param);
int MovesetPlus::cancelUpgradeFunctionState[2] = { 0, 0 };
__int64 MovesetPlus::sub_14097F1E0Adress = 0;
__int64 MovesetPlus::sub_1405C7EC0Adress = 0;
__int64 MovesetPlus::sub_1405C3970Adress = 0;
__int64 MovesetPlus::sub_140978B00Adress = 0;
__int64 MovesetPlus::sub_1405C8F00Adress = 0;
int MovesetPlus::PUCCI_AWA_COUNT[2] = { 0, 0};
const char* MovesetPlus::CHARACODE[2] = {"DUMMY", "DUMMY"};
MovesetPlus::orig_sub_14084E110_S4_t MovesetPlus::orig_sub_14084E110_S4 = nullptr;
// Перегрузка, если массив превратился в указатель — нужно передать длину явно
int MovesetPlus::findPlAnmIndex(const char* const* arr, size_t N, const std::string& param) {
	if (param.empty()) return -1;
	auto to_upper = [](std::string s) {
		for (char& c : s) c = (char)std::toupper(static_cast<unsigned char>(c));
		return s;
		};
	std::string p = to_upper(param);
	std::string candFull = "PL_ANM_" + p;

	for (size_t i = 0; i < N; ++i) {
		if (!arr[i]) continue;
		std::string entryU = to_upper(arr[i]);
		if (entryU == candFull || entryU == p) return static_cast<int>(i);
	}
	for (size_t i = 0; i < N; ++i) {
		if (!arr[i]) continue;
		std::string entryU = to_upper(arr[i]);
		if (entryU.size() >= p.size() && entryU.compare(entryU.size() - p.size(), p.size(), p) == 0) return static_cast<int>(i);
		if (entryU.find(p) != std::string::npos) return static_cast<int>(i);
	}
	return -1;
}


int MovesetPlus::findSoundIndex(const char* const* arr, size_t N, const std::string& param) {
	if (param.empty()) return 0;
	auto to_upper = [](std::string s) {
		for (char& c : s) c = (char)std::toupper(static_cast<unsigned char>(c));
		return s;
		};
	std::string p = to_upper(param);
	std::string candFull = p;

	for (size_t i = 0; i < N; ++i) {
		if (!arr[i]) continue;
		std::string entryU = to_upper(arr[i]);
		if (entryU == candFull || entryU == p) return static_cast<int>(i);
	}
	for (size_t i = 0; i < N; ++i) {
		if (!arr[i]) continue;
		std::string entryU = to_upper(arr[i]);
		if (entryU.size() >= p.size() && entryU.compare(entryU.size() - p.size(), p.size(), p) == 0) return static_cast<int>(i);
		if (entryU.find(p) != std::string::npos) return static_cast<int>(i);
	}
	return 0;
}



__int64 __fastcall MovesetPlus::meTest(__int64 a1, __int64 a2)
{
	int character = *((int*)(a1 + 0xE64));
	int characterSide = *((int*)(a1 + 0xE60));
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		int character = *((int*)(a1 + 0xE64));
		int characterSide = *((int*)(a1 + 0xE60));
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		int character = *((int*)(a1 + 0xC8C));
		int characterSide = *((int*)(a1 + 0xC88));
	}


	short param1 = *((short*)(a2 + 0x24));
	short param2 = *((short*)(a2 + 0x26));
	short param3 = *((short*)(a2 + 0x28));
	float param4 = *((float*)(a2 + 0x2C));
	int string_param_integer = *((int*)(a2));

	char string_param[31] = { 0 }; // Allocate 31 to include null terminator
	std::strncpy(string_param, reinterpret_cast<const char*>(a2), 30);
	string_param[30] = '\0'; // Ensure null termination

	__int64 enemy_pointer;



	enemy_pointer = BattleUtils::GetEnemyPointer(a1);

	switch (param1)
	{
	default:
		me_EnemyDispOff(a1);
		break;
	case 1:
		me_PlayBGM(param2);
		break;
	case 2:
		me_test_switch_stage(a2, param2, string_param, a1);
		break;
	case 3:
		me_change_skill(a1, param2, param3);
		break;
	case 4:
		me_change_speed(a1, param2, param4);
		break;
	case 5:
		me_change_speed_timed(a1, param2, param4, param3 * (1000 / 30));
		break;
	case 6:
		me_play_blur(a1);
		break;
	case 7:
		me_change_fov(a1, param4);
		break;
	case 8:
		me_change_walk_speed(a1, param4);
		break;
	case 9:
		me_change_jump_height(a1, param4);
		break;
	case 10:
		MovesetPlus::me_SetPlayerParam(MovesetPlus::me_FindHealthPointer(param3, characterSide), param2, param4);
		break;
	case 11:
		MovesetPlus::me_ChangePlayerParam(MovesetPlus::me_FindHealthPointer(param3, characterSide), param2, param4);
		break;
	case 12:
		me_SetPlayerVisibility(a1, param2);
		break;
	case 13:
		me_enable_dpad_animation(a1, param2);
		break;
	case 14:
		me_enable_control(a1, param2, param3);
		break;
	case 15:
		me_disable_control(a1, param2, param3);
		break;
	case 16:
		me_change_control_timed(a1, param2, param3, param4);
		break;
	case 17:
		me_change_dpad_charge(a1, param2, param3, param4);
		break;
	case 18: {
		me_play_gray(a1, param2, param3, param4, string_param);
		break;
	}
	case 19: {
		MovesetPlus::me_hud_control(param2);
		break;
	}
	case 20:
		me_play_IA(string_param);
		break;
	case 21:
		me_change_camera_algorithm();
		break;
	case 22:
		me_play_pl_anm(a1, param2, string_param);
		break;
	case 23:
		MovesetPlus::me_play_action(a1, param2, param3, string_param);
		break;

	case 24:
		me_play_face_anm(a1, param2, string_param);
		break;

	case 25:
		me_play_face_anm_timed(a1, param2, param3 * (1000 / 30), string_param);
		break;
	case 26:
		me_play_voice_string(a1, param2, string_param);
		break;
	/*case 26:
		me_control_timer(a1, param4);
		break;*/
	/*case 21:
		me_play_movie(param2);
		break;*/
	/*case 22:
		me_play_scene(param2);
		break;*/
	}



	return 1;
}
void me_play_voice_string(__int64 p, int enemy, const std::string& str_param) {
	__int64 player_ptr = p;

	if (enemy == 1) {
		player_ptr = BattleUtils::GetEnemyPointer(p);
	}
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		int sound_index = MovesetPlus::findSoundIndex(gameList.NSC_SFX_List, 160, str_param);

		(*(void(__fastcall**)(__int64, __int64, __int64))(*(__int64*)player_ptr + 4112i64))(
			player_ptr,
			(unsigned int)(sound_index+ 0x7000),
			0i64);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		int sound_index = MovesetPlus::findSoundIndex(gameList.NS4_SFX_List, 168, str_param);
		(*(void(__fastcall**)(__int64, __int64))(*(__int64*)player_ptr + 4000i64))(
			player_ptr,
			(unsigned int)(sound_index + 0x4000));
	}
}
void me_play_screen_effect(__int64 a1) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		typedef __int64(__fastcall* funct_sub_140AD3AE0)(__int64 a1, __int64 a2);
		funct_sub_140AD3AE0 sub_140AD3AE0 = (funct_sub_140AD3AE0)(moduleBase + 0xAD2EE0);
		*(__int64*)(a1 + 0x12D30) = 1;
		*(__int64*)(a1 + 0x12D40) = sub_140AD3AE0((__int64)"data/spc/Pucci/6pci02eff1.xfbin", (__int64)"6pci02_eff_ghh1_illusion00");
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		typedef __int64(__fastcall* funct_sub_140AD3AE0)(__int64 a1, __int64 a2);
		funct_sub_140AD3AE0 sub_140AD3AE0 = (funct_sub_140AD3AE0)(moduleBase + 0x8639E8);
		*(__int64*)(a1 + 0x15750) = 1;
		*(__int64*)(a1 + 0x15760) = sub_140AD3AE0((__int64)"data/spc/Pucci/6pci02eff1.xfbin", (__int64)"6pci02_eff_ghh1_illusion00");
	}
	
}
void me_play_screen_effect_test(__int64 a1) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		typedef __int64(__fastcall* funct_sub_140AD3AE0)(__int64 a1, __int64 a2);
		funct_sub_140AD3AE0 sub_140AD3AE0 = (funct_sub_140AD3AE0)(moduleBase + 0xAD2EE0);
		*(__int64*)(a1 + 0x12D30) = 1;
		*(__int64*)(a1 + 0x12D40) = sub_140AD3AE0((__int64)"data/spc/Pucci/6pci02eff1.xfbin", (__int64)"6pci02_eff_ghh1_illusion01");
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		typedef __int64(__fastcall* funct_sub_140AD3AE0)(__int64 a1, __int64 a2);
		funct_sub_140AD3AE0 sub_140AD3AE0 = (funct_sub_140AD3AE0)(moduleBase + 0x8639E8);
		*(__int64*)(a1 + 0x15750) = 1;
		*(__int64*)(a1 + 0x15760) = sub_140AD3AE0((__int64)"data/spc/Pucci/6pci02eff1.xfbin", (__int64)"6pci02_eff_ghh1_illusion01");
	}

}
void me_disable_screen_effect(__int64 a1) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		*(__int64*)(a1 + 0x12D30) = 0;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		*(__int64*)(a1 + 0x15750) = 0;
	}

}
void me_play_face_anm(__int64 p, int enemy, const std::string& str_param) {
	__int64 player_ptr = p;

	if (enemy == 1) {
		player_ptr = BattleUtils::GetEnemyPointer(p);
	}

	// 2) Или (в случае, если std::size недоступна) — явно:
	int pl_anm_id = MovesetPlus::findPlAnmIndex(gameList.PlAnmList, 1009, str_param);
	if (pl_anm_id < 0) {
		pl_anm_id = 112; // fallback по умолчанию (ваше текущее значение)
	}


	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


		typedef __int64(__fastcall* funct_ns2_ccPlayer_GetAnmChunk)(__int64 a1, unsigned int a2, __int64 a3);
		funct_ns2_ccPlayer_GetAnmChunk ns2_ccPlayer_GetAnmChunk = (funct_ns2_ccPlayer_GetAnmChunk)(moduleBase + 0x98E910);

		typedef __int64(__fastcall* funct_ns2_ccGameObjSubDraw_SetFaceAnm)(__int64 a1, __int64 a2);
		funct_ns2_ccGameObjSubDraw_SetFaceAnm ns2_ccGameObjSubDraw_SetFaceAnm = (funct_ns2_ccGameObjSubDraw_SetFaceAnm)(moduleBase + 0x5F2E30);

		__int64 AnmChunk = ns2_ccPlayer_GetAnmChunk(player_ptr, pl_anm_id, 1i64);
		if (AnmChunk || (ns2_ccPlayer_GetAnmChunk(player_ptr, pl_anm_id, 1i64)) != 0)
			ns2_ccGameObjSubDraw_SetFaceAnm(*(__int64*)(player_ptr + 520), AnmChunk);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		typedef __int64(__fastcall* funct_ns2_ccPlayer_GetAnmChunk)(__int64 a1, unsigned int a2, __int64 a3);
		funct_ns2_ccPlayer_GetAnmChunk ns2_ccPlayer_GetAnmChunk = (funct_ns2_ccPlayer_GetAnmChunk)(moduleBase + 0x77CE68);

		typedef __int64(__fastcall* funct_ns2_ccGameObjSubDraw_SetFaceAnm)(__int64 a1, __int64 a2);
		funct_ns2_ccGameObjSubDraw_SetFaceAnm ns2_ccGameObjSubDraw_SetFaceAnm = (funct_ns2_ccGameObjSubDraw_SetFaceAnm)(moduleBase + 0x55927C);

		__int64 AnmChunk = ns2_ccPlayer_GetAnmChunk(player_ptr, pl_anm_id, 1i64);
		if (AnmChunk || (ns2_ccPlayer_GetAnmChunk(player_ptr, pl_anm_id, 1i64)) != 0)
			ns2_ccGameObjSubDraw_SetFaceAnm(*(__int64*)(player_ptr + 520), AnmChunk);
	}
}
void me_play_face_anm_timed(__int64 p, int enemy, int duration_ms, const std::string& str_param) {
	me_play_face_anm(p, enemy, str_param);

	// Запустить поток, который через duration_ms восстановит id = 112
	std::thread([=]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));

		me_play_face_anm(p, enemy, "FACE_NUT");
		}).detach();
}


void me_play_pl_anm(__int64 p, int enemy, const std::string& str_param) {
	__int64 player_ptr = p;
	if (enemy == 1) {
		player_ptr = BattleUtils::GetEnemyPointer(p);
	}

	if (!player_ptr) return; // null check

	int pl_anm_id = MovesetPlus::findPlAnmIndex(gameList.PlAnmList, 1009, str_param);
	Console::PrintErr("String Param: %s, index=%d", str_param.c_str(), pl_anm_id);

	if (pl_anm_id > -1) {
		ccPlayer::SetAnmDirect((ccPlayer*)player_ptr, pl_anm_id);
	}
}
void MovesetPlus::me_play_action(__int64 p, int enemy, int action, const std::string& str_param) {
	__int64 player_ptr = p;
	if (enemy == 1) {
		player_ptr = BattleUtils::GetEnemyPointer(p);
	}

	ccPlayer::SetActionImmediate((ccPlayer*)player_ptr, action);
	me_play_pl_anm(p, enemy, str_param);

}

void me_control_timer(__int64 p, float speed) {
	render::timer_speed = speed;

}
__int64 __fastcall MovesetPlus::meTest2(__int64 a1, __int64 a2)
{
	int character = 0;
	int characterSide = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		character = *((int*)(a1 + 0xE64));
		characterSide = *((int*)(a1 + 0xE60));
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		character = *((int*)(a1 + 0xC8C));
		characterSide = *((int*)(a1 + 0xC88));
	}


	short param1 = *((short*)(a2 + 0x24));
	short param2 = *((short*)(a2 + 0x26));
	short param3 = *((short*)(a2 + 0x28));
	float param4 = *((float*)(a2 + 0x2C));
	int string_param_integer = *((int*)(a2));

	char string_param[31] = { 0 }; // Allocate 31 to include null terminator
	std::strncpy(string_param, reinterpret_cast<const char*>(a2), 30);
	string_param[30] = '\0'; // Ensure null termination

	__int64 enemy_pointer;
	enemy_pointer = BattleUtils::GetEnemyPointer(a1);

	switch (param1)
	{
	default:
		me_EnemyDispOn(a1);
		break;
	case 1:
		me_PucciAwakeFunc(a1, characterSide, param2, param3, string_param);
		break;
	case 2:
		me_play_screen_effect(a1);
		break;
	case 3:
		me_play_screen_effect_test(a1);
		break;
	case 4:
		me_disable_screen_effect(a1);
		break;
	}



	return 1;
}



void me_PucciAwakeFunc(__int64 player_ptr, int side, int count, int action, const std::string& str_param) {

	//play voice line

	if (MovesetPlus::PUCCI_AWA_COUNT[side] < 14) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			int characterSide = *((int*)(player_ptr + 0xE60));
			if (MovesetPlus::PUCCI_AWA_COUNT[characterSide] == 13) {
				__int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
				float player_chakra = *(float*)(gauge_pointer + 0x08);
				if (player_chakra > 34.0f) {
					MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -33.0f);
					MovesetPlus::PUCCI_AWA_COUNT[characterSide] += 1;
					//ccPlayer::SetActionImmediate((ccPlayer*)player_ptr, action);

					ccPlayer::SetAnmDirect((ccPlayer*)player_ptr, action);
				}
			}
			else {
				__int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
				float player_chakra = *(float*)(gauge_pointer + 0x08);
				if (player_chakra > 34.0f) {
					MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -33.0f);
					MovesetPlus::PUCCI_AWA_COUNT[characterSide] += 1;
					me_play_face_anm_timed(player_ptr, 0, 25 * (1000 / 30), "FACE_SPEAK");
					me_play_voice_string(player_ptr, 0, str_param);



					//(*(void(__fastcall**)(__int64, __int64, __int64))(*(__int64*)player_ptr + 4112i64))(
					//	player_ptr,
					//	(unsigned int)(count/* + MovesetPlus::PUCCI_AWA_COUNT[side]*/ + 0x7000),
					//	0i64);
				}
				
			}

		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			int characterSide = *((int*)(player_ptr + 0xC88));
			if (MovesetPlus::PUCCI_AWA_COUNT[characterSide] == 13) {

				__int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
				float player_chakra = *(float*)(gauge_pointer + 0x08);
				if (player_chakra > 34.0f) {
					MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -30.0f);
					MovesetPlus::PUCCI_AWA_COUNT[characterSide] += 1;
					ccPlayer::SetAnmDirect((ccPlayer*)player_ptr, action);
				}
			}
			else {
				__int64 gauge_pointer = MovesetPlus::me_FindHealthPointer(0, characterSide);
				float player_chakra = *(float*)(gauge_pointer + 0x08);
				if (player_chakra > 34.0f) {

					MovesetPlus::me_ChangePlayerParam(gauge_pointer, 2, -30.0f);
					
					MovesetPlus::PUCCI_AWA_COUNT[characterSide] += 1;
					me_play_face_anm_timed(player_ptr, 0, 25 * (1000 / 30), "FACE_SPEAK");
					me_play_voice_string(player_ptr, 0, str_param);


					//(*(void(__fastcall**)(__int64, __int64))(*(__int64*)player_ptr + 4000i64))(
					//	player_ptr,
					//	(unsigned int)(count/* + MovesetPlus::PUCCI_AWA_COUNT[side]*/ + 0x4000));
				}
			}
		}

	}
	
}

MovesetPlus::orig_ME_CAMERA_LOOKAT_SET_t MovesetPlus::orig_ME_CAMERA_LOOKAT_SET = nullptr;
__int64 __fastcall MovesetPlus::ME_CAMERA_LOOKAT_SET(__int64 a1, char* a2)
{
	size_t v2; // r8

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		typedef __int64*(__fastcall* funct_sub_1400B1B00)(__int64* a1, const void* a2, size_t a3);
		funct_sub_1400B1B00 sub_1400B1B00 = (funct_sub_1400B1B00)(moduleBase + 0xB0F00);
		v2 = -1i64;
		do
			++v2;
		while (a2[v2]);
		sub_1400B1B00((__int64*)(a1 + 0xC7C0), a2, v2);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		typedef __int64* (__fastcall* funct_sub_1401CB71C)(__int64* a1, const void* a2, size_t a3);
		funct_sub_1401CB71C sub_1401CB71C = (funct_sub_1401CB71C)(moduleBase + 0x1CAB1C);
		v2 = -1i64;
		do
			++v2;
		while (a2[v2]);
		sub_1401CB71C((__int64*)(a1 + 0xFCD8), a2, v2);
	}

	return 1i64;
}

MovesetPlus::orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2_t MovesetPlus::orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2 = nullptr;
__int64 __fastcall MovesetPlus::ME_CAMERA_LOOKAT_SET_HUGEAWAKE2(__int64 a1, char* a2)
{
	size_t v2; // r8

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		typedef __int64* (__fastcall* funct_sub_1400B1B00)(__int64* a1, const void* a2, size_t a3);
		funct_sub_1400B1B00 sub_1400B1B00 = (funct_sub_1400B1B00)(moduleBase + 0xB0F00);
		v2 = -1i64;
		do
			++v2;
		while (a2[v2]);
		sub_1400B1B00((__int64*)(a1 + 0xC7F8), a2, v2);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

		typedef __int64* (__fastcall* funct_sub_1401CB71C)(__int64* a1, const void* a2, size_t a3);
		funct_sub_1401CB71C sub_1401CB71C = (funct_sub_1401CB71C)(moduleBase + 0x1CAB1C);
		v2 = -1i64;
		do
			++v2;
		while (a2[v2]);
		sub_1401CB71C((__int64*)(a1 + 0xFD10), a2, v2);
	}

	return 1i64;
}

void MovesetPlus::me_hud_control(int mode)
{
	// ── Re-entry / spam guard ──────────────────────────────────
	static std::atomic<bool> s_busy{ false };
	if (s_busy.exchange(true)) return;
	auto guard = std::shared_ptr<void>(nullptr, [](void*) { s_busy.store(false); });

	// ── Determine desired transition ───────────────────────────
	const bool wantDisable = (render::hudon == 2 && mode == 0) || (mode == 1 && render::hudon != 1);
	const bool wantEnable = (render::hudon == 1 && mode == 0) || (mode == 2 && render::hudon != 2);

	if (!wantDisable && !wantEnable) return;
	if (!GameVersion) return;

	const bool isV160 = std::strcmp(GameVersion, "1.60") == 0;
	const bool isV109 = std::strcmp(GameVersion, "1.09") == 0;
	if (!isV160 && !isV109) return;

	// ── Safe pointer read helpers ──────────────────────────────
	// IsBadReadPtr checks the page is mapped and readable before we touch it,
	// avoiding access violations on dangling/mid-transition game pointers.
	auto safeRead64 = [](const void* addr) -> __int64 {
		if (IsBadReadPtr(addr, sizeof(__int64))) return 0;
		return *reinterpret_cast<const __int64*>(addr);
		};

	// ── Typedefs ───────────────────────────────────────────────
	using Fn_t = __int64(__fastcall*)(void*);
	using FnPtrArray = Fn_t*;
	using TripleFn = FnPtrArray*;
	using SceneLookup = TripleFn(__fastcall*)(__int64, __int64);
	using HudToggleFn = void(__fastcall*)(__int64);

	// ── Resolve highPart ───────────────────────────────────────
	const uintptr_t xmmOffset = isV160 ? offsetSC::VTableXmmwordOffset
		: offsetS4::VTableXmmwordOffset;
	auto* pXmmword = reinterpret_cast<__int64*>(moduleBase + xmmOffset - 0xC00);
	__int64 highPart = safeRead64(pXmmword + 1);
	if (!highPart) return;

	// ── Shared v2 -> v3 -> v4 pointer chain ───────────────────
	auto resolveV4 = [&]() -> __int64 {
		auto sceneLookup = reinterpret_cast<SceneLookup>(MovesetPlus::VTableAddress);
		TripleFn v2 = sceneLookup(highPart, reinterpret_cast<__int64>("scene_battle"));
		if (IsBadReadPtr(v2, sizeof(FnPtrArray) * 2)) return 0;
		FnPtrArray v3 = v2[1];
		if (IsBadReadPtr(v3, 24)) return 0;
		return safeRead64(reinterpret_cast<char*>(v3) + 16);
		};

	// ── HUD DISABLE ────────────────────────────────────────────
	if (wantDisable)
	{
		if (isV160)
		{
			using SceneLookup160 = __int64(__fastcall*)(__int64, __int64);
			using Sub_1404BF150_t = __int64(__fastcall*)(__int64);
			using Sub_14086C080_t = __int64(__fastcall*)(__int64);

			auto sceneLookup160 = reinterpret_cast<SceneLookup160>(MovesetPlus::VTableAddress);
			auto sub_1404BF150 = reinterpret_cast<Sub_1404BF150_t>(moduleBase + 0x4BE550);
			auto sub_14086C080 = reinterpret_cast<Sub_14086C080_t>(moduleBase + 0x86B480);

			__int64 v14 = sceneLookup160(highPart, reinterpret_cast<__int64>("scene_battle"));
			if (!v14) return;
			__int64 battleUI = sub_1404BF150(v14);
			if (!battleUI) return;
			if (safeRead64(reinterpret_cast<void*>(battleUI + 552)))
				sub_14086C080(battleUI);
		}
		else // v1.09
		{
			using Sub_1406D9230_t = __int64(__fastcall*)(__int64);
			auto sub_1406D9230 = reinterpret_cast<Sub_1406D9230_t>(moduleBase + 0x6D8630);
			__int64 v4 = resolveV4();
			if (v4) sub_1406D9230(v4);
		}

		render::hudon = 1;
		return;
	}

	// ── HUD ENABLE ─────────────────────────────────────────────
	if (wantEnable)
	{
		const uintptr_t fnOffset = isV160 ? 0x86B4A0 : 0x6D864C;
		auto sub_HudShow = reinterpret_cast<HudToggleFn>(moduleBase + fnOffset);
		__int64 v4 = resolveV4();
		if (v4) sub_HudShow(v4);

		render::hudon = 2;
	}
}


void me_play_gray(__int64 p, bool enable, int mode, float opacity, const std::string& color)
{
	ColorConvertSettings colorConverter;

	static const bool calib_swap_xy = true;
	static const bool calib_invert_x = false;
	static const bool calib_invert_y = true;
	static const float calib_hue_offset_deg = 25.0f;
	static const float calib_sat_scale = 1.0f;
	static const float calib_val_scale = 1.0f; // kept for clarity but NOT used for preview/HSV value
	colorConverter.enable = enable;
	colorConverter.mode = mode;
	colorConverter.opacity = opacity;

	// parse decimal string (decimal representation of hex RGB) to uint32
	uint32_t val = 0;
	try {
		val = static_cast<uint32_t>(std::stoul(color)); // assumes decimal string like "16711680"
	}
	catch (...) {
		val = 0;
	}

	// extract RGB (0..255) -> normalize to 0..1
	float r = static_cast<float>((val >> 16) & 0xFF) / 255.0f;
	float g = static_cast<float>((val >> 8) & 0xFF) / 255.0f;
	float b = static_cast<float>((val >> 0) & 0xFF) / 255.0f;

	// helper clamp
	auto clampf = [](float v, float lo, float hi) -> float {
		return (v < lo) ? lo : (v > hi) ? hi : v;
		};

	// ====== RGB -> HSV (provided) ======
	float h = 0.0f, s = 0.0f, v = 0.0f;
	{
		float maxc = fmaxf(r, fmaxf(g, b));
		float minc = fminf(r, fminf(g, b));
		v = maxc;
		float delta = maxc - minc;
		if (maxc == 0.0f) { s = 0.0f; h = 0.0f; }
		else {
			s = delta / maxc;
			if (delta == 0.0f) { h = 0.0f; }
			else {
				if (maxc == r) h = (g - b) / delta;
				else if (maxc == g) h = 2.0f + (b - r) / delta;
				else h = 4.0f + (r - g) / delta;
				h /= 6.0f;
				if (h < 0.0f) h += 1.0f;
			}
		}
	}

	// ====== ColorBR_FromHSV (uses calibration globals assumed in scope) ======
	float out_x = 0.0f, out_y = 0.0f;
	{
		const float TWO_PI = 6.28318530717958647692f;
		// calib_* variables are expected to exist in your codebase:
		// float calib_hue_offset_deg;
		// float calib_sat_scale;
		// bool calib_swap_xy;
		// bool calib_invert_x;
		// bool calib_invert_y;
		float h_shifted = h + (calib_hue_offset_deg / 360.0f);
		if (h_shifted >= 1.0f) h_shifted -= floorf(h_shifted);
		if (h_shifted < 0.0f) h_shifted += ceilf(-h_shifted);

		float length = s / (2.0f * calib_sat_scale);
		length = clampf(length, 0.0f, 0.5f);

		float angle = (h_shifted - 0.5f) * TWO_PI;
		float lx = cosf(angle) * length;
		float ly = sinf(angle) * length;

		float rx = lx, ry = ly;
		if (calib_swap_xy) std::swap(rx, ry);
		if (calib_invert_x) rx = -rx;
		if (calib_invert_y) ry = -ry;

		out_x = clampf(rx, -0.5f, 0.5f);
		out_y = clampf(ry, -0.5f, 0.5f);
	}

	// set ColorBR values
	colorConverter.ColorBR.x = out_x;
	colorConverter.ColorBR.y = out_y;

	// write settings
	__int64 cfptr = Game::ObjectList_GetPtrLightsAndFog();
	ColorConvertSettings::SetSettings(cfptr, &colorConverter);
}


void me_EnemyDispOff(__int64 a1)
{
	__int64 v1; // rax  
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)a1 + 3512i64))(a1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 3000i64))(v1);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)a1 + 3464i64))(a1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 2968i64))(v1);
	}
	


}
void me_EnemyDispOn(__int64 a1)
{
	__int64 v1; // rax  
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)a1 + 3512i64))(a1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 2992i64))(v1);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		v1 = (*(__int64(__fastcall**)(__int64))(*(__int64*)a1 + 3464i64))(a1);
		if (v1)
			(*(void(__fastcall**)(__int64))(*(__int64*)v1 + 2960i64))(v1);
	}



}
void me_enable_dpad_animation(__int64 a1, int param2) {

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		

		*(int*)(a1 + 0xF30) = param2;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		


		*(int*)(a1 + 0xD38) = param2;
	}

	

}


uintptr_t MovesetPlus::me_FindHealthPointer(int characterId, int playerSide)
{
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {



		// base address used in original code (moduleBase + 0x0219D808)
		constexpr uintptr_t basePointerOffset = 0x0219D818;

		// Выбираем firstOffset и fourthOffset в зависимости от playerSide и characterId
		uint32_t Offset_1 = 0x60;
		uint32_t Offset_2 = 0x08;
		uint32_t Offset_3 = 0;
		uint32_t Offset_4 = 0;
		uint32_t Offset_5 = 0x08;
		uint32_t Offset_6 = 0;
		uint32_t Offset_7 = 0x38;

		if (playerSide == 0) { // left
			Offset_3 = (characterId == 0) ? 0x8u : 0x0u;
			Offset_4 = (characterId == 0) ? 0x0u : 0x8u;
			Offset_6 = (characterId == 0) ? 0x0u : 0x80u;
		}
		else if (playerSide == 1) { // right
			Offset_3 = (characterId == 0) ? 0x0u : 0x8u;
			Offset_4 = (characterId == 0) ? 0x8u : 0x0u;
			Offset_6 = (characterId == 0) ? 0x80u : 0x0u;
		}
		else {
			std::cerr << "Invalid playerSide. Use 0 or 1." << std::endl;
			return 0;
		}

		// Собираем вектор смещений такой же, как в ручной цепочке: first, 0xB8, 0xC0, fourth, 0x38
		std::vector<uint32_t> chain = { Offset_1, Offset_2,Offset_3,Offset_4,Offset_5,Offset_6,Offset_7};
		// Попробовать ResolvePointerChainBase (вернёт базовый адрес блока float'ов, если удачно)
		uintptr_t resolved = Offset::ResolvePointerChainBase(moduleBase, basePointerOffset, chain);
		if (resolved != 0) {
			// resolved указывает на блок float'ов (вместо p6) — вернуть его как указатель на здоровье
			std::cout << "Health Pointer for character on side " << playerSide
				<< ": 0x" << std::hex << resolved << std::dec << std::endl;
			return resolved;
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {



		// base address used in original code (moduleBase + 0x0219D808)
		constexpr uintptr_t basePointerOffset = 0x0161C8B8;

		// Выбираем firstOffset и fourthOffset в зависимости от playerSide и characterId
		uint32_t Offset_1 = 0x40;
		uint32_t Offset_2 = 0;
		uint32_t Offset_3 = 0;
		uint32_t Offset_4 = 0;
		uint32_t Offset_5 = 0;
		uint32_t Offset_6 = 0;
		uint32_t Offset_7 = 0x38;

		if (playerSide == 0) { // left
			Offset_2 = (characterId == 0) ? 0x40u : 0x48u;
			Offset_3 = (characterId == 0) ? 0x60u : 0x0u;
			Offset_4 = (characterId == 0) ? 0x10u : 0x0u;
			Offset_5 = (characterId == 0) ? 0x8u : 0x60u;
			Offset_6 = (characterId == 0) ? 0x0u : 0x90u;
		}
		else if (playerSide == 1) { // right
			Offset_2 = (characterId == 0) ? 0x48u : 0x40u;
			Offset_3 = (characterId == 0) ? 0x0u : 0x60u;
			Offset_4 = (characterId == 0) ? 0x0u : 0x10u;
			Offset_5 = (characterId == 0) ? 0x60u : 0x8u;
			Offset_6 = (characterId == 0) ? 0x90u : 0x0u;
		}
		else {
			std::cerr << "Invalid playerSide. Use 0 or 1." << std::endl;
			return 0;
		}

		// Собираем вектор смещений такой же, как в ручной цепочке: first, 0xB8, 0xC0, fourth, 0x38
		std::vector<uint32_t> chain = { Offset_1, Offset_2,Offset_3,Offset_4,Offset_5,Offset_6,Offset_7 };
		// Попробовать ResolvePointerChainBase (вернёт базовый адрес блока float'ов, если удачно)
		uintptr_t resolved = Offset::ResolvePointerChainBase(moduleBase, basePointerOffset, chain);
		if (resolved != 0) {
			// resolved указывает на блок float'ов (вместо p6) — вернуть его как указатель на здоровье
			std::cout << "Health Pointer for character on side " << playerSide
				<< ": 0x" << std::hex << resolved << std::dec << std::endl;
			return resolved;
		}
	}
	

}



void me_change_dpad_charge(__int64 char_p, int enemy, int arrow, float charge)
{
	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 0x12B88;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 0x15688;
	}
	__int64 pointer;
	if (enemy == 0)
		pointer = char_p;
	else
		pointer = BattleUtils::GetEnemyPointer(char_p);

	switch (arrow) {
	case 0://All Arrow
		*(float*)(pointer + offset) = charge; //Up Arrow
		*(float*)(pointer + offset+4) = charge; //Down Arrow
		*(float*)(pointer + offset + 8) = charge; //Left Arrow
		*(float*)(pointer + offset + 12) = charge; //Right Arrow
		break;
	case 1:
		*(float*)(pointer + offset) = charge; //Up Arrow
		break;
	case 2:
		*(float*)(pointer + offset + 4) = charge; //Down Arrow
		break;
	case 3:
		*(float*)(pointer + offset + 8) = charge; //Left Arrow
		break;
	case 4:
		*(float*)(pointer + offset + 12) = charge; //Right Arrow
		break;
	}
}


void me_SetPlayerVisibility(__int64 p, int cancel)
{


	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		int* visible = (int*)(p + 0xE9C);
		*visible = cancel;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		int* visible = (int*)(p + 0xCB8);
		*visible = cancel;
	}
	
}

void MovesetPlus::me_SetPlayerParam(__int64 s, int param2, float value)
{
	switch (param2)
	{
	case 0: // health
		*(float*)(s + 0x00) = (value > *(float*)(s + 0x04)) ? *(float*)(s + 0x04) : value;
		break;

	case 1: // maxhealth
		*(float*)(s + 0x04) = value;
		*(float*)(s + 0x00) = min(*(float*)(s + 0x00), value);
		break;

	case 2: // chakra
		*(float*)(s + 0x08) = (value > *(float*)(s + 0x0C)) ? *(float*)(s + 0x0C) : value;
		break;

	case 3: // maxchakra
		*(float*)(s + 0x0C) = value;
		*(float*)(s + 0x08) = min(*(float*)(s + 0x08), value);
		break;

	case 4: // sub
		*(float*)(s + 0x10) = (value > *(float*)(s + 0x14)) ? *(float*)(s + 0x14) : value;
		break;

	case 5: // maxsub
		*(float*)(s + 0x14) = value;
		*(float*)(s + 0x10) = min(*(float*)(s + 0x10), value);
		break;
	}
}

void MovesetPlus::me_ChangePlayerParam(__int64 s, int param2, float value)
{
	switch (param2)
	{
	case 0: // health
		*(float*)(s + 0x00) = min(*(float*)(s + 0x00) + value, *(float*)(s + 0x04));
		break;

	case 1: // maxhealth
		*(float*)(s + 0x04) += value;
		*(float*)(s + 0x00) = min(*(float*)(s + 0x00), *(float*)(s + 0x04));
		break;

	case 2: // chakra
		*(float*)(s + 0x08) = min(*(float*)(s + 0x08) + value, *(float*)(s + 0x0C));
		break;

	case 3: // maxchakra
		*(float*)(s + 0x0C) += value;
		*(float*)(s + 0x08) = min(*(float*)(s + 0x08), *(float*)(s + 0x0C));
		break;

	case 4: // sub
		*(float*)(s + 0x10) = min(*(float*)(s + 0x10) + value, *(float*)(s + 0x14));
		break;

	case 5: // maxsub
		*(float*)(s + 0x14) += value;
		*(float*)(s + 0x10) = min(*(float*)(s + 0x10), *(float*)(s + 0x14));
		break;
	}
}


void me_change_skill(__int64 char_p, int jutsu, int index) {

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		if (index > -1 && index <= 6) {
			if (jutsu == 0) {

				*(int*)(char_p + 0xE78) = index; //Jutsu 1
			}
			else if (jutsu == 1) {

				*(int*)(char_p + 0xE7C) = index; //Jutsu 2
			}
			else if (jutsu == 2) {

				*(int*)(char_p + 0xE80) = index; // Ultimate Jutsu
			}
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		if (index > -1 && index <= 6) {
			if (jutsu == 0) {

				*(int*)(char_p + 0xC98) = index; //Jutsu 1
			}
			else if (jutsu == 2) {

				*(int*)(char_p + 0xC9C) = index; // Ultimate Jutsu
			}
		}
	}
	

}
void me_play_blur(__int64 p) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		*(int*)(p + 0x11998) = 1;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		Console::PrintErr("ME_PLAY_BLUR isn't available in Storm 4 :(");
	}
}
void me_change_fov(__int64 p, float FOV) {

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		if (FOV > 0)
			*(float*)(p + 0x119A0) = FOV;
		else
			*(float*)(p + 0x119A0) = -1;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		if (FOV > 0)
			*(float*)(p + 0x14D08) = FOV;
		else
			*(float*)(p + 0x14D08) = -1;
	}

	

}

void me_change_walk_speed(__int64 p, float speed) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		*(float*)(p + 0x10D44) = speed;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		*(float*)(p + 0x14174) = speed;
	}
}
void me_change_jump_height(__int64 p, float jump_h) {
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		*(float*)(p + 0x10D3C) = jump_h;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		*(float*)(p + 0x1416C) = jump_h;
	}
}
void me_change_speed(__int64 char_p, int enemy, float speed) {
	__int64 enemy_pointer;
	enemy_pointer = BattleUtils::GetEnemyPointer(char_p);
	if (enemy == 0) {

		*(float*)(char_p + 0x214) = speed; //Player
	}
	else if (enemy == 1) {

		*(float*)(enemy_pointer + 0x214) = speed; //Enemy
	}
}

void me_change_speed_timed(__int64 char_p, int enemy, float speed, int duration_ms) {
	__int64 enemy_pointer;

	// Get Enemy Pointer
	enemy_pointer = BattleUtils::GetEnemyPointer(char_p);

	// Save the original speed
	float* target_speed_ptr = (enemy == 0) ? (float*)(char_p + 0x214) : (float*)(enemy_pointer + 0x214);
	float original_speed = *target_speed_ptr;

	// Set the new speed
	*target_speed_ptr = speed;

	// Start a new thread to reset speed after the duration
	std::thread([=]() {
		// Wait for the specified duration
		std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));

		// Reset the speed back to the original value
		*target_speed_ptr = 1.0f;
		}).detach(); // Detach the thread to run independently
}


__int64 MovesetPlus::HandleStageChangeAddress = 0;
__int64 MovesetPlus::DefaultStageHandlerAddress = 0;
__int64 MovesetPlus::SpecificStageHandlerAddress = 0;
__int64 MovesetPlus::FixCharPositionAddress = 0;
__int64 MovesetPlus::VTableAddress = 0;




int MovesetPlus::STAGE_ID;
void me_test_switch_stage(__int64 function_param, __int64 param2, char* string_param, __int64 character_pointer)
{
	typedef signed __int64(__fastcall* Sub_1408EAE00)(unsigned int);
	Sub_1408EAE00 sub_1408EAE00_f = (Sub_1408EAE00)(MovesetPlus::HandleStageChangeAddress);

	typedef signed __int64(__fastcall* Sub_1406F6800)(__int64);
	Sub_1406F6800 sub_1406F6800_f = (Sub_1406F6800)(MovesetPlus::DefaultStageHandlerAddress);

	typedef void(__fastcall* Sub_1406F6830)(__int64, unsigned int);
	Sub_1406F6830 sub_1406F6830_f = (Sub_1406F6830)(MovesetPlus::SpecificStageHandlerAddress);

	typedef void(__fastcall* sub_140643C10)(__int64);
	sub_140643C10 sub_140643C10_f = (sub_140643C10)(MovesetPlus::FixCharPositionAddress);

	//__int64(__fastcall * **__fastcall sub_141086E40(__int64 a1, __int64 a2))(void* Block)
	typedef __int64(__fastcall* BlockFunc)(void* Block);
	typedef BlockFunc* StageMoveVTable;
	typedef StageMoveVTable(__fastcall* Sub_141086E40Type)(__int64, __int64);

	//&xmmword_1422FB990
	__int64* pXmmword;

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetSC::VTableXmmwordOffset - 0xC00);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		pXmmword = reinterpret_cast<__int64*>(moduleBase + offsetS4::VTableXmmwordOffset - 0xC00);
	}

	//*((__int64 *)&xmmword_1422FB990 + 1)
	__int64 highPart = pXmmword[1];

	Sub_141086E40Type sub_141086E40_f = reinterpret_cast<Sub_141086E40Type>(MovesetPlus::VTableAddress);

	//v7 = (__int64)sub_141086E40(*((__int64 *)&xmmword_1422FB990 + 1), (__int64)"StageMove");
	StageMoveVTable vtable = sub_141086E40_f(highPart, reinterpret_cast<__int64>("StageMove")); //sub_140AB7930

	//*(_QWORD *)(*(_QWORD *)(v7 + 8)
	__int64 innerPointer = *reinterpret_cast<__int64*>(reinterpret_cast<char*>(vtable) + 8);

	//*(_QWORD *)(*(_QWORD *)(v7 + 8) + 16i64);
	__int64 v9 = *reinterpret_cast<__int64*>(reinterpret_cast<char*>(reinterpret_cast<void*>(innerPointer)) + 16);


	if (param2 == 0) {
		sub_1406F6830_f(v9, Common::crc32((std::string)string_param)); //sub_1405E5D10
	}
	else {
		sub_1406F6800_f(v9); //sub_1405E5CEC
	}

	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		// *(DWORD*)(qword_14218F7C0 + 8)
		//cout << "Hash Stage: " << *reinterpret_cast<int*>(Common::GetQword(offsetSC::stageOffset) + 8) << endl;
		sub_1408EAE00_f(*reinterpret_cast<int*>(Common::GetQword(offsetSC::stageOffset) + 8));
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		// sub_140722544(dword_141611A88)
		//cout << "Hash Stage: " << Common::GetDword(offsetS4::stageOffset) << endl;
		sub_1408EAE00_f(static_cast<unsigned int>(Common::GetDword(offsetS4::stageOffset)));
	}


	__int64 enemy_pointer = BattleUtils::GetEnemyPointer(character_pointer);
	sub_140643C10_f(character_pointer); //sub_140580448
	sub_140643C10_f(enemy_pointer); //sub_140580448
}



__int64 MovesetPlus::BgmOffFunctionAdress = 0;
__int64 MovesetPlus::BgmOnFunctionAdress = 0;
__int64 MovesetPlus::BgmOff2FunctionAdress = 0;

int MovesetPlus::BGM_ID = 0;
void me_PlayBGM(int snd)
{
	//find ccAdvPlayStageBgm or check offset 0xB2B10 in 1.01 version of file
	__int64 offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = offsetSC::bgmOffset;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = offsetS4::bgmOffset;
	}
	if (snd == 0) {
		if (MovesetPlus::BGM_ID == 0) {
			
			typedef signed  __int64(__fastcall* IsPlayBgm)(__int64 a1, int a2);
			IsPlayBgm IsPlayBgm_f = (IsPlayBgm)(MovesetPlus::BgmOnFunctionAdress); //8E68B0
			do {
				MovesetPlus::BGM_ID++;
				//cout << "first = ";
				//cout << MovesetPlus::BGM_ID << endl;
			} while ((unsigned int)IsPlayBgm_f(Common::GetQword(offset), MovesetPlus::BGM_ID) != 1 && MovesetPlus::BGM_ID != 200); //qword_1420F3A20
			if (MovesetPlus::BGM_ID != -1 && MovesetPlus::BGM_ID != 200) {
				typedef signed  __int64(__fastcall* StopBgm)(__int64 a1, unsigned int a2);
				StopBgm StopBgm_f = (StopBgm)(MovesetPlus::BgmOffFunctionAdress); //8E93C0
				StopBgm_f(Common::GetQword(offset), 0); //qword_1420F3A20
			}
			

		}
		else {
			if (MovesetPlus::BGM_ID != -1 && MovesetPlus::BGM_ID != 200) {
				typedef signed  __int64(__fastcall* StopBgm)(__int64 a1, unsigned int a2);
				StopBgm StopBgm_f = (StopBgm)(MovesetPlus::BgmOffFunctionAdress); //8E93C0
				StopBgm_f(Common::GetQword(offset), 0); //qword_1420F3A20
			}
		}
	}
	else if (snd == 1) {
		if (MovesetPlus::BGM_ID != 0) {
			//cout << "second = ";
			//cout << MovesetPlus::BGM_ID << endl;
			typedef void(__fastcall* sub_14073C2E8)(__int64 a1, int a2, int a3, float a4, int a5);
			sub_14073C2E8 sub_14073C2E8_f = (sub_14073C2E8)(MovesetPlus::BgmOff2FunctionAdress); //8E6C10
			sub_14073C2E8_f(Common::GetQword(offset), MovesetPlus::BGM_ID, 0, -1, 0);
		}

	}
	
	


}

__int64 MovesetPlus::InitializeHandlerAddress = 0;
__int64 MovesetPlus::ResolveEffectAddress = 0;
__int64 MovesetPlus::ExecuteEffectAddress = 0;

__int64 __fastcall MovesetPlus::ApplyStatusEffect(__int64 a1, __int64 a2)
{
	__int64 v3; // rax
	__int64 v4; // rsi
	unsigned int v5; // eax
	int v6; // ebx
	unsigned int v7; // edi
	__int64 v8; // rax
	int param2_check; // ebx


	typedef signed  __int64(__fastcall* sub_14099A610)(__int64 a1);
	sub_14099A610 sub_14099A610_f = (sub_14099A610)(MovesetPlus::ResolveEffectAddress);
	typedef signed  __int64(__fastcall* sub_14099AEF0)(__int64 a1, unsigned int a2, int a3, float a4);
	sub_14099AEF0 sub_14099AEF0_f = (sub_14099AEF0)(MovesetPlus::ExecuteEffectAddress);



	param2_check = *(__int16*)(a2 + 38);

	if (param2_check == 1)
		v3 = a1;
	else
		v3 = BattleUtils::GetEnemyPointer(a1);
	v4 = v3;
	if (v3)
	{
		MovesetPlus::InitializeEffectHandler_f(v3);
		v5 = sub_14099A610_f(a2);
		v6 = *(__int16*)(a2 + 36);
		v7 = v5;
		v8 = MovesetPlus::InitializeEffectHandler_f(v4);
		sub_14099AEF0_f(v8, v7, v6, *(float*)(a2 + 44));
	}
	return 1;
}



__int64 __fastcall MovesetPlus::InitializeEffectHandler_f(__int64 a1)
{
	__int64 result; // rax
	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 71512;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 84840;
	}
	result = 0i64;
	if (*(__int64*)(a1 + offset))
		return *(__int64*)(a1 + offset);
	return result;
}


__int64 __fastcall MovesetPlus::CancelActionFunction(__int64 a1, __int64 a2)
{
	__int64 result; // rax 

	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 73728;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 85464;
	}
	// change 73712 value with update
	switch (*(int*)(a2 + 36))
	{
	case 0:
		*(int*)(a1 + offset) = 1;
		result = 1i64;
		break;
	case 1:
		*(int*)(a1 + offset) = 2; //JUMP CANCEL
		result = 1i64;
		break;
	case 2:
		*(int*)(a1 + offset) = 4;
		result = 1i64;
		break;
	case 3:
		*(int*)(a1 + offset) = 8; //DASH CANCEL
		result = 1i64;
		break;
	case 4:
		*(int*)(a1 + offset) = 16; // COMBO CANCEL
		result = 1i64;
		break;
	case 5:
		*(int*)(a1 + offset) = 32; // GRAB CANCEL
		result = 1i64;
		break;
	case 6:
		*(int*)(a1 + offset) = 64; //JUTSU CANCEL
		result = 1i64;
		break;
	case 7:
		*(int*)(a1 + offset) = 128;
		result = 1i64;
		break;
	case 8:
		*(int*)(a1 + offset) = 256; //ULTIMATE JUTSU CANCEL
		result = 1i64;
		break;
	case 9:
		*(int*)(a1 + offset) = 15; //WALK
		result = 1i64;
		break;
	case 0xA:
		*(int*)(a1 + offset) = 208; //JUTSU, COMBO CANCEL
		result = 1i64;
		break;
	case 0xB:
		*(int*)(a1 + offset) = 192;
		result = 1i64;
		break;
	case 0xC:
		*(int*)(a1 + offset) = -1; //ALL CANCEL
		result = 1i64;
		break;
	case 0xD:
		*(int*)(a1 + offset) = 512;
		result = 1i64;
		break;
	case 0xE:
		*(int*)(a1 + offset) = 1024; //SHURIKEN CANCEL
		result = 1i64;
		break;
	case 0xF:
		*(int*)(a1 + offset) = -1030; //COMBO, JUTSU, ULTIMATE, JUMP, GRAB, DASH
		result = 1i64;
		break;
	case 0x10:
		*(int*)(a1 + offset) = -22; // SHURIKEN, JUTSU, ULTIMATE, JUMP, GRAB, DASH
		result = 1i64;
		break;
	case 0x11:
		*(int*)(a1 + offset) = 1120; // GRAB, SHURIKEN, JUTSU
		result = 1i64;
		break;
	case 0x12:
		*(int*)(a1 + offset) = -6; //COMBO, JUTSU, ULTIMATE, JUMP, SHURIKEN, GRAB, DASH
		result = 1i64;
		break;
	default:
		*(int*)(a1 + offset) = 0;
		result = 1i64;
		break;
	}
	return result;
}

void me_enable_control(__int64 char_p, int enemy, int control) {
	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 0x12A34;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 0x15550;
	}
	__int64 pointer;
	if (enemy == 0)
		pointer = char_p;
	else
		pointer = BattleUtils::GetEnemyPointer(char_p);

	switch (control) {
	case 0:
		*(int*)(pointer + offset) = 1; //enable PL_ANM_ATK
		break;
	case 19:
		*(int*)(pointer + offset + 0x04) = 1; //enable PL_ANM_ATK_FAR and PL_ANM_ATK_FAR_ANOTHER
	case 1:
		*(int*)(pointer + offset + 0x08) = 1; //enable Ultimate Jutsu
		break;
	case 2:
		*(int*)(pointer + offset + 0x10) = 1; //enable Jutsus
		break;
	case 3:
		*(int*)(pointer + offset + 0x18) = 1; //enable PL_ANM_PRJ_LAND and PL_ANM_PRJ_ATK
		break;
	case 18:
		*(int*)(pointer + offset + 0x1C) = 1; //enable PL_ANM_PRJ_CHA_LAND
		break;
	case 4:
		*(int*)(pointer + offset + 0x20) = 1; //enable grab
		break;
	case 5:
		*(int*)(pointer + offset + 0x24) = 1; //enable substitution jutsu
		break;
	case 6:
		*(int*)(pointer + offset + 0x28) = 1; //enable guard
		break;
	case 7:
		*(int*)(pointer + offset + 0x2C) = 1; //enable chakra load
		break;
	case 8:
		*(int*)(pointer + offset + 0x30) = 1; //enable WASD and chakra
		break;
	case 9:
		*(int*)(pointer + offset + 0x34) = 1; //enable jump
		break;
	case 10:
		*(int*)(pointer + offset + 0x38) = 1; //enable ninja movement
		break;
	case 11:
		*(int*)(pointer + offset + 0x3C) = 1; //enable air dash
		break;
	case 12:
		*(int*)(pointer + offset + 0x40) = 1; //enable land dash
		break;
	case 13:
		*(int*)(pointer + offset + 0x44) = 1; //enable D-Pad items
		break;
	case 14:
		*(int*)(pointer + offset + 0x48) = 1; //enable leader switch
		break;
	case 15:
		*(int*)(pointer + offset + 0x4C) = 1; //enable awakening
		break;
	case 16:
		*(int*)(pointer + offset + 0x50) = 1; //enable supports
		break;
	case 17:
		*(int*)(pointer + offset + 0x58) = 1; //enable counter attack
		break;

	}
}
void me_disable_control(__int64 char_p, int enemy, int control) {

	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 0x12A34;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 0x15550;
	}
	__int64 pointer;
	if (enemy == 0)
		pointer = char_p;
	else
		pointer = BattleUtils::GetEnemyPointer(char_p);

	switch (control) {
	case 0:
		*(int*)(pointer + offset) = 0; //disable PL_ANM_ATK
		break;
	case 19:
		*(int*)(pointer + offset + 0x04) = 0; //disable PL_ANM_ATK_FAR and PL_ANM_ATK_FAR_ANOTHER
		break;
	case 1:
		*(int*)(pointer + offset + 0x08) = 0; //disable Ultimate Jutsu
		break;
	case 2:
		*(int*)(pointer + offset + 0x10) = 0; //disable Jutsus
		break;
	case 3:
		*(int*)(pointer + offset + 0x18) = 0; //disable PL_ANM_PRJ_LAND and PL_ANM_PRJ_ATK
		break;
	case 18:
		*(int*)(pointer + offset + 0x1C) = 0; //disable PL_ANM_PRJ_CHA_LAND
		break;
	case 4:
		*(int*)(pointer + offset + 0x20) = 0; //disable grab
		break;
	case 5:
		*(int*)(pointer + offset + 0x24) = 0; //disable substitution jutsu
		break;
	case 6:
		*(int*)(pointer + offset + 0x28) = 0; //disable guard
		break;
	case 7:
		*(int*)(pointer + offset + 0x2C) = 0; //disable chakra load
		break;
	case 8:
		*(int*)(pointer + offset + 0x30) = 0; //disable WASD and chakra
		break;
	case 9:
		*(int*)(pointer + offset + 0x34) = 0; //disable jump
		break;
	case 10:
		*(int*)(pointer + offset + 0x38) = 0; //disable ninja movement
		break;
	case 11:
		*(int*)(pointer + offset + 0x3C) = 0; //disable air dash
		break;
	case 12:
		*(int*)(pointer + offset + 0x40) = 0; //disable land dash
		break;
	case 13:
		*(int*)(pointer + offset + 0x44) = 0; //disable D-Pad items
		break;
	case 14:
		*(int*)(pointer + offset + 0x48) = 0; //disable leader switch
		break;
	case 15:
		*(int*)(pointer + offset + 0x4C) = 0; //disable awakening
		break;
	case 16:
		*(int*)(pointer + offset + 0x50) = 0; //disable supports
		break;
	case 17:
		*(int*)(pointer + offset + 0x58) = 0; //disable counter attack
		break;

	}

	

}
void me_change_control_timed(__int64 char_p, int enemy, int control, float duration_s) {
	int offset = 0;
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		offset = 0x12A34;
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		offset = 0x15550;
	}
	__int64 pointer;
	if (enemy == 0)
		pointer = char_p;
	else
		pointer = BattleUtils::GetEnemyPointer(char_p);

	switch (control) {
	case 0:
		*(int*)(pointer + offset) = 0; //disable PL_ANM_ATK
		break;
	case 19:
		*(int*)(pointer + offset + 0x04) = 0; //disable PL_ANM_ATK_FAR and PL_ANM_ATK_FAR_ANOTHER
		break;
	case 1:
		*(int*)(pointer + offset + 0x08) = 0; //disable Ultimate Jutsu
		break;
	case 2:
		*(int*)(pointer + offset + 0x10) = 0; //disable Jutsus
		break;
	case 3:
		*(int*)(pointer + offset + 0x18) = 0; //disable PL_ANM_PRJ_LAND and PL_ANM_PRJ_ATK
		break;
	case 18:
		*(int*)(pointer + offset + 0x1C) = 0; //disable PL_ANM_PRJ_CHA_LAND
		break;
	case 4:
		*(int*)(pointer + offset + 0x20) = 0; //disable grab
		break;
	case 5:
		*(int*)(pointer + offset + 0x24) = 0; //disable substitution jutsu
		break;
	case 6:
		*(int*)(pointer + offset + 0x28) = 0; //disable guard
		break;
	case 7:
		*(int*)(pointer + offset + 0x2C) = 0; //disable chakra load
		break;
	case 8:
		*(int*)(pointer + offset + 0x30) = 0; //disable WASD and chakra
		break;
	case 9:
		*(int*)(pointer + offset + 0x34) = 0; //disable jump
		break;
	case 10:
		*(int*)(pointer + offset + 0x38) = 0; //disable ninja movement
		break;
	case 11:
		*(int*)(pointer + offset + 0x3C) = 0; //disable air dash
		break;
	case 12:
		*(int*)(pointer + offset + 0x40) = 0; //disable land dash
		break;
	case 13:
		*(int*)(pointer + offset + 0x44) = 0; //disable D-Pad items
		break;
	case 14:
		*(int*)(pointer + offset + 0x48) = 0; //disable leader switch
		break;
	case 15:
		*(int*)(pointer + offset + 0x4C) = 0; //disable awakening
		break;
	case 16:
		*(int*)(pointer + offset + 0x50) = 0; //disable supports
		break;
	case 17:
		*(int*)(pointer + offset + 0x58) = 0; //disable counter attack
		break;

	}

	// Start a new thread to restore the control after the duration
	std::thread([=]() {
		// Wait for the specified duration
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(duration_s * 1000)));

		// Restore the control (set value back to 1)
		switch (control) {
		case 0:
			*(int*)(pointer + offset) = 1; //enable PL_ANM_ATK
			break;
		case 19:
			*(int*)(pointer + offset + 0x04) = 1; //enable PL_ANM_ATK_FAR and PL_ANM_ATK_FAR_ANOTHER
			break;
		case 1:
			*(int*)(pointer + offset + 0x08) = 1; //enable Ultimate Jutsu
			break;
		case 2:
			*(int*)(pointer + offset + 0x10) = 1; //enable Jutsus
			break;
		case 3:
			*(int*)(pointer + offset + 0x18) = 1; //enable PL_ANM_PRJ_LAND and PL_ANM_PRJ_ATK
			break;
		case 18:
			*(int*)(pointer + offset + 0x1C) = 1; //enable PL_ANM_PRJ_CHA_LAND
			break;
		case 4:
			*(int*)(pointer + offset + 0x20) = 1; //enable grab
			break;
		case 5:
			*(int*)(pointer + offset + 0x24) = 1; //enable substitution jutsu
			break;
		case 6:
			*(int*)(pointer + offset + 0x28) = 1; //enable guard
			break;
		case 7:
			*(int*)(pointer + offset + 0x2C) = 1; //enable chakra load
			break;
		case 8:
			*(int*)(pointer + offset + 0x30) = 1; //enable WASD and chakra
			break;
		case 9:
			*(int*)(pointer + offset + 0x34) = 1; //enable jump
			break;
		case 10:
			*(int*)(pointer + offset + 0x38) = 1; //enable ninja movement
			break;
		case 11:
			*(int*)(pointer + offset + 0x3C) = 1; //enable air dash
			break;
		case 12:
			*(int*)(pointer + offset + 0x40) = 1; //enable land dash
			break;
		case 13:
			*(int*)(pointer + offset + 0x44) = 1; //enable D-Pad items
			break;
		case 14:
			*(int*)(pointer + offset + 0x48) = 1; //enable leader switch
			break;
		case 15:
			*(int*)(pointer + offset + 0x4C) = 1; //enable awakening
			break;
		case 16:
			*(int*)(pointer + offset + 0x50) = 1; //enable supports
			break;
		case 17:
			*(int*)(pointer + offset + 0x58) = 1; //enable counter attack
			break;

		}
		}).detach(); // Detach the thread to run independently
}
MovesetPlus::orig_EnableUpgradeCancel_t MovesetPlus::orig_EnableUpgradeCancel = nullptr;
int __fastcall MovesetPlus::EnableUpgradeCancel(__int64 a1)
{

	int result = MovesetPlus::orig_EnableUpgradeCancel(a1);
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
	{
		int mainCharId = *(int*)(a1 + 0xE64);
		int characterSide = *((int*)(a1 + 0xE60));
		if (mainCharId == 0x72 || mainCharId == 0x2F) {
			return result;
		}
		else {
			return MovesetPlus::cancelUpgradeFunctionState[characterSide];
		}
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
	{
		int mainCharId = *(int*)(a1 + 0xC8C);
		int characterSide = *((int*)(a1 + 0xC88));
		if (mainCharId == 0x72 || mainCharId == 0x2F) {
			return result;
		}
		else {
			return MovesetPlus::cancelUpgradeFunctionState[characterSide];
		}
	}

	return result;

}

MovesetPlus::orig_UpgradeVerUnlocker_t MovesetPlus::orig_UpgradeVerUnlocker = nullptr;
__int64 __fastcall MovesetPlus::UpgradeVerUnlocker(__int64 a1, unsigned int a2)
{
	__int64 result = MovesetPlus::orig_UpgradeVerUnlocker(a1, a2);
	__int64 partner_ptr = (__int64)ccPlayer::GetPartnerPointer((ccPlayerMain*)a1);
	if (partner_ptr) {

		result = MovesetPlus::orig_UpgradeVerUnlocker(partner_ptr, a2);
	}
	int characterSide = *((int*)(a1 + 0xE60));
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		int characterSide = *((int*)(a1 + 0xE60));
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		int characterSide = *((int*)(a1 + 0xC88));
	}

	typedef __int64(__fastcall* fn_slot)(__int64 obj, unsigned int idx);
	fn_slot fn_slot_call = (fn_slot)MovesetPlus::sub_1405C8F00Adress;
	MovesetPlus::cancelUpgradeFunctionState[characterSide] = 0;

	auto compute_index_for = [&](__int64 obj, const char* debug_name) -> int {
		if (!obj) {
			// Log: debug_name + " is null"
			return -1;
		}

		__int64 ptr_at_520 = *(__int64*)(obj + 520);
		if (!ptr_at_520) {
			// Log: debug_name + " pointer at +520 is null"
			return -1;
		}

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			int value = *(int*)(obj + 0xEA0);
			// Log: debug_name + " value at +0xEA0: " + value
			switch (value) {
			case 2: return 0;
			case 3: return 1;
			case 4: return 2;
			case 5: return 3;
			case 6: return 4;
			case 7: return 5;
			case 8: return 6;
			default:
				// Log: debug_name + " unexpected value: " + value
				return -1;
			}
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			int value = *(int*)(obj + 0xCBC);
			// Log: debug_name + " value at +0xCBC: " + value
			switch (value) {
			case 2: return 0;
			case 3: return 1;
			case 4: return 2;
			case 5: return 3;
			case 6: return 4;
			case 7: return 5;
			case 8: return 6;
			default: return -1;
			}
		}
		return -1;
		};

	// Process main player
	int idx_main = compute_index_for(a1, "MainPlayer");
	if (idx_main >= 0) {
		fn_slot_call(*(__int64*)(a1 + 520), idx_main);
	}
	// Process partner
	int idx_partner = compute_index_for(partner_ptr, "Partner");
	if (idx_partner >= 0) {
		fn_slot_call(*(__int64*)(partner_ptr + 520), idx_partner);
	}

	return result;
}

__int64 MovesetPlus::Motion_cancel_function(int* a1)
{
	typedef signed __int64(__fastcall* sub_140978B00_t)(int* a1);
	sub_140978B00_t sub_140978B00_f = (sub_140978B00_t)(MovesetPlus::sub_140978B00Adress);



	__int64 partner_ptr = (__int64)ccPlayer::GetPartnerPointer((ccPlayerMain*)a1);
	if (a1)
		sub_140978B00_f(a1);
	if (partner_ptr)
		sub_140978B00_f((int*)partner_ptr);
	int characterSide = *((int*)(a1 + 0xE60));
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		int characterSide = *((int*)(a1 + 0xE60));
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		int characterSide = *((int*)(a1 + 0xC88));
	}
	//MovesetPlus::cancelUpgradeFunctionState[characterSide] = 1;
	return 1i64;
}
void me_play_movie( int param2) {
	// получаем нуль-терминированный буфер как unsigned char*
	/*unsigned char* param_buf = const_cast<unsigned char*>(
		reinterpret_cast<const unsigned char*>(str_param.c_str())
		);
	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
		using fn_sub_1405674F0 = void(__fastcall*)(unsigned char* a1);
		auto sub_1405674F0 = reinterpret_cast<fn_sub_1405674F0>(moduleBase + 0x5668F0);
		sub_1405674F0(param_buf);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		using fn_sub_1404E18B0 = void(__fastcall*)(unsigned char* a1);
		auto sub_1404E18B0 = reinterpret_cast<fn_sub_1404E18B0>(moduleBase + 0x4E0CB0);
		sub_1404E18B0(param_buf);
	}*/


	using fn_sub_140567580 = __int64(__fastcall*)(unsigned int a1);
	auto sub_140567580 = reinterpret_cast<fn_sub_140567580>(moduleBase + 0x566980);
	sub_140567580(param2);
}
void me_change_camera_algorithm() {



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
void me_character_param(__int64 char_p, const std::string& str_param, int param2) {

	//using fn_sub_1405AD390 = __int64* (__fastcall*)();
	//auto sub_1405AD390 = reinterpret_cast<fn_sub_1405AD390>(moduleBase + 0x929060);

	//sub_1405AD390();

	__int64 enemy_pointer = BattleUtils::GetEnemyPointer(char_p);

	ccPlayer::SetActionImmediate((ccPlayer*)char_p, param2);


	/*__int64  v47 = *(__int64*)(char_p + 0x208);

	render::CoordByFullName = ccGameObjSubDraw::GetCoordByFullName(v47, (__int64)"1sik00t0 trall", 0);
	Console::PrintErr("render::CoordByFullName: %p", render::CoordByFullName);
	if (render::CoordByFullName)
	{
		using fn_GetWorldPosNew = __int64(__fastcall*)(__int64 a1, __int64 a2);
		auto GetWorldPosNew = reinterpret_cast<fn_GetWorldPosNew>(moduleBase + 0x1261CC0);
		render::WorldPosNew = GetWorldPosNew(render::CoordByFullName, (__int64)render::WorldPosData);
		Console::PrintErr("render::WorldPosNew: %p", render::WorldPosNew);
		Console::PrintErr("render::WorldPosData: %p", render::WorldPosData);
	}*/
}
void me_play_scene(int param2) {

	using fn_EntryCreateSceneCommand = void(__fastcall*)(__int64 a1, int a2);
	auto EntryCreateSceneCommand = reinterpret_cast<fn_EntryCreateSceneCommand>(moduleBase + 0x10764B0);

	EntryCreateSceneCommand(Common::GetQword(0x1422FB988),param2);

}

void me_play_IA(const std::string& str_param) {


	if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

		char* param_buf = const_cast<char*>(
			reinterpret_cast<const char*>(str_param.c_str())
			);

		using fn_ccPlayIA = void(__fastcall*)(char* a1);
		auto ccPlayIA = reinterpret_cast<fn_ccPlayIA>(moduleBase + 0x5668F0);

		ccPlayIA(param_buf);
	}
	else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
		char* param_buf = const_cast<char*>(
			reinterpret_cast<const char*>(str_param.c_str())
			);

		using fn_ccPlayIA = void(__fastcall*)(char* a1);
		auto ccPlayIA = reinterpret_cast<fn_ccPlayIA>(moduleBase + 0x4E0CB0);

		ccPlayIA(param_buf);
	}


	

}
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

//D-pad function fix for Storm 4
__int64 __fastcall MovesetPlus::Hooked_sub_14084E110_S4(__int64* a1, int a2) {

	static std::array<uint8_t, 1> originalBytes{}; // save 1 original byte (for possible restore)
	static std::array<uint8_t, 1> originalBytes2{}; // save 1 original byte (for possible restore)
	int v6; // edi
	unsigned int v14; // ebx
	v6 = *((int*)a1 + 0x5594);


	uintptr_t target = moduleBase + 0x6C19EB;
	uintptr_t target2 = moduleBase + 0x6C19EF;
	std::array<uint8_t, 1> vals = { 0x03 };
	std::array<uint8_t, 1> vals2 = { 0x01 };

	//Console::PrintErr("D-PAD Address %p\n", target);
	//Console::PrintErr("v6 = %d\n", v6);
	switch (v6)
	{
	case 0:  // v6 == 0
		vals = { 0x00 };
		vals2 = { 0x02 };
		PatchBytes(target, vals.data(), vals.size(), originalBytes.data());

		PatchBytes(target2, vals2.data(), vals2.size(), originalBytes2.data());
		//Console::PrintErr("plAnmId = 923\n");
		//return 923;
		break;
	case 1:  // v6 == 1
		vals = { 0x01 };
		vals2 = { 0x03 };
		PatchBytes(target, vals.data(), vals.size(), originalBytes.data());
		PatchBytes(target2, vals2.data(), vals2.size(), originalBytes2.data());
		//Console::PrintErr("plAnmId = 924\n");
		//return 924;

		break;
	case 2:  // v6 == 3
		//Console::PrintErr("plAnmId = 921\n");
		break;
	case 3:  // v6 == 3
		vals = { 0x03 };
		vals2 = { 0x01 };
		PatchBytes(target, vals.data(), vals.size(), originalBytes.data());
		PatchBytes(target2, vals2.data(), vals2.size(), originalBytes2.data());
		//Console::PrintErr("plAnmId = 922\n");
		//return 922;

		break;
	}


	__int64 result = MovesetPlus::orig_sub_14084E110_S4(a1, a2);

	vals = { 0x03 };
	vals2 = { 0x01 };
	PatchBytes(target, vals.data(), vals.size(), originalBytes.data());
	PatchBytes(target2, vals2.data(), vals2.size(), originalBytes2.data());

	return result;
}

MovesetPlus::orig_ME_DRAWOBJ_DISABLE_t MovesetPlus::orig_ME_DRAWOBJ_DISABLE = nullptr;

// Helper function to replace a pattern in the string
bool ReplacePattern(char* string_param, const char* pattern, const char* replacement, __int64 a2) {
	char* pos = std::strstr(string_param, pattern);
	if (pos != nullptr && replacement != nullptr) {
		char modified_string[31] = { 0 };

		size_t prefix_len = pos - string_param;
		size_t replacement_len = std::strlen(replacement);
		size_t pattern_len = std::strlen(pattern);
		size_t suffix_len = std::strlen(pos + pattern_len);

		if (prefix_len + replacement_len + suffix_len <= 30) {
			std::memcpy(modified_string, string_param, prefix_len);
			std::memcpy(modified_string + prefix_len, replacement, replacement_len);
			std::memcpy(modified_string + prefix_len + replacement_len, pos + pattern_len, suffix_len);
			modified_string[prefix_len + replacement_len + suffix_len] = '\0';

			std::memcpy(reinterpret_cast<void*>(a2), modified_string, 31);
			return true;
		}
	}
	return false;
}

__int64 __fastcall MovesetPlus::ME_DRAWOBJ_DISABLE(__int64 a1, __int64 a2)
{
	char string_param[31] = { 0 };
	std::strncpy(string_param, reinterpret_cast<const char*>(a2), 30);
	string_param[30] = '\0';

	int charID = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
	int charCostumeID = ccPlayer::GetCharCodeCostumeID((ccPlayerMain*)a1);
	const char* charCodeCostume = ccPlayer::GetCharCostumeCode(charID, charCostumeID);

	// Try to replace "%s" first, if not found, try "2kzu"
	if (!ReplacePattern(string_param, "%s", charCodeCostume, a2)) {
		ReplacePattern(string_param, "2kzu", charCodeCostume, a2);
	}

	return MovesetPlus::orig_ME_DRAWOBJ_DISABLE(a1, a2);
}

MovesetPlus::orig_ME_DRAWOBJ_ENABLE_t MovesetPlus::orig_ME_DRAWOBJ_ENABLE = nullptr;

__int64 __fastcall MovesetPlus::ME_DRAWOBJ_ENABLE(__int64 a1, __int64 a2)
{
	char string_param[31] = { 0 };
	std::strncpy(string_param, reinterpret_cast<const char*>(a2), 30);
	string_param[30] = '\0';

	int charID = ccPlayer::GetCharCodeID((ccPlayerMain*)a1);
	int charCostumeID = ccPlayer::GetCharCodeCostumeID((ccPlayerMain*)a1);
	const char* charCodeCostume = ccPlayer::GetCharCostumeCode(charID, charCostumeID);

	// Try to replace "%s" first, if not found, try "2kzu"
	if (!ReplacePattern(string_param, "%s", charCodeCostume, a2)) {
		ReplacePattern(string_param, "2kzu", charCodeCostume, a2);
	}

	return MovesetPlus::orig_ME_DRAWOBJ_ENABLE(a1, a2);
}
