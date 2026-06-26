============================================================
MOD FOLDER AND CPK ROUTING
============================================================

- How mod folders, manifests, redirect maps, and CPK-style routing should work without destroying original installs.

Code map
- Mods directory, manifest reader, redirect map, CPK lookup hook, asset diagnostics.

============================================================
Folder Rules
============================================================

- Mods live in a controlled revived folder.
- Each mod has its own folder.
- A manifest should name mod, author, target game, IDs, and required files.
- Folder names can be readable while IDs stay explicit.
- Incomplete folders are skipped with reasons.
- Disabled mods remain visible as disabled.
- Load order is deterministic.
- Conflicts report both mods.
- Generated cache files stay separate.
- Example layouts belong in release docs.

============================================================
Routing Rules
============================================================

- Redirect lookups instead of overwriting base archives.
- Map original expected path to replacement path.
- Validate replacement before mapping.
- Prefer explicit paths over broad wildcards.
- Log active redirects in verbose mode.
- Fallback to original when safe.
- Keep project-specific paths separated.
- Expose redirect count in diagnostics.
- Clear old redirects before cache rebuild.
- Never require permanent base CPK replacement for normal mod loading.

============================================================
Examples
============================================================

- Stage replacement maps original stage file to mod file.
- Character icon replacement maps UI texture lookup.
- Lua script patch maps known script name.
- DLC-style package maps several files under one ownership record.
- Conflict logs which mod won.
- Disabled replacement leaves redirect map.
- Missing replacement logs file path.
- Support report includes active redirect count.

============================================================
Practical Example
============================================================

- A good practical test for MOD FOLDER AND CPK ROUTING starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Routing Lab
============================================================

- Scan controlled mod folder.
- Read manifest.
- Validate replacement files.
- Build explicit original-to-replacement map.
- Detect conflicts.
- Apply deterministic load order.
- Log active redirect count.
- Clear redirects when mods reload.

============================================================
Routing Examples
============================================================

- Stage replacement maps one expected stage file to one mod file.
- Icon replacement maps one UI texture path.
- Lua replacement maps one known script path.
- DLC-style package maps several files under one ownership record.
- Conflict logs winner and loser.
- Disabled mod removes redirects.
- Missing file falls back when safe.
- Base archives remain untouched.

End of manual.
