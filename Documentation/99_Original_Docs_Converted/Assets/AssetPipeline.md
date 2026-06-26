============================================================
ASSET PIPELINE
============================================================

- The mod content pipeline manual: discovery, validation, ownership, parsing, routing, diagnostics, and support.

Code map
- Mod folder scanner, asset manager, DLC ownership bridge, CPK redirect map, XFBIN parser, diagnostics report.

============================================================
Goal
============================================================

- Let mod content live beside the game.
- Avoid permanent base-file replacement.
- Discover mod folders.
- Validate required files.
- Parse metadata.
- Route ownership and IDs.
- Redirect lookups safely.
- Log accepted and skipped content.
- Keep content availability separate from menu slots.
- Give modders predictable rules.

============================================================
Pipeline Steps
============================================================

- Scan controlled mods directory.
- Read manifest or infer metadata.
- Validate required files.
- Check duplicate IDs.
- Check target game.
- Check DLC or ownership requirements.
- Parse binary formats when needed.
- Register accepted content.
- Build redirect map.
- Expose summary in diagnostics.

============================================================
Failure Handling
============================================================

- Missing file skips one mod.
- Duplicate ID reports both folders.
- Unsupported target game disables the mod.
- Parser failure reports file and offset when possible.
- Missing preview uses placeholder.
- Disabled mod remains visible as disabled.
- Broken redirect falls back when safe.
- A bad mod should not break the entire loader.

============================================================
Practical Example
============================================================

- A good practical test for ASSET PIPELINE starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Asset Lab
============================================================

- Create one mod folder with a manifest.
- Validate required files.
- Check target game and IDs.
- Parse one known file.
- Register one accepted content item.
- Redirect one lookup.
- Log accepted and skipped counts.
- Show the mod in diagnostics.

============================================================
Asset Examples
============================================================

- A valid asset without a slot is loaded content waiting for UI binding.
- A slot without a valid asset is a placeholder or broken binding.
- A duplicate ID should name both folders.
- A missing preview should use a placeholder.
- A parser failure should skip one mod, not all mods.
- A disabled mod should remain visible as disabled.
- A wrong target game should be ignored clearly.
- A redirect should not overwrite original files.

End of manual.
