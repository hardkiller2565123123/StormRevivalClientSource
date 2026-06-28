#pragma once

namespace CharacterSlotExpansionManager
{
    void Init();
    void RunDiagnostics();
    bool DiagnosticsReady();
    bool RuntimeEnabled();
    const char* LastStatus();
}
