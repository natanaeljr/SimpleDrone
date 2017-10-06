#include "Stabilizer.h"
// utils
#include <functions.h>
#include <debug.h>
// parts
#include <PID.h>
#include <Motors.h>
#include <SensorProcessor.h>


Stabilizer_t::Stabilizer_t() : Module_t(PSTR("Stabilizer")) {
}


void Stabilizer_t::init() {
	if(isInit) return;
	Debug << LogType::DEBUG << castF(name) << F(" init") << endl;
	// setup pids
	yawpid.outmax = YAW_PID_MAX;
	rollpid.outmax = ROLL_PID_MAX;
	pitchpid.outmax = PITCH_PID_MAX;
	isInit = true;
}


void Stabilizer_t::stabilize() {
	// compute pids
	yawpid.set_point = SensorProcessor.yaw;
	yawpid.compute(SensorProcessor.yaw);
	rollpid.compute(SensorProcessor.roll);
	pitchpid.compute(SensorProcessor.pitch);

	// sum thrust and set to motors
	Motors.set(Motors.FL, (int16_t)(throttle + yawpid.pid - rollpid.pid + pitchpid.pid));
	Motors.set(Motors.FR, (int16_t)(throttle - yawpid.pid + rollpid.pid + pitchpid.pid));
	Motors.set(Motors.ML, (int16_t)(throttle - yawpid.pid - rollpid.pid				  ));
	Motors.set(Motors.MR, (int16_t)(throttle + yawpid.pid + rollpid.pid				  ));
	Motors.set(Motors.RL, (int16_t)(throttle + yawpid.pid - rollpid.pid - pitchpid.pid));
	Motors.set(Motors.RR, (int16_t)(throttle - yawpid.pid + rollpid.pid - pitchpid.pid));

	// output new thrust to all motors
	Motors.output();
}


void Stabilizer_t::setThrottle(uint16_t value) {
	throttle = constrainf(value, (uint16_t) THROTTLE_MIN, (uint16_t) THROTTLE_MAX);
}


void Stabilizer_t::debug() {
	Debug << F("yawpid= ") << yawpid.pid
 		  << F("\t\trollpid= ") << rollpid.pid
		  << F("\t\tpitchpid= ") << pitchpid.pid << endl;
}





Stabilizer_t Stabilizer = Stabilizer_t();
