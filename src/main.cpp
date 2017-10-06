#include <Arduino.h>
#include <Drone.h>
#include <defines.h>

Drone_t SimpleDrone;

void setup() {
    #if CALIBRATE_OSCILLATOR
		OSCCAL = 0xC2;
	#endif

	SimpleDrone.init();
}

void loop() {
	SimpleDrone.run();
}
