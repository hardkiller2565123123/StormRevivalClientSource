#pragma once
#include "NS4GFX/ASSymbolRegistry.h"
#include <string>
#include <vector>

namespace NS4GFX {

enum class MenuExpansionTarget {
    OnlineMenu,
    CharacterSelect,
    StageSelect,
    BattleHUD,
    Settings,
    System,
    CommonWidgets
};

struct MenuExpansionEntry {
    MenuExpansionTarget target;
    std::string id;
    std::string label;
    std::string description;
    std::string movie;
    std::string rootPath;
    const ASSymbol* symbol;
};

void RegisterActionScriptBackedMenus();
const std::vector<MenuExpansionEntry>& GetMenuExpansionEntries();
bool InjectOnlineCustomOptions(const std::string& movie);
bool ExpandCharacterSelectUi(const std::string& movie);
bool ExpandStageSelectUi(const std::string& movie);

} // namespace NS4GFX
