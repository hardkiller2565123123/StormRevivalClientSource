#include "MainMenuOptionRegistry.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    MainMenuOptionRegistry& MainMenuOptionRegistry::Instance()
    {
        static MainMenuOptionRegistry registry;
        return registry;
    }

    void MainMenuOptionRegistry::ResetToDefaults()
    {
        m_options.clear();

        MainMenuOption openArchive;
        openArchive.Mode = 100;
        openArchive.Label = "OpenArchive";
        openArchive.Description = "ActionScript-backed custom online menu, LAN, character, and stage tools.";
        openArchive.Enabled = true;
        openArchive.InsertBelowOnlineMatch = true;
        RegisterOption(openArchive);

        MainMenuOption status;
        status.Mode = 101;
        status.Label = "StormRevival Status";
        status.Description = "Offline online-menu status and session information.";
        status.Enabled = true;
        status.InsertBelowOnlineMatch = true;
        RegisterOption(status);

        MainMenuOption unlocks;
        unlocks.Mode = 102;
        unlocks.Label = "Unlock All";
        unlocks.Description = "Visible stub only. Does not modify saves yet.";
        unlocks.Enabled = true;
        unlocks.InsertBelowOnlineMatch = true;
        RegisterOption(unlocks);

        MainMenuOption privateLan;
        privateLan.Mode = 103;
        privateLan.Label = "Private LAN Match";
        privateLan.Description = "Host/search private local rooms on the same LAN/VPN.";
        privateLan.Enabled = true;
        privateLan.InsertBelowOnlineMatch = true;
        RegisterOption(privateLan);

        MainMenuOption customStages;
        customStages.Mode = 104;
        customStages.Label = "Custom Stages";
        customStages.Description = "StageSelect ActionScript expansion and custom stage browser.";
        customStages.Enabled = true;
        customStages.InsertBelowOnlineMatch = true;
        RegisterOption(customStages);

        MainMenuOption characterTools;
        characterTools.Mode = 105;
        characterTools.Label = "Character Tools";
        characterTools.Description = "CharacterSelect ActionScript symbols and expanded roster slots.";
        characterTools.Enabled = true;
        characterTools.InsertBelowOnlineMatch = true;
        RegisterOption(characterTools);
    }

    void MainMenuOptionRegistry::RegisterOption(const MainMenuOption& option)
    {
        for (auto& item : m_options)
        {
            if (item.Mode == option.Mode)
            {
                item = option;
                return;
            }
        }

        m_options.push_back(option);
    }

    const std::vector<MainMenuOption>& MainMenuOptionRegistry::Options() const
    {
        return m_options;
    }

    bool MainMenuOptionRegistry::IsCustomMode(int mode) const
    {
        return FindByMode(mode) != nullptr;
    }

    const MainMenuOption* MainMenuOptionRegistry::FindByMode(int mode) const
    {
        for (const auto& option : m_options)
        {
            if (option.Mode == mode)
                return &option;
        }

        return nullptr;
    }
}
