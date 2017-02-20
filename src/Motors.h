#pragma once
#define MOTORS_H

#include <Arduino.h>
#include "_settings.h"

class Motors
{
public:
	Motors();
	~Motors();
	
	static bool newSet;
	static void initialize();
	static void run();
};