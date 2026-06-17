#include <stdio.h>
#include <iostream>
#include <string>

#include <WinSock2.h>
#include <Windows.h>

#include "Common.h"
#include "HookFunctions.h"
#include "PatternScan.h"
#include "PluginManager.h"
#include "DirectX.h"
#include "TeamUltimateJutsuManager.h"
#include "UltimateStormAPI.h"
#include "MinHook.h"
#include "Console.h"
#include "ConditionPrmManager.h"
#include "mem.h"
#include "SusanooCondParam.h"
#include "ModManager.h"
#include "SpecialInteractionManager.h"
#include "SpecialConditionParam.h"
#include "Utilities.h"
#include "PartnerSlotParam.h"
#include "MovesetPlus.h"
#include <array>
#include "FileParser.h"
#include "ProjectileManager.h"
#include "ProjectileManager.cpp"
#include "GudoBallParam.h"
#include "OugiAwakeningParam.h"
#include "GuardEffectParam.h"
#include "EditorGUI.h"
#include "LuaScripts.h"

using namespace std;

__int64 BattleUtils::GetEnemyPointerAddress = 0;

// This is used to hook game functions with your own (you can replace original functions and add your own code to them)
void HookFunctions::InitializeHooksAll()
{
	__int64 debug_str_address_NS4Debug = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx4Cxxxxxx4Cxxxxxx535748xxxxxxxxxxxx48xxxx48xxxxxxxx33xx41xxxxxxxxxx48xxxxxxE8xxxxxxxx");
	if (GetPrivateProfileInt("General", "enable_debug", 1, config_path.c_str()) == 1 && debug_str_address_NS4Debug > 1)
	{
		Console::PrintOutW("UltimateStormAPI:: Found Debug Strings S4\n");
		HookFunctions::Hook((void*)(debug_str_address_NS4Debug), Common::DebugString, 15);
	}
	BattleUtils::GetEnemyPointerAddress = PatternScan::Scan("40xx48xxxxxx48xxxx33xxFFxxxx3Bxxxxxxxxxx74xx48xxxxxxxxxxxx");
	
	

	Console::PrintErr("Filter pointer %p\n",Game::ObjectList_GetPtrLightsAndFog());

	Console::PrintErr("Light and Shadow pointer %p\n", Game::ObjectList_GetPtrLightsAndShadow());
	//// Partner function
	//__int64 partnerFunctionAddress = PatternScan::Scan("33xx48xxxxxxxxxxxx3Bxx74xx4Cxxxxxxxxxxxx48xxxxxxFFxx49xxxx7Cxx");
	//if (partnerFunctionAddress > 1) HookFunctions::Hook((void*)(partnerFunctionAddress), PartnerManager::CreatePartner, 20);

	// Initialize plugin hooks
	InitializePluginHooks();
}// This is used to hook game functions with your own (you can replace original functions and add your own code to them)


void CopyFunctionPointer(uint64_t srcAddr, uint64_t dstAddr)
{

	uint64_t funcPtr = *(uint64_t*)srcAddr;

	DWORD oldProtect;
	VirtualProtect((LPVOID)dstAddr, sizeof(uint64_t), PAGE_EXECUTE_READWRITE, &oldProtect);

	*(uint64_t*)dstAddr = funcPtr;

	VirtualProtect((LPVOID)dstAddr, sizeof(uint64_t), oldProtect, &oldProtect);
}

