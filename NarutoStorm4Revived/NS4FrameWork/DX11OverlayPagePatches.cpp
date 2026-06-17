#include "DX11OverlayInternal.h"
#include "PatchManager.h"

#include <cctype>
#include <cstdlib>

namespace
{
    bool ParseHexBytes(const char* text, std::vector<unsigned char>& outBytes, std::string& error)
    {
        outBytes.clear();
        error.clear();

        std::string token;
        auto flushToken = [&]() -> bool
        {
            if (token.empty())
                return true;

            if (token.size() > 2 && token[0] == '0' && (token[1] == 'x' || token[1] == 'X'))
                token.erase(0, 2);

            if (token.empty() || token.size() > 2)
            {
                error = "Use one-byte hex tokens like 90 or 0x90.";
                return false;
            }

            char* end = nullptr;
            unsigned long value = std::strtoul(token.c_str(), &end, 16);

            if (!end || *end != '\0' || value > 0xFF)
            {
                error = "Invalid hex byte: " + token;
                return false;
            }

            outBytes.push_back(static_cast<unsigned char>(value));
            token.clear();
            return true;
        };

        for (const char* p = text; p && *p; ++p)
        {
            const char c = *p;

            if (std::isspace(static_cast<unsigned char>(c)) || c == ',' || c == ';')
            {
                if (!flushToken())
                    return false;
                continue;
            }

            if (!std::isxdigit(static_cast<unsigned char>(c)) && c != 'x' && c != 'X')
            {
                error = "Only hex bytes, spaces, commas, and 0x prefixes are supported.";
                return false;
            }

            token.push_back(c);
        }

        if (!flushToken())
            return false;

        if (outBytes.empty())
        {
            error = "No bytes entered.";
            return false;
        }

        return true;
    }

    uintptr_t ParseAddressText(const char* text)
    {
        if (!text || !*text)
            return 0;

        return static_cast<uintptr_t>(_strtoui64(text, nullptr, 0));
    }

