#pragma once
#define __POWERMANAGER_H__
#include <Module.h>
#include <enums.h>
#include <inttypes.h>

namespace {
	struct Battery
	{
		float voltage;
		uint8_t percentage;
		BattLevels status;
		Battery() : voltage(0), percentage(0), status(BattLevels::NORMAL) {}
	};
}


class _PowerManager : public Module
{	

private:
	Battery battery;
	void updateBattery();
	void updateStatus();
	void shutdown();

public:
	_PowerManager(unsigned long _interval = 0);
	// Override Module::init
	void init();
	// Override Thread::run
	void run();
	// return the object Battery
	Battery getBattery();	
};

extern _PowerManager PowerManager;












