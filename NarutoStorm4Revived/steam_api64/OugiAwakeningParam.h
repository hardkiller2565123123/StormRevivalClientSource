
#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include "PatternScan.h"
#include <unordered_set>
#include <mutex>


class OugiAwakeningParam
{
public:
	typedef __int64(__fastcall* orig_sub_1407D3A64_S4_t)(__int64 a1, __int64 a2);
	static orig_sub_1407D3A64_S4_t orig_sub_1407D3A64_S4;

	typedef __int64(__fastcall* orig_sub_140A0E010_SC_t)(__int64 a1);
	static orig_sub_140A0E010_SC_t orig_sub_140A0E010_SC;


	static __int64 __fastcall sub_1407D3A64_S4(__int64 a1, __int64 a2);
	static __int64 __fastcall sub_14079BB7C_SC(__int64 a1);
	//  32- little-endian ID   
	static void ReadOugiAwakeningParamFile(const std::string& filename);

	//    ID
	static bool IsOugiAwakeningCharID(uint32_t id);

private:
	static std::unordered_set<uint32_t> s_ougiCharIDs;
	static std::vector<uint32_t> s_ougiCharIDList;
	static std::mutex s_ougiCharIDsMutex;
};
