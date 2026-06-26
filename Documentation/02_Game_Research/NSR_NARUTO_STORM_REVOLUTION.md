# Naruto Storm Revolution Research Notes

## Target Identity

| Field | Value |
|---|---|
| Internal code | NSR |
| Game | Naruto Storm Revolution |
| Steam AppID | 272510 |
| Architecture | Win32 |
| Proxy DLL | `steam_api.dll` |
| Current status | Currently crashes |

## Current Notes

Needs crash-first workflow. Do not add features until boot path is stable.

## Required Proof Before Status Changes

Before changing this game's status, collect:

- Fresh launch log.
- Steam diagnostics report.
- Screenshot or clear note of the highest reached menu.
- Interface request list.
- Callback count.
- Last error or crash address if failing.
- Exact build date and source commit if available.

## Research Checklist

- [ ] Confirm the correct proxy DLL loads.
- [ ] Confirm AppID is reported correctly.
- [ ] Confirm framework manager initializes.
- [ ] Confirm render/input hooks do not break the game.
- [ ] Log all Steam interface requests.
- [ ] Log all unknown interfaces.
- [ ] Log every online-menu gate.
- [ ] Document highest reachable menu.
- [ ] Document crash/hang if present.
- [ ] Add next-step notes after each test.

## API Plan Placeholder

This game will eventually receive its own API namespace. Do not mix API state between games.

Planned future API areas:

- Health/status.
- Players.
- Sessions.
- Lobbies.
- Match results.
- Leaderboards.
- Bans/moderation.
- Version checks.
- News/config.

## Known Risk Areas

- Steam interface version mismatch.
- Missing callbacks.
- Menu gate waiting for online state.
- Architecture mismatch.
- Unsafe shared offsets.
- Hook installed too early or too late.
- Missing export in proxy DLL.
