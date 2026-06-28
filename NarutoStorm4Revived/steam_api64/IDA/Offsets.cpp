#include <windows.h>
#include <vector>
#include <cstdint>
#include "Offsets.h"

// Безопасное чтение uintptr_t (защищено от AV)
bool Offset::SafeReadPtr(uintptr_t addr, uintptr_t& out)
{
    if (addr == 0) return false;
    __try {
        out = *reinterpret_cast<uintptr_t*>(addr);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

// Безопасное чтение float
bool Offset::SafeReadFloat(uintptr_t addr, float& out)
{
    if (addr == 0) return false;
    __try {
        out = *reinterpret_cast<float*>(addr);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

// Безопасная запись float
bool Offset::SafeWriteFloat(uintptr_t addr, float value)
{
    if (addr == 0) return false;
    __try {
        *reinterpret_cast<float*>(addr) = value;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

// Попытка разрешить цепочку в одном порядке.
// Возвращает pair(lastAddr, cur) где:
//  lastAddr = адрес последнего вычисленного указателя (cur 읽기 происходил по lastAddr),
//  cur = значение, прочитанное из lastAddr (может быть указателем на данные).
bool Offset::TryResolveOrder(uintptr_t moduleBase, uintptr_t baseOffset, const std::vector<uint32_t>& offsets, uintptr_t& outLastAddr, uintptr_t& outCur)
{
    if (moduleBase == 0) return false;

    uintptr_t startAddr = moduleBase - 0xC00 + baseOffset; // ваша схема
    uintptr_t curValue = 0;
    if (!Offset::SafeReadPtr(startAddr, curValue)) return false;

    // Для каждого шага: nextAddr = curValue + offsets[i]; затем curValue = *(uintptr_t*)nextAddr
    for (size_t i = 0; i < offsets.size(); ++i)
    {
        uintptr_t nextAddr = curValue + static_cast<uintptr_t>(offsets[i]);
        uintptr_t nextVal = 0;
        if (!Offset::SafeReadPtr(nextAddr, nextVal)) return false;
        curValue = nextVal;
        // продолжаем
    }

    // outLastAddr - адрес последнего места, откуда мы прочитали curValue:
    // вычисим его как (curValue_before_last + lastOffset). Но проще: повторим шаги, чтобы получить lastAddr:
    // (минимальный накладной — но безопасно)
    uintptr_t verify = 0;
    if (!Offset::SafeReadPtr(startAddr, verify)) return false;
    uintptr_t lastAddr = 0;
    for (size_t i = 0; i < offsets.size(); ++i)
    {
        lastAddr = verify + static_cast<uintptr_t>(offsets[i]);
        if (!SafeReadPtr(lastAddr, verify)) return false;
    }

    outLastAddr = lastAddr;
    outCur = curValue;
    return true;
}

// Основная функция: пробует обычный порядок, если не удаётся — обратный.
// Возвращает адрес блока float (адрес, по которому реально лежит первый float).
// Логика выбора:
//  - если outCur (значение, прочитанное из lastAddr) выглядит как валидный адрес float'ов -> возвращаем outCur
//  - иначе если lastAddr прям содержит float (т.е. чтение float по lastAddr успешно) -> возвращаем lastAddr
//  - иначе возвращаем 0
uintptr_t Offset::ResolvePointerChainBase(uintptr_t moduleBase, uintptr_t baseOffset, const std::vector<uint32_t>& offsets)
{
    uintptr_t lastAddr = 0, cur = 0;
    if (!Offset::TryResolveOrder(moduleBase, baseOffset, offsets, lastAddr, cur))
    {
        // попробовать в обратном порядке
        std::vector<uint32_t> rev = offsets;
        std::reverse(rev.begin(), rev.end());
        if (!Offset::TryResolveOrder(moduleBase, baseOffset, rev, lastAddr, cur))
            return 0;
    }

    // Проверить cur как возможную базу float'ов
    float tmp0 = 0.0f, tmp10 = 0.0f;
    bool curOk = Offset::SafeReadFloat(cur + 0 * sizeof(float), tmp0) && Offset::SafeReadFloat(cur + 10 * sizeof(float), tmp10);
    if (curOk) return cur;

    // Иначе проверить lastAddr прямо как база float'ов
    bool lastOk = Offset::SafeReadFloat(lastAddr + 0 * sizeof(float), tmp0) && Offset::SafeReadFloat(lastAddr + 10 * sizeof(float), tmp10);
    if (lastOk) return lastAddr;

    return 0;
}
bool Offset::WriteFloatAtIndexSafe(uintptr_t baseAddr, size_t index, float value)
{
    if (baseAddr == 0) return false;
    return Offset::SafeWriteFloat(baseAddr + index * sizeof(float), value);
}

namespace offsetSC
{
    const uintptr_t stageOffset = 0x14218F7C0; //get that id from kaguya's screen stage switch effect
    const uintptr_t VTableXmmwordOffset = 0x22FB990; //get that from kaguya's screen stage switch effect v7 = (__int64)sub_141086E40(*((__int64 *)&xmmword_1422FB990 + 1), (__int64)"StageMove");
    const uintptr_t bgmOffset = 0x14218F000; //find ccAdvPlayStageBgm 
    const uintptr_t OFFSET_TEAM_ULT_ARRAY = 0x18B2470; // can be found in any pairSpSkillCombinationParam function, its array of TUJs. Look for "2nrt3ssk" string to find it
    const int ORIGINAL_COUNT_TEAM_ULT_ARRAY = 55; // count of entries from offset which contain TUJ names
    const uintptr_t OFF_STRINGS_ARRAY = 0x201E930;  //Address for PL_ANM entries, list off_14201E930 1.60  dq offset aPlAnmDwnlp
    const uintptr_t OFF_BGMARRAY = 0x200A5E0; //Address for BGM entries, unk_14200A5E0 1.60 (literally start of array)
    const uintptr_t OFF_PROJECTILEARRAY = 0x201A790;
    const uintptr_t OFF_CHARRELATIONARRAY = 0x185DC20;
    const uintptr_t OFF_SCENEARRAY = 0x1FE9290;
};
namespace offsetS4
{
    const uintptr_t stageOffset = 0x141611A88; //get that id from kaguya's screen stage switch effect dword_141611A88
    const uintptr_t VTableXmmwordOffset = 0x16BDA20; //get that from kaguya's screen stage switch effect v7 = (__int64)sub_141086E40(*((__int64 *)&xmmword_1416BDA20 + 1), (__int64)"StageMove");
    const uintptr_t bgmOffset = 0x141610160; //find ccAdvPlayStageBgm  qword_141610160
    const uintptr_t OFFSET_TEAM_ULT_ARRAY = 0x105EF30; // can be found in any pairSpSkillCombinationParam function, its array of TUJs. Look for "2nrt3ssk" string to find it
    const int ORIGINAL_COUNT_TEAM_ULT_ARRAY = 47; // count of entries from offset which contain TUJ names
    //const uintptr_t OFF_STRINGS_ARRAY = 0x201E930;  //Address for PL_ANM entries, list off_14201E930 1.60  dq offset aPlAnmDwnlp
    const uintptr_t OFF_BGMARRAY = 0x1527EA0; //Address for BGM entries, unk_141527EA0 1.09 (literally start of array)
    const uintptr_t OFF_PROJECTILEARRAY = 0x153D130;
    const uintptr_t OFF_CHARRELATIONARRAY = 0x185DC20;
    const uintptr_t OFF_SCENEARRAY = 0x14F9300;
};