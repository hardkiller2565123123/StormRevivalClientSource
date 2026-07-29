#pragma once

namespace RuntimeEditorOverlay
{
    // Draws the standalone F2 runtime editor window. This is intentionally
    // separate from the F1 ImGui top-menu/dropdown so F2 feels like its own
    // tool window instead of another Debug tab.
    void Draw();
}
