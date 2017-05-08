#include "Stabilizer.h"
#include <settings.h>
#include <functions.h>
#include <SensorProcessor.h>
#include <inttypes.h>
#include <math.h>


Stabilizer::Stabilizer(unsigned long _interval) : Module(_interval),
	rollPid(0, 1, 0, 0, 10),
	pitchPid(0, 1, 0, 0, 10),
	pwm({0})
{
	moduleName = F("Stabilizer ");
}


void Stabilizer::setup()
{
	Module::setup();


}


void Stabilizer::init()
{
	Module::init();
	rollPid.max = MAX_ROLL_ANGLE;
	rollPid.min = MAX_ROLL_ANGLE * -1;
	pitchPid.max = MAX_ROLL_ANGLE;
	pitchPid.min = MAX_ROLL_ANGLE * -1;

}



void Stabilizer::run()
{
	float pid;
	uint8_t pos;
	uint8_t neg;
	//********************************** ROLL **********************************
	//calcula pid - PERFEITO
	pid = rollPid.compute(_sensorprocessor.getRoll());
	
	// calcula lado positivo - PERFEITO
	pos = (pid - MAX_ROLL_ANGLE * -1) * (MOTOR_PWM_MAX - MOTOR_PWM_MIN) / (MAX_ROLL_ANGLE - MAX_ROLL_ANGLE * -1) + MOTOR_PWM_MIN;
	if(pos > MOTOR_PWM_MAX) 
		pos = MOTOR_PWM_MAX;
	else if(pos < MOTOR_PWM_MIN)
		pos = MOTOR_PWM_MIN;

	// calcula lado negativo - PERFEITO
	neg = (pid - MAX_ROLL_ANGLE * -1) * (MOTOR_PWM_MIN - MOTOR_PWM_MAX) / (MAX_ROLL_ANGLE - MAX_ROLL_ANGLE * -1) + MOTOR_PWM_MAX;
	if(neg > MOTOR_PWM_MAX) 
		neg = MOTOR_PWM_MAX;
	else if(neg < MOTOR_PWM_MIN)
		neg = MOTOR_PWM_MIN;

	// calcula o pwm - QUASE PERFEITO
	pwm[0] = sin(radians(30)) * neg;
	pwm[1] = sin(radians(90)) * neg;
	pwm[2] = sin(radians(30)) * neg;
	pwm[3] = sin(radians(30)) * pos;
	pwm[4] = sin(radians(90)) * pos;
	pwm[5] = sin(radians(30)) * pos;


	//********************************** PITCH **********************************
	//calcula pid - PERFEITO
	pid = pitchPid.compute(_sensorprocessor.getPitch());
	
	// calcula lado positivo - PERFEITO
	pos = (pid - MAX_ROLL_ANGLE * -1) * (MOTOR_PWM_MAX - MOTOR_PWM_MIN) / (MAX_ROLL_ANGLE - MAX_ROLL_ANGLE * -1) + MOTOR_PWM_MIN;
	if(pos > MOTOR_PWM_MAX) 
		pos = MOTOR_PWM_MAX;
	else if(pos < MOTOR_PWM_MIN)
		pos = MOTOR_PWM_MIN;

	// calcula lado negativo - PERFEITO
	neg = (pid - MAX_ROLL_ANGLE * -1) * (MOTOR_PWM_MIN - MOTOR_PWM_MAX) / (MAX_ROLL_ANGLE - MAX_ROLL_ANGLE * -1) + MOTOR_PWM_MAX;
	if(neg > MOTOR_PWM_MAX) 
		neg = MOTOR_PWM_MAX;
	else if(neg < MOTOR_PWM_MIN)
		neg = MOTOR_PWM_MIN;

	// calcula o pwm - QUASE PERFEITO
	pwm[0] += sin(radians(60)) * pos;
	pwm[1] += sin(radians(00)) * pos;
	pwm[2] += sin(radians(60)) * neg;
	pwm[3] += sin(radians(60)) * neg;
	pwm[4] += sin(radians(00)) * neg;
	pwm[5] += sin(radians(60)) * pos;

	#if ENABLE_DEBUG_PID
		log("pid = "); log(pid);
		log("\t o1= "); log(pwm[0]);
		log("\t o2= "); log(pwm[1]);
		log("\t o3= "); log(pwm[2]);
		log("\t o4= "); log(pwm[3]);
		log("\t o5= "); log(pwm[4]);
		log("\t o6= "); log(pwm[5]);
		log("\n");
	#endif


	runned();
}



uint8_t Stabilizer::getPwm(uint8_t index)
{
	return pwm[index];
}



/*
(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

*/