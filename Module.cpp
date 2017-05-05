#include "Module.h"
#include <functions.h>



Module::Module(unsigned long _interval = 0) : Thread(NULL, _interval),
	isSetup(false),
	isInit(false)
{
	moduleName = F("Module "); // stored in flash since it's read-only and has few accesses.
}


void Module::setup()
{
	// if it was already setup, does nothing
	if(isSetup) 
		return;
	isSetup = true;
	logDebug2(moduleName, ThreadID);
}


void Module::init()
{
	// if it was not been setup yet or already initialized, does nothing
	if(!isSetup || isInit) 
		return;
	isInit = true;
	logDebug2(moduleName, ThreadID);
}


// Overrides to check if it has also been initialized
bool Module::shouldRun(unsigned long time)
{
	return isInit && Thread::shouldRun(time);
}