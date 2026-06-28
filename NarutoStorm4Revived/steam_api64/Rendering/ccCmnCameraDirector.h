#pragma once
#include "ccCmnCamera.h"
#include "Common.h"

class ccCmnCameraDirector
{
public:
	int m_unk;
	int m_unk1;
	int m_unk2;
	int actualCamera;

	static ccCmnCamera* __fastcall GetCamera(ccCmnCameraDirector* cameraDirector, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, unsigned int a2);
			funct fc = (funct)(moduleBase + 0x1093E50);
			return (ccCmnCamera*)fc(cameraDirector, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, unsigned int a2);
			funct fc = (funct)(moduleBase + 0xAB9860);
			return (ccCmnCamera*)fc(cameraDirector, a2);
		}

	}

	static ccCmnCamera* __fastcall GetActiveCamera(ccCmnCameraDirector* cameraDirector)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector);
			funct fc = (funct)(moduleBase + 0x1093E10);
			return (ccCmnCamera*)fc(cameraDirector);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector);
			funct fc = (funct)(moduleBase + 0xAB9880);
			return (ccCmnCamera*)fc(cameraDirector);
		}
		
	}

	static __int64 __fastcall ChangeCamera(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3)
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0x10937D0);
			return fc(cameraDirector, a2, a3);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0xAB9D10);
			return fc(cameraDirector, a2, a3);
		}


	}

	static __int64 __fastcall ChangeCameraImmediate(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0x1093800);
			return fc(cameraDirector, a2, a3);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, int a2, unsigned int a3);
			funct fc = (funct)(moduleBase + 0xAB9D50);
			return fc(cameraDirector, a2, a3);
		}
	}

	static __int64 __fastcall EntryCameraOperator(ccCmnCameraDirector* cameraDirector, unsigned int a2, __int64 cameraOperator)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, unsigned int a2, __int64 cameraOperator);
			funct fc = (funct)(moduleBase + 0x1093DF0);
			return fc(cameraDirector, a2, cameraOperator);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector, unsigned int a2, __int64 cameraOperator);
			funct fc = (funct)(moduleBase + 0xAB98A0);
			return fc(cameraDirector, a2, cameraOperator);
		}
	}

	static __int64 __fastcall ClearAllCameraOperator(ccCmnCameraDirector* cameraDirector)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector);
			funct fc = (funct)(moduleBase + 0x1093930);
			return fc(cameraDirector);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCameraDirector* cameraDirector);
			funct fc = (funct)(moduleBase + 0xAB96F0);
			return fc(cameraDirector);
		}
		
	}

	static __int64 __fastcall GetCameraOperator(ccCmnCameraDirector* a1, unsigned int a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(ccCmnCameraDirector * a1, unsigned int a2)>(moduleBase + 0x1093E90)(a1, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			return reinterpret_cast<__int64(__fastcall*)(ccCmnCameraDirector * a1, unsigned int a2)>(moduleBase + 0xAB9AD0)(a1, a2);
		}
	}
};