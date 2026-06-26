#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    struct RuntimeInjectionSettings
    {
        bool Enabled = true;
        bool TryAfterInitialize = true;
        const char* Label = "Settings";
        int Mode = 100;
    };

    RuntimeInjectionSettings& RuntimeSettings();

    void OnNetBattleMainMenuInitialized(GamePtr sceneOrFlashObject);

    bool TryHandleNoArgFlashCall(
        GamePtr sceneOrFlashObject,
        const char* movie,
        const char* root,
        const char* functionName);

    bool TryHandleSelectedMode(GamePtr menuUi, int mode);
}
