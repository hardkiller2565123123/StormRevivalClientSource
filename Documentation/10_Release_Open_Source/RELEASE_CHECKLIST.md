# Release Checklist

Use this checklist before publishing any NarutoRevival release.

## Public Text Checklist

- [ ] Says this is an offline/research release.
- [ ] Does not claim working LAN unless proven.
- [ ] Does not claim working online unless proven.
- [ ] Lists current compatibility honestly.
- [ ] Lists known broken games.
- [ ] Explains that some builds are unstable.
- [ ] States the project is open source.

## Build Checklist

- [ ] Correct architecture built.
- [ ] Correct proxy DLL name.
- [ ] Correct AppID.
- [ ] Fresh timestamp verified.
- [ ] Old DLL not accidentally packaged.
- [ ] Config included.
- [ ] Debug-only secrets removed.
- [ ] Logs folder behavior tested.

## Documentation Checklist

- [ ] README updated.
- [ ] Compatibility table updated.
- [ ] Known issues updated.
- [ ] Per-game notes updated.
- [ ] Changelog updated.
- [ ] Diagnostics instructions included.

## Testing Checklist

For each game in the release:

- [ ] Launch tested.
- [ ] Proxy load confirmed.
- [ ] Framework init confirmed.
- [ ] Highest menu state confirmed.
- [ ] Crash status confirmed.
- [ ] Logs generated.
- [ ] Diagnostics report generated.

## Open Source Commitment

NarutoRevival should remain open source. Public source code, docs, and research notes are part of the preservation goal. If something is not ready, mark it incomplete instead of hiding it.
