#include "PowerManager.h"
#include <functions.h>
#include <settings.h>



PowerManager::PowerManager(unsigned long _interval) : Module(_interval), 
	battery()
{
	moduleName = F("PowerManager ");
}


void PowerManager::setup()
{
	Module::setup();

}


void PowerManager::init()
{
	Module::init();

	battery.update();	

}


void PowerManager::run()
{
	battery.update();
	logInfo2(F("BATTERY Voltage = "), battery.getVoltage());
	logInfo2(F("BATTERY Percentege = "), battery.getPercentage())
	runned();
}








