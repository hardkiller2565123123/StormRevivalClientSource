OpenArchive UI Hook Pass

This update adds a real universal hook framework under OnlineMenu/Hooking and a custom option registry under OnlineMenu/CustomUI.

What it does now:
- Hooks known native Flash/Scaleform bridge functions.
- Logs movie registration/unregistration.
- Logs Invoke calls to menu movies like netbattlemainmenu and option/setting menus.
- Registers OpenArchive custom options in C++:
  - OpenArchive
  - Custom Stages
  - Mods
  - Plugins
  - LAN / Radmin
  - Developer Tools
- Hooks stage/resource/scenario/scene research targets for logging.
- Adds an ActionScript archive index generated from Cs.zip.

What it does NOT pretend to do yet:
- It does not patch GFX files.
- It does not force a fake menu button until the exact list population function for the target settings/menu GFX is confirmed.
- It does not bypass or replace online services.

Next step:
Run the game, open menus/settings/online menu, then inspect logs for:
- movie names
- Invoke function names
- list population calls
- current selection reads

Once the exact list setter/select handler is seen in logs, CustomOptionSystem can inject real selectable OpenArchive options without editing GFX.
