#include "InGameSettingsPanel.h"
#include "../Core/SRLogger.h"
#include "../Research/Progress.h"

namespace StormRevival::OnlineMenu::CustomMenu
{
    InGameSettingsState& State()
    {
        static InGameSettingsState s;
        return s;
    }

    void ShowSettingsPanel()
    {
        auto& s = State();
        Log::Info("=== StormRevival Offline Settings ===");
        Log::Info("Current player count: " + std::to_string(s.CurrentPlayerCount));
        Log::Info("Unlock All: visible stub only; disabled intentionally.");
        Log::Info("Server Status: offline online-menu research build.");
        Log::Info(Research::ProgressTable);
    }
}
