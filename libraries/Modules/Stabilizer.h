#pragma once
#define __STABILIZER_H__
#include <Module.h>
#include <PID.h>
#include <settings.h>
#include <inttypes.h>



class Stabilizer : public Module
{
private:
	PID rollPid;
	PID pitchPid;
	uint8_t pwm[NUM_MOTORS];

public:
	Stabilizer(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
	uint8_t getPwm(uint8_t index);

};

extern Stabilizer _stabilizer;





