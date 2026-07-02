#include "DX11OverlayInternal.h"
#include "EngineRuntimeResearch.h"

namespace
{
    EngineRuntimeResearch::RuntimeSymbol g_RuntimeModel[] =
    {
        { "sub_140687350", "RuntimeNode::Constructor", "Creates one live runtime node with transform/state/visibility fields.", "Safe to log only" },
        { "sub_140687790", "RuntimeNode::BindChunk", "Binds one parsed chunk/node into a RuntimeNode and copies base transform.", "Safe to log only" },
        { "sub_140687950", "RuntimeNode::SetParent", "Links runtime parent/child hierarchy and marks parent dirty.", "Safe to log only" },
        { "sub_140687910", "RuntimeNode::SetTransform", "Copies node transform and marks owning RuntimeModel dirty.", "Safe to log only" },
        { "sub_140687820", "RuntimeNode::Finalize", "Finalizes one runtime node after parent/transform setup.", "Safe to log only" },
        { "sub_14068B540", "RuntimeModel::BuildFromChunk", "Main bridge from ccStageClump/chunk to live RuntimeModel.", "Do not call manually yet" },
        { "sub_140689440", "RuntimeModel::BuildNodeHierarchy", "Allocates runtime node array and builds parent/child links.", "Do not call manually yet" },
        { "sub_1406898E0", "RuntimeModel::BuildDependencyGraph", "Builds material/model/dependency runtime references.", "Do not call manually yet" },
        { "sub_14068B960", "RuntimeModel::BuildLODGraph", "Finds *_lod* chunks and builds LOD switching lists.", "Safe to inspect" },
        { "sub_14068A930", "RuntimeModel::BuildBoneRuntime", "Creates runtime bone transform helpers for model nodes.", "Safe to inspect" },
        { "sub_14068A800", "RuntimeModel::Destroy", "Destroy/free path for RuntimeModel, nodes, transforms, LOD, and dependencies.", "Reference only" },
    };

    EngineRuntimeResearch::RuntimeSymbol g_RenderGraph[] =
    {
        { "sub_1406CF530", "RuntimeModel::BuildRenderExtra", "Builds render-related extra graph from RuntimeModel and model extras.", "Next xref target" },
        { "sub_140722510", "RuntimeRenderGraph::Constructor", "Creates render graph helper used before sub_140722BE0/sub_140722880.", "Mapped" },
        { "sub_140722BE0", "RuntimeRenderGraph::AddDrawNode", "Adds render entries using indices, ids, and alpha/weight values.", "Inspect after constructor" },
        { "sub_140722880", "RuntimeRenderGraph::BuildLists", "Returns finalized render graph/root pointer.", "Inspect after AddEntry" },
        { "sub_140722730", "RuntimeRenderGraph::Destroy", "Cleanup path for render graph builder helper.", "Reference for safe cleanup" },
        { "sub_140721690", "RuntimeAttachment::Constructor", "Creates attachment/render item for RuntimeModel node.", "Inspect after render graph" },
        { "sub_140721760", "RuntimeAttachment::AttachToNode", "Links attachment to graph/list when flags require it.", "Inspect after constructor" },
        { "sub_1407223A0", "RuntimeAttachmentList::PushBack", "Generic append helper for attachment/runtime lists. Useful but not the world manager by itself.", "Mapped" },
    };

    EngineRuntimeResearch::RuntimeSymbol g_SceneOwner[] =
    {
        { "XREF sub_140687CC0", "RuntimeModel allocation callers", "Find every caller that allocates 0x340 RuntimeModel.", "High value" },
        { "XREF sub_14068B540", "RuntimeModel build callers", "Find who builds stage/character/effect models.", "High value" },
        { "XREF sub_1406CF530", "Render extra owner", "Find who stores render graph return pointer into a scene manager.", "Highest value" },
        { "XREF sub_140722510", "Render graph owner", "Find the manager wrapping render graph construction.", "Highest value" },
        { "XREF sub_14073AD30", "Wrapper load path", "Find object wrappers that call RuntimeModel::Initialize.", "High value" },
    };

    EngineRuntimeResearch::RuntimeSymbol g_Capabilities[] =
    {
        { "Ready", "F2 standalone Stage Editor", "F2 opens the editor without the F1 framework window.", "Enabled" },
        { "Ready", "Input capture", "When F2 editor is open, mouse/keyboard are routed to ImGui.", "Enabled" },
        { "Ready", "Asset browser foundation", "Can list indexed XFBIN/stage assets and stage load requests.", "Safe" },
        { "Ready", "Runtime model map", "Source has named addresses for XFBIN/chunks/runtime model/node/render graph.", "Safe" },
        { "Ready", "Object list UI", "Can stage object entries, reorder, delete, and prepare for real scene insertion.", "Safe" },
        { "Blocked", "Real spawn into world", "Needs scene/world owner that stores RuntimeModel pointers.", "Do not enable yet" },
        { "Blocked", "Blank world creation", "Needs scene manager + update/render owner + camera/transform write path.", "Do not enable yet" },
    };
}

namespace EngineRuntimeResearch
{
    const RuntimeSymbol* RuntimeModelSymbols(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_RuntimeModel) / sizeof(g_RuntimeModel[0]));
        return g_RuntimeModel;
    }

    const RuntimeSymbol* RenderGraphSymbols(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_RenderGraph) / sizeof(g_RenderGraph[0]));
        return g_RenderGraph;
    }

    const RuntimeSymbol* SceneOwnerTargets(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_SceneOwner) / sizeof(g_SceneOwner[0]));
        return g_SceneOwner;
    }

    const RuntimeSymbol* CurrentCapabilities(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_Capabilities) / sizeof(g_Capabilities[0]));
        return g_Capabilities;
    }

    const char* NextSub()
    {
        return "sub_1402E7038";
    }

    const char* NextSubReason()
    {
        return "StageObjectInstance::Initialize calls this right before RuntimeModel::SetTransform. It should reveal the position/rotation/scale layout needed for moving and eventually spawning stage objects.";
    }
}
