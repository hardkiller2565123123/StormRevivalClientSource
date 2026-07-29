#pragma once
#include "ResourceTypes.h"
#include <cstdint>
#include <string>
#include <vector>

namespace ResourceRedirector
{
    bool Init(uintptr_t gameBase);
    void Shutdown();

    void RescanMods();
    bool Enabled();
    void SetEnabled(bool enabled);

    std::string ModsRoot();
    std::vector<std::string> ModFolders();
    std::vector<ResourceTypes::LoadedResourceRow> SnapshotRows();

    // Used by F2 menu buttons.
    void ClearLogRows();
}
