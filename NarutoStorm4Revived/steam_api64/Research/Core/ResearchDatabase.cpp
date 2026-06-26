#include "ResearchTypes.h"

namespace StormRevival
{
namespace Research
{
    const char* AreaName(ResearchArea area)
    {
        switch (area)
        {
        case Area_OnlineMenu: return "OnlineMenu";
        case Area_FreeBattle: return "FreeBattle";
        case Area_Story: return "Story";
        case Area_Settings: return "Settings";
        case Area_ShopUnlocks: return "ShopUnlocks";
        case Area_Stage: return "Stage";
        case Area_Character: return "Character";
        case Area_Combat: return "Combat";
        case Area_ResourceDatabase: return "ResourceDatabase";
        case Area_Lobby: return "Lobby";
        case Area_ProfileLeaderboard: return "ProfileLeaderboard";
        default: return "Unknown";
        }
    }

    static const ResearchAddress kAddressTable[] =
    {
        // ---------------------------------------------------------------------
        // Online menu / Scaleform bridge.
        // ---------------------------------------------------------------------
        { Area_OnlineMenu, "sub_14060759C", 0x14060759C, "Register Flash movie", "Loads/registers a SWF/GFX movie instance." },
        { Area_OnlineMenu, "sub_140607BA0", 0x140607BA0, "Invoke Flash with args", "Main ActionScript call bridge." },
        { Area_OnlineMenu, "sub_140607B5C", 0x140607B5C, "Invoke Flash no args", "Wrapper around sub_140607BA0 with no argument payload." },
        { Area_OnlineMenu, "sub_140607B7C", 0x140607B7C, "Invoke Flash return wrapper", "Wrapper around sub_140607BA0 used for getters like GetMode." },
        { Area_OnlineMenu, "sub_1406078CC", 0x1406078CC, "Unload Flash movie", "Finalizes/removes movie instance from runtime map." },
        { Area_OnlineMenu, "sub_1401FD0AC", 0x1401FD0AC, "Register Flash callbacks", "Binds ActionScript callback names to C++ callback handlers." },
        { Area_OnlineMenu, "sub_140676250", 0x140676250, "NetBattle main menu initialize", "Initializes netbattlemainmenu callbacks and Flash state." },
        { Area_OnlineMenu, "sub_1406760F4", 0x1406760F4, "GetMode", "Reads selected online menu mode from netbattlemainmenu." },
        { Area_OnlineMenu, "sub_140676164", 0x140676164, "GetModeBattele", "Reads selected battle sub-mode." },
        { Area_OnlineMenu, "sub_1406761E0", 0x1406761E0, "GetSelectLimitEventId", "Reads limit-event id from Flash." },
        { Area_OnlineMenu, "sub_1406722A0", 0x1406722A0, "Banner/title mode setup", "Sets online title/banner state." },

        // ---------------------------------------------------------------------
        // Lobby / online profile.
        // ---------------------------------------------------------------------
        { Area_Lobby, "sub_1406734A8", 0x1406734A8, "NetBattle lobby initialize", "Registers SelectNo, SelectNo2, MessageCall, voice callbacks." },
        { Area_Lobby, "sub_140673438", 0x140673438, "CallGetVsOk", "Lobby ready/VS confirmation getter." },
        { Area_Lobby, "sub_140673374", 0x140673374, "getLock1", "Lobby lock getter." },
        { Area_Lobby, "sub_1406B3DCC", 0x1406B3DCC, "Lobby member persona lookup", "Maps a lobby slot/member to known persona/card data." },
        { Area_Lobby, "sub_140AE6010", 0x140AE6010, "SteamID to persona name", "Uses SteamFriends persona name call." },
        { Area_Lobby, "sub_140AE6670", 0x140AE6670, "Lobby valid check", "Checks local/Steam lobby member availability." },
        { Area_Lobby, "sub_140AE6720", 0x140AE6720, "Lobby member id getter", "Returns SteamID for lobby member index." },
        { Area_ProfileLeaderboard, "sub_1406A60D4", 0x1406A60D4, "Player card builder", "Builds data sent to setCardInfo / RequestSetCardInfo." },

        // ---------------------------------------------------------------------
        // Resource database helpers.
        // ---------------------------------------------------------------------
        { Area_ResourceDatabase, "sub_140A03D30", 0x140A03D30, "Resource database lookup", "Finds loaded XFBIN resource by path/name." },
        { Area_ResourceDatabase, "sub_140A139F0", 0x140A139F0, "Table row lookup", "Searches a resource table using the hashed key format." },
        { Area_ResourceDatabase, "sub_140AAFB10", 0x140AAFB10, "Load table payload by key", "Resource lookup + row lookup + returns row payload at +16." },
        { Area_ResourceDatabase, "sub_140AAFA50", 0x140AAFA50, "Relative pointer fixup", "Converts packed-relative offsets into runtime pointers." },
        { Area_ResourceDatabase, "sub_140A01EB0", 0x140A01EB0, "Hash string", "Game hash for resource keys and lookup keys." },

        // ---------------------------------------------------------------------
        // Stage / settings / free battle.
        // ---------------------------------------------------------------------
        { Area_Stage, "sub_1403B0074", 0x1403B0074, "Stage filter variant loader", "Loads stageFilter.xfbin and selects base/noon/evening stage variant." },
        { Area_Stage, "sub_140A0FDB0", 0x140A0FDB0, "Apply stage filter", "Decodes packed stage filter bytes into runtime float parameters." },
        { Area_Stage, "sub_140A10150", 0x140A10150, "Stage filter singleton", "Returns address of global stage filter state." },
        { Area_Settings, "sub_14043FB28", 0x14043FB28, "GP scenario database loader", "Loads data/gp/setting/gpSetting.xfbin and iterates scenario rows." },
        { Area_Settings, "sub_14043F208", 0x14043F208, "GP scenario parser", "Parses Basic/World/Characters/Players/Uis/Files sections." },

        // ---------------------------------------------------------------------
        // Character / costumes / shop / unlocks.
        // ---------------------------------------------------------------------
        { Area_Character, "sub_1404B520C", 0x1404B520C, "216-byte entry database loader", "Clones packed records, fixes string pointers, pushes entries to runtime list." },
        { Area_Character, "sub_1404B5418", 0x1404B5418, "Character-like database bootstrap", "Calls sub_1404B520C with off_141485730 path." },
        { Area_Character, "sub_1404B612C", 0x1404B612C, "Vector push pointer", "Pushes pointer entries into a dynamic array." },
        { Area_Character, "sub_1404B9C0C", 0x1404B9C0C, "48-byte ID table loader", "Loads keyed ID table and inserts rows." },
        { Area_Character, "sub_1401C9590", 0x1401C9590, "64-byte variant table loader", "Loads and fixes a table of 64-byte records." },
        { Area_Character, "sub_1401C9CFC", 0x1401C9CFC, "Costume/variant key generator", "Builds keys with sprintf('%s%04d') and inserts by hash." },
        { Area_Character, "sub_1401CA4D0", 0x1401CA4D0, "96-byte metadata loader", "Loads name-keyed records with multiple string fields." },
        { Area_Character, "sub_1401CCC48", 0x1401CCC48, "Grouped item/localization table", "Groups 32-byte entries by hash key." },
        { Area_Character, "sub_1401CD508", 0x1401CD508, "104-byte reward/metadata table", "Loads larger records with five string pointers." },

        { Area_ShopUnlocks, "sub_14051956C", 0x14051956C, "Unlock material helper", "Entrypoint used by story completion to award costume materials." },
        { Area_ShopUnlocks, "sub_14050AA98", 0x14050AA98, "Add material progress by name", "Resolves group/name, updates material entries, and saves progress." },
        { Area_ShopUnlocks, "sub_14051EA54", 0x14051EA54, "Material group resolver", "Maps material name category to a group id." },
        { Area_ShopUnlocks, "sub_14051EDC0", 0x14051EDC0, "Material group expander", "Expands group id to COSTUME_MATERIAL_001 through 020 groups." },
        { Area_ShopUnlocks, "sub_14050C37C", 0x14050C37C, "Find material entry", "Searches material hash table at manager+22048; entries appear 16 bytes." },
        { Area_ShopUnlocks, "sub_14050A3F8", 0x14050A3F8, "Increment material progress", "Adds amount, clamps to max/current cap." },

        // ---------------------------------------------------------------------
        // Story / mission systems.
        // ---------------------------------------------------------------------
        { Area_Story, "sub_14068E778", 0x14068E778, "Story board UI loader", "Loads hist_cmn.swf and registers story board callbacks." },
        { Area_Story, "sub_140604588", 0x140604588, "Duel condition UI loader", "Loads duel_cond.swf and registers condition/boss callbacks." },
        { Area_Story, "sub_140595D24", 0x140595D24, "Story param lookup by key", "Looks up story/episode param row by string key." },
        { Area_Story, "sub_140595C64", 0x140595C64, "Story param lookup by id", "Looks up story/episode param row by numeric id." },
        { Area_Story, "sub_1405967C8", 0x1405967C8, "Story database root", "Returns qword_1415FD2D0 + 24 data root." },

        // ---------------------------------------------------------------------
        // Combat / battle parameter loaders.
        // ---------------------------------------------------------------------
        { Area_Combat, "sub_1402D3BE4", 0x1402D3BE4, "4-lane timing table", "Converts 30fps-authored frame values to runtime fps." },
        { Area_Combat, "sub_1402D4330", 0x1402D4330, "28-byte event table", "Loads timing/event records and resolves IDs." },
        { Area_Combat, "sub_1402D48B8", 0x1402D48B8, "28-byte fallback event table", "Applies default event id 77 when fields are zero." },
        { Area_Combat, "sub_140304DE0", 0x140304DE0, "Typed battle event loader", "Loads type/frame/id records and routes type < 3." },
        { Area_Combat, "sub_14033BF30", 0x14033BF30, "152-byte battle parameter loader", "Core combat/motion parameter loader with 30fps-to-runtime normalization." }
    };

