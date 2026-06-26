# Asset And Modding Plan

The asset/modding side should be safe, reversible, and documented. The goal is not to permanently overwrite base game files. The goal is controlled discovery, validation, routing, diagnostics, and eventual per-game tooling.

## Principles

- Keep mods outside base game archives when possible.
- Validate files before loading.
- Log every accepted and skipped mod.
- Keep mod IDs unique.
- Keep game targets explicit.
- Keep DLC/ownership checks separate from file discovery.
- Provide a manifest format.

## Recommended Mod Manifest

```json
{
  "id": "example.mod.id",
  "name": "Example Mod",
  "author": "AuthorName",
  "version": "1.0.0",
  "targetGame": "NS4",
  "type": "character|stage|music|ui|misc",
  "requiresDlc": [],
  "files": [
    {
      "source": "files/example.xfbin",
      "target": "data/example/path.xfbin"
    }
  ]
}
```

## Loader Checklist

- [ ] Scan mods directory.
- [ ] Read manifest.
- [ ] Validate target game.
- [ ] Validate files exist.
- [ ] Check duplicate mod IDs.
- [ ] Check unsupported types.
- [ ] Register accepted mods.
- [ ] Build redirect map.
- [ ] Write diagnostics summary.

## Future Tools

- Manifest validator.
- XFBIN parser viewer.
- CPK routing inspector.
- DLC/content state viewer.
- Title music override tool.
- Character slot visibility tool.
- Stage slot visibility tool.
