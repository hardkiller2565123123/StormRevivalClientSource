#include "MenuActionHook.h"
#include "../Config/OnlineMenuConfig.h"
#include "../CustomMenu/MainMenuOptionRegistry.h"
#include "../CustomMenu/RealMenuOptionInjector.h"
#include "../Store/StoreReplacement.h"
#include "../Core/SRLogger.h"

namespace StormRevival::OnlineMenu::Hooks
{
    void InstallMenuActionHook()
    {
        auto& cfg = Config::Get();

        Log::Info("MenuActionHook installed.");
        Log::Info("Custom modes: 100=Settings, 101=Status, 102=Unlocks.");
        Log::Info("Store replacement enabled=" + std::string(cfg.ReuseExistingButtonFirst ? "true" : "false") +
            " StoreMode=" + std::to_string(cfg.StoreMode));

        Store::Install();
    }

    bool ShouldHijackMode(int mode)
    {
        auto& cfg = Config::Get();

        // Reuse the stock Store option as Settings for the current offline build.
        // This avoids SWF editing and gives users a real clickable menu path.
        if (cfg.ReuseExistingButtonFirst && mode == cfg.StoreMode)
            return true;

        return CustomMenu::MainMenuOptionRegistry::Instance().IsCustomMode(mode);
    }

    void HandleHijackedMode(GamePtr menuUi, int mode)
    {
        auto& cfg = Config::Get();

        if (cfg.ReuseExistingButtonFirst && mode == cfg.StoreMode)
        {
            Log::Info("Hijacked Store mode " + std::to_string(mode) + " -> StormRevival Settings.");
            Store::ShowStoreReplacement(menuUi);
            return;
        }

        if (CustomMenu::HandleSyntheticMode(menuUi, mode))
            return;

        Log::Warn("Unhandled custom synthetic menu mode: " + std::to_string(mode));
    }
}
