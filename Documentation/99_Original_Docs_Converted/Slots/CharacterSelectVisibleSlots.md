============================================================
CHARACTER SELECT VISIBLE SLOTS
============================================================

- The hard chapter explaining why extra character boxes need more than target counts and what offsets must be
  discovered next.

Code map
- Character select UI draw loop, roster table, cursor bounds, portrait lookup, name lookup, costume lookup, battle
  handoff.

============================================================
Why Boxes Do Not Appear Yet
============================================================

- A target character count is only a requested capacity.
- A roster capacity patch is only storage.
- The select screen needs grid data.
- The cursor needs movement bounds.
- Portraits need icon lookup.
- Names need text lookup.
- Costumes need count lookup.
- Battle needs selected-index handoff.
- Missing any one part can crash or show bad data.
- That is why diagnostics are safer than blind writes.

============================================================
Offsets Needed
============================================================

- Roster table anchor.
- Original roster count comparison.
- Visible grid row and column data.
- Cursor bounds.
- Selected index mapping.
- Portrait table.
- Name table.
- Costume count table.
- Team/support compatibility.
- Battle handoff table or function.

============================================================
Research Method
============================================================

- Trace reads of known original character IDs.
- Find comparisons against original roster count.
- Watch draw loops for original box count.
- Change one candidate value at a time in a controlled test.
- Trace selected ID into portrait calls.
- Trace selected ID into name calls.
- Trace selected ID into battle load.
- Patch one placeholder before adding real characters.
- Log every found address.
- Version-gate every write.

============================================================
Practical Example
============================================================

- A good practical test for CHARACTER SELECT VISIBLE SLOTS starts by launching the correct game target, confirming
  the proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action
  connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Visible Slot Lab
============================================================

- Find where the original select screen decides how many boxes to draw.
- Find where cursor movement clamps row or column.
- Find where selected index becomes character ID.
- Find where character ID becomes portrait.
- Find where character ID becomes name.
- Find where character ID becomes costume list.
- Find where selected ID enters battle load.
- Patch one placeholder path before adding real assets.

============================================================
Why This Is Hard
============================================================

- The UI can draw a box that battle cannot load.
- The cursor can reach an index the name table cannot describe.
- The portrait can render while costume lookup crashes.
- The roster can store entries the visible grid never asks for.
- The battle handoff can reject a valid-looking menu selection.
- Team/support rules can have separate limits.
- Every table may have its own count.
- One missing table can make the whole feature unsafe.

End of manual.
