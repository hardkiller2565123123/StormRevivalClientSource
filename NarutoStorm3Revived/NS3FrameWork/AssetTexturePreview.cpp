#include "StdInc.h"
#include "AssetTexturePreview.h"
#include "AssetPreviewResolver.h"
#include "AssetTextureInfo.h"
#include "Logger.h"

#include <fstream>

namespace
{
    struct TextureCache
    {
        std::string Key;
        std::string Path;
        std::string Status;
        std::string Format;
        AssetTextureInfo::TextureInfo Info;
        int Width = 0;
        int Height = 0;
        bool Loaded = false;
        bool RealTexture = false;
        bool HasInfo = false;
        ID3D11ShaderResourceView* View = nullptr;
    };

    TextureCache g_Cache;

    template<typename T>
    T ReadLE(const std::vector<unsigned char>& bytes, size_t offset)
    {
        if (offset + sizeof(T) > bytes.size())
            return T{};

        T value{};
        std::memcpy(&value, bytes.data() + offset, sizeof(T));
        return value;
    }

    uint32_t FourCC(const char* text)
    {
        return
            static_cast<uint32_t>(static_cast<unsigned char>(text[0])) |
            (static_cast<uint32_t>(static_cast<unsigned char>(text[1])) << 8) |
            (static_cast<uint32_t>(static_cast<unsigned char>(text[2])) << 16) |
            (static_cast<uint32_t>(static_cast<unsigned char>(text[3])) << 24);
    }

    void ReleaseCache()
    {
        if (g_Cache.View)
        {
            g_Cache.View->Release();
            g_Cache.View = nullptr;
        }

        g_Cache = TextureCache{};
    }

