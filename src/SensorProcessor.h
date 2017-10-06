#ifndef __SENSORPROCESSOR_H__
#define __SENSORPROCESSOR_H__
#include <Module.h>
#include <MPU6050_6Axis_MotionApps20.h>

#define FIFO_RATE = 200 / (dmpConfig[MPU6050_DMP_CONFIG_SIZE - 1] + 1); // default = 100hz, changed to 50hz


class SensorProcessor_t : public Module_t{
public:
	MPU6050 Mpu = MPU6050();
	float yaw = 0;
	float pitch = 0;
	float roll = 0;
	void init_mpu();
    void read_mpu();
	void debug();
	void sleep(); // Mpu.setSleepEnabled(true);
    void init() override;
    SensorProcessor_t();
};

extern SensorProcessor_t SensorProcessor;

/*
MPU6050
getDeviceID()
getFIFOCount()
dmpPacketAvailable()
dmpGetFIFOPacketSize()
setSleepEnabled()
reset()
resetFIFO()
setDMPEnabled()
resetDMP()
dmpGetQuaternion()
dmpGetGravity()
dmpGetYawPitchRoll()

 */

#endif /* end of include guard: __SENSORPROCESSOR_H__ */
