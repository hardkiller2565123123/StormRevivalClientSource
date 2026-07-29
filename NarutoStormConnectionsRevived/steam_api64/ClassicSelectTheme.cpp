#include "StdInc.h"
#include "ClassicSelectTheme.h"
#include "PopupReverseMap.h"
#include "Logger.h"

#include <cstdint>
#include <sstream>

namespace
{
    uintptr_t g_Base = 0;
    bool g_Enabled = false;

    void LogTarget(const char* name, uintptr_t rva)
    {
        std::ostringstream ss;
        ss << "ClassicSelectTheme target " << name << " rva=0x" << std::hex << rva
           << " addr=0x" << (g_Base + rva);
        Logger::Info(ss.str());
    }
}

namespace ClassicSelectTheme
{
    bool Init(uintptr_t gameBase)
    {
        if (!gameBase)
        {
            Logger::Error("ClassicSelectTheme: invalid game base");
            return false;
        }

        g_Base = gameBase;
        g_Enabled = true;

        // Research map only for now. Actual SWF replacement/layout hooks should be added here later.
        LogTarget("CharacterSelect::SetCharacter", PopupReverseMap::CharacterSelect::SetCharacter);
        LogTarget("CharacterSelect::SetItemText", PopupReverseMap::CharacterSelect::SetItemText);
        LogTarget("CharacterSelect::LoadAccessoryOrSubstitution", PopupReverseMap::CharacterSelect::LoadAccessoryOrSubstitution);
        LogTarget("Flash::CallArgs", PopupReverseMap::Flash::CallArgs);
        LogTarget("SelectWindow::RegisterCallbacks", PopupReverseMap::SelectWindow::RegisterCallbacks);

        Logger::Info("ClassicSelectTheme initialized as research/scaffold mode");
        return true;
    }

    void Shutdown()
    {
        g_Enabled = false;
        g_Base = 0;
        Logger::Info("ClassicSelectTheme shutdown");
    }

    bool IsEnabled()
    {
        return g_Enabled;
    }
}
