#include "RuntimeFeatureRegistry.h"

namespace
{
    const std::vector<RuntimeFeatureInfo> kFeatures = {
        {"Core", "Startup diagnostics", RuntimeFeatureState::Active, "Logger, Steam diagnostics, interface registry, and offline init timeline are available."},
        {"Core", "In-game API dashboard", RuntimeFeatureState::Active, "Native DX11 overlay API tab with feature status and slot controls."},
        {"Core", "Safe mode / vanilla mode", RuntimeFeatureState::Managed, "Tracked in dashboard; final launch flag enforcement can be added at process startup."},
        {"Core", "Debug report export", RuntimeFeatureState::Active, "SteamDiagnostics report writer is wired into debug tools."},
        {"Steam", "Offline Steam profile", RuntimeFeatureState::Active, "SteamID, display name, local persona, and client overlay pages are present."},
        {"Steam", "Local achievements", RuntimeFeatureState::Active, "Achievement unlock, lock, save, and snapshot tools are present."},
        {"Steam", "Local stats", RuntimeFeatureState::Active, "Stat editor and local stat storage are present."},
        {"Steam", "DLC ownership layer", RuntimeFeatureState::Active, "Installed DLC loader and fake app ownership paths are present."},
        {"Steam", "LAN matchmaking", RuntimeFeatureState::Active, "Offline lobby, LAN discovery, callbacks, and call-result managers are present."},
        {"Steam", "Traffic blocking", RuntimeFeatureState::Active, "Network hook diagnostics and LAN-only controls are present."},
        {"Mods", "Plugin loader", RuntimeFeatureState::Ready, "Plugin load/reload path exists through Plugin and HookFunctions."},
        {"Mods", "Mod list manager", RuntimeFeatureState::Managed, "PluginManager lists are linked; overlay controls can be expanded on top."},
        {"Mods", "Dependency/conflict checks", RuntimeFeatureState::Planned, "Tracked for the next mod-manager pass."},
        {"Files", "CPK loader", RuntimeFeatureState::Ready, "CpkLoader source is wired and can be surfaced in the dashboard."},
        {"Files", "XFBIN parser", RuntimeFeatureState::Ready, "XfbinParser source is wired and available for content tools."},
        {"Files", "Lua loader", RuntimeFeatureState::Active, "Lua registration hooks and runtime script helpers are present."},
        {"Assets", "Asset browser", RuntimeFeatureState::Managed, "Framework asset tools are available when NS4FrameWork addon loads."},
        {"Assets", "Audio preview", RuntimeFeatureState::Managed, "Framework audio preview exists; CRI decode remains a deeper hook pass."},
        {"Assets", "Title music override", RuntimeFeatureState::Active, "NarutoStorm4Revived\\Audio\\Title.mp3 is played from the runtime audio folder when enabled."},
        {"Battle", "Moveset action tools", RuntimeFeatureState::Active, "MovesetPlus hooks and action helpers are compiled."},
        {"Battle", "Camera/HUD commands", RuntimeFeatureState::Active, "Lua HUD/camera command registration is compiled."},
        {"Battle", "Guard effect hooks", RuntimeFeatureState::Active, "GuardEffectParam hooks are compiled."},
        {"Battle", "Gudo ball hooks", RuntimeFeatureState::Active, "GudoBallParam hooks are compiled."},
        {"Battle", "Partner slot hook", RuntimeFeatureState::Active, "PartnerSlotParam and partner manager hooks are compiled."},
        {"Slots", "Stage/scene slots", RuntimeFeatureState::Ready, "Scene expander now has a dashboard-callable wrapper and higher slot capacity."},
        {"Slots", "Character support tables", RuntimeFeatureState::Managed, "Special conditions, relations, partners, TUJ, projectiles, and BGM are tracked for expanded content."},
        {"Slots", "Character roster table", RuntimeFeatureState::Managed, "CharacterSlotExpansionManager diagnostics are wired; visible grid patch still needs final select-screen offsets."},
        {"Slots", "Costume slots", RuntimeFeatureState::NeedsPatch, "Needs costume table offsets and UI bounds patching."},
        {"Content", "Special condition expansion", RuntimeFeatureState::Active, "SpecialConditionParam and ConditionPrmManager are compiled."},
        {"Content", "Team ultimate jutsu expansion", RuntimeFeatureState::Active, "TeamUltimateJutsuManager is compiled."},
        {"Content", "Projectile expansion", RuntimeFeatureState::Managed, "Projectile expander source exists; dashboard tracks capacity until enabled."},
        {"Content", "BGM expansion", RuntimeFeatureState::Managed, "BGM expander source exists; dashboard tracks capacity until enabled."},
        {"Content", "Scene expansion", RuntimeFeatureState::Ready, "Scene expander source can be invoked by SlotExpansionManager."},
        {"Diagnostics", "Hook status", RuntimeFeatureState::Managed, "Hook state is visible through debug pages and dashboard status."},
        {"Diagnostics", "Pattern scan report", RuntimeFeatureState::Planned, "PatternScan exists; report UI is a next pass."},
        {"Diagnostics", "Crash report collector", RuntimeFeatureState::Planned, "Error export foundation exists; minidump capture is not installed yet."}
    };
}

namespace RuntimeFeatureRegistry
{
    const std::vector<RuntimeFeatureInfo>& Snapshot()
    {
        return kFeatures;
    }

    const char* StateName(RuntimeFeatureState state)
    {
        switch (state)
        {
        case RuntimeFeatureState::Active: return "Active";
        case RuntimeFeatureState::Ready: return "Ready";
        case RuntimeFeatureState::Managed: return "Managed";
        case RuntimeFeatureState::Planned: return "Planned";
        case RuntimeFeatureState::NeedsPatch: return "Needs Patch";
        default: return "Unknown";
        }
    }

    int CountByState(RuntimeFeatureState state)
    {
        int count = 0;
        for (const RuntimeFeatureInfo& feature : kFeatures)
        {
            if (feature.State == state)
                ++count;
        }
        return count;
    }

    int CountAll()
    {
        return static_cast<int>(kFeatures.size());
    }
}
