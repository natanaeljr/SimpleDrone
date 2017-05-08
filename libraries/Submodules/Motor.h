#pragma once
#define __MOTOR_H__
#include <inttypes.h>



class Motor
{

private:
	const uint8_t pin;
public:
	Motor(const uint8_t _pin);
	void setup();
	void write(uint8_t pwm);
	
};