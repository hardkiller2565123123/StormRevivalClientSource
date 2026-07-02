#pragma once
#include "StdInc.h"

namespace EngineXfbinRuntime
{
    struct ChunkNameQuery
    {
        uint32_t Hash = 0;
        bool HasName = false;
        const char* Name = nullptr;
        uint64_t Reserved = 0;
    };

    bool IsUnsafeEngineCallsEnabled();
    void SetUnsafeEngineCallsEnabled(bool enabled);

    void* GetLoadedXfbin(const char* virtualPath);
    void ReleaseLoadedXfbin(const char* virtualPath, int reason);
    void* FindChunkInLoadedXfbin(const char* virtualPath, uintptr_t chunkTypeIda, const char* chunkName, int releaseReason);
    bool HasChunkInLoadedXfbin(const char* virtualPath, uintptr_t chunkTypeIda, const char* chunkName, int releaseReason);

    std::string LastStatus();
    std::string BuildCapabilityText();
}
