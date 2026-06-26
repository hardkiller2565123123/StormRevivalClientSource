============================================================
VISUAL STUDIO ORGANIZATION
============================================================

- How to keep folders, filters, projects, and source files aligned so Visual Studio builds what developers think it
  builds.

Code map
- Solution explorer, .vcxproj files, .vcxproj.filters, source folders, project settings.

============================================================
Why It Matters
============================================================

- A .cpp on disk does not compile unless the project includes it.
- Missing implementation files create unresolved externals.
- Duplicate folders make people edit the wrong copy.
- Filters can hide organization problems.
- Platform settings change pointer and library behavior.
- Character set settings change Windows API variants.
- Output paths decide which DLL the game actually loads.
- Documentation belongs in a predictable folder.

============================================================
Organization Rules
============================================================

- One active source copy.
- Add every new .cpp to the intended project.
- Add headers to filters when useful.
- Keep steam_api and steam_api64 separate.
- Keep x86 and x64 outputs separate.
- Keep framework projects game-specific.
- Keep docs outside runtime source.
- Keep generated caches away from source.

============================================================
Review Checklist
============================================================

- Open solution and verify all projects load.
- Check filters for misplaced files.
- Check every new implementation file is included.
- Check include directories.
- Check linker libraries.
- Check character set.
- Check platform target.
- Check output path.
- Check deployed DLL.
- Check git status for untracked docs.

============================================================
Practical Example
============================================================

- A good practical test for VISUAL STUDIO ORGANIZATION starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Organization Lab
============================================================

- Add a new .cpp to disk.
- Add it to the correct .vcxproj.
- Add its header to filters if useful.
- Build the project that should own it.
- Confirm no duplicate active copy exists.
- Confirm output path.
- Deploy the rebuilt DLL.
- Check git status for new docs and source files.

============================================================
Organization Smells
============================================================

- A source file exists but symbol is unresolved.
- Two folders contain similar files.
- A filter hides where runtime code lives.
- x86 and x64 outputs share a confusing folder.
- steam_api and steam_api64 names are mixed.
- Framework code references another game target casually.
- Documentation lives beside runtime code randomly.
- The game still loads an old DLL after a successful build.

End of manual.
