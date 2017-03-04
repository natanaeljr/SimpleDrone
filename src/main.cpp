//INCLUDES
#include <Arduino.h>
#include "_settings.h"
#include "_types.h"
#include "Thread.h"
#include "ThreadController.h"
#include "Battery.h"
#include "SerialDebug.h"
#include "Motors.h"

//OBJECTS
ThreadController _cpu;
Thread _battery;
Thread _serialDebug;
Thread _motors;

//GLOBAL VARS


//SETUP
void setup(){
	_battery.setInterval(BATTERY_RUN_INTERVAL);
	_battery.onRun(Battery::run);
	_serialDebug.setInterval(SERIALDEBUG_RUN_INTERVAL);
	_serialDebug.onRun(SerialDebug::run);
	_motors.setInterval(MOTORS_RUN_INTERVAL);
	_motors.onRun(Motors::run);

	_cpu.add(&_battery);
	_cpu.add(&_serialDebug);
	_cpu.add(&_motors);

	Battery::initialize();
	SerialDebug::initialize();
	Motors::initialize();
}

//LOOP
void loop(){
	_cpu.run();
}
