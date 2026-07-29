#include "../StdInc.h"
#include "RuntimeEditorOverlay.h"
#include "../CharacterRuntimeEditor.h"
#include "../RuntimeUiOptions.h"
#include "../PopupTypes.h"
#include "../PopupManager.h"
#include "../Logger.h"
#include "DX11OverlayPageResources.h"
#include "../CustomAudioPlayer.h"
#include "../DX11OverlayState.h"
#include "../imgui.h"

#include <sstream>
#include <string>
#include <vector>

namespace RuntimeEditorOverlay
{
    static std::atomic_bool g_Running{ false };
    static std::atomic_bool g_Open{ false };
    static HANDLE g_InputThread = nullptr;

    struct FunctionRow
    {
        const char* system;
        const char* name;
        uintptr_t rva;
        const char* ida;
        const char* use;
    };

    static const FunctionRow kFunctions[] =
    {
        { "Text", "TextManager::GetTextById", 0x1073930, "sub_141073930", "Text id -> display text" },
        { "Text", "TextManager::FindTextEntryByHash", 0x108E170, "sub_14108E170", "Hash tree lookup" },
        { "Text", "NuccTextHashString", 0x1254890, "sub_141254890", "CRC32-MPEG2 text hash" },
        { "Text", "NuccTextHashBuffer", 0x1254840, "sub_141254840", "CRC32-MPEG2 buffer hash" },

        { "Flash", "FlashObject::Ctor", 0x71DE20, "sub_14071DE20", "Base Scaleform object ctor" },
        { "Flash", "FlashObject::Dtor", 0x71E020, "sub_14071E020", "Base Scaleform object cleanup" },
        { "Flash", "FlashObject::CreateInstance", 0x71E2D0, "sub_14071E2D0", "Create/load Scaleform movie" },
        { "Flash", "FlashObject::GetValue", 0x71E220, "sub_14071E220", "Read Scaleform value" },
        { "Flash", "FlashObject::CallMethodNoArgs", 0x71F110, "sub_14071F110", "OpenWindow/CloseWindow/Push/Pop" },
        { "Flash", "FlashObject::CallMethodReturn", 0x71F250, "sub_14071F250", "GetSelectValue/GetFadeAlpha" },
        { "Flash", "FlashObject::CallMethodArgs", 0x71F390, "sub_14071F390", "SetMessageText/SetVisible/AddHelp" },

        { "Dialog", "DialogWindow::Ctor", 0x763340, "sub_140763340", "Native popup object" },
        { "Dialog", "DialogWindow::Create", 0x763B50, "sub_140763B50", "Create message window" },
        { "Dialog", "DialogWindow::Open", 0x764040, "sub_140764040", "OpenWindow + SE 24" },
        { "Dialog", "DialogWindow::SetMessageText", 0x764220, "sub_140764220", "Popup body text" },
        { "Dialog", "DialogWindow::SetVisible", 0x764370, "sub_140764370", "Hide/show popup" },
        { "Dialog", "DialogWindow::UpdateAutoVisibility", 0x7636A0, "sub_1407636A0", "Hide while busy" },
        { "Dialog", "DialogWindow::UpdateCloseCheck", 0x7638F0, "sub_1407638F0", "Input close check" },

        { "Fade", "FadeWindow::IsFadeBusyOrVisible", 0x7741F0, "sub_1407741F0", "Fade busy / alpha" },
        { "Fade", "FadeWindow::SetFadeColorType", 0x7742C0, "sub_1407742C0", "White/black/custom fade" },
        { "Fade", "FadeWindow::StartFade", 0x7744D0, "sub_1407744D0", "Start native fade" },

        { "Select", "SelectWindow::GetResult", 0x801E80, "sub_140801E80", "Choice result +0x1D0" },
        { "Select", "SelectWindow::Open", 0x801FD0, "sub_140801FD0", "Open select window" },
        { "Select", "SelectWindow::SetupYesNo", 0x803A90, "sub_140803A90", "Yes/No params" },
        { "Select", "SelectWindow::SetTitle", 0x803640, "sub_140803640", "Choice title" },
        { "Select", "SelectWindow::NotifyUiMode", 0x8016C0, "sub_1408016C0", "Help mode notify" },
        { "Select", "SelectWindow::OpenHelpPopup", 0x8021D0, "sub_1408021D0", "Push key help" },
        { "Select", "SelectWindow::CloseHelpPopup", 0x802160, "sub_140802160", "Pop key help" },

        { "Help", "HelpButtonManager::SetHelpModeText", 0x780450, "sub_140780450", "Footer button text" },
        { "Help", "HelpButtonManager::PushHelpSet", 0x780FC0, "sub_140780FC0", "Push xcmn_set" },
        { "Help", "HelpButtonManager::PopHelpSet", 0x780C30, "sub_140780C30", "Pop xcmn_set" },

        { "Sound", "SoundManager::PlayUiSoundEx", 0x923140, "sub_140923140", "UI SE with volume/pitch/pan" },
        { "Sound", "SoundManager::PlayUiSound", 0x922B00, "sub_140922B00", "Simple UI SE" },
        { "Sound", "CriAtomManager::PlaySoundEffectCue", 0x12CADC0, "sub_1412CADC0", "SE cue playback" },
        { "Sound", "CriAtomManager::GetLoadedBankStatus", 0x12C8500, "sub_1412C8500", "Bank load check" },

        { "Input", "InputManager::GetCurrentButtonMask", 0x1092020, "sub_141092020", "Global button mask" },
        { "Input", "TaskManager::HasTaskType", 0x1076B70, "sub_141076B70", "Task slot scan" },
        { "Input", "SystemBusy::IsBusyOrTask13Active", 0x8F34C0, "sub_1408F34C0", "Busy popup guard" },

        { "String", "NuccString::Assign", 0x0B1B00, "sub_1400B1B00", "Game string assign" },
        { "String", "NuccString::Append", 0x0B3830, "sub_1400B3830", "Game string append" },
        { "String", "NuccString::CopyCtor", 0x0B6920, "sub_1400B6920", "Game string copy" },
        { "String", "NuccObject::InitAllocator", 0x124BE90, "sub_14124BE90", "Allocator init" },
        { "String", "NuccAllocator::Free", 0x124BB20, "sub_14124BB20", "Allocator free" },

        { "Value", "FlashValue::Ctor", 0x0FEC40, "sub_1400FEC40", "48-byte arg ctor" },
        { "Value", "FlashValue::Dtor", 0x0FECE0, "sub_1400FECE0", "Release owned args" },
    };

