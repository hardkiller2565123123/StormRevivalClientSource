#include <windows.h>
#include <cstdint>
#include <cstring>
#include "Common.h"
#include "Offsets.h"
#include "PatternScan.h"
#include <iostream>
#include <cstdio>
#include <Psapi.h>
#include "mem.h"
#include <sstream>
#include <iomanip>
#include "SpecialInteractionManager.h"
#include "FileParser.h"
#include "Console.h"
#include "Utilities.h"
using namespace std;



__int64 SpecialInteractionManager::sub_140AC49A0Adress = 0;
// Assume this structure and global list exist and are filled by ReadSpecialInteractionParam:
struct SpecialInteractionFramework {
    int mainCharacter;
    std::vector<int> triggerList;  //  std::vector<int>   int[30]
};



namespace specialInteraction {
    std::vector<SpecialInteractionFramework*> specialInteractionList;
}


void SpecialInteractionManager::ReadSpecialInteractionParam(std::string _file)
{
    std::vector<BYTE> fileBytes = FileParser::ReadAllBytes(_file);
    size_t pos = 0;
    size_t fileSize = fileBytes.size();

    // Verify that file contains at least 4 bytes for the total entry count.
    if (fileSize < 4)
    {
        Console::PrintErr("SpecialInteractionManager :: Error: File too small: %s\n", _file.c_str());
        return;
    }

    // Read total entry count.
    int totalEntryCount = *reinterpret_cast<int*>(&fileBytes[pos]);
    pos += 4;
    Console::PrintOut("SpecialInteractionManager :: Total amount of entries in file: %d\n", totalEntryCount);

    // Process each entry.
    for (int entryIndex = 0; entryIndex < totalEntryCount; entryIndex++)
    {
        // Ensure there are at least 8 bytes for mainCharacter and triggerCount.
        if (pos + 8 > fileSize)
        {
            Console::PrintErr("SpecialInteractionManager :: Error: Not enough data for entry %d in file %s\n", entryIndex, _file.c_str());
            break;
        }

        // Read main character ID.
        int mainCharacter = *reinterpret_cast<int*>(&fileBytes[pos]);
        pos += 4;

        // Read trigger count.
        int triggerCount = *reinterpret_cast<int*>(&fileBytes[pos]);
        pos += 4;

        if (triggerCount < 0 || pos + triggerCount * 4 > fileSize)
        {
            Console::PrintErr("SpecialInteractionManager :: Error: Invalid trigger count (%d) for entry %d at pos %zu in file %s\n",
                triggerCount, entryIndex, pos, _file.c_str());
            break;
        }

        if (mainCharacter == 0)
        {
            Console::PrintErr("SpecialInteractionManager :: Error: Main character ID is 0 for entry %d at pos %zu.\n", entryIndex, pos);
            pos += triggerCount * 4;
            continue;
        }

        // Create a new entry.
        SpecialInteractionFramework* newEntry = new SpecialInteractionFramework();
        newEntry->mainCharacter = mainCharacter;
        newEntry->triggerList.reserve(triggerCount);
        for (int i = 0; i < triggerCount; i++)
        {
            int triggerID = *reinterpret_cast<int*>(&fileBytes[pos + i * 4]);
            if (triggerID != 0)
                newEntry->triggerList.push_back(triggerID);
        }
        pos += triggerCount * 4;

        // Store the new entry.
        specialInteraction::specialInteractionList.push_back(newEntry);

        // Log the loaded entry.
        Console::PrintOut("SpecialInteraction Entry %d loaded: { mainCharacter = 0x%X, count = %d, triggers = ",
            entryIndex, mainCharacter, triggerCount);
        for (int trigger : newEntry->triggerList)
        {
            Console::PrintOutW("0x%X ", trigger);
        }
        Console::PrintOut("}\n");

    }

    Console::PrintOut("SpecialInteractionManager :: Total amount of entries: %d\n", specialInteraction::specialInteractionList.size());
}





