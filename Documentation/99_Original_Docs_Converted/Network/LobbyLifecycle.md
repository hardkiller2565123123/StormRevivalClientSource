============================================================
LOBBY LIFECYCLE
============================================================

- How a lobby should exist through create, list, join, metadata update, leave, and teardown.

Code map
- Lobby object table, lobby ID generator, member list, metadata map, join state, leave cleanup.

============================================================
Lobby Object Shape
============================================================

- A lobby needs ID, owner, members, metadata, visibility, max members, source, and state.
- The source can be local, LAN, or future backend.
- The state can be Created, Listed, Entering, Entered, Leaving, Closed, or Failed.
- Metadata should use string keys because Steam lobby data is key-value shaped.
- Members should use stable SteamID values.
- The same lobby ID returned in search must resolve during join.
- Visibility controls whether it appears in lobby lists.
- Max members and current member count must stay consistent.

============================================================
Lifecycle Method
============================================================

- CreateLobby allocates state and queues a created callback.
- RequestLobbyList filters visible lobbies and queues a list callback.
- JoinLobby validates ID, sets pending state, adds local member, and queues enter callback.
- SetLobbyData updates metadata and logs the changed key.
- GetLobbyData reads the same object that search returned.
- LeaveLobby clears current membership and active lobby state.
- Shutdown clears pending lobbies that should not survive the session.
- Discovery refresh updates LAN lobbies without destroying active references.

============================================================
Bug Patterns
============================================================

- Search spins when list callback never dispatches.
- Join hangs when LobbyEnter_t never dispatches.
- Members vanish when SteamID is zero or changes.
- Metadata is blank when read/write paths point at different lobby objects.
- Second search fails when leave cleanup misses pending callbacks.
- Duplicate LAN entries appear when dedupe does not use host identity.
- Stale lobbies remain when expiration is missing.
- Crash after close often means a callback references destroyed lobby state.

============================================================
Practical Example
============================================================

- A good practical test for LOBBY LIFECYCLE starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Lifecycle Lab
============================================================

- Create a lobby and write its ID, owner, max members, and state.
- List lobbies and verify the same ID is returned.
- Join that ID and confirm the state changes from Listed to Entered.
- Set metadata and read it back through the same object.
- Add the local member and read it back by index.
- Leave and confirm current lobby state clears.
- Run the same create-list-join-leave test again.
- If the second run differs from the first, teardown is incomplete.

============================================================
Lifecycle Examples
============================================================

- A lobby can be visible but not joinable if its state is Closed.
- A lobby can be joinable but display wrong rules if metadata was never written.
- A discovered lobby can expire without killing an active joined lobby if references are separated.
- A host migration feature would need explicit owner transfer later.
- A private lobby should exist but stay out of public search.
- A failed lobby should queue a failure-shaped callback.
- A lobby object should outlive callbacks that reference it.
- A destroyed lobby ID should not resolve silently to a new object.

End of manual.
