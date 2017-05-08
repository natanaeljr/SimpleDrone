#pragma once
#define __PID_H__



class PID
{
private:
	float error, last_error;
	float p, i, d;
	float pid;

public:
	float set_point;
	float kp, ki, kd, imax;
	float min, max;

	PID(float _set_point, float _kp, float _ki, float _kd, float _imax);

	float compute(float sample);

	float getError();
	float getPid();
	float getP();
	float getI();
	float getD();
	
};