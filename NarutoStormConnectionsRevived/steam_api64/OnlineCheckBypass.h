#pragma once

namespace OnlineCheckBypass
{
    bool Init();
    void RevalidateSignatures();
    void ForceConnectedState();
    const char* SignatureReport();
    void Shutdown();
}
