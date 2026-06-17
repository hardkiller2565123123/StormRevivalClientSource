#pragma once
#include <string>
#include <Windows.h>  //   HMODULE
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>

extern __int64 moduleBase;
extern __int64 moduleLength;
extern __int64 st_hModule;
extern HMODULE g_hModule;   //   (extern)
extern __int64 datasection;

extern std::string game;
extern const char* GameVersion;
extern bool isDebug;
extern bool EnableAPI;
extern int PluginState;
struct AdvInline {
	char buf[16];        // 0..15 inline bytes
	uint64_t length;     // +16
	uint64_t flag;       // +24 (<0x10 => inline)
};
namespace render {
	inline int hudon = 2;
	inline int pause = 0;
	inline float timer_speed = 1.0f;

	inline __int64 CoordByFullName = 0;
	inline __int64 WorldPosNew = 0;
	inline char* WorldPosData[24];


	inline float stiffnessFactor = 1.0f;               //    60fps -> 0.5
	inline float bouncinessFactor = 1.0f; // :  60fps ~0.625,  30fps 1.0
	inline float elasticityFactor = 1.0f; //  60fps ~1.125 (  )
	inline AdvInline advDemoId;
	inline float movementFactor = 1.0f;

	inline __int64* jutsu_ptr = 0;
	inline bool skip_crc32_conv = false;

}
inline __int64 hudon_address = 0;


class Common
{
public:
	static __int64 hudon_address;
	static std::string to_lower_ascii(const std::string& s);

	//   default-   
	static bool MatchesFileName(const std::string& pathOrName, const std::string& targetName, bool caseInsensitive = true);
	static __int64 __fastcall sub_14132B8B0_SC(__int64 a1, int a2);

	//typedef void(__fastcall* Sub1413268E0_t)(int64_t a1, int64_t a2, unsigned int* a3, unsigned short a4);
	//static Sub1413268E0_t Original_sub_1413268E0;
	//static void __fastcall Hooked_sub_1413268E0_SC(int64_t a1, int64_t a2, unsigned int* a3, unsigned short a4);

	//static unsigned char* __fastcall sub_14066DBD0();
	//static void __fastcall sub_1405674F0(const char* a1);

	typedef __int64(__fastcall* orig_sub_14086B520_t)(__int64 a1);
	static orig_sub_14086B520_t orig_sub_14086B520;

	typedef __int64(__fastcall* orig_sub_14086ACA0_t)(__int64 a1);
	static orig_sub_14086ACA0_t orig_sub_14086ACA0;

	typedef __int64(__fastcall* orig_sub_140868D60_t)(__int64 a1);
	static orig_sub_140868D60_t orig_sub_140868D60;


	typedef __int64(__fastcall* orig_sub_140AB6F80_t)(__int64 a1, __int64 a2);
	static orig_sub_140AB6F80_t orig_sub_140AB6F80;
	static __int64 __fastcall Hooked_sub_140AB6F80(__int64 a1, __int64 a2);



	typedef __int64(__fastcall* orig_CtrlInputPad_t)(__int64 a1);
	static orig_CtrlInputPad_t orig_CtrlInputPad;
	static __int64 __fastcall CtrlInputPad(__int64 a1);

	typedef __int64(__fastcall* orig_Hooked_IASceneName_CutSymbol_t)(__int64 a1, char* a2);
	static orig_Hooked_IASceneName_CutSymbol_t orig_Hooked_IASceneName_CutSymbol;
	static __int64 __fastcall Hooked_IASceneName_CutSymbol(__int64 a1, char* a2);


	typedef __int64(__fastcall* orig_sub_140643E70_t)(__int64 a1);
	static orig_sub_140643E70_t orig_sub_140643E70;
	static __int64 __fastcall sub_140643E70(__int64 a1);


	typedef __int64(__fastcall* orig_sub_140744AF0_t)(__int64 a1, int a2);
	static orig_sub_140744AF0_t orig_sub_140744AF0;
	static __int64 __fastcall sub_140744AF0(__int64 a1, int a2);

	typedef __int64(__fastcall* orig_sub_14093C7D0_t)(__int64 a1);
	static orig_sub_14093C7D0_t orig_sub_14093C7D0;
	static __int64 __fastcall sub_14093C7D0(__int64 a1);

