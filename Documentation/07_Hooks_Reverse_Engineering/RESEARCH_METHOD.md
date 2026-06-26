# Reverse Engineering And Hook Research Method

This project should document methods, not just final code. Every future contributor should be able to understand why a hook exists and how it was proven safe.

## Safe Hook Rules

1. Identify the exact target game and executable.
2. Confirm architecture.
3. Confirm module base.
4. Prefer signatures over raw addresses when possible.
5. Version-gate dangerous patches.
6. Log hook install success/failure.
7. Disable hook if pattern is missing.
8. Never assume another game has the same layout.
9. Keep one patch per test when debugging.
10. Document the menu action that proves the hook.

## Research Record Template

Use this template for every new hook or patch:

```md
# Research Record: <Feature>

Game:
Architecture:
Executable:
Build/date:
Module:
Address or pattern:
Function purpose:
Why hook is needed:
Inputs observed:
Outputs observed:
Crash risk:
Fallback behavior:
Test steps:
Proof:
Logs:
Next work:
```

## Crash Investigation Flow

1. Reproduce with clean config.
2. Capture log and diagnostics report.
3. Note exact menu/action.
4. Disable optional hooks.
5. Re-enable one system at a time.
6. Inspect last Steam interface request.
7. Inspect last callback/result.
8. Inspect last installed hook.
9. Fix smallest likely cause.
10. Retest the same path.

## What Not To Do

- Do not blindly paste offsets from one game to another.
- Do not claim support from launch-only testing.
- Do not hide crashes by disabling important diagnostics.
- Do not return fake objects with incomplete vtables.
- Do not remove logs just because the log is noisy during research.
