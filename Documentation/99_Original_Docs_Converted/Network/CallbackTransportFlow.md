============================================================
CALLBACK TRANSPORT FLOW
============================================================

- The detailed bridge between network requests, local lobby state, callback queue, and game menu completion.

Code map
- ISteamMatchmaking methods, lobby table, pending call result table, SteamAPI_RunCallbacks, API tab counters.

============================================================
Flow Walkthrough
============================================================

- The menu asks for a lobby action.
- The Steam-shaped method validates the request.
- The method updates local lobby or discovery state.
- The method queues a callback payload.
- The game continues running.
- SteamAPI_RunCallbacks dispatches the payload.
- The menu receives the expected callback.
- The menu queries follow-up lobby data.

============================================================
Why This Shape Works
============================================================

- It matches the game expectation better than blocking calls.
- It allows local, LAN, and future backend data to share one event path.
- It makes hangs diagnosable by separating request from dispatch.
- It keeps transport timing from directly controlling menu state.
- It lets diagnostics show pending events.
- It supports failure callbacks.
- It prevents request methods from doing too much work.
- It makes repeated tests easier to clean up.

============================================================
Trace Example
============================================================

- RequestLobbyList logged with filter count.
- Lobby list builder returns zero or more lobby IDs.
- LobbyMatchList_t queued with result count.
- SteamAPI_RunCallbacks dispatches it.
- Game asks GetLobbyByIndex for each result.
- Game asks GetLobbyData for display keys.
- User selects a lobby.
- JoinLobby begins the next callback flow.

End of manual.
