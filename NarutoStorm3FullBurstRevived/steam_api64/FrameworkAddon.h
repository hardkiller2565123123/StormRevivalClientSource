#pragma once

namespace FrameworkAddon
{
    bool IsAvailable();
    bool IsLoaded();
    const char* Name();
    const char* StatusText();
    const char* PathText();
    void EnsureLoaded();
    bool Load();
    void DrawClientPanel();
    void DrawTabPanel(int tab);
    void DrawFrameOverlay();
bool WantsInputCapture();
    void Shutdown();
}
