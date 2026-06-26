#pragma once

#include <cstddef>
#include <cstdint>

namespace StormRevival
{
namespace Research
{
    enum ResearchArea
    {
        Area_OnlineMenu,
        Area_FreeBattle,
        Area_Story,
        Area_Settings,
        Area_ShopUnlocks,
        Area_Stage,
        Area_Character,
        Area_Combat,
        Area_ResourceDatabase,
        Area_Lobby,
        Area_ProfileLeaderboard
    };

    struct ResearchAddress
    {
        ResearchArea Area;
        const char* Name;
        std::uintptr_t Address;
        const char* Meaning;
        const char* Notes;
    };

    struct ResearchString
    {
        ResearchArea Area;
        const char* Text;
        const char* Meaning;
    };

    struct ResearchDatabase
    {
        ResearchArea Area;
        const char* Name;
        const char* FilePath;
        const char* LoaderFunction;
        const char* Notes;
    };

    const char* AreaName(ResearchArea area);

    const ResearchAddress* GetAddressTable();
    std::size_t GetAddressCount();

    const ResearchString* GetStringTable();
    std::size_t GetStringCount();

    const ResearchDatabase* GetDatabaseTable();
    std::size_t GetDatabaseCount();
}
}
