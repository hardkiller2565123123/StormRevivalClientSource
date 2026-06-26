#pragma once

namespace StormRevival::OnlineMenu::Config
{
    struct Settings
    {
        bool EnableInstallLog = true;
        bool EnableFlashTrace = true;

        // Offline build only.
        bool EnableCustomMenuEntry = true;

        // Research hooks remain off unless you wire and version-guard them.
        bool EnableMenuResearchHooks = false;
        bool EnableHardPatches = false;

        // Important: this build does NOT hijack Store/BingoBook by default.
        bool ReuseExistingButtonFirst = true;

        // True custom row path:
        // append a synthetic menu item below Online Match once the netbattlemainmenu
        // option provider / Flash callback table is hooked.
        bool AddRealCustomOptionRow = true;
        int CustomOptionMode = 100;
        int StoreMode = 13; // Current best-known stock Store/online-menu route candidate.
    };

    Settings& Get();
}
