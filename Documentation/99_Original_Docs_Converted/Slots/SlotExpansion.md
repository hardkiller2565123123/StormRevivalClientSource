============================================================
SLOT EXPANSION
============================================================

- The capacity manual for stage, scene, character, costume, and support slots. It separates settings from visible
  proof.

Code map
- SlotExpansionManager, StageSlotExpansionManager, CharacterSlotExpansionManager, config [slots], API tab slot
  controls.

============================================================
Slot Categories
============================================================

- Stage slots are table and lookup capacity problems.
- Scene slots are scene-list and selection lookup problems.
- Character slots are UI, roster, costume, portrait, name, and battle handoff problems.
- Costume slots depend on character lookup and costume count tables.
- Support slots may involve team and assist compatibility.
- Battle selection depends on selected index resolving to valid load data.
- Each category needs its own diagnostics.
- One success category does not prove another.

============================================================
Current Safe Behavior
============================================================

- Saved target counts are config requests.
- Stage and scene expansion can apply when signatures match.
- Character diagnostics can report missing anchors.
- Unknown character-select memory is not written.
- Restart-required behavior is visible because some tables form during boot.
- Logs show target counts and patch results.
- Feature state stays Managed or NeedsPatch when UI proof is missing.
- This prevents users from expecting visible boxes too early.

============================================================
How To Replicate
============================================================

- Prove one safe table capacity patch.
- Find one UI table anchor.
- Add one placeholder entry.
- Make cursor reach it.
- Make display data read safely.
- Make battle handoff resolve safely.
- Bind one real content item.
- Test restart, menu revisit, battle, and teardown.
- Raise counts gradually.
- Document supported version.

============================================================
Practical Example
============================================================

- A good practical test for SLOT EXPANSION starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Slot Lab
============================================================

- Save target stage, scene, character, and costume counts.
- Apply only supported stage or scene patches.
- Run character diagnostics without writing unknown select UI memory.
- Log detected version and target counts.
- Log every missing anchor.
- Show category states separately in the API tab.
- Restart when a table forms only during boot.
- Scale after one visible proof, not before.

============================================================
Slot Examples
============================================================

- Stage expansion can be Active while character select remains NeedsPatch.
- Scene expansion can prove table patching without proving roster patching.
- A character count of 512 does not draw 512 boxes.
- A costume count can be invalid if the character lookup table still points to original data.
- A support slot may require separate team compatibility tables.
- A battle slot needs handoff proof after UI proof.
- A placeholder slot is the first visual milestone.
- A real modded character is a later milestone.

End of manual.
