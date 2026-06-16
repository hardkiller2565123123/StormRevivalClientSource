#include "StdInc.h"
#include "FrameworkAddon.h"
#include "imgui.h"

namespace FrameworkAddon
{
    bool IsAvailable() { return false; }
    bool IsLoaded() { return false; }
    const char* Name() { return "LAN-only release"; }
    const char* StatusText() { return "Framework add-on removed for this LAN-only release."; }
    const char* PathText() { return ""; }
    void EnsureLoaded() {}
    bool Load() { return false; }
    void DrawClientPanel()
    {
        ImGui::TextUnformatted("LAN-only release");
        ImGui::TextWrapped("Framework add-on support is removed from this package.");
    }
    void DrawTabPanel(int) {}
    void BindRenderState(ID3D11Device*, ID3D11DeviceContext*, HWND, int) {}
    void Shutdown() {}
}