    static const ResearchString kStringTable[] =
    {
        { Area_OnlineMenu, "netbattlemainmenu", "Online battle main menu movie instance." },
        { Area_OnlineMenu, "netbattlelobby", "Online lobby movie instance." },
        { Area_OnlineMenu, "GetMode", "Main menu selected mode getter." },
        { Area_OnlineMenu, "GetModeBattele", "Battle mode getter." },
        { Area_OnlineMenu, "SetMatchingVoice", "Online menu/lobby voice text setter." },

        { Area_Stage, "data/stage/stageFilter.xfbin", "Stage filter database." },
        { Area_Stage, "BTL_NS4_si51c02", "Base stage variant." },
        { Area_Stage, "BTL_NS4_si51c02_noon", "Noon stage variant." },
        { Area_Stage, "BTL_NS4_si51c02_evening", "Evening stage variant." },

        { Area_Settings, "data/gp/setting/gpSetting.xfbin", "Scenario/free-battle/story battle setup database." },
        { Area_Settings, "Basic", "Scenario basic section." },
        { Area_Settings, "battleParam", "Scenario battle parameter reference." },
        { Area_Settings, "Players", "Scenario player spawn/team section." },
        { Area_Settings, "Characters", "Scenario character list section." },

        { Area_ShopUnlocks, "COSTUME_MATERIAL_001", "Costume material group entry." },
        { Area_ShopUnlocks, "COSTUME_MATERIAL_020", "Costume material group entry." },

        { Area_Story, "data/ui/flash/FLASH_PLAT/hist_cmn/hist_cmn.swf", "Story board Flash UI." },
        { Area_Story, "data/ui/flash/FLASH_PLAT/duel_cond/duel_cond.swf", "Duel condition Flash UI." },
        { Area_Story, "SetEpisode", "Story board callback." },
        { Area_Story, "GetCondition", "Duel condition callback." },

        { Area_Combat, "30.0 / currentFPS", "Common conversion from 30fps-authored battle data to runtime fps." }
    };

