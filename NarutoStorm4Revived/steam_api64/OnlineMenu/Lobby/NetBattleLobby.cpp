#include "NetBattleLobby.h"
#include "../Flash/FlashBridge.h"

namespace StormRevival::OnlineMenu::Lobby
{
    static constexpr Flash::FlashTarget LobbyTarget{ "netbattlelobby", "_root.all_nut" };

    void Initialize(GamePtr ui)
    {
        Flash::CallNoArgs(ui, LobbyTarget, "Initialize");
    }

    void SetUser(GamePtr ui, int slot, const char* name)
    {
        Flash::CallInt(ui, LobbyTarget, "setUser_slot", slot);
        Flash::CallString(ui, LobbyTarget, "setUser_name", name ? name : "");
    }

    void SetWave(GamePtr ui, int slot, int bars)
    {
        Flash::CallInt(ui, LobbyTarget, "setWave_slot", slot);
        Flash::CallInt(ui, LobbyTarget, "setWave_bars", bars);
    }

    void SetVoice(GamePtr ui, int slot, bool enabled)
    {
        Flash::CallInt(ui, LobbyTarget, "setVoice_slot", slot);
        Flash::CallBool(ui, LobbyTarget, "setVoice", enabled);
    }

    void SetFriend(GamePtr ui, int slot, int state)
    {
        Flash::CallInt(ui, LobbyTarget, "setFriend_slot", slot);
        Flash::CallInt(ui, LobbyTarget, "setFriend_state", state);
    }

    void SetHostNo(GamePtr ui, int slot)
    {
        Flash::CallInt(ui, LobbyTarget, "setHostNo", slot);
    }

    void SetWinStreak(GamePtr ui, int streak)
    {
        Flash::CallInt(ui, LobbyTarget, "setWinStreak", streak);
    }

    void SetNum(GamePtr ui, int current, int max)
    {
        Flash::CallInt(ui, LobbyTarget, "setNum_current", current);
        Flash::CallInt(ui, LobbyTarget, "setNum_max", max);
    }

    void SetReadyState(GamePtr ui, int slot, bool ready)
    {
        Flash::CallInt(ui, LobbyTarget, "setOk_slot", slot);
        Flash::CallBool(ui, LobbyTarget, "setOk", ready);
    }
}
