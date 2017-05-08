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
	return degrees(mpu.ypr[0]);
}


float SensorProcessor::getPitch()
{
	return degrees(mpu.ypr[2]);
}


float SensorProcessor::getRoll()
{
	return degrees(mpu.ypr[1]);
}
