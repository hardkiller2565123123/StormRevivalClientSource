#include "NS4GFX/CustomUI.h"
#include <utility>

namespace NS4GFX {

static CustomUIRuntime g_runtime;
CustomUIRuntime& Runtime() { return g_runtime; }

void CustomUIRuntime::RegisterPage(const CustomMenuPage& page) {
    for (auto& p : pages_) { if (p.id == page.id) { p = page; return; } }
    pages_.push_back(page);
}
const CustomMenuPage* CustomUIRuntime::FindPage(const std::string& id) const {
    for (const auto& p : pages_) if (p.id == id) return &p;
    return nullptr;
}
bool CustomUIRuntime::OpenPage(const std::string& movie, const std::string& pageId) {
    const auto* p = FindPage(pageId);
    if (!p) return false;
    Bridge().SetText(movie, "root.title", p->title);
    return RenderAsTextList(movie, "root.list", pageId);
}
bool CustomUIRuntime::RenderAsTextList(const std::string& movie, const std::string& rootPath, const std::string& pageId) {
    const auto* p = FindPage(pageId);
    if (!p) return false;
    bool ok = true;
    for (size_t i=0;i<p->options.size();++i) {
        ok = Bridge().SetText(movie, rootPath + ".item" + std::to_string(i) + ".label", p->options[i].label) && ok;
        ok = Bridge().SetText(movie, rootPath + ".item" + std::to_string(i) + ".desc", p->options[i].description) && ok;
        ok = Bridge().SetVisible(movie, rootPath + ".item" + std::to_string(i), true) && ok;
    }
    return ok;
}

void RegisterDefaultOpenArchivePages() {
    CustomMenuPage root("openarchive.root");
    root.title = "OpenArchive";
    root.options = {
        {"openarchive.lan", "Private LAN Match", "Host or search on the same LAN/VPN.", "openarchive.lan"},
        {"openarchive.custom_stages", "Custom Stages", "External stage browser.", "openarchive.custom_stages"},
        {"openarchive.mods", "Mods", "Enable, disable, and reload mods.", "openarchive.mods"},
        {"openarchive.plugins", "Plugins", "DLL plugin manager.", "openarchive.plugins"},
        {"openarchive.debug", "Developer Tools", "Diagnostics and hook status.", "openarchive.debug"}
    };
    Runtime().RegisterPage(root);

    CustomMenuPage lan("openarchive.lan"); lan.title = "Private LAN Match"; lan.options = {{"host","Host Lobby","Start a private local lobby.",""},{"search","Search Lobby","Find matching private LAN lobbies.",""},{"join","Join Direct","Connect by IP.",""}}; Runtime().RegisterPage(lan);
    CustomMenuPage stages("openarchive.custom_stages"); stages.title = "Custom Stages"; stages.options = {{"scan","Scan Stages","Read OpenArchive/Stages.",""},{"load","Load Selected","Inject selected stage once stage loader is mapped.",""}}; Runtime().RegisterPage(stages);
    CustomMenuPage debug("openarchive.debug"); debug.title = "Developer Tools"; debug.options = {{"hooks","Hook Status","Show installed hooks.",""},{"gfx","GFX Calls","Trace current movie/callbacks.",""},{"scene","Scene Info","Current scene and stage.",""}}; Runtime().RegisterPage(debug);
}

} // namespace NS4GFX
