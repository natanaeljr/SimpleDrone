#pragma once
#define __POWERMANAGER_H__
#include "Module.h"
#include "Battery.h"



class PowerManager : public Module
{
	
private:
	Battery battery;

public:
	PowerManager(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
};













