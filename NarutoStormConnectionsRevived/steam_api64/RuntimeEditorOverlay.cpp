#include "StdInc.h"
#include "RuntimeEditorOverlay.h"
#include "DX11OverlayInternal.h"
#include "CharacterRuntimeEditor.h"
#include "RuntimeUiOptions.h"
#include "PopupTypes.h"
#include "PopupManager.h"
#include "Logger.h"
#include "DX11OverlayPageResources.h"
#include "CustomAudioPlayer.h"

#include <string>
#include <vector>
#include <sstream>

namespace
{
    struct NativeFunctionEntry
    {
        const char* System;
        const char* CleanName;
        uintptr_t Rva;
        const char* IdaName;
        const char* Purpose;
        const char* ControlUse;
    };

    const NativeFunctionEntry kNativeFunctions[] =
    {
        { "Text", "TextManager::GetTextById", 0x1073930, "sub_141073930", "textId -> localized display string", "Custom labels, menu replacement text, popup/title localization." },
        { "Text", "TextManager::FindTextEntryByHash", 0x108E170, "sub_14108E170", "hash tree lookup for text entries", "Lookup diagnostics and future injected text ids." },
        { "Text", "NuccTextHashString", 0x1254890, "sub_141254890", "CRC32-MPEG2 text hash for null-terminated strings", "Exact hash generator for text IDs." },
        { "Text", "NuccTextHashBuffer", 0x1254840, "sub_141254840", "CRC32-MPEG2 hash for a fixed buffer", "Hash binary/name chunks safely." },

        { "Flash", "FlashObject::Ctor", 0x71DE20, "sub_14071DE20", "constructs base Flash/Scaleform object", "Documents base object used by all popup/select/fade windows." },
        { "Flash", "FlashObject::Dtor", 0x71E020, "sub_14071E020", "destroys Flash/Scaleform object and movie tree", "Cleanup map for safe lifecycle fixes." },
        { "Flash", "FlashObject::CreateInstance", 0x71E2D0, "sub_14071E2D0", "creates a Scaleform instance by movie/path", "Native popup/window creation pipeline." },
        { "Flash", "FlashObject::GetValue", 0x71E220, "sub_14071E220", "reads a Scaleform value from a movie", "Result polling, select window values, fade alpha." },
        { "Flash", "FlashObject::CallMethodNoArgs", 0x71F110, "sub_14071F110", "calls a Scaleform method with no args", "OpenWindow, CloseWindow, Push, Pop." },
        { "Flash", "FlashObject::CallMethodReturn", 0x71F250, "sub_14071F250", "calls a Scaleform method and writes a return value", "GetSelectValue, GetFadeAlpha." },
        { "Flash", "FlashObject::CallMethodArgs", 0x71F390, "sub_14071F390", "calls a Scaleform method with typed args", "SetMessageText, SetVisible, SetSelectParam, AddHelp." },

        { "Dialog", "DialogWindow::Ctor", 0x763340, "sub_140763340", "constructs native message dialog", "Startup popup and custom F2 dialog studio." },
        { "Dialog", "DialogWindow::Create", 0x763B50, "sub_140763B50", "creates mc_win01 and initializes word wrap", "Native popup creation." },
        { "Dialog", "DialogWindow::UpdateAutoVisibility", 0x7636A0, "sub_1407636A0", "auto hides dialog while system is busy", "Prevents popups covering fade/load states." },
        { "Dialog", "DialogWindow::UpdateCloseCheck", 0x7638F0, "sub_1407638F0", "checks input and closes dialog", "Manual close behavior." },
        { "Dialog", "DialogWindow::Open", 0x764040, "sub_140764040", "calls OpenWindow and plays SE 24", "Open popup from F2." },
        { "Dialog", "DialogWindow::SetMessageText", 0x764220, "sub_140764220", "calls SetMessageText", "Live popup body replacement." },
        { "Dialog", "DialogWindow::SetVisible", 0x764370, "sub_140764370", "calls SetVisible", "Hide/show native dialog." },

        { "Fade", "FadeWindow::IsFadeBusyOrVisible", 0x7741F0, "sub_1407741F0", "checks fade busy flag / GetFadeAlpha", "Avoids stacking fade effects." },
        { "Fade", "FadeWindow::SetFadeColorType", 0x7742C0, "sub_1407742C0", "classifies white/black/custom fade color", "Fade preset controls." },
        { "Fade", "FadeWindow::StartFade", 0x7744D0, "sub_1407744D0", "starts fadeInOut with color type and frame count", "Popup fade wrapper and future scene fades." },

        { "Select", "SelectWindow::GetResult", 0x801E80, "sub_140801E80", "returns result at +464", "Choice popup result polling." },
        { "Select", "SelectWindow::Open", 0x801FD0, "sub_140801FD0", "opens mc_win00 select window", "Future yes/no and multi-option dialogs." },
        { "Select", "SelectWindow::SetupYesNo", 0x803A90, "sub_140803A90", "builds MSG_Yes / MSG_No select params", "Native yes/no popup support." },
        { "Select", "SelectWindow::SetTitle", 0x803640, "sub_140803640", "sets select window title", "Choice popup title control." },
        { "Select", "SelectWindow::NotifyUiMode", 0x8016C0, "sub_1408016C0", "notifies help manager mode", "Correct help/footer behavior for select windows." },
        { "Select", "SelectWindow::OpenHelpPopup", 0x8021D0, "sub_1408021D0", "pushes key-help state", "Native button guide support." },
        { "Select", "SelectWindow::CloseHelpPopup", 0x802160, "sub_140802160", "pops key-help state", "Clean help/footer cleanup." },

        { "Help", "HelpButtonManager::SetHelpModeText", 0x780450, "sub_140780450", "sets current button-help text", "Button guide mode mapping." },
        { "Help", "HelpButtonManager::PushHelpSet", 0x780FC0, "sub_140780FC0", "Push/AddHelp/SetVisible for xcmn_set", "Native help/footer stack." },
        { "Help", "HelpButtonManager::PopHelpSet", 0x780C30, "sub_140780C30", "Pop and restore xcmn_set visibility", "Prevent stuck help prompts." },

        { "Sound", "SoundManager::PlayUiSoundEx", 0x923140, "sub_140923140", "plays UI SE with volume/pitch/pan/delay", "Popup open/close/click sounds." },
        { "Sound", "SoundManager::PlayUiSound", 0x922B00, "sub_140922B00", "small wrapper for UI SE", "Simple UI sound trigger path." },
        { "Sound", "CriAtomManager::PlaySoundEffectCue", 0x12CADC0, "sub_1412CADC0", "SE cue -> CRI SetCueId/Start", "Future external UI sound replacement." },
        { "Sound", "CriAtomManager::GetLoadedBankStatus", 0x12C8500, "sub_1412C8500", "checks BGM/SE/special bank load status", "Safe validation before playing cues." },

        { "Input", "InputManager::GetCurrentButtonMask", 0x1092020, "sub_141092020", "returns current global button mask", "Popup close and help button routing." },
        { "Input", "TaskManager::HasTaskType", 0x1076B70, "sub_141076B70", "checks 32 task slots for a type", "Busy-state and popup visibility guards." },
        { "Input", "SystemBusy::IsBusyOrTask13Active", 0x8F34C0, "sub_1408F34C0", "busy flag OR task type 13", "Hide popups during load/fade/system tasks." },

        { "String", "NuccString::Assign", 0x0B1B00, "sub_1400B1B00", "assigns SSO/heap game string", "Safe title/body/path string writes." },
        { "String", "NuccString::Append", 0x0B3830, "sub_1400B3830", "appends to SSO/heap game string", "Build native paths like ::CheckHideWindow." },
        { "String", "NuccString::CopyCtor", 0x0B6920, "sub_1400B6920", "copies a game string", "Popup/select window path copies." },
        { "Value", "FlashValue::Ctor", 0x0FEC40, "sub_1400FEC40", "constructs 48-byte Scaleform value", "Bool/int/float/string arg arrays." },
        { "Value", "FlashValue::Dtor", 0x0FECE0, "sub_1400FECE0", "releases owned Scaleform value", "Prevents leaks when calling native UI." },
    };

