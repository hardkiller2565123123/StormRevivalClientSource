#include "VoiceStatusExamples.h"
#include "../Flash/FlashCallLayer.h"

namespace StormRevival::OnlineMenu::VoiceStatus
{
    static constexpr const char* kMovie = "netbattlemainmenu";
    static constexpr const char* kRoot  = "_root.all_nut"; // verify from off_1414DCA90[0]

    void Show(std::uintptr_t ui)
    {
        Flash::CallNoArgs(ui, kMovie, kRoot, "SetVoiceIn");
    }

    void Hide(std::uintptr_t ui)
    {
        Flash::CallNoArgs(ui, kMovie, kRoot, "SetVoiceOut");
    }

    void SetText(std::uintptr_t ui, const char* text)
    {
        Flash::CallString(ui, kMovie, kRoot, "SetVoiceText", text);
    }

    void ExampleServerStatus(std::uintptr_t ui)
    {
        Show(ui);
        SetText(ui, "Storm Revival Online\\nPlayers Online: 0\\nServer: Research Stub");
    }
}
