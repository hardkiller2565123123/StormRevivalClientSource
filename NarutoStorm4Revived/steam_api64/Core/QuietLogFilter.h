#pragma once
#include <string>
#include <unordered_map>
#include <mutex>

namespace StormRevival
{
    enum class LogCategory
    {
        Lifecycle,
        Crash,
        HookSummary,
        Network,
        Storage,
        SteamCall,
        SteamInterface,
        OnlineMenuResearch,
        HookPlan,
        DebugSpam
    };

    class QuietLogFilter
    {
    public:
        static void Initialize();
        static bool ShouldLog(LogCategory category, const std::string& key = {});
        static bool Verbose();

    private:
        static bool ShouldLogRepeated(const std::string& key);
    };
}
