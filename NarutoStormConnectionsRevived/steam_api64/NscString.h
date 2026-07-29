#pragma once

#include <cstdint>
#include <cstring>

namespace NscStringUtil
{
    // Native small-string object used by Storm Connections UI/runtime code.
    // The game initializes this with sub_1400B7D70 and destroys it with
    // sub_1400B1700. It behaves like a small-string-optimized std::string:
    // text shorter than 16 bytes lives inline at +24, larger text is heap
    // allocated and the pointer is stored at +24.
    struct String56
    {
        uint64_t vtableOrAllocator = 0;  // +0  native string allocator/vtable cookie
        uint64_t allocatorState = 0;     // +8  allocator state used by nuccStlAllocator
        uint64_t reserved16 = 0;         // +16 native reserved field
        union                         // +24 inline text or heap pointer
        {
            char inlineText[16];
            char* heapText;
        } storage{};
        uint64_t length = 0;             // +40 current string length
        uint64_t capacity = 15;          // +48 < 0x10 means inline storage
    };

    static_assert(sizeof(String56) == 56, "NSC string object must stay 56 bytes");

    // Returns the readable character pointer from a native String56.
    // Mirrors the game's repeated pattern:
    //   ptr = object + 24;
    //   if (capacity >= 0x10) ptr = *(char**)(object + 24);
    inline const char* CStr(const String56& text)
    {
        return text.capacity >= 0x10 ? text.storage.heapText : text.storage.inlineText;
    }

    inline char* CStr(String56& text)
    {
        return text.capacity >= 0x10 ? text.storage.heapText : text.storage.inlineText;
    }

    // Lightweight local initializer for fresh local buffers. This does not set
    // the exact native allocator cookie, so only use it for helper/debug memory
    // that will not be passed into native destructors. Native game-owned strings
    // should still be constructed by sub_1400B7D70.
    inline void InitLocal(String56& text)
    {
        std::memset(&text, 0, sizeof(text));
        text.capacity = 15;
        text.storage.inlineText[0] = '\0';
    }
}

// Reverse map for the native string helpers we have now fully identified:
//
// sub_1400B7D70  - constructs a native 56-byte small string.
// sub_1400B1700  - destroys/resets a native 56-byte small string.
// sub_1400B1B00  - assigns raw text into a native string.
// sub_1400B3830  - appends raw text to a native string.
// sub_1400B6920  - copy-constructs one native string from another.