bool __fastcall SpecialInteractionManager::SpecialInteractionSoundFunction(__int64 a1) // sub_140A15A00
{
    int charClass_offset = 0;
    int ultID_offset = 0;
    bool awakened = 0;
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
    {
        charClass_offset = 0xE64;
        ultID_offset = 0xE80;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1));
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
    {
        charClass_offset = 0xC8C;
        ultID_offset = 0xC9C;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1));
    }

    int mainCharId = *(int*)(a1 + charClass_offset);
    bool triggered = false;
    int mode = *(unsigned int*)(a1 + ultID_offset);

    // Look up a special interaction entry for the current main character.
    SpecialInteractionFramework* entry = nullptr;
    for (auto* e : specialInteraction::specialInteractionList)
    {
        if (e->mainCharacter == mainCharId)
        {
            entry = e;
            break;
        }
    }

    if (entry)
    {
        // Get enemy character ID from sub_1409BB1B0.
        int enemyId = 0;
        __int64 enemyPtr = BattleUtils::GetEnemyPointer(a1);
        if (enemyPtr)
            enemyId = *(int*)(enemyPtr + charClass_offset);

        // Check if enemyId is in the trigger list for this entry (using dynamic iteration).
        for (int trigger : entry->triggerList)
        {
            if (trigger != 0 && trigger == enemyId)
            {
                triggered = true;
                break;
            }
        }
    }
    else if (awakened) {
        triggered = true;
    }
    else
    {
        // Fallback to original behavior if no special interaction entry is found.
        switch (mainCharId)
        {
        case 36:
        case 51:
        {
            int enemyId = 0;
            __int64 enemyPtr = BattleUtils::GetEnemyPointer(a1);
            if (enemyPtr)
                enemyId = *(int*)(enemyPtr + charClass_offset);
            if (mainCharId == 36)
            {
                if ((unsigned int)SpecialInteractionManager::SpecialInteractionKarin(a1, enemyId))
                    triggered = true;
            }
            else if (SpecialInteractionManager::SpecialInteractionHinata(a1, enemyId))
            {
                triggered = true;
            }
        }
        break;
        case 1:
        case 3:
            if (mode == 1)
                triggered = true;
            break;
        case 56:
            triggered = (mode == 1);
            break;
        default:
            break;
        }
    }
    return triggered;
}




__int64 __fastcall SpecialInteractionManager::SpecialInteractionUJChanger(__int64 a1, unsigned int a2, __int64 a3)
{
    int charClass_offset = 0;
    int ultID_offset = 0;
    bool awakened = 0;
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
    {
        charClass_offset = 0xE64;
        ultID_offset = 0xE80;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1));
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
    {
        charClass_offset = 0xC8C;
        ultID_offset = 0xC9C;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1));
    }

    //cout << "SpecialInteractionManager :: Entries Hooked!" << endl;
    int mainChar = *(int*)(a1 + charClass_offset);
    int enemyChar = 0;
    int flag = (int)a3;
    unsigned int ultID = a2;
    __int64 fallbackResult = 0;




    // Initial conditions (recursive call, etc.)
    if ((mainChar != 16 && mainChar != 227) || a2 != 224 ||
        *(__int64*)(a1 + 0x1248) == 0 ||
        (fallbackResult = SpecialInteractionManager::SpecialInteractionUJChanger(*(__int64*)(a1 + 0x1248), a2, a3)) == 0)
    {
        // If flag is zero, leave ultID unchanged.
        if (!flag)
        {
            __int64 handler = *(__int64*)(a1 + 520);
            return (handler) ? SpecialInteractionManager::sub_1405F0060(handler, ultID) : fallbackResult;
        }

        unsigned int newID = ultID;
        if (ultID - 700 <= 0xD0)
        {
            //Console::PrintErr("charClass_offset: 0x%X\n", charClass_offset);
            //Console::PrintErr("ultID_offset: 0x%X\n", ultID_offset);
            int mode = *(unsigned int*)(a1 + ultID_offset);
            if (mode == 1)
                newID = ultID + 84;
            else if (mode == 2)
                newID = ultID + 126;
            else if (mode == 3)
                newID = ultID + 168;

            //Console::PrintErr("Characode ID: 0x%X\n", mainChar);
            //Console::PrintErr("PL_ANM_ID: 0x%X\n", newID);
            //Console::PrintErr("Ultimate ID: 0x%X\n", mode);
            // --- Special Interaction File Override ---
            int currentMain = *(int*)(a1 + charClass_offset);
            SpecialInteractionFramework* entry = nullptr;
            // Look up a file entry for the current main character.
            for (auto* e : specialInteraction::specialInteractionList)
            {
                if (e->mainCharacter == currentMain)
                {
                    entry = e;
                    break;
                }
            }
            if (entry)
            {
                __int64 enemyPtr = BattleUtils::GetEnemyPointer(a1);
                if (enemyPtr)
                    enemyChar = *(int*)(enemyPtr + charClass_offset);
                bool fileTriggered = false;
                for (int trigger : entry->triggerList)
                {
                    if (trigger != 0 && trigger == enemyChar)
                    {
                        fileTriggered = true;
                        break;
                    }
                }
                if (fileTriggered)
                    newID = ultID + 42;
                //Console::PrintErr("Enemy ID: 0x%X\n", enemyChar);
            }
            else if (awakened == 1)
                newID = ultID + 42;
            else
            {
                // --- Vanilla logic fallback (if no file entry exists) ---
                int v12 = *(int*)(a1 + charClass_offset);
                unsigned int diff = v12 - 36;
                const __int64 mask = 0x100000000008001i64;
                if ((diff <= 0x38 && _bittest64(&mask, diff)) || v12 == 108)
                {
                    __int64 enemyPtr2 = BattleUtils::GetEnemyPointer(a1);
                    if (enemyPtr2)
                        enemyChar = *(int*)(enemyPtr2 + charClass_offset);
                    switch (v12)
                    {
                    case 36:
                        switch (enemyChar)
                        {
                        case 3:
                        case 4:
                        case 56:
                        case 85:
                        case 126:
                        case 130:
                        case 191:
                        case 193:
                        case 201:
                        case 241:
                            newID = ultID + 42;
                            break;
                        default:
                            break;
                        }
                        break;
                    case 51:
                        if (enemyChar == 46)
                            newID = ultID + 42;
                        break;
                    case 92:
                        if (enemyChar <= 268)
                        {
                            if (enemyChar != 268)
                            {
                                switch (enemyChar)
                                {
                                case 6:
                                case 7:
                                case 11:
                                case 12:
                                case 16:
                                case 18:
                                case 19:
                                case 20:
                                case 21:
                                case 29:
                                case 40:
                                case 53:
                                case 60:
                                case 67:
                                case 80:
                                case 83:
                                case 87:
                                case 91:
                                case 92:
                                case 93:
                                case 196:
                                case 198:
                                case 222:
                                case 223:
                                case 225:
                                case 227:
                                    newID = ultID + 42;
                                    break;
                                default:
                                    break;
                                }
                            }
                            else
                            {
                                newID = ultID + 42;
                            }
                        }
                        break;
                    case 108:
                        if (((enemyChar - 45) & 0xFFFFFFBF) == 0)
                            newID = ultID + 42;
                        break;
                    default:
                        break;
                    }
                }
            }
            ultID = newID;
        }
        __int64 handler = *(__int64*)(a1 + 520);
        return (handler) ? SpecialInteractionManager::sub_1405F0060(handler, ultID) : fallbackResult;
    }
    return fallbackResult;
}

