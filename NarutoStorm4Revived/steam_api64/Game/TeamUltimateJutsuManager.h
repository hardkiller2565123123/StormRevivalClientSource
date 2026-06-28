
#include <string>
class TUJManager {
public:
	static void ExpandTeamUltimateArray();
	static void ReadPairSpSkillManagerParam(std::string _file);


	typedef bool(__fastcall* orig_sub_140661ED0_t)(__int64 a1, __int64* a2, int a3);
	static orig_sub_140661ED0_t orig_sub_140661ED0;
	static bool __fastcall sub_140661ED0(__int64 a1, __int64* a2, int a3);


	typedef bool(__fastcall* orig_sub_140590818_t)(__int64 a1, __int64* a2, int a3);
	static orig_sub_140590818_t orig_sub_140590818;
	static bool __fastcall sub_140590818(__int64 a1, __int64* a2, int a3);
};
