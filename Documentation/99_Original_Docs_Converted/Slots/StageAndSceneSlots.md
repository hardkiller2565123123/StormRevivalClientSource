============================================================
STAGE AND SCENE SLOTS
============================================================

- A focused manual for stage and scene expansion, separate from character-select expansion.

Code map
- StageSlotExpansionManager, scene expansion path, table capacity signatures, API tab slot state.

============================================================
Difference From Character Slots
============================================================

- Stage and scene expansion usually target list capacity and lookup paths.
- Character expansion also needs visible select UI, portraits, names, costumes, and battle handoff.
- A stage patch can succeed while character boxes remain missing.
- A scene patch can be version-supported without proving roster support.
- Keep feature registry rows separate.
- Keep logs separate.
- Keep release notes separate.
- Do not use stage success as marketing for character slots.

============================================================
Stage Scene Method
============================================================

- Detect game version.
- Find stage or scene table signature.
- Validate original bytes or table shape.
- Apply capacity change if supported.
- Log old and new capacity.
- Expose state in API tab.
- Test menu selection.
- Test loading the selected stage or scene.

============================================================
Failure Cases
============================================================

- Signature missing means NeedsPatch.
- Capacity changed but menu still clamps means UI clamp is separate.
- Menu shows item but load fails means handoff or asset path is separate.
- Wrong version can crash when table layout changed.
- Restart may be needed if table builds at boot.
- A missing preview can look like failed slot expansion.
- Asset file failure can be mistaken for slot failure.
- Support logs should separate patch result from asset result.

End of manual.
