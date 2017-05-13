#include "SimpleDrone.h"
#include <functions.h>
//MODULES
#include <ModuleManager.h>
#include <Debuger.h>
#include <PowerManager.h>
#include <Communicator.h>
#include <SensorProcessor.h>
#include <Stabilizer.h>
#include <MotorsDriver.h>


//Instatiate MODULES (thread interval)
ModuleManager 	_moduleManager	(0);
#if ENABLE_SERIALDEBUG
	Debuger 	_debuger		(50);
#endif
PowerManager 	_powerManager	(100); // 10Hz
Communicator 	_communicator	(1000);
SensorProcessor _sensorprocessor(2);  // 500Hz
Stabilizer 		_stabilizer		(10); // 250Hz
MotorsDriver 	_motorsdriver	(10); // 250Hz




// Add Modules to ModuleManager, setup and initialize them
void SimpleDrone(void)
{	
	_communicator.enabled = false;

	#if ENABLE_SERIALDEBUG
		_moduleManager.add(&_debuger);
	#endif
	_moduleManager.add(&_powerManager);
	_moduleManager.add(&_communicator);
	_moduleManager.add(&_sensorprocessor);
	_moduleManager.add(&_stabilizer);
	_moduleManager.add(&_motorsdriver);

	logDebug(F("> SETUP MODULES"));
	_moduleManager.setup();
	logDebug(F("> INIT MODULES"));
	_moduleManager.init();

}



// Run all modules constantly
void SimpleDroneRun(void)
{
	while(true)
		_moduleManager.run();
}