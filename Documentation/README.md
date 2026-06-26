# NarutoRevival Offline Release Documentation

This documentation package is the complete public-facing research and development manual for the **NarutoRevival Offline Release** source code.

The current releases are early-stage offline/research builds. Their purpose is to help each supported Naruto Storm title launch, initialize the framework, expose diagnostics, and reach the highest currently supported online-menu state. These builds do **not** currently provide working LAN, matchmaking, or online play.

NarutoRevival is an open-source preservation and community project. The long-term goal is to document the games, preserve knowledge, build safe tooling, and eventually support per-game APIs, player services, LAN functionality, leaderboards, matchmaking, and community utilities.

## Current Compatibility

| Game | Current Status | Notes |
|---|---|---|
| Naruto Storm 1 | Reaches Online Menu | Foundation build; research continuing. |
| Naruto Storm 2 | Reaches Online Menu | Primary active target for framework and service work. |
| Naruto Storm 3 | Reaches Online Menu | Win32-sensitive target; keep architecture separate. |
| Naruto Storm 3 Full Burst | Reaches Online Menu | Separate from original Storm 3 where needed. |
| Naruto Storm Revolution | Currently crashes | Needs boot, Steam interface, and crash diagnostics work. |
| Naruto Storm 4 | Reaches Online Menu | Strong target for framework, DLC/content research, and future services. |
| Naruto Storm Connections | Does not currently reach Online Menu | Needs deeper Steam/menu-gate emulation and diagnostics. |

## What This Package Contains

- A clean README for the repository.
- A contributor-friendly project status map.
- Per-game research notes.
- Framework architecture notes.
- Steam API proxy documentation.
- Future API and master-server planning.
- LAN and networking research plans.
- Diagnostics and support report formats.
- Build and deployment checks.
- Release checklist and open-source guidelines.
- The original uploaded `.h` documentation converted into readable Markdown reference files.

## Important Project Rules

1. Tell the truth about current support.
2. Do not advertise LAN or online play until it works.
3. Keep every game target separated by architecture, executable version, AppID, and proxy DLL name.
4. Do not blindly port offsets or signatures between games.
5. Every risky feature needs diagnostics before public release.
6. Every public feature should have a log line, config option, and documentation entry.
7. NarutoRevival will remain open source.
