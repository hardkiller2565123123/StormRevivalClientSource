#include "Common.h"

class ccSceneManager
{
public:

	static ccSceneManager* GetInstance() // For permanent objects
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			return (ccSceneManager*)*((__int64*)(moduleBase + 0x1422FB988 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return (ccSceneManager*)*((__int64*)(moduleBase + 0x1416BDA18 - 0x140000C00));
		}
	}

	static __int64 __fastcall Push(ccSceneManager* sceneManager, unsigned int s)
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager, unsigned int s);
			funct fc = (funct)(moduleBase + 0x10764B0);
			return fc(sceneManager, s);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager, unsigned int s);
			funct fc = (funct)(moduleBase + 0xAB4D20);
			return fc(sceneManager, s);
		}

	}

	static __int64 __fastcall Pop(ccSceneManager* sceneManager)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0x1075FA0);
			return fc(sceneManager);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0xAB5020);
			return fc(sceneManager);
		}
		
	}

	static __int64 __fastcall PopAll(ccSceneManager* sceneManager)
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0x1076080);
			return fc(sceneManager);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0xAB5410);
			return fc(sceneManager);
		}

		
	}

	static __int64 __fastcall Execute(ccSceneManager* sceneManager)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0x1075C50);
			return fc(sceneManager);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* sceneManager);
			funct fc = (funct)(moduleBase + 0xAB4C10);
			return fc(sceneManager);
		}
		
	}

	static void __fastcall Change(ccSceneManager* sceneManager, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef void(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0x10750D0);
			fc(sceneManager, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef void(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0xAB54D0);
			fc(sceneManager, a2);
		}
		
	}

	static __int64 __fastcall PushPromptly(ccSceneManager* sceneManager, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0x1076640);
			return fc(sceneManager, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0xAB4EA0);
			return fc(sceneManager, a2);
		}
		
	}

	static __int64 __fastcall PopTo(ccSceneManager* sceneManager, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0x10762B0);
			return fc(sceneManager, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0xAB52C0);
			return fc(sceneManager, a2);
		}
		
	}

	static __int64 __fastcall SearchSceneRank(ccSceneManager* sceneManager, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0x1076EA0);
			return fc(sceneManager, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccSceneManager* a1, unsigned int a2);
			funct fc = (funct)(moduleBase + 0xAB5B00);
			return fc(sceneManager, a2);
		}
	}
	static __int64 __fastcall EntryCreateSceneCommand(ccSceneManager* sceneManager, int sceneName, int sceneNumber)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			typedef __int64(__fastcall* funct)(ccSceneManager* a1, int a2, __int64 a3);
			funct fc = (funct)(moduleBase + 0x1075A50);
			return fc(sceneManager, sceneName, sceneNumber);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccSceneManager* a1, int a2, __int64 a3);
			funct fc = (funct)(moduleBase + 0xaB57D0);
			return fc(sceneManager, sceneName, sceneNumber);
		}
	}
	static __int64 __fastcall EntryCreateSceneCommandJump(ccSceneManager* sceneManager, char* sceneName, int sceneNumber, __int64 sceneAddress)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			__int64 v4; // rcx
			char v5; // al
			__int64 v7; // [rsp+20h] [rbp-98h] BYREF
			char v8[144]; // [rsp+28h] [rbp-90h] BYREF

			v7 = sceneAddress;
			v4 = v8 - sceneName;
			do
			{
				v5 = *sceneName;
				sceneName[v4] = *sceneName;
				++sceneName;
			} while (v5);


			return ccSceneManager::EntryCreateSceneCommand(sceneManager, sceneNumber, (__int64)&v7);

		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(ccSceneManager * sceneManager, const char* sceneName, int sceneNumber, __int64 sceneAddress)>(moduleBase + 0x6E436C)(sceneManager, sceneName, sceneNumber, sceneAddress);

		}
	}

	static __int64 __fastcall GetCurrentSceneKey(ccSceneManager* a1)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {


			return reinterpret_cast<__int64(__fastcall*)(ccSceneManager * a1)>(moduleBase + 0x1075E40)(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(ccSceneManager * a1)>(moduleBase + 0xAB5A70)(a1);
		}
	}

	static const char* GetSceneNameByKey(__int64 sceneList, int totalSceneCount, int sceneKey)
	{
		int sceneIndexInList = -1;

		for (int x = 0; x < totalSceneCount; x++)
		{
			if (*(int*)(sceneList + 0x90 * x) == sceneKey)
			{
				sceneIndexInList = x;
				x = totalSceneCount;
				break;
			}
		}

		const char* sceneName = "[null]";

		if (sceneIndexInList != -1)
		{
			sceneName = (const char*)((sceneList + 0x10) + (0x90 * sceneIndexInList));
		}

		return sceneName;
	}
};
