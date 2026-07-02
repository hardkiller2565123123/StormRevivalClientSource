#include "DX11OverlayInternal.h"
#include "EngineStageObjectResearch.h"

namespace
{
    EngineStageObjectResearch::StageSymbol g_GameplayLoaders[] =
    {
        { "sub_1402364A8", "RuntimeModelManager::ReplaceModelsByName", "Searches active runtime models, replaces model-name substrings, builds replacement RuntimeModel objects, then reattaches them.", "Do not call manually yet" },
        { "sub_140238700", "RuntimeModelManager::LoadRuntimeModelList", "Loops over model descriptors, finds ccStageClump chunks, builds RuntimeModel objects, and stores them by hashed name.", "Good hook/log target" },
        { "sub_14025474C", "BossCharacter::LoadResources", "Loads boss base model/effect resources and wires RuntimeModel + effect chunks together.", "Research only" },
        { "sub_140296ABC", "CharacterChain::Initialize", "Loads rkyuchain1 and creates a RuntimeModel used by a character/boss attachment.", "Research only" },
        { "sub_1402A2DC0", "BossTailSystem::Initialize", "Loads tail RuntimeModel objects and tail shadow/effect resources.", "Research only" },
        { "sub_1403065B8", "BossEffect::Initialize", "Loads si34d_fall and b06_e_blt_point00 using the same RuntimeModel/effect pipeline.", "Research only" },
        { "sub_1403A0D34", "RPGCharacterLoader::LoadCharacter", "Resolves RPG character IDs, loads character XFBIN/chunks, builds RuntimeModel, and attaches it to RPG runtime.", "Research only" },
    };

    EngineStageObjectResearch::StageSymbol g_StageObjectPipeline[] =
    {
        { "sub_1402D0B7C", "StageObject::Initialize", "Finds model/effect chunks, creates RuntimeModel or effect object, copies transform, initializes runtime, and marks the object active.", "High value" },
        { "sub_1402E20A4", "StageObjectManager::Create", "Creates a stageobj helper, finds the stage object's ccStageClump, builds RuntimeModel, initializes transforms/scale.", "Highest value" },
        { "sub_1402E7A20", "StageObjectInstance::Initialize", "Initializes one stage object instance from descriptor flags; creates RuntimeModel or effect object and applies properties.", "Highest value" },
        { "sub_1402E7038", "StageObjectInstance::BuildTransform", "Called before RuntimeModel::SetTransform; likely converts descriptor/world data into runtime transform.", "Next target" },
        { "sub_1402D0784", "StageObject::BuildTransform", "Same transform path used by StageObject::Initialize before runtime model setup.", "Next target" },
        { "sub_14068F3D0", "RuntimeController::BindModel", "Used after RuntimeModel creation to bind model into higher-level controller/effect wrapper.", "Next target" },
        { "sub_14068F040", "RuntimeController::ReplaceOrAttachModel", "Called after model replacement/load to attach the RuntimeModel into a manager/controller list.", "Next target" },
        { "sub_14068C700", "RuntimeModel::ApplyReplacementNames", "Applies source/destination names to RuntimeModel before replacement/attachment.", "Next target" },
    };

    EngineStageObjectResearch::StageSymbol g_ReplacementPipeline[] =
    {
        { "sub_14069E450", "Xfbin::FindChunkByTypeAndName", "Core chunk lookup used by every stage/character/effect loader found so far.", "Safe to wrap after signature verified" },
        { "sub_140687CC0", "RuntimeModel::Initialize", "Allocates/builds 0x340 RuntimeModel from ccStageClump chunk.", "Do not call until scene owner known" },
        { "sub_140689200", "RuntimeModel::SetVisibilityOrMode", "Called after replacement/model creation with a flag byte; likely toggles a render/runtime mode.", "Next target" },
        { "sub_14068B200", "RuntimeModel::FindChunksByType", "Finds runtime nodes/chunks of a type inside a RuntimeModel.", "Good inspector target" },
        { "sub_14068B360", "RuntimeModel::FindChunksByWildcard", "Finds runtime nodes by type and wildcard string, used for LOD/hide operations.", "Good inspector target" },
    };

    EngineStageObjectResearch::StageSymbol g_NextTargets[] =
    {
        { "sub_1402E7038", "StageObjectInstance::BuildTransform", "Called right before RuntimeModel::SetTransform in sub_1402E7A20. This should expose position/rotation/scale layout.", "NEXT SUB" },
        { "sub_1402D0784", "StageObject::BuildTransform", "Same idea for the simpler StageObject path.", "After 2E7038" },
        { "sub_14068F3D0", "RuntimeController::BindModel", "May reveal the higher-level owner/controller list for active models.", "High value" },
        { "sub_14068F040", "RuntimeController::AttachReplacement", "Looks like the real attach/replace call after a new RuntimeModel is created.", "High value" },
        { "sub_14068C700", "RuntimeModel::SetReplacementNames", "Stores replacement source/destination names; useful for model swap tools.", "Research" },
        { "sub_140689200", "RuntimeModel::SetModeByte", "Called by boss/stage loaders after model creation; identify flags before exposing UI.", "Research" },
        { "XREF sub_1402E20A4", "Stage object manager callers", "Find who creates/stores every stageobj entry; this is likely the active stage object list.", "Highest value" },
        { "XREF sub_1402E7A20", "Stage object instance callers", "Find descriptor list and world manager ownership.", "Highest value" },
    };
}

namespace EngineStageObjectResearch
{
    const StageSymbol* GameplayLoaders(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_GameplayLoaders) / sizeof(g_GameplayLoaders[0]));
        return g_GameplayLoaders;
    }

    const StageSymbol* StageObjectPipeline(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_StageObjectPipeline) / sizeof(g_StageObjectPipeline[0]));
        return g_StageObjectPipeline;
    }

    const StageSymbol* ReplacementPipeline(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_ReplacementPipeline) / sizeof(g_ReplacementPipeline[0]));
        return g_ReplacementPipeline;
    }

    const StageSymbol* NextTargets(int* count)
    {
        if (count) *count = static_cast<int>(sizeof(g_NextTargets) / sizeof(g_NextTargets[0]));
        return g_NextTargets;
    }

    const char* NextSub()
    {
        return "sub_1402E7038";
    }

    const char* NextSubReason()
    {
        return "sub_1402E7038 is called inside StageObjectInstance::Initialize immediately before RuntimeModel::SetTransform. It should reveal the stage object transform layout needed for object moving/spawning.";
    }
}
