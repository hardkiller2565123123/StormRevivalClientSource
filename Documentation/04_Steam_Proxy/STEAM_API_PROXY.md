# Steam API Proxy

The Steam API proxy is the first critical boundary. The game already expects to load `steam_api.dll` or `steam_api64.dll`. NarutoRevival uses that boundary to provide stable offline-friendly behavior, logging, and future framework startup.

## Main Jobs

- Export every required Steam API function.
- Initialize logs before silent failure can happen.
- Return stable interface objects.
- Track requested interface versions.
- Provide safe local answers for ownership/persona/basic status.
- Pump callbacks through `SteamAPI_RunCallbacks`.
- Support game-specific framework initialization.
- Never return unsafe nulls where the game expects a valid interface.

## Required Exports

Every target should verify its imports. Common exports include:

- `SteamAPI_Init`
- `SteamAPI_Shutdown`
- `SteamAPI_RunCallbacks`
- `SteamAPI_RestartAppIfNecessary`
- `SteamAPI_GetHSteamUser`
- `SteamAPI_GetHSteamPipe`
- `SteamInternal_CreateInterface`
- `SteamAPI_ISteamClient_GetISteamUser`
- `SteamAPI_ISteamClient_GetISteamFriends`
- `SteamAPI_ISteamClient_GetISteamUtils`
- `SteamAPI_ISteamClient_GetISteamMatchmaking`
- `SteamAPI_ISteamClient_GetISteamUserStats`
- `SteamAPI_ISteamClient_GetISteamApps`
- `SteamAPI_ISteamClient_GetISteamRemoteStorage`

## Interface Factory Rules

1. Log every requested interface string.
2. Return exact versions when possible.
3. Do not alias versions unless vtable layout is proven compatible.
4. Keep interface objects alive for the whole process.
5. Never return stack objects.
6. Unknown interfaces should be logged once in normal mode and fully in verbose mode.
7. A menu crash after interface creation often means vtable mismatch.

## Callback Pump

Many online menus wait for callbacks. If callbacks are not pumped, a menu may hang forever even when interfaces exist.

The callback system should track:

- Callback queued count.
- Callback dispatched count.
- Last callback ID.
- Last callback source subsystem.
- Time since last callback.
- Pending callback count.

## Minimum Local Steam Answers

For online-menu research, the proxy usually needs safe answers for:

- User logged on.
- Persona name.
- SteamID.
- App ownership.
- DLC ownership when applicable.
- Stats initialized.
- Remote storage available or safely disabled.
- Matchmaking object exists.
- Lobby creation/search returns controlled responses.

## Crash Clues

| Symptom | Likely Area |
|---|---|
| Crash immediately at boot | Missing export or wrong architecture. |
| Crash after `CreateInterface` | Bad vtable or wrong interface version. |
| Online menu hangs | Missing callbacks or menu gate not satisfied. |
| Lobby screen empty forever | Matchmaking callback/result not returned. |
| DLC hidden | Apps/DLC ownership answer wrong. |
| Stats crash | UserStats vtable or output buffer issue. |
