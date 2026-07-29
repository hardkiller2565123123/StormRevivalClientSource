# Runtime UI Feature Notes

This branch adds a runtime-facing UI/debug layer for the Naruto Storm Connections Revival DLL.

## Popup system

The popup system uses the real NSC dialog path:

- `sub_140763340` - dialog ctor
- `sub_140763B50` - dialog create/load
- `sub_140764220` - `SetMessageText`
- `sub_140764040` - `OpenWindow`
- `sub_140764370` - `SetVisible`
- `sub_14071F110` - generic no-arg Scaleform call, used for `CloseWindow`

Supported runtime features:

- Timed welcome popup
- Custom popup from ImGui
- Live countdown text
- Optional click/key close
- Fade color wrapper
- Forced replacement of stale popup state
- Multiple popups per run

## Runtime player icon controls

The new `RuntimeUiOptions` module can suppress direct Scaleform icon calls:

- `SetLeaderIcon`
- `SetSupport1Icon`
- `SetSupport2Icon`

This is exposed in ImGui under `Debug > Character Select`.

## Character select findings

Important pipeline:

```text
gTeamPresetDatabase / unk_142221B40
    -> 448-byte team presets
    -> 20-byte preset member entries
    -> FindCharacterById / sub_140857560
    -> gCharacterCostumeDatabase / unk_142224550
    -> ResolveCostumeIndex / ResolveColorIndex
    -> 112-byte runtime member data
    -> gBattleRuntimeTeamCache / qword_14218F7C0
    -> CutInMng
    -> Scaleform SetCharacter / SetLeaderIcon / support icon calls
```

Useful direct Flash methods found:

- `SetCharacter`
- `setMenuKeyHelp`
- `SetLeaderIcon`
- `SetSupport1Icon`
- `SetSupport2Icon`

## Classic UI direction

The current code does not replace the SWF yet. It adds the runtime hooks, logging, docs, and toggles needed to safely move toward:

- Classic Storm 1/2/3 select screen themes
- Old portrait/icon packs
- Animated custom popups
- Hide/show player icon experiments
- Preset/team dumping and editing
- Runtime icon and character select logging
