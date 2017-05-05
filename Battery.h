#pragma once
#define __BATTERY_H__
#include <inttypes.h>
#include <settings.h>

class Battery
{
private:
	const uint8_t pin;
	float voltage;
	uint8_t percentage;

public:
	Battery(const uint8_t _pin = BATTERY_PIN);
	uint8_t getPercentage();
	float getVoltage();
	void update();
};












