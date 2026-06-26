============================================================
APPS DLC STATS STORAGE
============================================================

- How local AppID, DLC ownership, stats, achievements, and storage replace enough Steam backend behavior for offline
  play.

Code map
- ISteamApps, ISteamUserStats, remote storage wrappers, local config, ownership table, diagnostics report.

============================================================
App And DLC Identity
============================================================

- Each project has a fixed AppID.
- AppID affects diagnostics, lobby identity, DLC checks, and support reports.
- DLC ownership should be local and explicit.
- The base game should answer owned consistently.
- A mod can use DLC-style ownership only after the API exposes a stable answer.
- Ownership is not the same as asset presence.
- A DLC flag can allow a menu path while the asset loader still needs real files.
- Diagnostics should list AppID and DLC mode.

============================================================
Stats And Achievements
============================================================

- Stats can be no-op but stable until persistence exists.
- Achievements can accept unlock calls without real Steam backend.
- Missing stat keys should return safe defaults.
- Set calls should either persist locally or log unsupported behavior.
- Stats readiness callbacks matter if menus wait for them.
- Do not block on network in offline mode.
- Expose persistence mode in diagnostics.
- Future persistence should plug behind the existing API contract.

============================================================
Remote Storage
============================================================

- Use a controlled local folder for storage-like behavior.
- Keep project storage separated by game or AppID.
- Validate file names to prevent path escape.
- Respect buffer sizes on reads and writes.
- Return safe failure for unsupported cloud sync.
- Keep remote storage separate from mod content folders.
- Log storage paths when verbose diagnostics are enabled.
- Document the storage file format if persistence expands.

============================================================
Practical Example
============================================================

- A good practical test for APPS DLC STATS STORAGE starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Ownership Lab
============================================================

- Print AppID at startup.
- Print base-game ownership answer.
- Print every DLC ID queried in verbose diagnostics.
- Connect DLC ownership to asset visibility only through clear manager logic.
- Return safe defaults for unknown stat keys.
- Test menus that request stats before gameplay.
- Write storage only inside the revived controlled folder.
- Keep per-game storage separated so projects do not overwrite each other.

============================================================
Examples For Modders
============================================================

- A DLC-style mod can ask the API to report ownership before the asset manager exposes content.
- A local achievement unlock can be accepted without contacting Steam.
- A stat write can be logged and ignored until persistence is added.
- A remote storage read can map to a local file in the revived folder.
- A missing cloud operation can return unsupported without crashing.
- A bad path should be rejected before disk access.
- A diagnostics report should make ownership decisions visible.
- A future persistence file should document its format.

End of manual.
