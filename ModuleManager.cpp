#include "ModuleManager.h"



ModuleManager::ModuleManager(unsigned long _interval = 0) : Module(_interval)
{
	clear();
	
	moduleName = F("ModuleManager ");
}


bool ModuleManager::add(Module* _module)
{
	// Check if the Module already exists on the array
	for(int i = 0; i < MAX_MODULES; i++){
		if(module[i] != NULL && module[i]->ThreadID == _module->ThreadID)
			return true;
	}
	// Find an empty slot
	for(int i = 0; i < MAX_MODULES; i++){
		if(!module[i]){
			// Found a empty slot, now add Module
			module[i] = _module;
			cached_size++;
			return true;
		}
	}

	// Array is full
	return false;
}


bool ModuleManager::remove(int _id)
{
	// Find Modules with the id, and removes
	for(int i = 0; i < MAX_MODULES; i++){
		if(module[i]->ThreadID == _id){
			module[i] = NULL;
			cached_size--;
			return true;
		}
	}
	return false;
}


bool ModuleManager::remove(Module* _module)
{
	return remove(_module->ThreadID);
}


void ModuleManager::clear()
{
	for(int i = 0; i < MAX_MODULES; i++)
		module[i] = NULL;
	cached_size = 0;
}


int ModuleManager::size(bool cached)
{
	if(cached)
		return cached_size;

	int size = 0;
	for(int i = 0; i < MAX_MODULES; i++)
		if(module[i] != NULL)
			size++;
	cached_size = size;

	return cached_size;
}


Module* ModuleManager::get(int index)
{
	return index >= 0 && index < MAX_MODULES ? module[index] : NULL; 
}



void ModuleManager::run()
{
	if(_onRun != NULL)
		_onRun();

	unsigned long time = millis();
	for(int i = 0; i < cached_size; i++){
		// Object exists? Is enabled? Timeout exceeded?
		if(module[i] && module[i]->shouldRun(time))
			module[i]->run();
	}

	runned();
}



void ModuleManager::setup()
{
	Module::setup();

	for(int i = 0; i < cached_size; i++)
		if(module[i])
			module[i]->setup();
}

void ModuleManager::init()
{
	Module::init();

	for(int i = 0; i < cached_size; i++)
		if(module[i])
			module[i]->init();
}





