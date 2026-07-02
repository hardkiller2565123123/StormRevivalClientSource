#include "StdInc.h"
#include "StageEditorTools.h"
#include "BlankStageTools.h"
#include "DX11OverlayState.h"
#include "Logger.h"
#include "imgui.h"

#include <vector>
#include <string>
#include <ctime>
#include <cstring>
#include <sstream>
#include <cstdint>
#include <cstdio>

namespace
{
    bool g_Open = false;
    bool g_FrameworkOpen = false;
    bool g_F2WasDown = false;
    bool g_F3WasDown = false;
    int g_SelectedStageObject = 0;
    int g_SelectedResearchRow = 0;
    bool g_CaptureInput = true;
    bool g_ShowOnlyConfirmed = false;
    bool g_EnableUnsafeCalls = false;
    char g_StageObjectListPtr[32]{};
    char g_LastObjectAction[256] = "No live object action yet.";
    char g_ObjectSearch[128]{};
    char g_AssetPath[260] = "data/stage/example.xfbin";
    char g_ChunkName[128] = "stage_object_name";
    float g_EditPos[3] = { 0.0f, 0.0f, 0.0f };
    float g_EditRot[3] = { 0.0f, 0.0f, 0.0f };
    float g_EditScale[3] = { 1.0f, 1.0f, 1.0f };

    struct ResearchRow
    {
        const char* group;
        const char* name;
        const char* address;
        const char* status;
        const char* note;
    };