    bool ReadFileBytes(const std::string& path, std::vector<unsigned char>& bytes)
    {
        bytes.clear();

        std::ifstream file(path, std::ios::binary);

        if (!file.is_open())
            return false;

        file.seekg(0, std::ios::end);
        std::streamoff size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (size <= 0)
            return false;

        bytes.resize(static_cast<size_t>(size));
        file.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(size));
        return true;
    }

    bool IsBlockCompressed(DXGI_FORMAT format, int& blockBytes)
    {
        switch (format)
        {
        case DXGI_FORMAT_BC1_UNORM:
        case DXGI_FORMAT_BC4_UNORM:
            blockBytes = 8;
            return true;
        case DXGI_FORMAT_BC2_UNORM:
        case DXGI_FORMAT_BC3_UNORM:
        case DXGI_FORMAT_BC5_UNORM:
            blockBytes = 16;
            return true;
        default:
            blockBytes = 0;
            return false;
        }
    }

    bool MapDdsFormat(
        const std::vector<unsigned char>& bytes,
        DXGI_FORMAT& outFormat,
        std::string& outName,
        size_t& outDataOffset)
    {
        outFormat = DXGI_FORMAT_UNKNOWN;
        outName.clear();
        outDataOffset = 128;

        if (bytes.size() < 128 || std::memcmp(bytes.data(), "DDS ", 4) != 0)
            return false;

        const uint32_t flags = ReadLE<uint32_t>(bytes, 80);
        const uint32_t fourCC = ReadLE<uint32_t>(bytes, 84);
        const uint32_t rgbBits = ReadLE<uint32_t>(bytes, 88);
        const uint32_t rMask = ReadLE<uint32_t>(bytes, 92);
        const uint32_t gMask = ReadLE<uint32_t>(bytes, 96);
        const uint32_t bMask = ReadLE<uint32_t>(bytes, 100);
        const uint32_t aMask = ReadLE<uint32_t>(bytes, 104);

        constexpr uint32_t kDdsFourCC = 0x00000004;
        constexpr uint32_t kDdsRGB = 0x00000040;

        if ((flags & kDdsFourCC) != 0)
        {
            if (fourCC == FourCC("DXT1"))
            {
                outFormat = DXGI_FORMAT_BC1_UNORM;
                outName = "DDS BC1/DXT1";
                return true;
            }

            if (fourCC == FourCC("DXT3"))
            {
                outFormat = DXGI_FORMAT_BC2_UNORM;
                outName = "DDS BC2/DXT3";
                return true;
            }

            if (fourCC == FourCC("DXT5"))
            {
                outFormat = DXGI_FORMAT_BC3_UNORM;
                outName = "DDS BC3/DXT5";
                return true;
            }

            if (fourCC == FourCC("ATI1") || fourCC == FourCC("BC4U"))
            {
                outFormat = DXGI_FORMAT_BC4_UNORM;
                outName = "DDS BC4";
                return true;
            }

            if (fourCC == FourCC("ATI2") || fourCC == FourCC("BC5U"))
            {
                outFormat = DXGI_FORMAT_BC5_UNORM;
                outName = "DDS BC5";
                return true;
            }

            if (fourCC == FourCC("DX10") && bytes.size() >= 148)
            {
                outFormat = static_cast<DXGI_FORMAT>(ReadLE<uint32_t>(bytes, 128));
                outDataOffset = 148;
                outName = "DDS DX10 format " + std::to_string(static_cast<int>(outFormat));
                return outFormat != DXGI_FORMAT_UNKNOWN;
            }
        }

        if ((flags & kDdsRGB) != 0 && rgbBits == 32)
        {
            if (rMask == 0x00ff0000 && gMask == 0x0000ff00 && bMask == 0x000000ff && aMask == 0xff000000)
            {
                outFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
                outName = "DDS BGRA8";
                return true;
            }

            if (rMask == 0x000000ff && gMask == 0x0000ff00 && bMask == 0x00ff0000 && aMask == 0xff000000)
            {
                outFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
                outName = "DDS RGBA8";
                return true;
            }
        }

        return false;
    }

    bool CreateTextureFromMemory(
        ID3D11Device* device,
        int width,
        int height,
        DXGI_FORMAT format,
        const std::vector<D3D11_SUBRESOURCE_DATA>& subresources,
        ID3D11ShaderResourceView** outView)
    {
        if (!device || width <= 0 || height <= 0 || format == DXGI_FORMAT_UNKNOWN || subresources.empty())
            return false;

        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = static_cast<UINT>(width);
        desc.Height = static_cast<UINT>(height);
        desc.MipLevels = static_cast<UINT>(subresources.size());
        desc.ArraySize = 1;
        desc.Format = format;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        ID3D11Texture2D* texture = nullptr;
        HRESULT hr = device->CreateTexture2D(&desc, subresources.data(), &texture);

        if (FAILED(hr) || !texture)
            return false;

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
        srvDesc.Format = format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;

        hr = device->CreateShaderResourceView(texture, &srvDesc, outView);
        texture->Release();

        return SUCCEEDED(hr) && *outView;
    }

    bool TryLoadDds(ID3D11Device* device, const std::vector<unsigned char>& bytes)
    {
        DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
        std::string formatName;
        size_t dataOffset = 128;

        if (!MapDdsFormat(bytes, format, formatName, dataOffset))
            return false;

        const int width = static_cast<int>(ReadLE<uint32_t>(bytes, 16));
        const int height = static_cast<int>(ReadLE<uint32_t>(bytes, 12));
        int mipCount = static_cast<int>(ReadLE<uint32_t>(bytes, 28));

        if (mipCount <= 0)
            mipCount = 1;

        mipCount = std::min(mipCount, 16);

        std::vector<D3D11_SUBRESOURCE_DATA> subresources;
        size_t offset = dataOffset;
        int blockBytes = 0;
        const bool compressed = IsBlockCompressed(format, blockBytes);

        for (int mip = 0; mip < mipCount; ++mip)
        {
            const int w = std::max(1, width >> mip);
            const int h = std::max(1, height >> mip);
            size_t rowPitch = 0;
            size_t slicePitch = 0;

            if (compressed)
            {
                const int blocksWide = std::max(1, (w + 3) / 4);
                const int blocksHigh = std::max(1, (h + 3) / 4);
                rowPitch = static_cast<size_t>(blocksWide * blockBytes);
                slicePitch = rowPitch * static_cast<size_t>(blocksHigh);
            }
            else
            {
                rowPitch = static_cast<size_t>(w * 4);
                slicePitch = rowPitch * static_cast<size_t>(h);
            }

            if (offset + slicePitch > bytes.size())
                break;

            D3D11_SUBRESOURCE_DATA sub{};
            sub.pSysMem = bytes.data() + offset;
            sub.SysMemPitch = static_cast<UINT>(rowPitch);
            sub.SysMemSlicePitch = static_cast<UINT>(slicePitch);
            subresources.push_back(sub);
            offset += slicePitch;
        }

        ID3D11ShaderResourceView* view = nullptr;

        if (!CreateTextureFromMemory(device, width, height, format, subresources, &view))
            return false;

        g_Cache.View = view;
        g_Cache.Width = width;
        g_Cache.Height = height;
        g_Cache.Format = formatName;
        g_Cache.Status = "DDS texture loaded on GPU.";
        g_Cache.Loaded = true;
        g_Cache.RealTexture = true;
        return true;
    }

    bool CreateByteAtlas(ID3D11Device* device, const std::vector<unsigned char>& bytes)
    {
        if (!device || bytes.empty())
            return false;

        constexpr int width = 128;
        constexpr int height = 128;
        std::vector<unsigned char> rgba(width * height * 4);

        uint32_t rolling = 0x811C9DC5u;

        for (size_t i = 0; i < rgba.size() / 4; ++i)
        {
            unsigned char a = bytes[(i * 3 + 0) % bytes.size()];
            unsigned char b = bytes[(i * 5 + 1) % bytes.size()];
            unsigned char c = bytes[(i * 7 + 2) % bytes.size()];
            rolling ^= a;
            rolling *= 16777619u;

            rgba[i * 4 + 0] = static_cast<unsigned char>(a ^ (rolling & 0xFF));
            rgba[i * 4 + 1] = static_cast<unsigned char>(b ^ ((rolling >> 8) & 0xFF));
            rgba[i * 4 + 2] = static_cast<unsigned char>(c ^ ((rolling >> 16) & 0xFF));
            rgba[i * 4 + 3] = 255;
        }

        D3D11_SUBRESOURCE_DATA sub{};
        sub.pSysMem = rgba.data();
        sub.SysMemPitch = width * 4;
        sub.SysMemSlicePitch = static_cast<UINT>(rgba.size());

        std::vector<D3D11_SUBRESOURCE_DATA> subs;
        subs.push_back(sub);

        ID3D11ShaderResourceView* view = nullptr;

        if (!CreateTextureFromMemory(device, width, height, DXGI_FORMAT_R8G8B8A8_UNORM, subs, &view))
            return false;

        g_Cache.View = view;
        g_Cache.Width = width;
        g_Cache.Height = height;
        g_Cache.Format = "Byte atlas";
        g_Cache.Status = "Unsupported texture container shown as byte atlas.";
        g_Cache.Loaded = true;
        g_Cache.RealTexture = false;
        return true;
    }

    std::string CacheKey(const AssetBrowser::AssetEntry& asset, const std::string& path)
    {
        return asset.VirtualPath + "|" + path;
    }

    void LoadPreview(const AssetBrowser::AssetEntry& asset, ID3D11Device* device, bool autoDumpBeforePreview)
    {
        std::string path;

        if (!AssetPreviewResolver::ResolveReadablePath(asset, path, autoDumpBeforePreview))
        {
            ReleaseCache();
            g_Cache.Key = asset.VirtualPath;
            g_Cache.Status = "No readable texture file yet.";
            g_Cache.Info = {};
            g_Cache.HasInfo = false;
            return;
        }

        std::string key = CacheKey(asset, path);

        if (g_Cache.Key == key && g_Cache.Loaded)
            return;

        ReleaseCache();
        g_Cache.Key = key;
        g_Cache.Path = path;
        g_Cache.HasInfo = AssetTextureInfo::Inspect(asset, g_Cache.Info, false);

        std::vector<unsigned char> bytes;

        if (!ReadFileBytes(path, bytes))
        {
            g_Cache.Status = "Could not read texture file.";
            return;
        }

        if (TryLoadDds(device, bytes))
            return;

        if (CreateByteAtlas(device, bytes))
            return;

        g_Cache.Status = "Texture preview could not be created.";
    }
}

