#pragma once
#define __STABILIZER_H__
#include "Module.h"



class Stabilizer : public Module
{

public:
	Stabilizer(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
};






