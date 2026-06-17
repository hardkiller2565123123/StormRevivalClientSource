#pragma once
#include "StdInc.h"
#include "AssetBrowser.h"

namespace AssetDecodePipeline
{
    struct DecodeStats
    {
        int Total = 0;
        int Decoded = 0;
        int Extracted = 0;
        int Copied = 0;
        int Reported = 0;
        int ExternalDecoded = 0;
        int Unsupported = 0;
        int Failed = 0;
        std::string OutputRoot;
        std::string LastStatus;
    };

    bool DecodeAsset(const AssetBrowser::AssetEntry& asset);
    DecodeStats DecodeAllAssets();
    DecodeStats DecodeSelectedAssets(const std::vector<AssetBrowser::AssetEntry>& assets);
    const DecodeStats& GetLastStats();
    std::string BuildLastReport();
}
