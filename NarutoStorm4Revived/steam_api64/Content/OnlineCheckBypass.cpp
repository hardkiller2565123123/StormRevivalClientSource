#include "StdInc.h"
#include "OnlineCheckBypass.h"
#include "Logger.h"

namespace
{
    const char* g_SignatureReport = "Offline release: online bypass disabled.";
}

bool OnlineCheckBypass::Init()
{
    Logger::Info("OnlineCheckBypass disabled for offline release");
    return true;
}

void OnlineCheckBypass::RevalidateSignatures()
{
}

const char* OnlineCheckBypass::SignatureReport()
{
    return g_SignatureReport;
}

void OnlineCheckBypass::Shutdown()
{
}