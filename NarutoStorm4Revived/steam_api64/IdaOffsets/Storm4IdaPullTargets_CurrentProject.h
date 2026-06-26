#pragma once

// STORM 4 CURRENT PROJECT IDA PULL TARGETS
//
// This file is the hand-picked working list from the generated IDA string
// offset dump. The full dump is intentionally huge; this file is the shortlist
// for the current NarutoStorm4Revived work: visible extra character slots,
// visible extra stage slots, unlock checks, and systems our runtime managers
// already touch.
//
// Important IDA note from the current screenshots:
// Many string xrefs land in a .data descriptor table first. That is expected.
// Example from the screenshots:
//
//   .rdata:0000000141185D58 "data/network/event/PLAT/netEventParam.bin.xfbin"
//   .rdata:0000000141185D88 "netEventParam"
//   .data: 00000001416D0008 dq offset aDataNetworkEve
//   .data: 00000001416D0010 dq offset aNeteventparam
//
// That means the string belongs to a game resource descriptor record, usually
// shaped like:
//
//   file path pointer
//   chunk/parameter name pointer
//   flags, alignment, count, or loader metadata
//   next descriptor record
//
// Do not stop at the .data record. The workflow is:
//   1. Jump to the string.
//   2. Press X to find xrefs.
//   3. If the xref is a .data descriptor, jump to that descriptor.
//   4. Press X on the descriptor address or descriptor pointer.
//   5. The useful code is the manager/loader that walks that table.
//   6. Pattern scan the nearby code, not the raw string pointer.

namespace Storm4IdaPullTargets
{
    // ---------------------------------------------------------------------
    // Priority 1: visible extra character slots
    // ---------------------------------------------------------------------
    //
    // These are the first anchors to pull. Current runtime expansion can add
    // backing capacity, but visible boxes need UI scene/control patches too.

    constexpr unsigned long long CcUiCharacterSelect3DModel_Draw_StringVA = 0x141189C70ull;
    constexpr unsigned long long CcUiCharacterSelect3DModel_Draw_RVA      = 0x01189C70ull;
    // Purpose: visible character model/card draw path.
    // IDA action: xref this string, find the Draw function, inspect cell/model
    // count loops and hidden/invalid-cell branches.

    constexpr unsigned long long CcUiCharacterSelect3DModel_Ctrl_StringVA = 0x141189C98ull;
    constexpr unsigned long long CcUiCharacterSelect3DModel_Ctrl_RVA      = 0x01189C98ull;
    // Purpose: cursor movement, focus, and selection control path.
    // IDA action: xref this string, find slot index clamp logic.

    constexpr unsigned long long CharacterSelectParam_Path_StringVA = 0x1412ABC80ull;
    constexpr unsigned long long CharacterSelectParam_Path_RVA      = 0x012ABC80ull;
    // String: data/ui/max/select/PLAT/characterSelectParam.xfbin
    // Purpose: main char-select UI parameter file.
    // IDA action: if xref lands in a .data descriptor table, xref the descriptor
    // record to find the param manager and version/count checks.

    constexpr unsigned long long FreeBattleCharacterSelect_Source_StringVA = 0x1413307A0ull;
    constexpr unsigned long long FreeBattleCharacterSelect_Source_RVA      = 0x013307A0ull;
    // Source: ccSceneFreeBattleCharacterSelect.cpp
    // Purpose: offline Free Battle char-select scene, best first scene target.
    // IDA action: xref source string and nearby assert strings to find Initialize,
    // Ctrl, Draw, Finalize, and grid construction code.

    constexpr unsigned long long SetConvertSelectCharaInfo_StringVA = 0x1412C4228ull;
    constexpr unsigned long long SetConvertSelectCharaInfo_RVA      = 0x012C4228ull;
    // Purpose: selected character/team data conversion.
    // IDA action: xref to find selected character info layout.

    constexpr unsigned long long ConvertSelectCharaInfo_OugiFinish_StringVA = 0x1412C41E0ull;
    constexpr unsigned long long ConvertSelectCharaInfo_OugiFinish_RVA      = 0x012C41E0ull;
    // Purpose: team/ougi finish info and role/index layout.
    // IDA action: trace how selected char id, costume, role, support, and ougi
    // indexes are packed.

    constexpr unsigned long long NetworkCharacterSelectInitialize_StringVA = 0x1412FA9C8ull;
    constexpr unsigned long long NetworkCharacterSelectInitialize_RVA      = 0x012FA9C8ull;
    // Purpose: online char-select state base. Use after offline slots work.
    // IDA action: compare online state counts/clamps against free battle.

    // ---------------------------------------------------------------------
    // Priority 2: visible extra stage slots
    // ---------------------------------------------------------------------

    constexpr unsigned long long StageSelectConfig_Create_StringVA = 0x141300C30ull;
    constexpr unsigned long long StageSelectConfig_Create_RVA      = 0x01300C30ull;
    // String: ccStageSelectConfig::Create():NUCC_XFBIN_DOC_MNG->Search() failed.
    // Purpose: stage select config loader.
    // IDA action: xref to find the loader, chunk count reads, and config table.

