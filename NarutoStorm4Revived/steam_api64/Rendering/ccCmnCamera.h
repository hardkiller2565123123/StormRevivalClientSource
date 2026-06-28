#pragma once
#include "Vector3.h"
#include "Common.h"
#include "Console.h"


#include <cmath>
#include <cstring>

class ccCmnCamera
{
public:
	__int64 m_vtable; // 0x00 to 0x08
	char padding0[0x24]; // 0x08 to 0x2C
	float m_fov; // 0x2C to 0x30
	char padding1[0x0C]; // 0x30 to 0x3C
	float m_internalPosX; // 0x3C to 0x40
	char padding2[0x0C]; // 0x40 to 0x4C
	float m_internalPosY; // 0x4C to 0x50
	char padding3[0x0C]; // 0x50 to 0x5C
	float m_internalPosZ; // 0x5C to 0x60
	char padding4[0x10]; // 0x60 to 0x70
	Vector3 m_position; // 0x70 to 0x7C
	Vector3 m_look; // 0x7C to 0x88
	float m_tilt_unk; // 0x88 to 0x8C
	Vector3 m_tilt; // 0x8C to 0x98

	static __int64 __fastcall Init(ccCmnCamera* a1)
	{

		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCamera* a1);
			funct fc = (funct)(moduleBase + 0x1071850);
			return fc(a1);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCamera* a1);
			funct fc = (funct)(moduleBase + 0xAC7650); //S4
			return fc(a1);
		}

	}

	static __int64 __fastcall SetCameraPosNew(ccCmnCamera* a1, Vector3* a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0x10722C0);//SC
			return fc(a1, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {

			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0xAC7810); //S4
			return fc(a1, a2);
		}
	}

	static __int64 __fastcall SetCameraLookAtPosNew(ccCmnCamera* a1, Vector3* a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0x1072310);//SC
			return fc(a1, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0xAC7830); //S4
			return fc(a1, a2);
		}
		
	}

	static __int64 __fastcall SetCameraUpDirecNew(ccCmnCamera* a1, Vector3* a2)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0x10723D0);//SC
			return fc(a1, a2);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnCamera* a1, Vector3* a2);
			funct fc = (funct)(moduleBase + 0xAC7850);//S4
			return fc(a1, a2);
		}
	}

	static __int64 __fastcall Update(ccCmnCamera* cam)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			return reinterpret_cast<__int64(__fastcall*)(ccCmnCamera * cam)>(moduleBase + 0x10723F0)(cam);//SC
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			return reinterpret_cast<__int64(__fastcall*)(ccCmnCamera * cam)>(moduleBase + 0xAC76E0)(cam); //s4
		}
	}

	
};


