#include <cstdint>
#include <cstring>
#include <windows.h>

#pragma pack(push,1)
struct SceneEntry {
    uint32_t id;                   // 0x00
    uint8_t  pad0[4];              // 0x04..0x07
    uint64_t start_func_ptr;       // 0x08
    char     name[0x90 - 0x10];    // 0x10 .. 0x8F
};
static_assert(sizeof(SceneEntry) == 0x90, "SceneEntry size mismatch");
#pragma pack(pop)