#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "Common.h"
#include "HookFunctions.h"
#include "Vector3.h"
#include "ccCmnCamera.h"
#include "ccCmnCameraDirector.h"
#include "ccCmnScreenManager.h"
#include "ccPlayerMain.h"

struct __declspec(align(8)) ccFramework
{
	void* ptr0;
	void* ptr1;
	void* ptr2;
	void* ptr3;
	void* ptr4;
	void* ptr5;
	void* ptr6;
	void* ptr7;
	void* ptr8;
	void* SceneManager;
	void* TaskManager;
	void* GameProperty;
	void* ccTrophyManager;
	void* ccPresenceManager;
	void* ccSaveManager;
	void* CollisionManager;
	void* ccNetStartUp;
	void* ccNetOnlineCheck;
	void* ccMessageManager;
	void* ptr19;
	void* XfbinDocManagerForUi;
	void* UiManager;
	void* ptr22;
	void* ccInvitedParam;
	void* ccParentalControl;
	void* ptr25;
	void* ptr26;
	void* ptr27;
	void* ptr28;
	void* ptr29;
	void* ptr30;
	void* ptr31;
	void* ptr32;
	void* ptr33;
	void* ptr34;
};







//class ccUiWindow
//{
//public:
//	static __int64 Create(__int64 a1) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x65929C)(a1); }
//	static __int64 AllocateMessageWindow(__int64 a1, const char* a2) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2)>(moduleBase + 0x6594CC)(a1, a2); }
//	static __int64 SetTitleText(__int64 a1, const char* a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2, int a3)>(moduleBase + 0x6598C0)(a1, a2, a3); }
//	static __int64 SetMenuTextWordWrap(__int64 a1) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(moduleBase + 0x659848)(a1); }
//	static __int64 SetMenuText(__int64 a1, const char* a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, const char* a2, int a3)>(moduleBase + 0x6596AC)(a1, a2, a3); }
//	static __int64 SetMenuTextColor(__int64 a1, int a2) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2)>(moduleBase + 0x6597D0)(a1, a2); }
//	static void Open(__int64 a1) { return reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0x659690)(a1); }
//	static void Close(__int64 a1) { return reinterpret_cast<void(__fastcall*)(__int64 a1)>(moduleBase + 0x659488)(a1); }
//	static __int64 SetWindowSize(__int64 a1, int a2, int a3) { return reinterpret_cast<__int64(__fastcall*)(__int64 a1, int a2, int a3)>(moduleBase + 0x6599E4)(a1, a2, a3); }
//};
//





