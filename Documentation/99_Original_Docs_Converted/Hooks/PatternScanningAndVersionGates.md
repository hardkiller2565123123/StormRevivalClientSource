============================================================
PATTERN SCANNING AND VERSION GATES
============================================================

- How to find addresses safely and prevent patches from applying to unknown executables.

Code map
- PatternScan, module metadata, version detector, signature records, patch managers, feature registry NeedsPatch
  state.

============================================================
Scanning Purpose
============================================================

- Addresses can move between builds.
- Patterns identify code regions by byte sequence.
- Good patterns are specific but not brittle.
- Bad patterns match too much or too little.
- Scans must stay inside the intended module range.
- Multiple matches are unsafe.
- No match is a clear NeedsPatch result.
- One match still needs original-byte validation.

============================================================
Version Gate Method
============================================================

- Detect executable identity before patching.
- Store supported signatures per version.
- Refuse unknown versions by default.
- Do not silently fall back to another version.
- Log detected version label.
- Log missing signature names.
- Add new version records instead of overwriting old proof.
- Expose version support in diagnostics.

============================================================
Example Workflow
============================================================

- Define signature name.
- Scan module range.
- Handle no match.
- Handle multiple matches.
- Compute final target.
- Read original bytes.
- Compare expected instructions.
- Save address in diagnostics.
- Allow patch only after validation.
- Show result in API tab.

============================================================
Practical Example
============================================================

- A good practical test for PATTERN SCANNING AND VERSION GATES starts by launching the correct game target,
  confirming the proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu
  action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Scanner Lab
============================================================

- Name the signature after the feature, not the byte sequence.
- Scan only the target module range.
- Report no match distinctly.
- Report multiple matches distinctly.
- Validate original bytes after one match.
- Store address relative to module base for logs.
- Expose the result in diagnostics.
- Refuse patching on unknown version.

============================================================
Version Evidence
============================================================

- Executable hash is strong evidence.
- Executable size and timestamp are weaker but useful.
- A signature set can identify a supported layout.
- A supported version should list which signatures were proven.
- An unsupported version should still allow diagnostics.
- A game update should add a new record, not overwrite old proof.
- Users should see the detected version label.
- Release notes should say which version gained support.

End of manual.
