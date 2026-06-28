// Replace OnlineMenu startup spam with this compact version.

#include "QuietLogFilter.h"
#include "RuntimeSafetyGate.h"
#include "Logger.h"

namespace StormRevival::OnlineMenu
{
    void LogOnlineMenuStartupQuiet()
    {
        RuntimeSafetyGate::Initialize();

        if (QuietLogFilter::ShouldLog(LogCategory::Lifecycle, "OnlineMenuStartup"))
            Logger::Info("[OnlineMenu] initialized");

        if (QuietLogFilter::ShouldLog(LogCategory::OnlineMenuResearch))
        {
            Logger::Info("[OnlineMenu] research/debug logging enabled");
            // Only print the long research wall in debug mode.
        }

        if (!RuntimeSafetyGate::Allow(RuntimePatchKind::OnlineMenuMutation))
        {
            Logger::Warn("[OnlineMenu] custom menu mutation disabled for unsupported EXE");
            return;
        }

        Logger::Info("[OnlineMenu] custom menu mutation enabled");
    }

    bool ShouldInstallStoreReplacement()
    {
        return RuntimeSafetyGate::Allow(RuntimePatchKind::StoreReplacement);
    }

    bool ShouldInstallSyntheticModes()
    {
        return RuntimeSafetyGate::Allow(RuntimePatchKind::SyntheticMenuMode);
    }

    bool ShouldPrintHookPlan()
    {
        return QuietLogFilter::ShouldLog(LogCategory::HookPlan);
    }
}