class Game
{
public:
	static __int64 __fastcall operator_new(__int64 a1, const char* a2, unsigned int a3)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(__int64 a1, const char* a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0x124AA70);
			return fc(a1, a2, a3);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(__int64 a1, const char* a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0xA00BF0);
			return fc(a1, a2, a3);
		}
	}

	static signed __int64 __fastcall delete_operator(__int64 a1)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef signed __int64(__fastcall* funct)(__int64 a1);
			funct fc = (funct)(moduleBase + 0x124B430);
			return fc(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef signed __int64(__fastcall* funct)(__int64 a1);
			funct fc = (funct)(moduleBase + 0xA01180);
			return fc(a1);
		}
		
	}

	static __int64 __fastcall gameInfoPtr()
	{
		
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			__int64* gameInfo = (__int64*)(moduleBase + 0x1496CF1C8 - 0x140000C00);
			return (__int64)gameInfo;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			__int64* gameInfo = (__int64*)(moduleBase + 0x1416663C8 - 0x140000C00);
			return (__int64)gameInfo;
		}

		
	}

	static __int64 __fastcall gameInfo()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			__int64* gameInfo = (__int64*)(moduleBase + 0x1496CF1C8 - 0x140000C00);
			return *gameInfo;
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			__int64* gameInfo = (__int64*)(moduleBase + 0x1416663C8 - 0x140000C00);
			return *gameInfo;
		}
	}
	static __int64 ObjectList_GetPtrLightsAndFog()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return (__int64)(moduleBase + 0x142196BD0 - 0x140000C00);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return (__int64)(moduleBase + 0x14161A340 - 0x140000C00);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.00") == 0) {

			return (__int64)(moduleBase + 0x1419582E0 - 0x140000C00);
		}
	}

	static __int64 ObjectList_GetInstanceLightsAndFog()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *((__int64*)(moduleBase + 0x142196BD0 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return *((__int64*)(moduleBase + 0x14161A340 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.00") == 0) {

			return *((__int64*)(moduleBase + 0x1419582E0 - 0x140000C00));
		}

	}


	static __int64 ObjectList_GetPtrLightsAndShadow()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return (__int64)(moduleBase + 0x142198CD0 - 0x140000C00);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return (__int64)(moduleBase + 0x14161C550 - 0x140000C00);
		}
	}

	static __int64 ObjectList_GetInstanceLightsAndShadow()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return *((__int64*)(moduleBase + 0x142198CD0 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return *((__int64*)(moduleBase + 0x14161C550 - 0x140000C00));
		}

	}

	/*static __int64 ObjectList_GetInstanceGlobal() // For permanent objects
	{
		return *((__int64*)(moduleBase + 0x14161C948 - 0x140000C00));
	}

	static __int64 ObjectList_GetPtrLightsAndFog()
	{
		return (__int64)(moduleBase + 0x14161A340 - 0x140000C00);
	}

	static __int64 ObjectList_GetInstanceLightsAndFog()
	{
		return *((__int64*)(moduleBase + 0x14161A340 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceAdventure()
	{
		return *((__int64*)(moduleBase + 0x1415E7220 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceGroupBattle()
	{
		__int64* objectListPtr = (__int64*)(moduleBase + 0x1415DDDD0 - 0x140000C00);

		if (*objectListPtr)
		{
			objectListPtr = (__int64*)((*objectListPtr) + 72);
			return *objectListPtr;
		}
		else
		{
			return 0;
		}
	}
	*/

	static __int64 ObjectList_GetInstanceDuel()
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			// 14161C780
			return *((__int64*)(moduleBase + 0x14161C8C8 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			// 14161C780
			return *((__int64*)(moduleBase + 0x14161C8C8 - 0x140000C00));
		}
	}

	/*static __int64 ObjectList_StageObjectManager() // For local objects
	{
		// 14161C8B8
		return *((__int64*)(moduleBase + 0x14161C8B8 - 0x140000C00));
	}

	static __int64 ObjectList_GetInstanceUI()
	{
		return *((__int64*)(moduleBase + 0x14161C8D8 - 0x140000C00));
	}*/
	static ccCmnScreenManager* GetCmnScreenManager()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			// 14161C780


			return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x142198F00 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			// 14161C780
			return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x14161C780 - 0x140000C00));
		}
	}

	static __int64 ConvertOffset(__int64 address)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			if (address < 0x1709A00) // text
			{
				return moduleBase + address;
			}
			else if (address < 0x170AED0) // idata
			{
				return moduleBase + address + 0x200;
			}
			else if (address < 0x1F2D000) // rdata
			{
				return moduleBase + address + 0x200;
			}
			else if (address < 0x212BC00) // data
			{
				std::cout << "Address is in data" << std::endl;
				return moduleBase + address + 0x400;
			}
			else if (address < 0x2282C00) // pdata
			{
				return moduleBase + address + 0x1000;
			}
			else // _RDATA
			{
				return moduleBase + address + 0x1400;
			}
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			if (address < 0xEAC000) // text
			{
				return moduleBase + address;
			}
			else if (address < 0xEACF88) // idata
			{
				return moduleBase + address + 0x200;
			}
			else if (address < 0x13B6000) // rdata
			{
				return moduleBase + address + 0x200;
			}
			else if (address < 0x15BD400) // data
			{
				std::cout << "Address is in data" << std::endl;
				return moduleBase + address + 0x400;
			}
			else if (address < 0x1690400) // pdata
			{
				return moduleBase + address + 0x1000;
			}
			else // tls
			{
				return moduleBase + address + 0x1400;
			}
		}
		
	}

	static ccFramework* GetFramework()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return (ccFramework*)*((__int64*)(moduleBase + 0x1422FB940 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return (ccFramework*)*((__int64*)(moduleBase + 0x1416BD9D0 - 0x140000C00));
		}
		//return (ccFramework*)((__int64*)(gameInfo() + 0xF40));
	}

	static float GetResX()
	{
		return *(INT16*)(Game::gameInfo() + 0x470);
	}

	static float GetResY()
	{
		return *(INT16*)(Game::gameInfo() + 0x472);
	}

	static short GetFPS()
	{
		return *(short*)(gameInfo() + 0x942);
	}
};

class ccPlayerAnmIdManager
{
public:
	static const char* __fastcall GetName(int a1)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef const char* (__fastcall* funct)(int a1);
			funct fc = (funct)(moduleBase + 0x529884);
			return fc(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef const char* (__fastcall* funct)(int a1);
			funct fc = (funct)(moduleBase + 0x529884);
			return fc(a1);
		}
		
	}
};

