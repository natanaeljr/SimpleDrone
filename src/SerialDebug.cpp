#include "SerialDebug.h"
#include "Motors.h"

//PRIVATE
bool SerialDebug::ready = false;

//PUBLIC
void SerialDebug::initialize(){
	Serial.begin(UART_BAUD_RATE);
	//while(!Serial);
	log(PROJECT);
	ready = true;
}

void SerialDebug::run(){
	if(!Serial.available()) return;

	char data = Serial.read();
	if(data != 'M') return;
	int level = Serial.parseInt();

	if(level > MOTOR_PWM_MAX)
		level = MOTOR_PWM_MAX;
	else if(level < MOTOR_PWM_MIN)
		level = MOTOR_PWM_MIN;

	data = Serial.read();
	if(data != 'P') return;
	int pin = Serial.parseInt();


	//escreve saida PWM
	analogWrite(MOTOR_PIN[pin], level);
	//for(int i=0; i<NUM_MOTORS; i++)
	//	analogWrite(MOTOR_PIN[i], level);

}

//opc: disable/enable threads