    void DrawRuntimePatchLab()
    {
        static char patchName[96] = "Storm4RuntimePatch";
        static char rvaText[32] = "0x0";
        static char expectedHex[512]{};
        static char replacementHex[512] = "90";
        static char patternHex[512]{};
        static std::string lastResult;

        PatchManager::PatchState& state = PatchManager::State();

        ImGui::Separator();
        ImGui::Text("Runtime EXE Patch Lab");
        ImGui::Checkbox("Enable runtime patch lab", &state.RuntimePatchLab);
        ImGui::Text("Module base: 0x%p", reinterpret_cast<void*>(PatchManager::ModuleBase()));

        ImGui::InputText("Patch Name", patchName, sizeof(patchName));
        ImGui::InputText("RVA", rvaText, sizeof(rvaText));
        ImGui::InputTextMultiline("Expected Bytes", expectedHex, sizeof(expectedHex), ImVec2(0, 48));
        ImGui::InputTextMultiline("Replacement Bytes", replacementHex, sizeof(replacementHex), ImVec2(0, 48));

        if (ImGui::Button("Apply RVA Patch", ImVec2(150, 24)))
        {
            std::vector<unsigned char> expected;
            std::vector<unsigned char> replacement;
            std::string error;

            if (expectedHex[0] && !ParseHexBytes(expectedHex, expected, error))
                lastResult = error;
            else if (!ParseHexBytes(replacementHex, replacement, error))
                lastResult = error;
            else
            {
                auto result = PatchManager::ApplyRuntimePatchByRva(
                    patchName,
                    ParseAddressText(rvaText),
                    expected,
                    replacement);
                lastResult = result.Status;
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Revert Named Patch", ImVec2(170, 24)))
        {
            auto result = PatchManager::RevertRuntimePatch(patchName);
            lastResult = result.Status;
        }

        ImGui::InputTextMultiline("Find Pattern", patternHex, sizeof(patternHex), ImVec2(0, 48));

        if (ImGui::Button("Apply Pattern Patch", ImVec2(170, 24)))
        {
            std::vector<unsigned char> pattern;
            std::vector<unsigned char> replacement;
            std::string error;

            if (!ParseHexBytes(patternHex, pattern, error))
                lastResult = error;
            else if (!ParseHexBytes(replacementHex, replacement, error))
                lastResult = error;
            else
            {
                auto result = PatchManager::ApplyRuntimePatchByPattern(patchName, pattern, replacement);
                lastResult = result.Status;
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Copy Summary", ImVec2(130, 24)))
            ImGui::SetClipboardText(PatchManager::RuntimePatchSummary().c_str());

        if (!lastResult.empty())
            ImGui::TextWrapped("Last result: %s", lastResult.c_str());

        const auto& patches = PatchManager::RuntimePatches();
        ImGui::Text("Tracked patches: %d", static_cast<int>(patches.size()));

        ImGui::BeginChild("##RuntimePatchList", ImVec2(0, 120), true);
        for (const auto& patch : patches)
        {
            ImGui::Text("%s | RVA 0x%llX | %zu bytes | %s",
                patch.Name.c_str(),
                static_cast<unsigned long long>(patch.Rva),
                patch.Size,
                patch.Applied ? "applied" : "off");
            ImGui::TextDisabled("%s", patch.Status.c_str());
        }
        ImGui::EndChild();
    }
}

void DrawPatchesPage()
{
    if (g_SelectedSubPage == 0)
    {
        ImGui::Text("Patches > Display");
        ImGui::Separator();

        ActiveCheckbox("Borderless fullscreen helper", &g_PatchBorderlessFullscreen, "Uses the existing WindowedFullscreen system. This is the only borderless toggle now.");
        PlannedCheckbox("Native ultrawide support", &g_PatchNativeUltrawide, "Needs aspect ratio/FOV patch addresses. UI is ready.");
        PlannedCheckbox("Multi-monitor support", &g_PatchMultiMonitor, "Needs monitor selection/window placement options.");
        PlannedCheckbox("High refresh fix", &g_PatchHighRefresh, "Needs timing/FPS limiter investigation.");

        ImGui::Separator();
        ImGui::TextWrapped("Display patches live only here. Duplicate display patch controls were removed from Game.");
    }
    else if (g_SelectedSubPage == 1)
    {
        ImGui::Text("Patches > Gameplay");
        ImGui::Separator();

        PlannedCheckbox("Disable intro", &g_PatchDisableIntro, "Needs intro movie/file redirect.");
        PlannedCheckbox("Auto skip cutscenes", &g_PatchAutoSkipCutscenes, "Needs cutscene state hook.");
        PlannedCheckbox("Unlock all temporary", &g_PatchUnlockAllTemp, "Needs unlock table and temporary state layer.");
        PlannedCheckbox("Unlock all permanent", &g_PatchUnlockAllPermanent, "Needs save mutation support.");
        ActiveCheckbox("Background running / pause helper", &g_PatchBackgroundPauseFix, "Keeps the game active while tabbed out after a short startup grace period.");
        ActiveCheckbox("Skip online checks", &g_PatchSkipOnlineChecks, "Uses the offline/network-blocking framework already loaded by NS4 Revived.");

        ImGui::Separator();
        ImGui::TextWrapped("Gameplay patches live only here. Game tab now focuses on saves and information.");
    }
    else if (g_SelectedSubPage == 2)
    {
        ImGui::Text("Patches > Safety");
        ImGui::Separator();

        ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "[ACTIVE]");
        ImGui::SameLine();
        ImGui::TextWrapped("Feature is backed by current framework code or an existing helper.");

        ImGui::TextColored(ImVec4(1.0f, 0.65f, 0.2f, 1.0f), "[PLANNED]");
        ImGui::SameLine();
        ImGui::TextWrapped("UI is preserved, but the actual patch still needs addresses/hooks before it should touch memory.");

        ImGui::Separator();

        ImGui::Checkbox("Only enable safe patches by default", &g_PatchSkipOnlineChecks);
        HelpMarker("Keeps current safe/offline patch helpers enabled, while planned memory patches stay informational.");
    }
    else
    {
        ImGui::Text("Patches > Status");
        ImGui::Separator();

        ImGui::Text("Borderless fullscreen: %s", g_PatchBorderlessFullscreen ? "enabled" : "disabled");
        ImGui::Text("Focus passthrough: startup grace");
        ImGui::Text("Background helper: %s", g_PatchBackgroundPauseFix ? "enabled after grace" : "disabled");
        ImGui::Text("Offline check skip: %s", g_PatchSkipOnlineChecks ? "enabled" : "disabled");

        DrawRuntimePatchLab();
    }
}
