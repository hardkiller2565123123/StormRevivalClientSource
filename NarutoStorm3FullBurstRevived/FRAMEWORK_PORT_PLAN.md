# Storm 3 Full Burst Framework Port Plan

This file tracks the big-update path for porting the broader Naruto Revival framework into Storm 3 Full Burst without mixing in game-specific Storm 2/Storm 4 assumptions.

## Phase 1 - Stabilize The Base

- Correct public project identity and documentation for Storm 3 Full Burst.
- Keep offline Steam emulation as the default safe mode.
- Ensure crash handler, diagnostics, and support bundles are reachable from the overlay.
- Keep project files clean enough for Visual Studio to load reliably.

## Phase 2 - Framework Organization

- Rename remaining `NS2*` compatibility classes only after their Storm 3 responsibilities are clear.
- Split generic framework modules from game-specific offset modules.
- Keep shared DX11/ImGui helpers in one place and avoid duplicate overlay page files.
- Add a single status surface for hooks, asset systems, Lua, patches, and Steam emulation.

## Phase 3 - Storm 3 Runtime Research

- Verify executable names, module bases, and build variants.
- Replace placeholder offsets with Storm 3 Full Burst signatures.
- Add guarded pattern checks before enabling any runtime hook.
- Log hook enable/skip reasons so bad offsets fail closed instead of crashing.

## Phase 4 - Modding Tools

- Validate CPK/XFBIN parsing against Storm 3 files.
- Wire asset browser filters to Storm 3 folder and naming conventions.
- Add safe read-only previews before enabling write/override workflows.
- Keep backups automatic for any mod output path.

## Phase 5 - Release Readiness

- Produce a support-bundle-first testing flow.
- Add clear public configuration defaults.
- Keep private/research-only addresses out of release notes until verified.
- Document what is offline-only, experimental, or ready for normal users.
