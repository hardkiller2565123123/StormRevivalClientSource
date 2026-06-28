#pragma once
#include <string>
#include <Windows.h>  //   HMODULE
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>


class ModManager
{
public:
	

	typedef __int64(__fastcall* orig_sub_140695424_t)(__int64 a1, __int64 a2);
	static orig_sub_140695424_t orig_sub_140695424;
	static __int64 __fastcall sub_140695424_S4(__int64 a1, __int64 a2);


	typedef __int64(__fastcall* orig_sub_1407E8050_t)(__int64 a1, __int64 a2);
	static orig_sub_1407E8050_t orig_sub_1407E8050;
	static __int64 __fastcall sub_1407E8050_SC(__int64 a1, __int64 a2);
};
