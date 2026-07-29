#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace CharacterSelectResearch
{
    struct SymbolInfo
    {
        const char* Name;
        uintptr_t Rva;
        const char* CurrentName;
        const char* Notes;
    };

    struct DataLayoutInfo
    {
        const char* Name;
        uintptr_t Rva;
        int EntrySize;
        int CountHint;
        const char* Notes;
    };

    struct TeamPresetMember20
    {
        int CharacterId;
        int PresetOrCostumeIndex;
        int Param2;
        int Param3;
        int Param4;
    };

    struct RuntimeMember112Known
    {
        int CharacterDbId;
        int CharacterVariantId;
        int PresetParam1;
        int CostumeResolved;
        unsigned char ColorResolved;
        int PortraitMain;
        int PortraitSupport;
    };

    bool Init(uintptr_t gameBase);
    void Shutdown();
    uintptr_t Base();

    const std::vector<SymbolInfo>& Symbols();
    const std::vector<DataLayoutInfo>& DataLayouts();

    const char* SymbolName(uintptr_t rva);
    void LogResearchMap();
    void DumpNotesToLog();

    bool IsEnabled();
    void SetEnabled(bool enabled);

    int SelectedPresetIndex();
    void SetSelectedPresetIndex(int index);

    bool ClassicSelectOverlayEnabled();
    void SetClassicSelectOverlayEnabled(bool enabled);

    bool LogPresetChanges();
    void SetLogPresetChanges(bool enabled);

    bool LogCustomizePackets();
    void SetLogCustomizePackets(bool enabled);
}
