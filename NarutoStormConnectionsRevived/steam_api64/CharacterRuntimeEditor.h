#pragma once

#include <cstdint>
#include <vector>

namespace CharacterRuntimeEditor
{
    struct RuntimeEditorOptions
    {
        bool Enabled = true;
        bool F2OpensEditor = true;
        bool LogCharacterLookup = true;
        bool LogNameBuilder = true;
        bool LogBattleParamBuild = true;
        bool LogBattleParamCopy = false;
        bool LogBattleTableUpdate = true;
        bool LogTeamCustomizeVector = true;
        bool ClassicStormMode = false;
        bool RuntimePresetEditor = false;
        bool RuntimeNameOverride = false;
        bool RuntimePortraitOverride = false;
        bool RuntimeCostumeOverride = false;
        bool SafeModeNoMemoryWrites = true;
    };

    struct RuntimeOverrideState
    {
        int ForcedPreset = -1;
        int ForcedLeaderCharacter = -1;
        int ForcedSupport1Character = -1;
        int ForcedSupport2Character = -1;
        int ForcedCostume = -1;
        int ForcedColor = -1;
        int ForcedMainPortrait = -1;
        int ForcedSupportPortrait = -1;

        int SelectedPlayerSlot = 0;
        int PreviewCharacterId = -1;
        int PreviewCostumeId = -1;
        int PreviewColorId = -1;
        int PreviewVariantId = 0;
        int PreviewEffectId = -1;
        int PreviewFaceId = -1;
        int PreviewPairSkillId = -1;
        char CostumeNameOverride[64] = {};
        bool PendingApply = false;
        bool LastApplyBlockedBySafeMode = false;
        bool ForcePreviewReload = false;

        int BattleSlot = 0;
        int BattleCharacterId = -1;
        int BattleCostumeId = 0;
        int BattleCharaCode = 0;
        int BattleVariantId = 0;
        int BattleModelMode = 0;
        int BattleModelState = 0;
        bool WriteBattleSelectParam = true;
        bool ApplyNetMenuModel = true;
        bool BattleApplyPending = false;
        bool BattleApplyOk = false;
        bool BattleApplyBlockedBySafeMode = false;
        char LastBattleApplyMessage[160] = {};
    };

    struct FunctionMapEntry
    {
        const char* Name;
        uintptr_t Rva;
        const char* IdaName;
        const char* Description;
        const char* HookUse;
    };

    bool Init(uintptr_t gameBase);
    void Shutdown();
    uintptr_t Base();

    RuntimeEditorOptions& Options();
    RuntimeOverrideState& Overrides();

    const std::vector<FunctionMapEntry>& FunctionMap();
    void LogMap();
    void LogRuntimeSummary();
    void ResetOverrides();
    void ApplyOverrides();
    void ApplyBattleModelTest();
    void ReadCurrentSelectionScaffold();

    const char* RuntimePipelineSummary();
}
