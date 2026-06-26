#include "HelpOverlayExamples.h"

namespace StormRevival::OnlineMenu::Help
{
    void PushStormRevivalHelp(std::uintptr_t)
    {
        // TODO:
        // Use ccUiFlashKeyHelp:
        // sub_14066A9A0 -> create key/help entry
        // sub_14066AE94 -> AddHelp + Push
        //
        // Example planned hints:
        // Y  = Storm Revival
        // X  = News
        // RB = Settings
    }

    void PopStormRevivalHelp(std::uintptr_t)
    {
        // TODO:
        // sub_14066AC9C or help_msg Pop flow.
    }
}
