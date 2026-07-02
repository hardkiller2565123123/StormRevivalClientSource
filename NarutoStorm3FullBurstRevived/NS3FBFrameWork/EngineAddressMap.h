#pragma once
#include "StdInc.h"

namespace EngineAddressMap
{
    enum class AddressKind
    {
        Function,
        VTableOrType,
        Global,
        String,
        Unknown
    };

    enum class SafetyLevel
    {
        InfoOnly,
        WrapperReady,
        HookCandidate,
        UnsafeUntilSignatureVerified
    };

    struct KnownAddress
    {
        const char* Name;
        uintptr_t IdaAddress;
        AddressKind Kind;
        SafetyLevel Safety;
        const char* Notes;
    };

    struct KnownChunkType
    {
        const char* ChunkName;
        uintptr_t TypeObjectIda;
        uintptr_t RegisterFunctionIda;
        uintptr_t FactoryFunctionIda;
        const char* Notes;
    };

    uintptr_t ModuleBase();
    uintptr_t Rebase(uintptr_t idaAddress);
    uint32_t HashChunkName(const char* text);
    uint32_t HashChunkTypeName(const char* text);

    const std::vector<KnownAddress>& KnownAddresses();
    const std::vector<KnownChunkType>& KnownChunkTypes();
    const KnownAddress* FindByName(const std::string& name);
    std::string FormatAddress(uintptr_t value);
    const char* KindName(AddressKind kind);
    const char* SafetyName(SafetyLevel safety);
}
