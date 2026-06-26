#pragma once

#include "StdInc.h"

namespace TitleMusicOverride
{
    bool Init();
    void Shutdown();
    bool Restart();

    bool IsEnabled();
    bool IsPlaying();
    std::string AudioFolder();
    std::string TitleMusicPath();
    std::string Status();
}
