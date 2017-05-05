#include "MotorsDriver.h"
#include "Motor.h"
#include <settings.h>
#include <inttypes.h>



MotorsDriver::MotorsDriver(unsigned long _interval) : Module(_interval)
{
	for(char i = 0; i < NUM_MOTORS; i++){
		motor[i] = new Motor(MOTOR_PIN[i]);
	}
	moduleName = F("MotorsDriver ");
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


	runned();
}


void MotorsDriver::setOutput(uint8_t *value)
{
	for (int i = 0; i < NUM_MOTORS; i++)
		motor[i]->write(value[i]);
}