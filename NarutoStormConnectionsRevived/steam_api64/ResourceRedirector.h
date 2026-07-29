#pragma once

#include "ResourceTypes.h"

#include <cstdint>
#include <string>
#include <vector>

namespace ResourceRedirector
{
    // Hooks the native resource systems we have mapped:
    // sub_14126CE30 = ResourceManager_GetOrLoad for XFBIN/native resources.
    // sub_140BEEE70 = ScaleformManager_QueueMovieLoad for SWF/GFX UI movies.
    bool Init(uintptr_t gameBase);
    void Shutdown();

    // Scans NarutoStormConnectionsRevived/mods/<ModName>/ recursively.
    // Every file is indexed by normalized relative path and by file name so
    // loose files can be found even when the game asks for a slightly different
    // normalized key, such as a stripped .xfbin extension.
    void RescanMods();

    bool Enabled();
    void SetEnabled(bool enabled);

    std::string ModsRoot();
    std::vector<std::string> ModFolders();
    std::vector<ResourceTypes::ModFileEntry> SnapshotModFiles();
    std::vector<ResourceTypes::LoadedResourceRow> SnapshotRows();
    void ClearLogRows();
}
