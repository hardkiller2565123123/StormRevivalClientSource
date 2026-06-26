# Build And Deployment

Build issues are common because this project crosses Win32/x64, multiple Visual Studio versions, proxy DLL names, and Steam interface exports.

## Architecture Rules

| Target | Architecture | Proxy |
|---|---|---|
| NS1 | x64 | steam_api64.dll |
| NS2 | x64 | steam_api64.dll |
| NS3 | Win32 | steam_api.dll |
| NS3FB | x64 | steam_api64.dll |
| NSR | Win32 | steam_api.dll |
| NS4 | x64 | steam_api64.dll |
| NSC | x64 | steam_api64.dll |

## Common Build Failures

| Error | Likely Cause | Fix |
|---|---|---|
| unresolved `MH_Initialize` | MinHook library not linked | Link correct Win32/x64 MinHook `.lib`. |
| unresolved Windows API symbol | Missing system library | Add required `.lib` to linker input. |
| DLL builds but game ignores it | Wrong output name/path | Verify deployed `steam_api.dll` or `steam_api64.dll`. |
| Crash at boot | Wrong architecture or missing export | Verify imports/exports and platform. |
| Feature code exists but does nothing | File not in project | Add `.cpp` to project and rebuild. |

## Deployment Verification

Before testing a game:

1. Build correct configuration.
2. Check output DLL timestamp.
3. Copy DLL to game folder.
4. Confirm file name matches game architecture.
5. Delete old logs.
6. Launch game.
7. Confirm new log is created.
8. Confirm AppID and project name in log.
9. Confirm interface requests appear.

## Recommended Output Layout

```txt
Build/
  NS1/x64/steam_api64.dll
  NS2/x64/steam_api64.dll
  NS3/Win32/steam_api.dll
  NS3FB/x64/steam_api64.dll
  NSR/Win32/steam_api.dll
  NS4/x64/steam_api64.dll
  NSC/x64/steam_api64.dll
```

## Release Build Rule

A release zip should include:

- Correct DLL.
- Config file.
- README.
- Changelog.
- Compatibility status.
- Known issues.
- No misleading online/LAN claims.
