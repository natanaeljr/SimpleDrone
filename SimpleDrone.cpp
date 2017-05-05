#include "SimpleDrone.h"
#include <functions.h>



//INSTANTIATE MODULES (thread interval)
ModuleManager 	MANAGER(0);
#if ENABLE_SERIALDEBUG
	Debuger 	DEBUGER(50);
#endif
PowerManager 	POWERMANAGER(10000);
Communicator 	COMMUNICATOR(1000);
SensorProcessor SENSORPROCESSOR(2);
Stabilizer 		STABILIZER(5);
MotorsDriver 	MOTORSDRIVER(5);




// Add Modules to ModuleManager, setup and initialize them
void SimpleDrone(void) 
{

	#if ENABLE_SERIALDEBUG
		MANAGER.add(&DEBUGER);
	#endif
	MANAGER.add(&POWERMANAGER);
	MANAGER.add(&COMMUNICATOR);
	MANAGER.add(&SENSORPROCESSOR);
	MANAGER.add(&STABILIZER);
	MANAGER.add(&MOTORSDRIVER);

	logDebug(F("> SETUP MODULES"));
	MANAGER.setup();
	logDebug(F("> INIT MODULES"));
	MANAGER.init();

}



// Run all modules constantly
void SimpleDroneRun(void)
{
	while(true)
		MANAGER.run();
}