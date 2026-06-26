#include "DX11OverlayInternal.h"
#include "SteamConfig.h"
#include "SteamLobbyManager.h"
#include "SteamOfflineServer.h"
#include "SteamDiagnostics.h"
#include "OnlineMenu/OnlineMenuHubStub.h"

namespace
{
    const char* g_OnlineMenuAction = "Pick a Storm Revival online action.";
    char g_RoomCodeInput[32]{};
    char g_RadminAddressInput[128]{};
    char g_LobbyPasswordInput[64]{};
    char g_RadminPeersInput[512]{};
    bool g_RadminInputsLoaded = false;

    void LoadRadminInputs()
    {
        if (g_RadminInputsLoaded)
            return;

        const SteamConfig::Config& config = SteamConfig::Get();
        strncpy_s(g_RadminAddressInput, config.CustomServerHost.c_str(), _TRUNCATE);

        std::string peers;
        for (const std::string& peer : config.RadminPeers)
        {
            if (!peers.empty())
                peers += ",";
            peers += peer;
        }
        strncpy_s(g_RadminPeersInput, peers.c_str(), _TRUNCATE);
        g_RadminInputsLoaded = true;
    }

    void OnlineActionButton(const char* label, const char* status)
    {
        if (ImGui::Button(label, ImVec2(190.0f, 0.0f)))
        {
            g_OnlineMenuAction = status;
            Logger::Info(std::string("Storm Revival online menu action: ") + label);
        }
    }

    std::vector<std::string> ParsePeers(const char* text)
    {
        std::vector<std::string> peers;
        std::stringstream stream(text ? text : "");
        std::string item;

        while (std::getline(stream, item, ','))
        {
            item.erase(item.begin(), std::find_if(item.begin(), item.end(), [](unsigned char c)
            {
                return std::isspace(c) == 0;
            }));
            item.erase(std::find_if(item.rbegin(), item.rend(), [](unsigned char c)
            {
                return std::isspace(c) == 0;
            }).base(), item.end());

            if (!item.empty())
                peers.push_back(item);
        }

        std::sort(peers.begin(), peers.end());
        peers.erase(std::unique(peers.begin(), peers.end()), peers.end());
        return peers;
    }

    void SaveRadminSettings()
    {
        SteamConfig::Config& config = SteamConfig::Mutable();
        config.CurrentMode = SteamConfig::Mode::Offline;
        config.LanOnly = true;
        config.EnableLocalMatchmaking = true;
        config.EnableEmbeddedMasterServer = true;
        config.CustomServerHost = g_RadminAddressInput[0] ? g_RadminAddressInput : "127.0.0.1";
        config.CustomServerPort = 47584;
        config.RadminPeers = ParsePeers(g_RadminPeersInput);
        SteamConfig::Save();

        g_OnlineMenuAction = "Saved LAN/Radmin settings. Restarting the game is recommended after changing peer lists.";
        Logger::Info("Storm Revival saved LAN/Radmin settings");
    }
}

