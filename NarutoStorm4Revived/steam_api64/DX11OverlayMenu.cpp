#include "DX11OverlayInternal.h"

namespace
{
    int g_BasicTab = 0;
}

void DrawDropdownPanel()
{
}

void DrawAnimatedTopMenu()
{
    if (!g_MenuOpen)
        return;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    const float width = std::min(520.0f, std::max(320.0f, viewport->Size.x - 24.0f));
    const float height = std::min(360.0f, std::max(220.0f, viewport->Size.y - 24.0f));

    ImGui::SetNextWindowPos(ImVec2(12.0f, 36.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.92f);

    ImGui::Begin(
        "Naruto Revival Offline",
        nullptr,
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoCollapse);

    ImGui::TextUnformatted("Naruto Revival Offline");
    ImGui::SameLine();
    ImGui::TextDisabled("F1");
    ImGui::Separator();

    if (ImGui::Button("Client", ImVec2(110.0f, 0.0f)))
        g_BasicTab = 0;
    ImGui::SameLine();
    if (ImGui::Button("LAN", ImVec2(110.0f, 0.0f)))
        g_BasicTab = 1;

    ImGui::Separator();

    if (g_BasicTab == 0)
        DrawClientPage();
    else
        DrawOnlinePage();

    ImGui::End();
}