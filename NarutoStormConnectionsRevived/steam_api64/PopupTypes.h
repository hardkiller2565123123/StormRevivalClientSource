#pragma once

#include <cstdint>

namespace PopupTypes
{
    // Real NSC popup kind values seen in ccUiFlashDialog / ccUiFlashSelectWindow.
    enum class PopupKind : int
    {
        Dialog = 7,
        Normal = 7,
        Select = 8
    };

    enum class DialogResult : int
    {
        Waiting = -1,
        Accept = 0,
        Cancel = 1
    };

    enum class FadeMode : int
    {
        White = 0,
        Black = 1,
        Custom = 2
    };

    struct FadeRgb
    {
        float r;
        float g;
        float b;
    };

    constexpr FadeRgb WhiteFade{ 1.0f, 1.0f, 1.0f };
    constexpr FadeRgb BlackFade{ 0.0f, 0.0f, 0.0f };
    constexpr FadeRgb StormBlueFade{ 0.10f, 0.22f, 0.65f };
    constexpr FadeRgb ChakraOrangeFade{ 1.0f, 0.45f, 0.05f };
    constexpr FadeRgb InkPurpleFade{ 0.35f, 0.10f, 0.65f };

    struct TimedPopupConfig
    {
        int delayMs = 5000;
        int durationMs = 10000;
        bool allowInputClose = false;
        bool localizeText = false;
        bool useFade = false;
        int fadeDurationMs = 300;
        FadeRgb fadeColor = BlackFade;
    };

    struct CustomPopupConfig
    {
        const char* windowName = "StormRevivalCustomPopup";
        const char* titleText = "Storm API";
        const char* bodyText = "Runtime popup.";
        int delayMs = 0;
        int durationMs = 5000;
        bool allowInputClose = true;
        bool localizeText = false;
        bool useFade = false;
        int fadeDurationMs = 300;
        FadeRgb fadeColor = BlackFade;
    };

    struct SelectPopupConfig
    {
        const char* windowName = "StormRevivalSelect";
        const char* titleText = "Storm Revival";
        const char* messageText = "Select an option.";
        const char* acceptText = "MSG_Yes";
        const char* cancelText = "MSG_No";
        bool localizeTitle = false;
        bool localizeMessage = false;
        bool localizeButtons = true;
    };
}
