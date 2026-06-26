============================================================
MANAGER LIFECYCLE
============================================================

- How runtime managers should initialize, load config, register features, apply behavior, report diagnostics, and
  shut down.

Code map
- Managers, config loader, feature registry, API tab controls, logs, shutdown path.

============================================================
Lifecycle Steps
============================================================

- Construct manager with safe defaults.
- Load config without applying dangerous behavior immediately.
- Register feature rows.
- Detect game version if needed.
- Run diagnostics.
- Apply safe startup behavior.
- Expose controls to the framework.
- Write support summary.
- Handle shutdown without leaving stale state.

============================================================
Manager Contract
============================================================

- Managers own feature truth.
- Managers own their config keys.
- Managers own patch permission checks.
- Managers own diagnostic strings.
- Managers log state transitions.
- Managers reject unsafe requests.
- Managers provide read-only summaries for UI.
- Managers should be testable one behavior at a time.

============================================================
Bad Manager Signs
============================================================

- UI writes memory directly.
- Config changes do not reach runtime.
- State says Active without evidence.
- Failure reason is empty.
- Manager depends on another target game offset.
- Shutdown leaves callbacks or hooks alive.
- Diagnostics disagree with logs.
- Support cannot tell which manager failed.

End of manual.
