#pragma once
#define __COMMUNICATOR_H__
#include "Module.h"



class Communicator : public Module
{

public:
	Communicator(unsigned long _interval = 0);
	void setup();
	void init();
	void run();
	
};

/*
#define COMM_MUX_MULTI "AT+CIPMUX=1\r\n"
#define COMM_START_SERVER "AT+CIPSERVER=1,333\r\n"
#define COMM_SEND "AT+CIPSEND=0,30\r\n"


serialWifi.begin(WIFI_SERIAL_SPEED);
serialWifi.print(COMM_MUX_MULTI);
delay(2000); //tempo de resposta garantido
serialWifi.print(COMM_START_SERVER);
delay(2000); //tempo de resposta garantido
serialWifi.print("ATE0\r\n");
delay(2000); //tempo de resposta garantido


void wifi_callback(){
	if(!serialWifi.available()) return;

	String buffer = "";
	while(serialWifi.available()){
		buffer += (char)serialWifi.read();
		delayMicroseconds(100); //tempo minimo de intervalo de leitura
	}
	Serial.print("BUFFER: [");
	Serial.print(buffer);
	Serial.println("]");
}

*/