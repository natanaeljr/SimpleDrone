#include "PowerManager.h"
#include <functions.h>
#include <defines.h>
#include <enums.h>
#include <avr/sleep.h>



_PowerManager::_PowerManager(unsigned long _interval) : Module(_interval) {
	moduleName = F("PowerManager ");
}

void _PowerManager::init() {
	Module::init();
	for(int i = 0; i < 1000 / interval; i++){
		updateBattery();
		delay(5);
	}
	updateStatus();
}

void _PowerManager::run() {
	updateBattery(); // voltage and percetage reading
	updateStatus(); // check if level changed
	runned(); // update Thread stuff
}

void _PowerManager::updateBattery() {
	// read the instantaneous voltage
	float nowVoltage = ((analogRead(BATTERY_PIN) * CPU_VOLTAGE) / 1023) * BATTERY_CORRECTION;
	// applay the filter for noise reduction
	battery.voltage = battery.voltage * (1 - interval / 1000) + nowVoltage * (interval / 1000);
	// cast for percentage - formula from function map()
	battery.percentage = (battery.voltage - BATTERY_VOLT_MIN) * 100 / (BATTERY_VOLT_MAX - BATTERY_VOLT_MIN);
	// contrain the percentage to between 0% and 100%
	battery.percentage = constrain(battery.percentage, 0, 100);
}

void _PowerManager::updateStatus() {
	if(battery.percentage <= 5){
		battery.status = BattLevels::DEAD;
		logError("BATTERY DEAD! Shutting down!");
		Serial.flush();
		delay(1000);
		shutdown();
	}
	else if(battery.percentage <= 15){
		battery.status = BattLevels::CRITICAL;
	}
	else if(battery.percentage <= 30){
		battery.status = BattLevels::LLOW;
	}
	else{
		battery.status = BattLevels::NORMAL;
	}
}

void _PowerManager::shutdown(){
	// put IMU to sleep
	// SensorProcessor.sleep();
	// Wire.end();
	
	// put wifi to sleep
	// Communicator.sleep();
	 
	// put arduino to sleep
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	while(true)
		sleep_mode();
}

Battery _PowerManager::getBattery(){
	return battery;
}