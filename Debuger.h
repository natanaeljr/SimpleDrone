#pragma once
#define __DEBUGER_H__
#include "Module.h"
#include <settings.h>



class Debuger : public Module
{

private:
	char rx_buffer[SERIAL_RXBUFFER_SIZE + 1]; // store incoming data, + 1 for \0 character (default 64, see "settings.h")
	char tx_buffer[SERIAL_TXBUFFER_SIZE + 1]; // store outgoing data, + 1 for \0 character (default 64, see "settings.h")

public:
	Debuger(unsigned long _interval = 0);
	void setup();
	void init();
	void run();

	// bool shouldLog();
	
};



/*
Create varibles that enables logs in other modules
process these vars with commands input


*/







