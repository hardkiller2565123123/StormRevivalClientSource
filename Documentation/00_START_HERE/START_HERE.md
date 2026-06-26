# Start Here

This folder is the entry point for the NarutoRevival documentation set.

The project currently exists as a research and preservation framework for multiple Naruto Storm games. The releases are not final products. They are development snapshots intended to prove launch support, framework loading, hook safety, Steam API proxy behavior, menu access, diagnostics, and future service planning.

## Current Purpose

The primary goal is to provide as much useful research as possible:

- How each game boots.
- Which proxy DLL each game loads.
- Which Steam interfaces each game requests.
- Which menus are reachable.
- Which games crash and where.
- Which systems can be shared across projects.
- Which systems must stay game-specific.
- What needs to be documented before LAN or online work can be claimed.

## Current Public Claim

Use this wording publicly:

> NarutoRevival Offline Release is an early open-source research release. These builds are designed for framework development, testing, preservation, and online-menu research. They do not currently provide LAN or online play.

## Repository Reading Order

1. `README.md`
2. `01_Project_Status/PROJECT_STATUS.md`
3. `02_Game_Research/SEVEN_PROJECTS_MAP.md`
4. The specific game file you are working on.
5. `03_Framework/FRAMEWORK_ARCHITECTURE.md`
6. `04_Steam_Proxy/STEAM_API_PROXY.md`
7. `05_Networking_API_Plans/API_MASTER_SERVER_PLAN.md`
8. `09_Diagnostics_Support/DIAGNOSTICS_GUIDE.md`
9. `10_Release_Open_Source/RELEASE_CHECKLIST.md`

## Definition Of Complete For A Feature

A feature is not complete just because the game launches once. A feature is complete only when it has:

- A clear owner module.
- A config option if it can affect users.
- Safe failure behavior.
- A log line for success and failure.
- A diagnostics field.
- A reproducible test.
- Documentation.
- Per-game compatibility notes.

## Definition Of Research Done

Research is considered documented when it includes:

- Target game and executable.
- Architecture: Win32 or x64.
- Proxy DLL used.
- Steam AppID.
- Menu path tested.
- Behavior observed.
- Crash or hang details if applicable.
- Logs captured.
- Known missing interfaces or callbacks.
- Next investigation step.
