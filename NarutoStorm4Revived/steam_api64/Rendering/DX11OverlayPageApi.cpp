#include "DX11OverlayInternal.h"
#include "CharacterSlotExpansionManager.h"
#include "RuntimeFeatureRegistry.h"
#include "SlotExpansionManager.h"
#include "SteamDiagnostics.h"
#include "Storm4IdaRuntime.h"

namespace
{
    ImVec4 StateColor(RuntimeFeatureState state)
    {
        switch (state)
        {
        case RuntimeFeatureState::Active: return ImVec4(0.30f, 0.95f, 0.45f, 1.0f);
        case RuntimeFeatureState::Ready: return ImVec4(0.45f, 0.75f, 1.0f, 1.0f);
        case RuntimeFeatureState::Managed: return ImVec4(0.95f, 0.80f, 0.35f, 1.0f);
        case RuntimeFeatureState::Planned: return ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
        case RuntimeFeatureState::NeedsPatch: return ImVec4(1.0f, 0.45f, 0.35f, 1.0f);
        default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    void DrawFeatureRegistry()
    {
        ImGui::Text("API > Feature Registry");
        ImGui::Separator();

        ImGui::Text("Tracked: %d", RuntimeFeatureRegistry::CountAll());
        ImGui::SameLine();
        ImGui::TextColored(StateColor(RuntimeFeatureState::Active), "Active %d", RuntimeFeatureRegistry::CountByState(RuntimeFeatureState::Active));
        ImGui::SameLine();
        ImGui::TextColored(StateColor(RuntimeFeatureState::Ready), "Ready %d", RuntimeFeatureRegistry::CountByState(RuntimeFeatureState::Ready));
        ImGui::SameLine();
        ImGui::TextColored(StateColor(RuntimeFeatureState::Managed), "Managed %d", RuntimeFeatureRegistry::CountByState(RuntimeFeatureState::Managed));
        ImGui::SameLine();
        ImGui::TextColored(StateColor(RuntimeFeatureState::NeedsPatch), "Needs Patch %d", RuntimeFeatureRegistry::CountByState(RuntimeFeatureState::NeedsPatch));

        ImGui::Separator();

        if (ImGui::BeginTable("api_feature_table", 4, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY))
        {
            ImGui::TableSetupColumn("Category", ImGuiTableColumnFlags_WidthFixed, 130.0f);
            ImGui::TableSetupColumn("Feature", ImGuiTableColumnFlags_WidthFixed, 220.0f);
            ImGui::TableSetupColumn("State", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("Detail");
            ImGui::TableHeadersRow();

            for (const RuntimeFeatureInfo& feature : RuntimeFeatureRegistry::Snapshot())
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted(feature.Category);
                ImGui::TableSetColumnIndex(1);
                ImGui::TextWrapped("%s", feature.Name);
                ImGui::TableSetColumnIndex(2);
                ImGui::TextColored(StateColor(feature.State), "%s", RuntimeFeatureRegistry::StateName(feature.State));
                ImGui::TableSetColumnIndex(3);
                ImGui::TextWrapped("%s", feature.Detail);
            }

            ImGui::EndTable();
        }
    }

    void DrawSlotManager()
    {
        SlotExpansionConfig& config = SlotExpansionManager::MutableConfig();

        ImGui::Text("API > Slot Expansion");
        ImGui::Separator();

        ImGui::TextWrapped("Runtime slot settings are saved and loaded on game start. Saved count changes apply after restart. Stage/scene expansion can run automatically; character roster and costume roster still need final char-select table offsets before they can show new visible select-screen boxes.");
        ImGui::Separator();

        ImGui::Checkbox("Auto-apply runtime expansions on startup", &config.AutoApplyRuntime);
        ImGui::Checkbox("Enable stage/scene expansion at runtime", &config.EnableStageSceneRuntime);
        ImGui::Checkbox("Enable character roster runtime diagnostics", &config.EnableCharacterRosterRuntime);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Startup apply delay ms", &config.AutoApplyDelayMs);

        ImGui::Separator();

        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra character roster slots", &config.ExtraCharacterSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra costume slots", &config.ExtraCostumeSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra stage slots", &config.ExtraStageSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra scene slots", &config.ExtraSceneSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra BGM slots", &config.ExtraBgmSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra projectile slots", &config.ExtraProjectileSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra partner slots", &config.ExtraPartnerSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra team ultimate slots", &config.ExtraTeamUltimateSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra condition slots", &config.ExtraConditionSlots);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::InputInt("Extra character relation slots", &config.ExtraCharRelationSlots);

        ImGui::Separator();

        if (ImGui::Button("Apply Stage/Scene Expansion Now", ImVec2(260.0f, 24.0f)))
            SlotExpansionManager::ApplyStageExpansion();

        ImGui::SameLine();

        if (ImGui::Button("Run Character Slot Diagnostics", ImVec2(250.0f, 24.0f)))
            CharacterSlotExpansionManager::RunDiagnostics();

        ImGui::SameLine();

        if (ImGui::Button("Save Runtime Settings", ImVec2(190.0f, 24.0f)))
            SlotExpansionManager::Save();

        ImGui::SameLine();

        if (ImGui::Button("Reset Defaults", ImVec2(150.0f, 24.0f)))
            SlotExpansionManager::ResetDefaults();

        ImGui::Separator();
        ImGui::Text("Stage request: %s", SlotExpansionManager::StageExpansionRequested() ? "yes" : "no");
        ImGui::Text("Stage applied: %s", SlotExpansionManager::StageExpansionApplied() ? "yes" : "no");
        ImGui::TextWrapped("Status: %s", SlotExpansionManager::LastStatus());
        ImGui::TextWrapped("Character slots: %s", CharacterSlotExpansionManager::LastStatus());

        ImGui::Separator();
        ImGui::Text("Storm 4 IDA Targets");
        ImGui::TextWrapped("These are confirmed anchors from the current IDA pass. Callable targets stay disabled unless their signature is known and the loaded game version matches.");

        size_t targetCount = 0;
        const Storm4IdaRuntime::KnownTarget* targets = Storm4IdaRuntime::Targets(targetCount);
        if (ImGui::BeginTable("storm4_ida_targets", 5, ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0.0f, 260.0f)))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 280.0f);
            ImGui::TableSetupColumn("RVA", ImGuiTableColumnFlags_WidthFixed, 90.0f);
            ImGui::TableSetupColumn("Kind", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableSetupColumn("State", ImGuiTableColumnFlags_WidthFixed, 90.0f);
            ImGui::TableSetupColumn("Notes");
            ImGui::TableHeadersRow();

            for (size_t i = 0; i < targetCount; ++i)
            {
                const bool present = Storm4IdaRuntime::IsTargetPresent(targets[i]);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextWrapped("%s", targets[i].Name);
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("0x%llX", static_cast<unsigned long long>(targets[i].Rva));
                ImGui::TableSetColumnIndex(2);
                ImGui::TextUnformatted(Storm4IdaRuntime::KindName(targets[i].Kind));
                ImGui::TableSetColumnIndex(3);
                ImGui::TextColored(present ? StateColor(RuntimeFeatureState::Active) : StateColor(RuntimeFeatureState::NeedsPatch),
                    "%s", present ? "present" : "missing");
                ImGui::TableSetColumnIndex(4);
                ImGui::TextWrapped("%s", targets[i].Notes);
            }

            ImGui::EndTable();
        }
    }

    void DrawDiagnostics()
    {
        ImGui::Text("API > Diagnostics");
        ImGui::Separator();

        if (ImGui::Button("Write Steam/API Diagnostics Report", ImVec2(280.0f, 24.0f)))
            SteamDiagnostics::WriteReport();

        ImGui::Separator();
        ImGui::Text("Overlay: active");
        ImGui::Text("Feature registry: active");
        ImGui::Text("Slot manager: active");
        ImGui::Text("Framework bridge: available through framework tabs when loaded");
    }
}

void DrawApiPage()
{
    if (g_SelectedSubPage == 0)
        DrawFeatureRegistry();
    else if (g_SelectedSubPage == 1)
        DrawSlotManager();
    else
        DrawDiagnostics();
}
