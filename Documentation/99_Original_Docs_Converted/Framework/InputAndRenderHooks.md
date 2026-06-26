============================================================
INPUT AND RENDER HOOKS
============================================================

- How the framework should draw the overlay and handle input without breaking the game menus.

Code map
- Framework render hook, input capture, overlay open state, tab navigation, shutdown cleanup.

============================================================
Render Rules
============================================================

- Install render hooks only after the device or render context is safe.
- Draw the overlay once per frame when open.
- Keep frame work light to avoid stutter.
- Handle device reset or context loss if the game triggers it.
- Log first successful draw.
- Avoid duplicate hook installation.
- Separate drawing from feature logic.
- Keep UI state readable for screenshots.

============================================================
Input Rules
============================================================

- Open and close overlay predictably.
- Capture input only while overlay needs it.
- Release input cleanly when closing.
- Do not block game confirm/back when overlay is closed.
- Handle keyboard and controller paths if the game uses both.
- Avoid repeated toggles from one held key.
- Log input capture state in diagnostics.
- Test title screen, menus, battle, pause, and shutdown.

============================================================
Failure Signs
============================================================

- Overlay never appears: render hook did not install or draw.
- Game menu stops responding: input capture did not release.
- Overlay flickers: render state or duplicate draw path is unstable.
- Crash on alt-tab: device reset path is missing.
- Crash on shutdown: hook cleanup or stale UI state.
- Buttons trigger twice: input debounce missing.
- Text overlaps: layout bounds are wrong.
- Screenshot cannot prove state: UI lacks manager detail.

End of manual.
