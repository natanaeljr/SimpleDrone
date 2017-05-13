#include "SimpleDrone.h"
#include <Arduino.h>
#include <defines.h>
#include <functions.h>




// SETUP
void setup() 
{

	#if CALIBRATE_OSCILLATOR
		OSCCAL = 0xC2; //  Internal oscillator calibration		
	#endif

	// This is actually done on Debug module setup, it's here now just for earlier debugging
	#if ENABLE_SERIALDEBUG
		Serial.begin(SERIAL_BAUDRATE);
		logHeader(PROJECT);
		log(F("Serial is up! Initializing program.\n"));
		Serial.flush();
	#endif

	SimpleDrone();

	logDebug2(F("--- free SRAM = "), freeRam());
	logDebug(F("> READY TO ROCK. RUN!\n"));

}



// LOOP
void loop() 
{
	SimpleDroneRun();
}







/*********************************************************************************************
ATTITUDE is the aircraft’s reference with the earth’s horizon. 
For example if the aircraft pitches down, it could be described as having a nose low attitude. 
In this “attitude” the camera of a quadcopter would probably see only the ground and no sky.

README
- To compile it, set the sketchbook folder on Arduino IDE to SimpleDrone folder.
	That contains all of the libraries used, so as the hardware config (Atmega328 on a breadboard - 8Mhz internal clock).
- The firmware is very OOP written, so it's not time-efficient for the MPU, the objective is to be quite well understandable
- Delay is only allowed in setup() and init() methods of the modules. Please DO NOT place delays into run() methods.

TODO
- Write a sketch to evaluate oscillator calibration value
- Add Thread/Module 'expected time' system for tests
- Test access time to SRAM vs FLASH

CODING
- Reserve() your Strings
- Move constant data to PROGMEM 
	#include <avr/pgmspace.h> 
	const dataType variableName[] PROGMEM = {};   // use this form (better)
	const PROGMEM  dataType  variableName[] = {}; // or this form

DEBUG
KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK - 64 characters


PID
setPoint = 0 // which is the target angle
error = readAngle - setpoint // so the error is the readAngle itself
proportional_gain = 0.8
integral_gain = 0.1
derivative_gain = 0.1
proportional = proportion_gain * error;
integral = integral + (integral_gain * error);
derivative = derivative_gain * (error - lastError);
pid = proportional + integral + derivative;
lastError = error;



*/