	typedef void(__fastcall* orig_sub_140739220_t)(__int64 a1, __int64 a2);
	static orig_sub_140739220_t orig_sub_140739220;
	static void __fastcall sub_140739220(__int64 a1, __int64 a2);

	/*typedef __int64(__fastcall* orig_addSkillInfoFunc_t)(__int64 a1, int a2, unsigned int a3, __int64* a4, int a5);
	static orig_addSkillInfoFunc_t orig_addSkillInfoFunc;
	static __int64 __fastcall addSkillInfoFunc(__int64 a1, int a2, unsigned int a3, __int64* a4, int a5);

	typedef __int64(__fastcall* orig_addSpAtkInfoFunc_t)(__int64 a1, int a2, int a3, __int64* a4);
	static orig_addSpAtkInfoFunc_t orig_addSpAtkInfoFunc;
	static __int64 __fastcall addSpAtkInfoFunc(__int64 a1, int a2, int a3, __int64* a4);*/

	typedef void(__fastcall* orig_sub_14071EF30_t)(
		__int64 a1,
		__int64 a2,
		__int64 a3,
		__int64 a4,
		__int64 a5,
		__int64 a6,
		__int64 a7,
		unsigned int a8);
	static orig_sub_14071EF30_t orig_sub_14071EF30;
	static void __fastcall sub_14071EF30(
		__int64 a1,
		__int64 a2,
		__int64 a3,
		__int64 a4,
		__int64 a5,
		__int64 a6,
		__int64 a7,
		unsigned int a8);

	typedef __int64(__fastcall* orig_GetTextFromCRC32Code_t)(char* a1);
	static orig_GetTextFromCRC32Code_t orig_GetTextFromCRC32Code;
	static __int64 __fastcall GetTextFromCRC32Code(char* a1);

	typedef __int64(__fastcall* orig_sub_140749840_t)(__int64 a1, unsigned int a2, int a3, int a4);
	static orig_sub_140749840_t orig_sub_140749840;
	static __int64 __fastcall hook_sub_140749840(__int64 a1, unsigned int a2, int a3, int a4);

