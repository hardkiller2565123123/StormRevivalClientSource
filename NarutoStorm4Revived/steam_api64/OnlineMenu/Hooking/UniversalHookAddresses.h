#pragma once
#include <cstdint>

namespace StormRevival::OnlineMenu::Hooking::Addresses
{
    /*
        One place for every native Storm 4 address used by the OnlineMenu/OpenArchive
        hook layer. Keep new hook targets here instead of scattering 0x140... values
        through StageResourceHooks/ScenarioHooks/SceneHooks/etc.

        Safety policy:
        - UI hooks are enabled by default because they are the safest instrumentation layer.
        - Stage/Resource/Scenario/Scene hooks are catalogued here but disabled by default
          until each one is re-tested individually. The 2026-06-26 crash happened after
          the broad Resource/Scenario pass, so do not enable them all at once.
    */

    constexpr std::uintptr_t ImageBaseLabel = 0x140000000ULL;

    namespace UI
    {
        constexpr std::uintptr_t RegisterMovie       = 0x14060759C;
        constexpr std::uintptr_t InvokeWithArgs      = 0x140607BA0;
        constexpr std::uintptr_t InvokeNoArgs        = 0x140607B5C;
        constexpr std::uintptr_t InvokeReturn        = 0x140607B7C;
        constexpr std::uintptr_t UnregisterMovie     = 0x1406078CC;
        constexpr std::uintptr_t RegisterCallbacks   = 0x1401FD0AC;
    }

    namespace MainMenu
    {
        constexpr std::uintptr_t Initialize          = 0x140676250;
        constexpr std::uintptr_t Finalize            = 0x140676054;
        constexpr std::uintptr_t GetMode             = 0x1406760F4;
        constexpr std::uintptr_t GetModeBattle       = 0x140676164;
        constexpr std::uintptr_t GetSelectLimitEvent = 0x1406761E0;
        constexpr std::uintptr_t SetBingoItem        = 0x140676904;
        constexpr std::uintptr_t SetEventLock        = 0x14067699C;
        constexpr std::uintptr_t Restart             = 0x140676A34;
        constexpr std::uintptr_t SetUnlock           = 0x140676A9C;
        constexpr std::uintptr_t ActionDispatch      = 0x1405C17B4;
        constexpr std::uintptr_t StateMap            = 0x1405C3064;
    }

    namespace Stage
    {
        constexpr std::uintptr_t StageFilterLoad     = 0x1403B0074; // unsafe by default
        constexpr std::uintptr_t StageFilterApply    = 0x140A0FDB0; // unsafe by default
        constexpr std::uintptr_t StageInfoCreate     = 0x140941E90; // x86/old research anchor, not auto-hooked
        constexpr std::uintptr_t StageInfoInsert     = 0x140941AB0; // x86/old research anchor, not auto-hooked
    }

    namespace Resources
    {
        constexpr std::uintptr_t DatabaseLoad        = 0x140A03D30; // unsafe by default
        constexpr std::uintptr_t DatabaseLookup      = 0x140A139F0; // unsafe/hot by default
        constexpr std::uintptr_t ResourcePathTable   = 0x140136C6C;
    }

    namespace Scenario
    {
        constexpr std::uintptr_t GpSettingLoad       = 0x14043FB28; // unsafe by default
        constexpr std::uintptr_t ParseEntry          = 0x14043F208; // unsafe by default
        constexpr std::uintptr_t XmlParse            = 0x1404B6284; // unsafe by default
        constexpr std::uintptr_t XmlAttribute        = 0x1404B6B58; // unsafe/hot by default
        constexpr std::uintptr_t XmlChild            = 0x1404B6BC8; // unsafe/hot by default
        constexpr std::uintptr_t XmlSibling          = 0x1404B6B90; // unsafe/hot by default
        constexpr std::uintptr_t CharacterCodeToId   = 0x14052990C;
    }

    namespace Scene
    {
        constexpr std::uintptr_t BossSceneCreate     = 0x1406E4BC0; // disabled by default
        constexpr std::uintptr_t SetSceneName        = 0x140AB4550; // disabled by default
    }

    namespace Lobby
    {
        constexpr std::uintptr_t LobbyInit           = 0x1406734A8;
        constexpr std::uintptr_t LobbyFinalize       = 0x1406732AC;
        constexpr std::uintptr_t GetLock             = 0x140673374;
        constexpr std::uintptr_t GetVsOk             = 0x140673438;
    }
}