namespace AssetTexturePreview
{
    void Shutdown()
    {
        ReleaseCache();
    }

    void Invalidate()
    {
        ReleaseCache();
    }

    void Draw(const AssetBrowser::AssetEntry& asset, ID3D11Device* device, bool autoDumpBeforePreview, const ImVec2& requestedSize)
    {
        LoadPreview(asset, device, autoDumpBeforePreview);

        ImGui::Text("Texture Preview");
        ImGui::TextDisabled("%s", g_Cache.Status.c_str());

        if (!g_Cache.Path.empty())
            ImGui::TextWrapped("%s", g_Cache.Path.c_str());

        if (g_Cache.HasInfo && g_Cache.Info.Valid)
        {
            ImGui::Text("Metadata: %dx%d | %s | Mips %d",
                g_Cache.Info.Width,
                g_Cache.Info.Height,
                g_Cache.Info.Format.c_str(),
                g_Cache.Info.MipCount);
        }

        if (!g_Cache.View)
            return;

        ImGui::Separator();

        ImVec2 available = ImGui::GetContentRegionAvail();
        ImVec2 area = requestedSize;

        if (area.x <= 0.0f)
            area.x = available.x;

        if (area.y <= 0.0f)
            area.y = std::max(180.0f, available.y - 34.0f);

        area.x = std::max(160.0f, area.x);
        area.y = std::max(160.0f, area.y);

        float aspect = g_Cache.Height > 0 ? static_cast<float>(g_Cache.Width) / static_cast<float>(g_Cache.Height) : 1.0f;
        ImVec2 imageSize = area;

        if (imageSize.x / imageSize.y > aspect)
            imageSize.x = imageSize.y * aspect;
        else
            imageSize.y = imageSize.x / std::max(0.01f, aspect);

        imageSize.x = std::max(32.0f, imageSize.x);
        imageSize.y = std::max(32.0f, imageSize.y);

        ImGui::Image(ImTextureRef(static_cast<ImTextureID>(reinterpret_cast<intptr_t>(g_Cache.View))), imageSize);

        if (!g_Cache.RealTexture)
            ImGui::TextWrapped("This visual is a byte atlas because the selected texture container is not decoded yet.");
    }
}
