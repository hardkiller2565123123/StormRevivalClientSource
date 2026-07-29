# NS Connections Character Select Reverse Map

This file documents the Free Battle / character select pieces found so far.

## Main Pipeline

```text
gTeamPresetDatabase / unk_142221B40
    -> LoadPreset / SelectPreset
    -> FindCharacterById
    -> gCharacterCostumeDatabase / unk_142224550
    -> ResolveCostumeIndex + ResolveColorIndex
    -> RuntimeMember112 x3
    -> gBattleRuntimeTeamCache / qword_14218F7C0
    -> CutInMng
    -> Flash SetCharacter
    -> Customize packet send
```

## Data Layouts

| Name | Original | RVA | Layout |
|---|---|---:|---|
| gTeamPresetDatabase | unk_142221B40 | 0x2221B40 | 448 bytes per team preset |
| Category stride | n/a | n/a | 3584 bytes = 8 presets * 448 |
| Preset member entry | n/a | n/a | first 3 members appear to use 20 bytes each |
| Runtime member | n/a | n/a | 112 bytes per member |
| gCharacterCostumeDatabase | unk_142224550 | 0x2224550 | 120 * character + 28 * costume |
| gCharacterCustomizeDatabase | unk_1421A0310 | 0x21A0310 | 120 * character + 541248 + 28 * color |
| gCurrentTeamPresetIndex | dword_142224540 | 0x2224540 | current/default preset index |

## High-Value Functions

| New Name | Original | RVA | Notes |
|---|---|---:|---|
| LoadPresetByCategorySlot | sub_1400D5200 | 0x0D5200 | Loads category/slot preset, builds runtime team, updates CutInMng/cache |
| UpdateTeamPreviewPanel | sub_1400D55D0 | 0x0D55D0 | Reads leader/support IDs and updates preview UI |
| SelectPreset | sub_1400ED4C0 | 0x0ED4C0 | Main preset change path |
| ResetCharacterSelect | sub_1400FCFD0 | 0x0FCFD0 | Init/reset path for character select |
| BuildFlashSetCharacter | sub_14017CC00 | 0x17CC00 | Calls Flash SetCharacter with 6 args |
| UpdateSelectPresetList | sub_14017E6F0 | 0x17E6F0 | Refreshes preset/costume list |
| SendCustomizeData | sub_140615A80 | 0x615A80 | Sends one team customize packet |
| SendCustomizeDataCurrent | sub_1406160B0 | 0x6160B0 | Sends current team customize packet |
| SendCustomizeDataList | sub_1406166F0 | 0x6166F0 | Sends up to 8 team presets |
| FindManagerByName | sub_141086E40 | 0x1086E40 | Global manager lookup, e.g. CutInMng |

## Next Reverse Targets

1. `sub_1407D6400`, `sub_1407D6AB0`, `sub_1407D6BF0` — team preview UI setter functions.
2. `sub_14017CC00` callers and argument builders around `SetCharacter`.
3. `sub_14017DA00` — active cursor/preset display.
4. `sub_140857B90`, `sub_1408572C0`, `sub_1408576D0` — character lookup variants.
5. `sub_140528C10`, `sub_140528CE0`, `sub_140527CF0` — costume/color/customize conversion.
6. Xrefs to `dword_142224540` — find exact cursor/preset write points.
7. Xrefs to `SetCharacter`, `UpdateSelectPresetList`, `setMenuKeyHelp` — complete Flash API map.

## 2026-07-06 Runtime UI / Icon Update

New functions mapped from the latest IDA dump:

| Name | RVA | IDA | Meaning |
|---|---:|---|---|
| `SetLeaderIconFlash` | `0x7D6400` | `sub_1407D6400` | Calls Scaleform `SetLeaderIcon(iconPath, iconId)` |
| `SetSupport1IconFlash` | `0x7D6AB0` | `sub_1407D6AB0` | Calls Scaleform `SetSupport1Icon(iconPath, iconId)` |
| `SetSupport2IconFlash` | `0x7D6BF0` | `sub_1407D6BF0` | Calls Scaleform `SetSupport2Icon(iconPath, iconId)` |
| `CopyCharacterInfoById` | `0x857B90` | `sub_140857B90` | Copies 64 bytes of character-info record from `FindCharacterById` |
| `ResolveCharacterIdFromRuntime` | `0x8572C0` | `sub_1408572C0` | Finds character index by runtime character/variant fields |
| `ResolveCharacterVariantInfo` | `0x8576D0` | `sub_1408576D0` | Finds character info by character/variant pair |
| `ResolvePortraitAsset` | `0x175FB0` | `sub_140175FB0` | Returns main/support portrait asset IDs |
| `ResolveCostumeIndex` | `0x528C10` | `sub_140528C10` | Resolves costume table value using data list type 2 |
| `ResolveColorIndex` | `0x528CE0` | `sub_140528CE0` | Resolves color table value using data list type 5 |
| `CurrentTeamCustomizeSender` | `0x6160B0` | `sub_1406160B0` | Builds and sends one current team customize packet |

### New runtime feature added

`RuntimeUiOptions` can now suppress these Flash calls at runtime:

- `SetLeaderIcon`
- `SetSupport1Icon`
- `SetSupport2Icon`

This gives an ImGui option to hide all player/team preview icons without patching game data or save data. It works by intercepting the generic Scaleform dispatcher `sub_14071F390` and returning before the original call for selected methods.

### Popup manager fix

The previous custom popup path could get stuck after one popup because stale state could remain after `CloseWindow`. `PopupManager` now uses a popup request id, force-replaces stale dialogs, resets state after close, and exposes `IsBusy()` plus `ActivePopupId()` for ImGui.

### Practical result

The project can now do runtime popup tests, animated/timed custom popups, leader/support icon hiding, character-select Flash-call logging, and open-source documentation of the character preset pipeline.
