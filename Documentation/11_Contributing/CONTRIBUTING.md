# Contributing To NarutoRevival

NarutoRevival is a research-heavy open-source project. Contributions should improve stability, documentation, diagnostics, tooling, or game-specific support.

## Good Contributions

- Better logs.
- Safer hooks.
- Verified interface implementations.
- Per-game research notes.
- Build fixes.
- Documentation corrections.
- Reproducible crash reports.
- Clean config options.
- Test cases.

## Bad Contributions

- Unverified offsets.
- Removing diagnostics to hide errors.
- Claiming online support without proof.
- Mixing Win32 and x64 code unsafely.
- Hardcoding local user paths.
- Adding features without docs.
- Returning incomplete Steam vtables.

## Pull Request Checklist

- [ ] What game does this affect?
- [ ] What architecture was tested?
- [ ] What menu path was tested?
- [ ] What logs prove it works?
- [ ] What fails safely if the feature breaks?
- [ ] Was documentation updated?
- [ ] Was compatibility status changed honestly?

## Documentation Style

Keep documentation direct and factual. Prefer:

- What works.
- What does not work.
- What was tested.
- What is unknown.
- What to try next.

Avoid hype or unsupported claims.
