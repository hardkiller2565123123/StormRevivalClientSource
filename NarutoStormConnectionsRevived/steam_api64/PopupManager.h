#pragma once

#include <cstdint>
#include "PopupTypes.h"

namespace PopupManager
{
    bool Init(uintptr_t gameBase);
    void Shutdown();

    bool ShowTimedWelcome(const PopupTypes::TimedPopupConfig& config = PopupTypes::TimedPopupConfig{});
    bool ShowCustomPopup(const PopupTypes::CustomPopupConfig& config);
    bool IsShowing();
    bool IsBusy();
    unsigned int ActivePopupId();
    void CloseNow();
}
