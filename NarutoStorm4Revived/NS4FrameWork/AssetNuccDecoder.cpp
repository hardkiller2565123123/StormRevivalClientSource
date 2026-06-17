#include "StdInc.h"
#include "AssetNuccDecoder.h"
#include "AssetPreviewResolver.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace
{
    // XFBIN/NUCC field layout follows the MIT 010 templates from Al-Hydra/Storm-Engine-NUCC.
    struct ChunkMap
    {
        uint32_t TypeIndex = 0;
        uint32_t FileIndex = 0;
        uint32_t NameIndex = 0;
    };

    struct Reader
    {
        const std::vector<unsigned char>& Data;
        size_t Offset = 0;
        bool BigEndian = true;

        bool CanRead(size_t count) const
        {
            return Offset <= Data.size() && count <= Data.size() - Offset;
        }

        uint16_t U16()
        {
            if (!CanRead(2))
                return 0;

            uint16_t v = BigEndian
                ? static_cast<uint16_t>((Data[Offset] << 8) | Data[Offset + 1])
                : static_cast<uint16_t>(Data[Offset] | (Data[Offset + 1] << 8));
            Offset += 2;
            return v;
        }

        int16_t S16()
        {
            return static_cast<int16_t>(U16());
        }

        uint32_t U32()
        {
            if (!CanRead(4))
                return 0;

            uint32_t v = BigEndian
                ? (static_cast<uint32_t>(Data[Offset]) << 24) |
                  (static_cast<uint32_t>(Data[Offset + 1]) << 16) |
                  (static_cast<uint32_t>(Data[Offset + 2]) << 8) |
                  static_cast<uint32_t>(Data[Offset + 3])
                : static_cast<uint32_t>(Data[Offset]) |
                  (static_cast<uint32_t>(Data[Offset + 1]) << 8) |
                  (static_cast<uint32_t>(Data[Offset + 2]) << 16) |
                  (static_cast<uint32_t>(Data[Offset + 3]) << 24);
            Offset += 4;
            return v;
        }

        int32_t S32()
        {
            return static_cast<int32_t>(U32());
        }

        float F32()
        {
            uint32_t raw = U32();
            float value = 0.0f;
            std::memcpy(&value, &raw, sizeof(value));
            return value;
        }

        void Skip(size_t count)
        {
            Offset = std::min(Data.size(), Offset + count);
        }
    };

    bool ReadFileBytes(const std::string& path, std::vector<unsigned char>& out)
    {
        out.clear();

        std::ifstream file(path, std::ios::binary);

        if (!file.is_open())
            return false;

        file.seekg(0, std::ios::end);
        size_t size = static_cast<size_t>(std::max<std::streamoff>(0, file.tellg()));
        file.seekg(0, std::ios::beg);

        if (size == 0)
            return false;

        out.resize(size);
        file.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(size));
        return true;
    }

    std::vector<std::string> ReadStringBlock(Reader& r, uint32_t count, uint32_t size)
    {
        std::vector<std::string> strings;
        strings.reserve(count);

        const size_t end = std::min(r.Data.size(), r.Offset + size);

        for (uint32_t i = 0; i < count && r.Offset < end; ++i)
        {
            std::string value;

            while (r.Offset < end)
            {
                char c = static_cast<char>(r.Data[r.Offset++]);
                if (c == 0)
                    break;

                value.push_back(c);
            }

            strings.push_back(value);
        }

        r.Offset = end;
        return strings;
    }

    std::string AtOrEmpty(const std::vector<std::string>& values, uint32_t index)
    {
        return index < values.size() ? values[index] : std::string();
    }

    bool IsReasonableCoord(float v)
    {
        return std::isfinite(v) && std::abs(v) < 100000.0f;
    }

    bool AddVertexIfReasonable(AssetNuccDecoder::DecodedAsset& out, float x, float y, float z, float r, float g, float b)
    {
        if (!IsReasonableCoord(x) || !IsReasonableCoord(y) || !IsReasonableCoord(z))
            return false;

        AssetNuccDecoder::DecodedVertex vertex{};
        vertex.X = x;
        vertex.Y = y;
        vertex.Z = z;
        vertex.R = std::clamp(r, 0.0f, 1.0f);
        vertex.G = std::clamp(g, 0.0f, 1.0f);
        vertex.B = std::clamp(b, 0.0f, 1.0f);
        vertex.A = 1.0f;
        out.Vertices.push_back(vertex);
        return true;
    }

    void NormalizeVertices(AssetNuccDecoder::DecodedAsset& out)
    {
        if (out.Vertices.empty())
            return;

        float minX = out.Vertices[0].X;
        float minY = out.Vertices[0].Y;
        float minZ = out.Vertices[0].Z;
        float maxX = minX;
        float maxY = minY;
        float maxZ = minZ;

        for (const auto& vertex : out.Vertices)
        {
            minX = std::min(minX, vertex.X);
            minY = std::min(minY, vertex.Y);
            minZ = std::min(minZ, vertex.Z);
            maxX = std::max(maxX, vertex.X);
            maxY = std::max(maxY, vertex.Y);
            maxZ = std::max(maxZ, vertex.Z);
        }

        const float cx = (minX + maxX) * 0.5f;
        const float cy = (minY + maxY) * 0.5f;
        const float cz = (minZ + maxZ) * 0.5f;
        const float extent = std::max({ maxX - minX, maxY - minY, maxZ - minZ, 0.001f });
        const float scale = 3.2f / extent;

        for (auto& vertex : out.Vertices)
        {
            vertex.X = (vertex.X - cx) * scale;
            vertex.Y = (vertex.Y - cy) * scale;
            vertex.Z = (vertex.Z - cz) * scale;
        }
    }

    size_t PrimitiveVertexStride(uint32_t vertexType, uint32_t vertexSize)
    {
        if (vertexSize >= 16 && vertexSize <= 512)
            return vertexSize;

        switch (vertexType)
        {
        case 0:
            return 64;
        case 1:
        case 2:
            return 48;
        default:
            return 0;
        }
    }

    void ParsePrimitiveVertexChunk(const std::vector<unsigned char>& data, size_t bodyOffset, size_t size, AssetNuccDecoder::DecodedAsset& out)
    {
        if (size < 16)
            return;

        Reader r{ data, bodyOffset, true };
        const size_t bodyEnd = std::min(data.size(), bodyOffset + size);
        r.U32(); // BatchChunkIndex
        uint32_t vertexType = r.U32();
        uint32_t vertexSize = r.U32();
        uint32_t vertexCount = r.U32();

        if (vertexCount == 0 || vertexCount > 200000)
            return;

        const size_t stride = PrimitiveVertexStride(vertexType, vertexSize);
        if (stride == 0 || r.Offset + stride > bodyEnd)
            return;

        const size_t startVertex = out.Vertices.size();

        for (uint32_t i = 0; i < vertexCount && r.Offset + 12 <= bodyEnd; ++i)
        {
            const size_t vertexStart = r.Offset;
            float x = r.F32();
            float y = r.F32();
            float z = r.F32();

            float cr = 0.40f + static_cast<float>((i * 31) % 100) / 250.0f;
            float cg = 0.58f + static_cast<float>((i * 17) % 100) / 300.0f;
            float cb = 0.82f;

            AddVertexIfReasonable(out, x, y, z, cr, cg, cb);

            if (vertexStart + stride <= bodyEnd)
                r.Offset = vertexStart + stride;
            else
                break;
        }

        const int added = static_cast<int>(out.Vertices.size() - startVertex);
        for (int i = 0; i + 2 < added; i += 3)
            out.Faces.push_back({ static_cast<int>(startVertex) + i, static_cast<int>(startVertex) + i + 1, static_cast<int>(startVertex) + i + 2 });

        if (added > 0)
        {
            out.HasMesh = true;
            out.UsedPrimitiveVertices = true;
        }
    }

    void ParseModelHitChunk(const std::vector<unsigned char>& data, size_t bodyOffset, size_t size, uint32_t version, AssetNuccDecoder::DecodedAsset& out)
    {
        if (size < 8)
            return;

        Reader r{ data, bodyOffset, true };
        const size_t bodyEnd = std::min(data.size(), bodyOffset + size);
        uint32_t meshCount = r.U32();
        uint32_t totalTriangles = r.U32();

        if (meshCount == 0 || meshCount > 512 || totalTriangles > 100000)
            return;

        for (uint32_t mesh = 0; mesh < meshCount && r.Offset + 8 <= bodyEnd; ++mesh)
        {
            uint32_t triangles = r.U32();
            r.U32();

            if (version > 0x79)
                r.Skip(8);

            if (triangles > 50000 || r.Offset + static_cast<size_t>(triangles) * 36 > bodyEnd)
                break;

            for (uint32_t t = 0; t < triangles; ++t)
            {
                int base = static_cast<int>(out.Vertices.size());

                for (int i = 0; i < 3; ++i)
                {
                    float x = r.F32();
                    float y = r.F32();
                    float z = r.F32();
                    AddVertexIfReasonable(out, x, y, z, 0.9f, 0.64f, 0.34f);
                }

                if (static_cast<int>(out.Vertices.size()) >= base + 3)
                    out.Faces.push_back({ base, base + 1, base + 2 });
            }
        }

        if (!out.Faces.empty())
        {
            out.HasMesh = true;
            out.UsedHitMesh = true;
        }
    }

    void ParseChunkPayload(const std::vector<unsigned char>& data, const AssetNuccDecoder::ChunkInfo& chunk, uint32_t xfbinVersion, AssetNuccDecoder::DecodedAsset& out)
    {
        const size_t bodyOffset = chunk.Offset + 12;

        if (bodyOffset >= data.size() || chunk.Size == 0)
            return;

        if (chunk.Type == "nuccChunkPrimitiveVertex")
            ParsePrimitiveVertexChunk(data, bodyOffset, chunk.Size, out);
        else if (chunk.Type == "nuccChunkModelHit")
            ParseModelHitChunk(data, bodyOffset, chunk.Size, xfbinVersion, out);
        else if (chunk.Type == "nuccChunkTexture")
            out.TextureNames.push_back(chunk.Name.empty() ? chunk.FilePath : chunk.Name);
        else if (chunk.Type == "nuccChunkMaterial")
            out.MaterialNames.push_back(chunk.Name);
        else if (chunk.Type == "nuccChunkModel")
            out.ModelNames.push_back(chunk.Name);
    }

    const ChunkMap* ResolveChunkMap(
        const std::vector<ChunkMap>& maps,
        const std::vector<uint32_t>& chunkMapIndices,
        uint32_t pageStart,
        uint32_t localIndex)
    {
        uint32_t mapIndex = localIndex;
        const uint64_t mappedIndex = static_cast<uint64_t>(pageStart) + localIndex;

        if (mappedIndex < chunkMapIndices.size())
            mapIndex = chunkMapIndices[static_cast<size_t>(mappedIndex)];

        if (mapIndex >= maps.size())
            return nullptr;

        return &maps[mapIndex];
    }

    uint32_t ReadPageSize(const std::vector<unsigned char>& data, const AssetNuccDecoder::ChunkInfo& chunk)
    {
        const size_t bodyOffset = chunk.Offset + 12;

        if (bodyOffset + 4 > data.size() || chunk.Size < 4)
            return 0;

        Reader pageReader{ data, bodyOffset, true };
        return pageReader.U32();
    }
}

