#pragma once

namespace StormRevival::OnlineMenu::Hooks
{
    /*
      Runtime Settings Button Hook Plan

      Hook 1:
        sub_140607B5C(scene, movie, root, function)

      If:
        movie == "netbattlemainmenu"
        function == "Initialize"

      After original returns:
        CustomMenu::OnNetBattleMainMenuInitialized(scene)

      Hook 2:
        sub_1406760F4(menu)

      It returns:
        netbattlemainmenu.GetMode()

      If return == 100:
        CustomMenu::TryHandleSelectedMode(menu, 100)
        skip stock transition.

      Confirmed names:
        sub_14060759C = RegisterFlashMovie
        sub_1401FD0AC = RegisterFlashCallbacks
        sub_140607B5C = InvokeFlashNoArgs
        sub_140607BA0 = InvokeFlashWithArgs
        sub_1406760F4 = GetMode
        sub_140676164 = GetModeBattele
    */
}
