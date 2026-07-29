#include "StdInc.h"
#include "CharacterRuntimeEditor.h"
#include "Logger.h"

#include <sstream>
#include <string>

namespace
{
    uintptr_t g_Base = 0;
    CharacterRuntimeEditor::RuntimeEditorOptions g_Options{};
    CharacterRuntimeEditor::RuntimeOverrideState g_Overrides{};

    const std::vector<CharacterRuntimeEditor::FunctionMapEntry> g_FunctionMap =
    {
        { "FindCharacterById",          0x857560, "sub_140857560", "Looks up a CharacterInfo by numeric character id from the character manager tree.", "Log/look up ids, randomizer, safe character validation." },
        { "FindCharacterByNameHash",    0x8575E0, "sub_1408575E0", "Hashes an internal character name and returns the matching CharacterInfo.", "Name based lookup, custom/mod character aliases." },
        { "FindCharacterVariant",       0x8576D0, "sub_1408576D0", "Finds a CharacterInfo by character id and variation/costume id.", "Runtime costume swap and old-game costume mapping." },
        { "ResolveCharacterInfo64",     0x857B90, "sub_140857B90", "Copies a 64-byte character info block or writes a safe empty/default block.", "Portrait/icon/voice resolver hook." },
        { "FindInternalName",           0x58D8A0, "sub_14058D8A0", "Finds a 40-byte character database row by uid + variation and returns its internal name pointer.", "Runtime display names and classic name packs." },
        { "BuildLocalizedName",         0x0B1C30, "sub_1400B1C30", "Builds the localized display name string for character select.", "Rename characters, classic names, mod names." },
        { "ResolvePortraitId",          0x175FB0, "sub_140175FB0", "Resolves main/support portrait ids from character id, role, and variation.", "Portrait replacement and support icon override." },
        { "ResolveCostumeIndex",        0x528C10, "sub_140528C10", "Converts costume database value into runtime costume index.", "Runtime costume override." },
        { "ResolveColorIndex",          0x528CE0, "sub_140528CE0", "Converts color database value into runtime color index.", "Runtime color override." },
        { "SetCharacterFlash",          0x17CC00, "sub_14017CC00", "Builds six Scaleform args and calls SetCharacter for the current preset/team.", "Classic select bridge and SetCharacter logger." },
        { "SetMenuKeyHelp",             0x17CBE0, "sub_14017CBE0", "Calls setMenuKeyHelp on the character select Flash movie.", "Classic UI button-help replacement." },
        { "CopyPresetPagesToUi",        0x17DA00, "sub_14017DA00", "Copies every 448-byte preset page into the character select UI object and writes current preset at +10776.", "Preset dumper/editor starting point." },
        { "BuildCharacterSlot112",      0x93AB40, "sub_14093AB40", "Builds one 112-byte runtime character slot and resolves main/support portrait ids.", "Runtime team editor and icon overrides." },
        { "CommitTeamSlots",            0x93ABD0, "sub_14093ABD0", "Commits final team slot metadata/camera/transition values.", "Final stage before UI/battle parameter use." },
        { "BattleParamCtor592",         0x0D0BF0, "sub_1400D0BF0", "Constructs the 592-byte battle/team parameter object with 3 x 112-byte members.", "Team preset import/export." },
        { "CopyBattleParam592",         0x0D1380, "sub_1400D1380", "Copies the 592-byte battle/team parameter object.", "Safe copy point for custom teams." },
        { "SerializeBattleParam",       0x0DC060, "sub_1400DC060", "Serializes/copies battle parameter data for packets or table registration.", "Packet-side team editor." },
        { "LocalBattleTableUpdate",     0x611F70, "sub_140611F70", "Writes uid/status/BattleParam into a local battle table slot.", "Offline lobby/fake player experiments." },
        { "SendSignal",                 0x0F1F80, "sub_1400F1F80", "Sends a small lobby/network signal packet.", "Ready/start/cancel signal logging." },
        { "RegisterLocalBattleTable",   0x0EC260, "sub_1400EC260", "Registers local battle table data and then refreshes the lobby table.", "Local player slot edit path." },
        { "SendRegisterOnTable",        0x0F1550, "sub_1400F1550", "Sends a 608-byte RegisterOnTable packet containing team data.", "Online lobby team sync." },
        { "StoreBattleParamByPlayer",   0x6122F0, "sub_1406122F0", "Stores a copied BattleParam in a tree keyed by player id.", "Runtime player cache inspection." },
        { "BuildCurrentTeamCustomize",  0x611A50, "sub_140611A50", "Builds leader/support customize data from gTeamPresetDatabase and gCharacterCustomizeDatabase.", "Current preset preview/customize editor." },
        { "TeamCustomizeVectorAdd",     0x827B90, "sub_140827B90", "Dedupes and inserts an 88-byte team customize entry into a runtime vector.", "Runtime customize list logger." },
        { "QueuedUiCallbackPush",       0x10F250, "sub_14010F250", "Pushes a UI callback/task into a ring/queue structure.", "Animated popup/notification queue." },
        { "PopupInvokeCallback",        0xBE4010, "sub_140BE4010", "Invokes the popup callback object depending on type.", "Popup callback lifecycle fix." },
        { "CharacterSelectEventDispatcher", 0x739220, "sub_140739220", "Flash callback dispatcher for character select events: pad info, costume changed, color changed, model changed, apply.", "Main hook point for F2 apply/readback controls." },
        { "CharacterSelectCommandDispatcher", 0x739A00, "sub_140739A00", "Command dispatcher for select/validate/commit/clear/team actions from character select Flash.", "Map Flash commands to safe editor buttons." },
        { "CharacterSelectSetCursorDirect", 0x742460, "sub_140742460", "Calls SetCursorDirect(player,costume,color,extra) on charsel Flash.", "Move costume/color cursor without committing." },
        { "CharacterSelectBuildCostumePage", 0x749840, "sub_140749840", "Rebuilds costume page: AddCostumeInfo, AddColorInfo, AddSpAtkInfo, AddPairInfo, OpenCostumeSkillSelect.", "Refresh F2 costume/color lists and UI preview." },
        { "CharacterSelectStartSelect", 0x749260, "sub_140749260", "Calls StartCharacterSelect and handles Cos<->Sel transitions.", "Return to select / open selection flow." },
        { "CharacterSelectSetFaceIcon", 0x742FB0, "sub_140742FB0", "Calls SetFaceIcon(player,slot,enabled,faceName,costume,locked,selected).", "Portrait override and lock/selected preview." },
        { "CharacterSelectSetCostumeName", 0x7462E0, "sub_1407462E0", "Calls SetCostumeName(player,name) on _root.all_nut.", "Runtime costume name override." },
        { "CharacterSelectPairListRefresh", 0x74DAB0, "sub_14074DAB0", "Rebuilds pair info list after team/costume changes.", "Refresh team ultimate / pair skill list." },
        { "CharacterSelectSetAssistName", 0x741FA0, "sub_140741FA0", "Calls SetAssistName(player,text).", "Assist/support name override." },
        { "CharacterSelectPlayerSelect", 0x73C260, "sub_14073C260", "Handles player select/confirm flow and starts selection when needed.", "Read/apply player slot state." },
        { "CharacterSelectGetTeamSlot", 0x73C7C0, "sub_14073C7C0", "Returns selected team slot index from current vector count.", "Detect leader/support index for F2." },
        { "CharacterSelectApplyWindow", 0x74B020, "sub_14074B020", "Apply/confirm customization window; initializes slots and accessory/dodge/final cutin labels.", "Refresh customization panel." },
        { "CharacterSelectColorChange", 0x73A8B0, "sub_14073A8B0", "Wrapper that calls preview costume/color update through ccUiCharacterSelect3DModel.", "Instant color preview." },
        { "CharacterPreviewSetCostume", 0x7153D0, "sub_1407153D0", "Sets preview costume/color, reloads asset if model exists or queues it if not.", "Preview costume/color apply." },
        { "CharacterPreviewSetMode", 0x715290, "sub_140715290", "Sets preview model mode 3-7 and marks dirty/reload flags.", "Force preview reload/mode." },
        { "CharacterPreviewSwapModel", 0x715480, "sub_140715480", "Writes player/model id/variant and marks dirty/reload flags.", "Character select 3D preview model swap." },
        { "CharacterPreviewGetModel", 0x714060, "sub_140714060", "Returns current preview model id for a player slot.", "Compare before swapping model." },
        { "NetMenu3DModelSetModel", 0x807F40, "sub_140807F40", "ccUiNetMenu3DModel::SetModel writes character/costume/color/flags and marks dirty.", "Lobby/menu model apply button." },
        { "ValidatePairSkill", 0x661480, "sub_140661480", "Validates leader/support/pair skill compatibility and returns valid slots.", "Ignore pair restrictions later." },
        { "BuildPairSkillList", 0x73AAF0, "sub_14073AAF0", "Builds current pair/team ultimate list by calling pair validators.", "Rebuild pair skill dropdown." },
    };

