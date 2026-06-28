# NS4 GFX C++ SDK Generated From ActionScript

This is a standalone C++/header kit generated from `Cs.zip`.

It does **not** patch the game by itself. It gives your DLL a typed registry and helper API so the native hooks can call into known GFX/ActionScript symbols safely.

## Contents

- `include/NS4GFX/ASSymbolRegistry.h` - all 2078 ActionScript files indexed as C++ symbols.
- `src/ASSymbolRegistry.cpp` - generated registry data.
- `include/NS4GFX/GfxBridge.h` - bridge interface your Scaleform hooks implement.
- `include/NS4GFX/CustomUI.h` - OpenArchive custom menu/page abstraction.
- `src/CustomUI.cpp` - default pages: LAN, Custom Stages, Mods, Plugins, Developer Tools.
- `include/NS4GFX/GeneratedCategories.h` - category helpers for Online, Settings, StageSelect, CharacterSelect, AdventureWorld, etc.
- `original_as/` - original AS files organized by category for reference.
- `docs/` - symbol reports.

## How to use in steam_api64

1. Add `include` to Additional Include Directories.
2. Add all files from `src` to the project.
3. Implement `NS4GFX::IGfxBridge` using your real Scaleform hooks.
4. Call:

```cpp
NS4GFX::SetBridge(&yourBridge);
NS4GFX::RegisterDefaultOpenArchivePages();
NS4GFX::Runtime().OpenPage("net_match_menu", "openarchive.root");
```

The generated registry lets you query every AS class/method at runtime:

```cpp
size_t count = 0;
const auto* symbols = NS4GFX::GetAllSymbols(&count);
```

## Important

ActionScript code cannot be directly executed as C++. This kit converts the AS into metadata, wrappers, categories, and C++ runtime calls. Your DLL still needs the native GFx invoke/set-variable hooks to actually affect the game UI.
