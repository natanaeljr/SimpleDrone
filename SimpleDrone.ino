#include "SimpleDrone.h"
#include <Arduino.h>
#include <settings.h>
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
	pinMode(7, OUTPUT); 
	digitalWrite(7, HIGH);	

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
- Put a question: let me know if this firmware was usefull for you.
- To compile it, set the sketchbook folder on Arduino IDE to SimpleDrone folder.
	That contains all of the libraries used, so as the hardware config (Atmega328 on a breadboard - 8Mhz internal clock).
- The firmware is very OOP written, so it's not time-efficient for the MPU, the objective is to be quite well understandable
- Delay is only allowed in setup() and init() methods of the modules. Please DO NOT place delays into run() methods.

THREADS
Thread Modules::_debuger; //displays info to Serial for debug purpose
Thread Modules::_powermanager; //manages the power by checking the battery
Thread Modules::_communicator; //intefaces with the wifi module to send/receive data
Thread Modules::_motorsdriver; //outputs calculated PWM modulation to motors  //has Motor objects
Thread Modules::_stabilizer; //calculates PID to output to motors with the data from commander
Thread Modules::_commander; //calculates the target attitude through received commands of communicator and sets other states/modes
Thread Modules::_attitude; //colects IMU data and analyzes it
Thread Modules::_drone; //update led system and other things

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
*/