    std::string Hex(uintptr_t value)
    {
        std::ostringstream ss;
        ss << "0x" << std::hex << std::uppercase << value;
        return ss.str();
    }


    template <typename T>
    T Fn(uintptr_t rva)
    {
        if (!g_Base)
            return nullptr;
        return reinterpret_cast<T>(g_Base + rva);
    }

    template <typename T>
    T* Ptr(uintptr_t va)
    {
        if (!g_Base)
            return nullptr;
        return reinterpret_cast<T*>(g_Base + (va - 0x140000000ULL));
    }

    using SetModel_t = void(__fastcall*)(__int64 manager, int slot, unsigned int playerId, int costumeId, int charaCode, int variant);
    using SetModelMode_t = __int64(__fastcall*)(__int64 manager, int mode);
    using SetActive_t = __int64(__fastcall*)(__int64 manager, unsigned int active);
    using GetNetMenuModelMgr_t = __int64(__fastcall*)(__int64 sceneSystem);
    using CopyBattleData_t = __int64(__fastcall*)(__int64 dst, __int64 src);

    constexpr uintptr_t kSetModelRva = 0x807F40;
    constexpr uintptr_t kSetModelModeRva = 0x8080C0;
    constexpr uintptr_t kSetActiveRva = 0x807B80;
    constexpr uintptr_t kGetNetMenuModelMgrRva = 0x82C790;
    constexpr uintptr_t kCopyBattleDataRva = 0x0D1380;
    constexpr uintptr_t kGlobalBattleSelectParamVa = 0x14218F7C0ULL;
    constexpr uintptr_t kSceneSystemVa = 0x142188D20ULL;
    constexpr size_t kBattlePlayerDataSize = 592;

