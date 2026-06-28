#include "OpenArchiveHub.h"
#include "../MainMenu/NetBattleMainMenu.h"
#include "../CustomUI/CustomOptionSystem.h"
#include "../Core/SRLogger.h"
#include "NS4GFX/ASSymbolRegistry.h"
#include "NS4GFX/MenuExpansion.h"

#include <string>
#include <vector>

namespace StormRevival::OnlineMenu::OpenArchive
{
    namespace
    {
        struct CategoryCount
        {
            const char* Name;
            int Count;
        };

        std::vector<CategoryCount> BuildCategoryCounts()
        {
            std::vector<CategoryCount> counts =
            {
                { "Online", 0 },
                { "CharacterSelect", 0 },
                { "StageSelect", 0 },
                { "BattleHUD", 0 },
                { "CommonWidgets", 0 },
                { "Settings", 0 },
                { "System", 0 },
                { "AdventureWorld", 0 },
                { "Misc", 0 },
            };

            std::size_t symbolCount = 0;
            const NS4GFX::ASSymbol* symbols = NS4GFX::GetAllSymbols(&symbolCount);
            for (std::size_t i = 0; symbols && i < symbolCount; ++i)
            {
                const char* category = symbols[i].category ? symbols[i].category : "";
                for (auto& count : counts)
                {
                    if (std::string(category) == count.Name)
                    {
                        ++count.Count;
                        break;
                    }
                }
            }

            return counts;
        }

        std::string BuildHubText()
        {
            NS4GFX::RegisterActionScriptBackedMenus();
            CustomUI::RegisterDefaults();

            std::size_t symbolCount = 0;
            NS4GFX::GetAllSymbols(&symbolCount);

            std::string text;
            text += "OpenArchive Custom Menu\\n";
            text += "ActionScript symbols loaded: " + std::to_string(symbolCount) + "\\n\\n";
            text += "Selectable sections:\\n";

            const auto& entries = NS4GFX::GetMenuExpansionEntries();
            for (const auto& entry : entries)
            {
                text += "> " + entry.label;
                if (!entry.description.empty())
                    text += " - " + entry.description;
                text += "\\n";
            }

            text += "\\nRegistered custom options:\\n";
            for (const auto& option : CustomUI::GetOptions())
            {
                if (!option.Enabled)
                    continue;

                text += "> " + option.Label + " - " + option.Description + "\\n";
            }

            text += "\\nActionScript categories:\\n";
            for (const auto& count : BuildCategoryCounts())
            {
                if (count.Count <= 0)
                    continue;

                text += "> " + std::string(count.Name) + ": " + std::to_string(count.Count) + " classes\\n";
            }

            text += "\\nPrivate LAN: host/search from the same LAN/VPN.\\n";
            text += "Character/stage expansion: registered and ready for the native hook path.";
            return text;
        }
    }

    void Install()
    {
        NS4GFX::RegisterActionScriptBackedMenus();
        CustomUI::RegisterDefaults();
        Log::Info("[OpenArchive] Installed ActionScript-backed custom online menu hub.");
        Log::Info("[OpenArchive] Entries=" + std::to_string(NS4GFX::GetMenuExpansionEntries().size()));
    }

    void Show(GamePtr ui)
    {
        Install();
        MainMenu::VoiceIn(ui);
        MainMenu::RenameStoreButtonToOpenArchive(ui);
        const std::string hubText = BuildHubText();
        MainMenu::SetVoiceText(ui, hubText.c_str());
        MainMenu::Message(ui, "OpenArchive");
        Log::Info("[OpenArchive] Opened custom option hub from online menu.");
    }
}
