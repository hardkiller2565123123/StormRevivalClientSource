============================================================
LOGS AND CRASH SUPPORT
============================================================

- The evidence manual for supporting public users through logs, reports, screenshots, and crash triage.

Code map
- NarutoStorm4Revived.log, SteamDiagnosticsReport.txt, API tab, feature registry, crash-adjacent log lines.

============================================================
Evidence Order
============================================================

- Collect main revived log.
- Collect Steam diagnostics report.
- Collect API tab screenshot.
- Identify project and game version.
- Identify deployed proxy and framework files.
- Reproduce exact menu action.
- Compare deployed DLL to expected output when fixes seem missing.
- Find last manager state change.
- Separate build failure from runtime failure.
- Write the solved cause back into docs.

============================================================
Reading Logs
============================================================

- Startup lines prove proxy load.
- Framework lines prove overlay attach.
- Feature registry lines prove manager state.
- Version detection lines prove patch permission.
- Signature lines prove address discovery.
- Patch lines prove memory writes.
- Network lines prove lobby requests and callbacks.
- Asset lines prove mod scan and parser status.
- Slot lines prove target counts and missing anchors.
- Last risky line helps crash triage.

============================================================
Crash Patterns
============================================================

- Startup crash suggests proxy exports or early interface mismatch.
- Online menu crash suggests matchmaking interface or callback layout.
- Overlay crash suggests render hook or input capture.
- Asset crash suggests parser offset or missing file.
- Character-select crash suggests unverified slot UI offsets.
- Battle-start crash suggests handoff or content binding.
- Shutdown crash suggests stale callback or hook cleanup.
- Unknown-version patch crash means version gate failed.

============================================================
Practical Example
============================================================

- A good practical test for LOGS AND CRASH SUPPORT starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Support Lab
============================================================

- Ask for main log first.
- Ask for Steam diagnostics report second.
- Ask for API tab screenshot third.
- Identify project and game version.
- Identify deployed proxy and framework.
- Find last manager state change.
- Find last risky patch line.
- Tie the crash to a subsystem before editing code.

============================================================
Crash Examples
============================================================

- Startup crash points at proxy exports, interface factory, or early hook.
- Online menu crash points at matchmaking, callbacks, or network metadata.
- Overlay crash points at render hook or input capture.
- Asset crash points at parser or missing files.
- Character select crash points at UI offsets.
- Battle crash points at selected ID handoff or assets.
- Shutdown crash points at stale callbacks or cleanup.
- Unknown version crash points at missing gate.

End of manual.
