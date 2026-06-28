#include "CustomOptionSystem.h"
#include "../Core/SRLogger.h"
#include <algorithm>
#include <sstream>

namespace StormRevival::OnlineMenu::CustomUI
{
    namespace
    {
        std::vector<CustomOption> g_options;
        bool g_installed = false;
        std::string g_lastMovie;

        const char* KindName(OptionKind kind)
        {
            switch (kind)
            {
            case OptionKind::Page: return "Page";
            case OptionKind::Toggle: return "Toggle";
            case OptionKind::Action: return "Action";
            case OptionKind::Debug: return "Debug";
            default: return "Unknown";
            }
        }
    }

    void RegisterOption(const CustomOption& option)
    {
        auto it = std::find_if(g_options.begin(), g_options.end(), [&](const CustomOption& existing) { return existing.Id == option.Id; });
        if (it != g_options.end())
            *it = option;
        else
            g_options.push_back(option);

        Log::Info("[CustomUI] Registered option id=" + option.Id + " label=" + option.Label + " kind=" + KindName(option.Kind));
    }

    void RegisterDefaults()
    {
        RegisterOption({ "openarchive.root", "OpenArchive", "Main OpenArchive control panel", OptionKind::Page, true });
        RegisterOption({ "openarchive.private_match", "Private LAN Match", "Host/search private rooms on the same LAN/VPN", OptionKind::Page, true });
        RegisterOption({ "openarchive.custom_stages", "Custom Stages", "Browse and load custom stages from OpenArchive\\Stages", OptionKind::Page, true });
        RegisterOption({ "openarchive.character_select", "Character Tools", "Character select slots, costumes, roster filters, and ActionScript menu_param hooks", OptionKind::Page, true });
        RegisterOption({ "openarchive.stage_select", "Stage Tools", "Stage select pages, custom stages, and StageUtil hooks", OptionKind::Page, true });
        RegisterOption({ "openarchive.online_symbols", "Online Symbols", "net_match_menu, lobby, room, voice, ranking, and callback symbols from decompiled GFX", OptionKind::Page, true });
        RegisterOption({ "openarchive.battle_hud", "Battle HUD", "Battle HUD widgets and text/icon ActionScript bridge entries", OptionKind::Page, true });
        RegisterOption({ "openarchive.settings_symbols", "Settings UI", "Settings and system ActionScript symbol pages", OptionKind::Page, true });
        RegisterOption({ "openarchive.mods", "Mods", "Enable, disable, and order installed mods", OptionKind::Page, true });
        RegisterOption({ "openarchive.plugins", "Plugins", "Loaded DLL plugin manager", OptionKind::Page, true });
        RegisterOption({ "openarchive.debug", "Developer Tools", "Hook table, UI trace, and stage diagnostics", OptionKind::Debug, true });
    }

    void Install()
    {
        if (g_installed)
            return;
        g_installed = true;
        RegisterDefaults();
        Log::Info("[CustomUI] Installed custom option registry. Options=" + std::to_string(g_options.size()));
    }

    void Shutdown()
    {
        Log::Info("[CustomUI] Shutdown. Options kept in memory until DLL detach.");
        g_installed = false;
    }

    const std::vector<CustomOption>& GetOptions()
    {
        return g_options;
    }

    void OnFlashMovieRegistered(const char* movieName)
    {
        g_lastMovie = movieName ? movieName : "";
        Log::Info("[CustomUI] Movie registered: " + g_lastMovie);

        if (g_lastMovie.find("option") != std::string::npos ||
            g_lastMovie.find("setting") != std::string::npos ||
            g_lastMovie.find("menu") != std::string::npos ||
            g_lastMovie.find("netbattle") != std::string::npos)
        {
            Log::Info("[CustomUI] Candidate menu movie detected. Custom options are ready for injection after exact list setter is identified.");
        }
    }

    void OnFlashInvoke(const char* movie, const char* root, const char* functionName, int argc)
    {
        const std::string m = movie ? movie : "";
        const std::string f = functionName ? functionName : "";
        if (m.find("netbattlemainmenu") != std::string::npos || m.find("option") != std::string::npos || m.find("setting") != std::string::npos)
        {
            Log::Info("[CustomUI] UI call movie=" + m + " root=" + (root ? root : "<null>") + " function=" + f + " argc=" + std::to_string(argc));
        }

        // These are known safe points to log. Once the real list-population method is identified,
        // this module will call the same Flash bridge with generated OpenArchive options.
        if (f == "Initialize" || f == "Restart" || f == "SetUnLock" || f == "SetLock")
        {
            Log::Info("[CustomUI] Menu lifecycle call seen: " + f + ". Option count=" + std::to_string(g_options.size()));
        }
    }

    bool TryHandleMenuSelect(int selectedMode)
    {
        if (selectedMode < 0 || static_cast<std::size_t>(selectedMode) >= g_options.size())
            return false;

        const CustomOption& option = g_options[static_cast<std::size_t>(selectedMode)];
        Log::Info("[CustomUI] Selected custom option: " + option.Label + " (" + option.Id + ")");
        return true;
    }
}