    constexpr unsigned long long BattleStageSelect_Source_StringVA = 0x141339240ull;
    constexpr unsigned long long BattleStageSelect_Source_RVA      = 0x01339240ull;
    // Source: ccSceneBattleStageSelect.cpp
    // Purpose: offline stage select scene.
    // IDA action: find stage grid draw/control loops and count clamps.

    constexpr unsigned long long StageSelectChangeParam_StringVA = 0x141339220ull;
    constexpr unsigned long long StageSelectChangeParam_RVA      = 0x01339220ull;
    // Purpose: selected stage transition/change data.
    // IDA action: trace selected stage id from UI cell to battle startup.

    constexpr unsigned long long NetworkStageSelectInitialize_StringVA = 0x1412FE9D0ull;
    constexpr unsigned long long NetworkStageSelectInitialize_RVA      = 0x012FE9D0ull;
    // Purpose: online stage select state base.
    // IDA action: use after offline stage boxes work.

    constexpr unsigned long long StageSelectFlashImagePath_StringVA = 0x141312BE0ull;
    constexpr unsigned long long StageSelectFlashImagePath_RVA      = 0x01312BE0ull;
    // String: _root.all_nut.all_stagesel.all_stage_image
    // Purpose: visible Flash/NUT stage image path.
    // IDA action: xref to find where the Flash stage image list is filled.

    // ---------------------------------------------------------------------
    // Priority 3: unlock and DLC gates that can hide valid slots
    // ---------------------------------------------------------------------

    constexpr unsigned long long UnlockCharacterCheck_StringVA = 0x1412F89D0ull;
    constexpr unsigned long long UnlockCharacterCheck_RVA      = 0x012F89D0ull;
    // Purpose: hidden/locked character filtering.
    // IDA action: xref and identify whether this returns bool or checks a table.

    constexpr unsigned long long IsDlcCharacter_StringVA = 0x14130A150ull;
    constexpr unsigned long long IsDlcCharacter_RVA      = 0x0130A150ull;
    // Purpose: DLC character gate.
    // IDA action: xref and compare with our fake Steam/DLC ownership paths.

    constexpr unsigned long long UnlockCharacterTotalParam_Source_StringVA = 0x14133D760ull;
    constexpr unsigned long long UnlockCharacterTotalParam_Source_RVA      = 0x0133D760ull;
    // Source: ccUnlockCharacterTotalParam.cpp
    // Purpose: total unlock parameter manager.
    // IDA action: find version/count checks for unlockCharaTotal.bin.xfbin.

    // ---------------------------------------------------------------------
    // Priority 4: systems we already have managers for
    // ---------------------------------------------------------------------

    constexpr unsigned long long GetStageBgm_StringVA = 0x14133A07Cull;
    constexpr unsigned long long GetStageBgm_RVA      = 0x0133A07Cull;
    // Use for BGMManager and stage sound expansion.

    constexpr unsigned long long CcAdvPlayStageBgm_StringVA = 0x14137CF60ull;
    constexpr unsigned long long CcAdvPlayStageBgm_RVA      = 0x0137CF60ull;
    // Use for adventure/stage BGM script function lookup.

    constexpr unsigned long long NinjutsuBullet_StringVA = 0x141325160ull;
    constexpr unsigned long long NinjutsuBullet_RVA      = 0x01325160ull;
    // Use for ProjectileManager and bullet/action table work.

    constexpr unsigned long long PlSpSkillIndex1_StringVA = 0x141346250ull;
    constexpr unsigned long long PlSpSkillIndex1_RVA      = 0x01346250ull;
    // Use for TeamUltimateJutsuManager, pair special skill indexes, and ougi
    // table analysis.

    constexpr unsigned long long CcCameraCharacterSelect_StringVA = 0x141376460ull;
    constexpr unsigned long long CcCameraCharacterSelect_RVA      = 0x01376460ull;
    // Use for char-select camera behavior and debug camera hooks.

    constexpr unsigned long long MmInputManager_CreateInstance_StringVA = 0x1415FEEB0ull;
    constexpr unsigned long long MmInputManager_CreateInstance_RVA      = 0x015FEEB0ull;
    // Use for input focus, overlay input, and controller diagnostics.

    constexpr unsigned long long CcSceneManager_Header_StringVA = 0x141188E40ull;
    constexpr unsigned long long CcSceneManager_Header_RVA      = 0x01188E40ull;
    // Use for scene manager function naming and scene transition hooks.

    // ---------------------------------------------------------------------
    // Descriptor-table records observed in screenshots
    // ---------------------------------------------------------------------
    //
    // These are not final code hooks. They are resource table records that must
    // be xrefed again to find loader code.

    constexpr unsigned long long NetEventParam_DescriptorVA = 0x1416D0008ull;
    // record begins with path pointer -> data/network/event/PLAT/netEventParam.bin.xfbin
    // next pointer -> netEventParam

    constexpr unsigned long long NetEventCharaSelectParam_DescriptorVA = 0x1416D02B8ull;
    // record begins with path pointer ->
    // data/network/event/charaSelectParam/PLAT/netEventCharaSelectParam.bin.xfbin
    // next pointer -> netEventCharaSelectParam
}
