#include "Motors.h"
#include <Arduino.h>
#include <defines.h>
#include <debug.h>
#include <functions.h>



void Motors_t::set(_MotorEnum motor, int16_t value){
	thrust[motor] = constrainf(value, (int16_t) MOTOR_THRUST_MIN, (int16_t) MOTOR_THRUST_MAX);
}


void Motors_t::output(){
	analogWrite(MOTOR_FL_PIN, thrust[0]);
	analogWrite(MOTOR_FR_PIN, thrust[1]);
	analogWrite(MOTOR_ML_PIN, thrust[2]);
	analogWrite(MOTOR_MR_PIN, thrust[3]);
	analogWrite(MOTOR_RL_PIN, thrust[4]);
	analogWrite(MOTOR_RR_PIN, thrust[5]);
}


void Motors_t::debug() {
	Debug << LogType::DEBUG << F("FL= ")  << thrust[0]
							<< F(" FR= ") << thrust[1]
							<< F(" ML= ") << thrust[2]
							<< F(" MR= ") << thrust[3]
							<< F(" RL= ") << thrust[4]
							<< F(" RR= ") << thrust[5] << endl;
}



Motors_t Motors = Motors_t();
