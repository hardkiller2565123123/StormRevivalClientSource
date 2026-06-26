#include "OnlineMenuPatchStub.h"

namespace OnlineMenuPatchStub
{
    bool IsEnabled()
    {
        return false;
    }

    void InstallDisabled()
    {
        // Intentionally empty.
        // Next IDA targets before enabling:
        // 1) netbattlemainmenu button/action callback handler.
        // 2) MenuAction / SelectMenu xrefs.
        // 3) Function that receives selected menu index and branches to ranked/player/endless menu.
    }
}
