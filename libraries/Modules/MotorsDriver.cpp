#include "MotorsDriver.h"
#include <Motor.h>
#include <defines.h>
#include <Stabilizer.h>



MotorsDriver::MotorsDriver(unsigned long _interval) : Module(_interval)
{
	moduleName = F("MotorsDriver ");
	for(char i = 0; i < NUM_MOTORS; i++){
		motor[i] = new Motor(MOTOR_PIN[i]);
	}
}


void MotorsDriver::setup()
{
	Module::setup();

	for(char i = 0; i < NUM_MOTORS; i++)
		motor[i]->setup();
}


void MotorsDriver::init()
{
	Module::init();

	#if ENABLE_STARTUP_MOTOR_MELODY
		for(char i = 0; i < NUM_MOTORS; i++){
			motor[i]->write(10);
			delay(40);
			motor[i]->write(0);
		}
	#endif
}


void MotorsDriver::run()
{
	for (uint8_t i = 0; i < NUM_MOTORS; i++)
		motor[i]->write(_stabilizer.getPwm(i));

	runned();
}
