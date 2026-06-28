#pragma once
#include <string>
#include <vector>
#include <functional>

namespace NS4GFX {

// Runtime bridge your DLL implements with the real Scaleform/GFx hooks.
// The generated wrappers call this instead of touching .gfx files directly.
class IGfxBridge {
public:
    virtual ~IGfxBridge() {}
    virtual bool Invoke(const std::string& movie, const std::string& path, const std::string& method,
                        const std::vector<std::string>& args = {}) = 0;
    virtual bool SetText(const std::string& movie, const std::string& path, const std::string& text) = 0;
    virtual bool SetVisible(const std::string& movie, const std::string& path, bool visible) = 0;
    virtual bool SetNumber(const std::string& movie, const std::string& path, double value) = 0;
};

class NullGfxBridge : public IGfxBridge {
public:
    bool Invoke(const std::string&, const std::string&, const std::string&, const std::vector<std::string>& = {}) override { return false; }
    bool SetText(const std::string&, const std::string&, const std::string&) override { return false; }
    bool SetVisible(const std::string&, const std::string&, bool) override { return false; }
    bool SetNumber(const std::string&, const std::string&, double) override { return false; }
};

void SetBridge(IGfxBridge* bridge);
IGfxBridge& Bridge();

} // namespace NS4GFX
