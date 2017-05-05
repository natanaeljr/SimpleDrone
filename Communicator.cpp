#include "Communicator.h"
#include <SoftwareSerial.h>
#include <functions.h>
#include <settings.h>



Communicator::Communicator(unsigned long _interval = 0) : Module(_interval) 
{
	moduleName = F("Communicator ");
}


SoftwareSerial wifi(2, 4);
void Communicator::setup()
{
	Module::setup();

	wifi.begin(WIFI_BAUDRATE);
	delay(1);










}

bool dataSent = false;
void readToDebug(){
	if(!dataSent)
		return;
	dataSent = false;

	if(!wifi.available()){
		logDebug(F("Wifi serial not available!"));
		return;
	}
	
	char buffer[64] = {0};
	for(int i = 0; i < 64; i++){
		char data = wifi.read();
		if(data == -1)
			break;
		buffer[i] = data;
		delay(1);
	}

	logInfo(F("ESP8266:"));
	log(buffer);
	log("\n");

}
void Communicator::init()
{
	Module::init();
	
	wifi.print(F("AT\r\n"));
	dataSent = true;
	delay(2000);
	readToDebug();







}

void Communicator::run()
{
	readToDebug();
	
	runned();
}