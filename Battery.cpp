#include "Battery.h"
#include <Arduino.h>
#include <inttypes.h>
#include <settings.h>



Battery::Battery(const uint8_t _pin) : pin(_pin)
{
	update();
}

uint8_t Battery::getPercentage()
{
	return percentage;
}

float Battery::getVoltage()
{
	return voltage;
}


void Battery::update()
{
	voltage = BATTERY_ADC_CORRECTION * ((analogRead(pin) * CPU_VOLTAGE) / 1023);
	percentage = constrain((100 * (voltage - BATTERY_MIN_VOLTAGE) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE)), 0, 100);
}