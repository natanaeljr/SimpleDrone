#include "Console.h"
// standard
#include <Arduino.h>
#include <stdint.h>
// utils
#include <debug.h>
#include <functions.h>
// partss
#include <Task.h>
#include <Scheduler.h>
#include <Motors.h>
// modules
#include <PowerManager.h>
#include <SensorProcessor.h>
#include <Stabilizer.h>


Console_t::Console_t() : Module_t(PSTR("Console")) {}


void Console_t::init() {
	if(isInit) return;
	// check for previous Serial initialization, else init
	if(!Serial){
		Serial.begin(SERIAL_BAUDRATE);
        Serial << LogArg::HEADER;
        Serial.flush();
	}
	Debug << LogType::DEBUG << castF(name) << F(" init") << endl;
	Serial.setTimeout(0); // garantees it doesn't hang in any reading
	isInit = true;
}


void Console_t::check_input() {
	// check for data in HardwareSerial buffer
	if(!Serial.available()) return;
	char rxbuffer [CN_RXBUFFER_SIZE + 1] = {0}; // "+ 1" for '\0'
	uint8_t count = receive(rxbuffer);
	if(count == 0) return;
	// Info << LogType::INFO << F("RX(") << count << F(") = ") << rxbuffer << endl; // feedback
	translate(rxbuffer);
}


inline uint8_t Console_t::receive(char * rxbuffer) {
	uint32_t time; // mark the start time for each index
	char data;
	int count = 0;
	for(int8_t i = 0; i < CN_RXBUFFER_SIZE; i++){
		time = micros();
		while(true){
			data = Serial.read();
			if(data != -1){
				if(data == '\n' || data == '\r') // check for end-line
					i = CN_RXBUFFER_SIZE;
				else
					rxbuffer[count++] = data;
				break;
			}
			else if(micros() - time > CN_READ_TIMEOUT){
				i = CN_RXBUFFER_SIZE;
				break;
			}
		}
	}
	return count;
}


// Bad Ugly Translator
inline void Console_t::translate(char * buffer) {
	int8_t length = strlen(buffer);
	if(length < 3 && buffer[1] != ':') return;

	if(buffer[0] == 'D'){ // DEBUG ---------------------------------------------
		if(buffer[2] == 'P' && buffer[3] == 'M')
			PowerManager.debug();
		else
		if(buffer[2] == 'S' && buffer[3] == 'P')
			SensorProcessor.debug();
		else
		if(buffer[2] == 'C' && buffer[3] == 'N')
			this->debug();
		else
		if(buffer[2] == 'S' && buffer[3] == 'H')
			Scheduler.debug();
		else
		if(buffer[2] == 'S' && buffer[3] == 'T')
			Stabilizer.debug();
		else
		if(buffer[2] == 'M' && buffer[3] == 'T')
			Motors.debug();
		else
		if(buffer[2] == 'f' && buffer[3] == 'r')
			Debug << LogType::DEBUG << F("FREE RAM = ") << free_ram() << endl;
		else
			Debug << LogType::ERROR << F("Failed to debug Module") << endl;
		return;
	}

	if(buffer[0] == 'S'){ // SET -----------------------------------------------
		if(buffer[2] == 't' && buffer[3] == 'a' && buffer[4] == 's' && buffer[5] == 'k' && buffer[6] == ':' && buffer[7] == '\"'){
			// seek end of the task name
			uint8_t i; // index of the last '\"'
			for(i = 12; i < length; i++)
				if(buffer[i] == '\"')
					break;
			if(i < length){
				char taskname[i - 8 + 1] = {0};
				strncpy(taskname, buffer + 8, i - 8);
				// Debug << LogType::DEBUG << F("index = ") << i << F(" taskname = ") << taskname << endl;
				Task_t* task = Scheduler.getTask(taskname);
				if(task != nullptr){
					task->enable = !task->enable;
					Debug << LogType::DEBUG << taskname << F("->enable = ") << (task->enable ? F("true") : F("false")) << endl;
				}
				else
					Debug << LogType::ERROR << F("Task not found") << endl;
			}
			else
				Debug << LogType::ERROR << F("Bad Request! not found last ':'") << endl;
		}
		else
		if(buffer[2] == 't' && buffer[3] == 'h' && buffer[4] == 'r' && buffer[5] == 'o' && buffer[6] == 't' && buffer[7] == 't' && buffer[8] == 'l' && buffer[9] == 'e' && buffer[10] == ':'){
			int16_t value = atoi(buffer + 11);
			Stabilizer.setThrottle(value);
			Debug << LogType::DEBUG << F("value = ") << value << F(" throttle = ") << Stabilizer.throttle << endl;
		}
		else
			Debug << LogType::ERROR << F("Set is not a Task") << endl;
		return;
	}

	if(buffer[0] == 'G'){ // GET -----------------------------------------------
		if(buffer[2] == 't' && buffer[3] == 'h' && buffer[4] == 'r' && buffer[5] == 'o' && buffer[6] == 't' && buffer[7] == 't' && buffer[8] == 'l' && buffer[9] == 'e'){
			Debug << LogType::INFO << F("throttle = ") << Stabilizer.throttle << endl;
		}
		return;
	}

	Debug << LogType::ERROR << F("Bad Request!") << endl;
}


void Console_t::debug() {
}






Console_t Console = Console_t();
