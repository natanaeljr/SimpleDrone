#include "Battery.h"
#include <Arduino.h>
#include <functions.h>


__FlashStringHelper* battlevelToPrint(_BattLevels battlevel) {
    if(battlevel == _BattLevels::DEAD)
        return castF(PSTR("DEAD"));
    else
	if(battlevel == _BattLevels::CRITICAL)
        return castF(PSTR("CRITICAL"));
    else
	if(battlevel == _BattLevels::LOWW)
        return castF(PSTR("LOW"));
    else
	if(battlevel == _BattLevels::NORMAL)
        return castF(PSTR("NORMAL"));
    else
        return castF(PSTR("FULL"));
}
