#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Store
{
    void Install();
    bool ShouldBlockSteamStore();
    void ShowStoreReplacement(GamePtr ui);
}
