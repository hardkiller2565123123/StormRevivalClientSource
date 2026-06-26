============================================================
LAN DISCOVERY AND TRANSPORT
============================================================

- How LAN discovery should feed lobby-shaped data without becoming tangled with UI or Steam identity.

Code map
- Discovery socket or adapter, discovered session table, lobby conversion, diagnostics counters, protocol version
  field.

============================================================
Boundary
============================================================

- LAN discovery is not the public Steam API.
- LAN discovery is a transport source that creates lobby-shaped records.
- The game still asks Steam-shaped matchmaking methods.
- The user should see the mode labeled as LAN.
- The framework should show discovered count and last packet time.
- The proxy should convert discovered sessions into lobby results.
- Transport code should not draw UI.
- Discovery should not block the game thread.

============================================================
Protocol Data
============================================================

- Project ID prevents wrong games from listing each other.
- AppID prevents wrong title identity from mixing.
- Protocol version prevents old clients from silently misreading packets.
- Lobby ID identifies the session.
- Host identity supports deduplication.
- Member count and max members support menu display.
- Mode and rules support filters.
- Address data supports join attempts after the lobby is selected.

============================================================
Implementation Path
============================================================

- Start with loopback or manual entries to prove lobby conversion.
- Add broadcast or direct address discovery after conversion works.
- Validate received packet fields before creating lobbies.
- Deduplicate by host identity and lobby ID.
- Expire stale lobbies after timeout.
- Log packets received, ignored, added, updated, and expired.
- Expose discovery mode in diagnostics.
- Only add match transport after discovery and lobby lifecycle are stable.

============================================================
Practical Example
============================================================

- A good practical test for LAN DISCOVERY AND TRANSPORT starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
LAN Lab
============================================================

- Begin with loopback discovery so firewalls do not hide model bugs.
- Encode project, AppID, protocol, host ID, lobby ID, member count, and mode.
- Reject packets for the wrong project before they reach the lobby list.
- Reject packets for the wrong protocol with a diagnostic reason.
- Merge packets from the same host and lobby ID.
- Expire sessions that stop announcing.
- Convert valid sessions into lobby objects.
- Join through the lobby model rather than directly from packet data.

============================================================
Transport Warnings
============================================================

- Broadcast discovery can be blocked by network settings.
- Direct address mode can help testing but should still produce the same lobby object.
- Packet data must be validated because LAN does not mean trusted.
- Discovery should not block the game thread.
- Packet receive count is not the same as join readiness.
- A discovered lobby with wrong AppID should be visible only in diagnostics, not the game list.
- Timeouts should remove stale entries cleanly.
- Protocol version changes need release notes.

End of manual.
