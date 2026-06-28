# steam_api64 Organized Layout

This package reorganizes the project so root only contains:
- `dllmain.cpp`
- Visual Studio project files
- `.gitignore`

Main folders:
- `Core/` core runtime, logging, hooks, safety, common utilities
- `Steam/` Steam API emulation/proxy interfaces
- `OnlineMenu/` online menu, UI hooks, custom options, lobby, settings, store, hooks
- `Rendering/` DX11 overlay, ImGui, graphics helpers
- `Audio/` audio and BGM helpers
- `Input/` input and focus guard
- `Network/` LAN/network hooks and ENet C sources
- `Framework/` StormAPI/framework/plugin/mod bridge files
- `Game/` game-side parameters, scene/game systems, slot expansion, stage helpers
- `Content/` DLC/debug/TUI/content loader code
- `IDA/` IDA/runtime offset helpers
- `Documents/` all `.txt` and `.md` documentation moved here with original folder paths preserved
- `Lib/` `.lib` files
- `Config/` config/json/ini files

`steam_api64.vcxproj` and `.filters` were updated so Visual Studio shows files inside matching folders.
Additional include directories now include the project root and all source subfolders so existing `#include "File.h"` style includes keep working after the move.

Extra cleanup:
- `lua/` moved to `ThirdParty/lua/`.
- `sdk_includes/` moved to `Steam/SDK/`.
- `IdaOffsets/` moved to `IDA/IdaOffsets/`.
- GFX SDK moved to `GFX/NS4_GFX_CPP_SDK_Generated/`.
- Old `Build/` output folders were removed from the source ZIP.
