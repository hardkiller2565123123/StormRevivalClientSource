============================================================
HOOKING AND MEMORY PATCHES
============================================================

- The safe patching manual: how hooks should be planned, logged, applied, and refused when evidence is missing.

Code map
- HookFunctions, pattern scanner, moduleBase, patch managers, trampoline helpers, game-version checks.

============================================================
Hook Philosophy
============================================================

- Hooks change running code.
- A wrong hook can crash immediately.
- A public hook must know why it exists.
- A public hook must know which version it supports.
- A public hook must log before writing.
- A hook helper should perform mechanics, not feature policy.
- A manager should decide whether a feature may patch.
- Refusing to patch is a valid safe result.

============================================================
Patch Checklist
============================================================

- Detect executable version.
- Find module base and length.
- Scan or validate address.
- Verify original bytes.
- Choose patch length.
- Prepare trampoline if needed.
- Change memory protection only around the write.
- Write bytes.
- Flush instruction cache if required.
- Log result and update feature state.

============================================================
Lessons From Fixes
============================================================

- Files on disk are not enough; projects must include them.
- Unicode setting can select W APIs when code passes char strings.
- Decompiled goto flow can skip local initialization.
- Illegal qualified declarations need normal C++ cleanup.
- String literals should be const.
- Shared globals need one definition.
- System functions need correct import libraries.
- Infrastructure fixes make hook work possible.

============================================================
Practical Example
============================================================

- A good practical test for HOOKING AND MEMORY PATCHES starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Hook Lab
============================================================

- Find module base and length.
- Detect game version.
- Find or validate target address.
- Read original bytes.
- Compare expected bytes.
- Prepare patch or trampoline.
- Write under controlled memory protection.
- Log old bytes, new behavior, and result.

============================================================
Hook Failure Signs
============================================================

- Crash at startup can mean patch ran too early.
- Crash when opening menu can mean UI table patch hit wrong version.
- No effect can mean signature found a nearby but wrong instruction.
- Only one game version failing can mean version gate too broad.
- Random later crash can mean trampoline length was wrong.
- Feature row stuck Ready can mean patch apply path never ran.
- Feature row Active without log is suspicious.
- A hook with no disable story is not release-quality.

End of manual.
