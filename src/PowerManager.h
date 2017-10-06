#ifndef __POWERMANAGER_H__
#define __POWERMANAGER_H__
#include <Module.h>
#include <Battery.h>


class PowerManager_t : public Module_t {
public:
    Battery_t Battery;
    void update_battery();
    void check_battery();
    void debug();
    void shutdown();
    void init() override;
    PowerManager_t();
};

extern PowerManager_t PowerManager;





#endif /* end of include guard: __POWERMANAGER_H__ */
