============================================================
OVERLAY API TAB
============================================================

- The API tab manual. It teaches how runtime state becomes visible and controllable without hiding missing patches.

Code map
- DevToolsManager, API tab draw path, runtime controls, diagnostics view, feature registry table.

============================================================
Purpose
============================================================

- Make feature state visible.
- Make missing requirements visible.
- Make runtime settings editable only when a manager owns them.
- Make restart-required behavior clear.
- Make screenshots useful for support.
- Make dangerous features honest instead of flashy.
- Make diagnostics readable inside the game.
- Make public users less dependent on source code.

============================================================
Control Rules
============================================================

- A toggle maps to a manager setting.
- A number control maps to bounded config.
- An apply button calls a manager method.
- A diagnostics button refreshes read-only state.
- A disabled control explains why it is disabled.
- A restart-required control saves config and says restart needed.
- A live control logs before and after.
- A state label comes from the manager, not UI guessing.

============================================================
Examples
============================================================

- Stage expansion can show Active when patching succeeded.
- Character expansion can show Managed when diagnostics exist but select offsets are missing.
- LAN discovery can show Running with discovered count.
- Steam can show AppID and callback count.
- Assets can show loaded and skipped mod counts.
- Hooks can show version detected and signature result.
- Crash support can show report location.
- Every row should point to a real log line.

============================================================
Practical Example
============================================================

- A good practical test for OVERLAY API TAB starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
API Tab Lab
============================================================

- Add a row that reads from a manager summary.
- Change the manager state and verify the UI row changes.
- Add a disabled control with a reason string.
- Add a restart-required setting and verify config save.
- Add a live action and verify before/after logs.
- Screenshot the tab and confirm support can read the issue.
- Refresh diagnostics without restarting when possible.
- Remove any UI text that promises unproven behavior.

============================================================
Good UI States
============================================================

- Active should mean runtime evidence exists.
- Ready should mean available but waiting for condition.
- Managed should mean manager owns state but may guard writes.
- NeedsPatch should name the missing offset or signature category.
- Failed should include the failing operation.
- Disabled should say whether user config or release policy disabled it.
- Planned should not look like an active feature.
- Unknown should vanish after startup.

End of manual.
