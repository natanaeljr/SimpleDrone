#include "Debuger.h"
#include <Arduino.h>
#include <defines.h>
#include <functions.h>



Debuger::Debuger(unsigned long _interval) : Module(_interval),
	rx_buffer({0}),
	tx_buffer({0})
{
	moduleName = F("Debuger ");
}


void Debuger::setup()
{
	Module::setup();

	if(!Serial){
		Serial.begin(SERIAL_BAUDRATE);
		logHeader(PROJECT);
	}
	Serial.setTimeout(0); // To guarantee Serial do not stay waiting for data and screw up our timing 
}


void Debuger::init()
{
	Module::init();


}


void Debuger::run()
{
	//RECEIVE from Serial ----------
	if(Serial.available()) {
		empty_buffer(rx_buffer, SERIAL_RXBUFFER_SIZE);
		//reads data with custom TIMEOUT in microseconds to be quick as possible and do not loose delayed data
		for(int i = 0; i < SERIAL_RXBUFFER_SIZE; i++){
			unsigned long time = micros();
			do{ 
				if(Serial.peek() != -1){
					rx_buffer[i] = Serial.read();
					break;
				}
			} while (micros() - time <= SERIAL_READ_TIMEOUT);
		}
		//gives it a timeout and checks if there is data in buffer yet (it means that was sent more than 64 bytes in a row) 
		//comment out for getting 3x 64 in a row without loss :)
		delayMicroseconds(SERIAL_READ_TIMEOUT);
		if(Serial.peek() != -1)
			logWarn2(F("Serial OverFlow! Incoming Data might have been lost! Buffer size is "), SERIAL_RXBUFFER_SIZE);	
		//feedback
		logDebug2(F("RX_BUFFER = "), rx_buffer);
	}



	runned();
}