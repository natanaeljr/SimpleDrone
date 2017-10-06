#include "PID.h"
// standard
#include <stdlib.h>
#include <stdint.h>
// utils
#include <functions.h>


PID_t::PID_t(float _set_point, float _kp, float _ki, float _kd, float _imax) :
	set_point(_set_point),
	kp(_kp),
	ki(_ki),
	kd(_kd),
	imax(abs(_imax)) {
}


float PID_t::compute(float sample) {
	error = sample - set_point;
	float p, i = 0, d;
	// proportinal
	p = kp * error;
	// integral
	i = i + ki * error;
	i = constrainf(i, imax * -1, imax);
	// derivative
	d = kd * (error - last_error);
	last_error = error;
	// all together
	pid = p + i + d;
	pid = constrainf(pid, outmax * -1, outmax);
	return pid;
}
