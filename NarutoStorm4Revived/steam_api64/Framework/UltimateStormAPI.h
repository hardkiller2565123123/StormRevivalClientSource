#ifndef CCMAIN_H 
#define CCMAIN_H
#pragma once

#include <atomic>
#include <vector>
#include <string>

static bool enablemessages = 0;
extern std::string config_path;

//    (  UltimateStormAPI.cpp)
extern std::atomic_bool g_IsUpdateAvailable;
extern std::string g_RemoteLatestVersion;

class UltimateStormAPI
{
public:
    static int __stdcall Main();
    static int __stdcall LoopConsole();
    static int __stdcall LoopGame();

    static void Update();
    static void PreRender();
    static void PostRender();
    static void OnGUI(bool s, __int64 hwnd, __int64 imguiContext);

    static void ReadFrameworkFiles(bool isReloading = false);

};

#endif
