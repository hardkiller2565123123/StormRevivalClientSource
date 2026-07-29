#include "StdInc.h"
#include "CharacterSelectResearch.h"
#include "Logger.h"

#include <sstream>
#include <iomanip>

namespace
{
    uintptr_t g_Base = 0;
    bool g_Enabled = true;
    bool g_ClassicSelectOverlay = false;
    bool g_LogPresetChanges = true;
    bool g_LogCustomizePackets = true;
    int g_SelectedPresetIndex = 0;

    const std::vector<CharacterSelectResearch::SymbolInfo> g_Symbols =
    {
        { "LoadPresetByCategorySlot", 0x0D5200, "sub_1400D5200", "Loads gTeamPresetDatabase[category][slot], builds 3x runtime members, updates CutInMng and battle cache." },
        { "UpdateTeamPreviewPanel", 0x0D55D0, "sub_1400D55D0", "Reads leader/support IDs from a team preset and pushes preview UI for leader, support left, support right." },
        { "SetLeaderIconFlash", 0x7D6400, "sub_1407D6400", "Calls Scaleform SetLeaderIcon(iconPath, iconId) for the team preview panel." },
        { "SetSupport1IconFlash", 0x7D6AB0, "sub_1407D6AB0", "Calls Scaleform SetSupport1Icon(iconPath, iconId). Can be suppressed for no-player-icons mode." },
        { "SetSupport2IconFlash", 0x7D6BF0, "sub_1407D6BF0", "Calls Scaleform SetSupport2Icon(iconPath, iconId). Can be suppressed for no-player-icons mode." },
        { "SelectPreset", 0x0ED4C0, "sub_1400ED4C0", "Main team preset change path. Copies 448-byte team, rebuilds runtime data, refreshes UI, sends customize data." },
        { "ResetCharacterSelect", 0x0FCFD0, "sub_1400FCFD0", "Character select init/reset. Loads current preset, rebuilds runtime cache, refreshes Flash SetCharacter." },
        { "EndlessLobbyLoadDefaultTeam", 0x0FB5B0, "sub_1400FB5B0", "Endless lobby state path. Loads default team if missing, rebuilds runtime data and network sync." },
        { "StartFreeBattlePreviewA", 0x16E5E0, "sub_14016E5E0", "Pre-battle preview path. Loads current team and applies leader/support customize data to preview scene." },
        { "StartFreeBattlePreviewB", 0x16EBB0, "sub_14016EBB0", "Alternate pre-battle preview path. Same team-to-preview pipeline with cleanup differences." },
        { "StartFreeBattlePreviewC", 0x16F0E0, "sub_14016F0E0", "Another preview/transition path using current default team and runtime customize data." },
        { "BuildFlashSetCharacter", 0x17CC00, "sub_14017CC00", "Builds six Scaleform args and calls SetCharacter on the character select Flash movie." },
        { "SetMenuKeyHelp", 0x17CBE0, "sub_14017CBE0", "Calls setMenuKeyHelp on Flash after character select is refreshed." },
        { "UpdateSelectPresetList", 0x17E6F0, "sub_14017E6F0", "Refreshes preset/costume list after selected team preset changes." },
        { "SetActivePresetCursor", 0x17DA00, "sub_14017DA00", "Likely updates cursor/default preset display for character select." },
        { "RefreshPreviewQueue", 0x0EC9A0, "sub_1400EC9A0", "Maintains character preview/load queue after runtime team data changes." },
        { "CopyRuntimeTeam", 0x0D1380, "sub_1400D1380", "Copies a full runtime team/customize block to another cache." },
        { "InitRuntimeCustomizeBlock", 0x93A8B0, "sub_14093A8B0", "Initializes 3 member runtime customize block plus many defaults." },
        { "FindCharacterById", 0x857560, "sub_140857560", "Walks character database tree and returns character info for a character ID." },
        { "FindCharacterVariant", 0x8576D0, "sub_1408576D0", "Related character lookup using character/variant info." },
        { "ResolveCharacterIdFromRuntime", 0x8572C0, "sub_1408572C0", "Resolves runtime member fields back to character index for customization tables." },
        { "ResolvePortraitAsset", 0x175FB0, "sub_140175FB0", "Resolves main/support portrait/icon asset IDs from character data." },
        { "ResolveCostumeIndex", 0x528C10, "sub_140528C10", "Converts costume table value into runtime costume index." },
        { "ResolveColorIndex", 0x528CE0, "sub_140528CE0", "Converts costume color table value into runtime color index." },
        { "SendCustomizeData", 0x615A80, "sub_140615A80", "Builds and sends one team customize packet. Log string: ccNetCommunicateUserInfo::SendCustomizeData." },
        { "SendCustomizeDataCurrent", 0x6160B0, "sub_1406160B0", "Builds and sends current team customize packet from lobby/current preset." },
        { "SendCustomizeDataList", 0x6166F0, "sub_1406166F0", "Builds and sends list of up to 8 team customize presets. Log string: SendCustomizeDataList." },
        { "FindManagerByName", 0x1086E40, "sub_141086E40", "Global manager registry lookup. Used for CutInMng." },
        { "CharacterCustomizeDatabaseInit", 0x0739E0, "sub_1400739E0", "Initializes gCharacterCustomizeDatabase / unk_1421A0310 at boot." },
        { "CopyCharacterInfoById", 0x857B90, "sub_140857B90", "Copies a 64-byte character info record from FindCharacterById into an output buffer." },
        { "SupportUiRefreshThunk", 0x0F8B40, "sub_1400F8B40", "Refreshes support UI if its Flash object exists." },
        { "NetMatchInfoRefreshTask", 0x10E4C0, "sub_14010E4C0", "Queues a ccUiFlashNetMatchInfo task with mode 6 and current parameter." },
        { "CharacterSelectCustomizeSender", 0x6160B0, "sub_1406160B0", "Current-team SendCustomizeData path. Builds three 28-byte CustomizeData entries from gCharacterCustomizeDatabase." },
        { "CharacterNameAssetLookup", 0x58D8A0, "sub_14058D8A0", "Used by SetCharacter builder to resolve display strings from character id/variant." },
        { "CustomizationDtor", 0x527CF0, "sub_140527CF0", "Resets customize object vtable; cleanup helper for SendCustomizeData stack objects." },
        { "CutInCostumeValue", 0x594E10, "sub_140594E10", "Returns *(entry+104). Used by ResolveCostumeIndex." },
        { "CutInColorValue", 0x596E80, "sub_140596E80", "Returns *(entry+96). Used by ResolveColorIndex." },
        { "FindCharacterByNameHash", 0x8575E0, "sub_1408575E0", "Hashes internal character name and returns CharacterInfo from character DB tree." },
        { "BuildLocalizedDisplayName", 0x0B1C30, "sub_1400B1C30", "Builds localized display name string using character DB, localizer, and fallback name path." },
        { "BuildCharacterSlot112", 0x93AB40, "sub_14093AB40", "Builds one 112-byte runtime character slot; fills character, variant, portrait main/support, costume/color fields." },
        { "CommitTeamSlotMetadata", 0x93ABD0, "sub_14093ABD0", "Commits final team metadata at offsets +476/+480/+336 after 3 slots are built." },
        { "TeamCustomizeVectorAdd", 0x827B90, "sub_140827B90", "Dedupes and appends an 88-byte team customize entry to a runtime vector." },
        { "BattleParamCtor592", 0x0D0BF0, "sub_1400D0BF0", "Constructs 592-byte battle parameter/team customize object." },
        { "SerializeBattleParam", 0x0DC060, "sub_1400DC060", "Serializes/copies battle parameter data for local table/network use." },
        { "LocalBattleTableUpdate", 0x611F70, "sub_140611F70", "Writes uid/status/BattleParam into a local battle table slot and logs team ids." },
        { "LobbySignalSend", 0x0F1F80, "sub_1400F1F80", "Sends a 16-byte lobby signal packet with type/status fields." },
        { "LocalBattleRegister", 0x0EC260, "sub_1400EC260", "Registers local battle table data, serializes team, then refreshes table." },
        { "RegisterOnTablePacket", 0x0F1550, "sub_1400F1550", "Sends a 608-byte RegisterOnTable packet for Endless/lobby battle table." },
        { "StoreBattleParamByPlayer", 0x6122F0, "sub_1406122F0", "Stores a copied BattleParam in a tree keyed by player id." },
        { "BuildCurrentTeamCustomize", 0x611A50, "sub_140611A50", "Builds current leader/support customize entries from preset + character customize database." },
        { "PopupInvokeCallback", 0xBE4010, "sub_140BE4010", "Invokes bool/Scaleform callback object for popup/select UI entries." },
        { "UiTaskQueuePush", 0x10F250, "sub_14010F250", "Pushes a UI callback/task into a ring/queue." },
    };

