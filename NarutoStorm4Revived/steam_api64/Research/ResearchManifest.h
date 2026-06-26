#pragma once

/*
    StormRevival research manifest.

    This file replaces loose .md/.txt notes so Visual Studio shows the research
    inside organized source folders.

    Current organization:
      Research/Core        - shared address/string/database tables
      Research/OnlineMenu  - online menu and lobby UI research
      Research/FreePlay    - scenario/free-battle setup research
      Research/Story       - story board and duel condition research
      Research/Settings    - gpSetting.xfbin scenario parser research
      Research/Shop        - store/material/unlock research
      Research/Character   - character/costume/variant database research
      Research/Stage       - stage filter research
      Research/Combat      - battle parameter/timing research

    Public safety:
      - No service tokens, private API keys, Supabase keys, or Cloudflare tokens.
      - All data here is local research naming and comments.
      - Addresses are version-sensitive and should be guarded before hard hooks.
*/

namespace StormRevival
{
namespace Research
{
    const char* GetPublicResearchManifest();
}
}
