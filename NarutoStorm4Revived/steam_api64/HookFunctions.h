#ifndef HOOKFUNCTIONS_H 
#define HOOKFUNCTIONS_H
#pragma once

#include <Windows.h>
#include <vector>

class HookFunctions
{
public:
	static void InitializeHooksAll();
	static void InitializeHooksS4();
	static void InitializeHooksSC();
	static void InitializePluginHooks();

	static bool Hook(void*, void*, int, bool isPlugin = false);
	static bool HookPlugin(void*, void*, int);
	static void UnhookPlugins();
	static bool ReplaceBytes(void* address, const uint8_t* newBytes, size_t size);

	static std::vector<__int64> PluginHookAddress;
	static std::vector<__int64> PluginHookOriginal;
	static std::vector<int> PluginHookLength;


};

#endif
namespace plugin {
	bool init();
	void hookall();
	bool hookfunc(__int64 funcaddr, LPVOID detourfunc, LPVOID* originalfunc);
	void enableall();
	bool enablehook(__int64 funcaddr);
	bool disablehook(__int64 funcaddr);
	inline std::vector<__int64> funclist;
}