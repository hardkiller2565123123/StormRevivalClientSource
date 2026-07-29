# Next IDA Targets

## Best next target: BGM/menu song replacement

Pull these first:

1. xrefs to `data/duel/animeSongBgmParam.xfbin`
2. xrefs to `animeSongBgmParam`
3. xrefs to `ccAnimeSongBgmParamManager.cpp`
4. xrefs to `dword_14223AF90`
5. xrefs to `unk_14223AF88`

Then send the decompile of the function that loads or validates `animeSongBgmParam.xfbin`.

## Easy patch target

Pull xrefs/callers of:

```text
sub_1400B0CA0
```

This is the unlock check for BGM songs. Returning true should unlock the full menu-song list.

## Avoid for now

Online menu scene/state machine. The logs show hooks are installed but scene transition still never hits the net menu functions. It is not as clean as BGM yet.
