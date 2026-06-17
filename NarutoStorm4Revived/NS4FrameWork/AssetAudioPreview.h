#pragma once
#include "StdInc.h"
#include "AssetBrowser.h"

namespace AssetAudioPreview
{
    void Draw(const AssetBrowser::AssetEntry& asset, bool autoDumpBeforePreview);
    void Stop();
}
