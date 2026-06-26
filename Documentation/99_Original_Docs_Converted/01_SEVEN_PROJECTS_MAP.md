============================================================
SEVEN PROJECTS MAP
============================================================

- A target-by-target explanation of the seven revived games and why shared architecture does not mean shared offsets.

Code map
- Solution projects NS1, NS2, NS3, NS3FB, NS4, NSC, NSR plus steam_api and steam_api64 proxy projects.

============================================================
Target Records
============================================================

- NarutoStorm1Revived: AppID 495140, steam_api64, NS1FrameWork, x64.
- NarutoStorm2RevivedPrivate: AppID 543870, steam_api64, NS2FrameWork, x64.
- NarutoStorm3Revived: AppID 234670, steam_api, NS3FrameWork, Win32.
- NarutoStorm3FullBurstRevived: AppID 234670, steam_api64, NS3FBFrameWork, x64.
- NarutoStorm4Revived: AppID 349040, steam_api64, NS4FrameWork, x64.
- NarutoStormConnectionsRevived: AppID 1020790, steam_api64, NSCFrameWork, x64.
- NarutoStormRevolationRevived: AppID 272510, steam_api, NSRFrameWork, Win32.

============================================================
What Can Be Shared
============================================================

- The boot concept: proxy first, framework second, managers third.
- The feature registry state model.
- The callback queue idea.
- The diagnostics report idea.
- The public support workflow.
- The mod folder discipline.
- The safe patching philosophy.
- The habit of proving one small behavior before scaling.

============================================================
What Must Stay Per Game
============================================================

- Raw memory addresses.
- Pattern signatures.
- Hook lengths.
- Render hook timing.
- Input handling edge cases.
- Character-select table layout.
- Stage and scene table layout.
- Executable version gates.
- Win32 versus x64 calling convention assumptions.
- Proxy file name and deployment path.

============================================================
Practical Example
============================================================

- A good practical test for SEVEN PROJECTS MAP starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Porting Lab
============================================================

- Choose one feature and write down which project currently proves it.
- Write down the target game, AppID, proxy name, framework name, and platform before touching code.
- Check whether the feature uses Steam interfaces, memory patches, render hooks, or asset IDs.
- Port shared manager structure before raw addresses.
- Add target-specific version detection before enabling patches.
- Run diagnostics in the target game before claiming support.
- Document what transferred cleanly and what needed target-specific work.
- Leave the old target proof intact when adding new target proof.

============================================================
Project-Specific Risk
============================================================

- Win32 targets can fail from pointer-size mistakes that x64 targets never show.
- x64 targets can hide assumptions that break the older steam_api project.
- Storm 4 being the most advanced target does not make it the universal source of truth.
- Connections can require newer table logic even when naming looks familiar.
- Full Burst and Storm 3 share family identity but not all runtime details.
- AppID mistakes can poison ownership and networking diagnostics.
- Framework name mistakes can load the wrong UI layer.
- Release notes must say which target gained support.

End of manual.
