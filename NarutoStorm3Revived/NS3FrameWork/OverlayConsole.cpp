#include "StdInc.h"
#include "OverlayConsole.h"

#include "Logger.h"
#include "SteamDiagnostics.h"
#include "SupportBundle.h"
#include "CrashHandler.h"
#include "AssetBrowser.h"
#include "AssetPreloadManager.h"
#include "LuaManager.h"

namespace
{
    std::vector<std::string> g_Lines;

    void Push(const std::string& line)
    {
        g_Lines.push_back(line);

        if (g_Lines.size() > 400)
            g_Lines.erase(g_Lines.begin(), g_Lines.begin() + 100);
    }

    std::string Lower(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(),
            [](unsigned char c)
            {
                return static_cast<char>(std::tolower(c));
            });

        return s;
    }
}

namespace OverlayConsole
{
    bool Init()
    {
        Push("NS3 Revived console ready. Type help.");
        Logger::Info("OverlayConsole initialized");
        return true;
    }

    void Shutdown()
    {
        g_Lines.clear();
        Logger::Info("OverlayConsole shutdown");
    }

    void AddLine(const std::string& line)
    {
        Push(line);
    }

    void Clear()
    {
        g_Lines.clear();
    }

    const std::vector<std::string>& GetLines()
    {
        return g_Lines;
    }

    CommandResult Execute(const std::string& commandLine)
    {
        CommandResult result{};
        std::string cmd = Lower(commandLine);

        Push("> " + commandLine);

        if (cmd == "help")
        {
            result.Handled = true;
            result.Message =
                "Commands: help, fps, asset_rescan, asset_preload, asset_cache_save, "
                "asset_cache_load, lua_rescan, lua_dump, lua_clear, mods_reload, log_flush, log_path, log_tail, log_level, log_mark, diag_report, support_bundle, crash_last, breadcrumbs, clear";
        }
        else if (cmd == "fps")
        {
            result.Handled = true;
            result.Message = "FPS command received.";
        }
        else if (cmd == "asset_rescan")
        {
            AssetBrowser::StartAsyncScan(true);
            result.Handled = true;
            result.Message = "Asset rescan started.";
        }
        else if (cmd == "asset_preload")
        {
            AssetPreloadManager::StartFullPreload(false);
            result.Handled = true;
            result.Message = "Asset preload started.";
        }
        else if (cmd == "asset_cache_save")
        {
            AssetBrowser::SaveCache();
            result.Handled = true;
            result.Message = "Asset cache saved.";
        }
        else if (cmd == "asset_cache_load")
        {
            AssetBrowser::LoadCache();
            result.Handled = true;
            result.Message = "Asset cache loaded.";
        }
        else if (cmd == "lua_rescan")
        {
            LuaManager::Rescan();
            result.Handled = true;
            result.Message = "Lua rescan complete.";
        }
        else if (cmd == "lua_dump")
        {
            LuaManager::DumpKnownGamePaths();
            result.Handled = true;
            result.Message = "Known Lua paths dumped.";
        }
        else if (cmd == "lua_clear")
        {
            LuaManager::ClearConsoleLog();
            result.Handled = true;
            result.Message = "Lua console log cleared.";
        }
        else if (cmd == "mods_reload")
        {
            result.Handled = true;
            result.Message = "Mod reload requested.";
            Logger::Info("OverlayConsole: mods_reload requested");
        }

        else if (cmd == "log_flush")
        {
            Logger::Flush();
            result.Handled = true;
            result.Message = "Log flushed: " + Logger::GetLogPath();
        }
        else if (cmd == "log_path")
        {
            result.Handled = true;
            result.Message = "Log path: " + Logger::GetLogPath();
        }
        else if (cmd == "log_tail")
        {
            result.Handled = true;
            const auto recent = Logger::SnapshotRecent(40);
            for (const auto& line : recent)
                Push(line);
            result.Message = "Printed recent log lines: " + std::to_string(recent.size());
        }
        else if (cmd.rfind("log_level ", 0) == 0)
        {
            const std::string level = cmd.substr(10);
            result.Handled = true;
            if (Logger::SetMinimumLevelFromText(level))
                result.Message = std::string("Logger level set to ") + Logger::LevelName(Logger::GetMinimumLevel());
            else
                result.Message = "Unknown log level. Use trace, info, warn, error, fatal.";
        }
        else if (cmd.rfind("log_mark ", 0) == 0)
        {
            const std::string text = commandLine.substr(9);
            Logger::Mark(text.empty() ? "manual overlay marker" : text);
            result.Handled = true;
            result.Message = "Log marker written.";
        }
        else if (cmd == "diag_report")
        {
            const std::string path = SteamDiagnostics::WriteReport();
            result.Handled = true;
            result.Message = path.empty() ? "Diagnostics report failed." : "Diagnostics report written: " + path;
        }
        else if (cmd == "support_bundle" || cmd == "log_report" || cmd == "crash_report")
        {
            const std::string path = SupportBundle::Write(cmd);
            result.Handled = true;
            result.Message = path.empty() ? "Support bundle failed." : "Support bundle written: " + path;
        }
        else if (cmd == "crash_last")
        {
            result.Handled = true;
            result.Message = "Last exception: " + SteamDiagnostics::LastException() + " | Last dump: " + CrashHandler::LastDumpPath();
        }
        else if (cmd == "breadcrumbs")
        {
            result.Handled = true;
            const auto crumbs = SteamDiagnostics::Snapshot(30);
            for (const auto& crumb : crumbs)
            {
                Push(std::to_string(crumb.TickMs) + "ms [" + std::to_string(crumb.ThreadId) + "] " + crumb.Category + ": " + crumb.Name + (crumb.Detail.empty() ? "" : " | " + crumb.Detail));
            }
            result.Message = "Printed breadcrumbs: " + std::to_string(crumbs.size());
        }
        else if (cmd == "clear")
        {
            Clear();
            result.Handled = true;
            result.Message = "";
        }
        else
        {
            result.Handled = false;
            result.Message = "Unknown command. Type help.";
        }

        if (!result.Message.empty())
            Push(result.Message);

        return result;
    }
}