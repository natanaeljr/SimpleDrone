#include "MPU.h"
#include <MPU6050_6Axis_MotionApps20.h>
#include <helper_3dmath.h>
#include <functions.h>
#include <settings.h>
#include <Arduino.h>



MPU::MPU() :
	mpu6050(),
	ypr({0}),
	dmpReady(false),
	mpuIntStatus(0),
	devStatus(0),
	packetSize(0),
	fifoCount(0),
	fifoBuffer({0})
{

}


void MPU::setup()
{
	mpu6050.reset();
	delay(50);
}


void MPU::init()
{
	mpu6050.initialize();
	if(mpu6050.testConnection()){
		logDebug(F("MPU6050 connection successful"));
	} else {
		logError(F("MPU6050 connection failed"));
	}
	
	if(!mpu6050.dmpInitialize()){

    	mpu6050.setXGyroOffset(126);
    	mpu6050.setYGyroOffset(65);
    	mpu6050.setZGyroOffset(8);
    	mpu6050.setXAccelOffset(-3834);
    	mpu6050.setYAccelOffset(1297);
    	mpu6050.setZAccelOffset(1326);

    	mpu6050.setDMPEnabled(true);

    	packetSize = mpu6050.dmpGetFIFOPacketSize(); // default 42
       	dmpReady = true;

       	logDebug(F("DMP Initialization successful"));
	}
	else{
    	logError(F("DMP Initialization failed"));
	}
	delay(1000);
}

// Quaternion q;           // [w, x, y, z]         quaternion container
// VectorInt16 aa;         // [x, y, z]            accel sensor measurements
// VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
// VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
// VectorFloat gravity;    // [x, y, z]            gravity vector

void MPU::read()
{
	if(!dmpReady) 
		return;

	mpuIntStatus = mpu6050.getIntStatus();
	fifoCount = mpu6050.getFIFOCount();

	if(!mpuIntStatus && fifoCount < packetSize)
		return;

	if(mpuIntStatus & 0x10){
		mpu6050.resetFIFO();
		logWarn(F("MPU FIFO Overflow!"));
		return;
	}
	
	if(mpuIntStatus & 0x02){
		while (fifoCount < packetSize) 
			fifoCount = mpu6050.getFIFOCount(); //***see dmpPacketAvailable();
		mpu6050.getFIFOBytes(fifoBuffer, packetSize);
		fifoCount -= packetSize;

		Quaternion q;           // [w, x, y, z]         quaternion container
		VectorFloat gravity;    // [x, y, z]            gravity vector
		mpu6050.dmpGetQuaternion(&q, fifoBuffer);
		mpu6050.dmpGetGravity(&gravity, &q);
		mpu6050.dmpGetYawPitchRoll(ypr, &q, &gravity);
		
		#if ENABLE_DEBUG_MPUDATA
			//logDebug("MPU DATA:");
			log(F("ypr\t"));
	        log(ypr[0] * RAD_TO_DEG); // RAD_TO_DEG definition in "Arduino.h" 
	        log(F("\t"));
	        log(ypr[1] * RAD_TO_DEG); // RAD_TO_DEG definition in "Arduino.h" 
	        log(F("\t"));
	        log(ypr[2] * RAD_TO_DEG); // RAD_TO_DEG definition in "Arduino.h" 
	        log(F("\n"));
        #endif

	}


}