#pragma once
#define _SETTINGS_H

#include <Arduino.h>

//PROJECT**********************************************************************
#define PROJECT "-->> Running DroneBeta_v0.1 ..."


//DEBUG SERIAL*****************************************************************
#define UART_BAUD_RATE 38400
#define SERIALDEBUG_RUN_INTERVAL 50
#define LOG_LEVEL 3
// Change LOG_LEVEL to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug
#define log(x) Serial.println(x);
#if LOG_LEVEL > 0
#define logError(x) {Serial.print(">>ERROR| "); Serial.println(x);}
#define logError2(x, y) {Serial.print(">>ERROR| "); Serial.print(x); Serial.println(y);}
#else
#define logError(x)
#define logError2(x, y)
#endif
#if LOG_LEVEL > 1
#define logWarn(x) {Serial.print(">>WARN | "); Serial.println(x);}
#define logWarn2(x, y) {Serial.print(">>WARN | "); Serial.print(x); Serial.println(y);}
#else
#define logWarn(x)
#define logWarn2(x, y)
#endif
#if LOG_LEVEL > 2
#define logInfo(x) {Serial.print(">>INFO | "); Serial.println(x);}
#define logInfo2(x, y) {Serial.print(">>INFO | "); Serial.print(x); Serial.println(y);}
#else
#define logInfo(x)
#define logInfo2(x, y);
#endif
#if LOG_LEVEL > 3
#define logDebug(x) {Serial.print(">>DEBUG| "); Serial.println(x);}
#define logDebug2(x, y) {Serial.print(">>DEBUG| "); Serial.print(x); Serial.println(y);}
#else
#define logDebug(x)
#define logDebug2(x, y)
#endif


//WIFI ESP*********************************************************************
#define WIFI_BAUD_RATE 9600 //alterar para 38400


//I2C**************************************************************************
#define I2C_SPEED 100000L


//LEDS*************************************************************************
#define LED_GREEN_PIN 7
#define LED_RED_PIN 8

//BATTERY**********************************************************************
#define BATTERY_RUN_INTERVAL 300
#define BATTERY_SAMPLING 10
#define BATTERY_PIN A0
#define BATTERY_MIN_VOLTAGE 3.2f
#define BATTERY_MAX_VOLTAGE 4.2f
#define BATTERY_WARNING_LEVEL 20
#define BATTERY_DEAD_LEVEL 10
#define BATTERY_ADC_CORRECTION 2.0f
#define CPU_VOLTAGE 3.0f


//MOTORS***********************************************************************
#define MOTORS_RUN_INTERVAL 100
#define NUM_MOTORS 		6
#define MOTOR_1_PIN 	6
#define MOTOR_2_PIN 	5
#define MOTOR_3_PIN 	3
#define MOTOR_4_PIN 	11
#define MOTOR_5_PIN 	10
#define MOTOR_6_PIN 	9

#define MOTOR_PWM_MAX 	255
#define MOTOR_PWM_MIN	0
#define MOTOR_PWN_INC	2
#define MOTOR_PWN_DEC	5

const int MOTOR_PIN[NUM_MOTORS] = {
	MOTOR_1_PIN,
	MOTOR_2_PIN,
	MOTOR_3_PIN,
	MOTOR_4_PIN,
	MOTOR_5_PIN,
	MOTOR_6_PIN
};
