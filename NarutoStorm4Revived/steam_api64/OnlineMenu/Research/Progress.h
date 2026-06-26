#pragma once

namespace StormRevival::OnlineMenu::Research
{
    /*
        Public progress table for the offline open-source build.
        Keep this human-readable; it is printed to logs at install.
    */
    inline constexpr const char* ProgressTable =
        "StormRevival Online Menu Research\\n"
        "Flash Movie Loader: 100%\\n"
        "Flash Invoke System: 100%\\n"
        "Flash Callback Registration: 100%\\n"
        "Main Menu Initialization: 100%\\n"
        "GetMode/GetModeBattele: 100%\\n"
        "Banner/Event UI: 100%\\n"
        "Bingo/Event Lock UI: 100%\\n"
        "Player Card UI: 100%\\n"
        "Leaderboard Fake Local Data: 100%\\n"
        "Store -> Settings Route: 100%\\n"
        "Store Visible Rename: best-effort Flash probe\\n"
        "Lobby Member Data Flow: 85%\\n"
        "Steam Lobby Backend: 70%\\n"
        "Match Start Pipeline: 60%\\n"
        "Ranked Matchmaking: 45%\\n"
        "True Extra Menu Row Injection: research target\\n";
}
