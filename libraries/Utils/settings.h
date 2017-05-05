#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include <inttypes.h>

/****************************************************************************************
 * PROJECT PROPERTIES
*****************************************************************************************/
#define PROJECT "SimpleDrone"
#define VERSION "0.2"
#define MAX_MODULES 10




/****************************************************************************************
 * ENABLEMENTS
*****************************************************************************************/
#define ENABLE_SERIALDEBUG 1
#define ENABLE_STARTUP_MOTOR_MELODY 1
#define ENABLE_DEBUG_MPUDATA 0




/****************************************************************************************
 * HARDWARE
*****************************************************************************************/
#define CPU_FREQUENCY F_CPU
#define CALIBRATE_OSCILLATOR 1




/****************************************************************************************
 * SERIAL DEBUG
*****************************************************************************************/
#define SERIAL_BAUDRATE 38400
#define SERIAL_RXBUFFER_SIZE 64
#define SERIAL_TXBUFFER_SIZE 64
// SERIAL_READ_TIMEOUT custom timeout for read Serial incomings (to be quicker as possible)
// in microseconds. Must be greater than 250ms (for 38400 baudrate)
#define SERIAL_READ_TIMEOUT 300
// LOG_LEVEL change to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug
#define LOG_LEVEL 4




/****************************************************************************************
 * WIFI ESP8266
*****************************************************************************************/
#define WIFI_BAUDRATE 38400




/****************************************************************************************
 * IC2
*****************************************************************************************/
#define I2C_SPEED 200000L




/****************************************************************************************
 * IMU
*****************************************************************************************/





/****************************************************************************************
 * LEDS
*****************************************************************************************/
#define LED_GREEN_PIN 7
#define LED_RED_PIN 8




/****************************************************************************************
 * BATTERY
*****************************************************************************************/
#define BATTERY_PIN 0
#define BATTERY_MIN_VOLTAGE 3.2f
#define BATTERY_MAX_VOLTAGE 4.2f
#define BATTERY_WARNING_LEVEL 20
#define BATTERY_DEAD_LEVEL 10
#define BATTERY_ADC_CORRECTION 2.0f
#define CPU_VOLTAGE 3.0f




/****************************************************************************************
 * MOTORS
*****************************************************************************************/
#define NUM_MOTORS 	6
#define MOTOR_1_PIN 9
#define MOTOR_2_PIN 10
#define MOTOR_3_PIN 11
#define MOTOR_4_PIN 6
#define MOTOR_5_PIN 5
#define MOTOR_6_PIN 3
#define MOTOR_PWM_MAX 255
#define MOTOR_PWM_MIN 0
const uint8_t MOTOR_PIN[NUM_MOTORS] = {
	MOTOR_1_PIN,
	MOTOR_2_PIN,
	MOTOR_3_PIN,
	MOTOR_4_PIN,
	MOTOR_5_PIN,
	MOTOR_6_PIN
};




/****************************************************************************************
 * 
*****************************************************************************************/





/****************************************************************************************
 * 
*****************************************************************************************/



#endif // __SETTINGS_H__

//set GYRO to 1000 deg/s
//set ACCEL to 8G
//reading rate: 500Hz