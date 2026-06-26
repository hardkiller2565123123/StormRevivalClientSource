# Framework Architecture

The framework is the shared structure that lets each NarutoRevival project initialize cleanly, expose diagnostics, register features, and eventually communicate with per-game services.

## Boot Order

1. Game loads replacement/proxy Steam DLL.
2. Proxy initializes logging as early as possible.
3. Proxy identifies target game and AppID.
4. Proxy creates stable Steam-like interface singletons.
5. Framework initializes project-specific module.
6. Managers initialize in a safe order.
7. Optional hooks are installed only after gates pass.
8. Overlay/API tab and diagnostics become available.
9. Menu-specific behavior is tested.

## Manager Model

Every major system should be a manager:

- `SteamProxyManager`
- `FeatureRegistry`
- `HookManager`
- `OverlayManager`
- `NetworkManager`
- `ApiClientManager`
- `DiagnosticsManager`
- `AssetManager`
- `ConfigManager`

Each manager should expose:

- Name.
- Enabled/disabled state.
- Initialized state.
- Last error.
- Last successful action.
- Diagnostic summary.

## Feature Registry

The Feature Registry exists so features are not random global hacks. Each feature should have:

- Feature ID.
- Display name.
- Target games.
- Default state.
- Config key.
- Risk level.
- Required manager.
- Required proof.

Example feature IDs:

- `core.proxy.boot`
- `core.framework.init`
- `ui.overlay`
- `steam.callbacks`
- `network.lan.discovery`
- `api.leaderboards`
- `assets.mod.routing`

## Safe Failure Rule

A broken optional feature should not crash the game. It should:

1. Log the failure.
2. Disable only itself.
3. Update diagnostics.
4. Continue boot if possible.

## Complete Framework Goal

The complete framework should let a contributor answer:

- Which game is running?
- Which DLL loaded?
- Which AppID is active?
- Which managers initialized?
- Which hooks installed?
- Which features are enabled?
- Which features failed?
- Which menu state was reached?
- Which API endpoint is configured?