__int64 __fastcall SpecialInteractionManager::AdjustSpecialInteractionValue(__int64 a1, unsigned int a2)
{
    unsigned int adjustedValue = a2;
    // Adjust a2 based on mode from sub_140981F60

    int charClass_offset = 0;
    int ultID_offset = 0;
    bool awakened = 0;
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
    {
        charClass_offset = 0xE64;
        ultID_offset = 0xE80;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1));
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
    {
        charClass_offset = 0xC8C;
        ultID_offset = 0xC9C;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1));
    }



    if (a2 - 700 <= 0xD0) {
        int mode = *(unsigned int*)(a1 + ultID_offset);
        if (mode == 1) adjustedValue += 84;
        if (mode == 2) adjustedValue += 126;
        if (mode == 3) adjustedValue += 168;

        int mainCharId = *(int*)(a1 + charClass_offset);

        // Find special interaction entry
        SpecialInteractionFramework* entry = nullptr;
        for (auto* e : specialInteraction::specialInteractionList)
        {
            if (e->mainCharacter == mainCharId)
            {
                entry = e;
                break;
            }
        }

        __int64 enemyPtr = BattleUtils::GetEnemyPointer(a1);
        int enemyId = enemyPtr ? *(int*)(enemyPtr + charClass_offset) : 0;

        if (entry)
        {
            if (a2 >= 700 && a2 <= 916) {
                // If an entry exists, check the trigger list for adjustments
                for (int trigger : entry->triggerList)
                {
                    if (trigger == enemyId)
                        return a2 + 42;
                }
                
            }

        }
        else if (awakened == 1)
            return a2 + 42;
        else
        {
            // Fallback to vanilla logic
            if (a2 >= 700 && a2 <= 916)
            {
                if (mainCharId == 36)
                {
                    switch (enemyId)
                    {
                    case 3: case 4: case 56: case 85: case 126: case 130:
                    case 191: case 193: case 201: case 241:
                        return a2 + 42;
                    }
                }
                else if (mainCharId == 51)
                {
                    if (enemyId == 46 || enemyId == 194)
                        return a2 + 42;
                }
                else if (mainCharId == 92)
                {
                    if (enemyId == 268 || enemyId == 272)
                        return a2 + 42;

                    switch (enemyId)
                    {
                    case 6: case 7: case 11: case 12: case 16: case 18: case 19: case 20: case 21:
                    case 29: case 40: case 53: case 60: case 67: case 80: case 83: case 87: case 91:
                    case 92: case 93: case 196: case 198: case 222: case 223: case 225: case 227:
                        return a2 + 42;
                    }
                }
                else if (mainCharId == 108)
                {
                    if (enemyId == 45 || enemyId == 107)
                        return a2 + 42;
                }
            }
        }
    }


    return adjustedValue;
}