    PopupTypes::FadeRgb FadeFromPreset(int preset)
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

    const char* FadePresetName(int preset)
    {
        switch (preset)
        {
        case 0: return "White";
        case 2: return "Storm Blue";
        case 3: return "Chakra Orange";
        case 4: return "Ink Purple";
        default: return "Black";
        }
    }

    std::string Narrow(const std::wstring& ws)
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

    void LogNativeFunctionMap()
    {
        Logger::Info("=== Native UI / Runtime Function Map ===");
        for (const auto& entry : kNativeFunctions)
        {
            std::ostringstream ss;
            ss << entry.System << "::" << entry.CleanName
               << " rva=0x" << std::hex << std::uppercase << entry.Rva
               << " ida=" << entry.IdaName
               << " purpose=" << entry.Purpose
               << " use=" << entry.ControlUse;
            Logger::Info(ss.str());
        }
    }

    void DrawHeader()
    {
        ImGui::Text("Storm API Runtime Control Center");
        ImGui::SameLine();
        ImGui::TextDisabled("native UI wrappers + runtime controls");
        ImGui::Separator();
    }

    void DrawStatusStrip()
    {
        ImGui::Text("Popup: %s", PopupManager::IsShowing() ? "showing" : "idle");
        ImGui::SameLine();
        ImGui::Text("Busy: %s", PopupManager::IsBusy() ? "yes" : "no");
        ImGui::SameLine();
        ImGui::Text("Active Popup ID: %u", PopupManager::ActivePopupId());
        ImGui::SameLine();
        ImGui::Text("Title WAV: %s", CustomAudioPlayer::HasTitleTrack() ? "found" : "missing");
        if (CustomAudioPlayer::HasTitleTrack())
            ImGui::TextDisabled("%s", Narrow(CustomAudioPlayer::TitlePath()).c_str());
    }

