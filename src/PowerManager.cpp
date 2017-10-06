#include "PowerManager.h"
// standard
#include <Arduino.h>
#include <stdint.h>
#include <avr/sleep.h>
// utils
#include <defines.h>
#include <debug.h>
#include <functions.h>
#include <Scheduler.h>

static const uint16_t LEVELCHANGE_TIME = 1000;


PowerManager_t::PowerManager_t() : Module_t(PSTR("PowerManager")) {}


void PowerManager_t::init() {
    if(isInit) return;
    Debug << LogType::DEBUG << castF(name) << F(" init") << endl;
    for(uint8_t i = 0; i++ < 50; delay(1)){
        update_battery();
    }
    check_battery();
    isInit = true;
}


void PowerManager_t::update_battery() {
    // read the instantaneous voltage
	uint16_t nowVoltage = ((analogRead(BATTERY_PIN) * CPU_VOLTAGE) / 1023) * BATTERY_CORRECTION;
	// applay the filter for noise reduction
	Battery.voltage = Battery.voltage * 0.9 + nowVoltage * 0.1; //ARRUMAR COM PERIODO
    // constrain to between MIN and MAX in order to avoid bugs
    Battery.voltage = constrainf(Battery.voltage, (uint16_t) BATTERY_VOLT_MIN, (uint16_t) BATTERY_VOLT_MAX);
	// cast for percentage - formula from function map()
	Battery.percentage = (Battery.voltage - BATTERY_VOLT_MIN) * 100 / (BATTERY_VOLT_MAX - BATTERY_VOLT_MIN);
	// contrain the percentage to between 0% and 100%
	Battery.percentage = constrainf(Battery.percentage, (uint8_t) 0, (uint8_t) 100);
}


void PowerManager_t::check_battery() {
    // update and check the battery level state
    static _BattLevels nowLevel = Battery.level;
    if(Battery.percentage <= (uint8_t)_BattLevels::DEAD){
        if(Battery.level != _BattLevels::DEAD)
            nowLevel = _BattLevels::DEAD;
        else {
            Error << LogType::ERROR << F("BATTERY DEAD! Shutting Off!") << endl;
            #if ENABLE_DEBUG
                Serial.flush();
            #endif
            // TURN ON LED RED
            delay(1000);
            //shutdown();
        }
    }
	else if(Battery.percentage <= (uint8_t)_BattLevels::CRITICAL)
        nowLevel = _BattLevels::CRITICAL;
    else if(Battery.percentage <= (uint8_t)_BattLevels::LOWW)
        nowLevel = _BattLevels::LOWW;
    else // Battery.percentage > 30)
        nowLevel = _BattLevels::NORMAL;


    static uint32_t elapsed_time = 0;
    if(nowLevel != Battery.level){
        if(millis() - elapsed_time > LEVELCHANGE_TIME){
            Battery.level = nowLevel;
            debug();
        }
    }
    else elapsed_time = millis();
}


void PowerManager_t::debug(){
    #if ENABLE_DEBUG
        if(Battery.level == _BattLevels::NORMAL){
            Info << LogType::INFO << F("BATTERY = ") << battlevelToPrint(Battery.level)
                 << F(" | ") << Battery.voltage << F("v | ") << Battery.percentage << F("%") << endl;
			Scheduler.getTaskPS(PM_DEBUG_TASK)->period = 30000;
        }
        else if(Battery.level == _BattLevels::LOWW){
            Warn << LogType::WARN << F("BATTERY = ") << battlevelToPrint(Battery.level)
                 << F(" | ") << Battery.voltage << F("v | ") << Battery.percentage << F("%") << endl;
            Scheduler.getTaskPS(PM_DEBUG_TASK)->period = 10000;
        }
        else if(Battery.level == _BattLevels::CRITICAL){
            Error << LogType::ERROR << F("BATTERY = ") << battlevelToPrint(Battery.level)
                  << F(" | ") << Battery.voltage << F("v | ") << Battery.percentage << F("%") << endl;
            Scheduler.getTaskPS(PM_DEBUG_TASK)->period = 5000;
        }
    #endif
}


void PowerManager_t::shutdown() {
    // put IMU to sleep
	// SensorProcessor.sleep();
	// Wire.end();

	// put WIFI to sleep
	// Communicator.sleep();

	// put CPU to sleep
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();
	while(true)
		sleep_mode();
}


PowerManager_t PowerManager = PowerManager_t();