class ccScene
{
public:
	static __int64 Constructor(ccScene* a1)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccScene* a1);
			funct fc = (funct)(moduleBase + 0x106B8C0);
			return fc(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccScene* a1);
			funct fc = (funct)(moduleBase + 0xAB3760);
			return fc(a1);
		}
		
	}

	static __int64 __fastcall SetSceneName(ccScene* a1, const char* a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccScene* a1, const char* a2);
			funct fc = (funct)(moduleBase + 0x106BC90);
			return fc(a1, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccScene* a1, const char* a2);
			funct fc = (funct)(moduleBase + 0xAB3950);
			return fc(a1, a2);
		}
	}

	static bool AuthorizeGameProperty(__int64 a1)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<bool(__fastcall*)(__int64)>(moduleBase + 0x106BC30)(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<bool(__fastcall*)(__int64)>(moduleBase + 0xAB39B0)(a1);
		}
	}
};
class BattleUtils
{
public:
	static ccPlayerMain* __fastcall ccGame_GetPlayerLeader(unsigned int PLAYER_SIDE)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef ccPlayerMain* (__fastcall* funct)(unsigned int PLAYER_SIDE);
			funct fc = (funct)(moduleBase + 0xAC3D70);
			return fc(PLAYER_SIDE);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef ccPlayerMain* (__fastcall* funct)(unsigned int PLAYER_SIDE);
			funct fc = (funct)(moduleBase + 0x85A948);
			return fc(PLAYER_SIDE);
		}


	}
	static __int64 GetEnemyPointerAddress;
	static __int64 __fastcall GetEnemyPointer(__int64 player_ptr) {
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<__int64(__fastcall*)(__int64 player_ptr)>(GetEnemyPointerAddress)(player_ptr);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(__int64 player_ptr)>(moduleBase + 0x79ADCC)(player_ptr);
		}
	}

	static __int64 __fastcall GetPlayerContainer(unsigned int PLAYER_SIDE)
	{
		__int64 duel = Game::ObjectList_GetInstanceDuel();
		if (duel <= 0) return 0;

		__int64 a = (duel)+0x20;
		a = *(__int64*)a;
		if (a <= 0) return 0;

		a = a + (PLAYER_SIDE * 0x90);

		return a;
	}

	static __int64 __fastcall ccGame_GetPlayerRole(unsigned int PLAYER_SIDE, unsigned int PLAYER_ROLE)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<__int64(__fastcall*)(unsigned int PLAYER_SIDE, unsigned int PLAYER_ROLE)>(moduleBase + 0xAC3DA0)(PLAYER_SIDE, PLAYER_ROLE);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(unsigned int PLAYER_SIDE, unsigned int PLAYER_ROLE)>(moduleBase + 0x85A888)(PLAYER_SIDE, PLAYER_ROLE);
		}
	}
};


class FrameworkHelpers
{
public:
	static ccCmnScreenManager* GetCmnScreenManager()
	{
		ccCmnScreenManager* cmn = nullptr;

		ccCmnScreenManager* cmnScreenManager = Game::GetCmnScreenManager();
		if (cmnScreenManager) cmn = (ccCmnScreenManager*)cmnScreenManager;

		return cmn;
	}

	static ccCmnCameraDirector* GetCameraDirector()
	{
		ccCmnCameraDirector* cd = nullptr;
		ccCmnScreenManager* cmn = GetCmnScreenManager();

		if (cmn)
		{
			cd = (ccCmnCameraDirector*)(ccCmnScreenManager::GetCameraDirector((ccCmnScreenManager*)cmn, 0));
		}

		return cd;
	}

	static ccCmnCamera* GetActiveCamera()
	{
		ccCmnCamera* c = nullptr;
		ccCmnCameraDirector* cd = GetCameraDirector();

		if (cd)
		{
			c = (ccCmnCamera*)(ccCmnCameraDirector::GetActiveCamera(cd));
		}

		return c;
	}

	static __int64 __fastcall UpdateAnmCamNOP(__int64 a1)
	{
		return *(__int64*)(a1 + 432);
	}

	static __int64 __fastcall DisableCameraMovementHook(__int64 a1, Vector3* a2, Vector3* a3, Vector3* a4)
	{
		return 0;
	}