    static const ResearchDatabase kDatabaseTable[] =
    {
        { Area_Stage, "StageFilter", "data/stage/stageFilter.xfbin", "sub_1403B0074 / sub_140A0FDB0", "Stage variants and packed filter bytes decoded into float parameters." },
        { Area_Settings, "GP Settings", "data/gp/setting/gpSetting.xfbin", "sub_14043FB28 / sub_14043F208", "Scenario definitions: scripts, world, characters, players, UI, files." },
        { Area_Story, "Story Board Flash", "data/ui/flash/FLASH_PLAT/hist_cmn/hist_cmn.swf", "sub_14068E778", "Story board episode/progress UI." },
        { Area_Story, "Duel Condition Flash", "data/ui/flash/FLASH_PLAT/duel_cond/duel_cond.swf", "sub_140604588", "Mission conditions, boss icons, clear ranks, bonus data." },
        { Area_ShopUnlocks, "Costume Materials", "COSTUME_MATERIAL_001..020", "sub_14050AA98 / sub_14051EDC0", "Local material progress and unlock rewards." },
        { Area_Combat, "Battle Parameter Tables", "Unknown off_141401*/off_14140* paths", "sub_1402D3BE4/sub_14033BF30", "Combat timing/events normalized from 30fps-authored values." },
        { Area_Character, "Character/Variant Tables", "Unknown off_1413B*/off_141485* paths", "sub_1404B520C/sub_1401C9CFC", "Character, costume, variant, reward, or metadata tables; needs filename xrefs." }
    };

    const ResearchAddress* GetAddressTable()
    {
        return kAddressTable;
    }

    std::size_t GetAddressCount()
    {
        return sizeof(kAddressTable) / sizeof(kAddressTable[0]);
    }

    const ResearchString* GetStringTable()
    {
        return kStringTable;
    }

    std::size_t GetStringCount()
    {
        return sizeof(kStringTable) / sizeof(kStringTable[0]);
    }

    const ResearchDatabase* GetDatabaseTable()
    {
        return kDatabaseTable;
    }

    std::size_t GetDatabaseCount()
    {
        return sizeof(kDatabaseTable) / sizeof(kDatabaseTable[0]);
    }
}
}
