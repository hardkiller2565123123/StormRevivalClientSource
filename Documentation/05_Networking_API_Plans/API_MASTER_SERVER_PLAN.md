# API And Master Server Plan

Each game should eventually have its own API. The API should not be treated as one shared global service because every game has different menu behavior, lobby metadata, match rules, version needs, and future compatibility requirements.

## Current State

No current offline release should claim full LAN or online play. API work is planned and partially researched, but full integration is future work.

## Per-Game API Namespaces

Recommended namespace model:

- `/api/ns1/...`
- `/api/ns2/...`
- `/api/ns3/...`
- `/api/ns3fb/...`
- `/api/nsr/...`
- `/api/ns4/...`
- `/api/nsc/...`

## Core Endpoints

Every game should eventually support:

| Endpoint | Purpose |
|---|---|
| `/health` | Confirms API is alive. |
| `/status` | Returns public service state. |
| `/version` | Lets client compare local version with service version. |
| `/players` | Tracks public player profiles/state. |
| `/sessions` | Tracks game sessions. |
| `/lobbies` | Lists active joinable lobbies. |
| `/matchmaking/search` | Requests a match. |
| `/matchmaking/cancel` | Cancels search. |
| `/matches/report` | Reports match result. |
| `/leaderboards` | Returns ranked stats. |
| `/news` | Returns launcher/client news. |
| `/config` | Returns feature flags. |

## Data Model Draft

### Player

- `id`
- `game`
- `username`
- `display_name`
- `created_at`
- `last_seen_at`
- `client_version`
- `is_banned`
- `ban_reason_public`

### Lobby

- `id`
- `game`
- `host_player_id`
- `region`
- `mode`
- `ranked`
- `status`
- `max_players`
- `current_players`
- `metadata`
- `created_at`
- `expires_at`

### Match

- `id`
- `game`
- `player_a`
- `player_b`
- `winner`
- `ranked`
- `score_data`
- `reported_at`
- `verified`

### Leaderboard Entry

- `game`
- `player_id`
- `username`
- `wins`
- `losses`
- `score`
- `rating`
- `updated_at`

## Service Rules

- Keep game data separated.
- Never trust client-reported ranked results without validation planning.
- Rate-limit write endpoints.
- Support anonymous/offline testing separately from public ranked stats.
- Do not require a web account for basic offline research builds.
- Do require authentication for public profiles, ranked stats, moderation, and admin tools.

## Future Hosting Options

### Supabase

Good for:

- Auth.
- Postgres data.
- Leaderboards.
- Profiles.
- Edge functions.
- Admin tools.

### Cloudflare

Good for:

- Public website.
- API gateway.
- Lightweight Workers.
- Caching public status/news.
- D1/KV/R2 for lightweight storage.

### Hybrid Recommendation

- Website on Cloudflare.
- Public cached status/news on Cloudflare.
- Auth/profiles/stats on Supabase or a dedicated backend.
- Game API can start as Supabase Edge Functions, then move hot paths to Cloudflare Workers if needed.
