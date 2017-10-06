#ifndef __PID_H__
#define __PID_H__


class PID_t {
public:
	float set_point;
	float kp, ki, kd;
	float imax;
	float pid = 0;
	float error = 0;
	float last_error = 0;
	float outmax = 32767;
	float compute(float sample);
	PID_t(float _set_point, float _kp, float _ki, float _kd, float _imax);
};





#endif /* end of include guard: __PID_H__ */