    void SetBattleMessage(const std::string& message)
    {
        strncpy_s(g_Overrides.LastBattleApplyMessage, message.c_str(), _TRUNCATE);
        Logger::Info("BattleModelTest: " + message);
    }

    __int64 GetGlobalBattleSelectParam()
    {
        auto pp = Ptr<__int64>(kGlobalBattleSelectParamVa);
        return pp ? *pp : 0;
    }

    __int64 GetSceneSystem()
    {
        auto pp = Ptr<__int64>(kSceneSystemVa);
        return pp ? *pp : 0;
    }

    __int64 GetNetMenuModelManager()
    {
        auto getMgr = Fn<GetNetMenuModelMgr_t>(kGetNetMenuModelMgrRva);
        __int64 sceneSystem = GetSceneSystem();
        if (!getMgr || !sceneSystem)
            return 0;
        return getMgr(sceneSystem);
    }
}

namespace CharacterRuntimeEditor
{
    bool Init(uintptr_t gameBase)
    {
        g_Base = gameBase;
        Logger::Info("CharacterRuntimeEditor initialized base=" + Hex(g_Base));
        return g_Base != 0;
    }

    void Shutdown()
    {
        Logger::Info("CharacterRuntimeEditor shutdown");
        g_Base = 0;
    }

    uintptr_t Base()
    {
        return g_Base;
    }

    RuntimeEditorOptions& Options()
    {
        return g_Options;
    }

    RuntimeOverrideState& Overrides()
    {
        return g_Overrides;
    }

    const std::vector<FunctionMapEntry>& FunctionMap()
    {
        return g_FunctionMap;
    }

    void LogMap()
    {
        Logger::Info("=== Character Runtime Editor Map ===");
        for (const auto& entry : g_FunctionMap)
        {
            Logger::Info(std::string(entry.Name) + " rva=" + Hex(entry.Rva) +
                " ida=" + entry.IdaName + " use=" + entry.HookUse +
                " desc=" + entry.Description);
        }
    }

    void LogRuntimeSummary()
    {
        Logger::Info(RuntimePipelineSummary());
        Logger::Info("Known layouts: TeamPreset=448 bytes, RuntimeMember=112 bytes, BattleParam=592 bytes, TeamCustomizeVectorEntry=88 bytes, CharacterInfoResolved=64 bytes, CharacterNameRow=40 bytes.");
        Logger::Info("Current mode is scaffold/safe by default. Memory writes stay disabled while SafeModeNoMemoryWrites is true.");
    }

    void ResetOverrides()
    {
        g_Overrides = RuntimeOverrideState{};
    }

    void ApplyOverrides()
    {
        g_Overrides.PendingApply = true;
        g_Overrides.LastApplyBlockedBySafeMode = g_Options.SafeModeNoMemoryWrites;

        std::ostringstream ss;
        ss << "CharacterRuntimeEditor Apply queued"
           << " slot=" << g_Overrides.SelectedPlayerSlot
           << " character=" << g_Overrides.PreviewCharacterId
           << " costume=" << g_Overrides.PreviewCostumeId
           << " color=" << g_Overrides.PreviewColorId
           << " variant=" << g_Overrides.PreviewVariantId
           << " effect=" << g_Overrides.PreviewEffectId
           << " face=" << g_Overrides.PreviewFaceId
           << " pair=" << g_Overrides.PreviewPairSkillId
           << " safeMode=" << (g_Options.SafeModeNoMemoryWrites ? "on" : "off");
        Logger::Info(ss.str());

        if (g_Options.SafeModeNoMemoryWrites)
        {
            Logger::Warn("CharacterRuntimeEditor: safe mode is ON; apply only records values/logs. Native writes are blocked until hook wrappers are wired.");
            return;
        }

        Logger::Warn("CharacterRuntimeEditor: native write mode requested, but direct call wrappers are intentionally not enabled in this build.");
    }


