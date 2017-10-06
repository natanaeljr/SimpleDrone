#include "SensorProcessor.h"
// standard
#include <Arduino.h>
#include <Wire.h>
// helper
#include <helper_3dmath.h>
// utils
#include <defines.h>
#include <debug.h>
#include <functions.h>


SensorProcessor_t::SensorProcessor_t() : Module_t(PSTR("SensorProcessor")) {}


void SensorProcessor_t::init() {
    if(isInit) return;
	Debug << LogType::DEBUG << castF(name) << F(" init") << endl;
	// init I2C and set clock frequency
	Wire.begin();
	TWBR = ((CPU_FREQUENCY / I2C_SPEED) - 16) / 2;
	delay(1);
	// init sensor units
	init_mpu();
    isInit = true;
}


/****************************************************************************************
 * MOTION PROCESSOR UNIT  code
*****************************************************************************************/
inline void SensorProcessor_t::init_mpu() {
	Mpu.initialize();
	if(!Mpu.testConnection()){
		Error << LogType::ERROR << F("MPU6050 connection failed") << endl;
		while (!Mpu.testConnection()) {
			Mpu.initialize();
			delay(20);
		}
		Info << LogType::INFO << F("MPU6050 connection established") << endl;
	}
	if(Mpu.dmpInitialize() != 0){
		Error << LogType::ERROR << F("DMP initialization failed") << endl;
		while (Mpu.dmpInitialize() != 0) {
			delay(50);
		}
		Info << LogType::INFO << F("DMP initialization successful") << endl;
	}
	// Mpu.setXGyroOffset(126);
	// Mpu.setYGyroOffset(65);
	// Mpu.setZGyroOffset(8);
	// Mpu.setXAccelOffset(-3834);
	// Mpu.setYAccelOffset(1297);
	// Mpu.setZAccelOffset(1326);
	Mpu.setDMPEnabled(true);
	// MPU is setup! Just wait autocalib
	Debug << LogType::DEBUG << F("Waiting for DMP autocalibration ...") << endl;
	delay(DMP_AUTOCALIBRATION_TIME);
	// MPU is ready! wipe Interrupt_status_register and FIFO to start clean
	Mpu.getIntStatus();
	Mpu.resetFIFO();
}

void SensorProcessor_t::read_mpu() {
	if(!Mpu.getDMPEnabled()){
		Error << LogType::ERROR << F("DMP is not enabled") << endl;
		return;
		// STOP DRONE or INIT MPU AGAIN
	}
	uint8_t interrupt = Mpu.getIntStatus();
	// check for FIFO overflow (should never happen if reading rate matches FIFO rate)
	if(interrupt & (1 << MPU6050_INTERRUPT_FIFO_OFLOW_BIT)){
		Warn << LogType::WARN << F("MPU FIFO OverFlow, count = ") << Mpu.getFIFOCount() << endl;
		Mpu.resetFIFO();
		return;
	}
	// check if we're getting on time (if we're too slow)
	if(Mpu.getFIFOCount() > Mpu.dmpGetFIFOPacketSize()){ // it means there is already more than 1 packet in FIFO, we must speed up to catch up and stay clean
		Warn << LogType::WARN << F("Too Slow! FIFO = ") << Mpu.getFIFOCount() << endl;
		Mpu.resetFIFO();
		return;
	}
	// check for DMP data ready (if we're too fast)
	if(!(interrupt & (1 << MPU6050_INTERRUPT_DMP_INT_BIT))) { // it means there is no data to be read, slow down reading rate
		Warn << LogType::WARN << F("Too Fast! DMP is not ready. FIFO = ") << Mpu.getFIFOCount() << endl;
	}
	// check for a complete FIFO packet (-> never false, I think when DMP data is ready, always there will be a packet available ( > 42), no reason to check then)
	if(!Mpu.dmpPacketAvailable()){
		Info << LogType::INFO << F("DMP ready, but FIFO packet is not complete") << endl;
		while(!Mpu.dmpPacketAvailable());
	}
	// everything ok, get the packet
	uint8_t fifobuffer[Mpu.dmpGetFIFOPacketSize()]; // default = 42
	Mpu.getFIFOBytes(fifobuffer, Mpu.dmpGetFIFOPacketSize());
	// compute the yaw, pitch and roll
	Quaternion quaternion;
	VectorFloat gravity;
	float ypr[3];
	Mpu.dmpGetQuaternion(&quaternion, fifobuffer);
	Mpu.dmpGetGravity(&gravity, &quaternion);
	Mpu.dmpGetYawPitchRoll(ypr, &quaternion, &gravity);
	// convert them to degrees
	ypr[0] = degrees(ypr[0]);
	ypr[1] = degrees(ypr[1]);
	ypr[2] = degrees(ypr[2]);
	// filter "noisy angles"
	if(	ypr[0] < yaw + 50 	&& ypr[0] > yaw - 50  && // FIX YAW FILTER to accommodate full rotation (-179 | 179)
		ypr[1] < roll + 30 	&& ypr[1] > roll - 30 &&
		ypr[2] < pitch + 30 && ypr[2] > pitch - 30 )
	{
		// then save, (invert roll and pitch)
		yaw   = ypr[0];
		pitch = ypr[2];
		roll  = ypr[1];
	}
	// ROTATION UPDATED!
}


void SensorProcessor_t::debug() {
	Debug << "yrp = \t\t" << yaw << " \t\t" << roll << " \t\t" << pitch << endl;
}







SensorProcessor_t SensorProcessor = SensorProcessor_t();
