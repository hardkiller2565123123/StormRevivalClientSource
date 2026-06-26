============================================================
STEAM API PROXY
============================================================

- The manual for the fake Steam API DLL boundary that lets the game start, receive stable answers, and run
  offline-friendly systems.

Code map
- steam_api or steam_api64 project, exported SteamAPI functions, interface factory, callback pump, local AppID and
  ownership state.

============================================================
Job Of The Proxy
============================================================

- Export the functions the original executable imports.
- Initialize logs before other systems can fail silently.
- Return stable Steam-like interface objects.
- Hold AppID and local identity state.
- Answer ownership, DLC, persona, lobby, stats, and storage calls locally.
- Pump callbacks through SteamAPI_RunCallbacks.
- Load or enable framework startup after early state is ready.
- Stay safe even if the framework never loads.

============================================================
How We Did It
============================================================

- Started from the load boundary the game already trusts.
- Kept the proxy name matched to platform: steam_api for Win32 and steam_api64 for x64.
- Added missing project files when unresolved externals proved code existed but was not linked.
- Fixed narrow-string Windows calls by using A variants where the code already used char data.
- Linked the system libraries required by timer and module helpers.
- Restored global module state so scanners and managers used one base address.
- Logged unknown interface requests so missing Steam coverage becomes visible.
- Separated compatibility behavior from game-specific framework behavior.

============================================================
Replication Recipe
============================================================

- Build a DLL with the imported export names.
- Make SteamAPI_Init create stable singleton interface objects.
- Make SteamAPI_RunCallbacks dispatch queued events.
- Make the interface factory log every requested version string.
- Implement only the interfaces the game asks for first.
- Return safe local values instead of nulls that make menus hang.
- Expose AppID, callback count, and interface count in diagnostics.
- Only then add richer subsystems like lobbies, DLC, and storage.

============================================================
Practical Example
============================================================

- A good practical test for STEAM API PROXY starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Proxy Proof Lab
============================================================

- Delete all assumptions and start by confirming the game actually loaded the proxy DLL.
- Check export presence before debugging C++ logic.
- Log SteamAPI_Init and SteamAPI_RunCallbacks first.
- Log AppID and project identity during initialization.
- Log every interface request while entering major menus.
- Return stable persona and ownership values before testing lobbies.
- Verify callback pump activity before blaming matchmaking.
- Confirm the deployed DLL path matches the DLL you rebuilt.

============================================================
Implementation Example
============================================================

- A minimal proxy can boot with SteamAPI_Init, SteamAPI_Shutdown, SteamAPI_RunCallbacks, SteamUser, SteamFriends,
  SteamApps, and SteamUtils.
- The next layer adds matchmaking and callbacks because network menus wait for asynchronous answers.
- The next layer adds local DLC and storage because menus ask ownership and file questions.
- The final public layer exposes diagnostics so support can inspect what the proxy answered.
- Every missing interface string should become a to-do line.
- Every fake response should be deterministic.
- Every unsupported backend operation should fail safely.
- Every subsystem should leave a breadcrumb in the log.

End of manual.
