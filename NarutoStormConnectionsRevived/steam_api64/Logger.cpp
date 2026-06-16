#include "StdInc.h"
#include "Logger.h"

static std::ofstream g_Log;
static std::mutex g_LogMutex;

static bool g_ConsoleReady = false;
static bool g_ConsoleAllocatedByUs = false;
static bool g_LoggerInitialized = false;
static std::string g_LastInfoLine;
static uint32_t g_RepeatedInfoCount = 0;
static uint32_t g_InfoLinesSinceFlush = 0;

static std::string ToLowerString(std::string text)
{
    for (char& c : text)
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    return text;
}

static std::string GetProcessPath()
{
    char exePath[MAX_PATH]{};
    GetModuleFileNameA(nullptr, exePath, MAX_PATH);
    return exePath;
}

static std::string GetProcessName()
{
    std::string path = GetProcessPath();

    size_t slash = path.find_last_of("\\/");

    if (slash != std::string::npos)
        path = path.substr(slash + 1);

    return ToLowerString(path);
}

static std::string GetGameDirectory()
{
    std::string path = GetProcessPath();

    size_t slash = path.find_last_of("\\/");

    if (slash != std::string::npos)
        return path.substr(0, slash + 1);

    return "";
}

static bool IsRealGameProcess()
{
    std::string exe = GetProcessName();

    if (exe.empty())
        return false;

    if (exe == "explorer.exe" || exe == "devenv.exe" || exe == "msbuild.exe")
        return false;

    return exe.size() > 4 && exe.substr(exe.size() - 4) == ".exe";
}

static void InitConsole()
{
    if (g_ConsoleReady)
        return;

    if (!GetConsoleWindow())
    {
        if (!AttachConsole(ATTACH_PARENT_PROCESS))
        {
            if (AllocConsole())
                g_ConsoleAllocatedByUs = true;
        }
    }

    FILE* dummy = nullptr;
    freopen_s(&dummy, "CONOUT$", "w", stdout);
    freopen_s(&dummy, "CONOUT$", "w", stderr);
    freopen_s(&dummy, "CONIN$", "r", stdin);

    SetConsoleTitleA("Naruto Revival Offline Debug Console");
    g_ConsoleReady = true;
}

bool Logger::Init()
{
    if (g_LoggerInitialized)
        return true;

    g_LoggerInitialized = true;

    std::string gameDir = GetGameDirectory();
    std::string baseDir = gameDir + "NarutoStormConnectionsRevived";

    std::string logsDir = baseDir + "\\Logs";


    CreateDirectoryA(baseDir.c_str(), nullptr);

    CreateDirectoryA(logsDir.c_str(), nullptr);

    std::string logPath = logsDir + "\\NarutoStormConnectionsRevived.log";

    DeleteFileA(logPath.c_str());

    g_Log.open(logPath, std::ios::out | std::ios::trunc);

    if (!g_Log.is_open())
        return false;

    if (IsRealGameProcess())
        InitConsole();

    Info("Logger initialized");
    Info("Fresh log created");
    Info("Process: " + GetProcessPath());
    Info("Process name: " + GetProcessName());
    Info("Log path: " + logPath);

    return true;
}

void Logger::Shutdown()
{
    Info("Logger shutdown");
    Flush();

    {
        std::lock_guard<std::mutex> lock(g_LogMutex);

        if (g_Log.is_open())
            g_Log.close();
    }

    if (g_ConsoleReady && g_ConsoleAllocatedByUs)
        FreeConsole();

    g_ConsoleReady = false;
    g_ConsoleAllocatedByUs = false;
    g_LoggerInitialized = false;
    g_LastInfoLine.clear();
    g_RepeatedInfoCount = 0;
    g_InfoLinesSinceFlush = 0;
}

void Logger::Info(const std::string& text)
{
    std::lock_guard<std::mutex> lock(g_LogMutex);

    std::string line = "[INFO] " + text;

    if (line == g_LastInfoLine)
    {
        ++g_RepeatedInfoCount;
        return;
    }

    if (g_Log.is_open())
    {
        if (g_RepeatedInfoCount > 0)
        {
            g_Log << "[INFO] previous message repeated " << g_RepeatedInfoCount << " times\n";
            g_RepeatedInfoCount = 0;
        }

        g_Log << line << '\n';

        if (++g_InfoLinesSinceFlush >= 64)
        {
            g_Log.flush();
            g_InfoLinesSinceFlush = 0;
        }
    }

    if (g_ConsoleReady)
    {
        if (g_RepeatedInfoCount > 0)
        {
            std::cout << "[INFO] previous message repeated " << g_RepeatedInfoCount << " times" << std::endl;
            g_RepeatedInfoCount = 0;
        }

        std::cout << line << std::endl;
    }

    g_LastInfoLine = line;
}

void Logger::Error(const std::string& text)
{
    std::lock_guard<std::mutex> lock(g_LogMutex);

    std::string line = "[ERROR] " + text;

    if (g_Log.is_open())
    {
        if (g_RepeatedInfoCount > 0)
        {
            g_Log << "[INFO] previous message repeated " << g_RepeatedInfoCount << " times\n";
            g_RepeatedInfoCount = 0;
        }

        g_Log << line << '\n';
        g_Log.flush();
    }

    if (g_ConsoleReady)
        std::cout << line << std::endl;
}

void Logger::Flush()
{
    std::lock_guard<std::mutex> lock(g_LogMutex);

    if (g_Log.is_open())
    {
        if (g_RepeatedInfoCount > 0)
        {
            g_Log << "[INFO] previous message repeated " << g_RepeatedInfoCount << " times\n";
            g_RepeatedInfoCount = 0;
        }

        g_Log.flush();
        g_InfoLinesSinceFlush = 0;
    }
}

void Logger::ExportInitialized(const char* exportName)
{
    Info(std::string(exportName) + ": initialized");
}
