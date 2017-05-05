#include "SensorProcessor.h"
#include <Arduino.h>
#include <Wire.h>
#include <settings.h>



SensorProcessor::SensorProcessor(unsigned long _interval) : Module(_interval),
	mpu()
{
	moduleName = F("SensorProcessor ");
}


void SensorProcessor::setup()
{
	Module::setup();

	Wire.begin();
	TWBR = ((CPU_FREQUENCY / I2C_SPEED) - 16) / 2; // set I2C clock frequency
	delay(1);

	mpu.setup();
}


void SensorProcessor::init()
{
	Module::init();
	mpu.init();
}


void SensorProcessor::run()
{
	mpu.read();

	runned();
}


float SensorProcessor::getYaw()
{
	return mpu.ypr[0] * RAD_TO_DEG;
}


float SensorProcessor::getPitch()
{
	return mpu.ypr[2] * RAD_TO_DEG;
}


float SensorProcessor::getRoll()
{
	return mpu.ypr[1] * RAD_TO_DEG;
}
