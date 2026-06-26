============================================================
DEPLOYMENT AND DLL VERIFICATION
============================================================

- How to prove the game is using the DLL that was just built, not an old binary from another folder.

Code map
- Build output folder, game install folder, proxy DLL timestamp, framework DLL timestamp, logs, export checks.

============================================================
Why Deployment Lies
============================================================

- Visual Studio can build successfully into one folder while the game loads a DLL from another.
- An old deployed DLL can make fixed source look broken.
- A wrong architecture DLL can fail before logs.
- A wrong proxy name can make the game load the original Steam DLL.
- A stale framework DLL can show old overlay behavior.
- Output path drift is common in multi-project solutions.
- Release and Debug outputs can be confused.
- Support should always ask which DLL actually loaded.

============================================================
Verification Steps
============================================================

- Check build output timestamp.
- Check deployed DLL timestamp.
- Check file size changed when expected.
- Check startup log build label if available.
- Check export table for proxy functions.
- Check game folder contains correct proxy name.
- Check framework folder contains matching DLL.
- Delete or rename old test DLLs only when safe and intentional.

============================================================
Public Support Clues
============================================================

- User says fix did nothing after rebuild.
- Log format still looks old.
- API tab lacks a newly added row.
- Crash address belongs to old binary.
- Game folder has duplicate proxy copies.
- Build output folder differs from install folder.
- Release config built but Debug DLL deployed.
- x86 proxy was copied into x64 target or opposite.

End of manual.
