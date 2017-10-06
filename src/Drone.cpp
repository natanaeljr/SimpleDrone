#include "Drone.h"
// standard
#include <Arduino.h>
// utils
#include <defines.h>
#include <debug.h>
// parts
#include <Motors.h>
#include <Scheduler.h>
// modules
#include <Console.h>
#include <PowerManager.h>
#include <SensorProcessor.h>
#include <Stabilizer.h>



void Drone_t::init() {
    // init Serial debugging system if enabled
    #if ENABLE_DEBUG
        Serial.begin(SERIAL_BAUDRATE);
        Serial << LogArg::HEADER;
        Serial.flush();
    #endif
	Info << LogType::INFO << F(">> STARTING DRONE") << endl;
    // init all modules
    #if ENABLE_DEBUG
	Console.init();
	#endif
    PowerManager.init();
	SensorProcessor.init();
	Stabilizer.init();
    // load all tasks
    #if ENABLE_DEBUG
    Scheduler.addTask(createModuleTask(CN_CHECK_INPUT_TASK, Console, &Console_t::check_input, 50)); // 20hz
	#endif
    Scheduler.addTask(createModuleTask(PM_UPDATE_BATTERY_TASK, PowerManager, &PowerManager_t::update_battery, 20)); // 50hz
    Scheduler.addTask(createModuleTask(PM_CHECK_BATTERY_TASK, PowerManager, &PowerManager_t::check_battery, 200)); // 5hz
    Scheduler.addTask(createModuleTask(PM_DEBUG_TASK, PowerManager, &PowerManager_t::debug, 1100)); // varies from 5s to 30s
	Scheduler.addTask(createModuleTask(SP_READ_MPU, SensorProcessor, &SensorProcessor_t::read_mpu, 20)); // 50hz - must match FIFO_RATE
	Scheduler.addTask(createModuleTask(SP_DEBUG_TASK, SensorProcessor, &SensorProcessor_t::debug, 50)); // 20hz
	Scheduler.addTask(createModuleTask(ST_STABILIZE_TASK, Stabilizer, &Stabilizer_t::stabilize, 20)); // 50hz
	Scheduler.addTask(createModuleTask(ST_DEBUG_TASK, Stabilizer, &Stabilizer_t::debug, 100)); // 10hz
	Scheduler.addTask(createModuleTask(MT_DEBUG_TASK, Motors, &Motors_t::debug, 100)); // 10hz
	Scheduler.addTask(createModuleTask(SH_DEBUG_TASK, Scheduler, &Scheduler_t::debug, 10000)); // 0.1hz
	// disable some tasks
	Scheduler.getTaskPS(SP_DEBUG_TASK)->enable = false;
	Scheduler.getTaskPS(ST_DEBUG_TASK)->enable = false;
	Scheduler.getTaskPS(MT_DEBUG_TASK)->enable = false;
	Scheduler.getTaskPS(SH_DEBUG_TASK)->enable = false;
	// log
    Info << LogType::INFO << F(">> READY TO FLY!") << endl;
    Debug << LogType::DEBUG << F("FREE RAM = ") << free_ram() << endl;
}

void Drone_t::run() {
	// keep executing tasks
    Scheduler.execute();
}
