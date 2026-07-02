#include "DX11OverlayInternal.h"
#include "StageEditor.h"
#include "EngineResearchUI.h"
#include "EngineAddressMap.h"
#include "EngineXfbinRuntime.h"
#include "RuntimeAssetTelemetry.h"
#include "EngineRuntimeResearch.h"
#include "EngineStageObjectResearch.h"

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    bool g_Open = false;
    bool g_F2WasDown = false;
    int g_SelectedStageIndex = -1;
    int g_SelectedObjectIndex = -1;
    char g_ManualXfbinPath[260] = "data/stage/sp23a.xfbin";
    char g_MeshName[128] = "sp23a_forest";
    bool g_AnimatedMeshNoCollision = true;

    struct StageObjectEntry
    {
        std::string Name;
        std::string Type;
        uintptr_t RuntimeAddress;
    };

    std::vector<StageObjectEntry> g_Objects;

    const AssetBrowser::AssetEntry* SelectedStageAsset()
    {
        const auto& assets = AssetBrowser::GetAssets();
        if (g_SelectedStageIndex < 0 || g_SelectedStageIndex >= static_cast<int>(assets.size()))
            return nullptr;
        return &assets[g_SelectedStageIndex];
    }

    void PushMockObject(const char* name, const char* type, uintptr_t address)
    {
        StageObjectEntry e{};
        e.Name = name ? name : "object";
        e.Type = type ? type : "Unknown";
        e.RuntimeAddress = address;
        g_Objects.push_back(e);
    }


    void DrawHeaderBar()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
        ImGui::TextUnformatted("NS3 Full Burst Stage Editor");
        ImGui::SameLine();
        ImGui::TextDisabled("F2 standalone overlay");
        ImGui::SameLine(ImGui::GetWindowWidth() - 165.0f);
        if (ImGui::Button("Copy Next Sub", ImVec2(130, 24)))
            ImGui::SetClipboardText(EngineStageObjectResearch::NextSub());
        ImGui::PopStyleVar();
        ImGui::Separator();
    }

    void DrawSymbolTable(const char* id, const EngineRuntimeResearch::RuntimeSymbol* items, int count)
    {
        if (ImGui::BeginTable(id, 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 180)))
        {
            ImGui::TableSetupColumn("Sub / Status", ImGuiTableColumnFlags_WidthFixed, 135.0f);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 210.0f);
            ImGui::TableSetupColumn("What it does", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableHeadersRow();
            for (int i = 0; i < count; ++i)
            {
                const auto& it = items[i];
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                if (ImGui::Selectable(it.Address, false, ImGuiSelectableFlags_SpanAllColumns))
                    ImGui::SetClipboardText(it.Address);
                ImGui::TableSetColumnIndex(1); ImGui::TextUnformatted(it.Name);
                ImGui::TableSetColumnIndex(2); ImGui::TextWrapped("%s", it.Purpose);
                ImGui::TableSetColumnIndex(3); ImGui::TextUnformatted(it.Risk);
            }
            ImGui::EndTable();
        }
    }


    void DrawStageSymbolTable(const char* id, const EngineStageObjectResearch::StageSymbol* items, int count)
    {
        if (ImGui::BeginTable(id, 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 190)))
        {
            ImGui::TableSetupColumn("Sub / Status", ImGuiTableColumnFlags_WidthFixed, 135.0f);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 245.0f);
            ImGui::TableSetupColumn("What it does", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed, 125.0f);
            ImGui::TableHeadersRow();
            for (int i = 0; i < count; ++i)
            {
                const auto& it = items[i];
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                if (ImGui::Selectable(it.Address, false, ImGuiSelectableFlags_SpanAllColumns))
                    ImGui::SetClipboardText(it.Address);
                ImGui::TableSetColumnIndex(1); ImGui::TextUnformatted(it.Name);
                ImGui::TableSetColumnIndex(2); ImGui::TextWrapped("%s", it.Purpose);
                ImGui::TableSetColumnIndex(3); ImGui::TextUnformatted(it.Risk);
            }
            ImGui::EndTable();
        }
    }

    void DrawStageObjectResearch()
    {
        int count = 0;
        ImGui::SeparatorText("Stage Object Pipeline Found");
        ImGui::TextWrapped("The engine now has confirmed gameplay paths that build RuntimeModel objects from stage/character/effect descriptors. Real spawn stays disabled until the owning stage object list is identified.");

        const auto* stage = EngineStageObjectResearch::StageObjectPipeline(&count);
        if (ImGui::CollapsingHeader("Stage Object Creation", ImGuiTreeNodeFlags_DefaultOpen))
            DrawStageSymbolTable("##StageObjectPipeline", stage, count);

        const auto* replace = EngineStageObjectResearch::ReplacementPipeline(&count);
        if (ImGui::CollapsingHeader("Model Replacement / Runtime Hooks", ImGuiTreeNodeFlags_DefaultOpen))
            DrawStageSymbolTable("##ReplacementPipeline", replace, count);

        const auto* game = EngineStageObjectResearch::GameplayLoaders(&count);
        if (ImGui::CollapsingHeader("Gameplay Loaders Using RuntimeModel"))
            DrawStageSymbolTable("##GameplayLoaders", game, count);

        const auto* next = EngineStageObjectResearch::NextTargets(&count);
        if (ImGui::CollapsingHeader("Next IDA Targets", ImGuiTreeNodeFlags_DefaultOpen))
            DrawStageSymbolTable("##StageNextTargets", next, count);
    }

    void DrawStandaloneStatus()
    {
        ImGui::BeginChild("##StageEditorStatusCards", ImVec2(0, 72), true);
        ImGui::Columns(3, nullptr, false);
        ImGui::TextUnformatted("Mode");
        ImGui::TextColored(ImVec4(0.45f, 0.95f, 0.55f, 1.0f), "Safe / Staged");
        ImGui::NextColumn();
        ImGui::TextUnformatted("Input");
        ImGui::TextColored(ImVec4(0.45f, 0.75f, 1.0f, 1.0f), "F2 captures mouse");
        ImGui::NextColumn();
        ImGui::TextUnformatted("Next IDA");
        ImGui::TextColored(ImVec4(1.0f, 0.80f, 0.35f, 1.0f), "%s", EngineStageObjectResearch::NextSub());
        ImGui::Columns(1);
        ImGui::EndChild();
    }

    void DrawStageFileList()
    {
        const auto& assets = AssetBrowser::GetAssets();

        ImGui::Text("File List (Loaded by Framework)");
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 70.0f);
        ImGui::InputText("Path", g_ManualXfbinPath, sizeof(g_ManualXfbinPath));

        if (ImGui::Button("Load File", ImVec2(88, 23)))
        {
            EngineXfbinRuntime::GetLoadedXfbin(g_ManualXfbinPath);
            AssetNotification::PushInfo("Stage Editor", "Load request logged. Unsafe engine calls are still gated.");
        }

        ImGui::BeginChild("##StageEditorFileList", ImVec2(0, 140), true);

        int shown = 0;
        for (int i = 0; i < static_cast<int>(assets.size()); ++i)
        {
            const auto& a = assets[i];
            if (a.Type != AssetBrowser::AssetType::Stage)
                continue;

            std::string label = a.VirtualPath.empty() ? a.Name : a.VirtualPath;
            if (label.empty())
                label = a.FullPath;

            if (ImGui::Selectable(label.c_str(), g_SelectedStageIndex == i))
            {
                g_SelectedStageIndex = i;
                strncpy_s(g_ManualXfbinPath, label.c_str(), _TRUNCATE);
            }
            ++shown;
        }

        if (shown == 0)
            ImGui::TextDisabled("No stage assets indexed yet. Run Assets > Async Rescan first.");

        ImGui::EndChild();

        if (ImGui::Button("Unload", ImVec2(70, 23)))
            AssetNotification::PushWarning("Stage Editor", "Unload is staged only until ReleaseLoadedXfbin signature is verified.");
        ImGui::SameLine();
        if (ImGui::Button("Unload All", ImVec2(90, 23)))
        {
            g_Objects.clear();
            AssetNotification::PushWarning("Stage Editor", "Cleared staged object list. Engine release is still disabled.");
        }
    }

    void DrawMeshSpawnBox()
    {
        ImGui::SeparatorText("Mesh / Hit");
        ImGui::InputText("Mesh Name", g_MeshName, sizeof(g_MeshName));
        ImGui::Checkbox("Animated Mesh (No Collision)", &g_AnimatedMeshNoCollision);
        ImGui::SameLine();
        if (ImGui::Button("Spawn", ImVec2(72, 23)))
        {
            PushMockObject(g_MeshName, g_AnimatedMeshNoCollision ? "ccStageClump / animated" : "ccStageClump", 0);
            AssetNotification::PushInfo("Stage Editor", "Spawn staged. Need scene graph/register function before live world spawn.");
        }

        if (ImGui::Button("Spawn Test", ImVec2(96, 23)))
        {
            PushMockObject("sp23a", "ccStageClump", 0x2607D5CCBE0ull);
            PushMockObject("sp23a_forest", "ccStageClump", 0x2607D5CE260ull);
            AssetNotification::PushSuccess("Stage Editor", "Added test object entries.");
        }
    }

    void DrawObjectList()
    {
        ImGui::SeparatorText("Object List");
        ImGui::BeginChild("##StageEditorObjectList", ImVec2(0, 145), true);

        for (int i = 0; i < static_cast<int>(g_Objects.size()); ++i)
        {
            const auto& obj = g_Objects[i];
            std::ostringstream label;
            label << obj.Name << " [" << obj.Type << "]";
            if (obj.RuntimeAddress)
                label << " : " << EngineAddressMap::FormatAddress(obj.RuntimeAddress);

            if (ImGui::Selectable(label.str().c_str(), g_SelectedObjectIndex == i))
                g_SelectedObjectIndex = i;
        }

        if (g_Objects.empty())
            ImGui::TextDisabled("No staged objects yet.");

        ImGui::EndChild();

        if (ImGui::Button("Up", ImVec2(45, 23)) && g_SelectedObjectIndex > 0)
        {
            std::swap(g_Objects[g_SelectedObjectIndex], g_Objects[g_SelectedObjectIndex - 1]);
            --g_SelectedObjectIndex;
        }
        ImGui::SameLine();
        if (ImGui::Button("Down", ImVec2(60, 23)) && g_SelectedObjectIndex >= 0 && g_SelectedObjectIndex + 1 < static_cast<int>(g_Objects.size()))
        {
            std::swap(g_Objects[g_SelectedObjectIndex], g_Objects[g_SelectedObjectIndex + 1]);
            ++g_SelectedObjectIndex;
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete Selected", ImVec2(130, 23)) && g_SelectedObjectIndex >= 0 && g_SelectedObjectIndex < static_cast<int>(g_Objects.size()))
        {
            g_Objects.erase(g_Objects.begin() + g_SelectedObjectIndex);
            if (g_SelectedObjectIndex >= static_cast<int>(g_Objects.size()))
                g_SelectedObjectIndex = static_cast<int>(g_Objects.size()) - 1;
        }
    }

    void DrawWhatWorksNow()
    {
        int count = 0;
        const auto* caps = EngineRuntimeResearch::CurrentCapabilities(&count);
        ImGui::SeparatorText("Current Working State");
        DrawSymbolTable("##CurrentCapabilities", caps, count);
    }

    void DrawNextIdaTargets()
    {
        ImGui::SeparatorText("Next Sub To Go To In IDA");
        ImGui::TextWrapped("%s", EngineRuntimeResearch::NextSubReason());

        int count = 0;
        const auto* render = EngineRuntimeResearch::RenderGraphSymbols(&count);
        if (ImGui::CollapsingHeader("Render Graph / Scene Owner Targets", ImGuiTreeNodeFlags_DefaultOpen))
            DrawSymbolTable("##RenderGraphTargets", render, count);

        const auto* runtime = EngineRuntimeResearch::RuntimeModelSymbols(&count);
        if (ImGui::CollapsingHeader("Runtime Model / Node Targets", ImGuiTreeNodeFlags_DefaultOpen))
            DrawSymbolTable("##RuntimeModelTargets", runtime, count);

        const auto* scene = EngineRuntimeResearch::SceneOwnerTargets(&count);
        if (ImGui::CollapsingHeader("XREF Targets To Find Scene Manager", ImGuiTreeNodeFlags_DefaultOpen))
            DrawSymbolTable("##SceneOwnerTargets", scene, count);
    }
}

