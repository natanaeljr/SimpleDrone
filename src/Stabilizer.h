#ifndef __STABILIZER_H__
#define __STABILIZER_H__
#include <Module.h>
#include <PID.h>
// utils
#include <defines.h>


class Stabilizer_t : public Module_t {
public:
	uint8_t throttle = THROTTLE_MIN;
	PID_t yawpid   = PID_t(0, 1, 0, 0, 10);
	PID_t rollpid  = PID_t(0, 1, 0, 0, 10);
	PID_t pitchpid = PID_t(0, 1, 0, 0, 10);

	void setThrottle(const uint16_t value);
	void stabilize();
	void debug();
	void init() override;
	Stabilizer_t();
};

extern Stabilizer_t Stabilizer;





#endif /* end of include guard: __STABILIZER_H__ */