    const std::vector<CharacterSelectResearch::DataLayoutInfo> g_DataLayouts =
    {
        { "gTeamPresetDatabase", 0x2221B40, 448, 24, "unk_142221B40. Master team preset database. category*3584 + slot*448, where 3584 = 8 presets * 448." },
        { "gTeamPresetLockOrHeader", 0x2221B38, 8, 1, "unk_142221B38. Used with sub_1409110D0 before preset copy." },
        { "gCurrentTeamPresetIndex", 0x2224540, 4, 1, "dword_142224540. Current/default selected team preset index." },
        { "gCharacterCostumeDatabase", 0x2224550, 28, -1, "unk_142224550. Accessed as 120*character + 28*costume. Feeds ResolveCostumeIndex/ResolveColorIndex." },
        { "gCharacterCustomizeDatabase", 0x21A0310, 120, -1, "unk_1421A0310. Character customize/display table. Accessed as 120*character + 541248 + 28*color." },
        { "gBattleRuntimeTeamCache", 0x218F7C0, -1, 1, "qword_14218F7C0. Runtime battle team cache. +16 and +1200 hold mirrored team data." },
        { "gGameDataRoot", 0x219D7E0, -1, 1, "qword_14219D7E0. +304 character DB, +456 portrait/icon resolver input." },
        { "gCutInRuntimeStorage", 0x219D818, -1, 1, "qword_14219D818. Runtime cut-in/color slots around +1252592." },
        { "gOnlineLobbyRoot", 0x2188D20, -1, 1, "qword_142188D20. Online/lobby owner. +256 local user/session customize state." },
        { "CharacterInfoResolved64", 0, 64, -1, "Output of sub_140857B90. Safe empty block uses -1 sentinels at +8 and +24." },
        { "CharacterNameRow40", 0, 40, -1, "Rows walked by sub_14058D8A0: uid, variation, name pointer at +8." },
        { "BattleParam592", 0, 592, -1, "3 x 112-byte runtime members plus trailing team/battle metadata. Copied by sub_1400D1380." },
        { "TeamCustomizeVectorEntry88", 0, 88, -1, "Deduped/appended by sub_140827B90." },
    };

