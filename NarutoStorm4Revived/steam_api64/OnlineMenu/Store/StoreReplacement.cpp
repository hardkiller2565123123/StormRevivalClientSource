#include "StoreReplacement.h"
#include "../MainMenu/NetBattleMainMenu.h"
#include "../OpenArchive/OpenArchiveHub.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::Store
{
    void Install()
    {
        /*
            Offline build behavior:
            - The stock Store button is reused as the OpenArchive entry.
            - No Steam store / external browser is opened.
            - The visible label is attempted through Flash method calls. If the stock
              SWF ignores those calls, the click still routes to OpenArchive.
        */
        Log::Info("StoreReplacement installed. Store button is routed to OpenArchive.");
        Log::Info("Store label rename target: Store -> OpenArchive.");
        OpenArchive::Install();
    }

    bool ShouldBlockSteamStore()
    {
        return true;
    }

    void ShowStoreReplacement(GamePtr ui)
    {
        Log::Info("Store button selected; opening OpenArchive custom menu instead.");
        MainMenu::RenameStoreButtonToOpenArchive(ui);
        OpenArchive::Show(ui);
    }
}
