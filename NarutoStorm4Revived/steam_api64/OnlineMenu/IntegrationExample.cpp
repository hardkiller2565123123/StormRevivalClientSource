// Example integration file.
// Do not compile into release until you wire real addresses and include paths.

#include "Flash/FlashCallLayer.h"
#include "VoiceStatus/VoiceStatusExamples.h"
#include "Buttons/MenuActionHookPlan.h"
#include "Dialogs/DialogExamples.h"

namespace StormRevival::OnlineMenu
{
    void InstallResearchExamples()
    {
        // TODO:
        // Resolve version-specific addresses, then:
        //
        // Flash::SetSymbols({
        //   .callFlashWithArgs = 0x140607BA0,
        //   .callFlashNoArgs   = 0x140607B5C,
        //   .callFlashReturn   = 0x140607B7C,
        //   .objectExists      = 0x140607CBC,
        //   .loadMovie         = 0x14060759C
        // });
        //
        // Hook sub_140675FB4 for selected mode callback.
    }
}
