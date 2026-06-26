============================================================
HOW TO EXTEND THIS FOREVER
============================================================

- The contributor guide for extending the project in a way future people can understand, debug, and trust.

Code map
- All project folders, managers, docs, logs, diagnostics, feature registry, release notes.

============================================================
Mindset
============================================================

- Add evidence, not magic.
- Start with the smallest proof.
- Name failures plainly.
- Never copy offsets without proof.
- Include files in projects.
- Put lessons in docs.
- Do not claim active without runtime proof.
- Do not remove diagnostics for cosmetic cleanliness.
- Do not ship risky patches silently.
- Make the next developer faster.

============================================================
Workflow
============================================================

- State the goal.
- Identify the owning layer.
- Add diagnostics first.
- Build one safe proof.
- Log request, decision, action, and result.
- Add feature registry state.
- Add config only through a manager.
- Document reproduction steps.
- Test restart behavior.
- Scale only after proof.

============================================================
Good Future Work
============================================================

- Find one character-select grid anchor and document it.
- Add one placeholder visible character slot.
- Bind one mod character to one proven slot.
- Add LAN diagnostics before match transport.
- Add parser warnings that help modders.
- Add build checks for missing project files.
- Add support fields that name failing managers.
- Add release notes that tell the truth.

============================================================
Practical Example
============================================================

- A good practical test for HOW TO EXTEND THIS FOREVER starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Contributor Lab
============================================================

- Pick one small feature.
- Name its owning layer.
- Add diagnostics before behavior.
- Prove one menu action or one file parse.
- Add feature state if runtime-visible.
- Add logs for request and result.
- Write documentation with reproduction steps.
- Only then scale.

============================================================
Legacy Mindset
============================================================

- Future contributors should know why a file exists.
- Future modders should know what folder shape works.
- Future maintainers should know what evidence proved a patch.
- Future users should know what to send when broken.
- Future ports should know which assumptions are shared.
- Future builds should not rediscover old linker fixes.
- Future docs should be written with the code, not after memory fades.
- The project lives longer when its methods are teachable.

End of manual.
