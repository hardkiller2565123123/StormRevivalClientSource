#include <vector>
#include "FileParser.h"
#include "SusanooCondParam.h"
#include "Console.h"

int __fastcall ns4::player::susanoojumps4(__int64 a1)
{
	int characode = *(DWORD*)(a1 + 0xC8C);
	int charindex = NULL;
	for (int i = 0; i < charlist.size(); i++) {
		if (characode == charlist[i])
			charindex = i;
	}
	if (charindex == NULL)
		return osusanoojump(a1);
	else {
		*(DWORD*)(a1 + 0xC8C) = susanoocharlist[charindex];
		auto retval = osusanoojump(a1);
		*(DWORD*)(a1 + 0xC8C) = charlist[charindex];
		return retval;
	}
}

int __fastcall nsc::player::susanoojumpnsc(__int64 a1)
{
	int characode = *(DWORD*)(a1 + 0xE64);
	int charindex = NULL;
	for (int i = 0; i < charlist.size(); i++) {
		if (characode == charlist[i])
			charindex = i;
	}
	if (charindex == NULL)
		return osusanoojump(a1);
	else {
		*(DWORD*)(a1 + 0xE64) = susanoocharlist[charindex];
		auto retval = osusanoojump(a1);
		*(DWORD*)(a1 + 0xE64) = charlist[charindex];
		return retval;
	}
}


void SusanooCondManager::ReadSusanooCondParam(std::string _file)
{
	std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		std::string slotType = "";
		int condCharacter = 0;
		int actual = (0x20 * x);

		while (actual < (0x20 * x) + 0x18)
		{
			if (fileBytes[actual] != 0x0)
			{
				slotType = slotType + (char)fileBytes[actual];
				actual++;
			}
			else
			{
				actual = (0x20 * x) + 0x18;
			}
		}

		condCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);
		//cout << "stuff: " << std::hex << (uintptr_t)fileBytes[actual] << " " << (uintptr_t)fileBytes[actual + 1] << endl;

		int susanoochar = 0;
		if (slotType == "SSN_2ITC") susanoochar = 0x19;
		else if (slotType == "SSN_2SSZ") susanoochar = 0x38;
		else if (slotType == "SSN_3SSK") susanoochar = 0x55;
		else if (slotType == "SSN_4SSI") susanoochar = 0x60;
		else if (slotType == "SSN_BSSZ") susanoochar = 0xC1;

		Console::PrintOut("SusanooCondParam :: Added entry for 0x%X characode with slot type %s.\n", condCharacter, slotType);

		ns4::susanoocharlist.push_back(susanoochar);
		ns4::charlist.push_back(condCharacter);
		nsc::susanoocharlist.push_back(susanoochar);
		nsc::charlist.push_back(condCharacter);

	}
}