    static const ResearchRow kResearch[] =
    {
        { "XFBIN", "nuccXfbinParser_Read", "sub_14069D980", "confirmed", "Parses XFBIN header, string tables, chunk tables, dependency tables." },
        { "XFBIN", "XfbinManager_GetLoadedXfbin", "sub_140773FA0", "confirmed", "Finds already-loaded archive and increments ref count." },
        { "XFBIN", "XfbinManager_ReleaseLoadedXfbin", "sub_140774030", "confirmed", "Decrements archive ref count by path hash." },
        { "XFBIN", "Xfbin_FindChunkByTypeAndName", "sub_14069E450", "confirmed", "Looks up a chunk using type object plus hashed/name key." },
        { "Chunk", "ChunkTypeManager_Initialize", "sub_1406991B0", "confirmed", "Registers all nuccChunk classes at startup." },
        { "Chunk", "ChunkTypeManager_FindType", "sub_1406FFB20", "confirmed", "Finds chunk type object by type string/hash." },
        { "Chunk", "Create_nuccChunkModel", "sub_14069A620", "confirmed", "Allocates 0x138 and calls nuccChunkModel constructor." },
        { "Chunk", "Create_nuccChunkTexture", "sub_14069A950", "confirmed", "Factory for nuccChunkTexture." },
        { "Chunk", "Create_nuccChunkMaterial", "sub_14069A5F0", "confirmed", "Factory for nuccChunkMaterial." },
        { "RuntimeModel", "RuntimeModel_Constructor", "sub_140687CC0", "confirmed", "Allocates/initializes 0x340 RuntimeModel wrapper." },
        { "RuntimeModel", "RuntimeModel_BuildFromChunk", "sub_14068B540", "confirmed", "Main bridge from stage clump/chunk into runtime model." },
        { "RuntimeModel", "RuntimeModel_BuildNodeHierarchy", "sub_140689440", "confirmed", "Creates runtime nodes and parent/child links." },
        { "RuntimeModel", "RuntimeModel_InitializeRuntime", "sub_1406890C0", "confirmed", "Initializes model and all runtime nodes." },
        { "RuntimeModel", "RuntimeModel_BuildDependencyGraph", "sub_1406898E0", "confirmed", "Builds model/material/texture/dependency graph." },
        { "RuntimeModel", "RuntimeModel_BuildLODGraph", "sub_14068B960", "confirmed", "Finds and links _lod* objects." },
        { "RuntimeModel", "RuntimeModel_BuildBoneRuntime", "sub_14068A930", "confirmed", "Builds bone runtime objects and transform bindings." },
        { "RuntimeModel", "RuntimeModel_Destroy", "sub_14068A800", "confirmed", "Cleans runtime nodes, graph, transforms, LODs, resources." },
        { "RuntimeNode", "RuntimeNode_Constructor", "sub_140687350", "confirmed", "Runtime node constructor; local transforms, flags, parent pointer." },
        { "RuntimeNode", "RuntimeNode_InitFromChunk", "sub_140687790", "confirmed", "Binds node to source chunk and default transform." },
        { "RuntimeNode", "RuntimeNode_SetTransform", "sub_140687910", "confirmed", "Copies transform and marks model dirty." },
        { "RuntimeNode", "RuntimeNode_SetParent", "sub_140687950", "confirmed", "Sets parent pointer and dirty flags." },
        { "RenderGraph", "RuntimeRenderGraph_Constructor", "sub_140722510", "confirmed", "Builds render graph from RuntimeModel nodes; ignores blur nodes." },
        { "RenderGraph", "RuntimeRenderGraph_AddDrawNode", "sub_140722BE0", "confirmed", "Adds/updates a draw node for render passes." },
        { "RenderGraph", "RuntimeRenderGraph_BuildLists", "sub_140722880", "confirmed", "Builds draw lists in multiple passes." },
        { "RenderGraph", "RuntimeRenderGraph_TraverseAndBuild", "sub_140722910", "confirmed", "Recursively walks child/sibling render tree." },
        { "RenderGraph", "RuntimeDrawCommand_CreateOrUpdate", "sub_1407307D0", "confirmed", "Allocates 0x14 draw command and stores draw params." },
        { "Stage", "StageObjectInstance_InitializeFromDescriptor", "sub_1402E20A4", "confirmed", "Builds RuntimeModel for a stage object descriptor and creates stageobj controller." },
        { "Stage", "StageObjectManager_SpawnObjectFromDescriptor", "sub_1402CC0D8", "confirmed", "Allocates stage object wrapper, registers it, applies transform, pushes active list." },
        { "Stage", "StageObjectController_VisibilityCallback", "sub_1402E1DE4", "confirmed", "Stageobj callback; applies visibility/state flags." },
        { "Stage", "StageObjectController_Constructor", "sub_1402E1800", "confirmed", "Creates controller named stageobj and binds callback." },
        { "Stage", "StageObjectController_Activate", "sub_1402E6E28", "confirmed", "Activates controller." },
        { "Stage", "StageObjectInstance_SetTransformOverrideWorld", "sub_1402E7F38", "confirmed", "Enables flag 0x40 and stores transform override." },
        { "Stage", "StageObjectInstance_SetTransformOverrideLocal", "sub_1402E8228", "confirmed", "Enables flag 0x20 and stores local transform override." },
        { "Stage", "StageObjectInstance_SetDirectionOverride", "sub_1402E80D8", "confirmed", "Enables flag 0x100 and builds direction matrix." },
        { "Stage", "StageObjectInstance_SetRotationOverride", "sub_1402E7FA4", "confirmed", "Enables flag 0x1000 and builds rotation matrix." },
        { "Stage", "StageObject_BuildResolvedTransform", "sub_1402E7038", "confirmed", "Resolves final stage object transform from flags and overrides." },
        { "Runtime", "RuntimeModel_SetOwner", "sub_14068F3D0", "confirmed", "Stores owner pointer at runtime model +304." },
        { "Runtime", "RuntimeModel_SetResourceOverride", "sub_14068C700", "confirmed", "Stores replacement strings on runtime resource state." },
        { "Runtime", "RuntimeModel_SetVisibility", "sub_140689200", "confirmed", "Walks model nodes and writes visibility byte +208." },
        { "Runtime", "RuntimeModelCache_FindOrCreateEntry", "sub_14068F040", "confirmed", "Finds or inserts runtime model cache entry." },
        { "Runtime", "RuntimeModelCache_PushBackEntry", "sub_140691530", "confirmed", "Appends cache entry and increments count." },
        { "Math", "Matrix_MultiplyOrCompose", "sub_140685890", "confirmed", "Composes 4x4 transforms." },
        { "Math", "Matrix_ExtractTranslation", "sub_140686DE0", "confirmed", "Extracts translation/vector from matrix." },
        { "StageSpawn", "StageObjectInstance_Constructor", "sub_1402E18C4", "confirmed", "Constructs 0x160 stage object wrapper and default transforms/scale." },
        { "StageSpawn", "StageObjectRegistry_FindOrBindById", "sub_1403D3658", "confirmed", "Finds manager entry by object id and binds instance pointer if empty." },
        { "StageSpawn", "StageObjectInstance_SetBaseTransform", "sub_1402E22D0", "confirmed", "Applies base transform matrix or resets transform." },
        { "StageSpawn", "StageObjectController_Enable", "sub_1402E6F1C", "confirmed", "Enables the stageobj controller wrapper." },
        { "StageSpawn", "StageObjectActiveList_PushBack", "sub_1402CCBA8", "confirmed", "Pushes created stage object into active vector at a1+792." },
        { "StageSpawn", "StageObjectActiveList_Reserve", "sub_1402CC5E4", "confirmed", "Vector reserve/grow helper for active object list." },
        { "StageSpawn", "StageObjectActiveList_Reallocate", "sub_1402CC3F4", "confirmed", "Reallocates stage active object pointer vector." },
        { "StageSpawn", "StageObjectBase_Constructor", "sub_140739150", "confirmed", "Base constructor called by stage object wrapper constructor." },
        { "StageSpawn", "StageObjectInstance_ApplyBaseTransformMatrix", "sub_1402E234C", "confirmed", "Builds base transform matrix for spawned stage object." },
        { "BlankStage", "BossStage_SI31B_LoadObjects_VariantA", "sub_1402CA87C", "confirmed", "Contains vanilla si31b prop spawn loop using dummy names and StageObjectManager_SpawnObjectFromDescriptor." },
        { "BlankStage", "BossStage_SI31B_LoadObjects_VariantB", "sub_1402CBA28", "confirmed", "Second variant of same si31b stage population loop plus boss/camera setup." },
        { "BlankStage", "BossStage_SpawnMobDummyByName", "sub_1402CBFC0", "confirmed", "Spawns named mob dummy controller objects." },
        { "BlankStage", "BossStage_CacheMobDummyPositions", "sub_1402CB928", "confirmed", "Caches mob dummy positions; keep this for blank stage stability." },
        { "BlankStage", "BossStage_SpawnRandomMobDummy", "sub_1402CBE48", "confirmed", "Random mob dummy spawn batch; skip in full blank mode." },
        { "BlankStage", "BossStage_FinalizeLoad", "sub_1402CA7F0", "confirmed", "Final stage load call; keep this." },
        { "BlankStage", "BossStage_CreateBossUIManager", "sub_1402C9D80", "confirmed", "Creates ccUiBoss0510Manager; keep this." },
        { "BlankStage", "MobActiveList_PushBack", "sub_1402CCB2C", "confirmed", "Pushes created mob dummy into active mob vector at a1+840." },
        { "BlankStage", "MobActiveList_Reserve", "sub_1402CC568", "confirmed", "Vector reserve/grow helper for active mob list." },
        { "BlankStage", "MobDummyInstance_Constructor", "sub_1402DD818", "confirmed", "Constructs mob dummy instance wrapper." },
        { "BlankStage", "MobDummyInstance_Initialize", "sub_1402DDAFC", "confirmed", "Initializes mob controller and effect resources." },
        { "BlankStage", "BossStage_FindFreeMobDummySlot", "sub_1402CB6A0", "confirmed", "Finds safe dummy slot away from players/bosses." },
        { "Blackboard", "Blackboard_GetEntry", "sub_14074F050", "confirmed", "Gets blackboard entry by name." },
        { "Blackboard", "Blackboard_RegisterOrClearEntry", "sub_14074EE60", "confirmed", "Registers/clears blackboard entry by name." },
        { "Blackboard", "StageObjectList_LoadStageDefinition", "sub_1402E12E4", "confirmed", "Loads STAGE_SI31B definition in this boss-stage path." },
        { "Blackboard", "StageFileLoader_FindStageDefinition", "sub_1405BD690", "confirmed", "Finds stage definition by hashed name." },
        { "Blackboard", "StageObjectList_LoadDefinition", "sub_1405C05D0", "confirmed", "Loads/applies a stage definition object into StageObjectList." },
        { "Blackboard", "StageObjectList_SetActiveDefinition", "sub_1405BDB34", "confirmed", "Stores active definition pointer and id." },
        { "Global", "StageWorldContext", "qword_140B9F5E0", "candidate", "Global world/stage context. +6496 is stage object manager/list candidate." },

        { "StageList", "StageObjectList_ClearRuntimeEntries", "sub_1405C0590", "confirmed", "Calls StageObjectEntry_ClearAndDestroyGroups for each loaded entry." },
        { "StageList", "StageObjectList_UpdateAll", "sub_1405C06E4", "confirmed", "Generic any-stage update loop; checks raw+448 before updating object+8." },
        { "StageList", "StageObjectList_DrawAll", "sub_1405C0788", "confirmed", "Generic any-stage draw loop; checks raw+452 before drawing object+8." },
        { "StageList", "StageObjectList_GetObjectByIndex", "sub_1405C07E0", "confirmed", "Returns vector[index]+8 for StageObjectList objects." },
        { "StageList", "StageDefinition_BuildObjectEntries", "sub_1405BF104", "confirmed", "Builds generic object entries from stage definition using funcs_1405BF239." },
        { "StageList", "StageObjectEntry_UpdateGroups", "sub_1405BF55C", "confirmed", "Updates four group vectors inside one stage object entry." },
        { "StageList", "StageObjectEntry_DrawGroups", "sub_1405BF6F8", "confirmed", "Draws four group vectors inside one stage object entry." },
        { "StageList", "StageObjectEntry_ClearAndDestroyGroups", "sub_1405BED98", "confirmed", "Destroys all child group objects through virtual destructor; use only after hide testing." },
        { "StageList", "StageObjectEntry_AddDefaultProcessors", "sub_1405BF44C", "confirmed", "Adds default processors depending on stage definition type." },
        { "StageList", "StageDefinition_ApplyGlobalBattleTransforms", "sub_1405BECB0", "confirmed", "Copies battle/global transforms and applies collision/sequence state." },
        { "StageList", "StageObjectEntry_AddGroupTypeA", "sub_1405BEA74", "confirmed", "Creates group object if chunk exists and pushes into entry group at +264." },
        { "StageList", "StageObjectEntry_AddGroupTypeB", "sub_1405BEB28", "confirmed", "Creates group object if chunk exists and pushes into entry group at +312." },
        { "StageList", "StageObjectEntry_AddGroupTypeC", "sub_1405BEBDC", "confirmed", "Creates group object if chunk exists and pushes into entry group at +360." },
    };

