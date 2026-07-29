#include "StdInc.h"
#include "HookText.h"
#include "Logger.h"

#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <shellapi.h>

namespace
{
    constexpr uintptr_t kGetTextRVA = 0x75D8D0; // sub_14075D8D0
    constexpr uintptr_t kGithubButtonRVA = 0x45BEB4; // sub_14045BEB4
    constexpr uintptr_t kSceneChangeRVA = 0x74D040; // sub_14074D040

    using GetTextById_t = const char* (__fastcall*)(__int64 textId);
    using TitleButton_t = __int64(__fastcall*)(__int64 a1);
    using SceneChange_t = __int64(__fastcall*)(void* sceneMgr, unsigned int sceneId);

    GetTextById_t oGetTextById = nullptr;
    TitleButton_t oTitleGithubButton = nullptr;
    SceneChange_t oSceneChange = nullptr;

    uintptr_t g_GetTextAddr = 0;
    uintptr_t g_GithubButtonAddr = 0;
    uintptr_t g_SceneChangeAddr = 0;

    ULONGLONG g_LastGithubOpen = 0;

    static const std::unordered_map<std::string, const char*> g_TextOverrides =
    {
        { "NS3_title_msg03", "https://github.com/hardkiller2565123123" },
        { "NS3_title_msg04", "Thanks For Using NSRevival" },
        { "NS3_DirectInput_25_STEAM", "Start Playing Revival Client" },
        { "NS3_option_002", "Options" },
        { "NS3_title_msg02", "Checking Storm Revival Database..." },

        { "network_agreement", "Revival Network Agreement" },
        { "network_agreement2", "Revival Network Agreement" },
        { "network_agreement_message", "You are connecting to the community Revival network." },
        { "network_agreement_ok", "Revival Accept" },
        { "network_agreement_ng", "Revival Decline" },
        { "network_agreement_select", "Select an option." },
        { "network_agreement_view", "View Agreement" },
        { "network_privacy", "Revival Privacy Notice" },
        { "network_privacy2", "Revival Privacy Notice" },

        { "networkmode_187", "Online Revival Network" },
        { "network_sys_039", "Revival Network Notice" },

        { "MATCH_MENU_TEXT_1", "Create Revival Lobby" },
        { "MATCH_MENU_TEXT_2", "Search RevivalLobby" },
        { "MATCH_MENU_TEXT_3", "Invite / Friends" },
        { "MATCH_MENU_TEXT_4", "Player List" },
        { "MATCH_MENU_TEXT_5", "Back" },

        { "TEXT_SESSION_NAME", "Lobby Name" },
        { "TEXT_NUMBER_PLAYER", "Players" },
        { "TEXT_JOIN", "Join Lobby" },
        { "TEXT_JOIN_TO", "Join Revival Tournament" },
        { "TEXT_REGION", "Region" },
        { "TEXT_RULE_EN", "Rules" },
        { "TEXT_RULE_TO", "RevivalTournament Rules" },
        { "TEXT_DISCONNECTION", "Disconnects" },

        { "TEXT_BATTLE_PLAY", "Revival Player Match" },
        { "TEXT_BATTLE_RANK", "Revival Ranked Match" },
        { "TEXT_WIN_PLAY", "Player Wins" },
        { "TEXT_LOSE_PLAY", "Player Losses" },
        { "TEXT_WIN_RANK", "Ranked Wins" },
        { "TEXT_LOSE_RANK", "Ranked Losses" },
        { "TEXT_ENDLESS", "Endless Revival Battle" },
        { "TEXT_CHAMPION", "Revival Champion" },

        { "TEXT_RANK_NAME", "Rank" },
        { "TEXT_TITLE_00", "Title" },
        { "TEXT_TITLE_01", "Subtitle" },
        { "TEXT_USER_ID", "Player ID" },
        { "TEXT_USER_BP", "Battle Points" },
        { "TEXT_BP", "BP" },
        { "TEXT_RANK", "Rank" },
        { "TEXT_AREA", "Area" },

        { "MSG_Yes", "Yes" },
        { "MSG_No", "No" },
        { "MSG_ReturnToTitle", "Return to Revival Title" },
        { "MSG_Save", "Save" },
        { "MSG_PrevPage", "Previous Revival Page" },
        { "MSG_NextPage", "Next Revival Page" },
    };