void DrawOnlinePage()
{
    LoadRadminInputs();

    ImGui::TextUnformatted("LAN Online");
    ImGui::Separator();
    ImGui::TextWrapped("This release uses LAN/offline discovery only. Hosted master, account, friend, invite, leaderboard sync, and relay services are removed.");
    ImGui::Spacing();
    ImGui::Text("LAN discovery port: %u", static_cast<unsigned>(SteamOfflineServer::GetPort()));
    ImGui::Text("Visible LAN lobbies: %d", SteamLobbyManager::RefreshNetworkLobbies(0));
    const std::string room = SteamLobbyManager::GetCurrentRoomCode();
    if (!room.empty())
        ImGui::Text("Current room code: %s", room.c_str());
    ImGui::TextWrapped("Last join status: %s", SteamLobbyManager::GetLastJoinError().c_str());

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextUnformatted("Radmin / Direct LAN");
    ImGui::TextWrapped("Use the same Radmin network, allow UDP 47584 through Windows Firewall, and put your friend's Radmin IPv4 here if broadcast discovery does not find them.");
    ImGui::InputText("Friend Radmin IP", g_RadminAddressInput, IM_ARRAYSIZE(g_RadminAddressInput));
    ImGui::InputText("Known peers, comma separated", g_RadminPeersInput, IM_ARRAYSIZE(g_RadminPeersInput));
    ImGui::InputText("Room code", g_RoomCodeInput, IM_ARRAYSIZE(g_RoomCodeInput));
    ImGui::InputText("Password", g_LobbyPasswordInput, IM_ARRAYSIZE(g_LobbyPasswordInput), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Save Radmin Settings", ImVec2(190.0f, 0.0f)))
        SaveRadminSettings();
    ImGui::SameLine();
    if (ImGui::Button("Refresh LAN/Radmin", ImVec2(190.0f, 0.0f)))
    {
        SaveRadminSettings();
        const int count = SteamLobbyManager::RefreshNetworkLobbies(1200);
        static std::string status;
        status = "Refresh complete. Visible LAN/Radmin lobbies: " + std::to_string(count);
        g_OnlineMenuAction = status.c_str();
        Logger::Info(status);
    }
    ImGui::SameLine();
    if (ImGui::Button("Create Lobby", ImVec2(190.0f, 0.0f)))
    {
        CSteamID lobby = SteamLobbyManager::CreateLobbyWithOptions(2, 2, "NS4 Revived Radmin Lobby", g_LobbyPasswordInput);
        const std::string createdRoom = SteamLobbyManager::GetCurrentRoomCode();
        static std::string status;
        status = lobby
            ? "Lobby created. Give your friend this room code: " + createdRoom
            : "Lobby creation failed.";
        g_OnlineMenuAction = status.c_str();
        Logger::Info(status);
    }

    if (ImGui::Button("Join Room Code", ImVec2(190.0f, 0.0f)))
    {
        const bool joined = SteamLobbyManager::JoinRoomCode(g_RoomCodeInput, g_LobbyPasswordInput);
        static std::string status;
        status = joined
            ? "Joined room code. Continue through the stock Online Battle lobby flow."
            : "Join by room code failed: " + SteamLobbyManager::GetLastJoinError();
        g_OnlineMenuAction = status.c_str();
        Logger::Info(status);
    }
    ImGui::SameLine();
    if (ImGui::Button("Join Radmin IP", ImVec2(190.0f, 0.0f)))
    {
        SaveRadminSettings();
        const bool joined = SteamLobbyManager::JoinAddress(g_RadminAddressInput, static_cast<uint16_t>(SteamConfig::Get().CustomServerPort), g_LobbyPasswordInput);
        static std::string status;
        status = joined
            ? "Joined by Radmin IP. Continue through the stock Online Battle lobby flow."
            : "Join by Radmin IP failed: " + SteamLobbyManager::GetLastJoinError();
        g_OnlineMenuAction = status.c_str();
        Logger::Info(status);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextUnformatted("Storm Revival Online Menu");
    ImGui::TextWrapped("%s", g_OnlineMenuAction);
    ImGui::Spacing();

    OnlineActionButton("Server Status", "Server: offline LAN mode. No hosted master server is active.");
    ImGui::SameLine();
    OnlineActionButton("Room Browser", "Room Browser: using LAN lobby discovery from the offline Steam layer.");
    ImGui::SameLine();
    OnlineActionButton("Leaderboard", "Leaderboard: local debug leaderboards are being emulated.");

    OnlineActionButton("News", "News: local/offline news panel placeholder is ready.");
    ImGui::SameLine();
    OnlineActionButton("Settings", "Settings: online settings placeholder is ready.");
    ImGui::SameLine();
    OnlineActionButton("Unlock All", "Unlock All: placeholder only. No persistent unlock was applied.");

    if (ImGui::Button("Open Full Hub", ImVec2(190.0f, 0.0f)))
    {
        g_OnlineMenuAction = "Opening the full Storm Revival hub overlay.";
        Logger::Info("Storm Revival online menu action: Open Full Hub");
        Evo::OnlineMenuHubStub::OpenFromStore();
    }
}
