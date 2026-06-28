#include <windows.h>
#include <cstdint>
#include <cstring>
#include "Common.h"
#include "Offsets.h"
#include "PatternScan.h"
#include <iostream>
#include <cstdio>
#include <Psapi.h>
#include "SpecialConditionParam.h"
#include "FileParser.h"
#include "Console.h"
#include "MovesetPlus.h"
void SpecialCondParam::ReadSpecialConditionParam(std::string _file)
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

		//  :   
		std::string key = slotType;
		for (size_t i = 0; i < key.size(); ++i) key[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(key[i])));
		//    COND_, 
		if (key.rfind("COND_", 0) != 0) key = "COND_" + key;

		static const char* names[] = {
			"COND_1CMN","COND_2NRT","COND_2NRX","COND_2SSK","COND_2SSY","COND_2SKR","COND_2ROC","COND_2NEJ","COND_2TEN","COND_2INO","COND_2SIK","COND_2TYO","COND_2KIB","COND_2SIN","COND_2HNT","COND_2GAR",
			"COND_2KNK","COND_2TMR","COND_2KKS","COND_2GUY","COND_2ASM","COND_2JRY","COND_2TND","COND_2ORC","COND_2KBT","COND_2ITC","COND_2KSM","COND_2CYB","COND_2SAI","COND_2YMT","COND_2SCO","COND_2DDR",
			"COND_2HDN","COND_2KZU","COND_2SGT","COND_2JUG","COND_2KAR","COND_2TOB","COND_2KNN","COND_2PEA","COND_2KLB","COND_2AKM","COND_2KRS","COND_2PAR","COND_2KKG","COND_2FOU",
			"COND_1NRT","COND_1SSK","COND_1SKR","COND_1ROC","COND_1NEJ","COND_1HNT","COND_1GAR","COND_1HKG","COND_1KMM",
			"COND_2NRG","COND_2SSZ","COND_2MDR","COND_2DNZ","COND_2RKG","COND_2TKG","COND_2MKG",
			"COND_1ZBZ","COND_1HAK","COND_1FIR","COND_1SEC","COND_2KKX","COND_2OBT","COND_2KBX","COND_2SCX",
			"COND_3MDR","COND_3DRI","COND_3RUS","COND_3TOB","COND_3YGR","COND_3UTK","COND_3MFN","COND_3HAN","COND_3NYG","COND_3WHO","COND_3KLB","COND_3HNZ","COND_3NGT","COND_3TYO","COND_3NRT","COND_3SSK","COND_3GAR",
			"COND_4MKG","COND_4MUU","COND_4RKG","COND_4KKG","COND_3KKS","COND_3KHM","COND_3IRK","COND_3KBT","COND_3OBT","COND_4SSI",
			"COND_1TEN","COND_1INO","COND_1SIK","COND_1TYO","COND_1KIB","COND_1AKM","COND_1SIN","COND_1TMR","COND_1KNK","COND_1KRS",
			"COND_4NRT","COND_3KSN","COND_3MNT","COND_3HSM","COND_3MDR_2","COND_2GAV",
			"COND_5OBT","COND_5MDR","COND_5JRB","COND_5KDM","COND_5SKN","COND_5TYY",
			"COND_BHSM","COND_BMDR","COND_BMKJ","COND_4RIN","COND_6NRT","COND_5KGY","COND_TYYP","COND_6SSK","COND_6HNT","COND_6SKR","COND_5NRT","COND_5SSK","COND_6HNB",
			"COND_2OBX","COND_BJB1","COND_BJB2","COND_BJB3","COND_BJB4","COND_B4NR","COND_BKKX","COND_B5OB","COND_BKRL","COND_BSSN","COND_BOBT","COND_BGKT","COND_BAOD","COND_BKTY","COND_B2NR",
			"COND_1JBR","COND_2JBR","COND_3JBR","COND_4JBR","COND_5JBR","COND_6JBR",
			"COND_GFSA","COND_BJYD","COND_BKRS","COND_GMHR","COND_BTSK","COND_BKKU","COND_7BRT","COND_7SLD","COND_BGRG","COND_GZTU","COND_BOBR","COND_BOBS","COND_BMDJ","COND_BRMD","COND_BRSK","COND_BKMS","COND_BKSR","COND_BGYU","COND_BJYG","COND_BNRT","COND_BSSK","COND_BKGY","COND_BOBZ","COND_BKGV","COND_BKKK",
			"COND_BNRX","COND_BSSX","COND_BNRC","COND_BSSC","COND_JKKS","COND_BOBK","COND_5KRS","COND_B6BT","COND_BKKS","COND_BMDT","COND_BMDK","COND_BMHR","COND_7NRT","COND_7SSK","COND_BNRG","COND_BSSZ","COND_B1NR","COND_B1SS",
			"COND_3GUY","COND_B3HS","COND_BGUY","COND_BGRN","COND_7NRN","COND_7SSX","COND_7SKR","COND_7GAR","COND_7KHM","COND_7BRN","COND_7BRX","COND_7SLN","COND_7SKD","COND_7MMS","COND_7KIN","COND_7YRI","COND_4MNR",
			"COND_BISS","COND_BMNK","COND_7MMV","COND_7MTK","COND_ABRT","COND_8MMS","COND_8KIN","COND_8INO","COND_8SIK","COND_8TYO","COND_8KIB","COND_8SIN","COND_8ROC","COND_8TEN","COND_8KNK","COND_8TMR","COND_8SAI","COND_8AEM",
			"COND_9IND","COND_9ASR","COND_9NRT","COND_8BRA","COND_9KWK","COND_9JGN","COND_9KKJ","COND_9DLT","COND_9BOR","COND_8MTA","COND_8SSF","COND_BNNS","COND_1SSV","COND_1NRV","COND_BMRA","COND_BMRK","COND_BMRL","COND_BBRB","COND_BNSP","COND_BSSP","COND_BSKK","COND_BNRY","COND_BPEI","COND_B3NX","COND_B8KB","COND_B8IT","COND_8NNA","COND_8TGS","COND_8NRE","COND_8HMW","COND_BNRK","COND_BNRM","COND_7DRI",
			"COND_BUCA","COND_BUCB","COND_BUCC","COND_B2KK","COND_8KLB","COND_8NNC","COND_BITC","COND_8NRK","COND_8KKL","COND_8KTS","COND_8INJ","COND_9HGR","COND_9ISH","COND_9KRN","COND_9KWM","COND_9BRM"
		};

		const size_t namesCount = sizeof(names) / sizeof(names[0]);

		int condFunct = 0x0;
		int found = -1;
		for (size_t i = 0; i < namesCount; ++i) {
			//    (names[i]    )
			const char* n = names[i];
			size_t j = 0;
			bool eq = true;
			for (;;) {
				char a = (j < key.size()) ? key[j] : '\0';
				char b = n[j];
				if (b == '\0') { if (a != '\0') eq = false; break; }
				if (a != b) { eq = false; break; }
				++j;
			}
			if (eq) { found = static_cast<int>(i); break; }
		}

		if (found >= 0) condFunct = static_cast<uint32_t>(found);
		else condFunct = -1;

		//    (2  little-endian,    )
		condCharacter = (static_cast<int>(fileBytes[actual]) & 0xFF) | ((static_cast<int>(fileBytes[actual + 1]) & 0xFF) << 8);

		if (condFunct > -1) {
			
			auto it = std::find(charcodes.begin(), charcodes.end(), condCharacter);
			if (it != charcodes.end()) {
				size_t pos = std::distance(charcodes.begin(), it);
				int oldFunct = charfunction[pos];
				charfunction[pos] = condFunct;

				Console::PrintOut(
					"Replaced existing charcode 0x%X: %s (%d) -> %s (%d)\n",
					static_cast<unsigned int>(pos),
					names[oldFunct], oldFunct,
					names[condFunct], condFunct
				);
			}
			else {
				Console::PrintOut(
					"Added special Condition Entry for charcode 0x%X: %s (%d)\n",
					condCharacter,
					names[condFunct], condFunct
				);
				charfunction.push_back(condFunct);
				charcodes.push_back(condCharacter);
			}
		}

	}
}
void Call_LoadUiTable_BOSS()
{
	typedef void(__fastcall* fn_LoadUiTable)(__int64* a1, __int64 a2, __int64* a3);
	//   , : *(_QWORD *)&qword_14219D7E0
	__int64 baseQword = Common::GetQword(0x14219D7E0);

	if (!baseQword)
		return;

	// temp = *(_QWORD *)(baseQword + 504i64)
	__int64 temp = *reinterpret_cast<__int64*>(baseQword + 504);

	// arg0 = temp + 96i64
	__int64 arg0 = temp + 96;

	// table name       
	__int64 tableName = reinterpret_cast<__int64>("BOSS_BATTLE_CMN_FLASH");
	__int64* entries = reinterpret_cast<__int64*>(Common::GetQwordPtr(0x141F9F540));

	__int64 tableName2 = reinterpret_cast<__int64>("LOAD_BOSS01_ALL_Flash");
	__int64* entries2 = reinterpret_cast<__int64*>(Common::GetQwordPtr(0x141F543F8));

	//   (      ,    )
	fn_LoadUiTable fn = reinterpret_cast<fn_LoadUiTable>(moduleBase+0x4AB230);

	// 
	fn(reinterpret_cast<__int64*>(arg0), tableName, entries);
	fn(reinterpret_cast<__int64*>(arg0), tableName2, entries2);


	Console::PrintErr("Worked Fine\n");
}
__int64* __fastcall SpecialCondParam::Create(int characterNum, int a2) {

	MovesetPlus::BGM_ID = 0;
	MovesetPlus::cancelUpgradeFunctionState[0] = 0;
	MovesetPlus::cancelUpgradeFunctionState[1] = 0;
	render::hudon = 2;
	render::pause = 0;
	MovesetPlus::PUCCI_AWA_COUNT[0] = 0;
	MovesetPlus::PUCCI_AWA_COUNT[1] = 0;
	MovesetPlus::CHARACODE[0] = "DUMMY";
	MovesetPlus::CHARACODE[1] = "DUMMY";


	if (Common::GetQword(0x14161C8C0) != 0)
	{
		*reinterpret_cast<std::uint32_t*>(
			reinterpret_cast<std::uint8_t*>(Common::GetQword(0x14161C8C0)) + 124) = 1u;
	}

	for (int x = 0; x < charcodes.size(); x++) {
		if (characterNum == charcodes.at(x)) {

			//Console::PrintOut("Create called: char=%d\n", characterNum);
			return co(charfunction.at(x), a2);
		}
	}
	return co(characterNum, a2);

}
int* __fastcall SpecialCondParam::Create_NSC(int characterNum, int a2) {

	MovesetPlus::BGM_ID = 0;
	MovesetPlus::cancelUpgradeFunctionState[0] = 0;
	MovesetPlus::cancelUpgradeFunctionState[1] = 0;
	render::hudon = 2;
	render::pause = 0;
	render::timer_speed = 1.0f;
	MovesetPlus::PUCCI_AWA_COUNT[0] = 0;
	MovesetPlus::PUCCI_AWA_COUNT[1] = 0;
	MovesetPlus::CHARACODE[0] = "DUMMY";
	MovesetPlus::CHARACODE[1] = "DUMMY";

	if (Common::GetQword(0x14219D810) != 0)
	{
		*reinterpret_cast<std::uint32_t*>(
			reinterpret_cast<std::uint8_t*>(Common::GetQword(0x14219D810)) + 124) = 1u;
	}


	for (int x = 0; x < charcodes.size(); x++) {
		if (characterNum == charcodes.at(x)) {

			return co_nsc(charfunction.at(x), a2);
		}
	}
	return co_nsc(characterNum, a2);

}