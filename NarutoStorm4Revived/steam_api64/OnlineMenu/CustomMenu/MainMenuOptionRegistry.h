#pragma once
#include <vector>
#include <string>
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    struct MainMenuOption
    {
        int Mode = 100;
        std::string Label;
        std::string Description;
        bool Enabled = true;
        bool InsertBelowOnlineMatch = true;
    };

    class MainMenuOptionRegistry
    {
    public:
        static MainMenuOptionRegistry& Instance();

        void ResetToDefaults();
        void RegisterOption(const MainMenuOption& option);
        const std::vector<MainMenuOption>& Options() const;

        bool IsCustomMode(int mode) const;
        const MainMenuOption* FindByMode(int mode) const;

    private:
        std::vector<MainMenuOption> m_options;
    };
}
