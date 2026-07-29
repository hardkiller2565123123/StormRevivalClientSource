#pragma once

#include <cstdint>

namespace RuntimeStructures
{
    // Small option/default block stored at RuntimeMember112 + 72.
    // sub_1400B48D0 initializes it including the native vtable/cookie.
    // sub_1400B49E0 initializes only the default flag values.
    // sub_1400B4900 resets the native vtable/cookie during destruction.
    struct RuntimeMemberOptions40
    {
        uint64_t vtable = 0;       // +0 native option block vtable/cookie
        int flag8 = 1;             // +8 default enabled flag
        int flag12 = 1;            // +12 default enabled flag
        int flag16 = 1;            // +16 default enabled flag
        uint64_t flag20 = 1;       // +20 default enabled flag/value
        uint8_t reserved28[12]{};  // +28 unknown/padding
    };

    static_assert(sizeof(RuntimeMemberOptions40) == 40, "Runtime member options block must stay 40 bytes");

    // 112-byte runtime character/member slot. The game constructs this with
    // sub_1400B14E0, fills defaults with sub_14093A850, and destroys it with
    // sub_1400B17E0. Three of these are used for a team: leader, support 1,
    // support 2. sub_14093AB40 fills one slot with character/costume/portrait
    // data before the team gets committed into BattleParam592.
    struct RuntimeMember112
    {
        uint64_t value0 = 0;                 // +0  character/runtime value
        uint64_t value8 = 0;                 // +8  character/runtime value
        int value16 = 0;                     // +16 character/runtime value
        uint8_t flag20 = 1;                  // +20 enabled/valid flag
        uint8_t pad21[3]{};
        uint64_t value24 = 0;                // +24 character/runtime value
        uint64_t value32 = 0;                // +32 character/runtime value
        uint64_t value40 = UINT64_MAX;       // +40 sentinel -1
        uint64_t value48 = 0;                // +48 character/runtime value
        uint64_t value56 = 0;                // +56 character/runtime value
        int value64 = 1;                     // +64 default flag/value
        uint8_t pad68[4]{};
        RuntimeMemberOptions40 options;      // +72 small options/default block
    };

    static_assert(sizeof(RuntimeMember112) == 112, "Runtime member must stay 112 bytes");

    // 592-byte battle/team parameter object. The game constructs this with
    // sub_1400D0BF0, initializes defaults with sub_14093A8B0, copies it with
    // sub_1400D1380, and serializes/copies it with sub_1400DC060.
    // Layout is 3 RuntimeMember112 entries followed by team/battle metadata.
    struct BattleParam592
    {
        RuntimeMember112 members[3]; // +0 leader/support1/support2
        uint8_t metadata[256];       // +336 through +591 team/battle metadata
    };

    static_assert(sizeof(BattleParam592) == 592, "Battle param block must stay 592 bytes");

    // 224-byte native message dialog object. sub_140763340 constructs it.
    // It derives from ccUiFlash, has a task pointer at +80, stores the movie
    // key string at +88, the SWF name at +112, target path at +168, and several
    // task/status fields from +200 onward.
    struct DialogObject224
    {
        uint8_t raw[224];
    };

    static_assert(sizeof(DialogObject224) == 224, "Dialog object allocation size must stay 224 bytes");
}
