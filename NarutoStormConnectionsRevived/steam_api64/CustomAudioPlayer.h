#pragma once

#include "StdInc.h"

namespace CustomAudioPlayer
{
    bool Init();
    void Shutdown();

    bool HasTitleTrack();
    bool PlayTitleLoop();
    void StopTitle();
    void FadeOutTitle(int durationMs = 750);
    bool IsTitlePlaying();

    std::wstring TitlePath();
}