namespace StageEditor
{
    void Init()
    {
        g_Open = false;
        g_F2WasDown = false;
        g_SelectedStageIndex = -1;
        g_SelectedObjectIndex = -1;
    }

    void PollHotkeys()
    {
        const bool f2Down = (GetAsyncKeyState(VK_F2) & 0x8000) != 0;
        if (f2Down && !g_F2WasDown)
        {
            g_Open = !g_Open;
            Logger::Info(std::string("Stage Editor ") + (g_Open ? "opened" : "closed") + " by F2");
        }
        g_F2WasDown = f2Down;
    }

    void SetOpen(bool open)
    {
        g_Open = open;
    }

    bool IsOpen()
    {
        return g_Open;
    }

    bool WantsInputCapture()
    {
        return g_Open;
    }

    void DrawEmbeddedTools()
    {
        if (ImGui::Button("Open Stage Editor (F2)", ImVec2(190, 24)))
            g_Open = true;
        ImGui::SameLine();
        if (ImGui::Button("Copy Next IDA Target", ImVec2(170, 24)))
            ImGui::SetClipboardText(EngineStageObjectResearch::NextSub());

        DrawWhatWorksNow();
        DrawStageObjectResearch();
        DrawNextIdaTargets();
    }

    void DrawWindow()
    {
        if (!g_Open)
            return;

        ImGui::SetNextWindowSize(ImVec2(760, 660), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(48, 48), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin("Stage Editor / Runtime Tools", &g_Open, ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
            return;
        }

        DrawHeaderBar();
        DrawStandaloneStatus();

        if (ImGui::BeginTabBar("##StageEditorTabs"))
        {
            if (ImGui::BeginTabItem("Stage"))
            {
                ImGui::TextWrapped("Stage files and staged object actions. Real world spawn is disabled until scene manager insertion is confirmed.");
                DrawStageFileList();
                DrawMeshSpawnBox();
                DrawObjectList();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Objects"))
            {
                DrawObjectList();
                ImGui::SeparatorText("Inspector");
                if (g_SelectedObjectIndex >= 0 && g_SelectedObjectIndex < static_cast<int>(g_Objects.size()))
                {
                    const auto& obj = g_Objects[g_SelectedObjectIndex];
                    ImGui::Text("Name: %s", obj.Name.c_str());
                    ImGui::Text("Type: %s", obj.Type.c_str());
                    ImGui::Text("Runtime: %s", obj.RuntimeAddress ? EngineAddressMap::FormatAddress(obj.RuntimeAddress).c_str() : "staged only");
                    ImGui::TextDisabled("Transform gizmo will unlock after scene/world owner is found.");
                }
                else
                {
                    ImGui::TextDisabled("Select or stage an object first.");
                }
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Stage Systems"))
            {
                DrawStageObjectResearch();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Research"))
            {
                DrawWhatWorksNow();
                DrawNextIdaTargets();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Engine Map"))
            {
                EngineResearchUI::DrawPanel();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}