namespace AssetNuccDecoder
{
    bool DecodeFile(const std::string& path, DecodedAsset& outAsset)
    {
        outAsset = DecodedAsset{};

        std::vector<unsigned char> data;
        if (!ReadFileBytes(path, data))
        {
            outAsset.Status = "Could not read file.";
            return false;
        }

        if (data.size() < 32 || std::memcmp(data.data(), "NUCC", 4) != 0)
        {
            outAsset.Status = "Not an XFBIN/NUCC file.";
            return false;
        }

        Reader r{ data, 4, true };
        outAsset.Version = r.U32();
        r.U32();
        r.U32();
        uint32_t chunkTableSize = r.U32();
        r.U32();
        r.U16();
        r.U16();

        const size_t chunkTableStart = r.Offset;
        uint32_t typeCount = r.U32();
        uint32_t typeSize = r.U32();
        uint32_t fileCount = r.U32();
        uint32_t fileSize = r.U32();
        uint32_t nameCount = r.U32();
        uint32_t nameSize = r.U32();
        uint32_t mapCount = r.U32();
        uint32_t mapSize = r.U32();
        uint32_t mapIndexCount = r.U32();
        uint32_t extraIndexCount = r.U32();

        if (typeCount > 100000 || fileCount > 100000 || nameCount > 100000 || mapCount > 200000)
        {
            outAsset.Status = "Chunk table counts are not sane.";
            return false;
        }

        std::vector<std::string> types = ReadStringBlock(r, typeCount, typeSize);
        std::vector<std::string> files = ReadStringBlock(r, fileCount, fileSize);
        std::vector<std::string> names = ReadStringBlock(r, nameCount, nameSize);

        if ((typeCount || fileCount || nameCount) && r.Offset > 0)
        {
            r.Offset = r.Offset - 1;
            const size_t aligned = (r.Offset + 3) & ~size_t(3);
            r.Offset = std::min(data.size(), aligned);
        }

        std::vector<ChunkMap> maps;
        maps.reserve(mapCount);

        for (uint32_t i = 0; i < mapCount && r.CanRead(12); ++i)
            maps.push_back({ r.U32(), r.U32(), r.U32() });

        r.Skip(static_cast<size_t>(extraIndexCount) * 8);

        std::vector<uint32_t> chunkMapIndices;
        chunkMapIndices.reserve(mapIndexCount);
        for (uint32_t i = 0; i < mapIndexCount && r.CanRead(4); ++i)
            chunkMapIndices.push_back(r.U32());

        const size_t tableEndByHeader = chunkTableStart + chunkTableSize;
        if (tableEndByHeader > r.Offset && tableEndByHeader < data.size())
            r.Offset = tableEndByHeader;

        size_t parsedChunks = 0;
        uint32_t pageStart = 0;
        while (r.Offset + 12 <= data.size() && parsedChunks < 200000)
        {
            const size_t chunkOffset = r.Offset;
            uint32_t size = r.U32();
            uint32_t chunkMapIndex = r.U32();
            uint16_t version = r.U16();
            r.S16();

            if (size > data.size() || r.Offset + size > data.size())
                break;

            ChunkInfo info{};
            info.Size = size;
            info.Version = version;
            info.Offset = chunkOffset;

            if (const ChunkMap* map = ResolveChunkMap(maps, chunkMapIndices, pageStart, chunkMapIndex))
            {
                info.Type = AtOrEmpty(types, map->TypeIndex);
                info.FilePath = AtOrEmpty(files, map->FileIndex);
                info.Name = AtOrEmpty(names, map->NameIndex);
            }

            outAsset.Chunks.push_back(info);
            ParseChunkPayload(data, info, outAsset.Version, outAsset);

            if (info.Type == "nuccChunkPage")
            {
                const uint32_t pageSize = ReadPageSize(data, info);
                if (pageSize > 0 && static_cast<uint64_t>(pageStart) + pageSize <= 0xFFFFFFFFull)
                    pageStart += pageSize;
            }

            r.Offset += size;
            ++parsedChunks;
        }

        NormalizeVertices(outAsset);

        outAsset.Valid = true;
        std::ostringstream status;
        status << "NUCC decoded: chunks=" << outAsset.Chunks.size()
            << " vertices=" << outAsset.Vertices.size()
            << " faces=" << outAsset.Faces.size();
        if (outAsset.UsedHitMesh)
            status << " hitmesh";
        if (outAsset.UsedPrimitiveVertices)
            status << " primitive-vertices";
        outAsset.Status = status.str();
        return true;
    }

