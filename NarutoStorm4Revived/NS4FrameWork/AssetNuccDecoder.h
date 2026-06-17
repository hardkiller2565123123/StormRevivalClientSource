#pragma once
#include "StdInc.h"
#include "AssetBrowser.h"

namespace AssetNuccDecoder
{
    struct DecodedVertex
    {
        float X = 0.0f;
        float Y = 0.0f;
        float Z = 0.0f;
        float R = 0.45f;
        float G = 0.75f;
        float B = 1.0f;
        float A = 1.0f;
    };

    struct DecodedFace
    {
        int A = 0;
        int B = 0;
        int C = 0;
    };

    struct ChunkInfo
    {
        std::string Type;
        std::string Name;
        std::string FilePath;
        uint32_t Size = 0;
        uint32_t Version = 0;
        size_t Offset = 0;
    };

    struct DecodedAsset
    {
        bool Valid = false;
        bool HasMesh = false;
        bool UsedHitMesh = false;
        bool UsedPrimitiveVertices = false;
        std::string Status;
        uint32_t Version = 0;
        std::vector<ChunkInfo> Chunks;
        std::vector<DecodedVertex> Vertices;
        std::vector<DecodedFace> Faces;
        std::vector<std::string> TextureNames;
        std::vector<std::string> MaterialNames;
        std::vector<std::string> ModelNames;
    };

    bool DecodeFile(const std::string& path, DecodedAsset& outAsset);
    bool DecodeAsset(const AssetBrowser::AssetEntry& asset, DecodedAsset& outAsset, bool autoDumpIfNeeded);
    std::string BuildReport(const DecodedAsset& asset);
}
