#pragma once
#include "ccGameObjSubDraw.h"
#include "Vector3.h"

class ccPlayerMain
{
public:
	__int64 vtable; // 0x00 to 0x08
	char padding0[0x68]; // 0x08 to 0x70
	Vector3 m_position; // 0x70 to 0x7C
	char padding1[0x2C]; // 0x7C to 0xA8
	Vector3 m_moveDir; // 0xA8 to 0xB4
	char padding2[0x94]; // 0xB4 to 0x148
	Vector3 m_speedVector; // 0x148 to 0x154
	float m_speedForward; // 0x154 to 0x158
	float m_gravity; // 0x158 to 0x15C
	float m_speedVertical; // 0x15C to 0x160
	char padding3[0xA0]; // 0x160 to 0x200
	float m_modelScale; // 0x200 to 0x204
	char padding4[0x04]; // 0x204 to 0x208
	ccGameObjSubDraw* m_gameObjSubDraw; // 0x208 to 0x210
	char padding5[0x08]; // 0x210 to 0x218
	__int64 m_playerPad; // 0x218 to 0x220
	float m_pad_analogL; // 0x220 to 0x224
	char padding6[0xA64]; // 0x224 to 0xC88
	int m_playerIndex; // 0xC88 to 0xC8C
	int m_characterID; // 0xC8C to 0xC90
	char padding7[0x1C]; // 0xC90 to 0xCAC
	int m_enableInput; // 0xCAC to 0xCB0
	int m_enableControl; // 0xCB0 to 0xCB4
	char padding8[0x04]; // 0xCB4 to 0xCB8
	int m_enableDraw; // 0xCB8 to 0xCBC
	int m_unknownFlag; // 0xCBC to 0xCC0
	int m_PL_ACT_CURRENT; // 0xCC0 to 0xCC4
	int m_PL_ACT_PREVIOUS; // 0xCC4 to 0xCC8
	int m_PL_ACT_NEXT; // 0xCC8 to 0xCCC
	int m_isPlActAvailable; // 0xCCC to 0xCD0
	int m_isPlayerStateAvailable; // 0xCD0 to 0xCD4
	char padding9[0x3AC]; // 0xCD4 to 0x1080
	int m_PL_ANM_CURRENT; // 0x1080 to 0x1084
	float m_PL_ANM_CURRENT_unkFloat; // 0x1084 to 0x1088
	char padding10[0x0C]; // 0x1088 to 0x1094
	float m_PL_ANM_PREVIOUS; // 0x1094 to 0x1098
};

