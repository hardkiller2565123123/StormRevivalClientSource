#pragma once

namespace EngineRuntimeResearch
{
    struct RuntimeSymbol
    {
        const char* Address;
        const char* Name;
        const char* Purpose;
        const char* Risk;
    };

    const RuntimeSymbol* RuntimeModelSymbols(int* count);
    const RuntimeSymbol* RenderGraphSymbols(int* count);
    const RuntimeSymbol* SceneOwnerTargets(int* count);
    const RuntimeSymbol* CurrentCapabilities(int* count);
    const char* NextSub();
    const char* NextSubReason();
}
