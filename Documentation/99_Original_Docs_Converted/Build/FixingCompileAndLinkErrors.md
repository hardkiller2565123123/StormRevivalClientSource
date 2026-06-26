============================================================
FIXING COMPILE AND LINK ERRORS
============================================================

- A build repair manual based on the actual classes of errors already fixed in this project.

Code map
- Compiler errors, linker errors, .vcxproj item lists, Windows headers, linker input, deployed DLLs.

============================================================
Compile Errors
============================================================

- Skipped initialization can come from decompiled goto flow.
- Fix by restructuring flow or moving initialization safely.
- String literals should not initialize mutable char pointers.
- Use const char pointer unless mutation is real.
- Illegal qualified names come from pasted decompiler symbols.
- Declare members normally inside classes.
- Wide API errors happen when char strings meet W variants.
- Use A variants or convert strings intentionally.

============================================================
Link Errors
============================================================

- Unresolved project symbol often means missing .cpp project entry.
- Unresolved global means declaration lacks one definition.
- Multimedia timer functions require the right import library.
- Hook helper symbols need implementation linked.
- Parser helpers need parser implementation linked.
- Namespace or signature mismatch can look like missing implementation.
- Do not add dummy stubs unless behavior is truly optional.
- Verify deployed DLL after link fixes.

============================================================
Actual Lessons
============================================================

- ShellExecuteA needed the correct header and narrow API intent.
- LoadLibraryA fixed narrow-string loading.
- GetPrivateProfileIntA fixed config reads under char strings.
- winmm fixed timer unresolved externals.
- moduleBase needed one real definition.
- gameList needed ownership restored.
- Project inclusion fixed several missing manager symbols.
- Build fixes should be documented because they return later.

============================================================
Practical Example
============================================================

- A good practical test for FIXING COMPILE AND LINK ERRORS starts by launching the correct game target, confirming
  the proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action
  connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Build Repair Lab
============================================================

- Copy the exact compiler or linker error.
- Identify whether it is compile, link, project, or deployment.
- For compile errors, read the local line and selected project settings.
- For link errors, find the referencing object and missing definition.
- For Windows API errors, check A/W variant and headers.
- For system symbols, check linker input libraries.
- For project symbols, check .vcxproj inclusion.
- After fixing, verify deployed binary changed.

============================================================
Known Fix Patterns
============================================================

- ShellExecuteA needed correct include and narrow API intent.
- LoadLibraryA matched char plugin path strings.
- GetPrivateProfileIntA matched char config keys.
- winmm resolved multimedia timer imports.
- moduleBase needed one definition.
- gameList needed restored ownership.
- Skipped initialization needed decompiled flow cleanup.
- const char fixes respected string literal immutability.

End of manual.
