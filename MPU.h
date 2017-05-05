#pragma once
#define __MPU_H__
#include <MPU6050_6Axis_MotionApps20.h>
#include <helper_3dmath.h>
#include <inttypes.h>



class MPU
{

public:
	MPU6050 mpu6050; // motion processor unit

	float ypr[3];			// [yaw, pitch, roll]   yaw/pitch/roll container in radians

	bool dmpReady;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer



	MPU();
	void setup();
	void init();
	void read();

};