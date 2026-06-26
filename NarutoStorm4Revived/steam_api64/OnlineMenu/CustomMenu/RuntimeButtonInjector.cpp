#include "RuntimeButtonInjector.h"
#include "MainMenuOptionRegistry.h"
#include "RealMenuOptionInjector.h"
#include "InGameSettingsPanel.h"
#include "../Flash/FlashBridge.h"
#include "../Core/SRLogger.h"
#include "../MainMenu/NetBattleMainMenu.h"

#include <cstring>

namespace StormRevival::OnlineMenu::CustomMenu
{
    RuntimeInjectionSettings& RuntimeSettings()
    {
        static RuntimeInjectionSettings s;
        return s;
    }

    static bool Same(const char* a, const char* b)
    {
        return a && b && std::strcmp(a, b) == 0;
    }

    static void TryMethod(GamePtr ui, const char* method, const char* label, int mode)
    {
        Flash::TraceCall(Flash::NetBattleMainMenu, method, 2);
        Log::Info(std::string("Runtime menu injection test: ") + method +
            "(\"" + label + "\", " + std::to_string(mode) + ")");
        (void)ui;
    }

    void OnNetBattleMainMenuInitialized(GamePtr sceneOrFlashObject)
    {
        auto& s = RuntimeSettings();
        if (!s.Enabled)
            return;

        MainMenuOptionRegistry::Instance().ResetToDefaults();

        Log::Info("Detected netbattlemainmenu.Initialize. Attempting to add Settings button at runtime.");
        Log::Info("No SWF edit. Stock Store is renamed/routed to Settings while true extra row is researched.");
        MainMenu::RenameStoreButtonToSettings(sceneOrFlashObject);

        TryMethod(sceneOrFlashObject, "AddMenuItem", s.Label, s.Mode);
        TryMethod(sceneOrFlashObject, "AddItem", s.Label, s.Mode);
        TryMethod(sceneOrFlashObject, "AddButton", s.Label, s.Mode);
        TryMethod(sceneOrFlashObject, "SetMenuItem", s.Label, s.Mode);
        TryMethod(sceneOrFlashObject, "SetButtonText", s.Label, s.Mode);

        TryAddRowsBelowOnlineMatch(sceneOrFlashObject);
    }

    bool TryHandleNoArgFlashCall(GamePtr sceneOrFlashObject, const char* movie, const char* root, const char* functionName)
    {
        auto& s = RuntimeSettings();
        if (!s.Enabled || !s.TryAfterInitialize)
            return false;

        if (!Same(movie, "netbattlemainmenu"))
            return false;
        if (!Same(functionName, "Initialize"))
            return false;

        Log::Info(std::string("Flash hook saw netbattlemainmenu.Initialize root=") + (root ? root : "<null>"));
        OnNetBattleMainMenuInitialized(sceneOrFlashObject);
        return true;
    }

    bool TryHandleSelectedMode(GamePtr menuUi, int mode)
    {
        auto& s = RuntimeSettings();
        if (!s.Enabled)
            return false;

        if (mode != s.Mode && !MainMenuOptionRegistry::Instance().IsCustomMode(mode))
            return false;

        Log::Info("Custom runtime menu mode selected: " + std::to_string(mode));

        if (HandleSyntheticMode(menuUi, mode))
            return true;

        ShowSettingsPanel();
        return true;
    }
}
