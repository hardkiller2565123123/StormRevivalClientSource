# Seven Projects Map

NarutoRevival covers multiple Naruto Storm titles. Shared architecture is useful, but each target must be treated as its own game. The biggest mistake is assuming one offset, hook, vtable, or menu path works everywhere.

## Supported Targets

| Internal Target | Public Game | Architecture | Proxy | Notes |
|---|---|---|---|---|
| NS1 | Naruto Storm 1 | x64 | steam_api64 | Reaches Online Menu. |
| NS2 | Naruto Storm 2 | x64 | steam_api64 | Main active research target. |
| NS3 | Naruto Storm 3 | Win32 | steam_api | Watch pointer sizes and calling conventions. |
| NS3FB | Naruto Storm 3 Full Burst | x64 | steam_api64 | Do not merge blindly with NS3. |
| NSR | Naruto Storm Revolution | Win32 | steam_api | Currently crashes. Needs focused diagnostics. |
| NS4 | Naruto Storm 4 | x64 | steam_api64 | Good target for DLC/content and service research. |
| NSC | Naruto Storm Connections | x64 | steam_api64 | Does not reach online menu yet. |

## What Can Be Shared

- Logging system.
- Diagnostics report format.
- Feature registry concept.
- Manager lifecycle.
- Config reader.
- Overlay design.
- API client structure.
- Documentation format.
- Public release checklist.
- Safe patching philosophy.

## What Must Stay Per-Game

- Raw addresses.
- Pattern signatures.
- Hook install points.
- Steam interface version expectations.
- Menu gate behavior.
- Asset paths.
- DLC checks.
- Character slot layout.
- Stage slot layout.
- Calling convention assumptions.
- AppID.
- DLL architecture.

## Per-Game Rule

Every game needs its own file that answers:

1. Does it launch?
2. Does the proxy load?
3. Does the framework initialize?
4. Does the overlay/API tab work?
5. Does it reach online menu?
6. Which Steam interfaces are requested?
7. Which callbacks are needed?
8. Which menu gate fails?
9. Does it crash or hang?
10. What is the next research step?
