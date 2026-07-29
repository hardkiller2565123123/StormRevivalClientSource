#include "StdInc.h"
#include "DX11OverlayPageResources.h"
#include "ResourceRedirector.h"

#include <imgui.h>

namespace
{
    const char* KindText(ResourceTypes::RedirectKind kind)
    {
        return kind == ResourceTypes::RedirectKind::ScaleformMovie ? "Scaleform" : "XFBIN";
    }
}

namespace DX11OverlayPageResources
{
    void Draw()
    {
        bool enabled = ResourceRedirector::Enabled();
        if (ImGui::Checkbox("Enable mods/resource redirect", &enabled))
            ResourceRedirector::SetEnabled(enabled);

        ImGui::TextWrapped("Mods root: %s", ResourceRedirector::ModsRoot().c_str());

        if (ImGui::Button("Rescan mods", ImVec2(130.0f, 24.0f)))
            ResourceRedirector::RescanMods();
        ImGui::SameLine();
        if (ImGui::Button("Clear resource log", ImVec2(160.0f, 24.0f)))
            ResourceRedirector::ClearLogRows();

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Indexed mod files", ImGuiTreeNodeFlags_DefaultOpen))
        {
            const auto files = ResourceRedirector::SnapshotModFiles();
            ImGui::Text("Indexed files: %d", static_cast<int>(files.size()));

            if (ImGui::BeginTable("mod_files_table", 3,
                ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY,
                ImVec2(0.0f, 180.0f)))
            {
                ImGui::TableSetupColumn("Mod", ImGuiTableColumnFlags_WidthFixed, 140.0f);
                ImGui::TableSetupColumn("Relative path");
                ImGui::TableSetupColumn("Absolute path");
                ImGui::TableHeadersRow();

                for (const auto& file : files)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::TextWrapped("%s", file.ModName.c_str());
                    ImGui::TableSetColumnIndex(1); ImGui::TextWrapped("%s", file.RelativePath.c_str());
                    ImGui::TableSetColumnIndex(2); ImGui::TextWrapped("%s", file.AbsolutePath.c_str());
                }

                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("Resource requests", ImGuiTreeNodeFlags_DefaultOpen))
        {
            const auto rows = ResourceRedirector::SnapshotRows();
            ImGui::Text("Requests seen: %d", static_cast<int>(rows.size()));

            if (ImGui::BeginTable("resource_requests_table", 6,
                ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY,
                ImVec2(0.0f, 320.0f)))
            {
                ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 80.0f);
                ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                ImGui::TableSetupColumn("Mode", ImGuiTableColumnFlags_WidthFixed, 120.0f);
                ImGui::TableSetupColumn("Mod", ImGuiTableColumnFlags_WidthFixed, 130.0f);
                ImGui::TableSetupColumn("Original");
                ImGui::TableSetupColumn("Final");
                ImGui::TableHeadersRow();

                for (const auto& row : rows)
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted(KindText(row.Kind));
                    ImGui::TableSetColumnIndex(1); ImGui::Text("%u", row.RequestCount);
                    ImGui::TableSetColumnIndex(2); ImGui::TextUnformatted(row.Redirected ? "mods folder" : "original");
                    ImGui::TableSetColumnIndex(3); ImGui::TextWrapped("%s", row.ModName.empty() ? "-" : row.ModName.c_str());
                    ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", row.OriginalPath.c_str());
                    ImGui::TableSetColumnIndex(5); ImGui::TextWrapped("%s", row.FinalPath.c_str());
                }

                ImGui::EndTable();
            }
        }
    }
}