void HookFunctions::InitializeHooksS4()
{
	__int64 MotionBlurAddress = moduleBase + 0xA6EFD0;
	if (MotionBlurAddress > 1) {
		Console::PrintOut("UltimateStormAPI:: Motion blur Hooked\n");

		struct Patch {
			const char* pattern;
			int offset;
			std::array<std::uint8_t, 1> bytes; // : std::array,   { }
		};

		const Patch patches[] = {
			{ "41xxE02Bxxxx",   2, { 0xD8 } },
		};

		for (const auto& p : patches) {
			__int64 addr = PatternScan::Scan(p.pattern, MotionBlurAddress);
			if (addr > 1) {
				util::memory::mem::write_bytes(addr + p.offset, p.bytes);
			}
		}
	}
	//Conditions
	Console::PrintOut("UltimateStormAPI:: Creating Conditions\n");
	plugin::hookfunc(moduleBase+0x7C5334, SpecialCondParam::Create, (LPVOID*)&co);

	//Partners
	Console::PrintOut("UltimateStormAPI:: Creating Partners\n");
	HookFunctions::Hook((void*)(moduleBase + 0x7F0454), PartnerSlotParam::CreatePartner, 14);
	//Condition PRM
	__int64 conditionprmAddress = PatternScan::Scan("8Dxxxx3DDA01000077xx48xxxx48xxxxxxxxxxxx48xxxxxx48xxxxC333xxC3");
	if (conditionprmAddress > 1) {
		Console::PrintOut("UltimateStormAPI :: Condition PRM S4 Hooked\n");

		HookFunctions::Hook(
			reinterpret_cast<void*>(conditionprmAddress),
			ConditionPrmManager::GetConditionEntry,
			20
		);

		const auto conditionBytes1 = ToBytes(static_cast<std::uint32_t>(g_ConditionEntries.size() - 1));
		const auto conditionBytes2 = ToBytes(static_cast<std::uint32_t>(g_ConditionEntries.size()));

		// ---    ---
		{
			__int64 addr1 = PatternScan::Scan(
				"4Cxxxxxx4Dxxxx74xx81xxDB01000077xx48xxxx48xxxxxxxxxxxx49xxxxC333xxC3"
			);
			__int64 target = PatternScan::Scan("DB010000", addr1);
			if (target > 1) {
				util::memory::mem::write_bytes(target, conditionBytes1);
			}
		}

		// ---    ---
		{
			__int64 addr2 = PatternScan::Scan(
				"48xxxxxxxx5748xxxxxx8Bxx33xx8BxxE8xxxxxxxx48xxxx74xx48xxxx48xxxx74xx"
				"E8xxxxxxxx3Bxx74xxFFxx81xxDC0100007Cxx"
			);

			//     "DC010000"
			__int64 target = addr2;
			for (int i = 0; i < 3; ++i) {
				target = PatternScan::Scan("DC010000", target + (i ? 4 : 0));
				if (target > 1) {
					util::memory::mem::write_bytes(target, conditionBytes2);
				}
			}
		}
	}
	__int64 susanooAddressS4 = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx555741xx41xx41xx48xxxxxxxx48xxxxxxxxxxxx0Fxxxxxx0Fxxxxxx44xxxxxxxx48xxxx45xxxx48xxxx41xxxxFFxxxxxxxxxx45xxxxxx85xx");
	if (susanooAddressS4 > 1) {
		Console::PrintOutW("SusanooFunction S4 :: Hooked\n");
		plugin::hookfunc(susanooAddressS4, ns4::player::susanoojumps4, (LPVOID*)(&osusanoojump));
	}
	//SpecialInteraction UJ

	HookFunctions::Hook((void*)(moduleBase + 0x77B2C8), SpecialInteractionManager::AdjustSpecialInteractionValue, 15); //UJ interaction
	HookFunctions::Hook((void*)(moduleBase + 0x7D7DEC), SpecialInteractionManager::SpecialInteractionFunction2, 15);

	//Wall Run
	__int64 wallFunctionAdress = moduleBase+0x5944E0;
	Console::PrintOut("WallRunManager :: Hooking Wall Run\n");
	HookFunctions::Hook((void*)(wallFunctionAdress), Common::WallRun, 14);

	// Hide HUD
	__int64 hudon_address1 = PatternScan::Scan("48xxxxxxxx48xxxxxxxx41xx48xxxxxx48xxxx49xxxx0Fxxxxxx");
	Common::hudon_address = moduleBase + 0x8E0783;


	MovesetPlus::VTableAddress = moduleBase + 0xAB6D30;

	// Moveset Plus function
	__int64 movesetPlusFunctionAddress = PatternScan::Scan("48xxxxxx48xxxxFFxxxxxxxxxx48xxxx74xx48xxxx48xxxxFFxxxxxxxxxxB8xxxxxxxx48xxxxxxC3");
	if (movesetPlusFunctionAddress > 1) {

		Console::PrintOutW("MovesetPlus :: Creating Functions\n");
		MovesetPlus::BgmOffFunctionAdress = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxx48xxxxxxxxxxxx48xxxx8BxxE8xxxxxxxx48xxxxxxxxxx"); //73DB8C
		MovesetPlus::BgmOnFunctionAdress = PatternScan::Scan("33xx48xxxxxx39xx74xx48xxxx48xxxxxx48xxxxxx7Cxx33xxC3B8xxxxxxxxC333xx48xxxxxxxxxxxx");//0x73B654
		MovesetPlus::BgmOff2FunctionAdress = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx5748xxxxxx83xxxxxx8Bxx48xxxx75xx48xxxxxxxxxxxx48xxxx74xx49xxxx");//73B6E8


		MovesetPlus::ResolveEffectAddress = moduleBase + 0x784500;
		MovesetPlus::ExecuteEffectAddress = moduleBase + 0x784B9C;

		

		MovesetPlus::HandleStageChangeAddress = moduleBase + 0x721944;
		MovesetPlus::DefaultStageHandlerAddress = moduleBase + 0x5E50EC;
		MovesetPlus::SpecificStageHandlerAddress = moduleBase + 0x5E5110;
		MovesetPlus::FixCharPositionAddress = moduleBase + 0x57F848;
		
		// Address of the target bytes
		__int64 DPadHudAddress = PatternScan::Scan("41xxxx8C0C00007C44xxxxxx");
		void* targetAddress = (void*)(DPadHudAddress + 3); // Adjust offset if necessary

		// Original and new byte sequences
		uint8_t originalBytes[] = { 0x8C, 0x0C, 0x00, 0x00, 0x7C };
		uint8_t newBytes[] = { 0x38, 0x0D, 0x00, 0x00, 0x01 };

		// Replace bytes and monitor changes
		HookFunctions::ReplaceBytes(targetAddress, newBytes, sizeof(newBytes));
		HookFunctions::Hook((void*)(movesetPlusFunctionAddress), MovesetPlus::meTest, 16);

	}
	//Update Cancel Action Function
	__int64 ActionCancelFunctionAdress = moduleBase + 0x7F98C8;
	if (ActionCancelFunctionAdress > 1) {
		Console::PrintOutW("MovesetPlus :: Action Cancel Updated\n");
		HookFunctions::Hook((void*)(ActionCancelFunctionAdress), MovesetPlus::CancelActionFunction, 14);
	}
	//Update Condition Add Param Function
	__int64 ConditionAddParamAdress = moduleBase + 0x7F4450;
	if (ConditionAddParamAdress > 1) {
		cout << "MovesetPlus :: Condition Add Function Updated" << endl;
		HookFunctions::Hook((void*)(ConditionAddParamAdress), MovesetPlus::ApplyStatusEffect, 18);
	}


	//Disable Upgrade Cancellation
	//__int64 upgradeCancelFunctionAdress = moduleBase + 0x796DE8;
	__int64 upgradeCancelFunctionAdress = PatternScan::Scan("40xx48xxxxxx8Bxxxxxxxxxx48xxxx83xxxx83xxxx0Fxxxxxxxxxx8BxxxxxxxxxxE8xxxxxxxx83xxxx");
	if (upgradeCancelFunctionAdress > 1) {
		cout << "MovesetPlus :: Upgrade Cancel Disabled" << endl;


		plugin::hookfunc(upgradeCancelFunctionAdress,
			reinterpret_cast<LPVOID>(&MovesetPlus::EnableUpgradeCancel),
			reinterpret_cast<LPVOID*>(&MovesetPlus::orig_EnableUpgradeCancel));

		__int64 CancelFunctionAdress = moduleBase+0x7F8F10;
		if (CancelFunctionAdress > 1) {
			MovesetPlus::sub_140978B00Adress = moduleBase+0x796E90;

			HookFunctions::Hook((void*)(CancelFunctionAdress), MovesetPlus::Motion_cancel_function, 14);
			cout << "MovesetPlus :: Update Upgrade Cancel Function" << endl;
		}
	}

	//Expend Upgrade Function
	__int64 upgradeFunctionAdress = moduleBase+0x796D34;
	if (upgradeFunctionAdress > 1) {
		cout << "MovesetPlus :: Upgrade Function Expanded" << endl;

		MovesetPlus::sub_14097F1E0Adress = moduleBase + 0x79AE3C;
		MovesetPlus::sub_1405C3970Adress = moduleBase + 0x554714;
		MovesetPlus::sub_1405C7EC0Adress = moduleBase + 0x556AFC;
		MovesetPlus::sub_1405C8F00Adress = moduleBase + 0x55710C;

		MovesetPlus::cancelUpgradeFunctionState[0] = 0;
		MovesetPlus::cancelUpgradeFunctionState[1] = 0;


		cout << "MovesetPlus :: Fix Upgrade Function" << endl; //find sub_1409B94C0 in 1.50 exe and find 114 characode (5mdr). its some switch value
		__int64 fixUpgradeAddress1 = PatternScan::Scan("8B86BC0C0000");
		__int64 fixUpgradeAddress2 = PatternScan::Scan("8B86BC0C0000", fixUpgradeAddress1 + 6);
		const std::array<std::uint8_t, 2> fixUpgradeBytes1{ 0x04, 0x00 };
		util::memory::mem::write_bytes(fixUpgradeAddress2 + 2, fixUpgradeBytes1);


		plugin::hookfunc(upgradeFunctionAdress,
			reinterpret_cast<LPVOID>(&MovesetPlus::UpgradeVerUnlocker),
			reinterpret_cast<LPVOID*>(&MovesetPlus::orig_UpgradeVerUnlocker));
	}


	//Increase Memory Limits sub_140605050 (1.50)
	__int64 MemoryLimitAddress = moduleBase + 0x563F98;
	if (MemoryLimitAddress > 1) {
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Start\n");

		__int64 MemoryLimit1Address = PatternScan::Scan("BD0000A000", MemoryLimitAddress);
		const std::array<std::uint8_t, 4> MemoryLimitBytes1{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit1Address + 1, MemoryLimitBytes1);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Debug %p\n", (void*)MemoryLimit1Address);


		/*__int64 MemoryLimit2Address = PatternScan::Scan("41xx0000A000", MemoryLimit1Address);
		const std::array<std::uint8_t, 4> MemoryLimitBytes2{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit2Address + 2, MemoryLimitBytes2);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase 2 %p\n", (void*)MemoryLimit2Address);*/


		__int64 MemoryLimit3Address = PatternScan::Scan("41xx0000E010", MemoryLimit1Address); //App 270MB -> 800MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes3{ 0x00, 0x00, 0x00, 0x32 };
		util::memory::mem::write_bytes(MemoryLimit3Address + 2, MemoryLimitBytes3);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase App %p\n", (void*)MemoryLimit3Address);


		__int64 MemoryLimit4Address = PatternScan::Scan("48xxxxxxxx0000D007", MemoryLimit3Address); //UI 125MB -> 700MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes4{ 0x00, 0x00, 0xC0, 0x2B };
		util::memory::mem::write_bytes(MemoryLimit4Address + 5, MemoryLimitBytes4);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase UI %p\n", (void*)MemoryLimit4Address);


		__int64 MemoryLimit5Address = PatternScan::Scan("48xxxxxxxx00005000", MemoryLimit4Address); //Param 5MB -> 20MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes5{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit5Address + 5, MemoryLimitBytes5);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Param %p\n", (void*)MemoryLimit5Address);


		__int64 MemoryLimit7Address = PatternScan::Scan("41xx0000C008", MemoryLimit5Address); //Texture 140MB -> 300MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes7{ 0x00, 0x00, 0xC0, 0x12 };
		util::memory::mem::write_bytes(MemoryLimit7Address + 2, MemoryLimitBytes7);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Texture %p\n", (void*)MemoryLimit7Address);


		__int64 MemoryLimit8Address = PatternScan::Scan("41xx00009001", MemoryLimit7Address); //S_Texture 25MB -> 60MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes8{ 0x00, 0x00, 0xC0, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit8Address + 2, MemoryLimitBytes8);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase S_Texture %p\n", (void*)MemoryLimit8Address);


		__int64 MemoryLimit9Address = PatternScan::Scan("41xx0000E001", MemoryLimit8Address); //Sound 25MB -> 50MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes9{ 0x00, 0x00, 0x20, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit9Address + 2, MemoryLimitBytes9);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Sound %p\n", (void*)MemoryLimit9Address);


		__int64 MemoryLimit10Address = PatternScan::Scan("41xx00008002", MemoryLimit9Address); //Stage 40MB -> 200MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes10{ 0x00, 0x00, 0x80, 0x0C };
		util::memory::mem::write_bytes(MemoryLimit10Address + 2, MemoryLimitBytes10);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Stage %p\n", (void*)MemoryLimit10Address);



		__int64 MemoryLimit11Address = PatternScan::Scan("41xx00003002", MemoryLimit10Address); //StageSub 35MB -> 40MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes11{ 0x00, 0x00, 0x80, 0x02 };
		util::memory::mem::write_bytes(MemoryLimit11Address + 2, MemoryLimitBytes11);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase StageSub %p\n", (void*)MemoryLimit11Address);


		__int64 MemoryLimit12Address = PatternScan::Scan("41xx0000B001", MemoryLimit11Address); //Player 27MB -> 60MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes12{ 0x00, 0x00, 0xC0, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit12Address + 2, MemoryLimitBytes12);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Player %p\n", (void*)MemoryLimit12Address);

		Console::PrintOut("MemoryLimitExpand :: Memory Increase Complete!\n");
	}


	// Enable Monitor on stages
	__int64 monitor_address2 = moduleBase + 0x6D6DEC;
	const std::array<std::uint8_t, 1> monitor_bytes{ 0x01 };
	util::memory::mem::write_bytes(monitor_address2, monitor_bytes);

	//Character Expand
	Console::PrintOut("UltimateStormAPI:: Expanding Character Slots\n");
	const std::array<std::uint8_t, 2> charBytes{ 0xFF, 0xFF };
	util::memory::mem::write_bytes(moduleBase+0x7F3EB7, charBytes);
	util::memory::mem::write_bytes(moduleBase + 0x7F4139, charBytes);
	util::memory::mem::write_bytes(moduleBase + 0x7220C2, charBytes);
	util::memory::mem::write_bytes(moduleBase + 0x8553DB, charBytes);

	//Gudo balls
	plugin::hookfunc(moduleBase + 0x771A88,
		reinterpret_cast<LPVOID>(&GudoBallParam::Hooked_sub_14097E4C0_S4),
		reinterpret_cast<LPVOID*>(&GudoBallParam::orig_sub_14097E4C0_S4));


	//Awakening Ultimate Jutsus
	plugin::hookfunc(moduleBase + 0x7D2E64,
		reinterpret_cast<LPVOID>(&OugiAwakeningParam::sub_1407D3A64_S4),
		reinterpret_cast<LPVOID*>(&OugiAwakeningParam::orig_sub_1407D3A64_S4));

	//D-pad function fix for Storm 4
	plugin::hookfunc(moduleBase + 0x6C0E54,
		reinterpret_cast<LPVOID>(&MovesetPlus::Hooked_sub_14084E110_S4),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_sub_14084E110_S4));

	//Guard Effects
	plugin::hookfunc(moduleBase + 0x7AEEDC,
		reinterpret_cast<LPVOID>(&GuardEffectParam::sub_1407AFADC_S4),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_1407AFADC));


	//Guard States
	plugin::hookfunc(moduleBase + 0x7ADFF8,
		reinterpret_cast<LPVOID>(&GuardEffectParam::hk_sub_1407AEBF8_S4),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_1407AEBF8));

	//ccPlayer::DrawImpl
	plugin::hookfunc(moduleBase + 0x77518C,
		reinterpret_cast<LPVOID>(&GuardEffectParam::hk_sub_140775D8C_S4),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_140775D8C));


	/*plugin::hookfunc(moduleBase + 0xA3DD30,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_ATKHIT_ON),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_ATKHIT_ON));*/


	/*plugin::hookfunc(moduleBase + 0xA88040,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_1413268E0_SC),
		reinterpret_cast<LPVOID*>(&Common::Original_sub_1413268E0));*/


		//IA SCENE FUNCTIONS
	//Might crash, need to change ccSceneFreeBattle and ccScenePracticeBattle memory allocation value from 0x4F8 to 0x1BF8

	//ccSceneBattleRootBase::`vftable' properties
	plugin::hookfunc(moduleBase + 0x6D6908,
		reinterpret_cast<LPVOID>(&Common::sub_140868D60),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140868D60));
	//ccSceneFreeBattle::Initialize();
	plugin::hookfunc(moduleBase + 0x6D8144,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_14086B520),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14086B520));
	//ccSceneFreeBattle::Finalize();
	plugin::hookfunc(moduleBase + 0x6D7954,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_14086ACA0),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14086ACA0));

	plugin::hookfunc(moduleBase + 0x5996C0,
		reinterpret_cast<LPVOID>(&Common::Hooked_IASceneName_CutSymbol),
		reinterpret_cast<LPVOID*>(&Common::orig_Hooked_IASceneName_CutSymbol));
	//FreeBattle
	Common::PatchMemoryAtOffsetInt32(0x6DCBDF, 0x1BF8);
	//Practice Battle
	Common::PatchMemoryAtOffsetInt32(0x6DD7BF, 0x1BF8);
	//League Battle
	Common::PatchMemoryAtOffsetInt32(0x6DD17F, 0x1BF8);
	//Tournament Battle
	Common::PatchMemoryAtOffsetInt32(0x6DE39F, 0x1BF8);
	//Survival Battle
	Common::PatchMemoryAtOffsetInt32(0x6DDDAF, 0x1BF8);
	//Network Endless Battle
	Common::PatchMemoryAtOffsetInt32(0x6E13CB, 0x1BF8);
	//Network Event Battle
	Common::PatchMemoryAtOffsetInt32(0x6E335B, 0x1BF8);
	//Network League Battle
	Common::PatchMemoryAtOffsetInt32(0x6E191B, 0x1BF8);
	//Network Player Battle
	Common::PatchMemoryAtOffsetInt32(0x6E1FFB, 0x1BF8);
	//Network Rank Battle
	Common::PatchMemoryAtOffsetInt32(0x6E24FB, 0x1BF8);

	//Lua Scripts

	Common::PatchWithNops(0x85223B, 5);
	plugin::hookfunc(moduleBase + 0x849A68,
		reinterpret_cast<LPVOID>(&LuaScript::Hooked_ns2_tolua_ccRegistScript_open),
		reinterpret_cast<LPVOID*>(&LuaScript::orig_ns2_tolua_ccRegistScript_open));

	if (GetPrivateProfileInt("General", "skip_opening", 1, config_path.c_str()) == 1)
	{
		//Skip Intro
		Common::PatchMemoryAtOffsetInt32(0x862D62, 0x63);
	}


	//Character Controls
	plugin::hookfunc(moduleBase + 0x7DF614,
		reinterpret_cast<LPVOID>(&Common::CtrlInputPad),
		reinterpret_cast<LPVOID*>(&Common::orig_CtrlInputPad));


	//Kaguya's Condition D-Pad fix
	plugin::hookfunc(moduleBase + 0x57F574,
		reinterpret_cast<LPVOID>(&Common::sub_140643E70),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140643E70));

	//Skip CRC32 conversion
	plugin::hookfunc(moduleBase + 0xAB8720,
		reinterpret_cast<LPVOID>(&Common::GetTextFromCRC32Code),
		reinterpret_cast<LPVOID*>(&Common::orig_GetTextFromCRC32Code));


	//ModManager Update Notification
	plugin::hookfunc(moduleBase + 0x694824,
		reinterpret_cast<LPVOID>(&ModManager::sub_140695424_S4),
		reinterpret_cast<LPVOID*>(&ModManager::orig_sub_140695424));


	//Title Screen time before it start to play opening
	Common::PatchMemoryAtOffsetInt16(0x71B4B2, 0xFFFF);

	//Fix for ME_CAMERA_LOOKAT_SET_HUGEAWAKE2
	plugin::hookfunc(moduleBase + 0x7F5408,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_CAMERA_LOOKAT_SET_HUGEAWAKE2),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2));


	//Fix for ME_CAMERA_LOOKAT_SET
	plugin::hookfunc(moduleBase + 0x7F53CC,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_CAMERA_LOOKAT_SET),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_CAMERA_LOOKAT_SET));




	//Disable Armor Break notify if hud is disabled
	plugin::hookfunc(moduleBase + 0x63E738,
		reinterpret_cast<LPVOID>(&Common::sub_14063F338),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14063F338));



	//Moveset Plus functions not for release
	HookFunctions::Hook((void*)(moduleBase+0x7F62D0), MovesetPlus::meTest2, 16);


	//Gauge initialization
	plugin::hookfunc(moduleBase + 0x63FE2C,
		reinterpret_cast<LPVOID>(&Common::sub_14072B7A0_NSC),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14072B7A0_NSC));

	//Gauge Set Rate for bars
	plugin::hookfunc(moduleBase + 0x640E90,
		reinterpret_cast<LPVOID>(&Common::sub_140641A90_NS4),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140641A90_NS4));


	//Disable Smoke for Akamaru
	Common::PatchMemoryAtOffsetInt32(0x79E562, 0x00);
	Common::PatchMemoryAtOffsetInt8(0x7D4289, 0x05);
	Common::PatchMemoryAtOffsetInt32(0x7D4293, 0x04);


	//Fix for ME_DRAWOBJ_ENABLE
	plugin::hookfunc(moduleBase + 0x7F6054,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_DRAWOBJ_ENABLE),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_DRAWOBJ_ENABLE));
	//Fix for ME_DRAWOBJ_DISABLE
	plugin::hookfunc(moduleBase + 0x7F5FF0,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_DRAWOBJ_DISABLE),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_DRAWOBJ_DISABLE));



	//Fix for Stand position 
	plugin::hookfunc(moduleBase + 0x7EC70C,
		reinterpret_cast<LPVOID>(&Common::IsInFrontOfOwner),
		reinterpret_cast<LPVOID*>(&Common::orig_IsInFrontOfOwner));

	//Fix for Stand Sound 
	plugin::hookfunc(moduleBase + 0x7EDE04,
		reinterpret_cast<LPVOID>(&Common::ccPlayerPartner2AKM_OnThroughDamage),
		reinterpret_cast<LPVOID*>(&Common::orig_ccPlayerPartner2AKM_OnThroughDamage));

	//Fix for Stand Smoke effect 
	plugin::hookfunc(moduleBase + 0x7B657C,
		reinterpret_cast<LPVOID>(&Common::EntrySmokeAtPartnerPos),
		reinterpret_cast<LPVOID*>(&Common::orig_EntrySmokeAtPartnerPos));

	//Memory Allocate for 2kib condition
	Common::PatchMemoryAtOffsetInt32(0x7C32DD, 0x15780);
	//Expand 2kib condition  
	plugin::hookfunc(moduleBase + 0x578DBC,
		reinterpret_cast<LPVOID>(&Common::CharacterManager_1CMN),
		reinterpret_cast<LPVOID*>(&Common::orig_CharacterManager_1CMN));

	//Change camera function for 2kib condition to enable screen effect
	plugin::hookfunc(moduleBase + 0x7C7E1C,
		reinterpret_cast<LPVOID>(&Common::sub_1409FF490),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_1409FF490));
	//Fix for player double effect param for 2akm

	Common::PatchAddress(Game::ConvertOffset(0x10b9A68), moduleBase+0x6B6350);


	//damage reaction 
	plugin::hookfunc(moduleBase + 0x785D4C,
		reinterpret_cast<LPVOID>(&Common::GetDamageReactionAction),
		reinterpret_cast<LPVOID*>(&Common::orig_GetDamageReactionAction));



	//Fix for Damage DOWN reaction to make it react like in NSC 
	plugin::hookfunc(moduleBase + 0x7A7940,
		reinterpret_cast<LPVOID>(&Common::CtrlAct_PL_ACT_DMG_TO_DOWN),
		reinterpret_cast<LPVOID*>(&Common::orig_CtrlAct_PL_ACT_DMG_TO_DOWN));

	//Fix for Damage Down Reaction in S4
	Common::PatchMemoryAtOffsetInt8(0x785E17, 0xEB);


	//TUJ Unlock
	//plugin::hookfunc(moduleBase + 0x58FC18,
	//	reinterpret_cast<LPVOID>(&TUJManager::sub_140590818),
	//	reinterpret_cast<LPVOID*>(&TUJManager::orig_sub_140590818));

	////Battle Timer Control
	//plugin::hookfunc(moduleBase + 0x74C40C,
	//	reinterpret_cast<LPVOID>(&Common::sub_14093C7D0),
	//	reinterpret_cast<LPVOID*>(&Common::orig_sub_14093C7D0));
}