class ccPlayer
{
public:
	static int __fastcall GetCharCodeID(ccPlayerMain* player_ptr) {
		//  
		uintptr_t p = reinterpret_cast<uintptr_t>(player_ptr);

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *reinterpret_cast<int*>(p + 0xE64);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return *reinterpret_cast<int*>(p + 0xC8C);
		}
	}static int __fastcall GetCharCodeCostumeID(ccPlayerMain* player_ptr) {
		//  
		uintptr_t p = reinterpret_cast<uintptr_t>(player_ptr);

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *reinterpret_cast<int*>(p + 0xE70);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return *reinterpret_cast<int*>(p + 0xC94);
		}
	}
	static int __fastcall GetActionID(ccPlayerMain* player_ptr) {
		//  
		uintptr_t p = reinterpret_cast<uintptr_t>(player_ptr);

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *reinterpret_cast<int*>(p + 0xEA4);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return *reinterpret_cast<int*>(p + 0xCC0);
		}
	}
	static int __fastcall GetCharacterState(ccPlayerMain* player_ptr) {
		//  
		uintptr_t p = reinterpret_cast<uintptr_t>(player_ptr);

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *reinterpret_cast<int*>(p + 0xEA0);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return *reinterpret_cast<int*>(p + 0xCBC);
		}
	}
	static const char* __fastcall GetCharCode(unsigned int characode_id) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef const char* (__fastcall* funct)(unsigned int characode_id);
			funct fc = (funct)(moduleBase + 0x58F3D0);
			return fc(characode_id);


		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef const char* (__fastcall* funct)(unsigned int characode_id);
			funct fc = (funct)(moduleBase + 0x5289FC);
			return fc(characode_id);
		}
	}
	static const char* __fastcall GetCharCostumeCode(unsigned int characode_id, unsigned int costume_id) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef const char* (__fastcall* funct)(unsigned int characode_id, unsigned int costume_id);
			funct fc = (funct)(moduleBase + 0x58F5A0);
			return fc(characode_id, costume_id);


		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef const char* (__fastcall* funct)(unsigned int characode_id, unsigned int costume_id);
			funct fc = (funct)(moduleBase + 0x528B18);
			return fc(characode_id, costume_id);
		}
	}
	static const char* __fastcall GetAnmName(ccPlayerMain* player_ptr) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<const char* (__fastcall*)(ccPlayerMain * player_ptr)>(moduleBase + 0x9812A0)(player_ptr);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<const char* (__fastcall*)(ccPlayerMain * player_ptr)>(moduleBase + 0x77587C)(player_ptr);
		}
	}
	static const char* __fastcall GetPlAnmName(int pl_anm_id) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<const char* (__fastcall*)(int pl_anm_id)>(moduleBase + 0x5915A0)(pl_anm_id);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<const char* (__fastcall*)(int pl_anm_id)>(moduleBase + 0x529884)(pl_anm_id);
		}
	}
	static const char* __fastcall GetAnmId(ccPlayerMain* player_ptr) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<const char* (__fastcall*)(ccPlayerMain * player_ptr)>(moduleBase + 0x98ECE0)(player_ptr);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<const char* (__fastcall*)(ccPlayerMain * player_ptr)>(moduleBase + 0x77CF38)(player_ptr);
		}
	}
	static void __fastcall SetActionImmediate(ccPlayer* p, int action)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<void(__fastcall*)(ccPlayer * p, int action)>(moduleBase + 0x9D3E00)(p, action);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<void(__fastcall*)(ccPlayer * p, int action)>(moduleBase + 0x7ADC9C)(p, action);
		}
		/*typedef void(__fastcall * funct)(ccPlayer * p, int action);
		funct fc = (funct)(moduleBase + 0x7ADC9C);
		fc(p, action);*/

		//std::cout << "Setting action" << std::endl;
	}
	static void __fastcall SetAnmDirect(ccPlayer* p, int action)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef const char* (__fastcall* funct)(ccPlayer* a1, __int64 a2, __int64 a3, __int64 a4, int a5, int a6);
			funct fc = (funct)(moduleBase + 0x990D40);
			fc(p, action, 0, 0xFFFFFFFFi64, 0, 0);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef const char* (__fastcall* funct)(ccPlayer* a1, __int64 a2, __int64 a3, __int64 a4, int a5, int a6);

			funct fc = (funct)(moduleBase + 0x77DA4C);
			fc(p, action, 0, 0xFFFFFFFFi64, 0, 0);
		}
	}
	static ccPlayerMain* __fastcall GetPartnerPointer(ccPlayerMain* player_ptr) {
		//  
		uintptr_t p = reinterpret_cast<uintptr_t>(player_ptr);

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *reinterpret_cast<ccPlayerMain**>(p + 0x1248);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return *reinterpret_cast<ccPlayerMain**>(p + 0x1050);
		}
	}
	static const char* GetActFuncName(ccPlayerMain* p)
	{
		if (!p) return nullptr;
		constexpr size_t ENTRY_SIZE = 0x20;   // 32 
		constexpr size_t PTR_OFFSET = 0x10;   //    
		constexpr size_t FLAG_OFFSET = 0x18;  //  4- /
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			// read int at p + 0xEAC
			int idx = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(p) + 0xEA4);
			if (idx < 0 || idx > 324) return nullptr;

			// Option A: ASLR-aware (recommended)
			uintptr_t tableAddr = Common::GetOffset(0x142016450);

			//   
			uintptr_t entryAddr = tableAddr + static_cast<uintptr_t>(idx) * ENTRY_SIZE;

			//  8-    (PTR_OFFSET)
			void* strPtr = *reinterpret_cast<void**>(entryAddr + PTR_OFFSET);
			if (!strPtr) return nullptr;


			return reinterpret_cast<const char*>(strPtr);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			// read int at p + 0xEAC
			int idx = *reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(p) + 0xCC0);
			if (idx < 0 || idx > 324) return nullptr;

			// Option A: ASLR-aware (recommended)
			uintptr_t tableAddr = Common::GetOffset(0x141537DC0);

			//   
			uintptr_t entryAddr = tableAddr + static_cast<uintptr_t>(idx) * ENTRY_SIZE;

			//  8-    (PTR_OFFSET)
			void* strPtr = *reinterpret_cast<void**>(entryAddr + PTR_OFFSET);
			if (!strPtr) return nullptr;


			return reinterpret_cast<const char*>(strPtr);
		}
	}
};

class ccPlayerPad
{
public:
	static bool __fastcall IsFireArm(__int64 playerPad) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return (*(int*)(playerPad + 1456) & *(int*)(playerPad + 1028)) != 0;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return (*(int*)(playerPad + 1420) & *(int*)(playerPad + 1028)) != 0;
		}
	}
	
};