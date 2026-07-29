#pragma once

#include <cstdint>

namespace ClassicSelectTheme
{
    bool Init(uintptr_t gameBase);
    void Shutdown();
    bool IsEnabled();
}
