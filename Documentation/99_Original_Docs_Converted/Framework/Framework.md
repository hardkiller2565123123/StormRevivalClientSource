============================================================
FRAMEWORK
============================================================

- The framework overview. It explains the in-game overlay layer, manager ownership, feature registry, and why every
  game has its own framework DLL.

Code map
- NS1FrameWork, NS2FrameWork, NS3FrameWork, NS3FBFrameWork, NS4FrameWork, NSCFrameWork, NSRFrameWork, overlay hooks,
  managers.

============================================================
Job Of The Framework
============================================================

- Draw the in-game overlay.
- Handle overlay input safely.
- Expose feature registry state.
- Connect UI controls to managers.
- Show diagnostics that users can screenshot.
- Keep game-specific hooks inside game-specific projects.
- Avoid claiming success when managers lack evidence.
- Give non-programmers a way to understand the runtime.

============================================================
How We Built The Pattern
============================================================

- Let the proxy start first.
- Load the framework after early process state exists.
- Install render and input hooks carefully.
- Register manager states with the feature registry.
- Draw tabs for client, LAN, API, assets, mods, patches, and target-specific tools.
- Route controls through managers instead of global writes.
- Log user actions and manager responses.
- Keep dangerous patches guarded by state.

============================================================
Porting Method
============================================================

- Start with an overlay that opens and closes.
- Add one diagnostic line.
- Add feature registry rows.
- Wire one manager.
- Add one saved setting.
- Add one safe action.
- Test title screen, menus, battle, pause, and shutdown.
- Only then add advanced tabs.

============================================================
Practical Example
============================================================

- A good practical test for FRAMEWORK starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Framework Lab
============================================================

- Prove the framework loaded after the proxy.
- Open and close the overlay without stealing menu input.
- Draw one diagnostic line.
- Add a feature registry table with static rows.
- Wire one manager to update one row.
- Add one read-only diagnostics page.
- Add one saved setting through a manager.
- Test title screen, battle, pause, and shutdown.

============================================================
Framework Examples
============================================================

- A render hook can be active while a feature manager is still NeedsPatch.
- An overlay control can save config without applying runtime behavior until restart.
- A framework can show Steam proxy state without owning the proxy implementation.
- A manager failure should show as state text, not crash the overlay.
- A tab should exist because users need control or evidence, not because it looks cool.
- Input capture should release cleanly when the overlay closes.
- The framework should never invent success states.
- Each game framework earns its own hook proof.

End of manual.
