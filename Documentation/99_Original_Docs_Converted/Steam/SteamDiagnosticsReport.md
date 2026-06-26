============================================================
STEAM DIAGNOSTICS REPORT
============================================================

- What the Steam diagnostics report should contain and how support should read it.

Code map
- SteamDiagnosticsReport.txt, AppID record, interface counters, callback counters, lobby counters, ownership state.

============================================================
Report Fields
============================================================

- Project name and AppID.
- Proxy file name and architecture.
- SteamAPI_Init status.
- Interface request counts by version string.
- Unknown interface strings.
- Callback queued and dispatched counts.
- Last callback ID and source subsystem.
- Lobby request and result counts.
- DLC ownership answers.
- Last Steam-layer error.

============================================================
Support Reading Method
============================================================

- Start with AppID to make sure the correct project identity loaded.
- Check interface failures before debugging menus.
- Check callback counts when menus wait forever.
- Check lobby counters when online menus show empty state.
- Check DLC answers when content is hidden.
- Check architecture when the wrong proxy appears.
- Compare report time with main log time.
- Attach the report to every serious networking or Steam API issue.

============================================================
Future Expansion
============================================================

- Add per-interface last-called method when verbose mode is enabled.
- Add callback latency measurement.
- Add lobby metadata key list.
- Add remote storage path summary.
- Add stats persistence mode.
- Add framework attachment status.
- Add loaded config path.
- Add deployed DLL build label.

End of manual.
