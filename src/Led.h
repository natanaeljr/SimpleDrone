#ifndef __LED_H__
#define __LED_H__
#include <Arduino.h>
#include <stdint.h>


struct Led_t {
    const uint8_t pin;
	void toggle() { digitalWrite(pin, !state()); }
	void on() 	  { digitalWrite(pin, HIGH); }
    void off() 	  { digitalWrite(pin, LOW); }
	bool state()  { return digitalRead(pin); }
    Led_t(const uint8_t _pin) : pin(_pin) { pinMode(pin, OUTPUT); }
};


inline Led_t newLed(const uint8_t _pin) { return Led_t(_pin); }


#endif /* end of include guard: __LED_H__ */
