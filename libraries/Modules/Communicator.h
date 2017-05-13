#pragma once
#define __COMMUNICATOR_H__
#include <Module.h>




class Communicator : public Module
{

public:
	Communicator(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
};

extern Communicator _communicator;

