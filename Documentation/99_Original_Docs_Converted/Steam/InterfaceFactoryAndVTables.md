============================================================
INTERFACE FACTORY AND VTABLES
============================================================

- A deep dive into Steam interface versioning and why returning the wrong object shape can crash even when everything
  compiles.

Code map
- SteamInternal_CreateInterface, Steam client interface routing, ISteamUser, ISteamUtils, ISteamApps,
  ISteamMatchmaking wrappers.

============================================================
VTable Reality
============================================================

- The game calls method slots through interface pointers.
- The friendly C++ method name is gone at runtime.
- A shorter vtable than the requested Steamworks version can jump into invalid memory.
- An older interface can be unsafe even if the first few methods match.
- A crash inside the proxy soon after interface creation often means vtable mismatch.
- Exact version strings are evidence, not decoration.
- The interface factory is one of the highest-risk compatibility points.
- A missing interface should become a log entry and implementation task.

============================================================
Factory Rules
============================================================

- Log every requested interface string.
- Prefer exact version implementations.
- Only alias versions when the method layout is proven compatible.
- Keep interface singleton lifetime stable because the game may cache pointers.
- Do not return stack objects.
- Do not return a placeholder with missing methods for a version the game calls deeply.
- Route subsystems by interface family so diagnostics can report what was requested.
- Keep Win32 and x64 builds separate when object layout matters.

============================================================
Example Failure Analysis
============================================================

- If the game launches then crashes opening online menus, inspect matchmaking interface version.
- If the game crashes while reading persona, inspect friends or user interface version.
- If a dump points near a vtable call target, compare requested version to returned object.
- If an interface request logs unknown and the menu later hangs, implement that version path.
- If adding a method changes class layout, recheck every alias.
- If the game asks for newer utils, do not blindly return older utils.
- If a method writes output buffers, verify size and null termination.
- If support logs show repeated factory failures, prioritize the interface factory before feature code.

============================================================
Practical Example
============================================================

- A good practical test for INTERFACE FACTORY AND VTABLES starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
VTable Proof Lab
============================================================

- Capture every requested interface version string.
- Compare requested version with returned wrapper class.
- Check method order before aliasing nearby versions.
- Open menus that call the subsystem instead of trusting launch success.
- Use dumps or crash addresses to detect bad call targets.
- Log unknown versions once per session in normal mode and fully in verbose mode.
- Prefer explicit unsupported logs over unsafe fake objects.
- Add tests around buffer-writing methods because they expose layout mistakes fast.

============================================================
Crash Clues
============================================================

- Crash after interface creation can be a wrong vtable.
- Crash only in online menu can be matchmaking interface shape.
- Crash only in profile menu can be friends or user interface shape.
- Crash after utility call can be utils version mismatch.
- Crash after adding one method can mean aliases now point to changed layout.
- Null interface can hang where the game expected fallback data.
- Stack-created interface pointers can crash later.
- Wrong calling convention can look like random memory corruption.

End of manual.
