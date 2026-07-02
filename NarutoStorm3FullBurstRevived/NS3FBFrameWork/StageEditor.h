#pragma once

namespace StageEditor
{
    void Init();
    void PollHotkeys();
    void SetOpen(bool open);
    bool IsOpen();
bool WantsInputCapture();
    void DrawWindow();
    void DrawEmbeddedTools();
}
