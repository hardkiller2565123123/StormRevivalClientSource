#include "StdInc.h"
#include "AssetModelViewer.h"
#include "AssetPreviewResolver.h"
#include "Logger.h"
#include "XfbinInspector.h"
#include "imgui.h"

#include <cmath>

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

    bool g_Initialized = false;
    bool g_AutoOrbit = true;
    bool g_ShowGrid = true;
    bool g_ShowBounds = true;
    bool g_ShowLabels = true;
    bool g_ShowLinks = true;
    bool g_ShowStats = true;
    bool g_UseInspector = true;

    float g_Yaw = 0.45f;
    float g_Pitch = 0.35f;
    float g_Zoom = 1.0f;
    int g_SelectedNode = -1;

    std::string g_LastAssetKey;
    XfbinInspector::XfbinInfo g_LastInfo{};

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

    void DrawStatsPanel(const XfbinInspector::XfbinInfo& info, const std::vector<RenderNode>& nodes)
    {
        if (!g_ShowStats)
            return;

        ImGui::Separator();
        ImGui::Text("Render Graph");
        ImGui::Text("Nodes: %d", static_cast<int>(nodes.size()));
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

            if (g_UseInspector && (asset.Extension == ".xfbin" || asset.Extension == ".nud") && hasFile)
                XfbinInspector::Inspect(asset, g_LastInfo, false);
        }

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

        int hoveredNode = DrawNodes(draw, center, scale, nodes, hovered);

        if (hovered && hoveredNode >= 0)
        {
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                g_SelectedNode = hoveredNode;

            const RenderNode& node = nodes[hoveredNode];
            ImGui::SetTooltip("%s\n%s", node.Label.c_str(), node.Kind.c_str());
        }

        draw->AddText(ImVec2(canvasMin.x + 10.0f, canvasMin.y + 8.0f), IM_COL32(235, 240, 248, 255), "XFBIN / NUD Structure View");
        draw->AddText(ImVec2(canvasMin.x + 10.0f, canvasMax.y - 22.0f), IM_COL32(255, 190, 88, 255), "Drag orbit | Wheel zoom | Click node");

        ImGui::Checkbox("Orbit", &g_AutoOrbit);
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

            if (hasFile && (asset.Extension == ".xfbin" || asset.Extension == ".nud"))
                XfbinInspector::Inspect(asset, g_LastInfo, false);
        }

        DrawStatsPanel(g_LastInfo, nodes);

        ImGui::EndChild();
    }
}
