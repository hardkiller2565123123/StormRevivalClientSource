============================================================
NETWORK
============================================================

- The main network manual. It teaches the offline/LAN strategy, the Steam-shaped lobby model, and the method other
  developers can reproduce.

Code map
- ISteamMatchmaking replacement, lobby state table, callback queue, LAN discovery adapter, API tab network
  diagnostics.

============================================================
Design Goal
============================================================

- Do not claim official Steam service restoration.
- Keep the game talking to a Steam-shaped API because the menus already understand that path.
- Use local or LAN data underneath the Steam-shaped lobby model.
- Make the proxy satisfy requests and make the framework show state.
- Treat packet transport as later work; menu compatibility comes first.
- Label modes honestly: offline, LAN, disabled, experimental.
- The first proof is search returning cleanly.
- The second proof is one local lobby.
- The third proof is LAN discovery feeding the same lobby list.
- The fourth proof is stable join, leave, and repeat.

============================================================
How We Did The Network Method
============================================================

- Logged the game matchmaking requests first.
- Designed lobbies as local objects with ID, owner, members, metadata, visibility, and state.
- Queued callbacks instead of blocking request methods.
- Kept SteamID and lobby ID stable for the session.
- Converted local or discovered sessions into the same lobby object shape.
- Logged request, decision, queue, dispatch, and teardown.
- Exposed callback and lobby counts in diagnostics.
- Kept LAN discovery below the Steam API boundary.
- Avoided pretending unsupported global matchmaking exists.
- Made failure states readable instead of silent.

============================================================
Replication Steps
============================================================

- Log RequestLobbyList.
- Queue a zero-result LobbyMatchList_t and prove the menu stops waiting.
- Create one fake lobby and return one result.
- Implement GetLobbyData and SetLobbyData for keys the game reads.
- Implement GetNumLobbyMembers and GetLobbyMemberByIndex.
- Implement JoinLobby as a state transition and queue LobbyEnter_t.
- Implement LeaveLobby and prove a second test is clean.
- Add LAN discovery behind the same result model.
- Add diagnostics before adding more network features.
- Test with the same build on both machines before blaming transport.

============================================================
Practical Example
============================================================

- A good practical test for NETWORK starts by launching the correct game target, confirming the proxy loaded,
  checking the framework or diagnostics view, and then performing the smallest menu action connected to this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Deep Replication Walkthrough
============================================================

- Start with the game menu, not the socket. The menu proves what Steam-shaped behavior is missing.
- Log RequestLobbyList and return a zero-result callback. If the menu exits search cleanly, the callback path works.
- Create one local lobby with stable ID, owner, member count, and metadata. If the menu lists it, the list path works.
- Implement JoinLobby as a state change and callback. If the menu enters it, the enter path works.
- Implement LeaveLobby and repeat the test. If the second run works, teardown is healthy.
- Only after those steps should LAN discovery feed lobbies into the same table.
- Keep transport separate so future direct IP, broadcast, or service backends reuse the lobby model.
- Every step should have a log line and a diagnostics counter.

============================================================
Network Examples
============================================================

- Searching with no lobbies is still success if the menu receives LobbyMatchList_t with count zero.
- A local self-lobby is enough to prove metadata and member queries.
- A LAN-discovered lobby should look identical to a local lobby after conversion.
- A lobby with missing owner can appear but fail join.
- A callback with wrong ID can make the menu wait forever.
- A stale lobby can make only the second search fail.
- A zero SteamID can break member lookup.
- A public release should call this offline/LAN behavior until real backend support exists.

End of manual.
