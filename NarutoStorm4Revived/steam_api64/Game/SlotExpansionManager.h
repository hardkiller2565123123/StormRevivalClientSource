#pragma once

struct SlotExpansionConfig
{
    bool AutoApplyRuntime;
    bool EnableStageSceneRuntime;
    bool EnableCharacterRosterRuntime;
    int AutoApplyDelayMs;
    int ExtraCharacterSlots;
    int ExtraCostumeSlots;
    int ExtraStageSlots;
    int ExtraSceneSlots;
    int ExtraBgmSlots;
    int ExtraProjectileSlots;
    int ExtraPartnerSlots;
    int ExtraTeamUltimateSlots;
    int ExtraConditionSlots;
    int ExtraCharRelationSlots;
};

namespace SlotExpansionManager
{
    void Init();
    const SlotExpansionConfig& GetConfig();
    SlotExpansionConfig& MutableConfig();
    void ResetDefaults();
    bool Load();
    bool Save();
    void ApplyRuntimeExpansions();
    bool ApplyStageExpansion();
    bool StageExpansionRequested();
    bool StageExpansionApplied();
    const char* LastStatus();
}
