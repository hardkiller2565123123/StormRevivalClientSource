#pragma once

#include <cstdint>
#include <cstring>

namespace ScaleformValueUtil
{
    // Native NSC Scaleform argument value. The game constructs these with
    // sub_1400FEC40 and destroys them with sub_1400FECE0. Keep this layout
    // exactly 48 bytes because sub_14071F390 passes arrays of these directly
    // into Scaleform's ExternalInterface invoke path.
    struct Value48
    {
        uint64_t unknown0 = UINT64_MAX;   // +0  initialized to -1 by ctor
        uint64_t unknown8 = UINT64_MAX;   // +8  initialized to -1 by ctor
        uint64_t refObject = 0;           // +16 ref-counted Scaleform object when type has 0x40
        int type = 0;                     // +24 Scaleform value type/flags
        int padding28 = 0;                // +28 alignment/padding
        uint64_t payload = 0;             // +32 string pointer / bool / int / double payload
        uint64_t padding40 = 0;           // +40 keeps array stride at 48
    };

    static_assert(sizeof(Value48) == 48, "NSC Scaleform value must stay 48 bytes");

    // Clears a value the same way sub_1400FEC40 does, without touching any
    // ref-counted object. Use this only for fresh stack/local values.
    inline void Init(Value48& value)
    {
        std::memset(&value, 0, sizeof(value));
        value.unknown0 = UINT64_MAX;
        value.unknown8 = UINT64_MAX;
        value.refObject = 0;
        value.type = 0;
        value.payload = 0;
    }

    // Creates a string argument. Native type 6 is used by SetMessageText,
    // SetCharacter, SetLeaderIcon, support icons, and most text calls.
    inline Value48 String(const char* text)
    {
        Value48 value{};
        Init(value);
        value.type = 6;
        value.payload = reinterpret_cast<uint64_t>(text ? text : "");
        return value;
    }

    // Creates a bool argument. Native type 2 is used by SetVisible and the
    // localized/not-localized flag passed into SetMessageText.
    inline Value48 Bool(bool enabled)
    {
        Value48 value{};
        Init(value);
        value.type = 2;
        value.payload = enabled ? 1 : 0;
        return value;
    }

    // Creates a signed integer argument. Native type 3 is used by several UI
    // line/index setters and runtime character slot helpers.
    inline Value48 Int(int number)
    {
        Value48 value{};
        Init(value);
        value.type = 3;
        value.payload = static_cast<uint32_t>(number);
        return value;
    }

    // Creates a double/number argument. Native type 5 is used by fade/scaling
    // UI functions when passing floating-point values to Flash.
    inline Value48 Number(double number)
    {
        Value48 value{};
        Init(value);
        value.type = 5;
        std::memcpy(&value.payload, &number, sizeof(number));
        return value;
    }
}
