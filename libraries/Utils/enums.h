#pragma once
#define __ENUMS_H__
#include <inttypes.h>


/****************************************************************************************
 * BATTERY
*****************************************************************************************/
enum class BattLevels : uint8_t
{
	DEAD = 5,
	CRITICAL = 15,
	LLOW = 30, // prepend L because of conflicts with LOW from Arduino.h
	NORMAL
};