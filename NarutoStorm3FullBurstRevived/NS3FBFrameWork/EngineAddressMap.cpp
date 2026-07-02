#include "StdInc.h"
#include "EngineAddressMap.h"
#include <iomanip>

namespace
{
    constexpr uintptr_t kIdaBase = 0x140000000ull;

    std::vector<EngineAddressMap::KnownAddress> BuildKnownAddresses()
    {
        using namespace EngineAddressMap;
        return
        {
            { "GameAlloc", 0x140683F70, AddressKind::Function, SafetyLevel::WrapperReady, "Allocation wrapper used by many nucc constructors." },
            { "HashChunkTypeName", 0x140684CC0, AddressKind::Function, SafetyLevel::WrapperReady, "Hash/register helper used for nuccChunk* type names." },
            { "HashChunkName", 0x140684D80, AddressKind::Function, SafetyLevel::WrapperReady, "Hash helper for chunk/file object names." },

            { "nuccChunkTypeManager::Initialize", 0x1406991B0, AddressKind::Function, SafetyLevel::HookCandidate, "Registers every known nucc chunk type at engine startup." },
            { "nuccChunkTypeManager::Constructor", 0x1406FFA00, AddressKind::Function, SafetyLevel::WrapperReady, "Initializes the type manager tree/list." },
            { "nuccChunkTypeManager::RegisterChunkType", 0x1406FFA80, AddressKind::Function, SafetyLevel::WrapperReady, "Assigns type ids and inserts type objects." },
            { "nuccChunkTypeManager::FindTypeByHashOrName", 0x1406FFB20, AddressKind::Function, SafetyLevel::WrapperReady, "Used by the XFBIN parser to resolve chunk type names." },

            { "nuccXfbinParser::Read", 0x14069D980, AddressKind::Function, SafetyLevel::HookCandidate, "Reads XFBIN header/tables and builds runtime chunk entries." },
            { "BuildStringPointerTable", 0x14069E150, AddressKind::Function, SafetyLevel::WrapperReady, "Builds null-terminated string pointer arrays from XFBIN string tables." },
            { "Xfbin::FindChunkByTypeAndName", 0x14069E450, AddressKind::Function, SafetyLevel::WrapperReady, "Finds a chunk in a loaded archive using type object and name hash." },
            { "XfbinObject::GetAllChunksOfType", 0x14068E030, AddressKind::Function, SafetyLevel::WrapperReady, "Enumerates chunks matching a type object." },
            { "XfbinObject::FindChunksByTypeAndName", 0x14068E1A0, AddressKind::Function, SafetyLevel::WrapperReady, "Enumerates chunks by type and name, used for *head lookup." },

            { "XfbinManager::GetLoadedXfbin", 0x140773FA0, AddressKind::Function, SafetyLevel::WrapperReady, "Looks up an already loaded XFBIN by path hash and bumps refcount." },
            { "GetLoadedXfbin", 0x140740D30, AddressKind::Function, SafetyLevel::WrapperReady, "Small global wrapper around XfbinManager::GetLoadedXfbin." },
            { "FindChunkFromLoadedXfbin", 0x140740D80, AddressKind::Function, SafetyLevel::WrapperReady, "Loads/finds an XFBIN then optionally finds a chunk." },
            { "HasChunkFromLoadedXfbin", 0x140740E00, AddressKind::Function, SafetyLevel::WrapperReady, "Boolean wrapper for finding a chunk in a loaded XFBIN." },
            { "ReleaseLoadedXfbin", 0x140774030, AddressKind::Function, SafetyLevel::WrapperReady, "Releases/decrements loaded XFBIN reference." },
            { "ArchiveLookupOrLoad", 0x140693920, AddressKind::Function, SafetyLevel::HookCandidate, "Global archive lookup/load function used before chunk access." },
            { "FileRead", 0x140703630, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Raw read callback used by nuccXfbinParser." },

            { "Create_nuccChunkModel", 0x14069A620, AddressKind::Function, SafetyLevel::WrapperReady, "Allocates 0x138 and calls nuccChunkModel constructor." },
            { "nuccChunkModel::Constructor", 0x1406B16D0, AddressKind::Function, SafetyLevel::WrapperReady, "Constructor for nuccChunkModel." },
            { "Create_nuccChunkMaterial", 0x14069A5F0, AddressKind::Function, SafetyLevel::WrapperReady, "Allocates 0x90 and constructs material chunk." },
            { "Create_nuccChunkTexture", 0x14069A950, AddressKind::Function, SafetyLevel::WrapperReady, "Allocates 0x30 and constructs texture chunk." },
            { "Create_nuccChunkSprite2", 0x14069A830, AddressKind::Function, SafetyLevel::WrapperReady, "Factory for nuccChunkSprite2." },
            { "Create_nuccChunkNub", 0x14069A760, AddressKind::Function, SafetyLevel::WrapperReady, "Factory for nuccChunkNub." },

            { "RuntimeModel::Initialize", 0x140687CC0, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "0x340 runtime object initializer. Bridge between loaded chunk and live resource." },
            { "RuntimeModel::AttachResource", 0x14068B540, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Called by RuntimeModel::Initialize; likely binds model/resource data." },
            { "RuntimeSceneObject::LoadFromChunk", 0x14073AD30, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Finds off_140B5BC30 and creates RuntimeModel." },
            { "RuntimeSceneObject::Constructor", 0x14073AC50, AddressKind::Function, SafetyLevel::WrapperReady, "0x88 object wrapper constructor with runtime model at +24." },
            { "CharacterResourceLoader::BuildRuntimeObjects", 0x14017BB64, AddressKind::Function, SafetyLevel::HookCandidate, "Creates model wrappers from resource tables and searches *head." },
            { "RuntimeObjectList::Update", 0x14017C3EC, AddressKind::Function, SafetyLevel::HookCandidate, "Updates runtime objects and visibility/fade state." },
            { "ApplyModelOpacity", 0x140193874, AddressKind::Function, SafetyLevel::WrapperReady, "Iterates render children and applies visibility/opacity." },
            { "ApplyMaterialFloatToModel", 0x14017CAFC, AddressKind::Function, SafetyLevel::WrapperReady, "Finds off_140B5BA38 chunks and writes per-instance value +52." },

            { "nuccAnmAttachOrBindPipeline", 0x14068F8C0, AddressKind::Function, SafetyLevel::HookCandidate, "Animation/object attach pipeline. Links targets and finalizes binds." },

            { "RuntimeNode::Constructor", 0x140687350, AddressKind::Function, SafetyLevel::WrapperReady, "Constructs one runtime node with transforms/state/visibility flags." },
            { "RuntimeNode::DirtyVisibility", 0x140687460, AddressKind::Function, SafetyLevel::WrapperReady, "Marks visibility/parent dirty state up hierarchy." },
            { "RuntimeNode::BindChunk", 0x140687790, AddressKind::Function, SafetyLevel::WrapperReady, "Binds parsed node chunk to runtime node and copies base transform." },
            { "RuntimeNode::SetTransform", 0x140687910, AddressKind::Function, SafetyLevel::WrapperReady, "Copies runtime transform and marks owner dirty." },
            { "RuntimeNode::SetParent", 0x140687950, AddressKind::Function, SafetyLevel::WrapperReady, "Links runtime node parent and marks hierarchy dirty." },
            { "RuntimeModel::BuildNodeHierarchy", 0x140689440, AddressKind::Function, SafetyLevel::HookCandidate, "Creates runtime nodes and parent/child links from source chunk." },
            { "RuntimeModel::InitializeRuntime", 0x1406890C0, AddressKind::Function, SafetyLevel::HookCandidate, "Runs runtime init over model and each runtime node." },
            { "RuntimeModel::BuildDependencyGraph", 0x1406898E0, AddressKind::Function, SafetyLevel::HookCandidate, "Builds model/material/texture/dependency runtime references." },
            { "RuntimeModel::BuildLODGraph", 0x14068B960, AddressKind::Function, SafetyLevel::HookCandidate, "Finds *_lod* names and connects LOD runtime objects." },
            { "RuntimeModel::BuildBoneRuntime", 0x14068A930, AddressKind::Function, SafetyLevel::HookCandidate, "Builds runtime bone transform helper list." },
            { "RuntimeModel::Destroy", 0x14068A800, AddressKind::Function, SafetyLevel::WrapperReady, "Known cleanup path for runtime model/nodes/graphs." },
            { "RuntimeModel::BuildRenderExtra", 0x1406CF530, AddressKind::Function, SafetyLevel::HookCandidate, "Creates render graph extras from runtime model; xrefs should lead to scene owner." },
            { "RuntimeRenderGraph::Constructor", 0x140722510, AddressKind::Function, SafetyLevel::HookCandidate, "Render graph helper built inside RuntimeModel::BuildRenderExtra; mapped from latest dump." },
            { "RuntimeRenderGraph::AddDrawNode", 0x140722BE0, AddressKind::Function, SafetyLevel::HookCandidate, "Adds render entries to graph builder." },
            { "RuntimeRenderGraph::BuildLists", 0x140722880, AddressKind::Function, SafetyLevel::HookCandidate, "Returns finalized render graph/root pointer." },
            { "RuntimeRenderGraph::Destroy", 0x140722730, AddressKind::Function, SafetyLevel::WrapperReady, "Cleanup for render graph helper." },
            { "RenderAttachment::Constructor", 0x140721690, AddressKind::Function, SafetyLevel::HookCandidate, "Creates render attachment for runtime node." },
            { "RuntimeAttachment::AttachToNode", 0x140721760, AddressKind::Function, SafetyLevel::HookCandidate, "Links attachment to render graph/list." },
            { "RuntimeAttachmentList::PushBack", 0x1407223A0, AddressKind::Function, SafetyLevel::HookCandidate, "Generic append helper for runtime/attachment lists; not world manager by itself." },


            { "RuntimeModelManager::ReplaceModelsByName", 0x1402364A8, AddressKind::Function, SafetyLevel::HookCandidate, "Searches/replaces runtime models by chunk names and builds replacement RuntimeModel objects." },
            { "RuntimeModelManager::LoadRuntimeModelList", 0x140238700, AddressKind::Function, SafetyLevel::HookCandidate, "Loads a list of model descriptors into RuntimeModel objects stored by hashed name." },
            { "BossCharacter::LoadResources", 0x14025474C, AddressKind::Function, SafetyLevel::HookCandidate, "Gameplay loader using RuntimeModel + effect chunk pipeline." },
            { "CharacterChain::Initialize", 0x140296ABC, AddressKind::Function, SafetyLevel::HookCandidate, "Loads rkyuchain1 as a RuntimeModel attachment." },
            { "BossTailSystem::Initialize", 0x1402A2DC0, AddressKind::Function, SafetyLevel::HookCandidate, "Loads boss tail RuntimeModel objects and shadow resources." },
            { "StageObject::Initialize", 0x1402D0B7C, AddressKind::Function, SafetyLevel::HookCandidate, "Creates RuntimeModel or effect object, applies transform, initializes stage object state." },
            { "StageObjectManager::Create", 0x1402E20A4, AddressKind::Function, SafetyLevel::HookCandidate, "Creates stageobj helper and builds a RuntimeModel from a ccStageClump descriptor." },
            { "StageObjectInstance::Initialize", 0x1402E7A20, AddressKind::Function, SafetyLevel::HookCandidate, "Initializes one stage object instance from descriptor flags and RuntimeModel/effect chunk." },
            { "BossEffect::Initialize", 0x1403065B8, AddressKind::Function, SafetyLevel::HookCandidate, "Loads boss effect RuntimeModel and effect point resources." },
            { "RPGCharacterLoader::LoadCharacter", 0x1403A0D34, AddressKind::Function, SafetyLevel::HookCandidate, "Resolves RPG character model data and creates RuntimeModel." },
            { "StageObjectInstance::BuildTransform", 0x1402E7038, AddressKind::Function, SafetyLevel::HookCandidate, "NEXT SUB: called before RuntimeModel::SetTransform. Should reveal stage object position/rotation/scale layout." },
            { "StageObject::BuildTransform", 0x1402D0784, AddressKind::Function, SafetyLevel::HookCandidate, "StageObject transform builder used before runtime model setup." },
            { "RuntimeController::BindModel", 0x14068F3D0, AddressKind::Function, SafetyLevel::HookCandidate, "Binds RuntimeModel into a higher-level controller/effect wrapper." },
            { "RuntimeController::AttachReplacement", 0x14068F040, AddressKind::Function, SafetyLevel::HookCandidate, "Called after model replacement/load to attach RuntimeModel to manager/controller list." },
            { "RuntimeModel::SetReplacementNames", 0x14068C700, AddressKind::Function, SafetyLevel::HookCandidate, "Applies source/destination names for model replacement." },
            { "RuntimeModel::SetModeByte", 0x140689200, AddressKind::Function, SafetyLevel::HookCandidate, "Mode/visibility byte set after model creation by boss/stage loaders." },
            { "RuntimeModel::FindChunksByType", 0x14068B200, AddressKind::Function, SafetyLevel::WrapperReady, "Finds runtime nodes/chunks of a type inside RuntimeModel." },
            { "RuntimeModel::FindChunksByWildcard", 0x14068B360, AddressKind::Function, SafetyLevel::WrapperReady, "Finds runtime chunks by type and wildcard string." },

            { "AnimLink_SetSource", 0x1406D9310, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Sets source object in animation link entry." },
            { "AnimLink_AttachTarget", 0x1406D9320, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Attaches target object to animation link entry." },
            { "FinalizeAnimationBind", 0x140690C60, AddressKind::Function, SafetyLevel::UnsafeUntilSignatureVerified, "Finalizes animation/model bind arrays." },

            { "off_140B5BA08", 0x140B5BA08, AddressKind::VTableOrType, SafetyLevel::InfoOnly, "Registered chunk type object. Likely nuccChunkModel based on registration nearby." },
            { "off_140B5BA38", 0x140B5BA38, AddressKind::VTableOrType, SafetyLevel::InfoOnly, "Runtime queried chunk type, possibly material/render sub-object." },
            { "off_140B5BA50", 0x140B5BA50, AddressKind::VTableOrType, SafetyLevel::InfoOnly, "Important runtime/model chunk type used by animation pipeline." },
            { "off_140B5BA98", 0x140B5BA98, AddressKind::VTableOrType, SafetyLevel::InfoOnly, "Likely skeleton/bone/node chunk; searched by name '*head'." },
            { "off_140B5BC30", 0x140B5BC30, AddressKind::VTableOrType, SafetyLevel::InfoOnly, "Container/object-list chunk used to create RuntimeModel." },
            { "qword_140C69100", 0x140C69100, AddressKind::Global, SafetyLevel::InfoOnly, "Global nuccChunkTypeManager pointer." },
            { "xmmword_140C7BE10", 0x140C7BE10, AddressKind::Global, SafetyLevel::InfoOnly, "Global XFBIN/archive manager object used by wrappers." },
            { "unk_140C24430", 0x140C24430, AddressKind::Global, SafetyLevel::InfoOnly, "Global archive table passed into ArchiveLookupOrLoad." },
        };
    }

    std::vector<EngineAddressMap::KnownChunkType> BuildKnownChunkTypes()
    {
        return
        {
            { "nuccChunkModel",    0x140B5BA08, 0x140112410, 0x14069A620, "Confirmed by registration function and factory allocation." },
            { "nuccChunkMaterial", 0x140B5BA38, 0x1401123D0, 0x14069A5F0, "Confirmed registration string and constructor factory." },
            { "nuccChunkTexture",  0x140B5B9F0, 0x140112790, 0x14069A950, "Confirmed registration string and constructor factory." },
            { "nuccChunkSprite2",  0x140B5BC60, 0x140112690, 0x14069A830, "Confirmed registration string and factory." },
            { "nuccChunkNub",      0x140B5BC90, 0x140112590, 0x14069A760, "Confirmed registration string and factory." },
            { "unknown_model_runtime", 0x140B5BA50, 0, 0, "Used by animation pipeline; identify exact string next." },
            { "unknown_skeleton_or_bone", 0x140B5BA98, 0, 0, "FindChunksByTypeAndName searches this with '*head'." },
            { "unknown_container", 0x140B5BC30, 0, 0, "Used by RuntimeSceneObject::LoadFromChunk to create RuntimeModel." },
        };
    }
}

namespace EngineAddressMap
{
    uintptr_t ModuleBase()
    {
        return reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
    }

    uintptr_t Rebase(uintptr_t idaAddress)
    {
        if (!idaAddress)
            return 0;
        return ModuleBase() + (idaAddress - kIdaBase);
    }

    uint32_t HashChunkTypeName(const char* text)
    {
        if (!text)
            return 0;

        uint32_t result = 0;
        int i = 0;
        for (const unsigned char* p = reinterpret_cast<const unsigned char*>(text); *p; ++p)
        {
            const int ch = static_cast<char>(*p);
            const int v = i + (ch << ((ch & 7) + 2));
            i += 16633;
            result = static_cast<uint32_t>(v) ^ result;
        }
        return result;
    }

    uint32_t HashChunkName(const char* text)
    {
        // IDA shows sub_140684D80 forwards to a secondary hash routine after strlen.
        // Until that secondary routine is named, keep framework code from relying on a guessed value.
        if (!text)
            return 0;
        uint32_t hash = 2166136261u;
        for (const unsigned char* p = reinterpret_cast<const unsigned char*>(text); *p; ++p)
        {
            hash ^= *p;
            hash *= 16777619u;
        }
        return hash;
    }

    const std::vector<KnownAddress>& KnownAddresses()
    {
        static const std::vector<KnownAddress> list = BuildKnownAddresses();
        return list;
    }

    const std::vector<KnownChunkType>& KnownChunkTypes()
    {
        static const std::vector<KnownChunkType> list = BuildKnownChunkTypes();
        return list;
    }

    const KnownAddress* FindByName(const std::string& name)
    {
        const auto& list = KnownAddresses();
        for (const auto& item : list)
        {
            if (item.Name && name == item.Name)
                return &item;
        }
        return nullptr;
    }

    std::string FormatAddress(uintptr_t value)
    {
        std::ostringstream out;
        out << "0x" << std::uppercase << std::hex << value;
        return out.str();
    }

    const char* KindName(AddressKind kind)
    {
        switch (kind)
        {
        case AddressKind::Function: return "Function";
        case AddressKind::VTableOrType: return "Type/VTable";
        case AddressKind::Global: return "Global";
        case AddressKind::String: return "String";
        default: return "Unknown";
        }
    }

    const char* SafetyName(SafetyLevel safety)
    {
        switch (safety)
        {
        case SafetyLevel::InfoOnly: return "Info only";
        case SafetyLevel::WrapperReady: return "Wrapper ready";
        case SafetyLevel::HookCandidate: return "Hook candidate";
        case SafetyLevel::UnsafeUntilSignatureVerified: return "Unsafe until signature verified";
        default: return "Unknown";
        }
    }
}
