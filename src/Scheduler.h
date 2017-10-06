#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include <Task.h>

#define TASKLIST_SIZE 20

class Scheduler_t {
public:
    Task_t* TaskList[TASKLIST_SIZE];
    uint32_t looptime = 0;
    void addTask(Task_t* task);
    Task_t* getTaskPS(const PStringPtr_t _name); // get task with a string saved in flash
	Task_t* getTask(const char* _name); // get task with a string saved in RAM
    void execute();
    void debug();
};

extern Scheduler_t Scheduler;


#endif /* end of include guard: __SCHEDULER_H__ */
