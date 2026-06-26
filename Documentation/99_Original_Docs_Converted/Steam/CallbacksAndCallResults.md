============================================================
CALLBACKS AND CALL RESULTS
============================================================

- The asynchronous event manual: how call handles, callback payloads, and SteamAPI_RunCallbacks keep menus from
  hanging.

Code map
- Callback queue, call result table, lobby callbacks, stats callbacks, overlay callbacks, SteamAPI_RunCallbacks.

============================================================
Why Menus Wait
============================================================

- Steam-style APIs often start work now and finish through a callback later.
- The game may set a waiting flag after a request.
- The waiting flag is cleared only when the expected callback arrives.
- Returning true from the request is not enough.
- Dispatching the wrong callback ID is the same as dispatching nothing.
- Dispatching the wrong payload size can corrupt the reader.
- Dispatching too early can happen before the game records the call handle.
- Dispatching through SteamAPI_RunCallbacks matches the game expectation.

============================================================
Queue Design
============================================================

- Store callback ID, payload bytes, source subsystem, optional call handle, and timestamp.
- Queue events from request methods instead of calling handlers immediately.
- Pump events from SteamAPI_RunCallbacks.
- Keep payload storage alive until dispatch finishes.
- Assign unique call handles during a session.
- Map call handles to results for asynchronous methods.
- Log queue and dispatch events in verbose mode.
- Expose pending callback count in diagnostics.

============================================================
Examples
============================================================

- RequestLobbyList queues LobbyMatchList_t.
- CreateLobby queues LobbyCreated_t.
- JoinLobby queues LobbyEnter_t.
- Stats requests queue the expected stats-ready event if the game waits for one.
- Overlay state can queue overlay activation callbacks when supported.
- A failure still needs the failure-shaped callback the game expects.
- A search hang means check callback dispatch first.
- A crash after dispatch means check payload layout and size.

============================================================
Practical Example
============================================================

- A good practical test for CALLBACKS AND CALL RESULTS starts by launching the correct game target, confirming the
  proxy loaded, checking the framework or diagnostics view, and then performing the smallest menu action connected to
  this topic.
- If the test fails, keep the failure narrow. Do not change five systems at once. Read the log, identify the owning
  layer, make one correction, and test the same action again.
- When the test succeeds, update the matching manual file with the exact evidence so the next person does not have to
  rediscover it.


============================================================
Callback Lab
============================================================

- Make RequestLobbyList return zero results through a queued callback, not a direct fake return.
- Record call handle creation and callback dispatch separately.
- Print callback ID, payload size, and source subsystem in verbose logs.
- Delay dispatch until SteamAPI_RunCallbacks so the game can register its wait state.
- Test a successful callback and a failure callback for the same menu path.
- Clear dispatched call results so stale handles do not leak into the next attempt.
- Track pending callback count in diagnostics.
- When a menu spins forever, inspect this file before editing transport code.

============================================================
Payload Examples
============================================================

- LobbyMatchList_t should carry the number of lobbies the search produced.
- LobbyCreated_t should carry lobby ID and result.
- LobbyEnter_t should carry lobby ID and enter response.
- Stats-ready callbacks should match the game expectation even if stats are local no-op.
- Failure callbacks should be shaped like real Steam failures.
- Payload bytes must survive until dispatch finishes.
- Callback IDs must match what the game registered.
- Structure packing mistakes can turn a correct idea into a crash.

End of manual.