    void OpenGithub()
    {
        ULONGLONG now = GetTickCount64();

        if (now - g_LastGithubOpen < 1500)
            return;

        g_LastGithubOpen = now;

        Logger::Info("HookText: opening GitHub");

        ShellExecuteA(
            nullptr,
            "open",
            "https://github.com/hardkiller2565123123",
            nullptr,
            nullptr,
            SW_SHOWNORMAL);
    }

    const char* __fastcall hkGetTextById(__int64 textId)
    {
        const char* id = reinterpret_cast<const char*>(textId);

        if (!id)
            return oGetTextById ? oGetTextById(textId) : "";

        auto it = g_TextOverrides.find(id);
        if (it != g_TextOverrides.end())
            return it->second;

        return oGetTextById ? oGetTextById(textId) : "";
    }

    __int64 __fastcall hkTitleGithubButton(__int64 a1)
    {
        OpenGithub();

        if (a1)
        {
            *reinterpret_cast<int*>(a1 + 96) = 1;
            *reinterpret_cast<int*>(a1 + 84) = 14;
        }

        return 0;
    }

    __int64 __fastcall hkSceneChange(void* sceneMgr, unsigned int sceneId)
    {
        if (sceneId == 0x39 || sceneId == 0x3A)
        {
            Logger::Info("HookText: blocked credits/staff-roll scene");
            OpenGithub();
            return 0;
        }

        return oSceneChange ? oSceneChange(sceneMgr, sceneId) : 0;
    }

    bool InstallHook(uintptr_t addr, void* detour, void** original, const char* name)
    {
        MH_STATUS status = MH_CreateHook(
            reinterpret_cast<void*>(addr),
            detour,
            original);

        if (status != MH_OK)
        {
            Logger::Error(std::string(name) + " MH_CreateHook failed status=" + std::to_string(status));
            return false;
        }

        status = MH_EnableHook(reinterpret_cast<void*>(addr));

        if (status != MH_OK)
        {
            Logger::Error(std::string(name) + " MH_EnableHook failed status=" + std::to_string(status));
            return false;
        }

        Logger::Info(std::string(name) + " installed");
        return true;
    }

    void LogAddress(const char* name, uintptr_t addr, uintptr_t rva)
    {
        MEMORY_BASIC_INFORMATION mbi{};
        VirtualQuery(reinterpret_cast<void*>(addr), &mbi, sizeof(mbi));

        std::ostringstream info;
        info << std::hex
            << name
            << " Address=0x" << addr
            << " Base=0x" << reinterpret_cast<uintptr_t>(mbi.BaseAddress)
            << " Protect=0x" << mbi.Protect
            << " State=0x" << mbi.State
            << " RVA=0x" << rva;

        Logger::Info(info.str());
    }
}

namespace HookText
{
    bool Install()
    {
        HMODULE exe = GetModuleHandleA("NSUNS3.exe");
        if (!exe)
        {
            Logger::Error("HookText: failed to locate NSUNS3.exe");
            return false;
        }

        uintptr_t base = reinterpret_cast<uintptr_t>(exe);

        g_GetTextAddr = base + kGetTextRVA;
        g_GithubButtonAddr = base + kGithubButtonRVA;
        g_SceneChangeAddr = base + kSceneChangeRVA;

        LogAddress("HookText GetTextById", g_GetTextAddr, kGetTextRVA);
        LogAddress("HookText GitHubButton", g_GithubButtonAddr, kGithubButtonRVA);
        LogAddress("HookText SceneChange", g_SceneChangeAddr, kSceneChangeRVA);

        if (!InstallHook(
            g_GetTextAddr,
            reinterpret_cast<void*>(&hkGetTextById),
            reinterpret_cast<void**>(&oGetTextById),
            "HookText GetTextById"))
            return false;

        if (!InstallHook(
            g_GithubButtonAddr,
            reinterpret_cast<void*>(&hkTitleGithubButton),
            reinterpret_cast<void**>(&oTitleGithubButton),
            "HookText GitHubButton"))
            return false;

        if (!InstallHook(
            g_SceneChangeAddr,
            reinterpret_cast<void*>(&hkSceneChange),
            reinterpret_cast<void**>(&oSceneChange),
            "HookText SceneChange"))
            return false;

        Logger::Info("HookText installed successfully");
        return true;
    }

    void Shutdown()
    {
        if (g_GetTextAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_GetTextAddr));

        if (g_GithubButtonAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_GithubButtonAddr));

        if (g_SceneChangeAddr)
            MH_DisableHook(reinterpret_cast<void*>(g_SceneChangeAddr));

        Logger::Info("HookText shutdown");
    }
}