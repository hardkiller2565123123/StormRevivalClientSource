#include "CustomMenuEntry.h"
#include "MainMenuOptionRegistry.h"
#include "RealMenuOptionInjector.h"
#include "RuntimeButtonInjector.h"
#include "../Core/SRLogger.h"
#include "../Flash/FlashBridge.h"
#include "../Research/Progress.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    static EntryDefinition g_entry;

    void Install()
    {
        if (!g_entry.Enabled)
            return;

        MainMenuOptionRegistry::Instance().ResetToDefaults();

        Log::Info("CustomMenuEntry installed for OFFLINE build.");
        Log::Info("Mode 100/101/102 are synthetic custom menu options.");
        Log::Info("This build is configured to add new options, not replace Store/BingoBook.");
        Log::Info("Runtime path: hook netbattlemainmenu Initialize, then inject Settings mode 100.");
    }

    void Shutdown()
    {
        Log::Info("CustomMenuEntry shutdown.");
    }

    void OnCustomEntrySelected()
    {
        Log::Info("StormRevival Settings selected.");
        Log::Info(Research::ProgressTable);
        Flash::CallText(0, Flash::NetBattleMainMenu, "MessageCall", "StormRevival Settings");
    }

    void TryInjectBelowOnlineMatch(GamePtr netBattleMainMenuUi)
    {
        TryAddRowsBelowOnlineMatch(netBattleMainMenuUi);
    }
}
