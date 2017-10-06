#ifndef __DEFINES_H__
#define __DEFINES_H__
#include <stdint.h>
#include <types.h>

/****************************************************************************************
 * PROJECT PROPERTIES
*****************************************************************************************/
#define PROJECT "SimpleDrone"
#define VERSION "001"


/****************************************************************************************
 * SERIAL DEBUG
*****************************************************************************************/
#define SERIAL_BAUDRATE 38400


/****************************************************************************************
 * HARDWARE
*****************************************************************************************/
#define CALIBRATE_OSCILLATOR true
#define CPU_FREQUENCY F_CPU
#define CPU_VOLTAGE 3.0


/****************************************************************************************
 * BATTERY
*****************************************************************************************/
#define BATTERY_PIN 0
#define BATTERY_CORRECTION 200
#define BATTERY_VOLT_MAX 420    // 4.2v
#define BATTERY_VOLT_MIN 330    // 3.3v


/****************************************************************************************
 * TASKS
*****************************************************************************************/
const PString_t CN_CHECK_INPUT_TASK 	[] = "CN::check_input";
const PString_t PM_UPDATE_BATTERY_TASK 	[] = "PM::update_battery";
const PString_t PM_CHECK_BATTERY_TASK	[] = "PM::check_battery";
const PString_t PM_DEBUG_TASK			[] = "PM::debug";
const PString_t SP_READ_MPU				[] = "SP::read_mpu";
const PString_t SP_DEBUG_TASK			[] = "SP::debug";
const PString_t ST_STABILIZE_TASK		[] = "ST::stabilize";
const PString_t ST_DEBUG_TASK			[] = "ST::debug";
const PString_t MT_DEBUG_TASK			[] = "MT::debug";
const PString_t SH_DEBUG_TASK			[] = "SH::debug";


/****************************************************************************************
 * IC2
*****************************************************************************************/
#define I2C_SPEED 200000L


/****************************************************************************************
 * IMU
*****************************************************************************************/
#define DMP_AUTOCALIBRATION_TIME 15000 // change later to 15~20s


/****************************************************************************************
 * PID
*****************************************************************************************/
#define YAW_PID_MAX 180
#define ROLL_PID_MAX 60
#define PITCH_PID_MAX 60
#define THROTTLE_MAX 220
#define THROTTLE_MIN 0


/****************************************************************************************
 * MOTORS
*****************************************************************************************/
#define NUM_MOTORS 	6
#define MOTOR_FL_PIN 9
#define MOTOR_FR_PIN 3
#define MOTOR_ML_PIN 10
#define MOTOR_MR_PIN 5
#define MOTOR_RL_PIN 11
#define MOTOR_RR_PIN 6








#endif /* end of include guard: __DEFINES_H__ */
