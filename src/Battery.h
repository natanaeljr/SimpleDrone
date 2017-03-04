#pragma once
#define BATTERY_H

#include <Arduino.h>
#include "_settings.h"

class Battery
{
private:
	static char cont; //number of runs
	static int rawValue;
	static float voltage;
	static int level;
	static void update();

public:
	Battery();
	~Battery();
	
	static void initialize();
	static void run();
	static int getRawValue();
	static float getVoltage();
	static char getLevel();
};

