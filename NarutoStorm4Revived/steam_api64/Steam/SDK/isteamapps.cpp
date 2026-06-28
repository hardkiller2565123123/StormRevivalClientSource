#include <algorithm>
#include <array>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <string_view>

#include <koalabox/logger.hpp>

#include "smoke_api/smoke_api.hpp"
#include "smoke_api/interfaces/steam_apps.hpp"
#include "steam_api/virtuals/steam_api_virtuals.hpp"

namespace {
    constexpr AppId_t NS4_APP_ID = 349040;

    struct ns4_dlc_entry {
        AppId_t app_id;
        const char* name;
    };

    // Known Naruto Storm 4 DLC AppIDs that the game can ask SteamApps for.
    // Availability is still decided by the real Steam/SmokeAPI license result.
    constexpr std::array<ns4_dlc_entry, 4> NS4_DLC_LIST = {{
        {416420, "NARUTO SHIPPUDEN Ultimate Ninja STORM 4 - DLC Pack 1"},
        {416421, "NARUTO SHIPPUDEN Ultimate Ninja STORM 4 - DLC Pack 2"},
        {416422, "NARUTO SHIPPUDEN Ultimate Ninja STORM 4 - DLC Pack 3"},
        {495160, "NARUTO SHIPPUDEN Ultimate Ninja STORM 4 - Road to Boruto"},
    }};

    constexpr std::array<std::string_view, 92> NS4_DLC_CONTENT_MARKERS = {{
        "TUTORIAL_STORY_DLC2_004",
        "IsClearDlcCmnParam",
        "dlc/ep_r2b/st30_s020",
        "dlc/ep_r2b/pt11_s010",
        "dlc/ep_r2b/pt11_s020",
        "dlc/ep_r2b/pt42_s020",
        "dlc/ep_r2b/pt42_s030",
        "dlc/ep_r2b/pt42_s040",
        "dlc/ep_r2b/pt45_s010",
        "data/st/st_script_dlc.xfbin",
        "dlc/ep_gar/",
        "dlc/ep_sik/",
        "st/dlc/ep_r2b/",
        "pt/dlc/ep_r2b/",
        "dlc/ep_r2b/pt",
        "sim:data/sim/dlcpackdata.cpk",
        "data/sim/dlcpackdata.cpk",
        "DLC_ex_13",
        "DLC02_SUB_BATTLE_09",
        "DLC02_SUB_BATTLE_13",
        "DLCCheck",
        "DLCDegradeConfiurm",
        "DlcBorutoDownload",
        "DlcLimitCostumeDownload",
        "DlcCommonAddContentsDownload",
        "DLCUpdateConfiurm",
        "DisableDLC",
        "DLC_cha_050",
        "DLC_cha_052",
        "DLC_cha_054",
        "DLC_cha_051",
        "DLC_cha_044",
        "DLC_cha_047",
        "DLC_cha_053",
        "DLC_cha_059",
        "DLC_cha_056",
        "DLC_cha_064",
        "DLC_cha_055",
        "DLC_cha_068",
        "DLC_cha_072",
        "DLC_cha_069",
        "DLC_cha_070",
        "DLC_cha_067",
        "DLC_cha_071",
        "DLC_cha_063",
        "DLC_cha_042",
        "DLC_cha_081",
        "DLC_cha_079",
        "DLC_cha_080",
        "DLC_cha_075",
        "DLC_cha_073",
        "DLC_cha_014",
        "DLC_cha_017",
        "DLC_cha_019",
        "DLC_cha_022",
        "DLC_cha_026",
        "DLC_28",
        "DLC_29",
        "DLC_30",
        "DLC_44",
        "DLC_45",
        "DLC_39_Xbox",
        "DLCDegradeConf",
        "DLC_27",
        "DLC_38",
        "DLC_36_Xbox",
        "DLC_24",
        "DLC_notice_012_steam",
        "DLC_notice_014_steam",
        "DLC_notice_016_steam",
        "DLC_notice_015_steam",
        "DLC_ex_04",
        "PL_ANM_WIN_S_DLC",
        "PL_ANM_WIN_L_DLC",
        "data/no_release/message/plus_dlc/PLAT/LANG/messageInfo.bin.xfbin",
        "ClearDlcCmnParam",
        "DLC_ex_16",
        "DLC_ex_14",
        "dlc/%d",
        "BindDlcData",
        "DlcThread",
        "BattleDownloadContents",
        "IsEnableR2bContents",
        "ADDCONTENT_INSTALL",
        "LoadContents",
        "SetDisableRtbContents",
        "NotifyRtbContents",
        "data/network/PLAT/COMMON_ADD_CONTENTS.xfbin",
        "COMMON_ADD_CONTENTS",
        "ccSceneGameModeSelect::CheckRtbAddContents",
        "data/system/content_info.xfbin",
        "ccSceneDownloadContentsPossessCheck",
    }};

    const ns4_dlc_entry* find_known_ns4_dlc(const AppId_t app_id) noexcept {
        const auto found = std::ranges::find_if(NS4_DLC_LIST, [&](const ns4_dlc_entry& dlc) {
            return dlc.app_id == app_id;
        });

        return found == NS4_DLC_LIST.end() ? nullptr : &(*found);
    }

    std::filesystem::path get_game_root() {
        if(const char* override_dir = std::getenv("NS4_GAME_DIR")) {
            if(*override_dir) {
                return std::filesystem::path(override_dir);
            }
        }

        if(const char* dlc_dir = std::getenv("NS4_DLC_DIR")) {
            if(*dlc_dir) {
                const auto path = std::filesystem::path(dlc_dir);
                if(path.filename() == "dlc") {
                    return path.parent_path();
                }
            }
        }

        return std::filesystem::current_path();
    }

