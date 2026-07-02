#include "StdInc.h"
#include "EngineResearchUI.h"
#include "EngineAddressMap.h"
#include "EngineXfbinRuntime.h"
#include "RuntimeAssetTelemetry.h"
#include "imgui.h"

namespace
{
    char g_TestPath[256] = "data/stage/sd03a.xfbin";
    char g_TestChunkName[128] = "*head";
    int g_SelectedChunkType = 0;

    void CopyTextButton(const char* label, const std::string& text)
    {
        if (ImGui::Button(label, ImVec2(130, 22)))
            ImGui::SetClipboardText(text.c_str());
    }

    void DrawCapabilityBox()
    {
        ImGui::TextWrapped("This page is real C++ code, not a markdown note. It exposes the currently verified engine map and safe runtime wrappers.");
        ImGui::Separator();
        std::string text = EngineXfbinRuntime::BuildCapabilityText();
        ImGui::TextWrapped("%s", text.c_str());
        CopyTextButton("Copy Summary", text);
    }

    void DrawAddressTable()
    {
        const auto& addresses = EngineAddressMap::KnownAddresses();
        ImGui::Text("Known functions/globals: %d", static_cast<int>(addresses.size()));

        if (!ImGui::BeginTable("##KnownEngineAddresses", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 260)))
            return;

        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("IDA");
        ImGui::TableSetupColumn("Runtime");
        ImGui::TableSetupColumn("Safety");
        ImGui::TableSetupColumn("Notes");
        ImGui::TableHeadersRow();

        for (const auto& item : addresses)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            if (ImGui::Selectable(item.Name, false, ImGuiSelectableFlags_SpanAllColumns))
            {
                std::string line = std::string(item.Name) + " = " + EngineAddressMap::FormatAddress(item.IdaAddress);
                ImGui::SetClipboardText(line.c_str());
            }
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(EngineAddressMap::FormatAddress(item.IdaAddress).c_str());
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(EngineAddressMap::FormatAddress(EngineAddressMap::Rebase(item.IdaAddress)).c_str());
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(EngineAddressMap::SafetyName(item.Safety));
            ImGui::TableNextColumn();
            ImGui::TextWrapped("%s", item.Notes ? item.Notes : "");
        }

        ImGui::EndTable();
    }

    void DrawChunkTypeTable()
    {
        const auto& chunks = EngineAddressMap::KnownChunkTypes();
        ImGui::Text("Known chunk types: %d", static_cast<int>(chunks.size()));

        if (!ImGui::BeginTable("##KnownChunkTypes", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable, ImVec2(0, 180)))
            return;

        ImGui::TableSetupColumn("Chunk");
        ImGui::TableSetupColumn("Type Object");
        ImGui::TableSetupColumn("Register Fn");
        ImGui::TableSetupColumn("Factory Fn");
        ImGui::TableSetupColumn("Notes");
        ImGui::TableHeadersRow();

        for (const auto& item : chunks)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn(); ImGui::TextUnformatted(item.ChunkName);
            ImGui::TableNextColumn(); ImGui::TextUnformatted(EngineAddressMap::FormatAddress(item.TypeObjectIda).c_str());
            ImGui::TableNextColumn(); ImGui::TextUnformatted(EngineAddressMap::FormatAddress(item.RegisterFunctionIda).c_str());
            ImGui::TableNextColumn(); ImGui::TextUnformatted(EngineAddressMap::FormatAddress(item.FactoryFunctionIda).c_str());
            ImGui::TableNextColumn(); ImGui::TextWrapped("%s", item.Notes ? item.Notes : "");
        }

        ImGui::EndTable();
    }

    void DrawRuntimeQueryBox()
    {
        const auto& chunks = EngineAddressMap::KnownChunkTypes();
        if (g_SelectedChunkType < 0 || g_SelectedChunkType >= static_cast<int>(chunks.size()))
            g_SelectedChunkType = 0;

        bool unsafe = EngineXfbinRuntime::IsUnsafeEngineCallsEnabled();
        if (ImGui::Checkbox("Enable unsafe engine calls", &unsafe))
            EngineXfbinRuntime::SetUnsafeEngineCallsEnabled(unsafe);
        ImGui::SameLine();
        ImGui::TextDisabled("Leave off unless EXE/signatures match exactly.");

        ImGui::InputText("XFBIN path", g_TestPath, sizeof(g_TestPath));
        ImGui::InputText("Chunk name", g_TestChunkName, sizeof(g_TestChunkName));

        if (!chunks.empty())
        {
            std::vector<const char*> labels;
            labels.reserve(chunks.size());
            for (const auto& c : chunks)
                labels.push_back(c.ChunkName);
            ImGui::Combo("Chunk type", &g_SelectedChunkType, labels.data(), static_cast<int>(labels.size()));
        }

        if (ImGui::Button("Log/Get Loaded XFBIN", ImVec2(170, 24)))
            EngineXfbinRuntime::GetLoadedXfbin(g_TestPath);
        ImGui::SameLine();
        if (ImGui::Button("Log/Find Chunk", ImVec2(150, 24)) && !chunks.empty())
            EngineXfbinRuntime::FindChunkInLoadedXfbin(g_TestPath, chunks[g_SelectedChunkType].TypeObjectIda, g_TestChunkName, 0);
        ImGui::SameLine();
        if (ImGui::Button("Log/Has Chunk", ImVec2(140, 24)) && !chunks.empty())
            EngineXfbinRuntime::HasChunkInLoadedXfbin(g_TestPath, chunks[g_SelectedChunkType].TypeObjectIda, g_TestChunkName, 0);

        ImGui::TextWrapped("Status: %s", EngineXfbinRuntime::LastStatus().c_str());
    }
}

namespace EngineResearchUI
{
    void DrawPanel()
    {
        DrawCapabilityBox();

        if (ImGui::CollapsingHeader("Runtime XFBIN Query Wrappers", ImGuiTreeNodeFlags_DefaultOpen))
            DrawRuntimeQueryBox();

        if (ImGui::CollapsingHeader("Known Chunk Types", ImGuiTreeNodeFlags_DefaultOpen))
            DrawChunkTypeTable();

        if (ImGui::CollapsingHeader("Known Engine Addresses", ImGuiTreeNodeFlags_DefaultOpen))
            DrawAddressTable();
    }
}