	typedef __int64(__fastcall* orig_sub_14071EE00_t)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5);
	static orig_sub_14071EE00_t orig_sub_14071EE00;
	static __int64 __fastcall sub_14071EE00(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5);


	typedef void(__fastcall* orig_sub_140747120_t)(__int64 a1, unsigned int a2);
	static orig_sub_140747120_t orig_sub_140747120;
	static void __fastcall sub_140747120(__int64 a1, unsigned int a2);



	typedef __int64(__fastcall* orig_sub_14063F338_t)(__int64 a1, int a2, int a3, int a4, int a5);
	static orig_sub_14063F338_t orig_sub_14063F338;
	static __int64 __fastcall sub_14063F338(__int64 a1, int a2, int a3, int a4, int a5);


	typedef __int64(__fastcall* orig_sub_14072B7A0_NSC_t)(__int64 a1, unsigned int a2);
	static orig_sub_14072B7A0_NSC_t orig_sub_14072B7A0_NSC;
	static __int64 __fastcall sub_14072B7A0_NSC(__int64 a1, unsigned int a2);


	typedef void(__fastcall* orig_sub_14072D5B0_NSC_t)(__int64 a1);
	static orig_sub_14072D5B0_NSC_t orig_sub_14072D5B0_NSC;
	static void __fastcall sub_14072D5B0_NSC(__int64 a1);

	typedef __int64(__fastcall* orig_sub_140641A90_NS4_t)(int* a1);
	static orig_sub_140641A90_NS4_t orig_sub_140641A90_NS4;
	static __int64 __fastcall sub_140641A90_NS4(int* a1);

	typedef bool(__fastcall* orig_IsInFrontOfOwner_t)(__int64 a1, float a2, float a3, float a4);
	static orig_IsInFrontOfOwner_t orig_IsInFrontOfOwner;
	static bool __fastcall IsInFrontOfOwner(__int64 a1, float a2, float a3, float a4);



	typedef void(__fastcall* orig_ccPlayerPartner2AKM_OnThroughDamage_t)(__int64* a1);
	static orig_ccPlayerPartner2AKM_OnThroughDamage_t orig_ccPlayerPartner2AKM_OnThroughDamage;
	static void __fastcall ccPlayerPartner2AKM_OnThroughDamage(__int64* a1);


	typedef void(__fastcall* orig_EntrySmokeAtPartnerPos_t)(__int64 a1);
	static orig_EntrySmokeAtPartnerPos_t orig_EntrySmokeAtPartnerPos;
	static void __fastcall EntrySmokeAtPartnerPos(__int64 a1);

	typedef __int64* (__fastcall* orig_CharacterManager_1CMN_t)(__int64 a1);
	static orig_CharacterManager_1CMN_t orig_CharacterManager_1CMN;
	static __int64* __fastcall CharacterManager_1CMN(__int64 a1);

	typedef __int64 (__fastcall* orig_sub_1409FF490_t)(__int64* a1);
	static orig_sub_1409FF490_t orig_sub_1409FF490;
	static __int64 __fastcall sub_1409FF490(__int64 a1);


	typedef void(__fastcall* orig_nullsub_3187_t)();
	static orig_nullsub_3187_t orig_nullsub_3187;
	static __int64 __fastcall sub_14083B360(__int64 a1);

	static void __fastcall sub_1400FEC40(__int64* a1);
	static void __fastcall sub_1400FECE0(__int64** a1);


	typedef __int64(__fastcall* orig_GetDamageReactionAction_t)(int* a1, int a2, __int64 a3);
	static orig_GetDamageReactionAction_t orig_GetDamageReactionAction;
	static __int64 __fastcall GetDamageReactionAction(int* a1, int a2, __int64 a3);


	typedef __int64(__fastcall* orig_CtrlAct_PL_ACT_DMG_TO_DOWN_t)(__int64 a1, int a2);
	static orig_CtrlAct_PL_ACT_DMG_TO_DOWN_t orig_CtrlAct_PL_ACT_DMG_TO_DOWN;
	static void __fastcall CtrlAct_PL_ACT_DMG_TO_DOWN(__int64 a1, int a2);


	static int PatchAddress(uintptr_t slotAddress, uintptr_t newFunctionAddress);

	static __int64* sub_14066DBD0();
	static __int64 __fastcall Hooked_sub_14086B520(__int64 a1);
	static __int64 __fastcall sub_140868D60(__int64 a1);
	static __int64 __fastcall Hooked_sub_14086ACA0(__int64 a1);
	static bool MatchesAnyFileName(const std::string& pathOrName, std::initializer_list<std::string> targets, bool caseInsensitive = true);
	static void __fastcall DebugString(const char* Format, ...);
	static const char* __fastcall GetVersion();
	static int __fastcall NoClipCursor(__int64 a1);
	static __int64 __fastcall GetVersionString(std::uintptr_t address);
	static __int64 RecalculateAddress(__int64);
	static std::vector<int> crc32_table();
	static int crc32(const std::string& input);
	static bool WallRun();
	static bool PatchMemoryAtOffsetInt64(uint64_t offset, uint64_t newValue);
	static bool PatchMemoryAtOffsetInt32(uint64_t offset, uint32_t newValue);
	static bool PatchMemoryAtOffsetInt16(uint64_t offset, uint16_t newValue);
	static bool PatchMemoryAtOffsetInt8(uint64_t offset, uint8_t newValue);
	static uint64_t ReadInt64AtOffset(uint64_t offset);
	static bool CopyInt64(uint64_t sourceOffset, uint64_t destOffset);
	static bool PatchWithNops(uintptr_t offset, size_t length);
	static constexpr unsigned int str2int(const char* str, int h)
	{
		return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
	}
	static __int64* GetQwordPtr(__int64 qw)
	{
		__int64 qwr = qw - 0x140000000;               // offset   
		return (__int64*)((moduleBase - 0xC00) + qwr);
	}

	static __int64 GetQword(__int64 qw)
	{
		__int64 qwr = qw - 0x140000000;
		return *(__int64*)((moduleBase - 0xC00) + qwr);
	}

	static __int64* GetXmmword(__int64 addr) {
		__int64 offset = addr - 0x140000000;
		return *(__int64**)((moduleBase - 0xC00) + offset);
	}

	// Get a DWORD value from the game by absolute IDA address
	static int GetDword(__int64 dw)
	{
		__int64 dwr = dw - 0x140000000;
		return *(int*)((moduleBase - 0xC00) + dwr);
	}

	// Get an OFFSET pointer from the game
	static __int64 GetOffset(__int64 of)
	{
		__int64 ofr = of - 0x140000000; // make it consistent: input is absolute IDA addr
		return ((moduleBase - 0xC00) + ofr);
	}
};