void HookFunctions::InitializeHooksSC()
{

	__int64 debug_str_address = PatternScan::Scan("48xxxxxxxx4Cxxxxxxxx4CxxxxxxxxC30Fxxxx33xx4Cxxxx44xxxx85xx74xx908Bxx4Dxxxxxx83xxxx83xxxxD3xx41xxxx41xxxxxxxxxxxx33xx41xxxxxx85xx75xxC3");
	if (GetPrivateProfileInt("General", "enable_debug", 1, config_path.c_str()) == 1 && debug_str_address > 1)
	{
		Console::PrintOutW("UltimateStormAPI:: Found Debug Strings SC\n");
		HookFunctions::Hook((void*)(debug_str_address), Common::DebugString, 15);
	}
	else if (debug_str_address < 1) {
		Console::PrintErr("UltimateStormAPI:: Couldnt find Debug Strings SC\n");
	}
	//No Clip Cursor
	__int64 noClipCursorFunctionAdress = PatternScan::Scan("40xx48xxxxxx48xxxx48xxxxxxxxxxxxE8xxxxxxxx48xxxxxx48xxxxFFxxxxxxxxxxxxxxxxFFxxxxxxxxxx48xxxx74xx41xxxxxxxxxx");
	if (noClipCursorFunctionAdress > 1) {
		Console::PrintOut("UltimateStormAPI:: No Clip Cursor Enabled\n");
		HookFunctions::Hook((void*)(noClipCursorFunctionAdress), Common::NoClipCursor, 16);
	}
	//Increase costume limit
	__int64 costumeLimitAdress = PatternScan::Scan("48xxxxxxxx55565741xx41xx41xx41xx48xxxxxxxxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxx");
	if (costumeLimitAdress > 1) {
		Console::PrintOut("UltimateStormAPI:: Increase costume limit\n");
		__int64 costumeLimitAdress1 = PatternScan::Scan("488B7DA083F8");
		const std::array<std::uint8_t, 1> costumeLimitBytes1{ 0x64 };
		util::memory::mem::write_bytes(costumeLimitAdress1 + 6, costumeLimitBytes1);
	}
	//Motion blur
	__int64 MotionBlurAddress = PatternScan::Scan("B9xxxxxxxx48xxxxxx80xxxxxx75xxE8xxxxxxxx65xxxxxxxxxxxxxxxxB9xxxxxxxx48xxxxxx48xxxxxx83xxxxxxxxxxxx75xx48xxxxxxxxxxxxB9xxxxxxxxE8xxxxxxxx");
	if (MotionBlurAddress > 1) {
		Console::PrintOut("UltimateStormAPI:: Motion blur Hooked\n");

		struct Patch {
			const char* pattern;
			int offset;
			std::array<std::uint8_t, 1> bytes; // : std::array,   { }
		};

		const Patch patches[] = {
			{ "B92C34xxxx",   1, { 0x34 } },
			{ "B90034xxxx",   1, { 0x08 } },
			{ "83xx4002xxxx", 2, { 0x48 } },
		};

		for (const auto& p : patches) {
			__int64 addr = PatternScan::Scan(p.pattern, MotionBlurAddress);
			if (addr > 1) {
				util::memory::mem::write_bytes(addr + p.offset, p.bytes);
			}
		}
	}
	// Hide HUD
	__int64 hudon_address1 = PatternScan::Scan("48xxxxxxxx48xxxxxxxx41xx48xxxxxx48xxxx49xxxx0Fxxxxxx4Cxxxx0Fxxxx24xx3Cxx74xxF6xxxx75xx33xx49xxxxxx49xxxx41xxxxxx48xxxxxxxx48xxxxxxxx48xxxxxx41xxC38Bxxxxxxxxxx");
	Common::hudon_address = PatternScan::Scan("3C01", hudon_address1) + 1;

	//Wall Run
	__int64 wallFunctionAdress = PatternScan::Scan("40xx48xxxxxx48xxxxxxxxxxxx33xx8Bxxxx81xxxxxxxxxx74xx81xxxxxxxxxx74xx81xxxxxxxxxx74xx8Bxx48xxxxxx");
	if (wallFunctionAdress > 1) {
		Console::PrintOut("WallRunManager :: Hooking Wall Run\n");
		HookFunctions::Hook((void*)(wallFunctionAdress), Common::WallRun, 15);
	}
	// Partner function
	__int64 partnerFunctionAddress = PatternScan::Scan("33xx48xxxxxxxxxxxx4Cxxxxxxxxxxxx3Bxx74xxFFxx48xxxxxx49xxxx7Cxx33xxC348xxxx48xxxxxxxxxxxx48xxxx48xxxxxx");
	if (partnerFunctionAddress > 1) {
		Console::PrintOut("UltimateStormAPI:: Creating Partners\n");
		HookFunctions::Hook((void*)(partnerFunctionAddress), PartnerSlotParam::CreatePartner, 16);
	}
	//Conditions
	__int64 charCondFunctionAddress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx5548xxxx48xxxxxx8Bxx81xxxxxxxxxx0Fxxxxxxxxxx8Dxxxx48xxxxxxxxxxxxE8xxxxxxxx85xx0Fxxxxxxxxxx");
	if (charCondFunctionAddress > 1) {
		Console::PrintOut("UltimateStormAPI:: Creating Conditions\n");
		Console::PrintErr("UltimateStormAPI:: Creating Conditions Address %p\n", charCondFunctionAddress - moduleBase);
		plugin::hookfunc(charCondFunctionAddress, SpecialCondParam::Create_NSC, (LPVOID*)&co_nsc);
	}

	//Condition PRM
	__int64 conditionprmAddress = PatternScan::Scan("8Dxxxx3DFB01000077xx48xxxx48xxxxxxxxxxxx48xxxxxx48xxxxC333xxC3");
	if (conditionprmAddress > 1) {
		Console::PrintOut("UltimateStormAPI :: Condition PRM SC Hooked\n");

		HookFunctions::Hook(
			reinterpret_cast<void*>(conditionprmAddress),
			ConditionPrmManager::GetConditionEntry,
			20
		);

		const auto conditionBytes1 = ToBytes(static_cast<std::uint32_t>(g_ConditionEntries.size() - 1));
		const auto conditionBytes2 = ToBytes(static_cast<std::uint32_t>(g_ConditionEntries.size()));

		// ---    ---
		{
			__int64 addr1 = PatternScan::Scan(
				"4Cxxxxxx4Dxxxx74xx81xxFC01000077xx48xxxx48xxxxxxxxxxxx49xxxxC333xxC3"
			);
			__int64 target = PatternScan::Scan("FC010000", addr1);
			if (target > 1) {
				util::memory::mem::write_bytes(target, conditionBytes1);
			}
		}

		// ---    ---
		{
			__int64 addr2 = PatternScan::Scan(
				"48xxxxxxxx5748xxxxxx8Bxx33xx66xx8BxxE8xxxxxxxx48xxxx74xx48xxxx48xxxx74xx"
				"E8xxxxxxxx3Bxx74xxFFxx81xxFD0100007Cxx33xx48xxxxxxxx48xxxxxx5FC38Bxx48xxxxxxxx48xxxxxx5FC3"
			);

			//     "FD010000"
			__int64 target = addr2;
			for (int i = 0; i < 3; ++i) {
				target = PatternScan::Scan("FD010000", target + (i ? 4 : 0));
				if (target > 1) {
					util::memory::mem::write_bytes(target, conditionBytes2);
				}
			}
		}
	}
	__int64 susanooAddressSC = PatternScan::Scan("48xxxxxxxx55565748xxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxx48xxxx33xx48xxxx8BxxFFxxxxxxxxxx85xx74xx8Bxxxxxxxxxx83xxxx74xx");
	if (susanooAddressSC > 1) {
		Console::PrintOutW("SusanooFunction SC :: Hooked\n");
		plugin::hookfunc(susanooAddressSC, nsc::player::susanoojumpnsc, (LPVOID*)(&osusanoojump));
	}

	//SpecialInteraction UJ
	__int64 specialInteractionChangerAddress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx5741xx41xx48xxxxxx8Bxxxxxxxxxx33xx41xxxx8Bxx4Cxxxx44xxxx83xxxx74xx3Dxxxxxxxx75xx81xxxxxxxxxx75xx48xxxxxxxxxxxx48xxxx74xx8BxxE8xxxxxxxx4Cxxxx48xxxx0Fxxxxxxxxxx85xx");
	if (specialInteractionChangerAddress > 1) {
		BattleUtils::GetEnemyPointerAddress = PatternScan::Scan("40xx48xxxxxx48xxxx33xxFFxxxx3Bxxxxxxxxxx74xx48xxxxxxxxxxxx4Cxxxxxx49xxxx49xxxxxx38xxxx75xx0Fxxxx39xxxx73xx48xxxxxxEBxx48xxxx48xxxx38xxxx74xx38xxxx");

		Console::PrintOutW("SpecialInteractionManager :: Initializing\n"); 
		HookFunctions::Hook((void*)(specialInteractionChangerAddress), SpecialInteractionManager::SpecialInteractionUJChanger, 15);
		__int64 specialInteractionSoundAddress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx48xxxxxxxx48xxxxxxxx41xx48xxxxxx8Bxxxxxxxxxx48xxxx33xxE8xxxxxxxx8Bxx83xxxx74xx83xxxx75xx48xxxx44xxxxE8xxxxxxxx48xxxx74xx44xxxxxxxxxxxx83xxxx75xx41xxxx48xxxxE8xxxxxxxx85xx74xx8Dxxxx");
		HookFunctions::Hook((void*)(specialInteractionSoundAddress), SpecialInteractionManager::SpecialInteractionSoundFunction, 15);

		Console::PrintOutW("SpecialInteractionManager :: Initializing Sounds\n");
		__int64 specialInteractionSound2Address = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxx33xxE8xxxxxxxx48xxxx0Fxxxxxxxxxx8Bxxxxxxxxxx8Bxxxxxxxxxx83xxxx74xx83xxxx74xx83xxxx74xx83xxxx75xx48xxxxE8xxxxxxxx85xx74xxBBxxxxxxxx8Bxx48xxxxxxxx48xxxxxx5FC348xxxx");
		HookFunctions::Hook((void*)(specialInteractionSound2Address), SpecialInteractionManager::SpecialInteractionFunction2, 15);

		Console::PrintOutW("SpecialInteractionManager :: Initializing PRM Function\n");
		__int64 specialInteractionPRMFunctionAddress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx41xx48xxxxxx8Dxxxxxxxxxx8Bxx4Cxxxx8Bxx3Dxxxxxxxx0Fxxxxxxxxxx48xxxxxxxxE8xxxxxxxx83xxxx75xx8Dxxxx49xxxxE8xxxxxxxx83xxxx75xx8Dxxxx49xxxxE8xxxxxxxx83xxxx75xx8Dxxxxxxxxxx41xxxxxxxxxxxx");
		HookFunctions::Hook((void*)(specialInteractionPRMFunctionAddress), SpecialInteractionManager::AdjustSpecialInteractionValue, 16);


		SpecialInteractionManager::sub_140AC49A0Adress = PatternScan::Scan("83xxxx77xx83xxxx77xx4Cxxxxxxxxxxxx4Dxxxx74xx48xxxx49xxxxxx48xxxxxx48xxxxxx49xxxxE9xxxxxxxx33xxC383xxxx77xx83xxxx77xx4Cxxxxxxxxxxxx4Dxxxx74xx48xxxx49xxxxxxFFxx48xxxxxx48xxxxxx49xxxxE9xxxxxxxx33xxC3");

	}
	MovesetPlus::VTableAddress = PatternScan::Scan("48xxxxxxxx5748xxxxxx8Bxxxxxxxxxx48xxxx65xxxxxxxxxxxxxxxx48xxxxB9xxxxxxxx4Dxxxxxx42xxxxxx39xxxxxxxxxx7Fxx48xxxxE8xxxxxxxx48xxxxxx4Cxxxx");

	// Moveset Plus function
	__int64 movesetPlusFunctionAddress = PatternScan::Scan("48xxxxxx48xxxxFFxxxxxxxxxx48xxxx74xx48xxxx48xxxxFFxxxxxxxxxxB8xxxxxxxx48xxxxxxC3");
	if (movesetPlusFunctionAddress > 1) {

		Console::PrintOutW("MovesetPlus :: Creating Functions\n");
		MovesetPlus::BgmOffFunctionAdress = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxx48xxxx48xxxxxxxxxxxx8BxxE8xxxxxxxx48xxxxxxxxxxxx44xxxx33xxE8xxxxxxxxC7xxxxxxxxxxxxxxxxxxxx");
		MovesetPlus::BgmOnFunctionAdress = PatternScan::Scan("45xxxx48xxxxxxxxxxxx66xxxxxxxxxx39xx74xx49xxxx48xxxxxx49xxxxxx7Cxx33xxC3B8xxxxxxxxC3");
		MovesetPlus::BgmOff2FunctionAdress = PatternScan::Scan("48xxxxxxxx5748xxxxxx83xxxxxx8Bxx48xxxx75xx48xxxxxxxxxxxx48xxxx74xx48xxxxxxxx49xxxx39xxxxxxxxxxxx74xxF3xxxxxxxx45xxxx");


		MovesetPlus::ResolveEffectAddress = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxx33xx908BxxE8xxxxxxxx48xxxx74xx48xxxx48xxxx74xx4Cxxxx4Cxxxx66xxxxxxxxxx");
		MovesetPlus::ExecuteEffectAddress = PatternScan::Scan("4Cxxxx535741xx48xxxxxxxxxxxx0Fxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxx0Fxxxx41xxxx44xxxx");

		MovesetPlus::HandleStageChangeAddress = PatternScan::Scan("40xx48xxxxxx8Bxx48xxxxxxxxxxxxE8xxxxxxxx48xxxxxxxxxxxx8BxxE8xxxxxxxx48xxxxxxxxxxxxC7xxxxxxxxxxxxC7xxxxxxxxxxxx");
		MovesetPlus::DefaultStageHandlerAddress = PatternScan::Scan("40xx48xxxxxx83xxxxxx48xxxx74xx8BxxxxE8xxxxxxxxC7xxxxxxxxxxxx48xxxxxx5BC3");
		MovesetPlus::SpecificStageHandlerAddress = PatternScan::Scan("40xx48xxxxxx48xxxxxxxxxxxx48xxxx39xxxx74xxE8xxxxxxxxC7xxxxxxxxxxxx48xxxxxx5BC3");

		MovesetPlus::FixCharPositionAddress = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx48xxxxxx5541xx41xx41xx41xx48xxxxxxxxxxxx48xxxxxxxxxxxx0Fxxxxxx0Fxxxxxx44xxxxxxxx44xxxxxxxx44xxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxx4Cxxxx33xx89xxxxxx48xxxxxxxxxxxx45xxxxxx");

		
		//Dpad animations
		// Address of the target bytes
		__int64 DPadHudAddress = PatternScan::Scan("83xxxxxxxxxxxx44xxxxxx44xxxxxx44xxxxxx0Fxxxxxxxxxx44xxxxxx66xxxxxxxxxxxxxxF3xxxxxxxxxx");
		void* targetAddress = (void*)(DPadHudAddress + 2); // Adjust offset if necessary

		// Original and new byte sequences
		uint8_t originalBytes[] = { 0x64, 0x0E, 0x00, 0x00, 0x7C };
		uint8_t newBytes[] = { 0x30, 0x0F, 0x00, 0x00, 0x01 };
		// Replace bytes and monitor changes
		HookFunctions::ReplaceBytes(targetAddress, newBytes, sizeof(newBytes));


		HookFunctions::Hook((void*)(movesetPlusFunctionAddress), MovesetPlus::meTest, 16);

	}
	//Update Cancel Action Function
	__int64 ActionCancelFunctionAdress = PatternScan::Scan("48xxxxxxxx83xxxx0Fxxxxxxxxxx4Cxxxxxxxxxxxx41xxxxxxxxxxxxxx49xxxxFFxxC7xxxxxxxxxx01xxxxxxB8xxxxxxxxC3C7xxxxxxxxxx02xxxxxxB8xxxxxxxx");
	if (ActionCancelFunctionAdress > 1) {
		Console::PrintOutW("MovesetPlus :: Action Cancel Updated\n");
		HookFunctions::Hook((void*)(ActionCancelFunctionAdress), MovesetPlus::CancelActionFunction, 14);
	}
	//Disable Upgrade Cancellation
	__int64 upgradeCancelFunctionAdress = PatternScan::Scan("40xx48xxxxxx8Bxxxxxxxxxx48xxxx83xxxx83xxxx0Fxxxxxxxxxx8BxxxxxxxxxxE8xxxxxxxx83xxxx");
	if (upgradeCancelFunctionAdress > 1) {
		cout << "MovesetPlus :: Upgrade Cancel Disabled" << endl;
		plugin::hookfunc(upgradeCancelFunctionAdress,
			reinterpret_cast<LPVOID>(&MovesetPlus::EnableUpgradeCancel),
			reinterpret_cast<LPVOID*>(&MovesetPlus::orig_EnableUpgradeCancel));
		Console::PrintErr("MovesetPlus :: Action Cancel Updated Address %p\n", upgradeCancelFunctionAdress - moduleBase);
		__int64 CancelFunctionAdress = moduleBase+0xA43510;
		if (CancelFunctionAdress > 1) {
			MovesetPlus::sub_140978B00Adress = PatternScan::Scan("48xxxxxxxx5748xxxxxx48xxxxxxxxxxxx48xxxxBAxxxxxxxx33xx48xxxxxxE8xxxxxxxx48xxxx74xx48xxxx");
			HookFunctions::Hook((void*)(CancelFunctionAdress), MovesetPlus::Motion_cancel_function, 14);
			cout << "MovesetPlus :: Update Upgrade Cancel Function" << endl;
		}
	}

	//Expand Upgrade Function
	__int64 upgradeFunctionAdress = PatternScan::Scan("48xxxxxxxx5748xxxxxx8Bxxxxxxxxxx48xxxx89xxxxxxxxxxE8xxxxxxxx48xxxx74xx4Cxxxxxxxxxxxx44xxxxxx48xxxx48xxxxxxxxxxxx");
	if (upgradeFunctionAdress > 1) {
		cout << "MovesetPlus :: Upgrade Function Expanded" << endl;

		MovesetPlus::sub_14097F1E0Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx5748xxxxxx48xxxx48xxxx48xxxxxx48xxxxxxxxxxxx48xxxx75xx48xxxxxxxxxxxx");
		MovesetPlus::sub_1405C3970Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx55565741xx41xx41xx41xx48xxxxxx4Dxxxx49xxxx48xxxx4Cxxxx48xxxxxxxx");
		MovesetPlus::sub_1405C7EC0Adress = moduleBase + 0x5EDEE0;
		MovesetPlus::sub_1405C8F00Adress = PatternScan::Scan("45xxxx4Cxxxx44xxxxxxxxxxxx7Exx45xxxx0Fxxxxxx66xxxxxxxxxxxxxxxxxx49xxxxxxxxxxxx49xxxxxx48xxxx");

		MovesetPlus::cancelUpgradeFunctionState[0] = 0;
		MovesetPlus::cancelUpgradeFunctionState[1] = 0;


		cout << "MovesetPlus :: Fix Upgrade Function" << endl; //find sub_1409B94C0 in 1.50 exe and find 112 characode (5mdr). its some switch value
		__int64 fixUpgradeAddress1 = PatternScan::Scan("8B87A00E0000");
		__int64 fixUpgradeAddress2 = PatternScan::Scan("8B87A00E0000", fixUpgradeAddress1 + 6);
		__int64 fixUpgradeAddress3 = PatternScan::Scan("8B87A00E0000", fixUpgradeAddress2 + 6);
		const std::array<std::uint8_t, 2> fixUpgradeBytes1{ 0x04, 0x00 };
		util::memory::mem::write_bytes(fixUpgradeAddress3 + 2, fixUpgradeBytes1);


		plugin::hookfunc(upgradeFunctionAdress,
			reinterpret_cast<LPVOID>(&MovesetPlus::UpgradeVerUnlocker),
			reinterpret_cast<LPVOID*>(&MovesetPlus::orig_UpgradeVerUnlocker));
	}
	//Update Condition Add Param Function
	__int64 ConditionAddParamAdress = PatternScan::Scan("48xxxxxxxx5648xxxxxx48xxxxE8xxxxxxxx48xxxx48xxxx74xx48xxxxxxxx48xxxx48xxxxxxxxE8xxxxxxxx48xxxxE8xxxxxxxx0Fxxxxxx48xxxx");
	if (ConditionAddParamAdress > 1) {
		cout << "MovesetPlus :: Condition Add Function Updated" << endl;
		HookFunctions::Hook((void*)(ConditionAddParamAdress), MovesetPlus::ApplyStatusEffect, 18);
	}
	//Character Expander
	const std::array<std::uint8_t, 2> charBytes6{ 0x2C, 0x03 };
	__int64 characterExpend1Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx48xxxxxxxx5541xx41xx41xx41xx48xxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxx4CxxxxC7xxxxxxxxxxxx");
	if (characterExpend1Adress > 1) {
		cout << "CharacterExpanderManager :: Character Code Hooked" << endl;
		__int64 char1Adress = PatternScan::Scan("C7xxxxxxxxxxxx41xxxxxxxxxx48xxxxxxxxxxxx", characterExpend1Adress);
		//cout << char1Adress << endl;
		util::memory::mem::write_bytes(char1Adress + 3, charBytes6);

		__int64 char2Adress = PatternScan::Scan("B9xxxxxxxxE8xxxxxxxx49xxxx45xxxxxx", characterExpend1Adress);
		//cout << char2Adress << endl;
		const std::array<std::uint8_t, 4> charBytes2{ 0x64, 0x78, 0x01, 0x00 };
		util::memory::mem::write_bytes(char2Adress + 1, charBytes2);


		__int64 char3Adress = PatternScan::Scan("41xxxxxxxxxxxx0Fxxxxxxxxxx48xxxxxx48xxxxE8xxxxxxxx4Cxxxxxxxxxxxxxx49xxxxxx", characterExpend1Adress);
		//cout << char3Adress << endl;
		util::memory::mem::write_bytes(char3Adress + 3, charBytes6);
	}


	__int64 characterExpend6Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx48xxxxxxxx41xx48xxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxx33xx66xxxxxxxxxxxxxxxxxx");
	if (characterExpend6Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 1 Hooked" << endl;
		__int64 char8Adress = PatternScan::Scan("81xxxxxxxxxx77xxE8xxxxxxxx", characterExpend6Adress);
		//cout << char8Adress << endl;
		util::memory::mem::write_bytes(char8Adress + 2, charBytes6);
		//cout << "CharacterExpanderManager :: Character 2 Hooked" << endl;
		__int64 char9Adress = PatternScan::Scan("3Dxxxxxxxx77xx8Bxx", char8Adress);
		//cout << char9Adress << endl;
		util::memory::mem::write_bytes(char9Adress + 1, charBytes6);
		//cout << "CharacterExpanderManager :: Character 3 Hooked" << endl;
		__int64 char11Adress = PatternScan::Scan("3Dxxxxxxxx77xx8Bxx", char9Adress + 1);
		//cout << char11Adress << endl;
		util::memory::mem::write_bytes(char11Adress + 1, charBytes6);
	}
	__int64 characterExpend4Adress = PatternScan::Scan("48xxxxxx81xxxxxxxxxx77xxE8xxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxE9xxxxxxxx33xx48xxxxxxC3");
	if (characterExpend4Adress > 1) {
		//cout << "CharacterExpanderManager :: Character Sound Entries Hooked" << endl;
		__int64 char6Adress = PatternScan::Scan("81xxxxxxxxxx77xxE8xxxxxxxx", characterExpend4Adress);
		//cout << char6Adress << endl;
		util::memory::mem::write_bytes(char6Adress + 2, charBytes6);
	}
	__int64 characterExpend5Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx5748xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxxxx48xxxxxxxxxxxx48xxxxxxxxxxxx49xxxx");
	if (characterExpend5Adress > 1) {
		//cout << "CharacterExpanderManager :: Character Sound ACBs Hooked" << endl;
		__int64 char7Adress = PatternScan::Scan("41xxxxxxxxxxxx0Fxxxxxxxxxx83xxxx0Fxxxxxxxxxx41xxxxxx", characterExpend5Adress);
		//cout << char7Adress << endl;
		util::memory::mem::write_bytes(char7Adress + 3, charBytes6);
	}
	__int64 characterExpend3Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx48xxxxxxxx5541xx41xx41xx41xx48xxxx48xxxxxx48xxxxxxxxxxxx48xxxx48xxxxxx4Cxxxx");
	if (characterExpend3Adress > 1) {
		//cout << "CharacterExpanderManager :: Character PRM_Load Hooked" << endl;
		__int64 char5Adress = PatternScan::Scan("81xxxxxxxxxx0Fxxxxxxxxxx48xxxxxxxxxxxx4Cxxxxxxxxxxxx45xxxx44xxxx", characterExpend3Adress);
		//cout << char5Adress << endl;
		util::memory::mem::write_bytes(char5Adress + 2, charBytes6);
	}
	__int64 characterExpend7Adress = PatternScan::Scan("4Cxxxx41xx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxxxx4Cxxxxxxxxxxxx45xxxx44xxxxxxxx44xxxx89xxxxxx4Dxxxxxx");
	if (characterExpend7Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 4 Hooked" << endl;
		__int64 char12Adress = PatternScan::Scan("81xxxxxxxxxx77xx8BxxE8xxxxxxxx", characterExpend7Adress);
		//cout << char12Adress << endl;
		util::memory::mem::write_bytes(char12Adress + 2, charBytes6);
	}
	__int64 characterExpend8Adress = PatternScan::Scan("48xxxxxxxx5748xxxxxx41xxxx8Bxx81xxxxxxxxxx0FxxxxxxxxxxE8xxxxxxxx48xxxxxxxxxxxx48xxxxE8xxxxxxxx");
	if (characterExpend8Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 5 Hooked" << endl;
		__int64 char13Adress = PatternScan::Scan("81xxxxxxxxxx0FxxxxxxxxxxE8xxxxxxxx48xxxxxxxxxxxx48xxxxE8xxxxxxxx", characterExpend8Adress);
		//cout << char13Adress << endl;
		util::memory::mem::write_bytes(char13Adress + 2, charBytes6);
	}
	__int64 characterExpend9Adress = PatternScan::Scan("41xx41xx41xx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxxxx45xxxx44xxxxxxxx44xxxx89xxxxxxxx");
	if (characterExpend9Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 6 Hooked" << endl;
		__int64 char14Adress = PatternScan::Scan("41xxxxxxxxxxxx0Fxxxxxxxxxx41xxxx", characterExpend9Adress);
		//cout << char14Adress << endl;
		util::memory::mem::write_bytes(char14Adress + 3, charBytes6);
	}
	__int64 characterExpend10Adress = PatternScan::Scan("40xx555641xx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxxxx4Cxxxx41xxxx48xxxxxxxxxxxx8Bxx");
	if (characterExpend10Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 7 Hooked" << endl;
		__int64 char15Adress = PatternScan::Scan("81xxxxxxxxxx77xx8BxxE8xxxxxxxx", characterExpend10Adress);
		//cout << char15Adress << endl;
		util::memory::mem::write_bytes(char15Adress + 2, charBytes6);
	}
	__int64 characterExpend11Adress = PatternScan::Scan("48xxxxxx85xx74xx81xxxxxxxxxx77xx48xxxxxxxxE8xxxxxxxx48xxxxxxxxxxxx48xxxx");
	if (characterExpend11Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 8 Hooked" << endl;
		__int64 char16Adress = PatternScan::Scan("81xxxxxxxxxx77xx48xxxxxxxx", characterExpend11Adress);
		//cout << char16Adress << endl;
		util::memory::mem::write_bytes(char16Adress + 2, charBytes6);
	}
	__int64 characterExpend12Adress = PatternScan::Scan("48xxxxxxxx48xxxxxxxx565741xx48xxxxxxxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxx49xxxx");
	if (characterExpend12Adress > 1) {
		//cout << "CharacterExpanderManager :: Character 9 Hooked" << endl;
		__int64 char17Adress = PatternScan::Scan("81xxxxxxxxxx0Fxxxxxxxxxx85xx78xx8BxxE8xxxxxxxx", characterExpend12Adress);
		//cout << char17Adress << endl;
		util::memory::mem::write_bytes(char17Adress + 2, charBytes6);
	}

	// Increase Memory Limits sub_140605050 (1.50)
	__int64 MemoryLimitAddress = PatternScan::Scan("48xxxxxxxx5748xxxxxxE8xxxxxxxxC7xxxxxxxxxxxxE8xxxxxxxx48xxxxBAxxxxxxxxE8xxxxxxxxE8xxxxxxxx");
	if (MemoryLimitAddress > 1) {
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Start\n");

		__int64 MemoryLimit1Address = PatternScan::Scan("48xxxxxxxxxxxx0000A000", MemoryLimitAddress);
		const std::array<std::uint8_t, 4> MemoryLimitBytes1{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit1Address + 7, MemoryLimitBytes1);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Unknown %p\n", (void*)MemoryLimit1Address);


		__int64 MemoryLimit2Address = PatternScan::Scan("41xx0000A000", MemoryLimit1Address);
		const std::array<std::uint8_t, 4> MemoryLimitBytes2{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit2Address + 2, MemoryLimitBytes2);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Debug %p\n", (void*)MemoryLimit2Address);


		__int64 MemoryLimit3Address = PatternScan::Scan("41xx00000019", MemoryLimit2Address); //App 400MB -> 800MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes3{ 0x00, 0x00, 0x00, 0x32 };
		util::memory::mem::write_bytes(MemoryLimit3Address + 2, MemoryLimitBytes3);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase App %p\n", (void*)MemoryLimit3Address);


		__int64 MemoryLimit4Address = PatternScan::Scan("41xx0000E015", MemoryLimit3Address); //UI 350MB -> 700MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes4{ 0x00, 0x00, 0xC0, 0x2B };
		util::memory::mem::write_bytes(MemoryLimit4Address + 2, MemoryLimitBytes4);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase UI %p\n", (void*)MemoryLimit4Address);


		__int64 MemoryLimit5Address = PatternScan::Scan("48xxxxxxxx0000A000", MemoryLimit4Address); //Param 10MB -> 20MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes5{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit5Address + 5, MemoryLimitBytes5);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Param %p\n", (void*)MemoryLimit5Address);


		__int64 MemoryLimit6Address = PatternScan::Scan("48xxxxxxxx0000A000", MemoryLimit5Address); //Skill 10MB -> 20MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes6{ 0x00, 0x00, 0x40, 0x01 };
		util::memory::mem::write_bytes(MemoryLimit6Address + 5, MemoryLimitBytes6);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Skill %p\n", (void*)MemoryLimit6Address);


		__int64 MemoryLimit7Address = PatternScan::Scan("41xx00002003", MemoryLimit6Address); //Texture 50MB -> 300MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes7{ 0x00, 0x00, 0xC0, 0x12 };
		util::memory::mem::write_bytes(MemoryLimit7Address + 2, MemoryLimitBytes7);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Texture %p\n", (void*)MemoryLimit7Address);


		__int64 MemoryLimit8Address = PatternScan::Scan("41xx0000E001", MemoryLimit7Address); //Sound 30MB -> 60MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes8{ 0x00, 0x00, 0xC0, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit8Address + 2, MemoryLimitBytes8);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Sound %p\n", (void*)MemoryLimit8Address);


		__int64 MemoryLimit9Address = PatternScan::Scan("41xx00009001", MemoryLimit8Address); //S_Texture 25MB -> 50MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes9{ 0x00, 0x00, 0x20, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit9Address + 2, MemoryLimitBytes9);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase S_Texture %p\n", (void*)MemoryLimit9Address);


		__int64 MemoryLimit10Address = PatternScan::Scan("41xx00002003", MemoryLimit9Address); //Stage 50MB -> 200MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes10{ 0x00, 0x00, 0x80, 0x0C };
		util::memory::mem::write_bytes(MemoryLimit10Address + 2, MemoryLimitBytes10);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Stage %p\n", (void*)MemoryLimit10Address);



		__int64 MemoryLimit11Address = PatternScan::Scan("41xx00004001", MemoryLimit10Address); //StageSub 20MB -> 40MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes11{ 0x00, 0x00, 0x80, 0x02 };
		util::memory::mem::write_bytes(MemoryLimit11Address + 2, MemoryLimitBytes11);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase StageSub %p\n", (void*)MemoryLimit11Address);


		__int64 MemoryLimit12Address = PatternScan::Scan("41xx0000E001", MemoryLimit11Address); //Player 30MB -> 60MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes12{ 0x00, 0x00, 0xC0, 0x03 };
		util::memory::mem::write_bytes(MemoryLimit12Address + 2, MemoryLimitBytes12);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Player %p\n", (void*)MemoryLimit12Address);

		__int64 MemoryLimit13Address = PatternScan::Scan("41xx0000E015", MemoryLimit12Address); //Resident 350MB -> 700MB
		const std::array<std::uint8_t, 4> MemoryLimitBytes13{ 0x00, 0x00, 0xC0, 0x2B };
		util::memory::mem::write_bytes(MemoryLimit13Address + 2, MemoryLimitBytes13);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Resident %p\n", (void*)MemoryLimit13Address);
		Console::PrintOut("MemoryLimitExpand :: Memory Increase Complete!\n");
	}

	// Enable Monitor on stages
	__int64 monitor_address = PatternScan::Scan("48xxxx48xxxxxx48xxxxxx48xxxxxx5541xx41xx41xx41xx48xxxxxxxxxxxx48xxxxxxxxxxxx0Fxxxxxx0Fxxxxxx48xxxxxxxxxxxx48xxxx48xxxxxxxxxxxx4Cxxxx48xxxxxxxx48xxxxxxxx48xxxxFFxxxx904Cxxxxxxxxxxxx");
	__int64 monitor_address2 = PatternScan::Scan("C7xxxxxxxxxx00000000", monitor_address) + 6;
	const std::array<std::uint8_t, 4> monitor_bytes{ 0x01, 0x00, 0x00, 0x00 };
	util::memory::mem::write_bytes(monitor_address2, monitor_bytes);


	//HookFunctions::Hook((void*)(moduleBase+0x9EFB30), ProjectileExpander::sub_1409F0730, 14);

	//Gudoballs
	plugin::hookfunc(moduleBase+0x97D8C0,
		reinterpret_cast<LPVOID>(&GudoBallParam::Hooked_sub_14097E4C0),
		reinterpret_cast<LPVOID*>(&GudoBallParam::orig_sub_14097E4C0));

	//Awakening Ultimates
	plugin::hookfunc(moduleBase + 0xA0D410,
		reinterpret_cast<LPVOID>(&OugiAwakeningParam::sub_14079BB7C_SC),
		reinterpret_cast<LPVOID*>(&OugiAwakeningParam::orig_sub_140A0E010_SC));

	//Guard Effects
	plugin::hookfunc(moduleBase + 0x9D5620,
		reinterpret_cast<LPVOID>(&GuardEffectParam::sub_1409D6220_SC),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_1409D6220));


	//Guard States
	plugin::hookfunc(moduleBase + 0x9D4440,
		reinterpret_cast<LPVOID>(&GuardEffectParam::hk_sub_1409D5040_SC),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_1409D5040));

	//ccPlayer::DrawImpl
	plugin::hookfunc(moduleBase + 0x980680,
		reinterpret_cast<LPVOID>(&GuardEffectParam::hk_sub_140981280_SC),
		reinterpret_cast<LPVOID*>(&GuardEffectParam::orig_sub_140981280));
	//Fix for Alt Tab debug error
	HookFunctions::Hook((void*)(moduleBase+0x132ACB0), Common::sub_14132B8B0_SC, 15);




	//IA SCENE FUNCTIONS
	//Might crash, need to change ccSceneFreeBattle and ccScenePracticeBattle memory allocation value from 0x4F8 to 0x1BF8

	//ccSceneBattleRootBase::`vftable' properties
	plugin::hookfunc(moduleBase + 0x868160,
		reinterpret_cast<LPVOID>(&Common::sub_140868D60),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140868D60));
	//ccSceneFreeBattle::Initialize();
	plugin::hookfunc(moduleBase + 0x86A920,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_14086B520),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14086B520));
	//ccSceneFreeBattle::Finalize();
	plugin::hookfunc(moduleBase + 0x86A0A0,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_14086ACA0),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14086ACA0));
	//ns2::ccTaskCameraJudge::ChangeAlgorithm
	/*plugin::hookfunc(moduleBase + 0xAB6380,
		reinterpret_cast<LPVOID>(&Common::Hooked_sub_140AB6F80),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140AB6F80));*/
	//IA Scene name output code for _script and _xml 
	plugin::hookfunc(moduleBase + 0x66D040,
		reinterpret_cast<LPVOID>(&Common::Hooked_IASceneName_CutSymbol),
		reinterpret_cast<LPVOID*>(&Common::orig_Hooked_IASceneName_CutSymbol));
	//FreeBattle
	Common::PatchMemoryAtOffsetInt32(0x87827B, 0x1BF8);
	//Practice Battle
	Common::PatchMemoryAtOffsetInt32(0x878ABB, 0x1BF8);
	//League Battle
	Common::PatchMemoryAtOffsetInt32(0x87863B, 0x1BF8);
	//Tournament Battle
	Common::PatchMemoryAtOffsetInt32(0x8793EB, 0x1BF8);
	//Survival Battle
	Common::PatchMemoryAtOffsetInt32(0x87902B, 0x1BF8);
	//Network Endless Battle
	Common::PatchMemoryAtOffsetInt32(0x870BFB, 0x1BF8);
	//Network Event Battle
	Common::PatchMemoryAtOffsetInt32(0x87233B, 0x1BF8);
	//Network League Battle
	Common::PatchMemoryAtOffsetInt32(0x870F5B, 0x1BF8);
	//Network Player Battle
	Common::PatchMemoryAtOffsetInt32(0x87137B, 0x1BF8);
	//Network Rank Battle
	Common::PatchMemoryAtOffsetInt32(0x8716DB, 0x1BF8);

	//Lua Scripts
	Common::PatchWithNops(0xAB1FC0, 5);
	plugin::hookfunc(moduleBase + 0xAAA540,
		reinterpret_cast<LPVOID>(&LuaScript::Hooked_ns2_tolua_ccRegistScript_open),
		reinterpret_cast<LPVOID*>(&LuaScript::orig_ns2_tolua_ccRegistScript_open));

	//Skip Intro 
	if (GetPrivateProfileInt("General", "skip_opening", 1, config_path.c_str()) == 1)
	{
		Common::PatchMemoryAtOffsetInt32(0xAD16F1, 0x80);
	}
	//Character Controls
	plugin::hookfunc(moduleBase + 0xA201D0,
		reinterpret_cast<LPVOID>(&Common::CtrlInputPad),
		reinterpret_cast<LPVOID*>(&Common::orig_CtrlInputPad));

	

	//Kaguya's Condition D-Pad fix
	plugin::hookfunc(moduleBase + 0x643270,
		reinterpret_cast<LPVOID>(&Common::sub_140643E70),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140643E70));

	//Skip CRC32 conversion
	plugin::hookfunc(moduleBase + 0x1072D30,
		reinterpret_cast<LPVOID>(&Common::GetTextFromCRC32Code),
		reinterpret_cast<LPVOID*>(&Common::orig_GetTextFromCRC32Code));



	//Creates Jutsu Selector Info
	plugin::hookfunc(moduleBase + 0x748C40,
		reinterpret_cast<LPVOID>(&Common::hook_sub_140749840),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140749840));

	//Set Jutsu Selector Info to character Data
	plugin::hookfunc(moduleBase + 0x746520,
		reinterpret_cast<LPVOID>(&Common::sub_140747120),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140747120));



	//ModManager Update Notification
	plugin::hookfunc(moduleBase + 0x7E7450,
		reinterpret_cast<LPVOID>(&ModManager::sub_1407E8050_SC),
		reinterpret_cast<LPVOID*>(&ModManager::orig_sub_1407E8050));

	//Title Screen time before it start to play opening
	Common::PatchMemoryAtOffsetInt16(0x8DF573, 0xFFFF);

	//Fix for ME_CAMERA_LOOKAT_SET
	plugin::hookfunc(moduleBase + 0xA3EE50,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_CAMERA_LOOKAT_SET),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_CAMERA_LOOKAT_SET));



	//Fix for ME_CAMERA_LOOKAT_SET_HUGEAWAKE2
	plugin::hookfunc(moduleBase + 0xA3EE90,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_CAMERA_LOOKAT_SET_HUGEAWAKE2),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_CAMERA_LOOKAT_SET_HUGEAWAKE2));


	//Moveset Plus functions not for release
	HookFunctions::Hook((void*)(moduleBase + 0xA40740), MovesetPlus::meTest2, 16);


	//Gauge initialization
	plugin::hookfunc(moduleBase + 0x72ABA0,
		reinterpret_cast<LPVOID>(&Common::sub_14072B7A0_NSC),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14072B7A0_NSC));

	//Gauge Set Rate for bars
	plugin::hookfunc(moduleBase + 0x72C9B0,
		reinterpret_cast<LPVOID>(&Common::sub_14072D5B0_NSC),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_14072D5B0_NSC));


	//Disable Smoke for Akamaru
	Common::PatchMemoryAtOffsetInt32(0x9C0AFA, 0x00);
	Common::PatchMemoryAtOffsetInt32(0x19D5A1, 0x00);
	Common::PatchMemoryAtOffsetInt8(0xA0F41A, 0x05);
	Common::PatchMemoryAtOffsetInt32(0xA0F427, 0x04);


	//Fix for ME_DRAWOBJ_ENABLE
	plugin::hookfunc(moduleBase + 0xA40410,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_DRAWOBJ_ENABLE),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_DRAWOBJ_ENABLE));
	//Fix for ME_DRAWOBJ_DISABLE
	plugin::hookfunc(moduleBase + 0xA40330,
		reinterpret_cast<LPVOID>(&MovesetPlus::ME_DRAWOBJ_DISABLE),
		reinterpret_cast<LPVOID*>(&MovesetPlus::orig_ME_DRAWOBJ_DISABLE));


	//Fix for Stand position 
	plugin::hookfunc(moduleBase + 0xA32690,
		reinterpret_cast<LPVOID>(&Common::IsInFrontOfOwner),
		reinterpret_cast<LPVOID*>(&Common::orig_IsInFrontOfOwner));
	//Fix for Stand Sound 
	plugin::hookfunc(moduleBase + 0xA34610,
		reinterpret_cast<LPVOID>(&Common::ccPlayerPartner2AKM_OnThroughDamage),
		reinterpret_cast<LPVOID*>(&Common::orig_ccPlayerPartner2AKM_OnThroughDamage));

	//Fix for Stand Smoke effect 
	plugin::hookfunc(moduleBase + 0x9DE980,
		reinterpret_cast<LPVOID>(&Common::EntrySmokeAtPartnerPos),
		reinterpret_cast<LPVOID*>(&Common::orig_EntrySmokeAtPartnerPos));

	//Memory Allocate for 2kib condition
	Common::PatchMemoryAtOffsetInt32(0x9F4729, 0x12D60);
	//Expand 2kib condition  
	plugin::hookfunc(moduleBase + 0x638AC0,
		reinterpret_cast<LPVOID>(&Common::CharacterManager_1CMN),
		reinterpret_cast<LPVOID*>(&Common::orig_CharacterManager_1CMN));

	//Change camera function for 2kib condition to enable screen effect
	plugin::hookfunc(moduleBase + 0x9FE890,
		reinterpret_cast<LPVOID>(&Common::sub_1409FF490),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_1409FF490));


	//Fix for Player Double Effect param for 2akm
	plugin::hookfunc(moduleBase + 0x664f30,
		reinterpret_cast<LPVOID>(&Common::sub_14083B360),
		reinterpret_cast<LPVOID*>(&Common::orig_nullsub_3187));


	//damage reaction 
	plugin::hookfunc(moduleBase + 0x99CAF0,
		reinterpret_cast<LPVOID>(&Common::GetDamageReactionAction),
		reinterpret_cast<LPVOID*>(&Common::orig_GetDamageReactionAction));

	//TUJ Unlock
	plugin::hookfunc(moduleBase + 0x6612D0,
		reinterpret_cast<LPVOID>(&TUJManager::sub_140661ED0),
		reinterpret_cast<LPVOID*>(&TUJManager::orig_sub_140661ED0));

	//Fix for 3v3 for jutsu selector
	plugin::hookfunc(moduleBase + 0x743EF0,
		reinterpret_cast<LPVOID>(&Common::sub_140744AF0),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140744AF0));



	//ccUiFlashCharacterSelect::CosSklCstmFunc 
	plugin::hookfunc(moduleBase + 0x738620,
		reinterpret_cast<LPVOID>(&Common::sub_140739220),
		reinterpret_cast<LPVOID*>(&Common::orig_sub_140739220));


	////Battle Timer Control
	//plugin::hookfunc(moduleBase + 0x93BBD0,
	//	reinterpret_cast<LPVOID>(&Common::sub_14093C7D0),
	//	reinterpret_cast<LPVOID*>(&Common::orig_sub_14093C7D0));
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
// Iterate through all the plugins, and apply their hooks.
void HookFunctions::InitializePluginHooks()
{
	std::vector<Mod*> modList = PluginManager::GetModList();
	int modCount = modList.size();
	for (int mod = 0; mod < modCount; mod++)
	{
		Mod* m = modList[mod];

		std::vector<Plugin*> pluginList = m->pluginList;
		int pluginCount = pluginList.size();
		for (int plugin = 0; plugin < pluginCount; plugin++)
		{
			Plugin* p = pluginList[plugin];
			HINSTANCE hGetProcIDDLL = (HINSTANCE)(p->hInstance);

			typedef void(__stdcall* hookfunct)(__int64 moduleBase, __int64 hookFunction);
			hookfunct funct = (hookfunct)GetProcAddress(hGetProcIDDLL, "InitializeHooks");
			if (funct) funct(moduleBase, (__int64)HookFunctions::HookPlugin);
		}
	}
}


