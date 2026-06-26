#include "StdInc.h"
#include "AssetModelViewer.h"
#include "AssetPreviewResolver.h"
#include "Logger.h"
#include "XfbinInspector.h"
#include "AssetNuccDecoder.h"
#include "imgui.h"

#include <algorithm>
#include <cmath>
#include <fstream>

namespace
{
    struct Vec3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct RenderNode
    {
        std::string Label;
        std::string Kind;
        Vec3 Position;
        float Radius = 0.12f;
        ImU32 Color = IM_COL32(120, 180, 255, 255);
    };

    struct ProjectedNode
    {
        int Index = -1;
        ImVec2 Position;
        float Depth = 0.0f;
        float Radius = 0.0f;
    };

    struct MeshVertex
    {
        Vec3 Position;
        ImU32 Color = IM_COL32(100, 190, 255, 255);
    };

    struct MeshFace
    {
        int A = 0;
        int B = 0;
        int C = 0;
    };

    struct MeshPreview
    {
        std::string Key;
        std::string Status;
        std::vector<MeshVertex> Vertices;
        std::vector<MeshFace> Faces;
        bool Loaded = false;
    };

    bool g_Initialized = false;
    bool g_AutoOrbit = true;
    bool g_ShowGrid = true;
    bool g_ShowBounds = true;
    bool g_ShowLabels = true;
    bool g_ShowLinks = true;
    bool g_ShowStats = true;
    bool g_UseInspector = true;
    bool g_ShowSurface = true;
    bool g_ShowWireframe = true;
    bool g_ShowStructureGraph = false;

    float g_Yaw = 0.45f;
    float g_Pitch = 0.35f;
    float g_Zoom = 1.0f;
    int g_SelectedNode = -1;

    std::string g_LastAssetKey;
    XfbinInspector::XfbinInfo g_LastInfo{};
    MeshPreview g_MeshPreview{};
    AssetNuccDecoder::DecodedAsset g_LastDecoded{};

    float Clamp(float value, float minValue, float maxValue)
    {
        return std::max(minValue, std::min(maxValue, value));
    }

    uint32_t HashText(const std::string& text)
    {
        uint32_t hash = 2166136261u;

        for (unsigned char c : text)
        {
            hash ^= c;
            hash *= 16777619u;
        }

        return hash;
    }

    float Hash01(const std::string& text, uint32_t salt)
    {
        uint32_t hash = HashText(text + std::to_string(salt));
        return static_cast<float>(hash & 0x00FFFFFFu) / static_cast<float>(0x01000000u);
    }

    std::string MakeAssetKey(const AssetBrowser::AssetEntry& asset)
    {
        if (!asset.VirtualPath.empty())
            return asset.VirtualPath;

        if (!asset.ArchiveEntryPath.empty())
            return asset.ArchivePath + ":" + asset.ArchiveEntryPath;

        return asset.FullPath;
    }

    std::string ShortLabel(const std::string& value, size_t maxChars = 34)
    {
        if (value.size() <= maxChars)
            return value;

        if (maxChars < 4)
            return value.substr(0, maxChars);

        return value.substr(0, maxChars - 3) + "...";
    }

    Vec3 Rotate(const Vec3& p, float yaw, float pitch)
    {
        float cy = cosf(yaw);
        float sy = sinf(yaw);
        float cp = cosf(pitch);
        float sp = sinf(pitch);

        Vec3 yRot{};
        yRot.x = p.x * cy - p.z * sy;
        yRot.z = p.x * sy + p.z * cy;
        yRot.y = p.y;

        Vec3 out{};
        out.x = yRot.x;
        out.y = yRot.y * cp - yRot.z * sp;
        out.z = yRot.y * sp + yRot.z * cp;
        return out;
    }

    ImVec2 Project(const Vec3& p, const ImVec2& center, float scale, float yaw, float pitch, float zoom, float* outDepth = nullptr)
    {
        Vec3 r = Rotate(p, yaw, pitch);
        float depth = r.z + 7.0f;
        float perspective = 1.0f / std::max(2.0f, depth);
        float projectedScale = scale * zoom * perspective * 5.0f;

        if (outDepth)
            *outDepth = depth;

        return ImVec2(center.x + r.x * projectedScale, center.y - r.y * projectedScale);
    }

