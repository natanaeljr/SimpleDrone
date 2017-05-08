#include "Motor.h"
#include <Arduino.h>
#include <inttypes.h>



Motor::Motor(const uint8_t _pin) : 
	pin(_pin)
{

}


void Motor::setup()
{
	pinMode(pin, OUTPUT);
}


void Motor::write(uint8_t pwm)
{
	analogWrite(pin, pwm);
}