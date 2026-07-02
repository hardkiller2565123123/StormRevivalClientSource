#include "StdInc.h"
#include "EngineXfbinRuntime.h"
#include "EngineAddressMap.h"
#include "RuntimeAssetTelemetry.h"
#include "Logger.h"

namespace
{
    std::atomic<bool> g_EnableUnsafeEngineCalls{ false };
    std::mutex g_StatusMutex;
    std::string g_LastStatus = "Runtime engine calls disabled. Asset browser and static inspectors are safe.";

    void SetStatus(const std::string& text)
    {
        std::lock_guard<std::mutex> lock(g_StatusMutex);
        g_LastStatus = text;
        Logger::Info(std::string("EngineXfbinRuntime: ") + text);
    }

    template <typename T>
    T Fn(uintptr_t idaAddress)
    {
        return reinterpret_cast<T>(EngineAddressMap::Rebase(idaAddress));
    }

    EngineXfbinRuntime::ChunkNameQuery MakeQuery(const char* chunkName, bool useGameHash)
    {
        EngineXfbinRuntime::ChunkNameQuery q{};
        if (chunkName && chunkName[0])
        {
            if (useGameHash)
            {
                using HashNameFn = uint32_t(__fastcall*)(const char*);
                q.Hash = Fn<HashNameFn>(0x140684D80)(chunkName);
            }
            else
            {
                q.Hash = EngineAddressMap::HashChunkName(chunkName);
            }
            q.HasName = true;
            q.Name = chunkName;
        }
        return q;
    }

}

namespace EngineXfbinRuntime
{
    bool IsUnsafeEngineCallsEnabled()
    {
        return g_EnableUnsafeEngineCalls.load();
    }

    void SetUnsafeEngineCallsEnabled(bool enabled)
    {
        g_EnableUnsafeEngineCalls.store(enabled);
        SetStatus(enabled
            ? "Unsafe engine calls enabled by user. Use only in a live test build with matching EXE."
            : "Unsafe engine calls disabled.");
    }

    void* GetLoadedXfbin(const char* virtualPath)
    {
        if (!virtualPath || !virtualPath[0])
        {
            SetStatus("GetLoadedXfbin skipped: empty path.");
            return nullptr;
        }

        RuntimeAssetTelemetry::Push(RuntimeAssetTelemetry::EventType::Xfbin, "GetLoadedXfbin", virtualPath);

        if (!IsUnsafeEngineCallsEnabled())
        {
            SetStatus(std::string("Logged XFBIN lookup only: ") + virtualPath);
            return nullptr;
        }

        using GetLoadedXfbinFn = void* (__fastcall*)(const char*, int);
        auto fn = Fn<GetLoadedXfbinFn>(0x140740D30);
        void* result = fn(virtualPath, 0);
        SetStatus(std::string("GetLoadedXfbin called: ") + virtualPath + (result ? " -> ok" : " -> null"));
        return result;
    }

    void ReleaseLoadedXfbin(const char* virtualPath, int reason)
    {
        if (!virtualPath || !virtualPath[0])
            return;

        RuntimeAssetTelemetry::Push(RuntimeAssetTelemetry::EventType::Xfbin, "ReleaseLoadedXfbin", virtualPath);

        if (!IsUnsafeEngineCallsEnabled())
        {
            SetStatus(std::string("Release skipped because unsafe calls are disabled: ") + virtualPath);
            return;
        }

        using ReleaseFn = void(__fastcall*)(uintptr_t, const char*, int);
        auto fn = Fn<ReleaseFn>(0x140774030);
        fn(EngineAddressMap::Rebase(0x140C7BE10), virtualPath, reason);
        SetStatus(std::string("ReleaseLoadedXfbin called: ") + virtualPath);
    }

    void* FindChunkInLoadedXfbin(const char* virtualPath, uintptr_t chunkTypeIda, const char* chunkName, int releaseReason)
    {
        if (!virtualPath || !virtualPath[0] || !chunkTypeIda)
        {
            SetStatus("FindChunkInLoadedXfbin skipped: path or type missing.");
            return nullptr;
        }

        RuntimeAssetTelemetry::Push(RuntimeAssetTelemetry::EventType::Xfbin, "FindChunkInLoadedXfbin", virtualPath);

        if (!IsUnsafeEngineCallsEnabled())
        {
            SetStatus(std::string("Logged chunk query only: ") + virtualPath + " / " + (chunkName ? chunkName : "<any>"));
            return nullptr;
        }

        ChunkNameQuery query = MakeQuery(chunkName, true);
        using FindChunkFn = void* (__fastcall*)(const char*, ChunkNameQuery*, int, uintptr_t);
        auto fn = Fn<FindChunkFn>(0x140740D80);
        void* result = fn(virtualPath, &query, releaseReason, EngineAddressMap::Rebase(chunkTypeIda));
        SetStatus(std::string("FindChunkInLoadedXfbin called: ") + virtualPath + (result ? " -> ok" : " -> null"));
        return result;
    }

    bool HasChunkInLoadedXfbin(const char* virtualPath, uintptr_t chunkTypeIda, const char* chunkName, int releaseReason)
    {
        if (!virtualPath || !virtualPath[0] || !chunkTypeIda)
            return false;

        if (!IsUnsafeEngineCallsEnabled())
        {
            RuntimeAssetTelemetry::Push(RuntimeAssetTelemetry::EventType::Xfbin, "HasChunkInLoadedXfbin", virtualPath);
            SetStatus(std::string("Logged has-chunk query only: ") + virtualPath);
            return false;
        }

        ChunkNameQuery query = MakeQuery(chunkName, true);
        using HasChunkFn = bool(__fastcall*)(const char*, ChunkNameQuery*, int, uintptr_t);
        auto fn = Fn<HasChunkFn>(0x140740E00);
        bool result = fn(virtualPath, &query, releaseReason, EngineAddressMap::Rebase(chunkTypeIda));
        SetStatus(std::string("HasChunkInLoadedXfbin called: ") + virtualPath + (result ? " -> yes" : " -> no"));
        return result;
    }

    std::string LastStatus()
    {
        std::lock_guard<std::mutex> lock(g_StatusMutex);
        return g_LastStatus;
    }

    std::string BuildCapabilityText()
    {
        std::ostringstream out;
        out << "Current safe capabilities:\n";
        out << "- Scan game/mod folders and index CPK/XFBIN paths.\n";
        out << "- Inspect XFBIN files statically from disk.\n";
        out << "- Show model/texture/material/string references from assets.\n";
        out << "- Log planned runtime XFBIN/chunk queries without touching game memory.\n";
        out << "- Keep real engine wrappers compiled but disabled until signatures are verified.\n\n";
        out << "Next blocked feature: true blank-world spawning needs the scene graph registration and transform writer.";
        return out.str();
    }
}
