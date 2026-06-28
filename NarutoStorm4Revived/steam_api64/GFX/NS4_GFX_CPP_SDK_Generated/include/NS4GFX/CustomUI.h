#pragma once
#include "NS4GFX/GfxBridge.h"
#include <string>
#include <vector>

namespace NS4GFX {

struct CustomMenuOption {
    std::string id;
    std::string label;
    std::string description;
    std::string targetPage;
};

class CustomMenuPage {
public:
    explicit CustomMenuPage(std::string pageId = {}) : id(std::move(pageId)) {}
    std::string id;
    std::string title;
    std::vector<CustomMenuOption> options;
};

class CustomUIRuntime {
public:
    void RegisterPage(const CustomMenuPage& page);
    const CustomMenuPage* FindPage(const std::string& id) const;
    bool OpenPage(const std::string& movie, const std::string& pageId);
    bool RenderAsTextList(const std::string& movie, const std::string& rootPath, const std::string& pageId);
private:
    std::vector<CustomMenuPage> pages_;
};

CustomUIRuntime& Runtime();
void RegisterDefaultOpenArchivePages();

} // namespace NS4GFX
