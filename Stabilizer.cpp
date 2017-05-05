#include "Stabilizer.h"
#include "SimpleDrone.h"
#include <settings.h>
#include <functions.h>



Stabilizer::Stabilizer(unsigned long _interval) : Module(_interval)
{
	moduleName = F("Stabilizer ");
}


void Stabilizer::setup()
{
	Module::setup();


}


void Stabilizer::init()
{
	Module::init();


}


void Stabilizer::run()
{


	runned();
}