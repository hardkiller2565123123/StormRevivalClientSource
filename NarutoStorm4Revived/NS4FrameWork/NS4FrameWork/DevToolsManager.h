#pragma once

#include "StdInc.h"

namespace DevToolsManager
{
    bool Init();
    void Shutdown();
    void DrawPage();
    void TickHotkeys();

    void SetCurrentScene(const char* sceneName);
    void SetNetworkState(const char* stateText);
    void SetLobbyState(const char* stateText);
    void AddSceneTransition(const char* fromScene, const char* toScene);
    void AddLoadedPath(const char* path);
    void AddNetworkEvent(const char* eventText);
}
