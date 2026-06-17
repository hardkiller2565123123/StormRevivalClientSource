#include "DX11OverlayInternal.h"

bool ActiveCheckbox(const char* label, bool* value, const char* help)
{
    bool changed = ImGui::Checkbox(label, value);

    ImGui::SameLine();
    ImGui::TextColored(ImVec4(0.35f, 1.0f, 0.35f, 1.0f), "[ACTIVE]");

    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", help ? help : "");

    return changed;
}

bool PlannedCheckbox(const char* label, bool* value, const char* reason)
{
    bool changed = ImGui::Checkbox(label, value);

    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 0.70f, 0.25f, 1.0f), "[PLANNED]");

    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("%s", reason ? reason : "");

    return changed;
}

void DrawLeftButton(const char* label, int page)
{
    bool selected = g_SelectedSubPage == page;
    float width = std::max(120.0f, ImGui::GetContentRegionAvail().x);

    if (selected)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.17f, 0.38f, 0.66f, 1.0f));

    if (ImGui::Button(label, ImVec2(width, 25.0f)))
        g_SelectedSubPage = page;

    if (selected)
        ImGui::PopStyleColor();
}

bool IniCheckbox(const char* label, int& value)
{
    bool checked = value != 0;

    if (ImGui::Checkbox(label, &checked))
    {
        value = checked ? 1 : 0;
        return true;
    }

    return false;
}

bool IniCheckbox(const char* label, int& value, const char* help)
{
    bool changed = IniCheckbox(label, value);
    HelpMarker(help);
    return changed;
}

void HelpMarker(const char* text)
{
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");

    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(420.0f);
        ImGui::TextUnformatted(text ? text : "");
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void ResolutionPreset(const char* label, int width, int height)
{
    auto& screen = NS2Config::Screen();

    if (ImGui::Button(label, ImVec2(112.0f, 24.0f)))
    {
        screen.Width = width;
        screen.Height = height;
    }
}
