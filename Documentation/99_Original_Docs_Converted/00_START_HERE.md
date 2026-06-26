============================================================
START HERE
============================================================

- The entry manual for the rebuilt documentation library. It tells readers how to navigate the project without
  needing the original chat history.

Code map
- Documentation folder, solution explorer, runtime logs, API tab screenshots, and game-specific project folders.

============================================================
What This Library Is
============================================================

- A public manual set written as .h comment files so Visual Studio shows them cleanly.
- A replacement for the older repeated documentation dump. These files are now topic-owned instead of template-owned.
- A teaching system for players, modders, contributors, and maintainers.
- A map from runtime behavior to source ownership.
- A way to preserve the knowledge needed to keep the revived projects alive.
- A reminder that source, project files, deployed DLLs, logs, and docs all need to agree.
- A place to record methods, not just final results.
- A safe place to say what is not finished yet.

============================================================
Reading Path
============================================================

- Read this file first.
- Read Seven Projects Map before porting features.
- Read Steam API Proxy when the game fails before the overlay appears.
- Read Network when lobby search, LAN discovery, or callbacks are involved.
- Read Framework when the API tab, overlay, or feature registry is involved.
- Read Hooks before touching memory patches.
- Read Slots before changing character, stage, scene, or costume counts.
- Read Assets before adding mod files.
- Read Build when Visual Studio errors appear.
- Read Diagnostics before guessing at crashes.

============================================================
Rules For Every Future Update
============================================================

- Every risky feature starts with diagnostics.
- Every runtime feature gets a log line.
- Every public control maps to a manager.
- Every manager reports a state.
- Every patch checks version or signature.
- Every port proves itself on its target game.
- Every source file that should build is added to the project.
- Every release tells the truth about unfinished work.

============================================================
Practical Example
============================================================

- A good practical test for START HERE starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Reader Lab
============================================================

- Open the solution first and identify which game project you are looking at before reading any system manual.
- Open the Documentation folder in Visual Studio and confirm every topic is split by ownership instead of age.
- Pick one runtime symptom and trace it to the correct manual: boot, network, overlay, hook, slot, asset, build, or
  crash.
- Use the code map line in each file as the first search query in the source tree.
- When a manual says a feature is guarded, treat that as a safety decision rather than unfinished wording.
- When a manual says proof, look for a log line, overlay state, or visible in-game behavior.
- Use this start file as the index when onboarding new contributors.
- Update this start file only when the structure of the documentation library changes.

============================================================
What Not To Do
============================================================

- Do not paste one huge repeated block into every manual.
- Do not mix user instructions, reverse-engineering notes, and release claims in one file.
- Do not advertise a feature just because a config value exists.
- Do not let the docs drift away from the source tree.
- Do not hide dangerous patch requirements behind friendly wording.
- Do not assume another Storm game shares offsets.
- Do not leave knowledge trapped in private chat history.
- Do not remove a limitation from docs until runtime proof replaces it.

End of manual.
