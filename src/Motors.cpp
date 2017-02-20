#include "Motors.h"

bool Motors::newSet = false;

void Motors::initialize(){
	for(int i=0; i<NUM_MOTORS; i++){
		pinMode(MOTOR_PIN[i], OUTPUT);
		digitalWrite(MOTOR_PIN[i], LOW);
	}
}

void Motors::run(){
	
}