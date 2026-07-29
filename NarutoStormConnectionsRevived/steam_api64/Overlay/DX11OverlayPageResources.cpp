#include "StdInc.h"
#include "DX11OverlayPageResources.h"
#include "Runtime/ResourceRedirector.h"

#include <imgui.h>

namespace DX11OverlayPageResources
{
    void Draw()
    {
        bool enabled = ResourceRedirector::Enabled();
        if (ImGui::Checkbox("Enable mods/resource redirect", &enabled))
            ResourceRedirector::SetEnabled(enabled);

        ImGui::TextWrapped("Mods root: %s", ResourceRedirector::ModsRoot().c_str());

        if (ImGui::Button("Rescan mods"))
            ResourceRedirector::RescanMods();
        ImGui::SameLine();
        if (ImGui::Button("Clear resource log"))
            ResourceRedirector::ClearLogRows();

        ImGui::Separator();
        ImGui::Text("Mod folders");
        for (const auto& mod : ResourceRedirector::ModFolders())
            ImGui::BulletText("%s", mod.c_str());

        ImGui::Separator();
        ImGui::Text("Resource requests");

        const auto rows = ResourceRedirector::SnapshotRows();
        if (ImGui::BeginTable("ResourceTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 360)))
        {
            ImGui::TableSetupColumn("Type");
            ImGui::TableSetupColumn("Count");
            ImGui::TableSetupColumn("Redirect");
            ImGui::TableSetupColumn("Original");
            ImGui::TableSetupColumn("Final");
            ImGui::TableHeadersRow();

            for (const auto& row : rows)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted(row.kind == ResourceTypes::RedirectKind::ScaleformMovie ? "Scaleform" : "XFBIN");
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%u", row.requestCount);
                ImGui::TableSetColumnIndex(2);
                ImGui::TextUnformatted(row.redirected ? row.modName.c_str() : "original");
                ImGui::TableSetColumnIndex(3);
                ImGui::TextWrapped("%s", row.originalPath.c_str());
                ImGui::TableSetColumnIndex(4);
                ImGui::TextWrapped("%s", row.finalPath.c_str());
            }

            ImGui::EndTable();
        }
    }
}
