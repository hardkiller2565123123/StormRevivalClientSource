#include "OnlineMenuResearch.h"

#include <sstream>

namespace OnlineMenuResearch
{
    const std::vector<FlashCallInfo>& KnownFlashCalls()
    {
        static const std::vector<FlashCallInfo> calls = {
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "Initialize", 7,
             "Called from sub_140676250 after binding netbattlemainmenu."},
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "Start", 0,
             "Called from sub_140676A68."},
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "SetLock", 0,
             "Called from sub_140676A18."},
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "SetStepEnd", 0,
             "Registered as callback name in sub_140676250."},
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "SetStepLogin", 0,
             "Registered as callback name in sub_140676250."},
            {"ccUiFlashNetBattleMainMenu", "netbattlemainmenu", "unknown/off_1414DCA90", "SetMatchingVoice", 0,
             "Registered as callback name in sub_140676250."},
            {"ccUiFlashNetBattleMainMenu", "net_card.swf", "_root.all_nut.all_card", "Initialize", 0,
             "Called by sub_1406A5F18 through sub_1406A5F38."},
            {"ccUiFlashNetBattleMainMenu", "net_card.swf", "_root.all_nut.all_card", "setCardInfo", 11,
             "Called by sub_1406A60D4 when a5 == 0."},
            {"ccUiFlashNetBattleMainMenu", "net_card.swf", "_root.all_nut.all_card", "RequestSetCardInfo", 11,
             "Called by sub_1406A60D4 when a5 != 0."},
            {"ccUiFlashNetBattleMainMenu", "netbattleeventbanner", "_root.all_nut.all_banner", "Initialize", 0,
             "Called by sub_140671D28 through sub_140671D48."},
            {"ccUiFlashNetBattleMainMenu", "netbattleeventbanner", "_root.all_nut.all_banner", "setTitleBanner", 1,
             "Called by sub_140672320."},
            {"ccUiFlashNetBattleMainMenu", "netbattleeventbanner", "_root.all_nut.all_banner", "SetTextTitle", 1,
             "Called by sub_140672384."},
            {"ccUiFlashNetBattleMainMenu", "netbattleeventbanner", "_root.all_nut.all_banner", "SetTextDay", 1,
             "Called by sub_140671DC0."},
        };
        return calls;
    }

    std::string BuildResearchReport()
    {
        std::ostringstream out;
        out << "Storm Evo Online Menu Research Base\n";
        out << "===================================\n\n";
        out << "This module is intentionally unused. It documents confirmed IDA findings only.\n\n";
        for (const auto& call : KnownFlashCalls())
        {
            out << "Owner: " << call.owner << "\n";
            out << "SWF: " << call.swf << "\n";
            out << "Root: " << call.root << "\n";
            out << "Method: " << call.method << "\n";
            out << "Args: " << call.argCount << "\n";
            out << "Notes: " << call.notes << "\n\n";
        }
        return out.str();
    }
}
