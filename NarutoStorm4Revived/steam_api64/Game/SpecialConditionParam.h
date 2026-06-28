#pragma once
#include <vector>
#include <string>
#include <fstream>
inline std::vector<int> charfunction;
inline std::vector<int> charcodes;
typedef __int64(__fastcall* gpi)(__int64 player, int charcode);
inline gpi gpio;
typedef __int64*(__fastcall* c)(int characterNum, int a2);
inline c co;


typedef int*(__fastcall* c_nsc)(int characterNum, int a2);
inline c_nsc co_nsc;

typedef unsigned char BYTE;



class SpecialCondParam {
public:


	static void ReadSpecialConditionParam(std::string _file);
	static __int64* __fastcall Create(int characterNum, int a2);
	static int* __fastcall Create_NSC(int characterNum, int a2);
	

};
