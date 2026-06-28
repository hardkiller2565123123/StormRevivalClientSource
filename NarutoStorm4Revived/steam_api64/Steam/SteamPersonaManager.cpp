#include "StdInc.h"
#include "SteamPersonaManager.h"
#include "SteamIDManager.h"
#include "Logger.h"

namespace
{
    std::mutex g_Mutex;
    std::vector<CSteamID> g_Friends;
    std::unordered_map<uint64_t, std::string> g_Names;
    std::map<std::string, std::string> g_RichPresence;

    std::string g_DefaultName = "NS4 Player";
    thread_local std::string g_ReturnString;

    uint64_t ToKey(CSteamID id)
    {
        return SteamIDManager::ToUint64(id);
    }

    bool LooksLikeSteamID(uint64_t value)
    {
        if (value == 0 || value == UINT64_MAX)
            return false;

        const uint64_t universe = (value >> 56) & 0xffull;
        const uint64_t type = (value >> 52) & 0xfull;
        const uint64_t account = value & 0xffffffffull;
        return universe >= 1 && universe <= 6 && account != 0 && (type == 1 || type == 8);
    }

    CSteamID SanitizeSteamID(CSteamID id)
    {
        const uint64_t value = ToKey(id);
        if (LooksLikeSteamID(value))
            return id;
        return SteamIDManager::GetLocalSteamID();
    }

    std::string CleanName(const std::string& name, CSteamID id)
    {
        if (!name.empty())
            return name;
        if (ToKey(id) == SteamIDManager::GetSteamID64())
            return SteamIDManager::GetPersonaName();
        return g_DefaultName;
    }

    void AddOrUpdateFriendUnlocked(CSteamID steamID, const std::string& name)
    {
        steamID = SanitizeSteamID(steamID);
        const uint64_t key = ToKey(steamID);
        if (key == 0)
            return;

        bool exists = false;
        for (CSteamID friendID : g_Friends)
        {
            if (ToKey(friendID) == key)
            {
                exists = true;
                break;
            }
        }

        if (!exists)
            g_Friends.push_back(steamID);

        g_Names[key] = CleanName(name, steamID);
    }
}

namespace SteamPersonaManager
{
    bool Init()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Friends.clear();
        g_Names.clear();
        g_RichPresence.clear();

        CSteamID local = SteamIDManager::GetLocalSteamID();
        AddOrUpdateFriendUnlocked(local, SteamIDManager::GetPersonaName());

        g_RichPresence["status"] = "Online";
        g_RichPresence["connect"] = "";
        g_RichPresence["steam_display"] = "#Status_Online";

        Logger::Info("SteamPersonaManager initialized");
        return true;
    }

    void Shutdown()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_Friends.clear();
        g_Names.clear();
        g_RichPresence.clear();
    }

    const char* GetPersonaName()
    {
        return SteamIDManager::GetPersonaName();
    }

    void SetPersonaName(const std::string& name)
    {
        SteamIDManager::SetPersonaName(name);
        std::lock_guard<std::mutex> lock(g_Mutex);
        AddOrUpdateFriendUnlocked(SteamIDManager::GetLocalSteamID(), SteamIDManager::GetPersonaName());
    }

    int GetFriendCount()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (g_Friends.empty())
            return 1;
        return static_cast<int>(g_Friends.size());
    }

    CSteamID GetFriendByIndex(int index)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (g_Friends.empty())
            return SteamIDManager::GetLocalSteamID();
        if (index < 0 || index >= static_cast<int>(g_Friends.size()))
            return SteamIDManager::GetLocalSteamID();
        return g_Friends[index] ? g_Friends[index] : SteamIDManager::GetLocalSteamID();
    }

    uint64_t GetFriendByIndex64(int index)
    {
        return SteamIDManager::ToUint64(GetFriendByIndex(index));
    }

    void AddOrUpdateRemotePlayer(CSteamID steamID, const std::string& name)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        AddOrUpdateFriendUnlocked(steamID, name);
    }

    void AddOrUpdateFriend(CSteamID steamID, const std::string& name)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        AddOrUpdateFriendUnlocked(steamID, name);
    }

    bool HasFriend(CSteamID steamID)
    {
        const uint64_t key = ToKey(SanitizeSteamID(steamID));
        std::lock_guard<std::mutex> lock(g_Mutex);
        for (CSteamID friendID : g_Friends)
        {
            if (ToKey(friendID) == key)
                return true;
        }
        return false;
    }

    const char* GetFriendPersonaName(CSteamID steamID)
    {
        steamID = SanitizeSteamID(steamID);
        const uint64_t key = ToKey(steamID);

        std::lock_guard<std::mutex> lock(g_Mutex);
        auto it = g_Names.find(key);
        if (it != g_Names.end() && !it->second.empty())
        {
            g_ReturnString = it->second;
            return g_ReturnString.c_str();
        }

        g_ReturnString = CleanName(std::string(), steamID);
        g_Names[key] = g_ReturnString;

        bool exists = false;
        for (CSteamID friendID : g_Friends)
        {
            if (ToKey(friendID) == key)
            {
                exists = true;
                break;
            }
        }
        if (!exists)
            g_Friends.push_back(steamID);

        return g_ReturnString.c_str();
    }

    bool SetRichPresence(const char* key, const char* value)
    {
        if (!key || key[0] == '\0')
            return false;

        std::lock_guard<std::mutex> lock(g_Mutex);
        g_RichPresence[key] = value ? value : "";
        Logger::Info("SteamPersonaManager rich presence set " + std::string(key));
        return true;
    }

    bool SetRichPresence(const std::string& key, const std::string& value)
    {
        return SetRichPresence(key.c_str(), value.c_str());
    }

    void ClearRichPresence()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        g_RichPresence.clear();
        Logger::Info("SteamPersonaManager rich presence cleared");
    }

    const char* GetRichPresence(const char* key)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (!key)
        {
            g_ReturnString.clear();
            return g_ReturnString.c_str();
        }

        auto it = g_RichPresence.find(key);
        if (it == g_RichPresence.end())
        {
            g_ReturnString.clear();
            return g_ReturnString.c_str();
        }

        g_ReturnString = it->second;
        return g_ReturnString.c_str();
    }

    const char* GetRichPresence(const std::string& key)
    {
        return GetRichPresence(key.c_str());
    }

    int GetRichPresenceKeyCount()
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        return static_cast<int>(g_RichPresence.size());
    }

    const char* GetRichPresenceKeyByIndex(int index)
    {
        std::lock_guard<std::mutex> lock(g_Mutex);
        if (index < 0 || index >= static_cast<int>(g_RichPresence.size()))
        {
            g_ReturnString.clear();
            return g_ReturnString.c_str();
        }

        auto it = g_RichPresence.begin();
        std::advance(it, index);
        g_ReturnString = it->first;
        return g_ReturnString.c_str();
    }
}
