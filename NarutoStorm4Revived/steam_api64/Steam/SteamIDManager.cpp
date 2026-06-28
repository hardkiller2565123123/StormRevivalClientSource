#include "StdInc.h"
#include "SteamIDManager.h"
#include "SteamConfig.h"
#include "Logger.h"

#pragma comment(lib, "Advapi32.lib")

namespace
{
    constexpr uint64_t kSteamID64Base = 76561197960265728ull;
    constexpr uint64_t kDefaultConfiguredSteamID = 76561199006065889ull;

    std::string g_FallbackPersona = "NS4Revived";
    std::mutex g_EffectiveMutex;
    uint64_t g_EffectiveSteamID = 0;
    uint64_t g_EffectiveBaseSteamID = 0;
    DWORD g_EffectiveProcessID = 0;
    HANDLE g_InstanceSlotMutex = nullptr;
    uint32_t g_InstanceSlot = 0;

    uint64_t Fnv1a64(const std::string& text)
    {
        uint64_t hash = 1469598103934665603ull;
        for (unsigned char c : text)
        {
            hash ^= static_cast<uint64_t>(c);
            hash *= 1099511628211ull;
        }
        return hash;
    }

    std::string ReadRegistryString(HKEY root, const char* subkey, const char* valueName)
    {
        HKEY key = nullptr;
        if (RegOpenKeyExA(root, subkey, 0, KEY_READ | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
        {
            if (RegOpenKeyExA(root, subkey, 0, KEY_READ | KEY_WOW64_32KEY, &key) != ERROR_SUCCESS)
                return std::string();
        }

        char buffer[512]{};
        DWORD type = 0;
        DWORD size = sizeof(buffer);
        const LONG result = RegQueryValueExA(key, valueName, nullptr, &type, reinterpret_cast<LPBYTE>(buffer), &size);
        RegCloseKey(key);

        if (result != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ))
            return std::string();

        return std::string(buffer);
    }

    uint32_t ReadRegistryDword(HKEY root, const char* subkey, const char* valueName)
    {
        HKEY key = nullptr;
        if (RegOpenKeyExA(root, subkey, 0, KEY_READ | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
        {
            if (RegOpenKeyExA(root, subkey, 0, KEY_READ | KEY_WOW64_32KEY, &key) != ERROR_SUCCESS)
                return 0;
        }

        DWORD value = 0;
        DWORD type = 0;
        DWORD size = sizeof(value);
        const LONG result = RegQueryValueExA(key, valueName, nullptr, &type, reinterpret_cast<LPBYTE>(&value), &size);
        RegCloseKey(key);

        if (result != ERROR_SUCCESS || type != REG_DWORD)
            return 0;

        return static_cast<uint32_t>(value);
    }

    uint64_t ReadSteamIDFromRegistry()
    {
        // Steam stores the currently active account ID here. SteamID64 = base + accountID.
        const uint32_t activeUser = ReadRegistryDword(HKEY_CURRENT_USER, "Software\\Valve\\Steam\\ActiveProcess", "ActiveUser");
        if (activeUser != 0)
            return kSteamID64Base + static_cast<uint64_t>(activeUser);

        return 0;
    }

    uint64_t BuildMachineFallbackSteamID()
    {
        char userName[256]{};
        DWORD userNameSize = sizeof(userName);
        GetUserNameA(userName, &userNameSize);

        char computerName[256]{};
        DWORD computerNameSize = sizeof(computerName);
        GetComputerNameA(computerName, &computerNameSize);

        const std::string machineGuid = ReadRegistryString(
            HKEY_LOCAL_MACHINE,
            "SOFTWARE\\Microsoft\\Cryptography",
            "MachineGuid");

        std::string material = "NS4Revived:";
        material += machineGuid;
        material += ':';
        material += userName;
        material += ':';
        material += computerName;

        uint32_t accountID = static_cast<uint32_t>(Fnv1a64(material) & 0x7FFFFFFFu);
        if (accountID == 0)
            accountID = 1;

        return kSteamID64Base + static_cast<uint64_t>(accountID);
    }

    uint64_t ResolveBaseSteamID()
    {
        const SteamConfig::Config& config = SteamConfig::Get();

        if (config.AutoDetectSteamID)
        {
            const uint64_t realSteamID = ReadSteamIDFromRegistry();
            if (realSteamID != 0)
                return realSteamID;

            if (config.SteamID == 0 || config.SteamID == kDefaultConfiguredSteamID)
                return BuildMachineFallbackSteamID();
        }

        if (config.SteamID != 0)
            return config.SteamID;

        return BuildMachineFallbackSteamID();
    }

    void ReleaseInstanceSlot()
    {
        if (g_InstanceSlotMutex)
        {
            CloseHandle(g_InstanceSlotMutex);
            g_InstanceSlotMutex = nullptr;
        }

        g_InstanceSlot = 0;
    }

    uint32_t AcquireInstanceSlot(uint64_t baseID)
    {
        if (g_InstanceSlotMutex)
            return g_InstanceSlot;

        for (uint32_t slot = 0; slot <= 32; ++slot)
        {
            const std::string name =
                "Local\\NS4RevivedSteamIDSlot_" +
                std::to_string(static_cast<unsigned long long>(baseID)) +
                "_" +
                std::to_string(slot);

            HANDLE handle = CreateMutexA(nullptr, TRUE, name.c_str());
            if (!handle)
                continue;

            if (GetLastError() != ERROR_ALREADY_EXISTS)
            {
                g_InstanceSlotMutex = handle;
                g_InstanceSlot = slot;
                return slot;
            }

            CloseHandle(handle);
        }

        return 0;
    }

    uint64_t BuildEffectiveSteamID()
    {
        const SteamConfig::Config& config = SteamConfig::Get();
        const uint64_t baseID = ResolveBaseSteamID();

        if (!config.AutoInstanceSteamID)
            return baseID;

        return baseID + AcquireInstanceSlot(baseID);
    }
}

namespace SteamIDManager
{
    bool Init()
    {
        const uint64_t effectiveID = GetSteamID64();
        const uint64_t configuredID = SteamConfig::Get().SteamID;
        Logger::Info(
            "SteamIDManager initialized id=" +
            std::to_string(static_cast<unsigned long long>(effectiveID)) +
            " configured=" +
            std::to_string(static_cast<unsigned long long>(configuredID)) +
            " auto_detect=" +
            std::to_string(SteamConfig::Get().AutoDetectSteamID ? 1 : 0) +
            " auto_instance=" +
            std::to_string(SteamConfig::Get().AutoInstanceSteamID ? 1 : 0));
        return true;
    }

    void Shutdown()
    {
        std::lock_guard<std::mutex> lock(g_EffectiveMutex);
        ReleaseInstanceSlot();
        g_EffectiveSteamID = 0;
        g_EffectiveBaseSteamID = 0;
        g_EffectiveProcessID = 0;
    }

    CSteamID FromUint64(uint64_t value)
    {
        return static_cast<CSteamID>(value);
    }

    CSteamID GetLocalSteamID()
    {
        return FromUint64(GetSteamID64());
    }

    CSteamID GetLocalUser()
    {
        return GetLocalSteamID();
    }

    uint64_t ToUint64(CSteamID value)
    {
        return static_cast<uint64_t>(value);
    }

    uint64_t GetSteamID64()
    {
        const uint64_t baseID = ResolveBaseSteamID();
        const DWORD processID = GetCurrentProcessId();

        std::lock_guard<std::mutex> lock(g_EffectiveMutex);
        if (g_EffectiveSteamID == 0 ||
            g_EffectiveBaseSteamID != baseID ||
            g_EffectiveProcessID != processID)
        {
            g_EffectiveBaseSteamID = baseID;
            g_EffectiveProcessID = processID;
            ReleaseInstanceSlot();
            g_EffectiveSteamID = BuildEffectiveSteamID();
        }

        return g_EffectiveSteamID;
    }

    uint32_t GetAccountID()
    {
        return static_cast<uint32_t>(GetSteamID64() & 0xFFFFFFFFu);
    }

    const char* GetPersonaName()
    {
        const std::string& name = SteamConfig::Get().PersonaName;
        return name.empty() ? g_FallbackPersona.c_str() : name.c_str();
    }

    const std::string& GetPersonaNameString()
    {
        const std::string& name = SteamConfig::Get().PersonaName;
        return name.empty() ? g_FallbackPersona : name;
    }

    void SetPersonaName(const std::string& name)
    {
        SteamConfig::Mutable().PersonaName = name.empty() ? g_FallbackPersona : name;
        SteamConfig::Save();
    }
}
