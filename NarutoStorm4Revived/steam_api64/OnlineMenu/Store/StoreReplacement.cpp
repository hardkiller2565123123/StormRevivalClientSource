#include "StoreReplacement.h"
#include "../MainMenu/NetBattleMainMenu.h"
#include "../Settings/SettingsHub.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::Store
{
    void Install()
    {
        /*
            Offline build behavior:
            - The stock Store button is reused as the Settings entry.
            - No Steam store / external browser is opened.
            - The visible label is attempted through Flash method calls. If the stock
              SWF ignores those calls, the click still routes to Settings.
        */
        Log::Info("StoreReplacement installed. Store button is routed to StormRevival Settings.");
        Log::Info("Store label rename target: Store -> Settings.");
    }

    bool ShouldBlockSteamStore()
    {
        return true;
    }

    void ShowStoreReplacement(GamePtr ui)
    {
        Log::Info("Store button selected; opening StormRevival Settings instead.");
        MainMenu::RenameStoreButtonToSettings(ui);
        Settings::Show(ui);
    }
}
