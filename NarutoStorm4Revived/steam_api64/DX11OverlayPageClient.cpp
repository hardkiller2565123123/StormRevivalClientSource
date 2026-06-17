#include "DX11OverlayInternal.h"
#include "FrameworkAddon.h"
#include "SteamConfig.h"
#include "SteamIDManager.h"

void DrawClientPage()
{
    ImGui::TextUnformatted("LAN-only release");
    ImGui::Separator();
    ImGui::TextWrapped("Account login and hosted master services are removed from this package.");
    ImGui::Text("SteamID64: %llu", static_cast<unsigned long long>(SteamIDManager::GetSteamID64()));
    ImGui::TextWrapped("Steam ID auto-detect is enabled by default. It uses the active Steam account when available, otherwise a machine-unique offline ID.");

    static char personaBuffer[64]{};
    static bool personaLoaded = false;
    if (!personaLoaded)
    {
        strncpy_s(personaBuffer, SteamIDManager::GetPersonaName(), _TRUNCATE);
        personaLoaded = true;
    }

    if (ImGui::InputText("Display name", personaBuffer, sizeof(personaBuffer)))
    {
        SteamIDManager::SetPersonaName(personaBuffer);
    }

    if (ImGui::Button("Save display name"))
    {
        SteamIDManager::SetPersonaName(personaBuffer);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::TextUnformatted("DLC");

    bool enableDlcUnlock = SteamConfig::IsDlcUnlockEnabled();
    if (ImGui::Checkbox("Enable installed DLC loader", &enableDlcUnlock))
        SteamConfig::SetDlcUnlockEnabled(enableDlcUnlock);

    ImGui::TextWrapped("Default is OFF. Turn this on only when your owned DLC files are installed. This enables Steam DLC responses and client file redirection for DLC content paths.");
    ImGui::Text("DLC folder: %s", SteamConfig::GetDlcFolder().c_str());
    ImGui::Text("DLC files detected: %s", SteamConfig::HasDlcContentOnDisk() ? "yes" : "no");
}
