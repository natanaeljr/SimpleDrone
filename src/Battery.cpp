#include "Battery.h"

//PRIVATE
char Battery::cont = 0;
int Battery::rawValue = 0;
float Battery::voltage = 0;
int Battery::level = 0;

void Battery::update(){
	rawValue = analogRead(BATTERY_PIN);
	voltage = BATTERY_ADC_CORRECTION * ((rawValue * CPU_VOLTAGE) / 1023);
	level = (voltage - BATTERY_MIN_VOLTAGE) * (100 - 0) / (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE) + 0;
	logDebug2("Battery rawValue: ", rawValue);
}

//PUBLIC
void Battery::initialize(){}

void Battery::run(){
	update();
	cont++;
	if(cont < BATTERY_SAMPLING) return;

	cont = 0;
	logInfo2("Battery Level: ", level);
	logInfo2("Battery Voltage: ", voltage);

	if(level <= BATTERY_DEAD_LEVEL){
		logError("Battery DEAD!!!");
		logWarn2("Battery Level: ", level);
		logWarn2("Battery Voltage: ", voltage);
		return;
	}
	else if(level <= BATTERY_WARNING_LEVEL){
		logError("Battery LOW!!!");
		logWarn2("Battery Level: ", level);
		logWarn2("Battery Voltage: ", voltage);
		return;
	}
}