    std::filesystem::path get_dlc_root() {
        if(const char* dlc_dir = std::getenv("NS4_DLC_DIR")) {
            if(*dlc_dir) {
                return std::filesystem::path(dlc_dir);
            }
        }

        return get_game_root() / "dlc";
    }

    bool exists_anywhere(const std::string_view game_relative_path) {
        auto normalized = std::string(game_relative_path);

        if(normalized.starts_with("sim:")) {
            normalized.erase(0, 4);
        }

        std::ranges::replace(normalized, '/', static_cast<char>(std::filesystem::path::preferred_separator));

        const auto game_root = get_game_root();
        const auto dlc_root = get_dlc_root();

        const std::array candidates = {
            game_root / normalized,
            dlc_root / normalized,
            dlc_root / std::filesystem::path(normalized).filename(),
        };

        for(const auto& candidate : candidates) {
            std::error_code ec;
            if(std::filesystem::exists(candidate, ec)) {
                return true;
            }
        }

        return false;
    }

    bool has_installed_ns4_dlc_payload() {
        std::error_code ec;
        const auto dlc_root = get_dlc_root();
        if(std::filesystem::exists(dlc_root, ec) && std::filesystem::is_directory(dlc_root, ec)) {
            return true;
        }

        for(const auto marker : NS4_DLC_CONTENT_MARKERS) {
            if(marker.find('/') != std::string_view::npos && exists_anywhere(marker)) {
                return true;
            }
        }

        return false;
    }

    bool is_ns4(const AppId_t app_id) noexcept {
        return app_id == NS4_APP_ID;
    }

    bool real_license_allows_dlc(
        const char* caller,
        const AppId_t game_app_id,
        const AppId_t dlc_id,
        const std::function<bool()>& original_function
    ) noexcept {
        // Keep ownership delegated to real Steam/SmokeAPI. File presence only helps install/detection logic.
        return smoke_api::steam_apps::IsDlcUnlocked(caller, game_app_id, dlc_id, original_function);
    }

    void copy_name(char* dst, const int dst_size, const char* src) noexcept {
        if(!dst || dst_size <= 0) {
            return;
        }

        std::strncpy(dst, src ? src : "", static_cast<size_t>(dst_size - 1));
        dst[dst_size - 1] = '\0';
    }
}

VIRTUAL(bool) ISteamApps_BIsSubscribedApp(PARAMS(const AppId_t dlc_id)) noexcept {
    return real_license_allows_dlc(
        __func__,
        smoke_api::get_app_id(),
        dlc_id,
        SWAPPED_CALL_CLOSURE(ISteamApps_BIsSubscribedApp, ARGS(dlc_id))
    );
}

VIRTUAL(bool) ISteamApps_BIsDlcInstalled(PARAMS(const AppId_t dlc_id)) noexcept {
    const auto app_id = smoke_api::get_app_id();
    const bool licensed = real_license_allows_dlc(
        __func__,
        app_id,
        dlc_id,
        SWAPPED_CALL_CLOSURE(ISteamApps_BIsDlcInstalled, ARGS(dlc_id))
    );

    if(!licensed) {
        return false;
    }

    if(is_ns4(app_id) && find_known_ns4_dlc(dlc_id)) {
        return has_installed_ns4_dlc_payload();
    }

    return true;
}

VIRTUAL(int) ISteamApps_GetDLCCount(PARAMS()) noexcept {
    const auto original_count = smoke_api::steam_apps::GetDLCCount(
        __func__,
        smoke_api::get_app_id(),
        SWAPPED_CALL_CLOSURE(ISteamApps_GetDLCCount, ARGS())
    );

    if(is_ns4(smoke_api::get_app_id()) && has_installed_ns4_dlc_payload()) {
        return std::max(original_count, static_cast<int>(NS4_DLC_LIST.size()));
    }

    return original_count;
}

VIRTUAL(bool) ISteamApps_BGetDLCDataByIndex(
    PARAMS(
        const int iDLC,
        AppId_t* p_dlc_id,
        bool* pbAvailable,
        char* pchName,
        const int cchNameBufferSize
    )
) noexcept {
    const bool original_result = smoke_api::steam_apps::GetDLCDataByIndex(
        __func__,
        smoke_api::get_app_id(),
        iDLC,
        p_dlc_id,
        pbAvailable,
        pchName,
        cchNameBufferSize,
        SWAPPED_CALL_CLOSURE(
            ISteamApps_BGetDLCDataByIndex,
            ARGS(iDLC, p_dlc_id, pbAvailable, pchName, cchNameBufferSize)
        ),
        SWAPPED_CALL_CLOSURE(
            ISteamApps_BIsSubscribedApp,
            ARGS(p_dlc_id ? *p_dlc_id : 0)
        )
    );

    if(original_result) {
        return true;
    }

    const auto app_id = smoke_api::get_app_id();
    if(!is_ns4(app_id) || iDLC < 0 || iDLC >= static_cast<int>(NS4_DLC_LIST.size())) {
        return false;
    }

    const auto& dlc = NS4_DLC_LIST[static_cast<size_t>(iDLC)];
    if(p_dlc_id) {
        *p_dlc_id = dlc.app_id;
    }

    if(pbAvailable) {
        *pbAvailable = real_license_allows_dlc(
            "ISteamApps_BGetDLCDataByIndex::NS4Fallback",
            app_id,
            dlc.app_id,
            SWAPPED_CALL_CLOSURE(ISteamApps_BIsSubscribedApp, ARGS(dlc.app_id))
        );
    }

    copy_name(pchName, cchNameBufferSize, dlc.name);
    return has_installed_ns4_dlc_payload();
}
