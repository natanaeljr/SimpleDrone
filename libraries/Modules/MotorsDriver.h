#pragma once
#define __MOTORSDRIVER_H__
#include <Module.h>
#include <Motor.h>
#include <settings.h>
#include <inttypes.h>




class MotorsDriver : public Module
{

private:
	Motor* motor[NUM_MOTORS];

public:
	MotorsDriver(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
};

extern MotorsDriver _motorsdriver;