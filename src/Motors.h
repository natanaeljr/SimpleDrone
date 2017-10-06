#ifndef __MOTORS_H__
#define __MOTORS_H__
#include <stdint.h>
#include <defines.h>

#define MOTOR_THRUST_MIN 0 	 // PWM MIN
#define MOTOR_THRUST_MAX 255 // PWM MAX


class Motors_t {
public:
	enum _MotorEnum : uint8_t {
		FL = 0, // Front Left  CCW
		FR = 1, // Front Right CW
		ML = 2, // Most  Left  CW
		MR = 3, // Most  Right CCW
		RL = 4, // Rear  Left  CCW
		RR = 5  // Rear  Right CW
	};

	uint8_t thrust[NUM_MOTORS] = {0};
	void set(_MotorEnum motor, int16_t value);
	void output();
	void debug();
};

extern Motors_t Motors;




#endif /* end of include guard: __MOTORS_H__ */
