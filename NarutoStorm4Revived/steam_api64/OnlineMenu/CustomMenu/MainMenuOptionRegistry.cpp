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

        MainMenuOption settings;
        settings.Mode = 100;
        settings.Label = "StormRevival Settings";
        settings.Description = "Offline options, player count, unlock stubs, and research info.";
        settings.Enabled = true;
        settings.InsertBelowOnlineMatch = true;
        RegisterOption(settings);

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