    static const char* kNextSubs[] =
    {
        "sub_1405C01F0  // push group object into StageObjectEntry group vector",
        "sub_1405BCBAC  // stage group object constructor",
        "sub_1405BCC2C  // stage group object init from chunk/path",
        "sub_1405BF930  // test if chunk exists for stage group",
        "sub_1402EEC24  // player/boss visibility lookup used by sub_1402F1E00",
        "sub_1402F1D30  // player/boss visibility apply used by sub_1402F1E00"
    };

    struct FakeObject
    {
        const char* name;
        const char* type;
        const char* status;
    };

    static const FakeObject kObjectTemplates[] =
    {
        { "StageObjectDescriptor", "stageobj", "ready to inspect" },
        { "RuntimeModel", "0x340 object", "constructor mapped" },
        { "RuntimeNode", "hierarchy node", "tree mapped" },
        { "RuntimeRenderGraph", "draw graph", "render passes mapped" },
        { "RuntimeModelCacheEntry", "cache", "entry list mapped" },
    };

    void DrawHeader()
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.42f, 0.72f, 1.0f, 1.0f));
        ImGui::TextUnformatted("NS3 Full Burst Stage Editor");
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::TextDisabled("F2 Stage Editor | F3 Framework Tools | safe mode enabled");
        ImGui::Separator();
    }

    void DrawStatusCard(const char* title, const char* value, const char* note)
    {
        ImGui::BeginChild(title, ImVec2(0, 72), true);
        ImGui::TextColored(ImVec4(0.55f, 0.78f, 1.0f, 1.0f), "%s", title);
        ImGui::TextWrapped("%s", value);
        ImGui::TextDisabled("%s", note);
        ImGui::EndChild();
    }

    void DrawDashboard()
    {
        ImGui::Columns(3, nullptr, false);
        DrawStatusCard("Asset Pipeline", "XFBIN -> Chunk -> RuntimeModel mapped", "Safe browser/logging can be built now.");
        ImGui::NextColumn();
        DrawStatusCard("Stage Objects", "Descriptor -> stageobj controller mapped", "Spawn path located; manager update loop next.");
        ImGui::NextColumn();
        DrawStatusCard("Blank Stage", "Safe gate mode ready", "Real blank stage needs live hooks wired.");
        ImGui::Columns(1);

        ImGui::Spacing();
        ImGui::TextWrapped("Current working features: F2 Stage Editor, F3 Framework Tools, compact debug HUD, research browser, any-stage blank mode gates, safe transform editor UI, stage/mob counters, and logging. Real engine spawning/removal stays disabled until live hook signatures are verified.");

        ImGui::Separator();
        ImGui::Checkbox("Capture mouse/keyboard while F2/F3 tools are open", &g_CaptureInput);
        ImGui::SameLine();
        ImGui::Checkbox("Show only confirmed research", &g_ShowOnlyConfirmed);
        ImGui::Checkbox("Enable unsafe engine calls", &g_EnableUnsafeCalls);
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Disabled by default. Do not turn this on until function signatures and thiscall/fastcall arguments are verified.");
    }

    void DrawAssets()
    {
        ImGui::Text("Safe Asset Browser Prototype");
        ImGui::Separator();
        ImGui::InputText("XFBIN path", g_AssetPath, IM_ARRAYSIZE(g_AssetPath));
        ImGui::InputText("Chunk name", g_ChunkName, IM_ARRAYSIZE(g_ChunkName));

        if (ImGui::Button("Log asset lookup plan"))
        {
            Logger::Info(std::string("StageEditor asset lookup plan: ") + g_AssetPath + " :: " + g_ChunkName);
        }
        ImGui::SameLine();
        ImGui::Button("Live lookup disabled");
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Live engine lookup is disabled until addresses/calling convention are finalized.");

        ImGui::Separator();
        ImGui::BulletText("Use XfbinManager_GetLoadedXfbin for loaded archive lookup.");
        ImGui::BulletText("Use Xfbin_FindChunkByTypeAndName for model/material/texture chunk lookup.");
        ImGui::BulletText("Use RuntimeModel_BuildFromChunk only after stage manager owner is verified.");
    }

    void DrawObjects()
    {
        ImGui::Text("Stage Object Inspector Prototype");
        ImGui::Separator();
        ImGui::InputText("Search", g_ObjectSearch, IM_ARRAYSIZE(g_ObjectSearch));
        ImGui::BeginChild("##objectList", ImVec2(260, 0), true);
        for (int i = 0; i < static_cast<int>(IM_ARRAYSIZE(kObjectTemplates)); ++i)
        {
            if (ImGui::Selectable(kObjectTemplates[i].name, g_SelectedStageObject == i))
                g_SelectedStageObject = i;
        }
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("##objectDetails", ImVec2(0, 0), true);
        const FakeObject& obj = kObjectTemplates[g_SelectedStageObject];
        ImGui::Text("Name: %s", obj.name);
        ImGui::Text("Type: %s", obj.type);
        ImGui::Text("Status: %s", obj.status);
        ImGui::Separator();
        ImGui::Text("Transform editor design");
        ImGui::DragFloat3("Position", g_EditPos, 0.05f);
        ImGui::DragFloat3("Rotation", g_EditRot, 0.25f);
        ImGui::DragFloat3("Scale", g_EditScale, 0.01f, 0.01f, 100.0f);
        if (ImGui::Button("Log transform edit"))
            Logger::Info("StageEditor transform edit logged. Live write disabled until stage object pointers are verified.");
        ImGui::SameLine();
        ImGui::Button("Apply disabled");
        ImGui::EndChild();
    }

    void DrawResearch()
    {
        ImGui::Text("Research Map");
        ImGui::Separator();
        if (ImGui::BeginTable("##research", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 0)))
        {
            ImGui::TableSetupColumn("Group", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 270.0f);
            ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthFixed, 145.0f);
            ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 95.0f);
            ImGui::TableSetupColumn("Note");
            ImGui::TableHeadersRow();

            for (int i = 0; i < static_cast<int>(IM_ARRAYSIZE(kResearch)); ++i)
            {
                const ResearchRow& row = kResearch[i];
                if (g_ShowOnlyConfirmed && strcmp(row.status, "confirmed") != 0)
                    continue;
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted(row.group);
                ImGui::TableSetColumnIndex(1); ImGui::TextUnformatted(row.name);
                ImGui::TableSetColumnIndex(2); ImGui::TextUnformatted(row.address);
                ImGui::TableSetColumnIndex(3); ImGui::TextUnformatted(row.status);
                ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", row.note);
            }
            ImGui::EndTable();
        }
    }


    bool ParseHexPointer(const char* text, std::uintptr_t& out)
    {
        out = 0;
        if (!text || !text[0])
            return false;
#if defined(_MSC_VER)
        return sscanf_s(text, "%llx", &out) == 1;
#else
        return std::sscanf(text, "%llx", &out) == 1;
#endif
    }

    void StoreObjectAction(const char* prefix, const BlankStageTools::ListOperationResult& r)
    {
#if defined(_MSC_VER)
        sprintf_s(g_LastObjectAction, "%s: success=%s total=%u changed=%u invalid=%u",
            prefix, r.success ? "yes" : "no", r.total, r.changed, r.invalid);
#else
        std::snprintf(g_LastObjectAction, sizeof(g_LastObjectAction), "%s: success=%s total=%u changed=%u invalid=%u",
            prefix, r.success ? "yes" : "no", r.total, r.changed, r.invalid);
#endif
    }

    void DrawBlankStage()
    {
        BlankStageTools::State& st = BlankStageTools::GetState();

        ImGui::TextColored(ImVec4(0.45f, 0.78f, 1.0f, 1.0f), "Blank / Clean Stage");
        ImGui::SameLine();
        ImGui::TextDisabled("confirmed offsets only");
        ImGui::Separator();

        if (ImGui::CollapsingHeader("1. Load-time blank mode", ImGuiTreeNodeFlags_DefaultOpen))
        {
            int mode = static_cast<int>(st.mode);
            const char* modes[] = { "Off", "Blank props only", "Blank props + mobs" };
            if (ImGui::Combo("Mode", &mode, modes, IM_ARRAYSIZE(modes)))
                BlankStageTools::SetMode(static_cast<BlankStageTools::Mode>(mode));

            ImGui::Checkbox("Any-stage mode", &st.anyStageMode);
            ImGui::SameLine();
            ImGui::Checkbox("Hide instead of destroy", &st.hideInsteadOfDestroy);
            ImGui::SameLine();
            ImGui::Checkbox("Log hook decisions", &st.logDecisions);

            ImGui::Columns(3, nullptr, false);
            DrawStatusCard("Props skipped", std::to_string(st.skippedStageObjects).c_str(), "sub_1402CC0D8 gate");
            ImGui::NextColumn();
            DrawStatusCard("Mob dummies skipped", std::to_string(st.skippedMobDummies).c_str(), "sub_1402CBFC0 gate");
            ImGui::NextColumn();
            DrawStatusCard("Random mobs skipped", std::to_string(st.skippedRandomMobs).c_str(), "sub_1402CBE48 gate");
            ImGui::Columns(1);

            if (ImGui::Button("Reset skip counters"))
                BlankStageTools::ResetCounters();
            ImGui::SameLine();
            if (ImGui::Button("Log hook plan"))
                BlankStageTools::LogPlan();
        }

        if (ImGui::CollapsingHeader("2. Current-stage object controls", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextWrapped("Use this with a verified StageObjectList pointer. The buttons write only confirmed flags: raw+448 update and raw+452 draw. This hides/shows objects without freeing memory.");
            ImGui::InputText("StageObjectList pointer", g_StageObjectListPtr, IM_ARRAYSIZE(g_StageObjectListPtr), ImGuiInputTextFlags_CharsHexadecimal);

            std::uintptr_t listPtr = 0;
            const bool validPtr = ParseHexPointer(g_StageObjectListPtr, listPtr);
            if (validPtr)
            {
                const unsigned int count = BlankStageTools::CountStageObjectList(listPtr);
                BlankStageTools::UpdateActiveCounts(count, st.activeMobObjects);
                ImGui::Text("Detected StageObjectList entries: %u", count);
            }
            else
            {
                ImGui::TextDisabled("Paste a StageObjectList address as hex, example: 140B9F5E0");
            }

            ImGui::BeginDisabled(!validPtr);
            if (ImGui::Button("Hide all stage objects", ImVec2(190.0f, 28.0f)))
            {
                const auto r = BlankStageTools::SetStageObjectListDrawUpdate(listPtr, false);
                StoreObjectAction("Hide all stage objects", r);
            }
            ImGui::SameLine();
            if (ImGui::Button("Show all stage objects", ImVec2(190.0f, 28.0f)))
            {
                const auto r = BlankStageTools::SetStageObjectListDrawUpdate(listPtr, true);
                StoreObjectAction("Show all stage objects", r);
            }
            ImGui::EndDisabled();
            ImGui::TextWrapped("Last action: %s", g_LastObjectAction);

            ImGui::Separator();
            ImGui::TextDisabled("Real clear/delete is intentionally not wired yet. Confirmed destructor path: sub_1405BED98 clears a StageObjectEntry groups, but hide/show flags are safer for testing.");
        }

        if (ImGui::CollapsingHeader("3. Confirmed object/list layout"))
        {
            ImGui::BulletText("StageObjectList +0x08 begin, +0x10 end, +0x18 capacity.");
            ImGui::BulletText("StageObjectList_GetObjectByIndex / sub_1405C07E0 returns rawEntry + 8.");
            ImGui::BulletText("StageObjectList_UpdateAll / sub_1405C06E4 checks rawEntry + 448.");
            ImGui::BulletText("StageObjectList_DrawAll / sub_1405C0788 checks rawEntry + 452.");
            ImGui::BulletText("StageObjectEntry_ClearAndDestroyGroups / sub_1405BED98 calls group object virtual destructors.");
        }

        if (ImGui::CollapsingHeader("4. Next IDA targets"))
        {
            for (int i = 0; i < static_cast<int>(IM_ARRAYSIZE(kNextSubs)); ++i)
                ImGui::BulletText("%s", kNextSubs[i]);
        }
    }


    const char* BlankModeName()
    {
        BlankStageTools::State& st = BlankStageTools::GetState();
        switch (st.mode)
        {
        case BlankStageTools::Mode::SkipVanillaProps: return "Props Only";
        case BlankStageTools::Mode::SkipPropsAndMobs: return "Props + Mobs";
        default: return "Off";
        }
    }

    unsigned int KnownResearchCount()
    {
        return static_cast<unsigned int>(IM_ARRAYSIZE(kResearch));
    }

    unsigned int KnownStageFunctionCount()
    {
        unsigned int count = 0;
        for (int i = 0; i < static_cast<int>(IM_ARRAYSIZE(kResearch)); ++i)
        {
            if (std::strcmp(kResearch[i].group, "Stage") == 0 ||
                std::strcmp(kResearch[i].group, "StageSpawn") == 0 ||
                std::strcmp(kResearch[i].group, "BlankStage") == 0 ||
                std::strcmp(kResearch[i].group, "StageList") == 0)
                ++count;
        }
        return count;
    }

    void DrawMiniDebugHud()
    {
        BlankStageTools::State& st = BlankStageTools::GetState();
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        (void)viewport;

        ImGui::SetNextWindowPos(ImVec2(8.0f, 34.0f), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.62f);
        ImGui::Begin("##NS3FBFrameworkMiniHud", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoNav);

        ImGui::TextColored(ImVec4(0.45f, 0.78f, 1.0f, 1.0f), "NS3FB Framework");
        ImGui::SameLine();
        ImGui::TextDisabled("F2");
        ImGui::Separator();
        ImGui::Text("Blank: %s", BlankModeName());
        ImGui::Text("Skipped props/mobs/random: %u / %u / %u",
            st.skippedStageObjects, st.skippedMobDummies, st.skippedRandomMobs);
        ImGui::Text("Active props/mobs: %u / %u", st.activeStageObjects, st.activeMobObjects);
        ImGui::Text("Known funcs: %u  Stage funcs: %u", KnownResearchCount(), KnownStageFunctionCount());
        ImGui::TextDisabled("F2 Editor / F3 Tools");
        ImGui::End();
    }

    void DrawCompactHome()
    {
        BlankStageTools::State& st = BlankStageTools::GetState();

        ImGui::TextColored(ImVec4(0.45f, 0.78f, 1.0f, 1.0f), "Framework Tools");
        ImGui::SameLine();
        ImGui::TextDisabled("safe research build");
        ImGui::Separator();

        ImGui::Columns(4, nullptr, false);
        DrawStatusCard("Blank Mode", BlankModeName(), "Arms hook gates only");
        ImGui::NextColumn();
        DrawStatusCard("Props Skipped", std::to_string(st.skippedStageObjects).c_str(), "Counter from hook gates");
        ImGui::NextColumn();
        DrawStatusCard("Research", std::to_string(KnownResearchCount()).c_str(), "Known functions mapped");
        ImGui::NextColumn();
        DrawStatusCard("Live Objects", "Pending", "Needs verified hooks");
        ImGui::Columns(1);

        ImGui::Spacing();
        ImGui::TextWrapped("Use F2 for stage editing/blanking/assets. Use F3 for framework research, IDA names, settings, and hook planning.");
    }


}

