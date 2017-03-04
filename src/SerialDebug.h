#pragma once
#define SERIAL_DEBUG_H

#include <Arduino.h>
#include "_settings.h"

class SerialDebug
{
private:
	static bool ready; 
	
public:
	SerialDebug();
	~SerialDebug();
	
	static void initialize();
	static void run();
};
