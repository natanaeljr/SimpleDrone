#ifndef __TASK_H__
#define __TASK_H__
// standard
#include <Arduino.h>
#include <stdint.h>
// utils
#include <types.h>
#include <debug.h>
#include <functions.h>

#define PERIOD_ERROR 2 // correction

class Task_t {
public:
    const PStringPtr_t name;
	bool enable = true;
    uint32_t period;
	uint32_t lastrun;
    uint32_t runtime = 0;
    Task_t(const PStringPtr_t _name, const uint32_t _period) : name(_name), period(_period) {
		lastrun = millis();
	}
    bool shouldRun() {
        return enable && millis() - lastrun > period - PERIOD_ERROR;
    }
    virtual void run() = 0;
};


template<class class_t>
class ModTask_t : public Task_t{
public:
	class_t& object;
    methodptr_t<class_t> method;
    ModTask_t(const PStringPtr_t _name, class_t& _object, methodptr_t<class_t> _method, const uint32_t _period) : Task_t(_name, _period), object(_object), method(_method) {
    }
    void run() override {
        const uint32_t time = millis();
		// check if the task is too early
		if(time - lastrun < period - 1)
            Warn << LogType::WARN << F("Task ") << castF(name) << F(" ran EARLY by: ") << (int32_t)(time - lastrun - period) << endl;
		// check if the task is too late
        if(time - lastrun > period + 15)
            Warn << LogType::WARN << F("Task ") << castF(name) << F(" ran LATE  by: ") << (time - lastrun - period) << endl;
        // register the start time
        const uint32_t start = micros();
        // run the task
        (object.*method)();
        // register the time it took to run
        runtime = micros() - start;
        // update lastrun to now
        lastrun = millis();
    }
};




template<class class_t>
inline ModTask_t<class_t>* createModuleTask(const PStringPtr_t _name, class_t& _object, methodptr_t<class_t> _method, const uint16_t _period) {
    return new ModTask_t<class_t>(_name, _object, _method, _period);
}


#endif /* end of include guard: __TASK_H__ */
