#include "StdInc.h"
#include "ModLoader.h"
#include "Logger.h"
#include "SteamConfig.h"

static std::string GetExeDirectory()
{
    char exePath[MAX_PATH]{};
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);

    std::string path = exePath;
    size_t slash = path.find_last_of("\\/");

    if (slash == std::string::npos)
        return "";

    return path.substr(0, slash + 1);
}

static bool DirectoryExists(const std::string& path)
{
    DWORD attr = GetFileAttributesA(path.c_str());

    return attr != INVALID_FILE_ATTRIBUTES &&
        (attr & FILE_ATTRIBUTE_DIRECTORY);
}

static bool EndsWith(const std::string& value, const std::string& suffix)
{
    return value.size() >= suffix.size() &&
        value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
}


static bool ShouldSkipStormEvolutionFile(const std::string& path)
{
    std::string lower = path;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c)
    {
        return static_cast<char>(std::tolower(c));
    });

    return lower.find("checksum") != std::string::npos ||
        lower.find("launcher") != std::string::npos ||
        EndsWith(lower, ".exe") ||
        EndsWith(lower, ".bat") ||
        EndsWith(lower, ".cmd") ||
        EndsWith(lower, ".ps1");
}

static void ScanStormEvolutionFolder(const std::string& folder)
{
    DWORD attr = GetFileAttributesA(folder.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES || !(attr & FILE_ATTRIBUTE_DIRECTORY))
        return;

    Logger::Info("StormEvolution folder detected: " + folder);

    std::error_code ec;
    int registered = 0;
    for (std::filesystem::recursive_directory_iterator it(folder, std::filesystem::directory_options::skip_permission_denied, ec), end; it != end; it.increment(ec))
    {
        if (ec)
        {
            ec.clear();
            continue;
        }

        if (!it->is_regular_file(ec))
            continue;

        const std::string path = it->path().string();
        if (ShouldSkipStormEvolutionFile(path))
        {
            Logger::Info("StormEvolution skipped sidecar: " + path);
            continue;
        }

        std::string lower = path;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c)
        {
            return static_cast<char>(std::tolower(c));
        });

        ++registered;
        if (EndsWith(lower, ".dll"))
        {
            HMODULE modModule = LoadLibraryA(path.c_str());
            if (modModule)
                Logger::Info("Loaded StormEvolution DLL: " + path);
            else
                Logger::Error("Failed to load StormEvolution DLL: " + path);
        }
        else if (registered <= 50)
        {
            Logger::Info("StormEvolution registered content: " + path);
        }
    }

    Logger::Info("StormEvolution scan complete: " + folder + " files=" + std::to_string(registered));
}

namespace ModLoader
{
    void LoadMods()
    {
        std::string rootDir = GetExeDirectory() + "NarutoStorm4Revived\\";
        std::string modsDir = rootDir + "mods\\";

        CreateDirectoryA(rootDir.c_str(), nullptr);
        CreateDirectoryA(modsDir.c_str(), nullptr);

        if (!DirectoryExists(modsDir))
        {
            Logger::Error("Failed to create mods folder: " + modsDir);
            return;
        }

        Logger::Info("Mods folder: " + modsDir);

        for (const std::string folder : SteamConfig::GetEvolutionFolders())
            ScanStormEvolutionFolder(folder);

        WIN32_FIND_DATAA findData{};
        HANDLE findHandle = FindFirstFileA(
            (modsDir + "*.dll").c_str(),
            &findData);

        if (findHandle == INVALID_HANDLE_VALUE)
        {
            Logger::Info("No mod DLLs found");
            return;
        }

        do
        {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                continue;

            std::string modPath = modsDir + findData.cFileName;

            HMODULE modModule = LoadLibraryA(modPath.c_str());

            if (modModule)
            {
                Logger::Info("Loaded mod: " + modPath);
            }
            else
            {
                Logger::Error("Failed to load mod: " + modPath);
            }

        } while (FindNextFileA(findHandle, &findData));

        FindClose(findHandle);
    }
}