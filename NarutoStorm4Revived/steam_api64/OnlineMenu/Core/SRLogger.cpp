#include "SRLogger.h"
#include "../../Logger.h"
#include <windows.h>
namespace StormRevival::OnlineMenu::Log {
static void Out(const char* level, const std::string& msg)
{
    const std::string line = "[StormRevivalOnlineMenu][" + std::string(level) + "] " + msg;
    OutputDebugStringA((line + "\n").c_str());

    if (std::string(level) == "ERROR")
        Logger::Error(line);
    else if (std::string(level) == "WARN")
        Logger::Warn(line);
    else
        Logger::Info(line);
}
void Info(const std::string& msg){Out("INFO",msg);} void Warn(const std::string& msg){Out("WARN",msg);} void Error(const std::string& msg){Out("ERROR",msg);}
}