    void AddNode(std::vector<RenderNode>& nodes, const std::string& label, const std::string& kind, const Vec3& pos, float radius, ImU32 color)
    {
        RenderNode node{};
        node.Label = ShortLabel(label);
        node.Kind = kind;
        node.Position = pos;
        node.Radius = radius;
        node.Color = color;
        nodes.push_back(node);
    }

    bool ReadBytes(const std::string& path, std::vector<unsigned char>& bytes, size_t maxBytes)
    {
        bytes.clear();

        std::ifstream file(path, std::ios::binary);

        if (!file.is_open())
            return false;

        file.seekg(0, std::ios::end);
        size_t size = static_cast<size_t>(std::max<std::streamoff>(0, file.tellg()));
        file.seekg(0, std::ios::beg);

        size = std::min(size, maxBytes);
        bytes.resize(size);

        if (size)
            file.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(size));

        return !bytes.empty();
    }

    float ByteToUnit(unsigned char value)
    {
        return (static_cast<float>(value) / 255.0f) * 2.0f - 1.0f;
    }

    MeshPreview BuildByteSurfaceMesh(const AssetBrowser::AssetEntry& asset, const std::string& readablePath)
    {
        MeshPreview mesh{};
        mesh.Key = MakeAssetKey(asset) + "|" + readablePath;

        std::vector<unsigned char> bytes;
        if (!ReadBytes(readablePath, bytes, 4 * 1024 * 1024))
        {
            mesh.Status = "Could not read asset bytes for render preview.";
            return mesh;
        }

        const int columns = 22;
        const int rows = 18;
        const int vertexCount = columns * rows;
        mesh.Vertices.reserve(vertexCount);
        mesh.Faces.reserve((columns - 1) * (rows - 1) * 2);

        uint32_t seed = HashText(asset.VirtualPath + asset.Name);
        const float modelScale = asset.Type == AssetBrowser::AssetType::Character ? 1.2f : 1.65f;
        const float heightScale = asset.Type == AssetBrowser::AssetType::Stage ? 0.85f : 1.25f;

        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                const size_t base = (static_cast<size_t>(x) * 131u + static_cast<size_t>(y) * 977u + seed) % bytes.size();
                const unsigned char a = bytes[base % bytes.size()];
                const unsigned char b = bytes[(base + 97) % bytes.size()];
                const unsigned char c = bytes[(base + 193) % bytes.size()];
                const unsigned char d = bytes[(base + 389) % bytes.size()];

                const float u = columns <= 1 ? 0.0f : static_cast<float>(x) / static_cast<float>(columns - 1);
                const float v = rows <= 1 ? 0.0f : static_cast<float>(y) / static_cast<float>(rows - 1);
                const float centeredX = (u - 0.5f) * 3.6f * modelScale;
                const float centeredZ = (v - 0.5f) * 3.0f * modelScale;
                const float ripple = sinf((u * 8.0f) + ByteToUnit(a) * 2.5f) * 0.25f +
                    cosf((v * 7.0f) + ByteToUnit(b) * 2.0f) * 0.22f;

                MeshVertex vertex{};
                vertex.Position.x = centeredX + ByteToUnit(c) * 0.18f;
                vertex.Position.z = centeredZ + ByteToUnit(d) * 0.18f;
                vertex.Position.y = ripple * heightScale + ByteToUnit(a ^ b) * 0.35f;

                if (asset.Type == AssetBrowser::AssetType::Character)
                {
                    const float body = 1.0f - std::abs(u - 0.5f) * 1.55f;
                    vertex.Position.y += (v - 0.5f) * 1.9f;
                    vertex.Position.x *= std::max(0.18f, body);
                    vertex.Position.z *= 0.55f;
                }

                vertex.Color = IM_COL32(
                    70 + (a % 120),
                    110 + (b % 115),
                    150 + (c % 95),
                    235);
                mesh.Vertices.push_back(vertex);
            }
        }

        for (int y = 0; y < rows - 1; ++y)
        {
            for (int x = 0; x < columns - 1; ++x)
            {
                const int i = y * columns + x;
                mesh.Faces.push_back({ i, i + 1, i + columns });
                mesh.Faces.push_back({ i + 1, i + columns + 1, i + columns });
            }
        }

        mesh.Loaded = true;
        mesh.Status = "Rendered fallback byte-surface preview. No usable NUCC mesh geometry was found in this asset.";
        return mesh;
    }

    MeshPreview BuildNuccMesh(const AssetBrowser::AssetEntry& asset, const AssetNuccDecoder::DecodedAsset& decoded)
    {
        MeshPreview mesh{};
        mesh.Key = MakeAssetKey(asset) + "|nucc";

        if (!decoded.Valid || decoded.Vertices.empty() || decoded.Faces.empty())
        {
            mesh.Status = decoded.Status.empty() ? "NUCC decode produced no renderable mesh yet." : decoded.Status;
            return mesh;
        }

        mesh.Vertices.reserve(decoded.Vertices.size());
        mesh.Faces.reserve(decoded.Faces.size());

        for (const auto& vertex : decoded.Vertices)
        {
            MeshVertex out{};
            out.Position.x = vertex.X;
            out.Position.y = vertex.Y;
            out.Position.z = vertex.Z;
            out.Color = IM_COL32(
                static_cast<int>(std::clamp(vertex.R, 0.0f, 1.0f) * 255.0f),
                static_cast<int>(std::clamp(vertex.G, 0.0f, 1.0f) * 255.0f),
                static_cast<int>(std::clamp(vertex.B, 0.0f, 1.0f) * 255.0f),
                235);
            mesh.Vertices.push_back(out);
        }

        for (const auto& face : decoded.Faces)
        {
            if (face.A >= 0 && face.B >= 0 && face.C >= 0 &&
                face.A < static_cast<int>(mesh.Vertices.size()) &&
                face.B < static_cast<int>(mesh.Vertices.size()) &&
                face.C < static_cast<int>(mesh.Vertices.size()))
            {
                mesh.Faces.push_back({ face.A, face.B, face.C });
            }
        }

        mesh.Loaded = !mesh.Vertices.empty() && !mesh.Faces.empty();
        mesh.Status = decoded.Status;
        return mesh;
    }

    void EnsureMeshPreview(const AssetBrowser::AssetEntry& asset, const std::string& readablePath)
    {
        const std::string key = MakeAssetKey(asset) + "|" + readablePath;

        if (g_MeshPreview.Key == key && g_MeshPreview.Loaded)
            return;

        AssetNuccDecoder::DecodedAsset decoded{};
        if (AssetNuccDecoder::DecodeFile(readablePath, decoded))
        {
            g_LastDecoded = decoded;

            if (decoded.HasMesh)
            {
                g_MeshPreview = BuildNuccMesh(asset, g_LastDecoded);
                if (g_MeshPreview.Loaded)
                    return;
            }
        }

        g_LastDecoded = decoded;
        g_MeshPreview = BuildByteSurfaceMesh(asset, readablePath);
    }

    void AddRing(
        std::vector<RenderNode>& nodes,
        const std::vector<std::string>& refs,
        const char* kind,
        float ringRadius,
        float y,
        float startAngle,
        ImU32 color,
        int maxCount)
    {
        int count = std::min<int>(static_cast<int>(refs.size()), maxCount);

        for (int i = 0; i < count; ++i)
        {
            float t = count <= 1 ? 0.0f : static_cast<float>(i) / static_cast<float>(count);
            float angle = startAngle + t * 6.2831853f;
            float jitter = (Hash01(refs[i], 17) - 0.5f) * 0.45f;

            Vec3 pos{};
            pos.x = cosf(angle) * (ringRadius + jitter);
            pos.y = y + (Hash01(refs[i], 29) - 0.5f) * 0.5f;
            pos.z = sinf(angle) * (ringRadius + jitter);

            AddNode(nodes, refs[i], kind, pos, 0.10f, color);
        }

        if (static_cast<int>(refs.size()) > maxCount)
        {
            Vec3 pos{};
            pos.x = cosf(startAngle + 0.45f) * (ringRadius + 0.8f);
            pos.y = y;
            pos.z = sinf(startAngle + 0.45f) * (ringRadius + 0.8f);
            AddNode(nodes, "+" + std::to_string(static_cast<int>(refs.size()) - maxCount) + " more", kind, pos, 0.11f, color);
        }
    }

    void AddFallbackNodes(std::vector<RenderNode>& nodes, const AssetBrowser::AssetEntry& asset)
    {
        AddNode(nodes, "proxy mesh", "Model", Vec3{ -0.9f, 0.25f, 0.0f }, 0.16f, IM_COL32(88, 188, 255, 255));
        AddNode(nodes, "material set", "Material", Vec3{ 0.8f, -0.15f, 0.45f }, 0.14f, IM_COL32(255, 190, 86, 255));
        AddNode(nodes, "texture slots", "Texture", Vec3{ 0.35f, -0.8f, -0.75f }, 0.13f, IM_COL32(98, 230, 170, 255));

        if (asset.Type == AssetBrowser::AssetType::Stage)
            AddNode(nodes, "stage bounds", "Stage", Vec3{ 1.35f, 0.5f, -0.55f }, 0.16f, IM_COL32(190, 140, 255, 255));

        if (asset.Type == AssetBrowser::AssetType::Character)
            AddNode(nodes, "character rig", "Rig", Vec3{ -1.35f, 0.7f, 0.65f }, 0.16f, IM_COL32(255, 110, 130, 255));

        for (int i = 0; i < static_cast<int>(asset.Markers.size()) && i < 10; ++i)
        {
            float angle = static_cast<float>(i) * 0.62f;
            AddNode(nodes, asset.Markers[i], "Marker", Vec3{ cosf(angle) * 1.9f, 0.2f, sinf(angle) * 1.9f }, 0.09f, IM_COL32(210, 220, 235, 255));
        }
    }

    std::vector<RenderNode> BuildNodes(const AssetBrowser::AssetEntry& asset, const XfbinInspector::XfbinInfo& info)
    {
        std::vector<RenderNode> nodes;
        nodes.reserve(96);

        AddNode(nodes, asset.Name.empty() ? "asset" : asset.Name, "Root", Vec3{ 0.0f, 0.0f, 0.0f }, 0.20f, IM_COL32(85, 165, 255, 255));

        if (info.Valid)
        {
            AddRing(nodes, info.ModelRefs, "Model", 1.45f, 0.45f, 0.05f, IM_COL32(100, 195, 255, 255), 18);
            AddRing(nodes, info.MaterialRefs, "Material", 1.90f, -0.15f, 0.42f, IM_COL32(255, 190, 90, 255), 18);
            AddRing(nodes, info.TextureRefs, "Texture", 2.35f, -0.70f, 0.82f, IM_COL32(95, 230, 170, 255), 22);
            AddRing(nodes, info.AnimationRefs, "Animation", 2.75f, 0.55f, 1.15f, IM_COL32(255, 125, 155, 255), 16);
            AddRing(nodes, info.Chunks, "Chunk", 3.15f, 0.0f, 1.55f, IM_COL32(190, 155, 255, 255), 24);
            AddRing(nodes, info.LuaRefs, "Lua", 2.05f, 1.15f, 2.05f, IM_COL32(130, 220, 255, 255), 10);
        }

        if (nodes.size() <= 1)
            AddFallbackNodes(nodes, asset);

        return nodes;
    }

    void DrawGrid(ImDrawList* draw, const ImVec2& center, float scale)
    {
        ImU32 minor = IM_COL32(45, 78, 105, 88);
        ImU32 major = IM_COL32(70, 130, 170, 130);

        for (int i = -6; i <= 6; ++i)
        {
            ImU32 color = (i == 0) ? major : minor;
            ImVec2 a = Project(Vec3{ static_cast<float>(i), -1.35f, -6.0f }, center, scale, g_Yaw, g_Pitch, g_Zoom);
            ImVec2 b = Project(Vec3{ static_cast<float>(i), -1.35f, 6.0f }, center, scale, g_Yaw, g_Pitch, g_Zoom);
            ImVec2 c = Project(Vec3{ -6.0f, -1.35f, static_cast<float>(i) }, center, scale, g_Yaw, g_Pitch, g_Zoom);
            ImVec2 d = Project(Vec3{ 6.0f, -1.35f, static_cast<float>(i) }, center, scale, g_Yaw, g_Pitch, g_Zoom);

            draw->AddLine(a, b, color, 1.0f);
            draw->AddLine(c, d, color, 1.0f);
        }
    }

    void DrawBounds(ImDrawList* draw, const ImVec2& center, float scale)
    {
        Vec3 verts[8] =
        {
            { -2.8f, -1.1f, -2.8f }, { 2.8f, -1.1f, -2.8f },
            { 2.8f,  1.6f, -2.8f }, { -2.8f,  1.6f, -2.8f },
            { -2.8f, -1.1f,  2.8f }, { 2.8f, -1.1f,  2.8f },
            { 2.8f,  1.6f,  2.8f }, { -2.8f,  1.6f,  2.8f }
        };

        int edges[12][2] =
        {
            {0, 1}, {1, 2}, {2, 3}, {3, 0},
            {4, 5}, {5, 6}, {6, 7}, {7, 4},
            {0, 4}, {1, 5}, {2, 6}, {3, 7}
        };

        for (const auto& edge : edges)
        {
            ImVec2 a = Project(verts[edge[0]], center, scale, g_Yaw, g_Pitch, g_Zoom);
            ImVec2 b = Project(verts[edge[1]], center, scale, g_Yaw, g_Pitch, g_Zoom);
            draw->AddLine(a, b, IM_COL32(80, 155, 220, 145), 1.15f);
        }
    }

    int DrawNodes(ImDrawList* draw, const ImVec2& center, float scale, const std::vector<RenderNode>& nodes, bool canvasHovered)
    {
        std::vector<ProjectedNode> projected;
        projected.reserve(nodes.size());

        for (int i = 0; i < static_cast<int>(nodes.size()); ++i)
        {
            float depth = 0.0f;
            ImVec2 p = Project(nodes[i].Position, center, scale, g_Yaw, g_Pitch, g_Zoom, &depth);
            float radius = Clamp((nodes[i].Radius * scale * g_Zoom * 2.6f) / std::max(2.0f, depth), 4.0f, 18.0f);
            projected.push_back({ i, p, depth, radius });
        }

        if (g_ShowLinks && !projected.empty())
        {
            ImVec2 root = projected.front().Position;

            for (size_t i = 1; i < projected.size(); ++i)
                draw->AddLine(root, projected[i].Position, IM_COL32(95, 145, 190, 95), 1.0f);
        }

        ImVec2 mouse = ImGui::GetIO().MousePos;
        int hovered = -1;
        float bestDistance = 999999.0f;

        for (const ProjectedNode& item : projected)
        {
            float dx = mouse.x - item.Position.x;
            float dy = mouse.y - item.Position.y;
            float dist = sqrtf(dx * dx + dy * dy);

            if (canvasHovered && dist <= item.Radius + 6.0f && dist < bestDistance)
            {
                hovered = item.Index;
                bestDistance = dist;
            }
        }

        std::sort(projected.begin(), projected.end(), [](const ProjectedNode& a, const ProjectedNode& b) {
            return a.Depth > b.Depth;
        });

        for (const ProjectedNode& item : projected)
        {
            const RenderNode& node = nodes[item.Index];
            bool selected = item.Index == g_SelectedNode;
            bool hot = item.Index == hovered;

            ImU32 outline = selected ? IM_COL32(255, 255, 255, 255) : (hot ? IM_COL32(255, 230, 150, 255) : IM_COL32(10, 18, 26, 230));
            float radius = item.Radius + (selected ? 4.0f : (hot ? 2.0f : 0.0f));

            draw->AddCircleFilled(item.Position, radius + 2.0f, outline, 24);
            draw->AddCircleFilled(item.Position, radius, node.Color, 24);
            draw->AddCircle(item.Position, radius, IM_COL32(255, 255, 255, 80), 24, 1.0f);

            if (g_ShowLabels)
            {
                ImVec2 textPos(item.Position.x + radius + 4.0f, item.Position.y - 7.0f);
                draw->AddText(textPos, IM_COL32(235, 240, 248, 235), node.Label.c_str());
            }
        }

        return hovered;
    }

    ImU32 ShadeColor(ImU32 color, float shade)
    {
        shade = Clamp(shade, 0.35f, 1.25f);

        const int r = static_cast<int>(((color >> IM_COL32_R_SHIFT) & 0xFF) * shade);
        const int g = static_cast<int>(((color >> IM_COL32_G_SHIFT) & 0xFF) * shade);
        const int b = static_cast<int>(((color >> IM_COL32_B_SHIFT) & 0xFF) * shade);
        const int a = static_cast<int>((color >> IM_COL32_A_SHIFT) & 0xFF);

        return IM_COL32(std::min(255, r), std::min(255, g), std::min(255, b), a);
    }

    void DrawMeshPreview(ImDrawList* draw, const ImVec2& center, float scale, const MeshPreview& mesh)
    {
        if (!mesh.Loaded || mesh.Vertices.empty())
            return;

        struct ProjectedVertex
        {
            ImVec2 Position;
            float Depth = 0.0f;
            Vec3 Rotated;
        };

        struct ProjectedFace
        {
            ImVec2 A;
            ImVec2 B;
            ImVec2 C;
            ImU32 Color = IM_COL32_WHITE;
            float Depth = 0.0f;
        };

        std::vector<ProjectedVertex> projected;
        projected.reserve(mesh.Vertices.size());

        for (const MeshVertex& vertex : mesh.Vertices)
        {
            ProjectedVertex out{};
            out.Rotated = Rotate(vertex.Position, g_Yaw, g_Pitch);
            out.Position = Project(vertex.Position, center, scale, g_Yaw, g_Pitch, g_Zoom, &out.Depth);
            projected.push_back(out);
        }

        std::vector<ProjectedFace> faces;
        faces.reserve(mesh.Faces.size());

        for (const MeshFace& face : mesh.Faces)
        {
            if (face.A < 0 || face.B < 0 || face.C < 0 ||
                face.A >= static_cast<int>(projected.size()) ||
                face.B >= static_cast<int>(projected.size()) ||
                face.C >= static_cast<int>(projected.size()))
            {
                continue;
            }

            const ProjectedVertex& a = projected[face.A];
            const ProjectedVertex& b = projected[face.B];
            const ProjectedVertex& c = projected[face.C];

            const Vec3 ab{ b.Rotated.x - a.Rotated.x, b.Rotated.y - a.Rotated.y, b.Rotated.z - a.Rotated.z };
            const Vec3 ac{ c.Rotated.x - a.Rotated.x, c.Rotated.y - a.Rotated.y, c.Rotated.z - a.Rotated.z };
            Vec3 normal{};
            normal.x = ab.y * ac.z - ab.z * ac.y;
            normal.y = ab.z * ac.x - ab.x * ac.z;
            normal.z = ab.x * ac.y - ab.y * ac.x;

            const float len = std::max(0.001f, sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z));
            normal.x /= len;
            normal.y /= len;
            normal.z /= len;

            const float shade = 0.55f + std::max(0.0f, normal.y * 0.45f) + std::max(0.0f, -normal.z * 0.18f);
            const ImU32 baseColor = mesh.Vertices[face.A].Color;

            ProjectedFace out{};
            out.A = a.Position;
            out.B = b.Position;
            out.C = c.Position;
            out.Depth = (a.Depth + b.Depth + c.Depth) / 3.0f;
            out.Color = ShadeColor(baseColor, shade);
            faces.push_back(out);
        }

        std::sort(faces.begin(), faces.end(), [](const ProjectedFace& a, const ProjectedFace& b) {
            return a.Depth > b.Depth;
        });

        for (const ProjectedFace& face : faces)
        {
            if (g_ShowSurface)
                draw->AddTriangleFilled(face.A, face.B, face.C, face.Color);

            if (g_ShowWireframe)
            {
                const ImU32 wire = IM_COL32(220, 235, 255, g_ShowSurface ? 55 : 175);
                draw->AddTriangle(face.A, face.B, face.C, wire, 1.0f);
            }
        }
    }

    void DrawStatsPanel(const XfbinInspector::XfbinInfo& info, const AssetNuccDecoder::DecodedAsset& decoded, const std::vector<RenderNode>& nodes)
    {
        if (!g_ShowStats)
            return;

        ImGui::Separator();
        ImGui::Text("Render Decode");
        ImGui::Text("NUCC: %s", decoded.Valid ? "decoded" : "fallback");
        ImGui::Text("Chunks: %d | Vertices: %d | Faces: %d",
            static_cast<int>(decoded.Chunks.size()),
            static_cast<int>(decoded.Vertices.size()),
            static_cast<int>(decoded.Faces.size()));
        ImGui::Text("Hitmesh: %s | Primitive vertices: %s",
            decoded.UsedHitMesh ? "yes" : "no",
            decoded.UsedPrimitiveVertices ? "yes" : "no");
        ImGui::TextDisabled("%s", decoded.Status.c_str());
        ImGui::Text("Graph nodes: %d", static_cast<int>(nodes.size()));
        ImGui::Text("Inspector: %s", info.Valid ? "ready" : "fallback");

        if (info.Valid)
        {
            ImGui::Text("Chunks: %d  Models: %d  Materials: %d",
                static_cast<int>(info.Chunks.size()),
                static_cast<int>(info.ModelRefs.size()),
                static_cast<int>(info.MaterialRefs.size()));
            ImGui::Text("Textures: %d  Animations: %d  Lua: %d",
                static_cast<int>(info.TextureRefs.size()),
                static_cast<int>(info.AnimationRefs.size()),
                static_cast<int>(info.LuaRefs.size()));
        }

        if (g_SelectedNode >= 0 && g_SelectedNode < static_cast<int>(nodes.size()))
        {
            const RenderNode& node = nodes[g_SelectedNode];
            ImGui::Separator();
            ImGui::Text("Selected:");
            ImGui::TextWrapped("%s", node.Label.c_str());
            ImGui::TextDisabled("%s", node.Kind.c_str());
        }
    }
}