    bool DecodeAsset(const AssetBrowser::AssetEntry& asset, DecodedAsset& outAsset, bool autoDumpIfNeeded)
    {
        std::string path;
        if (!AssetPreviewResolver::ResolveReadablePath(asset, path, autoDumpIfNeeded))
        {
            outAsset = DecodedAsset{};
            outAsset.Status = "Could not resolve readable asset file.";
            return false;
        }

        return DecodeFile(path, outAsset);
    }

    std::string BuildReport(const DecodedAsset& asset)
    {
        std::ostringstream out;
        out << "NUCC Decode Report\n";
        out << "==================\n";
        out << "Valid: " << (asset.Valid ? "true" : "false") << "\n";
        out << "Status: " << asset.Status << "\n";
        out << "Version: " << asset.Version << "\n";
        out << "Chunks: " << asset.Chunks.size() << "\n";
        out << "Vertices: " << asset.Vertices.size() << "\n";
        out << "Faces: " << asset.Faces.size() << "\n";
        out << "Textures: " << asset.TextureNames.size() << "\n";
        out << "Materials: " << asset.MaterialNames.size() << "\n";
        out << "Models: " << asset.ModelNames.size() << "\n\n";

        for (const auto& chunk : asset.Chunks)
        {
            out << "- " << chunk.Type << " | " << chunk.Name
                << " | size=" << chunk.Size
                << " | version=0x" << std::hex << chunk.Version << std::dec
                << "\n";
        }

        return out.str();
    }
}
