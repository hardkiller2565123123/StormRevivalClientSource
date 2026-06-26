TITLE MUSIC OVERRIDE
Project: NarutoStorm4Revived
Status: runtime MP3 playback is wired; exact title-scene audio hook is still an IDA target pass.

Purpose
-------
The title music override gives public builds a simple audio drop folder:

    NarutoStorm4Revived\Audio\Title.mp3

When steam_api64 loads, the runtime creates NarutoStorm4Revived\Audio and
NarutoStorm4Revived\Config if they do not already exist. It then reads:

    NarutoStorm4Revived\Config\Audio.ini

The current config shape is:

    [TitleMusic]
    Enabled=1
    File=Title.mp3
    Volume=80

Enabled controls whether the override attempts playback. File can be a file
name relative to NarutoStorm4Revived\Audio or an absolute path. Volume is
clamped from 0 to 100 and passed to the Windows media layer as 0 to 1000.

Implementation Notes
--------------------
The first implementation lives in steam_api64\AudioPlayer.cpp under the
TitleMusicOverride namespace. The original AudioPlayer class was unfinished:
it created XAudio2 objects but did not keep them alive, did not load a file,
and did not return a success HRESULT. That made it unsafe to build on.

The replacement uses the Windows MCI API through mciSendStringA. That path is
intentionally boring: Windows already knows how to decode common MP3 files,
so the project can support a public "drop Title.mp3 here" workflow before we
finish the deeper CRI/ADX2 research.

Runtime Flow
------------
1. dllmain.cpp calls TitleMusicOverride::Init after Steam local storage/stat
   systems are initialized.
2. Init resolves the game folder from GetModuleFileNameA(nullptr).
3. Init creates NarutoStorm4Revived\Audio and NarutoStorm4Revived\Config.
4. Init reads Audio.ini.
5. Init resolves Title.mp3.
6. If the file exists, it opens it with:

       open "<path>" type mpegvideo alias ns4revived_title_music

7. It applies volume with:

       setaudio ns4revived_title_music volume to <0-1000>

8. It starts playback with:

       play ns4revived_title_music repeat

9. dllmain.cpp calls TitleMusicOverride::Shutdown during process detach, which
   stops and closes the MCI alias.

Current Limitation
------------------
This is a real runtime feature, but it is not yet a perfect game-native title
scene replacement. It starts when the proxy DLL initializes. The next IDA pass
needs to bind this system to the actual title scene or title BGM call so the
custom track starts/stops only when the title screen is active and can mute or
bypass the original BGM cleanly.

IDA Targets To Continue
-----------------------
Useful strings already found in the executable:

    ccSceneTitle.cpp
    ccUiFlashTitle.cpp
    RequestLoadTitle
    RequestTitleIn
    RequestTitleOut
    LoadTitle
    PlayMusic
    StopMusic
    ccSound.cpp
    ccLoadSound
    ccStartSound
    bgm.acb
    bgm.awb
    data/rpg/param/PLAT/musicParam.bin.xfbin

The best next target is not the BGM table alone. The BGM table helps with
adding songs, but title-screen replacement needs the scene flow around
ccSceneTitle and the sound start/stop functions. Once IDA bridge access is
stable, inspect xrefs to ccSceneTitle.cpp and PlayMusic/StopMusic first.

Reproducing The Method
----------------------
To reproduce the current approach for another Storm game:

1. Add a runtime audio folder under that game's Revived folder.
2. Add a small config file with Enabled/File/Volume.
3. Resolve the game folder from the loaded EXE, not from the current working
   directory. Steam and launchers can change the working directory.
4. Use a fixed MCI alias per process so restart/shutdown can close the same
   handle every time.
5. Log missing files as warnings, not errors. A public build should still
   launch when the user has not installed a custom track.
6. Add the exact game-native scene hook only after IDA confirms the target
   function and version gates are stable.

Why MP3 First
-------------
Naruto Storm 4 uses CRI/ADX2 assets such as ACB/AWB/ADX. Full native audio
replacement will eventually need either an archive override for the correct
internal sound asset or a hook around the game's sound manager. MP3 support is
a practical first public feature because users can test it without rebuilding
CRI banks.
