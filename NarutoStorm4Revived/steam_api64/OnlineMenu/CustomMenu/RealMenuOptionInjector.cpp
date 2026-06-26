#include "RealMenuOptionInjector.h"
#include "MainMenuOptionRegistry.h"
#include "InGameSettingsPanel.h"
#include "../Flash/FlashBridge.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    InjectionResult TryAddRowsBelowOnlineMatch(GamePtr netBattleMainMenuUi)
    {
        InjectionResult result;
        result.Attempted = true;

        auto& registry = MainMenuOptionRegistry::Instance();
        if (registry.Options().empty())
            registry.ResetToDefaults();

        Log::Info("Trying to add real custom rows below Online Match without replacing stock buttons.");

        for (const auto& option : registry.Options())
        {
            if (!option.Enabled || !option.InsertBelowOnlineMatch)
                continue;

            ++result.AddedCount;

            // Safe trace/stub path. The real renderer needs the Flash option-list provider hook.
            Flash::TraceCall(Flash::NetBattleMainMenu, "AddMenuOptionBelowOnlineMatch", 3);
            Flash::CallText(netBattleMainMenuUi, Flash::NetBattleMainMenu, "MessageCall", option.Label.c_str());
        }

        result.Added = result.AddedCount > 0;

        if (result.Added)
        {
            Log::Info("Custom option rows registered. If they do not visibly render, hook netbattlemainmenu option provider next.");
        }

        return result;
    }

    bool HandleSyntheticMode(GamePtr menuUi, int mode)
    {
        const auto* option = MainMenuOptionRegistry::Instance().FindByMode(mode);
        if (!option)
            return false;

        Log::Info("Handling synthetic menu option mode " + std::to_string(mode) + ": " + option->Label);

        switch (mode)
        {
        case 100:
            ShowSettingsPanel();
            Flash::CallText(menuUi, Flash::NetBattleMainMenu, "MessageCall", "StormRevival Settings");
            return true;

        case 101:
            Flash::CallText(menuUi, Flash::NetBattleMainMenu, "SetVoiceText", "StormRevival Status\\nOffline Online Menu Build\\nPlayers: stub");
            return true;

        case 102:
            Flash::CallText(menuUi, Flash::NetBattleMainMenu, "MessageCall", "Unlock All is a visible stub only.");
            return true;

        default:
            Flash::CallText(menuUi, Flash::NetBattleMainMenu, "MessageCall", option->Label.c_str());
            return true;
        }
    }
}
