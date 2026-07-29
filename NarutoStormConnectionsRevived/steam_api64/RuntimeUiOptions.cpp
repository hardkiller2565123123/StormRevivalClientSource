#include "StdInc.h"
#include "RuntimeUiOptions.h"
#include "Logger.h"

#include <cstring>
#include <string>

namespace
{
    RuntimeUiOptions::Options g_Options;

    bool Equals(const char* a, const char* b)
    {
        return a && b && std::strcmp(a, b) == 0;
    }

    const char* ExplainSuppression(const char* method)
    {
        if (!RuntimeUiOptions::ShouldSuppressScaleformMethod(method))
            return "not suppressed";
        if (Equals(method, "SetLeaderIcon")) return "leader icon hidden by runtime UI option";
        if (Equals(method, "SetSupport1Icon")) return "support 1 icon hidden by runtime UI option";
        if (Equals(method, "SetSupport2Icon")) return "support 2 icon hidden by runtime UI option";
        if (Equals(method, "SetCharacter")) return "SetCharacter hidden by experimental classic UI option";
        if (Equals(method, "setMenuKeyHelp")) return "menu key help hidden by experimental classic UI option";
        return "suppressed by runtime UI option";
    }
}

namespace RuntimeUiOptions
{
    bool Init()
    {
        ResetDefaults();
        Logger::Info("RuntimeUiOptions initialized");
        return true;
    }

    void Shutdown()
    {
        Logger::Info("RuntimeUiOptions shutdown");
    }

    Options& Mutable()
    {
        return g_Options;
    }

    const Options& Get()
    {
        return g_Options;
    }

    void ResetDefaults()
    {
        g_Options = Options{};
    }

    bool ShouldSuppressScaleformMethod(const char* method)
    {
        if (!g_Options.EnableRuntimeUiPatches || !method)
            return false;

        if (g_Options.HideAllPlayerIcons)
        {
            if (Equals(method, "SetLeaderIcon") ||
                Equals(method, "SetSupport1Icon") ||
                Equals(method, "SetSupport2Icon"))
                return true;
        }

        if (g_Options.HideLeaderIcon && Equals(method, "SetLeaderIcon"))
            return true;

        if (g_Options.HideSupport1Icon && Equals(method, "SetSupport1Icon"))
            return true;

        if (g_Options.HideSupport2Icon && Equals(method, "SetSupport2Icon"))
            return true;

        if (g_Options.HideSetCharacter && Equals(method, "SetCharacter"))
            return true;

        if (g_Options.HideMenuKeyHelp && Equals(method, "setMenuKeyHelp"))
            return true;

        return false;
    }

    void LogScaleformMethod(const char* swf, const char* target, const char* method, unsigned int argCount)
    {
        if (!g_Options.EnableRuntimeUiPatches || !method)
            return;

        const bool isIcon = Equals(method, "SetLeaderIcon") || Equals(method, "SetSupport1Icon") || Equals(method, "SetSupport2Icon");
        const bool isSetCharacter = Equals(method, "SetCharacter");
        const bool isMenuHelp = Equals(method, "setMenuKeyHelp");

        if ((isIcon && !g_Options.LogIconCalls) || (isSetCharacter && !g_Options.LogSetCharacterCalls))
            return;

        if (!isIcon && !isSetCharacter && !isMenuHelp && !g_Options.LogCharacterSelectFlash)
            return;

        Logger::Info(
            std::string("RuntimeUiOptions Scaleform method=") + method +
            " swf=" + (swf ? swf : "") +
            " target=" + (target ? target : "") +
            " argc=" + std::to_string(argCount));
    }

    const char* ExplainSuppression(const char* method)
    {
        if (!ShouldSuppressScaleformMethod(method))
            return "not suppressed";
        if (Equals(method, "SetLeaderIcon")) return "leader icon hidden by runtime UI option";
        if (Equals(method, "SetSupport1Icon")) return "support 1 icon hidden by runtime UI option";
        if (Equals(method, "SetSupport2Icon")) return "support 2 icon hidden by runtime UI option";
        if (Equals(method, "SetCharacter")) return "SetCharacter hidden by experimental classic UI option";
        if (Equals(method, "setMenuKeyHelp")) return "menu key help hidden by experimental classic UI option";
        return "suppressed by runtime UI option";
    }
}