    void DrawQuickActions()
    {
        if (ImGui::Button("Welcome popup", ImVec2(150.0f, 30.0f)))
        {
            PopupTypes::TimedPopupConfig cfg{};
            cfg.delayMs = 0;
            cfg.durationMs = 4500;
            cfg.allowInputClose = true;
            cfg.useFade = false;
            PopupManager::ShowTimedWelcome(cfg);
        }
        ImGui::SameLine();
        if (ImGui::Button("Close popup", ImVec2(130.0f, 30.0f)))
            PopupManager::CloseNow();
        ImGui::SameLine();
        if (ImGui::Button("Play title.wav", ImVec2(140.0f, 30.0f)))
            CustomAudioPlayer::PlayTitleLoop();
        ImGui::SameLine();
        if (ImGui::Button("Fade title.wav", ImVec2(140.0f, 30.0f)))
            CustomAudioPlayer::FadeOutTitle(750);
        ImGui::SameLine();
        if (ImGui::Button("Stop title.wav", ImVec2(140.0f, 30.0f)))
            CustomAudioPlayer::StopTitle();
    }

    void DrawPopupStudio()
    {
        ImGui::Text("Native Dialog Studio");
        ImGui::TextWrapped("Backed by DialogWindow::Ctor/Create/SetMessageText/Open/SetVisible/Close. This uses the game popup path instead of a fake ImGui popup.");
        ImGui::Separator();

        static char title[128] = "Storm API";
        static char body[512] = "Runtime popup test.";
        static int durationMs = 5000;
        static bool allowInputClose = true;
        static bool useFade = false;
        static int fadePreset = 1;
        static int fadeDurationMs = 300;

        ImGui::InputText("Dialog title", title, ARRAYSIZE(title));
        ImGui::InputTextMultiline("Dialog body", body, ARRAYSIZE(body), ImVec2(0.0f, 90.0f));
        ImGui::SliderInt("Duration", &durationMs, 1000, 30000, "%d ms");
        ImGui::Checkbox("Allow controller/keyboard close", &allowInputClose);
        ImGui::Checkbox("Use native fade wrapper", &useFade);
        ImGui::BeginDisabled(!useFade);
        ImGui::Combo("Fade color", &fadePreset, "White\0Black\0Storm Blue\0Chakra Orange\0Ink Purple\0");
        ImGui::SliderInt("Fade duration", &fadeDurationMs, 100, 2000, "%d ms");
        ImGui::EndDisabled();

        if (ImGui::Button("Spawn native dialog", ImVec2(190.0f, 30.0f)))
        {
            PopupTypes::CustomPopupConfig cfg{};
            cfg.windowName = "StormRevivalF2Dialog";
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
        if (ImGui::Button("Black fade test", ImVec2(150.0f, 30.0f)))
        {
            PopupTypes::CustomPopupConfig cfg{};
            cfg.windowName = "StormRevivalFadeDialog";
            cfg.titleText = "Native Fade";
            cfg.bodyText = "This popup was opened with the fade wrapper enabled.";
            cfg.durationMs = 3500;
            cfg.allowInputClose = true;
            cfg.useFade = true;
            cfg.fadeDurationMs = 350;
            cfg.fadeColor = PopupTypes::BlackFade;
            PopupManager::ShowCustomPopup(cfg);
        }
        ImGui::SameLine();
        if (ImGui::Button("Close current", ImVec2(130.0f, 30.0f)))
            PopupManager::CloseNow();

        ImGui::TextDisabled("Current fade preset: %s", FadePresetName(fadePreset));
    }

    void DrawNativeUiControls()
    {
        DrawPopupStudio();
        ImGui::Spacing();
        ImGui::Separator();

        if (ImGui::CollapsingHeader("Native select / choice window", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextWrapped("Mapped: SelectWindow::SetupYesNo, Open, GetResult, SetTitle, OpenHelpPopup, CloseHelpPopup. Runtime yes/no creation is documented here; direct external select creation is kept scaffold-only until the lifetime wrapper is finished.");
            ImGui::BulletText("Result field: +464");
            ImGui::BulletText("State field: +468");
            ImGui::BulletText("Help flags: +512 / +520 / +524");
            ImGui::BulletText("Scaleform methods: SetSelectParam, SetWindowTitle, OpenWindow, GetSelectValue");
        }

        if (ImGui::CollapsingHeader("Help buttons / footer prompts", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextWrapped("Mapped: PushHelpSet, PopHelpSet, SetHelpModeText. Used by select windows and button guide UI.");
            ImGui::BulletText("xcmn_set = normal confirm/help set");
            ImGui::BulletText("xcmn_set_Back = back/cancel help set");
            ImGui::BulletText("Scaleform path: _root.all_nut.all_help_btn");
        }

        if (ImGui::CollapsingHeader("Text and Scaleform pipeline", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::TextWrapped("Text IDs use CRC32-MPEG2 / non-reflected CRC32, then a hash tree lookup. FlashObject wrappers use the same hash to find movie instances before calling Scaleform methods.");
            ImGui::BulletText("TextManager::GetTextById -> FindTextEntryByHash -> TextEntry +24");
            ImGui::BulletText("FlashObject::CallMethodArgs -> SetMessageText / SetVisible / SetSelectParam / AddHelp");
            ImGui::BulletText("FlashValue types: 2 bool, 3 int, 5 double/float, 6 string/text pointer");
        }
    }

    void DrawRuntimeUiToggles()
    {
        ImGui::Text("Runtime UI Controls");
        ImGui::TextWrapped("Live Scaleform suppression and logging toggles. These do not edit files.");
        ImGui::Separator();

        auto& opt = RuntimeUiOptions::Mutable();
        if (ImGui::Button("Reset UI toggles", ImVec2(160.0f, 28.0f)))
            RuntimeUiOptions::ResetDefaults();
        ImGui::SameLine();
        if (ImGui::Button("Log native function map", ImVec2(190.0f, 28.0f)))
            LogNativeFunctionMap();

        ImGui::Columns(2, nullptr, false);
        ImGui::Checkbox("Hide all player icons", &opt.HideAllPlayerIcons);
        ImGui::Checkbox("Hide leader icon", &opt.HideLeaderIcon);
        ImGui::Checkbox("Hide support 1 icon", &opt.HideSupport1Icon);
        ImGui::Checkbox("Hide support 2 icon", &opt.HideSupport2Icon);
        ImGui::Checkbox("Hide menu key help", &opt.HideMenuKeyHelp);
        ImGui::NextColumn();
        ImGui::Checkbox("Hide SetCharacter calls", &opt.HideSetCharacter);
        ImGui::Checkbox("Enable classic Storm theme scaffold", &opt.EnableClassicStormTheme);
        ImGui::Checkbox("Log character select Flash", &opt.LogCharacterSelectFlash);
        ImGui::Checkbox("Log icon calls", &opt.LogIconCalls);
        ImGui::Checkbox("Log SetCharacter calls", &opt.LogSetCharacterCalls);
        ImGui::Columns(1);
    }

    void DrawAudioControls()
    {
        ImGui::Text("External Audio Control");
        ImGui::TextWrapped("Title replacement is already wired to cue 203. Cue 202 or any other music cue fades it out.");
        ImGui::Separator();
        ImGui::Text("Status: %s", CustomAudioPlayer::IsTitlePlaying() ? "playing" : "stopped");
        ImGui::Text("File: %s", CustomAudioPlayer::HasTitleTrack() ? Narrow(CustomAudioPlayer::TitlePath()).c_str() : "missing Audio\\title.wav");

        if (ImGui::Button("Play loop", ImVec2(120.0f, 28.0f)))
            CustomAudioPlayer::PlayTitleLoop();
        ImGui::SameLine();
        if (ImGui::Button("Fade out", ImVec2(120.0f, 28.0f)))
            CustomAudioPlayer::FadeOutTitle(750);
        ImGui::SameLine();
        if (ImGui::Button("Stop now", ImVec2(120.0f, 28.0f)))
            CustomAudioPlayer::StopTitle();
        ImGui::TextDisabled("Playback backend: waveOut, PCM 16-bit WAV, scaled to 30%% volume in the loader.");
    }

    void DrawCharacterEditor()
    {
        auto& ed = CharacterRuntimeEditor::Options();
        auto& ov = CharacterRuntimeEditor::Overrides();

        ImGui::Text("Runtime Character / Battle Scaffold");
        ImGui::TextWrapped("Safe-mode controls for the character runtime pipeline. Keep Safe Mode on unless we are intentionally testing memory writes.");
        ImGui::Separator();

        ImGui::Checkbox("Runtime editor enabled", &ed.Enabled);
        ImGui::Checkbox("F2 opens this standalone editor", &ed.F2OpensEditor);
        ImGui::Checkbox("Safe mode: no memory writes", &ed.SafeModeNoMemoryWrites);
        ImGui::Checkbox("Log character lookups", &ed.LogCharacterLookup);
        ImGui::Checkbox("Log name builder", &ed.LogNameBuilder);
        ImGui::Checkbox("Log battle param build", &ed.LogBattleParamBuild);

        ImGui::Separator();
        ImGui::Text("Scaffold override values (-1 disables)");
        ImGui::Columns(2, nullptr, false);
        ImGui::InputInt("Forced preset", &ov.ForcedPreset);
        ImGui::InputInt("Forced leader", &ov.ForcedLeaderCharacter);
        ImGui::InputInt("Forced support 1", &ov.ForcedSupport1Character);
        ImGui::InputInt("Forced support 2", &ov.ForcedSupport2Character);
        ImGui::NextColumn();
        ImGui::InputInt("Forced costume", &ov.ForcedCostume);
        ImGui::InputInt("Forced color", &ov.ForcedColor);
        ImGui::InputInt("Forced main portrait", &ov.ForcedMainPortrait);
        ImGui::InputInt("Forced support portrait", &ov.ForcedSupportPortrait);
        ImGui::Columns(1);

        if (ImGui::Button("Reset overrides", ImVec2(150.0f, 28.0f)))
            CharacterRuntimeEditor::ResetOverrides();
        ImGui::SameLine();
        if (ImGui::Button("Log character map", ImVec2(160.0f, 28.0f)))
            CharacterRuntimeEditor::LogMap();
        ImGui::SameLine();
        if (ImGui::Button("Log runtime summary", ImVec2(170.0f, 28.0f)))
            CharacterRuntimeEditor::LogRuntimeSummary();

        ImGui::Separator();
        ImGui::Text("Battle / In-Game Model Test");
        ImGui::TextWrapped("Test build. Safe Mode ON logs only. Safe Mode OFF writes BattleSelectParam slot data and tries NetMenu3DModel::SetModel if the manager exists.");

        ImGui::Checkbox("Write BattleSelectParam slot", &ov.WriteBattleSelectParam);
        ImGui::SameLine();
        ImGui::Checkbox("Apply NetMenu3DModel", &ov.ApplyNetMenuModel);

        ImGui::Columns(2, nullptr, false);
        ImGui::InputInt("Battle slot 0/1", &ov.BattleSlot);
        ImGui::InputInt("Player/Character ID", &ov.BattleCharacterId);
        ImGui::InputInt("Costume ID", &ov.BattleCostumeId);
        ImGui::InputInt("CharaCode/Model ID", &ov.BattleCharaCode);
        ImGui::NextColumn();
        ImGui::InputInt("Variant", &ov.BattleVariantId);
        ImGui::InputInt("Model mode", &ov.BattleModelMode);
        ImGui::InputInt("Model state", &ov.BattleModelState);
        ImGui::InputInt("Pair skill", &ov.PreviewPairSkillId);
        ImGui::Columns(1);

        if (ImGui::Button("Apply Battle Test", ImVec2(170.0f, 30.0f)))
            CharacterRuntimeEditor::ApplyBattleModelTest();
        ImGui::SameLine();
        if (ImGui::Button("Read Current", ImVec2(130.0f, 30.0f)))
            CharacterRuntimeEditor::ReadCurrentSelectionScaffold();

        ImGui::Text("Last battle apply: %s", ov.LastBattleApplyMessage[0] ? ov.LastBattleApplyMessage : "none");
        if (ov.BattleApplyBlockedBySafeMode)
            ImGui::TextDisabled("Safe mode blocked native writes. Turn it off only when testing.");
    }

    void DrawKnownFunctions()
    {
        static int systemFilter = 0;
        const char* systems = "All\0Text\0Flash\0Dialog\0Fade\0Select\0Help\0Sound\0Input\0String\0Value\0Character\0";
        const char* systemNames[] = { "All", "Text", "Flash", "Dialog", "Fade", "Select", "Help", "Sound", "Input", "String", "Value", "Character" };

        ImGui::Text("Mapped Native Functions");
        ImGui::TextWrapped("Consolidated names for everything we have mapped so far. This replaces the old random function tabs.");
        ImGui::Combo("System filter", &systemFilter, systems);

        if (ImGui::BeginTable("native_function_map_f2", 5,
            ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY,
            ImVec2(0.0f, 280.0f)))
        {
            ImGui::TableSetupColumn("System", ImGuiTableColumnFlags_WidthFixed, 82.0f);
            ImGui::TableSetupColumn("Clean name", ImGuiTableColumnFlags_WidthFixed, 220.0f);
            ImGui::TableSetupColumn("RVA", ImGuiTableColumnFlags_WidthFixed, 82.0f);
            ImGui::TableSetupColumn("Purpose");
            ImGui::TableSetupColumn("Control use");
            ImGui::TableHeadersRow();

            for (const auto& entry : kNativeFunctions)
            {
                if (systemFilter != 0 && strcmp(entry.System, systemNames[systemFilter]) != 0)
                    continue;
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted(entry.System);
                ImGui::TableSetColumnIndex(1); ImGui::TextWrapped("%s", entry.CleanName);
                ImGui::TableSetColumnIndex(2); ImGui::Text("0x%llX", static_cast<unsigned long long>(entry.Rva));
                ImGui::TableSetColumnIndex(3); ImGui::TextWrapped("%s", entry.Purpose);
                ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", entry.ControlUse);
            }

            if (systemFilter == 0 || strcmp(systemNames[systemFilter], "Character") == 0)
            {
                for (const auto& entry : CharacterRuntimeEditor::FunctionMap())
                {
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0); ImGui::TextUnformatted("Character");
                    ImGui::TableSetColumnIndex(1); ImGui::TextWrapped("%s", entry.Name);
                    ImGui::TableSetColumnIndex(2); ImGui::Text("0x%llX", static_cast<unsigned long long>(entry.Rva));
                    ImGui::TableSetColumnIndex(3); ImGui::TextWrapped("%s", entry.Description);
                    ImGui::TableSetColumnIndex(4); ImGui::TextWrapped("%s", entry.HookUse);
                }
            }

            ImGui::EndTable();
        }
    }

    void DrawControlCenter()
    {
        DrawStatusStrip();
        ImGui::Spacing();
        DrawQuickActions();
        ImGui::Separator();

        if (ImGui::BeginChild("control_center_left", ImVec2(0.0f, 0.0f), false))
        {
            if (ImGui::CollapsingHeader("Native dialog controls", ImGuiTreeNodeFlags_DefaultOpen))
                DrawPopupStudio();
            if (ImGui::CollapsingHeader("Runtime UI toggles", ImGuiTreeNodeFlags_DefaultOpen))
                DrawRuntimeUiToggles();
            if (ImGui::CollapsingHeader("Audio controls", ImGuiTreeNodeFlags_DefaultOpen))
                DrawAudioControls();
        }
        ImGui::EndChild();
    }
}

namespace RuntimeEditorOverlay
{
    void Draw()
    {
        if (!g_RuntimeEditorOpen)
            return;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 size(940.0f, 700.0f);
        ImVec2 pos(viewport->Pos.x + 32.0f, viewport->Pos.y + 54.0f);

        if (viewport->Size.x < 1000.0f)
            size.x = viewport->Size.x - 32.0f;
        if (viewport->Size.y < 780.0f)
            size.y = viewport->Size.y - 80.0f;

        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowBgAlpha(0.95f);

        if (!ImGui::Begin("Storm API Runtime Control Center (F2)", &g_RuntimeEditorOpen,
            ImGuiWindowFlags_NoCollapse))
        {
            ImGui::End();
            return;
        }

        DrawHeader();

        if (ImGui::BeginTabBar("runtime_control_tabs"))
        {
            if (ImGui::BeginTabItem("Control Center"))
            {
                DrawControlCenter();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Native UI"))
            {
                DrawNativeUiControls();
                ImGui::Separator();
                DrawKnownFunctions();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Characters / Runtime"))
            {
                DrawCharacterEditor();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Resources / Mods"))
            {
                DX11OverlayPageResources::Draw();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}
