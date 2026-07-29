#pragma once

namespace RuntimeEditorOverlay
{
    bool Init();
    void Shutdown();

    void Toggle();
    bool IsOpen();

    void Update();
    void Render();
}