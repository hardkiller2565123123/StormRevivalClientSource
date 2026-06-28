#pragma once
// STORM 4 IDA OFFSET USAGE GUIDE
// Generated from the IDA string export, then organized for NarutoStorm4Revived.
//
// What this dump is:
// The input file is an IDA Strings window export. Each row gives a string address, length, type, and text.
// A string address is not automatically a function address. It is an anchor. The workflow is: string -> xrefs -> nearby function -> version-safe pattern -> runtime patch.
//
// Files generated beside Offsets.h:
// 1. Storm4IdaStringOffsets_All.h keeps every parsed row from IDA as comments.
// 2. Storm4IdaStringOffsets_Actionable.h groups useful rows by system so we can search fast.
// 3. This guide explains what to use each category for.
//
// Image base:
// IDA addresses in this export look like 0x141185D58, so the assumed image base is 0x140000000.
// Runtime RVA = IDA_VA - 0x140000000. Runtime address = moduleBase + RVA.
// Do not hard-patch raw VA values unless the executable image base is guaranteed. Prefer RVAs or byte patterns.
//
// CharacterSelect:
// Use charaSelectParam, ccUiCharSelect, select/costume/player/support strings as anchors for visible roster work.
// For extra character boxes, xref the strings that load chara select params and inspect the code that allocates or indexes UI cells.
// The correct patch is usually not the string itself. Find the function that reads the table count, allocates the grid, clamps the index, or maps UI cell -> character id.
// After finding the clamp, create a pattern around nearby instructions and add a game-version gate before enabling it.
//
// StageScene:
// Use STAGE_* strings, scene manager strings, and stage param paths to find stage arrays, scene tables, and menu preview loading.
// Stage expansion needs both data-table loading and visible UI list expansion. If stages load but boxes do not appear, the UI list clamp still needs patching.
//
// Network:
// netEvent*, lobby, matching, session, Steam, and friend strings identify online-safe paths.
// For offline releases, prefer stubbing network calls at the Steam API layer first, then patch game-side calls only when the game waits forever or crashes.
//
// Battle:
// Battle strings help locate free battle, pair special skill, team ultimate, guard, awakening, projectile, damage, and round logic.
// These are useful for mod-facing APIs, but most battle patches need exact struct layout validation before writes are enabled.
//
// ParamTables:
// Manager::Create errors and version asserts are high-value loader anchors. They tell us which manager owns a data file and what version check can block custom files.
// When a custom XFBIN loads but does nothing, xref its manager string and inspect version/count/key checks.
//
// Assets:
// data/, xfbin, swf, flash, nucc, model, texture, and cpk strings map the shipped asset tree.
// Use these to build asset browser categories, preload targets, and file override paths.
//
// UI:
// UI/Flash/menu/icon strings are the fastest way to locate visible screens.
// For visible extra slots, UI anchors matter as much as data anchors because the game can have data capacity without drawing boxes.
//
// SourceFiles:
// Jenkins source paths expose original internal file names. These are extremely useful for naming our hooks and documentation.
// If a source path mentions a manager class, search nearby strings and xrefs to map that class responsible area.
//
// Audio:
// BGM/sound/voice/CRI strings point at audio tables and can help the BGM manager, voice replacement, and preload diagnostics.
//
// InputCamera:
// Camera/input/pad/key/button anchors are useful for overlay focus handling, camera mods, debug freecam, and controller remapping.
//
// SlotsExpansion:
// slot/count/max/array/selectParam anchors are candidates for roster/stage/projectile/team tables.
// Treat them as candidates only: verify with xrefs, nearby constants, and runtime logging before writing memory.
//
// Immediate fixes these files enable:
// - Build a char-select xref hunt list instead of guessing offsets.
// - Build a stage-select xref hunt list separate from stage data loading.
// - Name unknown managers from source-path and Manager::Create strings.
// - Add asset browser filters from real shipped paths.
// - Convert repeated high-value anchors into PatternScan signatures.
//
// Recommended next workflow:
// 1. Pick one user-visible goal, such as visible extra character boxes.
// 2. Search Storm4IdaStringOffsets_Actionable.h for charaSelectParam, ccUiCharSelect, costume, support, and slot.
// 3. In IDA, jump to that VA and use xrefs.
// 4. Find the function that reads or clamps the count.
// 5. Copy 20-40 bytes around stable instructions, wildcard addresses, and add a PatternScan entry.
// 6. Add runtime logging before writing so bad versions disable the patch instead of crashing.
//
// Do not blindly write every address from the generated list. The all-list exists so nothing is lost; the actionable list exists so we can work safely.
