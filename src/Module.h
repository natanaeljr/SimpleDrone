#ifndef __MODULE_H__
#define __MODULE_H__
#include <types.h>


// abstract class to create modules
class Module_t {
public:
    const PStringPtr_t name;
    bool isInit = false;
    virtual void init() = 0;
    Module_t(const PStringPtr_t _name) : name(_name) {}
};




#endif /* end of include guard: __MODULE_H__ */
