#include "Scheduler.h"
#include <Task.h>
// utils
#include <defines.h>
#include <debug.h>
#include <functions.h>


void Scheduler_t::addTask(Task_t* task) {
    for(int i = 0; i < TASKLIST_SIZE; i++)
        if(TaskList[i] == nullptr){
            TaskList[i] = task;
            break;
        }
}


Task_t* Scheduler_t::getTaskPS(const PStringPtr_t _name) {
    char buffer[strlen_P(_name) + 1];
    return getTask(strcpy_P(buffer, _name));
}

Task_t* Scheduler_t::getTask(const char* _name){
	for(int i = 0; i < TASKLIST_SIZE && TaskList[i] != nullptr; i++)
    	if(strcmp_P(_name, TaskList[i]->name) == 0)
    		return TaskList[i];
    return nullptr;
}


void Scheduler_t::execute() {
    const uint32_t start = micros();
    for(int i = 0; i < TASKLIST_SIZE; i++)
    	if(TaskList[i] != nullptr && TaskList[i]->shouldRun())
    		TaskList[i]->run();
    const uint32_t end = micros();
    looptime = end - start < looptime ? looptime : end - start;
}


void Scheduler_t::debug() {
    #if ENABLE_DEBUG
        Debug << LogType::DEBUG << F("TASKLIST") << endl;
        for(int i = 0; i < TASKLIST_SIZE; i++)
            if(TaskList[i] != nullptr)
                Debug << F("\t") << castF(TaskList[i]->name) << F(" [") << TaskList[i]->runtime << F("]") << endl;
        Debug << LogType::DEBUG << F("LOOPTIME = ") << looptime << endl;
    #endif
}




Scheduler_t Scheduler = Scheduler_t();
