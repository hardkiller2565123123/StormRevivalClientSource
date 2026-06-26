#pragma once
#include "../Core/SRTypes.h"
namespace StormRevival::OnlineMenu::Research {
struct KnownAddresses {
    static constexpr GameAddress Flash_InvokeArgs = 0x140607BA0;
    static constexpr GameAddress Flash_InvokeNoArgs = 0x140607B5C;
    static constexpr GameAddress Flash_LoadMovie = 0x14060759C;
    static constexpr GameAddress Flash_RegisterCallbacks = 0x1401FD0AC;

    static constexpr GameAddress NetBattleLobby_Initialize = 0x1406734A8;
    static constexpr GameAddress NetBattleLobby_SyncLobbyToFlash = 0x140674688;
    static constexpr GameAddress NetBattleLobby_PopulateLobbySlots = 0x140674E74;
    static constexpr GameAddress NetBattleLobby_SetUser = 0x140675494;
    static constexpr GameAddress NetBattleLobby_SetWave = 0x14067518C;
    static constexpr GameAddress NetBattleLobby_SetVoice = 0x14067501C;
    static constexpr GameAddress NetBattleLobby_SetFriend = 0x140674CD4;
    static constexpr GameAddress NetBattleLobby_SetHostNo = 0x140673D98;
    static constexpr GameAddress NetBattleLobby_SetWinStreak = 0x140673D18;
    static constexpr GameAddress NetBattleLobby_SetNum = 0x1406749F4;
    static constexpr GameAddress NetBattleLobby_SetReadyState = 0x140674B20;
    static constexpr GameAddress NetBattleLobby_ClearReady = 0x140673BB0;

    static constexpr GameAddress Session_IsIdle = 0x140AE7A40;
    static constexpr GameAddress Session_IsEstablished = 0x140AE7AA0;
    static constexpr GameAddress Session_BeginLeave = 0x140AE8160;
    static constexpr GameAddress Session_BeginJoin = 0x140AE7EC0;
    static constexpr GameAddress Session_DestroyCallbacks = 0x140AE8250;
    static constexpr GameAddress Session_GetCurrentRoom = 0x140AE7B00;
    static constexpr GameAddress Session_GetHandle = 0x140AE7B30;
    static constexpr GameAddress Session_IsHost = 0x140AE7B90;
    static constexpr GameAddress Session_GetRoomData = 0x140AE7AD0;
    static constexpr GameAddress Session_GetLobbyType = 0x140AE7A10;

    static constexpr GameAddress Match_BuildBattlePlayerList = 0x1405B76BC;
    static constexpr GameAddress Match_BuildReadyMask = 0x1405B44F0;
    static constexpr GameAddress Match_DetermineLocalSlot = 0x1405B4420;
    static constexpr GameAddress Match_LobbyUpdate = 0x1405B776C;
    static constexpr GameAddress Match_StartBattle = 0x1405C3B30;

    static constexpr GameAddress Net_RegisterPlayerInfo = 0x1406B1524;
    static constexpr GameAddress Net_RebuildPlayerIdList = 0x1406B163C;
    static constexpr GameAddress Net_RebuildPlayerMetadataList = 0x1406B17A4;
    static constexpr GameAddress Net_SetActiveSession = 0x1406B2E84;
    static constexpr GameAddress Net_LocalSteamId = 0x1406B4D44;
    static constexpr GameAddress Net_BuildLocalPlayerInfo = 0x1406B4224;
    static constexpr GameAddress Net_SendPlayerMetadata = 0x1406B5260;

    static constexpr GameAddress Storage_WriteFile = 0x140AE43C0;
    static constexpr GameAddress Storage_ReadFile = 0x140AE4460;
    static constexpr GameAddress Ranking_ReadMyRanking = 0x1405C572C;
    static constexpr GameAddress Ranking_ReadRankingTop = 0x1405C5B0C;
    static constexpr GameAddress Stats_UploadCharacterUsage = 0x140565488;
};
}
