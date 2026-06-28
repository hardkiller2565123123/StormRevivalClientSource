#include "NS4GFX/MenuExpansion.h"
#include "NS4GFX/CustomUI.h"
#include "NS4GFX/GeneratedCategories.h"
#include <algorithm>
#include <utility>

namespace NS4GFX {
namespace {
    std::vector<MenuExpansionEntry> g_entries;

    const ASSymbol* FindFirstClass(const std::vector<const ASSymbol*>& symbols, const char* className)
    {
        auto it = std::find_if(symbols.begin(), symbols.end(), [&](const ASSymbol* symbol)
        {
            return symbol && symbol->className && std::string(symbol->className) == className;
        });
        return it == symbols.end() ? nullptr : *it;
    }

    void Upsert(MenuExpansionEntry entry)
    {
        auto it = std::find_if(g_entries.begin(), g_entries.end(), [&](const MenuExpansionEntry& existing)
        {
            return existing.id == entry.id;
        });
        if (it != g_entries.end())
            *it = std::move(entry);
        else
            g_entries.push_back(std::move(entry));
    }

    bool RenderEntry(const MenuExpansionEntry& entry, std::size_t index)
    {
        const std::string base = entry.rootPath + ".item" + std::to_string(index);
        bool ok = true;
        ok = Bridge().SetText(entry.movie, base + ".label", entry.label) && ok;
        ok = Bridge().SetText(entry.movie, base + ".desc", entry.description) && ok;
        ok = Bridge().SetVisible(entry.movie, base, true) && ok;
        return ok;
    }

    bool RenderTarget(MenuExpansionTarget target, const std::string& movie)
    {
        bool ok = false;
        std::size_t index = 0;
        for (auto& entry : g_entries)
        {
            if (entry.target != target)
                continue;

            entry.movie = movie;
            ok = RenderEntry(entry, index++) || ok;
        }
        return ok;
    }
}

void RegisterActionScriptBackedMenus()
{
    RegisterDefaultOpenArchivePages();

    const auto online = Categories::Online::Symbols();
    const auto characterSelect = Categories::CharacterSelect::Symbols();
    const auto stageSelect = Categories::StageSelect::Symbols();
    const auto battleHud = Categories::BattleHUD::Symbols();
    const auto settings = Categories::Settings::Symbols();
    const auto system = Categories::System::Symbols();
    const auto commonWidgets = Categories::CommonWidgets::Symbols();

    Upsert({ MenuExpansionTarget::OnlineMenu, "openarchive.root", "OpenArchive", "Custom options from the ActionScript menu registry.", "net_match_menu", "root.list", FindFirstClass(online, "net_match_menu") });
    Upsert({ MenuExpansionTarget::OnlineMenu, "openarchive.private_match", "Private LAN Match", "Pair only the selected host/search clients on the same LAN/VPN.", "net_match_menu", "root.list", FindFirstClass(online, "net_match_menu") });
    Upsert({ MenuExpansionTarget::OnlineMenu, "openarchive.custom_stages", "Custom Stages", "Open the stage expansion tools from the online menu.", "net_match_menu", "root.list", FindFirstClass(online, "net_match_menu") });
    Upsert({ MenuExpansionTarget::OnlineMenu, "openarchive.room_browser", "Room Browser", "Use net_match_menu room/search symbols for private local room selection.", "net_match_menu", "root.list", FindFirstClass(online, "net_match_menu") });
    Upsert({ MenuExpansionTarget::OnlineMenu, "openarchive.voice_status", "Voice/Status", "Expose voice status and player-status ActionScript calls.", "net_match_menu", "root.list", FindFirstClass(online, "net_match_menu") });

    Upsert({ MenuExpansionTarget::CharacterSelect, "characterselect.expand_slots", "Expanded Slots", "Expose extra character/costume rows through native roster expansion.", "character_select", "root.list", FindFirstClass(characterSelect, "menu_param") });
    Upsert({ MenuExpansionTarget::CharacterSelect, "characterselect.filters", "Roster Filters", "Reserved character select filter page backed by menu_param.", "character_select", "root.list", FindFirstClass(characterSelect, "menu_param") });
    Upsert({ MenuExpansionTarget::CharacterSelect, "characterselect.costumes", "Costume Pages", "Character/costume ActionScript slots reserved for expanded costume menus.", "character_select", "root.list", FindFirstClass(characterSelect, "menu_param") });

    Upsert({ MenuExpansionTarget::StageSelect, "stageselect.custom_stages", "Custom Stage List", "Expose external stages through the stage select bridge.", "stage_select", "root.list", FindFirstClass(stageSelect, "StageUtil") });
    Upsert({ MenuExpansionTarget::StageSelect, "stageselect.stage_pages", "More Stage Pages", "Reserved extra stage-page controls backed by StageSelect symbols.", "stage_select", "root.list", FindFirstClass(stageSelect, "StageUtil") });
    Upsert({ MenuExpansionTarget::StageSelect, "stageselect.preview", "Stage Preview", "Stage preview and StageUtil metadata bridge.", "stage_select", "root.list", FindFirstClass(stageSelect, "StageUtil") });

    Upsert({ MenuExpansionTarget::BattleHUD, "battlehud.widgets", "Battle HUD Widgets", "Battle HUD text, icon, and animation symbols from decompiled GFX.", "battle_hud", "root.list", battleHud.empty() ? nullptr : battleHud.front() });
    Upsert({ MenuExpansionTarget::Settings, "settings.pages", "Settings Pages", "Settings menu ActionScript classes and text setters.", "settings", "root.list", settings.empty() ? nullptr : settings.front() });
    Upsert({ MenuExpansionTarget::System, "system.dialogs", "System Dialogs", "System dialog and confirmation ActionScript symbols.", "system", "root.list", system.empty() ? nullptr : system.front() });
    Upsert({ MenuExpansionTarget::CommonWidgets, "common.text_icons", "Text/Icon Widgets", "Shared font, icon, text, and list widgets used by menu pages.", "common_widgets", "root.list", commonWidgets.empty() ? nullptr : commonWidgets.front() });
}

const std::vector<MenuExpansionEntry>& GetMenuExpansionEntries()
{
    return g_entries;
}

bool InjectOnlineCustomOptions(const std::string& movie)
{
    RegisterActionScriptBackedMenus();
    bool ok = RenderTarget(MenuExpansionTarget::OnlineMenu, movie);
    ok = Runtime().OpenPage(movie, "openarchive.root") || ok;
    return ok;
}

bool ExpandCharacterSelectUi(const std::string& movie)
{
    RegisterActionScriptBackedMenus();
    return RenderTarget(MenuExpansionTarget::CharacterSelect, movie);
}

bool ExpandStageSelectUi(const std::string& movie)
{
    RegisterActionScriptBackedMenus();
    return RenderTarget(MenuExpansionTarget::StageSelect, movie);
}

} // namespace NS4GFX
