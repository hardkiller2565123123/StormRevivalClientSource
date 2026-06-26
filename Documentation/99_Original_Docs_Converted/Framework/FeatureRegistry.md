============================================================
FEATURE REGISTRY
============================================================

- The state model that lets managers report truth to the overlay and support reports.

Code map
- RuntimeFeatureRegistry, feature rows, categories, manager summary strings, API tab table.

============================================================
States
============================================================

- Planned means design exists but runtime does not claim implementation.
- NeedsPatch means addresses or signatures are missing.
- Managed means a manager owns diagnostics or settings but may guard writes.
- Ready means the feature can run when conditions allow.
- Active means runtime evidence exists.
- Failed means an attempt produced a specific failure.
- Disabled means config or release policy turned it off.
- Unknown should be temporary during startup only.

============================================================
Manager Contract
============================================================

- Register rows during initialization.
- Update state after config load.
- Update state after version detection.
- Update state after patch attempts.
- Expose detail strings with counts, addresses, or missing requirements.
- Log state transitions.
- Avoid UI-invented state.
- Keep categories consistent.

============================================================
Good Rows
============================================================

- Stage slots: Active after supported patch applied.
- Scene slots: Failed if signature missing.
- Character select: NeedsPatch if UI anchors missing.
- LAN discovery: Active if socket and discovery loop run.
- Steam callbacks: Active after dispatch.
- Assets: Ready after parser and mod folder scan.
- Overlay hook: Active after first successful draw.
- Crash report: Planned until capture exists.

============================================================
Practical Example
============================================================

- A good practical test for FEATURE REGISTRY starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Registry Lab
============================================================

- Create one feature row during manager initialization.
- Update it after config load.
- Update it after version detection.
- Update it after a patch attempt.
- Expose a detail string with counts or missing anchors.
- Log every state transition.
- Show the row in the API tab.
- Use the same summary in the support report.

============================================================
State Mistakes
============================================================

- Do not mark saved settings as Active.
- Do not mark diagnostics-only managers as complete features.
- Do not let UI code guess manager state.
- Do not collapse all failures into Unknown.
- Do not use Ready when a missing signature blocks execution.
- Do not use NeedsPatch when the user simply disabled a feature.
- Do not hide dangerous patch refusal.
- Do not remove Planned rows if they explain the roadmap honestly.

End of manual.
