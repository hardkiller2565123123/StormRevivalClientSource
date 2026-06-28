#pragma once
#include "StdInc.h"
#include <filesystem>
#include <string>
#include <vector>

namespace StormAPIBridge
{
    bool Init();
    void Shutdown();
    bool IsEnabled();
    const char* CreditText();
    std::filesystem::path ExeFolder();
    std::filesystem::path RootFolder();
    std::filesystem::path SourceFolder();
    int BundledSourceFileCount();
}
