<p align="center">
    <img src="https://cdn2.steamgriddb.com/hero/0bf727e907c5fc9d5356f11e4c45d613.png" alt="NarutoStorm3FullBurstRevived Banner">
</p>

# NarutoStorm3FullBurstRevived

A community-driven preservation, offline-play, research, modding, and enhancement project for **NARUTO SHIPPUDEN: Ultimate Ninja STORM 3 Full Burst** on PC.

NarutoStorm3FullBurstRevived preserves community knowledge, improves modern Windows compatibility, and provides a framework for offline Steam emulation, runtime hooks, overlays, asset research, and modding tools.

---

## About

Released by CyberConnect2 and Bandai Namco Entertainment, **Ultimate Ninja STORM 3 Full Burst** remains one of the most important entries in the Storm series, with cinematic story battles, a large roster, and a PC release that benefits from preservation and compatibility work.

This project focuses on:

* Offline preservation and play support
* Steam API proxy/emulation research
* Runtime hooking and diagnostics
* Asset inspection and mod-loading tools
* DX11 overlay tooling
* Crash reports and support bundles
* Quality-of-life improvements for modern PCs
* Documentation for future research

---

## Current Features

### Steam / Offline Layer

* `steam_api64.dll` proxy framework
* Local Steam persona and SteamID emulation
* Local stats and remote-storage replacement
* Local/offline lobby and matchmaking scaffolding
* LAN-only safety defaults
* Steam interface route diagnostics
* Packet and callback logging tools

### Framework Features

* Runtime hook bootstrap
* Patch manager
* DX11 + ImGui overlay
* Asset browser and inspection pages
* CPK/archive research helpers
* Lua manager and Lua hook scaffolding
* Mod redirector and override manager
* Windowed/borderless helpers
* Crash handler with minidump generation
* Support-bundle generation for testing

### Research / Modding Features

* File loading telemetry
* Asset discovery and reporting
* Texture/model preview scaffolding
* Asset conflict and duplicate scanning
* Bulk extraction and backup helpers
* Runtime game/file hook organization
* Framework add-on entry points

> Some systems are experimental while Storm 3-specific offsets and behavior are still being verified.

---

## Recommended Test Flow

1. Build the `steam_api64` project for the platform you are testing.
2. Place the proxy DLL next to the Storm 3 Full Burst executable.
3. Launch the game and keep the debug console open.
4. Check `NarutoStorm3FullBurstRevived\Logs\NarutoStorm3FullBurstRevived.log`.
5. Use the overlay debug page to write diagnostics or a support bundle when something breaks.

---

## Research & Documentation Targets

The project is intended to document and improve:

* Character and costume systems
* Stages and scene loading
* Animation and effect containers
* Menu and UI flow
* Save data behavior
* Steam API usage
* Networking and lobby behavior
* Rendering and overlay compatibility
* Asset containers and mod overrides

---

## Contributing

Contributions are welcome, especially in these areas:

* Storm 3 Full Burst offset verification
* Compatibility testing
* Reverse engineering notes
* Asset format documentation
* Crash logs and support bundles
* Mod-loader testing
* UI/overlay testing

---

## Disclaimer

NarutoStorm3FullBurstRevived is an unofficial fan-made project created for preservation, research, educational, offline-play, and modding purposes.

No copyrighted game assets, game files, or proprietary content are distributed through this repository. Users are expected to own a legitimate copy of the game.

NarutoStorm3FullBurstRevived is not affiliated with, endorsed by, or sponsored by:

* CyberConnect2
* Bandai Namco Entertainment
* Shueisha
* Studio Pierrot
* Masashi Kishimoto

---

## AI Assistance Notice

AI tools were used to assist with development, documentation, and research. All content is reviewed and maintained by the project owner.

---

## License

Released under the MIT License. See the LICENSE file for details.

---

## Links

Game on Steam:

https://store.steampowered.com/app/234670/NARUTO_SHIPPUDEN_Ultimate_Ninja_STORM_3_Full_Burst/

---

*Preserving Storm 3 Full Burst, one hook and one asset at a time.*