namespace StageEditorTools
{
    void UpdateHotkeys()
    {
        const bool f2Down = (GetAsyncKeyState(VK_F2) & 0x8000) != 0;
        if (f2Down && !g_F2WasDown)
        {
            g_Open = !g_Open;
            if (g_Open)
                Logger::Info("Stage Editor opened with F2");
        }
        g_F2WasDown = f2Down;

        const bool f3Down = (GetAsyncKeyState(VK_F3) & 0x8000) != 0;
        if (f3Down && !g_F3WasDown)
        {
            g_FrameworkOpen = !g_FrameworkOpen;
            if (g_FrameworkOpen)
                Logger::Info("Framework Tools opened with F3");
        }
        g_F3WasDown = f3Down;
    }

    bool IsOpen()
    {
        return g_Open || g_FrameworkOpen;
    }

    bool WantsInputCapture()
    {
        return (g_Open || g_FrameworkOpen) && g_CaptureInput;
    }

    void DrawFrame()
    {
        DrawMiniDebugHud();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        const float panelWidth = viewport->Size.x > 1100.0f ? 980.0f : viewport->Size.x - 32.0f;
        const float panelHeight = viewport->Size.y > 720.0f ? 610.0f : viewport->Size.y - 70.0f;
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;

        if (g_Open)
        {
            ImGui::SetNextWindowPos(ImVec2(10.0f, 58.0f), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowBgAlpha(0.94f);

            if (ImGui::Begin("NS3FB Stage Editor  (F2)", &g_Open, flags))
            {
                DrawHeader();
                if (ImGui::BeginTabBar("##stageEditorTabs", ImGuiTabBarFlags_Reorderable))
                {
                    if (ImGui::BeginTabItem("Home")) { DrawCompactHome(); ImGui::EndTabItem(); }
                    if (ImGui::BeginTabItem("Blank / Clean")) { DrawBlankStage(); ImGui::EndTabItem(); }
                    if (ImGui::BeginTabItem("Objects")) { DrawObjects(); ImGui::EndTabItem(); }
                    if (ImGui::BeginTabItem("Assets")) { DrawAssets(); ImGui::EndTabItem(); }
                    ImGui::EndTabBar();
                }
            }
            ImGui::End();
        }

        if (g_FrameworkOpen)
        {
            ImGui::SetNextWindowPos(ImVec2(46.0f, 86.0f), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowBgAlpha(0.94f);

            if (ImGui::Begin("NS3FB Framework Tools  (F3)", &g_FrameworkOpen, flags))
            {
                DrawHeader();
                if (ImGui::BeginTabBar("##frameworkToolsTabs", ImGuiTabBarFlags_Reorderable))
                {
                    if (ImGui::BeginTabItem("Dashboard")) { DrawDashboard(); ImGui::EndTabItem(); }
                    if (ImGui::BeginTabItem("Research Map")) { DrawResearch(); ImGui::EndTabItem(); }
                    if (ImGui::BeginTabItem("Blank Hook Plan")) { DrawBlankStage(); ImGui::EndTabItem(); }
                    ImGui::EndTabBar();
                }
            }
            ImGui::End();
        }
    }
}
