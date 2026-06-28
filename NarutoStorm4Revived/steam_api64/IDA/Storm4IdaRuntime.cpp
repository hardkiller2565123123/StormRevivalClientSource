#include "Storm4IdaRuntime.h"
#include <Windows.h>
#include <cstring>

namespace
{
    constexpr uintptr_t kImageBase = 0x140000000;

    constexpr Storm4IdaRuntime::KnownTarget kTargets[] = {
        { "ccUiCharacterSelect3DModel::Draw string", 0x1189C70, Storm4IdaRuntime::TargetKind::String, false, "Scene object draw name anchor; xrefs register select-screen model object." },
        { "ccUiCharacterSelect3DModel::Ctrl string", 0x1189C98, Storm4IdaRuntime::TargetKind::String, false, "Scene object control name anchor; xrefs register select-screen model object." },
        { "RegisterCharacterSelectSceneObject", 0x0641E8B, Storm4IdaRuntime::TargetKind::Function, false, "Registers character-select scene object names and callbacks; useful anchor, not the slot grid." },
        { "characterSelectParam.xfbin path", 0x12ABC80, Storm4IdaRuntime::TargetKind::String, false, "Character-select parameter file path; points into the resource path registration table." },
        { "RegisterGameResourcePathTable", 0x0136C6C, Storm4IdaRuntime::TargetKind::Function, false, "Resource-path table loader that references characterSelectParam.xfbin and select_stage.xfbin." },
        { "ccSceneFreeBattleCharacterSelect.cpp string", 0x13307A0, Storm4IdaRuntime::TargetKind::String, false, "Free battle character-select scene source anchor." },
        { "FreeBattleCharacterSelect_ModelAdjustmentOptions", 0x0740858, Storm4IdaRuntime::TargetKind::Function, false, "Debug/model-adjustment branch; useful UI anchor, not visible slot count." },
        { "CharacterSelect_MessageOrUiTextSetup", 0x0740740, Storm4IdaRuntime::TargetKind::Function, false, "Loads characterselect_008, icons, random text, and help/footer messages." },
        { "characterselect_008 string", 0x1330788, Storm4IdaRuntime::TargetKind::String, false, "Message text anchor used by normal character-select text setup." },
        { "SetConvertSelectCharaInfo string", 0x12C4228, Storm4IdaRuntime::TargetKind::String, false, "Selected character info debug string; xrefs locate selected-team packing." },
        { "ConvertSelectCharaInfo", 0x05B83C0, Storm4IdaRuntime::TargetKind::Function, false, "Packs the selected character/team/costume/support info after UI selection." },
        { "UnlockCharacterCheck command table", 0x181F5B8, Storm4IdaRuntime::TargetKind::DataTable, false, "Command table entry: name pointer, handler pointer, cleanup pointer." },
        { "UnlockCharacterCheck_Handler", 0x0743420, Storm4IdaRuntime::TargetKind::Function, false, "Tiny command wrapper; calls UnlockCharacterCheck_Core and writes command status fields." },
        { "UnlockCharacterCheck_Core", 0x05F7234, Storm4IdaRuntime::TargetKind::Function, true, "No-argument unlock check core found from the handler wrapper. Signature verified only as no-argument return value." },
        { "UnlockCollectionCheck_Handler", 0x0743468, Storm4IdaRuntime::TargetKind::Function, false, "Command-table handler found beside UnlockCharacterCheck." },
        { "UnlockCollectionCheck_Callback", 0x07434C4, Storm4IdaRuntime::TargetKind::Function, false, "Command-table callback found beside UnlockCollectionCheck." },
        { "UnlockPopUp_Callback", 0x05F8158, Storm4IdaRuntime::TargetKind::Function, false, "Callback from UnlockPopUp command table entry." },
        { "IsDlcCharacter string", 0x130A150, Storm4IdaRuntime::TargetKind::String, false, "Visible/hidden character filtering anchor; still needs core xref path verified." },
        { "ccStageSelectConfig::Create string", 0x1300C30, Storm4IdaRuntime::TargetKind::String, false, "Stage-select config creation anchor." },
        { "ccSceneBattleStageSelect.cpp string", 0x1339240, Storm4IdaRuntime::TargetKind::String, false, "Battle stage-select scene anchor." }
    };

    bool QueryAddress(uintptr_t absoluteAddress, MEMORY_BASIC_INFORMATION& mbi)
    {
        if (absoluteAddress == 0)
            return false;

        return VirtualQuery(reinterpret_cast<LPCVOID>(absoluteAddress), &mbi, sizeof(mbi)) == sizeof(mbi);
    }

    uintptr_t GameModuleBase()
    {
        return reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    }

    bool HasExpectedString(uintptr_t rva, const char* expected)
    {
        const uintptr_t address = Storm4IdaRuntime::Absolute(rva);
        if (!Storm4IdaRuntime::IsReadable(address))
            return false;

        return std::strncmp(reinterpret_cast<const char*>(address), expected, std::strlen(expected) + 1) == 0;
    }
}

namespace Storm4IdaRuntime
{
    bool IsSupportedStorm4Version()
    {
        return HasExpectedString(0x1189C98, "ccUiCharacterSelect3DModel::Ctrl") &&
            HasExpectedString(0x130A150, "IsDlcCharacter");
    }

    uintptr_t Absolute(uintptr_t rva)
    {
        const uintptr_t moduleBase = GameModuleBase();
        if (moduleBase == 0 || rva == 0)
            return 0;

        if (rva >= kImageBase)
            rva -= kImageBase;

        return moduleBase + rva;
    }

    bool IsReadable(uintptr_t absoluteAddress)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        if (!QueryAddress(absoluteAddress, mbi))
            return false;

        if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD))
            return false;

        return (mbi.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY |
            PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
    }

    bool IsExecutable(uintptr_t absoluteAddress)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        if (!QueryAddress(absoluteAddress, mbi))
            return false;

        if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_NOACCESS) || (mbi.Protect & PAGE_GUARD))
            return false;

        return (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ |
            PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
    }

    bool IsTargetPresent(const KnownTarget& target)
    {
        const uintptr_t address = Absolute(target.Rva);
        if (target.Kind == TargetKind::Function)
            return IsExecutable(address);

        return IsReadable(address);
    }

    const char* KindName(TargetKind kind)
    {
        switch (kind)
        {
        case TargetKind::Function: return "function";
        case TargetKind::String: return "string";
        case TargetKind::DataTable: return "data table";
        default: return "unknown";
        }
    }

    const KnownTarget* Targets(size_t& count)
    {
        count = sizeof(kTargets) / sizeof(kTargets[0]);
        return kTargets;
    }

    UnlockCharacterCheckCoreFn UnlockCharacterCheckCore()
    {
        const uintptr_t address = Absolute(0x05F7234);
        if (!IsSupportedStorm4Version() || !IsExecutable(address))
            return nullptr;

        return reinterpret_cast<UnlockCharacterCheckCoreFn>(address);
    }

    int CountPresentTargets()
    {
        size_t count = 0;
        const KnownTarget* targets = Targets(count);
        int present = 0;
        for (size_t i = 0; i < count; ++i)
        {
            if (IsTargetPresent(targets[i]))
                ++present;
        }
        return present;
    }
}
