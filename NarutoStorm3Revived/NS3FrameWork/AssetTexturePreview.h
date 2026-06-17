#pragma once
#include "StdInc.h"
#include "AssetBrowser.h"
#include "imgui.h"

namespace AssetTexturePreview
{
    void Shutdown();
    void Invalidate();
    void Draw(const AssetBrowser::AssetEntry& asset, ID3D11Device* device, bool autoDumpBeforePreview, const ImVec2& requestedSize);
}
