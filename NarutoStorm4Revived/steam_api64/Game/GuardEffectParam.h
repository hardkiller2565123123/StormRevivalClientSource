
#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "PatternScan.h"
#include <unordered_set>
#include <mutex>


class GuardEffectParam
{
public:
	typedef __int64(__fastcall* orig_sub_1409D6220_t)(__int64 a1, int a2);
	static orig_sub_1409D6220_t orig_sub_1409D6220;

	typedef __int64(__fastcall* t_sub_1409D5040)(__int64 a1, int a2, int a3);
	static t_sub_1409D5040 orig_sub_1409D5040;

	typedef void** (__fastcall* sub_140981280_t)(__int64 a1);
	static sub_140981280_t orig_sub_140981280;

    static void ReadGuardEffectParam(const std::string& filename);
	static __int64 __fastcall sub_1409D6220_SC(__int64 a1, int a2);
	static void __fastcall hk_sub_1409D5040_SC(__int64 a1, int a2, int a3);
	static void** __fastcall hk_sub_140981280_SC(__int64 a1);



	typedef __int64(__fastcall* orig_sub_1407AFADC_t)(__int64 a1, int a2);
	static orig_sub_1407AFADC_t orig_sub_1407AFADC;

	typedef void**(__fastcall* t_sub_1407AEBF8)(__int64 a1, int a2, int a3);
	static t_sub_1407AEBF8 orig_sub_1407AEBF8;

	typedef __int64(__fastcall* sub_140775D8C_t)(__int64 a1);
	static sub_140775D8C_t orig_sub_140775D8C;

	static __int64 __fastcall sub_1407AFADC_S4(__int64 a1, __int64 a2);
	static void** __fastcall hk_sub_1407AEBF8_S4(__int64 a1, int a2, __int64 a3);
	static __int64 __fastcall hk_sub_140775D8C_S4(__int64 a1);
	

private:
	static std::unordered_set<uint32_t> s_ougiCharIDs;
	static std::vector<uint32_t> s_ougiCharIDList;
	static std::mutex s_ougiCharIDsMutex;
};
struct GuardEffectParamEntry {
	uint32_t CharacodeID;
	uint32_t Mode;
	std::string EffectPath;
	std::string StartEffect;
	std::string LoopEffect;
	std::string EndEffect;
	std::string Coord;
};