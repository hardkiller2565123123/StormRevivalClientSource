#include "ActionScriptIntegrationNotes.h"

namespace StormRevival::OnlineMenu::ActionScript
{
    const char* GetIntegrationSummary()
    {
        return
            "ActionScript archive first pass: the extracted .as scripts are used as a symbol map, not patched directly. "
            "The DLL hooks the native Scaleform bridge once, logs every movie/function call, and CustomUI uses those calls "
            "to discover safe injection points for OpenArchive options, custom stage browser, private LAN page, plugin page, and developer tools.";
    }
}
