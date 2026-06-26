============================================================
MANIFEST FORMAT
============================================================

- A proposed manifest guide for public mod folders so content can be discovered, validated, and diagnosed
  consistently.

Code map
- mod.json or equivalent manifest, mod folder scanner, asset registry, diagnostics output.

============================================================
Suggested Fields
============================================================

- mod name.
- author.
- target game.
- content type.
- primary ID.
- version.
- required files.
- optional preview.
- dependencies.
- enabled flag.

============================================================
Validation Rules
============================================================

- Target game must match current project.
- Primary ID must be unique within the content type.
- Required files must exist before registration.
- Version should be readable by support.
- Dependencies should fail clearly.
- Disabled mods should not register redirects.
- Unknown fields can be ignored with verbose warning.
- Malformed manifest should skip only that mod.

============================================================
Example Outcome
============================================================

- Valid character manifest registers character content but does not create a visible slot by itself.
- Valid stage manifest registers files and preview for stage systems.
- Invalid target game is ignored with a log reason.
- Duplicate ID reports both folders.
- Missing required file lists the exact path.
- Disabled mod appears in diagnostics as disabled.
- Manifest parse error includes file name and line or offset if known.
- Accepted manifest contributes to loaded mod count.

End of manual.
