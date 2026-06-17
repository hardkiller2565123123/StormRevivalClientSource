#pragma once
#include <Windows.h>
#include <vector>

typedef int(__fastcall* r) (__int64 a1);
inline r osusanoojump = NULL;
namespace ns4 {
	inline std::vector<int> susanoocharlist;
	inline std::vector<int> charlist;
	class player
	{
	public:
		static int __fastcall susanoojumps4(__int64 a1);
	};

}

namespace nsc {
	inline std::vector<int> susanoocharlist;
	inline std::vector<int> charlist;
	class player
	{
	public:
		static int __fastcall susanoojumpnsc(__int64 a1);
	};

}

class SusanooCondManager {
public:
	static void ReadSusanooCondParam(std::string _file);
};