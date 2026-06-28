#include "QuietLogFilter.h"
#include "SteamConfig.h"
#include <unordered_map>
#include <mutex>

namespace StormRevival
{
    static bool g_Init = false;
    static bool g_Verbose = false;
    static bool g_LogSteamCalls = false;
    static bool g_LogSteamInterfaces = false;
    static bool g_LogHookPlan = false;
    static bool g_LogOnlineMenuResearch = false;
    static bool g_LogRepeated = false;
    static std::mutex g_Mutex;
    static std::unordered_map<std::string, unsigned> g_Counts;

    void QuietLogFilter::Initialize()
    {
        if (g_Init)
            return;

        const std::string level = SteamConfig::GetString("log_level", "normal");
        g_Verbose = (level == "debug" || level == "verbose");

        g_LogSteamCalls = SteamConfig::GetBool("log_steam_calls", g_Verbose);
        g_LogSteamInterfaces = SteamConfig::GetBool("log_steam_interfaces", g_Verbose);
        g_LogHookPlan = SteamConfig::GetBool("log_hook_plan", g_Verbose);
        g_LogOnlineMenuResearch = SteamConfig::GetBool("log_online_menu_research", g_Verbose);
        g_LogRepeated = SteamConfig::GetBool("log_repeated_messages", false);
        g_Init = true;
    }

    bool QuietLogFilter::Verbose()
    {
        Initialize();
        return g_Verbose;
    }

    bool QuietLogFilter::ShouldLogRepeated(const std::string& key)
    {
        if (key.empty())
            return true;

        std::lock_guard<std::mutex> lock(g_Mutex);
        unsigned& count = g_Counts[key];
        ++count;

        if (g_LogRepeated)
            return true;

        // Log first hit, then powers of 10 only: x1, x10, x100, x1000.
        return count == 1 || count == 10 || count == 100 || count == 1000 || count == 10000;
    }

    bool QuietLogFilter::ShouldLog(LogCategory category, const std::string& key)
    {
        Initialize();

        switch (category)
        {
        case LogCategory::Lifecycle:
        case LogCategory::Crash:
        case LogCategory::HookSummary:
        case LogCategory::Network:
        case LogCategory::Storage:
            return ShouldLogRepeated(key);

        case LogCategory::SteamCall:
            return g_LogSteamCalls && ShouldLogRepeated(key);

        case LogCategory::SteamInterface:
            return g_LogSteamInterfaces && ShouldLogRepeated(key);

        case LogCategory::OnlineMenuResearch:
            return g_LogOnlineMenuResearch;

        case LogCategory::HookPlan:
            return g_LogHookPlan;

        case LogCategory::DebugSpam:
            return g_Verbose && ShouldLogRepeated(key);

        default:
            return false;
        }
    }
}
