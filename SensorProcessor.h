#pragma once
#define __SENSORPROCESSOR_H__
#include "Module.h"
#include "MPU.h"
// #include "Compass.h"
// #include "Barometer.h"




class SensorProcessor : public Module
{
private:
	MPU mpu;
	// Compass compass;
	// Barometer barometer;

public:
	SensorProcessor(unsigned long _interval);
	void setup();
	void init();
	void run();

	float getYaw();
	float getPitch();
	float getRoll();

	
};