__int64 __fastcall SpecialInteractionManager::SpecialInteractionFunction2(__int64 a1)
{
    int charClass_offset = 0;
    int ultID_offset = 0;
    bool awakened = 0;
    if (GameVersion && std::strcmp(GameVersion, "1.60") == 0) //Naruto Storm Connections
    {
        charClass_offset = 0xE64;
        ultID_offset = 0xE80;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x1260i64))(a1));
    }
    else if (GameVersion && std::strcmp(GameVersion, "1.09") == 0) //Naruto 4
    {
        charClass_offset = 0xC8C;
        ultID_offset = 0xC9C;
        awakened = ((*(unsigned int(__fastcall**)(__int64))(*(__int64*)a1 + 0x11B8i64))(a1));
    }

    bool triggered = false;
    __int64 enemyPtr = BattleUtils::GetEnemyPointer(a1);

    if (enemyPtr)
    {
        int enemyId = *(int*)(enemyPtr + charClass_offset);
        int mainCharId = *(int*)(a1 + charClass_offset);

        // Look up a special interaction entry for the current main character.
        SpecialInteractionFramework* entry = nullptr;
        for (auto* e : specialInteraction::specialInteractionList)
        {
            if (e->mainCharacter == mainCharId)
            {
                entry = e;
                break;
            }
        }

        // If a special interaction entry exists, check the trigger list
        if (entry)
        {
            for (int trigger : entry->triggerList)
            {
                if (trigger != 0 && trigger == enemyId)
                {
                    triggered = true;
                    break;
                }
            }
        }
        else if (awakened == 1)
            triggered = true;
        else
        {
            // Fallback logic if no special interaction entry is found
            switch (mainCharId)
            {
            case 36:
                triggered = SpecialInteractionManager::SpecialInteractionKarin(a1, enemyId);
                break;
            case 51:
                if (SpecialInteractionManager::SpecialInteractionHinata(a1, enemyId))
                    return 1;
                break;
            case 92:
                if (SpecialInteractionManager::SpecialInteractionKonohamaru(a1, enemyId))
                    return 1;
                break;
            case 108:
                if (SpecialInteractionManager::SpecialInteractionKushina(a1, enemyId))
                    return 1;
                break;
            default:
                break;
            }
        }
    }
    return triggered;
}
__int64 __fastcall SpecialInteractionManager::SpecialInteractionKarin(__int64 a1, int a2) // Karin and Sasuke
{
    unsigned int v2; // r8d

    v2 = 0;
    switch (a2)
    {
    case 3:
    case 4:
    case 56:
    case 85:
    case 126:
    case 130:
    case 191:
    case 193:
    case 201:
    case 241:
        v2 = 1;
        break;
    default:
        return v2;
    }
    return v2;
}
__int64 __fastcall SpecialInteractionManager::sub_1405F0060(__int64 a1, unsigned int a2)
{
    __int64 v2; // r8
    v2 = *(__int64*)(a1 + 12808);
    if (v2 && a2 < 0x3F1)
        return *(__int64*)(v2 + 8i64 * a2);
    else
        return 0i64;
}

bool __fastcall SpecialInteractionManager::SpecialInteractionHinata(__int64 a1, int a2) // Hinata and Naruto
{
    return a2 == 46 || a2 == 194;
}
__int64 __fastcall SpecialInteractionManager::SpecialInteractionKonohamaru(__int64 a1, int a2)
{
    unsigned int v2; // r8d

    v2 = 0;
    if (a2 > 268)
    {
        if (a2 != 272)
            return v2;
        return 1;
    }
    if (a2 == 268)
        return 1;
    switch (a2)
    {
    case 6:
    case 7:
    case 11:
    case 12:
    case 16:
    case 18:
    case 19:
    case 20:
    case 21:
    case 29:
    case 40:
    case 53:
    case 60:
    case 67:
    case 80:
    case 83:
    case 87:
    case 91:
    case 92:
    case 93:
    case 196:
    case 198:
    case 222:
    case 223:
    case 225:
    case 227:
        return 1;
    default:
        return v2;
    }
    return v2;
}

bool __fastcall SpecialInteractionManager::SpecialInteractionKushina(__int64 a1, int a2)
{
    return ((a2 - 45) & 0xFFFFFFBF) == 0;
}


