============================================================
EXPORT TABLE AND DLL LOADING
============================================================

- How the original game finds the proxy DLL and why exported names must exist before any higher-level code matters.

Code map
- DLL exports, import table, steam_api or steam_api64 deployment path, dumpbin export checks, Windows loader
  behavior.

============================================================
Loader Sequence
============================================================

- The executable imports a Steam API DLL by name.
- Windows resolves that DLL before the game reaches menus.
- If the DLL name is wrong, none of the project code runs.
- If an export is missing, the loader can fail before logging exists.
- The 32-bit games need steam_api.
- The x64 games need steam_api64.
- Deployment must place the right DLL where the game loader searches.
- Export-table checks are a first sanity test after build.

============================================================
Developer Method
============================================================

- List imported names from the game executable when uncertain.
- List exported names from the rebuilt proxy.
- Compare both lists before debugging runtime logic.
- Confirm architecture matches: Win32 DLL for Win32 game, x64 DLL for x64 game.
- Confirm the deployed DLL timestamp changed after rebuild.
- Add a startup log as the first runtime proof.
- Keep proxy exports stable when refactoring internal classes.
- Document new exports if they are added.

============================================================
Failure Signs
============================================================

- Game refuses to start before log creation.
- Windows reports missing procedure entry point.
- A rebuilt source fix has no effect because the old DLL is still deployed.
- The game loads the real Steam DLL instead of the revived proxy.
- A Win32 game rejects an x64 proxy.
- An x64 game never calls the steam_api project.
- Export names are decorated when they should be C-style.
- Support reports lack startup log lines.

End of manual.
