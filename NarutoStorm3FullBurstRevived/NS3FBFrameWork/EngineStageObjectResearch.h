#pragma once

namespace EngineStageObjectResearch
{
    struct StageSymbol
    {
        const char* Address;
        const char* Name;
        const char* Purpose;
        const char* Risk;
    };

    const StageSymbol* GameplayLoaders(int* count);
    const StageSymbol* StageObjectPipeline(int* count);
    const StageSymbol* ReplacementPipeline(int* count);
    const StageSymbol* NextTargets(int* count);

    const char* NextSub();
    const char* NextSubReason();
}
