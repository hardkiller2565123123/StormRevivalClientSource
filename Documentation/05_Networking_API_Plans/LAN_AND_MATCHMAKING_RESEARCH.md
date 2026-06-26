# LAN And Matchmaking Research

LAN and matchmaking are future goals. They should not be marked as working until proven with two clients and repeatable tests.

## Current Truth

The offline releases do not currently provide LAN or online play. Current research is focused on launch, framework initialization, Steam API emulation, online-menu access, and diagnostics.

## Research Goals

1. Understand how each game enters online menu.
2. Understand how each game creates/searches lobbies.
3. Identify which Steam matchmaking interfaces are used.
4. Identify which callbacks are required.
5. Identify whether game traffic is Steam P2P, sockets, or custom transport.
6. Build local lobby discovery only after the menu path is stable.
7. Build two-client tests before public claims.

## LAN Design Draft

Possible local LAN flow:

1. Client starts.
2. Framework reads LAN config.
3. Client broadcasts local presence.
4. Other clients respond with game/version/lobby metadata.
5. Lobby list is displayed through fake Steam matchmaking results or custom overlay.
6. Join request routes to the selected host.
7. Game-specific transport bridge handles the actual connection path.

## Matchmaking Design Draft

Possible API matchmaking flow:

1. Player enters matchmaking.
2. Client sends search request to API.
3. API places player into a queue by game/mode/region/version.
4. API pairs compatible players.
5. API returns match/lobby connection info.
6. Client injects/bridges the result into the game path.
7. Match result is reported after completion.

## Required Proof For LAN

- Two separate clients can discover each other.
- Host can create a visible lobby.
- Guest can join.
- Match can start.
- Match can complete.
- Disconnect is handled.
- Logs show exact flow.
- Feature can be disabled.

## Required Proof For Matchmaking

- Search request reaches API.
- Queue state is visible in logs.
- Pairing result is returned.
- Client handles success and timeout.
- Bad version mismatch is rejected cleanly.
- Match starts between paired players.
- Result reporting works or is clearly marked disabled.
