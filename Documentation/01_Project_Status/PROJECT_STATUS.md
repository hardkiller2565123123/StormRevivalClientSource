# Project Status

NarutoRevival is currently in the **offline research foundation** stage.

The source code is being released so the community can study, preserve, improve, and contribute to the Naruto Storm project lineup. The current builds are intentionally honest: they are bare-minimum foundation builds, not finished LAN or online replacements.

## Current Feature Status

| Feature | Status | Details |
|---|---|---|
| Game launch support | In progress / working on most targets | Each game needs its own verification. |
| Framework initialization | In progress | Shared architecture exists, but game-specific modules must remain separate. |
| Startup hooks | In progress | Must be version-gated and logged. |
| Online Menu access | Partially working | Most targets reach online menu; Revolution crashes; Connections does not reach online menu. |
| LAN play | Not implemented | Planned future feature. |
| Matchmaking | Not implemented | Requires master-server/API work and game-specific network replacement research. |
| Leaderboards | Planned / partial research | Per-game API planned. |
| Player profiles | Planned | Should be web/API-backed later. |
| Documentation | Active | This package is the first complete organized public manual. |
| Open source | Committed | Project should stay public and documented. |

## Current Compatibility Table

| Game | AppID | Proxy | Architecture | Current State | Priority |
|---|---:|---|---|---|---|
| Naruto Storm 1 | 495140 | steam_api64.dll | x64 | Reaches Online Menu | Medium |
| Naruto Storm 2 | 543870 | steam_api64.dll | x64 | Reaches Online Menu | High |
| Naruto Storm 3 | 234670 | steam_api.dll | Win32 | Reaches Online Menu | Medium |
| Naruto Storm 3 Full Burst | 234670 | steam_api64.dll | x64 | Reaches Online Menu | Medium |
| Naruto Storm Revolution | 272510 | steam_api.dll | Win32 | Currently crashes | High debug priority |
| Naruto Storm 4 | 349040 | steam_api64.dll | x64 | Reaches Online Menu | High |
| Naruto Storm Connections | 1020790 | steam_api64.dll | x64 | Does not reach Online Menu | High research priority |

## Public Release Warning

Do not describe this as a working online revival yet. The accurate wording is:

- Offline research release.
- Source code release.
- Framework foundation.
- Online-menu access research.
- No LAN yet.
- No full matchmaking yet.
- Some games unstable or incomplete.

## Highest Priority Work

1. Stabilize Revolution boot crash.
2. Find why Connections fails before online menu.
3. Standardize logs across all projects.
4. Add per-game diagnostics reports.
5. Add clean config files for every game.
6. Build a per-game API plan before implementation.
7. Make every menu claim provable with screenshots/logs.
