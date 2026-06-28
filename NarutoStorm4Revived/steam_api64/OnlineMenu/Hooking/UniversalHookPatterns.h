#pragma once

namespace StormRevival::OnlineMenu::Hooking::Patterns
{
    /*
        Pattern table for version-independent hook resolving.

        Rules:
        - Leave a pattern as nullptr until it is verified in IDA for at least one EXE.
        - Unsupported EXEs will NOT use fixed 0x140... addresses unless explicitly allowed
          in steam_config.ini with online_menu_allow_fixed_addresses=1.
        - Once you verify a signature, place it here and every hook will automatically use
          pattern scan fallback on base game, Evolution, or future exe variants.

        IDA pattern format:
            "48 89 5C 24 ?? 57 48 83 EC ??"
    */

    namespace UI
    {
        // TODO: fill these from the target exe once IDA byte signatures are verified.
        static const char* RegisterMovie      = nullptr;
        static const char* InvokeWithArgs     = nullptr;
        static const char* InvokeNoArgs       = nullptr;
        static const char* InvokeReturn       = nullptr;
        static const char* UnregisterMovie    = nullptr;
        static const char* RegisterCallbacks  = nullptr;
    }

    namespace MainMenu
    {
        static const char* Initialize          = nullptr;
        static const char* GetMode             = nullptr;
        static const char* GetModeBattle       = nullptr;
        static const char* ActionDispatch      = nullptr;
        static const char* StateMap            = nullptr;
    }

    namespace Resources
    {
        static const char* DatabaseLoad        = nullptr;
        static const char* DatabaseLookup      = nullptr;
        static const char* ResourcePathTable   = nullptr;
    }

    namespace Stage
    {
        static const char* StageFilterLoad     = nullptr;
        static const char* StageFilterApply    = nullptr;
    }

    namespace Scenario
    {
        static const char* GpSettingLoad       = nullptr;
        static const char* ParseEntry          = nullptr;
        static const char* XmlParse            = nullptr;
        static const char* XmlAttribute        = nullptr;
        static const char* XmlChild            = nullptr;
        static const char* XmlSibling          = nullptr;
    }

    namespace Scene
    {
        static const char* BossSceneCreate     = nullptr;
        static const char* SetSceneName        = nullptr;
    }
}
