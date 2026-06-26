# Diagnostics Guide

Diagnostics are the most important part of this project. Without logs, every crash becomes guessing.

## Required Logs

Each game should produce:

- Main runtime log.
- Steam diagnostics report.
- Framework diagnostics report.
- Crash summary if available.
- Config snapshot.

## Main Log Should Include

- Build label.
- Game target.
- AppID.
- Architecture.
- Proxy DLL loaded.
- Config path.
- Managers initialized.
- Hooks installed.
- Steam interfaces requested.
- Unknown interfaces.
- Callback queue activity.
- Online-menu state changes.
- Last error.

## Steam Diagnostics Report

Recommended fields:

```txt
Project:
Game:
AppID:
Architecture:
Proxy DLL:
Build:
SteamAPI_Init:
SteamAPI_RunCallbacks count:
Requested interfaces:
Unknown interfaces:
Callbacks queued:
Callbacks dispatched:
Last callback:
Lobby requests:
Leaderboard requests:
Stats requests:
Remote storage requests:
DLC ownership checks:
Last Steam error:
```

## Support Report Format

When someone reports a bug, ask for:

1. Game.
2. What they clicked.
3. What happened.
4. What they expected.
5. Main log.
6. Steam diagnostics report.
7. Screenshot if menu-related.
8. Whether it happens on clean config.
9. Whether any mods are installed.
10. Build/date of the release.

## Crash Classification

| Crash Type | Meaning |
|---|---|
| Boot crash | Proxy/export/architecture issue. |
| Menu crash | Interface, callback, hook, or menu gate issue. |
| Lobby crash | Matchmaking or callback result issue. |
| Asset crash | Bad file, bad redirect, bad parser, missing ownership state. |
| Exit crash | Shutdown order or stale hook issue. |