namespace AssetModelViewer
{
    void Init()
    {
        if (g_Initialized)
            return;

        g_Initialized = true;
        Logger::Info("AssetModelViewer initialized");
    }

    void Shutdown()
    {
        if (!g_Initialized)
            return;

        g_Initialized = false;
        g_LastAssetKey.clear();
        g_LastInfo = {};
        Logger::Info("AssetModelViewer shutdown");
    }

    void Draw(const AssetBrowser::AssetEntry& asset, ImVec2 size)
    {
        Init();

        ImVec2 available = ImGui::GetContentRegionAvail();

        if (size.x <= 0.0f || size.x < available.x)
            size.x = available.x;

        if (size.y <= 0.0f || size.y < available.y)
            size.y = available.y;

        if (size.x < 340.0f)
            size.x = 340.0f;

        if (size.y < 340.0f)
            size.y = 340.0f;

        std::string readablePath;
        bool hasFile = AssetPreviewResolver::ResolveReadablePath(asset, readablePath, false);
        std::string assetKey = MakeAssetKey(asset);

        if (assetKey != g_LastAssetKey)
        {
            g_LastAssetKey = assetKey;
            g_LastInfo = {};
            g_SelectedNode = -1;
            g_MeshPreview = {};

            if (g_UseInspector && (asset.Extension == ".xfbin" || asset.Extension == ".xbin" || asset.Extension == ".nud") && hasFile)
                XfbinInspector::Inspect(asset, g_LastInfo, false);
        }

        if (hasFile)
            EnsureMeshPreview(asset, readablePath);

        std::vector<RenderNode> nodes = BuildNodes(asset, g_LastInfo);

        ImGui::BeginChild("##AssetModelViewer", size, true);

        ImGui::Text("Asset Renderer");
        ImGui::SameLine();
        ImGui::TextDisabled("%s", asset.Name.c_str());

        if (hasFile)
        {
            ImGui::TextDisabled("Readable: %s", ShortLabel(readablePath, 96).c_str());
        }
        else
        {
            ImGui::TextColored(ImVec4(1.0f, 0.60f, 0.25f, 1.0f), "Readable file not resolved yet. Dump/extract the asset to inspect raw chunks.");
        }

        ImGui::Separator();

        ImVec2 canvasSize = ImGui::GetContentRegionAvail();
        canvasSize.y = std::max(260.0f, canvasSize.y - 146.0f);

        ImVec2 canvasMin = ImGui::GetCursorScreenPos();
        ImGui::InvisibleButton("##AssetRenderCanvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
        bool hovered = ImGui::IsItemHovered();

        if (hovered && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        {
            ImVec2 delta = ImGui::GetIO().MouseDelta;
            g_Yaw += delta.x * 0.008f;
            g_Pitch = Clamp(g_Pitch + delta.y * 0.006f, -1.2f, 1.2f);
            g_AutoOrbit = false;
        }

        if (hovered && ImGui::GetIO().MouseWheel != 0.0f)
            g_Zoom = Clamp(g_Zoom + ImGui::GetIO().MouseWheel * 0.08f, 0.35f, 3.25f);

        if (g_AutoOrbit)
            g_Yaw += ImGui::GetIO().DeltaTime * 0.22f;

        ImVec2 canvasMax(canvasMin.x + canvasSize.x, canvasMin.y + canvasSize.y);
        ImVec2 center((canvasMin.x + canvasMax.x) * 0.5f, (canvasMin.y + canvasMax.y) * 0.52f);
        float scale = std::min(canvasSize.x, canvasSize.y) * 0.28f;

        ImDrawList* draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(canvasMin, canvasMax, IM_COL32(5, 9, 15, 245));
        draw->AddRect(canvasMin, canvasMax, IM_COL32(70, 130, 190, 200));

        if (g_ShowGrid)
            DrawGrid(draw, center, scale);

        if (g_ShowBounds)
            DrawBounds(draw, center, scale);

        DrawMeshPreview(draw, center, scale, g_MeshPreview);

        int hoveredNode = -1;

        if (g_ShowStructureGraph)
            hoveredNode = DrawNodes(draw, center, scale, nodes, hovered);

        if (hovered && hoveredNode >= 0)
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                g_SelectedNode = hoveredNode;

            const RenderNode& node = nodes[hoveredNode];
            ImGui::SetTooltip("%s\n%s", node.Label.c_str(), node.Kind.c_str());
        }

        draw->AddText(ImVec2(canvasMin.x + 10.0f, canvasMin.y + 8.0f), IM_COL32(235, 240, 248, 255), "XFBIN / XBIN / NUD Render Preview");
        draw->AddText(ImVec2(canvasMin.x + 10.0f, canvasMax.y - 22.0f), IM_COL32(255, 190, 88, 255), "Drag orbit | Wheel zoom | Click node");

        ImGui::Checkbox("Orbit", &g_AutoOrbit);
        ImGui::SameLine();
        ImGui::Checkbox("Surface", &g_ShowSurface);
        ImGui::SameLine();
        ImGui::Checkbox("Wire", &g_ShowWireframe);
        ImGui::SameLine();
        ImGui::Checkbox("Graph", &g_ShowStructureGraph);
        ImGui::SameLine();
        ImGui::Checkbox("Grid", &g_ShowGrid);
        ImGui::SameLine();
        ImGui::Checkbox("Bounds", &g_ShowBounds);
        ImGui::SameLine();
        ImGui::Checkbox("Links", &g_ShowLinks);
        ImGui::SameLine();
        ImGui::Checkbox("Labels", &g_ShowLabels);
        ImGui::SameLine();
        ImGui::Checkbox("Stats", &g_ShowStats);

        ImGui::SliderFloat("Zoom", &g_Zoom, 0.35f, 3.25f);

        if (ImGui::Button("Reset Camera", ImVec2(120, 24)))
        {
            g_Yaw = 0.45f;
            g_Pitch = 0.35f;
            g_Zoom = 1.0f;
            g_AutoOrbit = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("Reinspect", ImVec2(100, 24)))
        {
            g_LastInfo = {};
            g_MeshPreview = {};

            if (hasFile && (asset.Extension == ".xfbin" || asset.Extension == ".xbin" || asset.Extension == ".nud"))
                XfbinInspector::Inspect(asset, g_LastInfo, false);
        }

        ImGui::SameLine();
        ImGui::TextDisabled("%s", g_MeshPreview.Status.c_str());

        DrawStatsPanel(g_LastInfo, g_LastDecoded, nodes);

        ImGui::EndChild();
    }
}
