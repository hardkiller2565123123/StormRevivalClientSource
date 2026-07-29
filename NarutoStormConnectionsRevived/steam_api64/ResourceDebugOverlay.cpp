#include "StdInc.h"
#include "ResourceDebugOverlay.h"
#include "ResourceRedirector.h"

#include "imgui.h"

namespace ResourceDebugOverlay
{
    void Draw()
    {
        if (!ImGui::CollapsingHeader("Resource Redirector", ImGuiTreeNodeFlags_DefaultOpen))
            return;

        bool enabled = ResourceRedirector::IsEnabled();
        if (ImGui::Checkbox("Enable mods folder redirect", &enabled))
            ResourceRedirector::SetEnabled(enabled);

        bool absolutePath = ResourceRedirector::PreferAbsolutePath();
        if (ImGui::Checkbox("Pass absolute mod path to game", &absolutePath))
            ResourceRedirector::SetPreferAbsolutePath(absolutePath);

        if (ImGui::Button("Refresh mods folder"))
            ResourceRedirector::RefreshModFolders();

        ImGui::SameLine();
        if (ImGui::Button("Clear resource log"))
            ResourceRedirector::ClearRecentRequests();

        ImGui::Text("Mod folders: %d", static_cast<int>(ResourceRedirector::GetModFolders().size()));
        for (const std::string& folder : ResourceRedirector::GetModFolders())
            ImGui::BulletText("%s", folder.c_str());

        ImGui::Separator();
        ImGui::TextUnformatted("Recent resource requests");

        const auto& requests = ResourceRedirector::GetRecentRequests();
        if (ImGui::BeginTable("ResourceRequests", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
        {
            ImGui::TableSetupColumn("Original");
            ImGui::TableSetupColumn("Redirected");
            ImGui::TableSetupColumn("Matched file");
            ImGui::TableHeadersRow();

            for (const auto& req : requests)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::TextUnformatted(req.originalPath.c_str());
                ImGui::TableSetColumnIndex(1);
                ImGui::TextUnformatted(req.redirected ? req.redirectedPath.c_str() : "-");
                ImGui::TableSetColumnIndex(2);
                ImGui::TextUnformatted(req.redirected ? req.matchedFile.c_str() : "-");
            }

            ImGui::EndTable();
        }
    }
}