    static const char* kStructNotes[] =
    {
        "NuccString: +0x18 small string / heap pointer, +0x28 size, +0x30 capacity, heap when capacity >= 0x10.",
        "FlashValue: +0x18 type flags. 2 bool, 3 int, 5 double/float, 6 string/text, 0x40 owned object.",
        "FlashObject: +0x30 movie tree root, +0x38 count, +0x48 current movie.",
        "DialogWindow: +0xC8 visibleState, +0xCC openSoundId, +0xD0 visibilityLock, +0xD4 input close, +0xD8 close mode.",
        "SelectWindow: +0x1D0 result, +0x1D4 state, +0x1D8 default, +0x200 help enabled, +0x20C help open.",
        "SoundManager: +0xF0 atom manager, soundId >> 12 = bank, soundId & 0xFFF = cue."
    };

    static std::string Narrow(const std::wstring& ws)
    {
        if (ws.empty())
            return {};
        int size = WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, nullptr, 0, nullptr, nullptr);
        if (size <= 0)
            return {};
        std::string out(size - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, out.data(), size, nullptr, nullptr);
        return out;
    }

    static PopupTypes::FadeRgb FadeFromPreset(int preset)
    {
        switch (preset)
        {
        case 0: return PopupTypes::WhiteFade;
        case 2: return PopupTypes::StormBlueFade;
        case 3: return PopupTypes::ChakraOrangeFade;
        case 4: return PopupTypes::InkPurpleFade;
        default: return PopupTypes::BlackFade;
        }
    }

    static void LogAllFunctions()
    {
        Logger::Info("=== Runtime F2 Function Map ===");
        for (const auto& f : kFunctions)
        {
            std::ostringstream ss;
            ss << f.system << " :: " << f.name << " rva=0x" << std::hex << std::uppercase << f.rva
               << " ida=" << f.ida << " use=" << f.use;
            Logger::Info(ss.str());
        }
        CharacterRuntimeEditor::LogMap();
    }

    static DWORD WINAPI InputThreadProc(LPVOID)
    {
        bool lastF2 = false;
        Logger::Info("RuntimeEditorOverlay F2 polling thread started");
        while (g_Running.load())
        {
            const bool f2Down = (GetAsyncKeyState(VK_F2) & 0x8000) != 0;
            if (f2Down && !lastF2)
                Toggle();
            lastF2 = f2Down;
            Sleep(25);
        }
        Logger::Info("RuntimeEditorOverlay F2 polling thread stopped");
        return 0;
    }

    static void DrawTopBar()
    {
        ImGui::TextUnformatted("Storm API Control Center");
        ImGui::SameLine();
        ImGui::TextDisabled("F2 | full input block while open");
        ImGui::Separator();
        ImGui::Text("Popup: %s", PopupManager::IsShowing() ? "showing" : "idle");
        ImGui::SameLine();
        ImGui::Text("Busy: %s", PopupManager::IsBusy() ? "yes" : "no");
        ImGui::SameLine();
        ImGui::Text("Popup ID: %u", PopupManager::ActivePopupId());
        ImGui::SameLine();
        ImGui::Text("Audio: %s", CustomAudioPlayer::IsTitlePlaying() ? "playing" : "off");
    }

    static void DrawPopupStudio()
    {
        static char title[128] = "Storm API";
        static char body[512] = "Runtime popup test.";
        static int durationMs = 5000;
        static bool allowInputClose = true;
        static bool useFade = false;
        static int fadePreset = 1;
        static int fadeDurationMs = 300;

        ImGui::TextUnformatted("Popup / Dialog Control");
        ImGui::InputText("Title", title, IM_ARRAYSIZE(title));
        ImGui::InputTextMultiline("Body", body, IM_ARRAYSIZE(body), ImVec2(0.0f, 86.0f));
        ImGui::SliderInt("Duration", &durationMs, 500, 30000, "%d ms");
        ImGui::Checkbox("Allow input close", &allowInputClose);
        ImGui::Checkbox("Native fade", &useFade);
        ImGui::BeginDisabled(!useFade);
        ImGui::Combo("Fade color", &fadePreset, "White\0Black\0Storm Blue\0Chakra Orange\0Ink Purple\0");
        ImGui::SliderInt("Fade time", &fadeDurationMs, 100, 2500, "%d ms");
        ImGui::EndDisabled();

        if (ImGui::Button("Spawn popup", ImVec2(140.0f, 28.0f)))
        {
            PopupTypes::CustomPopupConfig cfg{};
            cfg.windowName = "StormApiF2Popup";
            cfg.titleText = title;
            cfg.bodyText = body;
            cfg.durationMs = durationMs;
            cfg.allowInputClose = allowInputClose;
            cfg.useFade = useFade;
            cfg.fadeDurationMs = fadeDurationMs;
            cfg.fadeColor = FadeFromPreset(fadePreset);
            PopupManager::ShowCustomPopup(cfg);
        }
        ImGui::SameLine();
        if (ImGui::Button("Welcome", ImVec2(105.0f, 28.0f)))
        {
            PopupTypes::TimedPopupConfig cfg{};
            cfg.delayMs = 0;
            cfg.durationMs = 4500;
            cfg.allowInputClose = true;
            PopupManager::ShowTimedWelcome(cfg);
        }
        ImGui::SameLine();
        if (ImGui::Button("Close", ImVec2(90.0f, 28.0f)))
            PopupManager::CloseNow();
    }

    static void DrawAudioControl()
    {
        ImGui::TextUnformatted("Title Audio Control");
        ImGui::Text("title.wav: %s", CustomAudioPlayer::HasTitleTrack() ? Narrow(CustomAudioPlayer::TitlePath()).c_str() : "missing");
        if (ImGui::Button("Play", ImVec2(90.0f, 26.0f)))
            CustomAudioPlayer::PlayTitleLoop();
        ImGui::SameLine();
        if (ImGui::Button("Fade", ImVec2(90.0f, 26.0f)))
            CustomAudioPlayer::FadeOutTitle(750);
        ImGui::SameLine();
        if (ImGui::Button("Stop", ImVec2(90.0f, 26.0f)))
            CustomAudioPlayer::StopTitle();
        ImGui::TextDisabled("Auto: cue 203 starts title.wav; any other music cue fades it out. Volume is 30%%.");
    }

    static void DrawRuntimeUiToggles()
    {
        auto& opt = RuntimeUiOptions::Mutable();
        ImGui::TextUnformatted("Runtime UI Toggles");
        ImGui::Columns(2, nullptr, false);
        ImGui::Checkbox("Hide all player icons", &opt.HideAllPlayerIcons);
        ImGui::Checkbox("Hide leader icon", &opt.HideLeaderIcon);
        ImGui::Checkbox("Hide support 1", &opt.HideSupport1Icon);
        ImGui::Checkbox("Hide support 2", &opt.HideSupport2Icon);
        ImGui::Checkbox("Hide menu key help", &opt.HideMenuKeyHelp);
        ImGui::NextColumn();
        ImGui::Checkbox("Hide SetCharacter", &opt.HideSetCharacter);
        ImGui::Checkbox("Classic theme scaffold", &opt.EnableClassicStormTheme);
        ImGui::Checkbox("Log character Flash", &opt.LogCharacterSelectFlash);
        ImGui::Checkbox("Log icon calls", &opt.LogIconCalls);
        ImGui::Checkbox("Log SetCharacter", &opt.LogSetCharacterCalls);
        ImGui::Columns(1);
        if (ImGui::Button("Reset UI toggles", ImVec2(150.0f, 26.0f)))
            RuntimeUiOptions::ResetDefaults();
    }

    static void DrawInputControl()
    {
        ImGui::TextUnformatted("Overlay Input");
        ImGui::Checkbox("Block game clicks/keys while F1/F2 is open", &g_BlockGameInputWhenOpen);
        ImGui::Checkbox("Draw mouse cursor", &g_DrawMouseCursor);
        ImGui::TextDisabled("This update defaults to ON, so the game behind F1/F2 will not receive clicks/keyboard/controller input.");
    }

    static void DrawControlTab()
    {
        if (ImGui::BeginTable("control_layout", 2, ImGuiTableFlags_Resizable))
        {
            ImGui::TableSetupColumn("left", ImGuiTableColumnFlags_WidthStretch, 0.55f);
            ImGui::TableSetupColumn("right", ImGuiTableColumnFlags_WidthStretch, 0.45f);
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            if (ImGui::CollapsingHeader("Popup Studio", ImGuiTreeNodeFlags_DefaultOpen))
                DrawPopupStudio();
            if (ImGui::CollapsingHeader("Runtime UI", ImGuiTreeNodeFlags_DefaultOpen))
                DrawRuntimeUiToggles();
            ImGui::TableSetColumnIndex(1);
            if (ImGui::CollapsingHeader("Input Block", ImGuiTreeNodeFlags_DefaultOpen))
                DrawInputControl();
            if (ImGui::CollapsingHeader("Audio", ImGuiTreeNodeFlags_DefaultOpen))
                DrawAudioControl();
            ImGui::EndTable();
        }
    }

    static void DrawCharacterTab()
    {
        auto& ed = CharacterRuntimeEditor::Options();
        auto& ov = CharacterRuntimeEditor::Overrides();

        ImGui::TextUnformatted("Character Control");
        ImGui::Checkbox("Enabled", &ed.Enabled);
        ImGui::SameLine();
        ImGui::Checkbox("Safe mode", &ed.SafeModeNoMemoryWrites);
        ImGui::SameLine();
        ImGui::Checkbox("Log", &ed.LogCharacterLookup);

        if (ed.SafeModeNoMemoryWrites)
            ImGui::TextDisabled("Safe mode blocks native writes. Apply logs/queues values only.");
        else
            ImGui::TextColored(ImVec4(1.0f, 0.55f, 0.25f, 1.0f), "Native write mode requested. Direct wrappers still blocked in this build.");

        ImGui::Separator();
        if (ImGui::CollapsingHeader("Apply Queue", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::InputInt("Player slot", &ov.SelectedPlayerSlot);
            if (ov.SelectedPlayerSlot < 0) ov.SelectedPlayerSlot = 0;
            if (ov.SelectedPlayerSlot > 2) ov.SelectedPlayerSlot = 2;

            ImGui::Columns(2, nullptr, false);
            ImGui::InputInt("Character ID", &ov.PreviewCharacterId);
            ImGui::InputInt("Costume ID", &ov.PreviewCostumeId);
            ImGui::InputInt("Color ID", &ov.PreviewColorId);
            ImGui::InputInt("Variant", &ov.PreviewVariantId);
            ImGui::NextColumn();
            ImGui::InputInt("Face/portrait", &ov.PreviewFaceId);
            ImGui::InputInt("Costume effect", &ov.PreviewEffectId);
            ImGui::InputInt("Pair skill", &ov.PreviewPairSkillId);
            ImGui::Checkbox("Force preview reload", &ov.ForcePreviewReload);
            ImGui::Columns(1);

            ImGui::InputText("Costume name", ov.CostumeNameOverride, sizeof(ov.CostumeNameOverride));

            if (ImGui::Button("Apply", ImVec2(110.0f, 30.0f)))
                CharacterRuntimeEditor::ApplyOverrides();
            ImGui::SameLine();
            if (ImGui::Button("Read Current", ImVec2(120.0f, 30.0f)))
                CharacterRuntimeEditor::ReadCurrentSelectionScaffold();
            ImGui::SameLine();
            if (ImGui::Button("Reset", ImVec2(90.0f, 30.0f)))
                CharacterRuntimeEditor::ResetOverrides();

            if (ov.PendingApply)
                ImGui::TextDisabled("Last apply queued%s", ov.LastApplyBlockedBySafeMode ? " - blocked by safe mode" : "");
        }

        if (ImGui::CollapsingHeader("Old Runtime Overrides"))
        {
            ImGui::Columns(2, nullptr, false);
            ImGui::InputInt("Preset", &ov.ForcedPreset);
            ImGui::InputInt("Leader", &ov.ForcedLeaderCharacter);
            ImGui::InputInt("Support 1", &ov.ForcedSupport1Character);
            ImGui::InputInt("Support 2", &ov.ForcedSupport2Character);
            ImGui::NextColumn();
            ImGui::InputInt("Forced costume", &ov.ForcedCostume);
            ImGui::InputInt("Forced color", &ov.ForcedColor);
            ImGui::InputInt("Main portrait", &ov.ForcedMainPortrait);
            ImGui::InputInt("Support portrait", &ov.ForcedSupportPortrait);
            ImGui::Columns(1);
        }

        if (ImGui::CollapsingHeader("Mapped native calls", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::BulletText("SetCursorDirect: sub_140742460");
            ImGui::BulletText("SetFaceIcon: sub_140742FB0");
            ImGui::BulletText("SetCostumeName: sub_1407462E0");
            ImGui::BulletText("SetCostumeEffect: dispatched by sub_140739220 case 2");
            ImGui::BulletText("Preview set costume/color: sub_1407153D0 / sub_14073A8B0");
            ImGui::BulletText("Preview swap model: sub_140715480");
            ImGui::BulletText("NetMenu3DModel::SetModel: sub_140807F40");
        }

        if (ImGui::Button("Log summary", ImVec2(130.0f, 26.0f)))
            CharacterRuntimeEditor::LogRuntimeSummary();
        ImGui::SameLine();
        if (ImGui::Button("Log map", ImVec2(100.0f, 26.0f)))
            CharacterRuntimeEditor::LogMap();
    }

    static void DrawFunctionsTab()
    {
        static int filter = 0;
        const char* filters = "All\0Text\0Flash\0Dialog\0Fade\0Select\0Help\0Sound\0Input\0String\0Value\0Character\0Structs\0";
        const char* names[] = { "All", "Text", "Flash", "Dialog", "Fade", "Select", "Help", "Sound", "Input", "String", "Value", "Character", "Structs" };
        ImGui::TextUnformatted("Functions / Structs");
        ImGui::SameLine();
        if (ImGui::Button("Log all", ImVec2(90.0f, 24.0f)))
            LogAllFunctions();
        ImGui::Combo("Filter", &filter, filters);

        if (filter == 12 || filter == 0)
        {
            if (ImGui::CollapsingHeader("Struct notes", ImGuiTreeNodeFlags_DefaultOpen))
            {
                for (const char* note : kStructNotes)
                    ImGui::BulletText("%s", note);
            }
        }

        if (filter != 12)
        {
            if (ImGui::BeginTable("function_table", 5,
                ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY,
                ImVec2(0.0f, 420.0f)))
            {
                ImGui::TableSetupColumn("System", ImGuiTableColumnFlags_WidthFixed, 78.0f);
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 230.0f);
                ImGui::TableSetupColumn("RVA", ImGuiTableColumnFlags_WidthFixed, 82.0f);
                ImGui::TableSetupColumn("IDA", ImGuiTableColumnFlags_WidthFixed, 130.0f);
                ImGui::TableSetupColumn("Use");
                ImGui::TableHeadersRow();

                for (const auto& f : kFunctions)
                {
                    if (filter != 0 && strcmp(f.system, names[filter]) != 0)
                        continue;
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted(f.system);
                    ImGui::TableSetColumnIndex(1); ImGui::TextWrapped("%s", f.name);
                    ImGui::TableSetColumnIndex(2); ImGui::Text("0x%llX", static_cast<unsigned long long>(f.rva));
                    ImGui::TableSetColumnIndex(3); ImGui::TextUnformatted(f.ida);
                    ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", f.use);
                }

                if (filter == 0 || filter == 11)
                {
                    for (const auto& e : CharacterRuntimeEditor::FunctionMap())
                    {
                        ImGui::TableNextRow();
                        ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted("Character");
                        ImGui::TableSetColumnIndex(1); ImGui::TextWrapped("%s", e.Name);
                        ImGui::TableSetColumnIndex(2); ImGui::Text("0x%llX", static_cast<unsigned long long>(e.Rva));
                        ImGui::TableSetColumnIndex(3); ImGui::TextUnformatted(e.IdaName);
                        ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", e.HookUse);
                    }
                }
                ImGui::EndTable();
            }
        }
    }

    bool Init()
    {
        if (g_Running.exchange(true))
            return true;
        g_Open = false;
        g_BlockGameInputWhenOpen = true;
        g_InputThread = CreateThread(nullptr, 0, InputThreadProc, nullptr, 0, nullptr);
        if (!g_InputThread)
        {
            g_Running = false;
            Logger::Error("RuntimeEditorOverlay failed to create F2 polling thread");
            return false;
        }
        Logger::Info("RuntimeEditorOverlay initialized with consolidated F2 control center");
        return true;
    }

    void Shutdown()
    {
        if (!g_Running.exchange(false))
            return;
        if (g_InputThread)
        {
            WaitForSingleObject(g_InputThread, 1500);
            CloseHandle(g_InputThread);
            g_InputThread = nullptr;
        }
        g_Open = false;
        Logger::Info("RuntimeEditorOverlay shutdown");
    }

    void Toggle()
    {
        const bool nowOpen = !g_Open.load();
        g_Open = nowOpen;
        g_BlockGameInputWhenOpen = true;
        Logger::Info(nowOpen ? "RuntimeEditorOverlay opened with input block" : "RuntimeEditorOverlay closed");
    }

    bool IsOpen()
    {
        return g_Open.load();
    }

    void Update()
    {
        Render();
    }

    void Render()
    {
        if (!g_Open.load())
            return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 size(980.0f, 720.0f);
        ImVec2 pos(viewport->Pos.x + 24.0f, viewport->Pos.y + 42.0f);
        if (viewport->Size.x < 1040.0f)
            size.x = viewport->Size.x - 32.0f;
        if (viewport->Size.y < 780.0f)
            size.y = viewport->Size.y - 64.0f;

        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowBgAlpha(0.96f);

        bool open = g_Open.load();
        if (!ImGui::Begin("Storm API Control Center (F2)", &open, ImGuiWindowFlags_NoCollapse))
        {
            g_Open = open;
            ImGui::End();
            return;
        }
        g_Open = open;

        DrawTopBar();

        if (ImGui::BeginTabBar("runtime_tabs_v35"))
        {
            if (ImGui::BeginTabItem("Control"))
            {
                DrawControlTab();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Characters"))
            {
                DrawCharacterTab();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Resources"))
            {
                DX11OverlayPageResources::Draw();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Functions"))
            {
                DrawFunctionsTab();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}
