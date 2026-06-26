#pragma once

namespace StormRevival::OnlineMenu::Lobby
{
    /*
        Confirmed main UI sync function:

        sub_140674688(
            uiObject,
            roomData,
            slotOrder,
            selectedSlot,
            throttledUpdate
        )

        Meaning:
        - Updates CallsetOnUser
        - Updates setNum
        - Updates setWinStreak
        - Updates setHostNo
        - Updates setFriend
        - Updates setWave
        - Updates setVoice
        - Updates CallsetRoomInfoIconHost
        - Updates CallsetHost
        - Updates setUser
        - Updates CallsetLockOk / CallsetUnLockOk

        Confirmed full fallback slot loop:

        sub_140674E74(uiObject, roomData, selectedSlot)
    */
    struct LobbySyncMap
    {
        static constexpr const char* MainSync = "sub_140674688";
        static constexpr const char* FullSlotSync = "sub_140674E74";
        static constexpr const char* SetFriend = "sub_140674CD4";
        static constexpr const char* SetWave = "sub_14067518C";
        static constexpr const char* SetVoice = "sub_14067501C";
        static constexpr const char* SetHost = "sub_140675364";
        static constexpr const char* SetHostNo = "sub_140673D98";
        static constexpr const char* SetWinStreak = "sub_140673D18";
        static constexpr const char* SetUser = "sub_140675494";
    };
}
