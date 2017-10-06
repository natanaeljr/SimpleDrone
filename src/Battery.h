#ifndef __BATTERY_H__
#define __BATTERY_H__
#include <Arduino.h>
#include <stdint.h>


enum class _BattLevels : uint8_t {
    DEAD     = 5,
    CRITICAL = 15,
    LOWW     = 30, // LOWW because LOW conflicts with LOW defined in "Arduino.h"
    NORMAL,
    FULL     = 100
};


struct Battery_t {
    uint16_t voltage    = 0; // voltage x 100 (e.g. 4.2v x 100 = 420)
    uint8_t percentage  = 0; // 0 - 100
    _BattLevels level   = _BattLevels::NORMAL;
};


__FlashStringHelper* battlevelToPrint(_BattLevels battlevel);




#endif /* end of include guard: __BATTERY_H__ */
