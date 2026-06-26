============================================================
NETWORK TROUBLESHOOTING
============================================================

- The support playbook for searches, joins, LAN discovery, callback failures, and stale lobbies.

Code map
- Network logs, Steam diagnostics report, API tab network state, lobby object table, callback queue.

============================================================
Search Troubleshooting
============================================================

- If the menu searches forever, check whether RequestLobbyList was logged.
- If it was logged but no callback dispatched, fix the queue.
- If callback count is zero, verify whether zero results should still close the menu wait.
- If callback count is positive but UI is empty, check metadata and visibility.
- If LAN packets arrive but no lobbies appear, check project, AppID, and protocol filtering.
- If duplicate lobbies appear, check dedupe.
- If stale lobbies stay forever, check expiration.
- If search works once only, check cleanup after leave or shutdown.

============================================================
Join Troubleshooting
============================================================

- If a lobby appears but join fails, inspect JoinLobby logs.
- If JoinLobby logs success but waits, inspect LobbyEnter_t.
- If enter fires and UI returns to menu, inspect result code and member list.
- If member names are blank, inspect persona and SteamID state.
- If host and client disagree, inspect LAN conversion.
- If second join fails, inspect stale active lobby state.
- If crash happens after callback, inspect payload size.
- If the wrong game appears in LAN list, inspect filters.

============================================================
Support Packet
============================================================

- Ask for main log.
- Ask for Steam diagnostics report.
- Ask which project and game version.
- Ask whether host and client use the same build.
- Ask whether the test is same machine, same LAN, or remote.
- Ask for firewall notes when no packets arrive.
- Ask for last lobby ID and callback ID.
- Ask for exact menu action.

============================================================
Practical Example
============================================================

- A good practical test for NETWORK TROUBLESHOOTING starts by launching the correct game target, confirming the proxy
  loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to this
  topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Decision Tree
============================================================

- Search hangs: inspect callback dispatch.
- Search returns empty: inspect lobby count and filters.
- Lobby appears but join hangs: inspect LobbyEnter_t.
- Join succeeds then drops: inspect member data and metadata.
- Only second attempt fails: inspect teardown.
- LAN sees nothing: inspect discovery start, firewall, packets, and protocol.
- Wrong games appear: inspect AppID and project filters.
- Crash after callback: inspect payload layout.

============================================================
Support Questions
============================================================

- Which revived game and build are both users running?
- Does the main log show the proxy loaded?
- Does the diagnostics report show RequestLobbyList?
- How many callbacks are pending and dispatched?
- What lobby ID was last created or joined?
- Was the test offline, same machine, same LAN, or remote?
- Did both sides use the same protocol version?
- What exact menu action happened before failure?

End of manual.
