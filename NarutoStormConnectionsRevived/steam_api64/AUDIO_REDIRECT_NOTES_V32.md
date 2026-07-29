# V32 Audio Redirect

Goal: replace menu/title music with an external MP3 without editing CRI Atom ACB/AWB assets.

## Files added

- `AudioCueRedirector.h/.cpp`
- `CustomAudioPlayer.h/.cpp`
- `NarutoStormConnectionsRevived/audio_redirect.ini`
- `NarutoStormConnectionsRevived/Audio/PUT_TITLE_MP3_HERE.txt`

## MP3 names searched

The module checks these paths in order:

1. `NarutoStormConnectionsRevived/Audio/title.mp3`
2. `NarutoStormConnectionsRevived/Audio/tittle.mp3`
3. `NarutoStormConnectionsRevived/title.mp3`
4. `NarutoStormConnectionsRevived/tittle.mp3`
5. `NarutoStormConnectionsRevived/Audio Title.mp3`
6. `Audio/title.mp3`
7. `Audio/tittle.mp3`

## Hook

IDA target:

- `sub_1412CB040`
- RVA: `0x12CB040`
- Name: `CriAtomManager::PlayCue`

The hook logs every cue as:

`[AUDIO-CUE] cueId=... slot=... mode=... bank=...`

Default config auto-captures the first `mode=0 slot=0` cue and replaces it with the MP3.
After a good test, set `TitleCueId=<captured id>` in `audio_redirect.ini`.

## Notes

This does not make CRI Atom decode MP3. It blocks the selected CRI cue and plays the MP3 through WinMM/MCI.
This is intentionally isolated from popup/F2/online code.
