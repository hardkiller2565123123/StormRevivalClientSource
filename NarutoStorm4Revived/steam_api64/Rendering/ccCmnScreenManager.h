#pragma once
#include "ccCmnCameraDirector.h"
#include "Common.h"

class ccCmnScreenManager
{
public:
	static ccCmnScreenManager* GetInstance()
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			// 142198F00
			return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x142198F00 - 0x140000C00));
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			// 14161C780
			return (ccCmnScreenManager*)*((__int64*)(moduleBase + 0x14161C780 - 0x140000C00)); 
		}
	}

	static ccCmnCameraDirector* __fastcall GetCameraDirector(ccCmnScreenManager* cmnscreenmanager, int id)
	{
		if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnScreenManager* a1, int id);
			funct fc = (funct)(moduleBase + 0x1092C90);
			return (ccCmnCameraDirector*)fc(cmnscreenmanager, id);
		}
		else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) {
			typedef __int64(__fastcall* funct)(ccCmnScreenManager* a1, int id);
			funct fc = (funct)(moduleBase + 0xAB3C30);
			return (ccCmnCameraDirector*)fc(cmnscreenmanager, id);
		}
		
	}
};