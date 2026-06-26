#pragma once
namespace StormRevival::OnlineMenu::Research {
struct FunctionMapItem { const char* Address; const char* Name; const char* Meaning; };
inline constexpr FunctionMapItem DecompiledFunctionMap[] = {
{"sub_140607BA0","Flash_InvokeArgs","Generic Scaleform/ActionScript call with args"},
{"sub_140607B5C","Flash_InvokeNoArgs","No-arg Scaleform call wrapper"},
{"sub_14060759C","Flash_LoadMovie","Loads/registers Flash movie"},
{"sub_140674688","SyncLobbyToFlash","Main room/player UI renderer"},
{"sub_140674E74","PopulateLobbySlots","Full slot refresh fallback"},
{"sub_140675494","SetUser","Persona/icon/title into lobby row"},
{"sub_14067518C","SetWave","Connection bars"},
{"sub_14067501C","SetVoice","Voice state"},
{"sub_140674CD4","SetFriend","Friend/status icon"},
{"sub_140673D98","SetHostNo","Host slot/crown"},
{"sub_140673D18","SetWinStreak","Win streak UI"},
{"sub_1406749F4","SetNum","Current/max player count"},
{"sub_140674B20","SetReadyState","netbattlelobby.setOk"},
{"sub_140AE7A40","Session_IsIdle","No busy/error state"},
{"sub_140AE7AA0","Session_IsEstablished","Session established flags +1192/+1196"},
{"sub_140AE8160","Session_BeginLeave","Begin leave/close session"},
{"sub_140AE7EC0","Session_BeginJoin","Begin join/session transition"},
{"sub_140AE8250","Session_DestroyCallbacks","Destroy two session callback objects"},
{"sub_140AE7B00","Session_GetCurrentRoom","session + 1144"},
{"sub_140AE7B30","Session_GetHandle","session + 1160"},
{"sub_140AE7B90","Session_IsHost","state==2 and session + 368"},
{"sub_1405B76BC","BuildBattlePlayerList","Copies lobby players into battle start cache"},
{"sub_1405B44F0","BuildReadyMask","Builds 8-slot ready mask and broadcasts"},
{"sub_1405B4420","DetermineLocalPlayerSlot","Compares local slot against current room"},
{"sub_1405B776C","LobbyUpdate","Heartbeat: refresh UI, ready, launch checks"},
{"sub_1405C3B30","StartBattle","Final netBattleStart transition"},
{"sub_140AE43C0","Storage_WriteFile","SteamRemoteStorage FileWrite"},
{"sub_140AE4460","Storage_ReadFile","SteamRemoteStorage FileRead"},
{"sub_1405C572C","ReadMyRanking","Ranking request"},
{"sub_1405C5B0C","ReadRankingTop","Top ranking request"}
};
}
