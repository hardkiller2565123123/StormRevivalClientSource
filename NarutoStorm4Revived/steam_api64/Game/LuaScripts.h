#pragma once
#include <string>
#include <Windows.h>  //   HMODULE
#include <vector>
#include <fstream>
#include <iostream>
#include <streambuf>

class LuaScript
{
public:


	typedef __int64(__fastcall* orig_ns2_tolua_ccRegistScript_open_t)(__int64* a1);
	static orig_ns2_tolua_ccRegistScript_open_t orig_ns2_tolua_ccRegistScript_open;
	static __int64 __fastcall Hooked_ns2_tolua_ccRegistScript_open(__int64* a1);


};
