#pragma once
#define __MODULEMANAGER_H__
#include <Module.h>
#include <defines.h>



class ModuleManager : public Module
{

protected:
	Module* module[MAX_MODULES];
	int cached_size;

public:
	ModuleManager(unsigned long _interval = 0);

	bool add(Module* _module);
	bool remove(int _id);
	bool remove(Module* _module);
	void clear();
	int size(bool cached = true);
	Module* get(int index);
	
	//Thread override
	void run();
	
	//Module overrides
	void setup();
	void init();
	
};

extern ModuleManager _moduleManager;