#ifndef OFFSETS_H
#define OFFSETS_H

#include <cstdint>
#include <vector>

// IDA string-anchor exports from the Storm 4 executable are kept in:
//   IdaOffsets/Storm4IdaOffsetUsageGuide.h
//   IdaOffsets/Storm4IdaStringOffsets_Actionable.h
//   IdaOffsets/Storm4IdaStringOffsets_All.h
//
// Those generated files preserve the full IDA dump and group useful anchors by
// system. They are search/reference material: convert a string VA to an RVA,
// follow xrefs in IDA, then build a pattern-scanned runtime patch here.

namespace offsetSC
{
    extern const uintptr_t stageOffset;
    extern const uintptr_t VTableXmmwordOffset;
    extern const uintptr_t bgmOffset;
    extern const uintptr_t OFFSET_TEAM_ULT_ARRAY;
    extern const int ORIGINAL_COUNT_TEAM_ULT_ARRAY;
    extern const uintptr_t OFF_STRINGS_ARRAY;
    extern const uintptr_t OFF_BGMARRAY;
    extern const uintptr_t OFF_PROJECTILEARRAY;
    extern const uintptr_t OFF_CHARRELATIONARRAY;
    extern const uintptr_t OFF_SCENEARRAY;
}

namespace offsetS4
{
    extern const uintptr_t stageOffset;
    extern const uintptr_t VTableXmmwordOffset;
    extern const uintptr_t bgmOffset;
    extern const uintptr_t OFFSET_TEAM_ULT_ARRAY;
    extern const int ORIGINAL_COUNT_TEAM_ULT_ARRAY;
    extern const uintptr_t OFF_BGMARRAY;
    extern const uintptr_t OFF_PROJECTILEARRAY;
    extern const uintptr_t OFF_CHARRELATIONARRAY;
    extern const uintptr_t OFF_SCENEARRAY;
}

class Offset
{
public:
    static bool WriteFloatAtIndexSafe(uintptr_t baseAddr, size_t index, float value);
    static uintptr_t ResolvePointerChainBase(uintptr_t moduleBase, uintptr_t baseOffset, const std::vector<uint32_t>& offsets);
    static bool TryResolveOrder(uintptr_t moduleBase, uintptr_t baseOffset, const std::vector<uint32_t>& offsets, uintptr_t& outLastAddr, uintptr_t& outCur);
    static bool SafeWriteFloat(uintptr_t addr, float value);
    static bool SafeReadFloat(uintptr_t addr, float& out);
    static bool SafeReadPtr(uintptr_t addr, uintptr_t& out);
};

#endif // OFFSETS_H
