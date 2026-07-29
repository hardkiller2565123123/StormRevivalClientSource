# BGM / Menu Song Research Notes

Status: clean decompile target. No destructive patching added yet.

## Confirmed functions

| IDA name | Suggested name | What it does |
|---|---|---|
| `sub_1400C6F50` | `ccSceneBgmSelect::ctor/init` | Scene object setup for BGM select. |
| `sub_1400C6C60` | `ccSceneBgmSelect::LoadFlash` | Loads `data/ui/flash/FLASH_PLAT/freebtl_song_select/freebtl_song_select.swf`. |
| `sub_1400C6C80` | `ccSceneBgmSelect::CreateUi` | Allocates/initializes the BGM select UI object. |
| `sub_1400FEC60` | `ccUiFlashBgmSelect::ctor` | Initializes the BGM select UI wrapper. |
| `sub_1401001A0` | `ccUiFlashBgmSelect::SetInfoListAndStart` | Builds song rows, sends `SetInfoList`, then calls `StartList`. |
| `sub_1400FF590` | `ccUiFlashBgmSelect::OpenLoadDefaultConfirm` | Opens the load-default confirmation. |
| `sub_1400FF660` | `ccUiFlashBgmSelect::OpenMessageDialog` | Opens a message dialog. |
| `sub_1400FFFD0` | `ccUiFlashBgmSelect::SetEnableInput` | Calls Scaleform `SetEnableInput`. |
| `sub_1400B09E0` | `GetAnimeSongBgmList` | Returns manager/list pointer at `a1 + 0x48`. |
| `sub_1400B0C20` | `RemapSongSlotToBgmId` | Uses table at `manager + 0x10` to map visible slot -> internal BGM id. |
| `sub_1400B0CA0` | `IsBgmUnlocked` | Checks unlock bitfield at `manager + 0x0C`. |

## Safe first runtime patch idea

Hook `sub_1400B0CA0` and return true to unlock every menu song:

```cpp
_BOOL8 __fastcall hkIsBgmUnlocked(__int64 manager, char songId)
{
    return true;
}
```

This should unlock all songs without editing game assets.

## Actual music replacement path

The real replacement target should be the parameter/audio mapping, not the UI.

Search/decompile next:

- `ccAnimeSongBgmParamManager.cpp`
- `data/duel/animeSongBgmParam.xfbin`
- `animeSongBgmParam`
- `dword_14223AF90`
- `unk_14223AF88`
- xrefs from `sub_1401001A0`

Likely goal: map `Song ID -> cue/bank/file/loop info`.
