#include "PID.h"
#include <stdlib.h>



PID::PID(float _set_point, float _kp, float _ki, float _kd, float _imax) {
	set_point = _set_point;
	kp = _kp;
	ki = _ki;
	kd = _kd;
	imax = abs(_imax);
	p = i = d = pid = error = last_error = 0;
	min = -65536;
	max = 65536;
}


float PID::compute(float sample) {
	error = sample - set_point;
	p = kp * error;
	i = i + ki * error;
	if(i >= 0)
		i = (i > imax) ? imax : i;
	else
		i = (i < imax * -1) ? (imax * -1) : i;
	d = kd * (error - last_error);
	last_error = error;
	pid = p + i + d;
	if(pid > max)
		pid = max;
	else if (pid < min)
		pid = min;
	return pid;
}


float PID::getError(){return error;}
float PID::getPid(){return pid;}
float PID::getP(){return p;}
float PID::getI(){return i;}
float PID::getD(){return d;}
	