	static void EnableCameraMovement()
	{
		__int64 player_ptr = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
		__int64 enemy_ptr = (__int64)BattleUtils::ccGame_GetPlayerLeader(1);
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			*(int*)(player_ptr + 0xC7B0) = 1;
			*(int*)(enemy_ptr + 0xC7B0) = 1;

			// 4C 8B DC 55 57 49 8D AB  68 FF FF FF 48 81 EC 88 01 00 00
			char restore[15] = { 0x48, 0x8b, 0xc4, 0x48, 0x89, 0x58, 0x08, 0x48, 0x89, 0x70, 0x10, 0x48, 0x89, 0x78, 0x18 };
			char restore2[5] = { 0xF3, 0x0F, 0x11, 0x77, 0x6C };
			__int64 vtable_originalOperatorAnm = moduleBase + 0xAB5870;

			DWORD dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0x1072010), 15, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0x1072010), &restore[0], 15);
			VirtualProtect((void*)(moduleBase + 0x1072010), 15, dwOld, &dwOld);

			// NOP FOV
			dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0x92B82E), 5, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0x92B82E), &restore2[0], 5);
			VirtualProtect((void*)(moduleBase + 0x92B82E), 5, dwOld, &dwOld);

			// Enable Cam Anm Operator
			ReplaceVirtualFunction(0x14195F240, (void*)vtable_originalOperatorAnm);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			*(int*)(player_ptr + 0xFCCC) = 1;
			*(int*)(enemy_ptr + 0xFCCC) = 1;


			// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18
			char restore[15] = { 0x48, 0x8b, 0xc4, 0x48, 0x89, 0x58, 0x08, 0x48, 0x89, 0x70, 0x10, 0x48, 0x89, 0x78, 0x18 };
			char restore2[5] = { 0xF3, 0x0F, 0x11, 0x77, 0x6C };
			__int64 vtable_originalOperatorAnm = moduleBase + 0x8540EC;

			DWORD dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0xAC7990), 15, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0xAC7990), &restore[0], 15);
			VirtualProtect((void*)(moduleBase + 0xAC7990), 15, dwOld, &dwOld);

			// NOP FOV
			dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0x743420), 5, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0x743420), &restore2[0], 5);
			VirtualProtect((void*)(moduleBase + 0x743420), 5, dwOld, &dwOld);

			// Enable Cam Anm Operator
			ReplaceVirtualFunction(0x1410E8B68, (void*)vtable_originalOperatorAnm);
		}

		
	}

	static void DisableCameraMovement()
	{
		__int64 player_ptr = (__int64)BattleUtils::ccGame_GetPlayerLeader(0);
		__int64 enemy_ptr = (__int64)BattleUtils::ccGame_GetPlayerLeader(1);
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			if (player_ptr && enemy_ptr) {

				*(int*)(player_ptr + 0xC7B0) = 0;
				*(int*)(enemy_ptr + 0xC7B0) = 0;
			}
			HookFunctions::Hook((void*)(moduleBase + 0x1072010), DisableCameraMovementHook, 15);

			char nop[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

			// NOP FOV
			DWORD dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0x92B82E), 5, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0x92B82E), &nop[0], 5);
			VirtualProtect((void*)(moduleBase + 0x92B82E), 5, dwOld, &dwOld);

			// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18

			// Disable Cam Anm Operator
			ReplaceVirtualFunction(0x14195F240, UpdateAnmCamNOP);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			if (player_ptr && enemy_ptr) {

				*(int*)(player_ptr + 0xFCCC) = 0;
				*(int*)(enemy_ptr + 0xFCCC) = 0;
			}

			HookFunctions::Hook((void*)(moduleBase + 0xAC7990), DisableCameraMovementHook, 15);

			char nop[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };

			// NOP FOV
			DWORD dwOld = 0;
			VirtualProtect((void*)(moduleBase + 0x743420), 5, PAGE_EXECUTE_READWRITE, &dwOld);
			memcpy((void*)(moduleBase + 0x743420), &nop[0], 5);
			VirtualProtect((void*)(moduleBase + 0x743420), 5, dwOld, &dwOld);

			// 48 8B C4 48 89 58 08 48 89 70 10 48 89 78 18

			// Disable Cam Anm Operator
			ReplaceVirtualFunction(0x1410E8B68, UpdateAnmCamNOP);
		}
		
	}

	
	static __int64 __fastcall WaitVSync(__int64 a1)
	{
		Sleep(1);
		return 0;
	}

	static void ReplaceVirtualFunction(__int64 original_140000000, void* funct)
	{
		__int64* a = (__int64*)(moduleBase - 0xC00 + original_140000000 - 0x140000000);

		DWORD dwOld = 0;
		VirtualProtect((void*)(a), 8, PAGE_EXECUTE_READWRITE, &dwOld);

		*a = (__int64)funct;
		std::cout << "Replaced vfunct at " << std::hex << (__int64)a << std::endl;

		VirtualProtect((void*)(a), 8, dwOld, &dwOld);
	}

	
};