std::vector<__int64> HookFunctions::PluginHookAddress;
std::vector<__int64> HookFunctions::PluginHookOriginal;
std::vector<int> HookFunctions::PluginHookLength;

// Credits for this function to: GuidedHacking, Broihon, Traxin & A200K
bool HookFunctions::Hook(void* toHook, void* ourFunct, int len, bool isPlugin)
{
	DWORD MinLen = 14;

	if (len < MinLen)
	{
		return false;
	}

	BYTE stub[] = { 0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
					0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	void* pTrampoline = VirtualAlloc(0, len + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD dwOld = 0;

	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &dwOld);

	DWORD64 retto = (DWORD64)toHook + len;

	// trampoline
	memcpy(stub + 6, &retto, 8);
	memcpy((void*)((DWORD_PTR)pTrampoline), toHook, len);
	memcpy((void*)((DWORD_PTR)pTrampoline + len), stub, sizeof(stub));

	// orig
	memcpy(stub + 6, &ourFunct, 8);

	if (isPlugin)
	{
		void* originalBytes = VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		memcpy(originalBytes, toHook, len);

		PluginHookAddress.push_back((__int64)toHook);
		PluginHookOriginal.push_back((__int64)originalBytes);
		PluginHookLength.push_back(len);
	}

	memcpy(toHook, stub, sizeof(stub));

	for (int i = MinLen; i < len; i++)
	{
		*(BYTE*)((DWORD_PTR)toHook + i) = 0x90;
	}
	VirtualProtect(toHook, len, dwOld, &dwOld);

	return true;
}

// Function used to hook
bool HookFunctions::HookPlugin(void* toHook, void* ourFunct, int len)
{
	cout << toHook << endl;
	return HookFunctions::Hook(toHook, ourFunct, len, true);
}

void HookFunctions::UnhookPlugins()
{
	for (int x = 0; x < PluginHookAddress.size(); x++)
	{
		void* address = (void*)PluginHookAddress[x];
		void* bytes = (void*)PluginHookOriginal[x];
		int len = PluginHookLength[x];

		DWORD dwOld = 0;
		VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy(address, bytes, len);
		VirtualProtect(address, len, dwOld, &dwOld);

		VirtualFree((void*)PluginHookOriginal[x], len, MEM_RESET);
	}

	PluginHookAddress.clear();
	PluginHookOriginal.clear();
	PluginHookLength.clear();
}

//Hooks a singular function.
bool plugin::hookfunc(__int64 funcaddr, LPVOID detourfunc, LPVOID* originalfunc = NULL) {
	bool status = MH_CreateHook((LPVOID)funcaddr, detourfunc, originalfunc);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be created." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was created." << std::endl;
	plugin::funclist.push_back(funcaddr);
	return 1;
}

//Initializes Minhook
bool plugin::init() {
	if (MH_Initialize() == MH_OK) {
		if (enablemessages)
			std::cout << "Minhook initialized" << std::endl;
		return 1;
	}
	if (enablemessages)
		std::cout << "Minhook not initialized" << std::endl;
	return 0;
}

//Enables a single hook.
bool plugin::enablehook(__int64 funcaddr) {
	bool status = MH_EnableHook((LPVOID)funcaddr);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be enabled." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was enabled." << std::endl;
	return 1;
}

//Disables a single hook.
bool plugin::disablehook(__int64 funcaddr) {
	bool status = MH_DisableHook((LPVOID)funcaddr);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be disabled." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was disabled." << std::endl;
	return 1;
}

//Enables every hook initialized in hookall.
void plugin::enableall() {
	for (__int64 i : plugin::funclist) {
		plugin::enablehook(i);
	}
}
bool HookFunctions::ReplaceBytes(void* address, const uint8_t* newBytes, size_t size)
{
	DWORD oldProtect;
	if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;

	memcpy(address, newBytes, size);

	DWORD tempProtect;
	VirtualProtect(address, size, oldProtect, &tempProtect);
	FlushInstructionCache(GetCurrentProcess(), address, size);
	return true;
}