    void ApplyBattleModelTest()
    {
        g_Overrides.BattleApplyPending = true;
        g_Overrides.BattleApplyOk = false;
        g_Overrides.BattleApplyBlockedBySafeMode = g_Options.SafeModeNoMemoryWrites;

        std::ostringstream ss;
        ss << "slot=" << g_Overrides.BattleSlot
           << " playerId=" << g_Overrides.BattleCharacterId
           << " costume=" << g_Overrides.BattleCostumeId
           << " charaCode=" << g_Overrides.BattleCharaCode
           << " variant=" << g_Overrides.BattleVariantId
           << " mode=" << g_Overrides.BattleModelMode
           << " state=" << g_Overrides.BattleModelState
           << " writeBattleParam=" << (g_Overrides.WriteBattleSelectParam ? "yes" : "no")
           << " applyNetModel=" << (g_Overrides.ApplyNetMenuModel ? "yes" : "no")
           << " safe=" << (g_Options.SafeModeNoMemoryWrites ? "on" : "off");
        Logger::Info("BattleModelTest requested: " + ss.str());

        if (g_Options.SafeModeNoMemoryWrites)
        {
            SetBattleMessage("safe mode on - logged only");
            return;
        }

        if (!g_Base)
        {
            SetBattleMessage("failed: game base missing");
            return;
        }

        int slot = g_Overrides.BattleSlot;
        if (slot < 0) slot = 0;
        if (slot > 1) slot = 1;

        const int playerId = g_Overrides.BattleCharacterId;
        if (playerId < 0)
        {
            SetBattleMessage("failed: playerId must be >= 0");
            return;
        }

        bool wroteBattleParam = false;
        if (g_Overrides.WriteBattleSelectParam)
        {
            __int64 root = GetGlobalBattleSelectParam();
            auto copyBattleData = Fn<CopyBattleData_t>(kCopyBattleDataRva);
            if (root && copyBattleData)
            {
                const __int64 primary = root + 16 + (static_cast<__int64>(slot) * kBattlePlayerDataSize);
                const __int64 mirror = root + 1200 + (static_cast<__int64>(slot) * kBattlePlayerDataSize);

                *reinterpret_cast<int*>(primary + 0) = playerId;
                *reinterpret_cast<int*>(primary + 4) = g_Overrides.BattleCostumeId;
                *reinterpret_cast<int*>(primary + 8) = g_Overrides.BattleCharaCode;
                *reinterpret_cast<int*>(primary + 32) = g_Overrides.BattleVariantId;
                *reinterpret_cast<int*>(primary + 40) = g_Overrides.PreviewPairSkillId;
                *reinterpret_cast<float*>(primary + 476) = 1.0f;
                *reinterpret_cast<float*>(primary + 480) = 1.0f;
                copyBattleData(mirror, primary);
                wroteBattleParam = true;
            }
            else
            {
                Logger::Warn("BattleModelTest: could not edit BattleSelectParam root/copy function");
            }
        }

        bool appliedModel = false;
        if (g_Overrides.ApplyNetMenuModel)
        {
            __int64 manager = GetNetMenuModelManager();
            auto setActive = Fn<SetActive_t>(kSetActiveRva);
            auto setMode = Fn<SetModelMode_t>(kSetModelModeRva);
            auto setModel = Fn<SetModel_t>(kSetModelRva);
            if (manager && setModel)
            {
                if (setActive)
                    setActive(manager, 1);
                if (setMode)
                    setMode(manager, g_Overrides.BattleModelMode);
                setModel(manager, slot, static_cast<unsigned int>(playerId), g_Overrides.BattleCostumeId, g_Overrides.BattleCharaCode, g_Overrides.BattleVariantId);
                appliedModel = true;
            }
            else
            {
                Logger::Warn("BattleModelTest: model manager unavailable; likely not in net menu/model scene");
            }
        }

        g_Overrides.BattleApplyOk = wroteBattleParam || appliedModel;
        SetBattleMessage(std::string("done: battleParam=") + (wroteBattleParam ? "yes" : "no") + " netModel=" + (appliedModel ? "yes" : "no"));
    }

    void ReadCurrentSelectionScaffold()
    {
        Logger::Info("CharacterRuntimeEditor Read Current requested. Current build logs the request; native readback pointer discovery is the next hook step.");
    }

    const char* RuntimePipelineSummary()
    {
        return "Pipeline: BattleSelectParam root -> BattlePlayerData592 slots -> NetMenu3DModel::SetActive/SetModel -> dirty/reload flags. Match actor pointer is still unknown.";
    }
}
