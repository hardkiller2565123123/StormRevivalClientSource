#include "NS4GFX/CustomUI.h"
#include <iostream>

class DebugBridge : public NS4GFX::IGfxBridge {
public:
    bool Invoke(const std::string& movie, const std::string& path, const std::string& method,
                const std::vector<std::string>& args = {}) override {
        std::cout << "Invoke " << movie << " " << path << "." << method << "\n";
        return true;
    }
    bool SetText(const std::string& movie, const std::string& path, const std::string& text) override {
        std::cout << "SetText " << movie << " " << path << " = " << text << "\n";
        return true;
    }
    bool SetVisible(const std::string& movie, const std::string& path, bool visible) override {
        std::cout << "SetVisible " << movie << " " << path << " = " << visible << "\n";
        return true;
    }
    bool SetNumber(const std::string& movie, const std::string& path, double value) override {
        std::cout << "SetNumber " << movie << " " << path << " = " << value << "\n";
        return true;
    }
};

void ExampleUse() {
    static DebugBridge bridge;
    NS4GFX::SetBridge(&bridge);
    NS4GFX::RegisterDefaultOpenArchivePages();
    NS4GFX::Runtime().OpenPage("net_match_menu", "openarchive.root");
}
