#pragma once
#include "../Core/SRTypes.h"

namespace StormRevival::OnlineMenu::Flash
{
    struct Target
    {
        const char* Movie;
        const char* Root;
    };

    // Backward-compatible alias used by older OnlineMenu files.
    using FlashTarget = Target;

    inline constexpr Target NetBattleMainMenu{ "netbattlemainmenu", "_root.all_nut" };
    inline constexpr Target NetBattleLobby{ "netbattlelobby", "_root.all_nut" };
    inline constexpr Target NetBattleBg{ "netbattlebg", "_root.all_nut" };

    void Install();

    void TraceCall(const Target& target, const char* functionName, int argc);

    void CallNoArgs(GamePtr ui, const Target& target, const char* functionName);
    void CallInt(GamePtr ui, const Target& target, const char* functionName, int value);
    void CallText(GamePtr ui, const Target& target, const char* functionName, const char* text);

    // Compatibility wrappers expected by NetBattleMainMenu.cpp / NetBattleLobby.cpp.
    inline void CallString(GamePtr ui, const Target& target, const char* functionName, const char* text)
    {
        CallText(ui, target, functionName, text);
    }

    inline void CallBool(GamePtr ui, const Target& target, const char* functionName, bool value)
    {
        CallInt(ui, target, functionName, value ? 1 : 0);
    }
}
