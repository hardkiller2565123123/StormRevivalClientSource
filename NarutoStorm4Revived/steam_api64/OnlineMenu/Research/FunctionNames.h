#pragma once

namespace StormRevival::OnlineMenu::Research
{
    struct NamedFunction
    {
        const char* sub;
        const char* name;
        const char* notes;
    };

    inline constexpr NamedFunction KnownFunctions[] =
    {
        {"sub_140607BA0", "CallFlashFunction", "Generic Scaleform/ActionScript invoke with args."},
        {"sub_140607B5C", "CallFlashFunctionNoArgs", "Wrapper for no-argument Flash calls."},
        {"sub_14060759C", "LoadFlashMovie", "Loads/registers SWF movie by movie name/path."},
        {"sub_1406734A8", "NetBattleLobby_Initialize", "Loads netbattlelobby and registers callbacks."},
        {"sub_140674688", "NetBattleLobby_Refresh", "Master lobby refresh / room population path."},
        {"sub_140674E74", "NetBattleLobby_RefreshAllSlots", "Fallback full player slot refresh."},
        {"sub_140675494", "NetBattleLobby_SetUser", "Flash setUser(slot, personaName, icon/title)."},
        {"sub_14067518C", "NetBattleLobby_SetWave", "Flash setWave(selected, slot, bars)."},
        {"sub_14067501C", "NetBattleLobby_SetVoice", "Flash setVoice(selected, slot, voiceState)."},
        {"sub_140674CD4", "NetBattleLobby_SetFriend", "Flash setFriend(selected, slot, state, flag)."},
        {"sub_140673D98", "NetBattleLobby_SetHostNo", "Flash setHostNo(slot)."},
        {"sub_140673D18", "NetBattleLobby_SetWinStreak", "Flash setWinStreak(value)."},
        {"sub_1406749F4", "NetBattleLobby_SetNum", "Flash setNum(current,max)."},
        {"sub_140674C58", "NetBattleLobby_SetOnUser", "Flash CallsetOnUser(bool)."},
        {"sub_140674200", "NetBattleLobby_SetRoomInfoHostIcon", "Flash CallsetRoomInfoIconHost(bool)."},
        {"sub_140675364", "NetBattleLobby_SetHost", "Flash CallsetHost(bool)."},
        {"sub_140673E48", "NetBattleLobby_SetRoomInfoIcon", "Flash CallsetRoomInfoIcon with 6 args."},
        {"sub_140AE6670", "HasLobbyUsers", "Checks internal vector or SteamNetworking lobby data."},
        {"sub_140AE6720", "GetLobbyUserSteamIdByIndex", "Gets SteamID for lobby user index."},
        {"sub_140AEB5B0", "IsFriend", "SteamFriends relationship == friend."},
        {"sub_140673408", "LobbyTypeToUiMode", "Maps mode 4..8 to UI modes 100/110/120/130/140."}
    };
}
