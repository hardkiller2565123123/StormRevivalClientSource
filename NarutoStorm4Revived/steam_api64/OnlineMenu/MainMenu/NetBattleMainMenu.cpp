#include "NetBattleMainMenu.h"
#include "../Flash/FlashBridge.h"

namespace StormRevival::OnlineMenu::MainMenu
{
    static constexpr Flash::FlashTarget Target{ "netbattlemainmenu", "_root.all_nut" };

    void Initialize(GamePtr ui) { Flash::CallNoArgs(ui, Target, "Initialize"); }
    void Start(GamePtr ui) { Flash::CallNoArgs(ui, Target, "Start"); }
    void Lock(GamePtr ui) { Flash::CallNoArgs(ui, Target, "SetLock"); }
    void Unlock(GamePtr ui) { Flash::CallNoArgs(ui, Target, "SetUnLock"); }
    void Restart(GamePtr ui) { Flash::CallNoArgs(ui, Target, "Restart"); }
    void Message(GamePtr ui, const char* text) { Flash::CallString(ui, Target, "MessageCall", text); }
    void SetEventLock(GamePtr ui, bool locked) { Flash::CallBool(ui, Target, "SetEventLock", locked); }
    void SetBingoItem(GamePtr ui, bool enabled) { Flash::CallBool(ui, Target, "SetBingoItem", enabled); }

    void VoiceIn(GamePtr ui)
    {
        Flash::CallNoArgs(ui, Target, "MatchingVoiceAnmLoop");
    }

    void VoiceOut(GamePtr ui)
    {
        Flash::CallNoArgs(ui, Target, "MatchingVoiceAnmOut");
    }

    void SetVoiceText(GamePtr ui, const char* text)
    {
        Flash::CallString(ui, Target, "SetMatchingVoice", text ? text : "");
    }


    void RenameStoreButtonToSettings(GamePtr ui)
    {
        /*
            The stock SWF owns the real text fields. These method names are safe
            runtime probes. On builds where the SWF exposes a menu text setter, the
            visible Store label becomes Settings. If the SWF ignores the call, the
            click route still opens Settings through StoreReplacement.
        */
        Flash::CallString(ui, Target, "SetStoreText", "Settings");
        Flash::CallString(ui, Target, "SetStoreLabel", "Settings");
        Flash::CallString(ui, Target, "SetButtonText", "Settings");
        Flash::CallString(ui, Target, "ReplaceMenuText", "Store:Settings");
    }

    void RenameStoreButtonToOpenArchive(GamePtr ui)
    {
        Flash::CallString(ui, Target, "SetStoreText", "OpenArchive");
        Flash::CallString(ui, Target, "SetStoreLabel", "OpenArchive");
        Flash::CallString(ui, Target, "SetButtonText", "OpenArchive");
        Flash::CallString(ui, Target, "ReplaceMenuText", "Store:OpenArchive");
        Flash::CallString(ui, Target, "ReplaceMenuText", "General Store Bandai:OpenArchive");
    }

}
