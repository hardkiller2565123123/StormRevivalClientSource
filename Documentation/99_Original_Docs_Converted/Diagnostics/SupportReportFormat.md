============================================================
SUPPORT REPORT FORMAT
============================================================

- The exact information public users should send when something breaks.

Code map
- Main log, Steam diagnostics report, API tab screenshot, project name, game version, deployed DLL details.

============================================================
Required User Data
============================================================

- Revived project name.
- Game executable version.
- Proxy DLL name and location.
- Framework DLL name and location.
- Main revived log.
- Steam diagnostics report.
- Screenshot of API tab if overlay opens.
- Exact menu path or action.
- Whether the issue happens after restart.
- Whether mods are installed.

============================================================
Maintainer Reading Order
============================================================

- Confirm correct project.
- Confirm correct architecture.
- Confirm proxy startup.
- Confirm framework startup.
- Confirm feature registry state.
- Confirm manager diagnostics.
- Confirm last error.
- Confirm whether deployed binary is current.
- Reproduce smallest action.
- Document result.

============================================================
Issue Template Example
============================================================

- Title should include project and subsystem.
- Body should include expected result and actual result.
- Attach logs instead of screenshots alone.
- Mention whether the game crashed, hung, or showed wrong content.
- Mention whether this is a clean install.
- Mention mod list when asset issues happen.
- Mention host/client setup for network issues.
- Mention slot target settings for expansion issues.

End of manual.
