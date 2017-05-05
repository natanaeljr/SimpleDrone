#pragma once
#define __SIMPLEDRONE_H__

#include "ModuleManager.h"
#include "Debuger.h"
#include "PowerManager.h"
#include "Communicator.h"
#include "SensorProcessor.h"
#include "Stabilizer.h"
#include "MotorsDriver.h"




//MODULES
extern ModuleManager 	MANAGER;
#if ENABLE_SERIALDEBUG
	extern Debuger 		DEBUGER;
#endif
extern PowerManager 	POWERMANAGER;
extern Communicator 	COMMUNICATOR;
extern SensorProcessor 	SENSORPROCESSOR;
extern Stabilizer STABILIZER;
extern MotorsDriver 	MOTORSDRIVER;


void SimpleDrone(void);

void SimpleDroneRun(void);