#pragma once

namespace RuntimeUiOptions
{
    struct Options
    {
        bool EnableRuntimeUiPatches = true;

        // Scaleform icon suppressors. These do not edit save data; they only suppress
        // the Flash calls that draw the current player/team preview icons.
        bool HideAllPlayerIcons = false;
        bool HideLeaderIcon = false;
        bool HideSupport1Icon = false;
        bool HideSupport2Icon = false;
        bool HideSetCharacter = false;
        bool HideMenuKeyHelp = false;
        bool HideCustomPlayerIcons = false;

        // Experimental runtime replacement/scaffold toggles.
        bool EnableClassicStormTheme = false;
        bool EnableAnimatedPopupResearch = true;
        bool EnableRuntimeNameEditor = false;
        bool EnableRuntimePortraitEditor = false;
        bool EnableRuntimeTeamEditor = false;

        // Research logging. Useful while mapping SetCharacter / portrait / preset calls.
        bool LogCharacterSelectFlash = true;
        bool LogIconCalls = true;
        bool LogSetCharacterCalls = true;
    };

    bool Init();
    void Shutdown();

    Options& Mutable();
    const Options& Get();

    void ResetDefaults();

    bool ShouldSuppressScaleformMethod(const char* method);
    void LogScaleformMethod(const char* swf, const char* target, const char* method, unsigned int argCount);
    const char* ExplainSuppression(const char* method);
}