    std::string Hex(uintptr_t value)
    {
        std::ostringstream ss;
        ss << "0x" << std::hex << std::uppercase << value;
        return ss.str();
    }
}

namespace CharacterSelectResearch
{
    bool Init(uintptr_t gameBase)
    {
        g_Base = gameBase;
        Logger::Info("CharacterSelectResearch initialized base=" + Hex(g_Base));
        return g_Base != 0;
    }

    void Shutdown()
    {
        g_Base = 0;
        Logger::Info("CharacterSelectResearch shutdown");
    }

    uintptr_t Base()
    {
        return g_Base;
    }

    const std::vector<SymbolInfo>& Symbols()
    {
        return g_Symbols;
    }

    const std::vector<DataLayoutInfo>& DataLayouts()
    {
        return g_DataLayouts;
    }

    const char* SymbolName(uintptr_t rva)
    {
        for (const auto& symbol : g_Symbols)
        {
            if (symbol.Rva == rva)
                return symbol.Name;
        }
        return "Unknown";
    }

    void LogResearchMap()
    {
        Logger::Info("=== Character Select Reverse Map ===");
        for (const auto& symbol : g_Symbols)
        {
            Logger::Info(std::string(symbol.Name) + " rva=" + Hex(symbol.Rva) + " original=" + symbol.CurrentName + " note=" + symbol.Notes);
        }
        Logger::Info("=== Character Select Data Layouts ===");
        for (const auto& layout : g_DataLayouts)
        {
            Logger::Info(std::string(layout.Name) + " rva=" + Hex(layout.Rva) + " entrySize=" + std::to_string(layout.EntrySize) + " note=" + layout.Notes);
        }
    }

    void DumpNotesToLog()
    {
        Logger::Info("Team preset member appears to be 20 bytes: characterId, costume/preset index, and three unknown params.");
        Logger::Info("Full team preset is 448 bytes. First 60 bytes contain 3 member entries. Remaining bytes are team metadata/customization extras.");
        Logger::Info("Runtime team member block is 112 bytes. Three members form a 336-byte runtime team, then extra defaults/settings follow.");
        Logger::Info("Customize packet uses 28-byte CharacterCustomize entries pulled from gCharacterCustomizeDatabase by character/color.");
        Logger::Info("SetLeaderIcon, SetSupport1Icon, and SetSupport2Icon are direct Scaleform methods and can be runtime-suppressed from HookText.");
        Logger::Info("sub_14017DA00 copies all static 448-byte preset pages into the character select UI object, ending with CurrentPreset at +10776.");
    }

    bool IsEnabled() { return g_Enabled; }
    void SetEnabled(bool enabled) { g_Enabled = enabled; }

    int SelectedPresetIndex() { return g_SelectedPresetIndex; }
    void SetSelectedPresetIndex(int index) { g_SelectedPresetIndex = index; }

    bool ClassicSelectOverlayEnabled() { return g_ClassicSelectOverlay; }
    void SetClassicSelectOverlayEnabled(bool enabled) { g_ClassicSelectOverlay = enabled; }

    bool LogPresetChanges() { return g_LogPresetChanges; }
    void SetLogPresetChanges(bool enabled) { g_LogPresetChanges = enabled; }

    bool LogCustomizePackets() { return g_LogCustomizePackets; }
    void SetLogCustomizePackets(bool enabled) { g_LogCustomizePackets = enabled; }
}
