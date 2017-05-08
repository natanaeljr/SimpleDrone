#pragma once
#define __MODULE_H__
#include <Thread.h>
#include <WString.h>


// Module is an abstract class
class Module : public Thread
{

protected:
	// __FlashStringHelper is a type that points to a string stored in flash instead of RAM 
	// the string needs to be defined between macro F() to be in flash only (WString.h)
	const __FlashStringHelper* moduleName;
	bool isSetup; // tells if method setup() was called
	bool isInit; // tells if method init() was called

public:
	Module(unsigned long _interval = 0);
	virtual void setup(); // has to be called to flip its flag, also check if has already been called
	virtual void init(); // has to be called to flip its flag, also check if has already been called
	virtual bool shouldRun(unsigned long time); // overrides to check if it has been initialized
	// if override run(), must call runned() at the end.
	
};



/*
- Create new Thread library (faster and lighter)

- Calculate elapsed time on Thread
unsigned long finishTime = millis();
if(finishTime - startTime > _interval) // or an "estimated running time"
	logDebug2("Thread is taking longer than it should to run!");

- Change interval to frequency (freq / 1000 = interval)


*/