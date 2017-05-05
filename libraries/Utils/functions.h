#pragma once
#define __FUNCTIONS_H__
#include <settings.h>

/****************************************************************************************
 * DEBUG SYSTEM
*****************************************************************************************/
#if ENABLE_SERIALDEBUG
    #define log(arg) Serial.print(arg);

    #define logHeader(__PROJECT__){\
        log(F("-->> "));\
        log(F(__PROJECT__));\
        log(F(" [build: "));\
        log(F(__DATE__));\
        log(F(" - "));\
        log(F(__TIME__));\
        log(F("]\n"));\
    }

    #define logPlace(arg){\
        log(arg);\
        log(F(" \t["));\
        log(F(__FILE__));\
        log(F(", "));\
        log(F(__LINE__));\
        log(F(", "));\
        log(F(__FUNCTION__));\
        log(F("]\n"));\
    }

#else
    #define logHeader(arg)
    #define logPlace(arg)
    #define log(arg)

#endif


#if ENABLE_SERIALDEBUG != 1
    #ifdef LOG_LEVEL
        #undef LOG_LEVEL
    #endif
    #define LOG_LEVEL 0
#endif

#if LOG_LEVEL > 0 
    #define logError(x) {log(F("[ERROR]| ")); log(x); log(F("\n"));}
    #define logError2(x, y) {log(F("[ERROR]| ")); log(x); log(y); log(F("\n"));}
#else
    #define logError(x)
    #define logError2(x, y)
#endif
#if LOG_LEVEL > 1
    #define logWarn(x) {log(F("[WARN] | ")); log(x); log(F("\n"));}
    #define logWarn2(x, y) {log(F("[WARN] | ")); log(x); log(y); log(F("\n"));}
#else
    #define logWarn(x)
    #define logWarn2(x, y)
#endif
#if LOG_LEVEL > 2
    #define logInfo(x) {log(F("[INFO] | ")); log(x); log(F("\n"));}
    #define logInfo2(x, y) {log(F("[INFO] | ")); log(x); log(y); log(F("\n"));}
#else
    #define logInfo(x)
    #define logInfo2(x, y)
#endif
#if LOG_LEVEL > 3
    #define logDebug(x) {log(F("[DEBUG]| ")); log(x); log(F("\n"));}
    #define logDebug2(x, y) {log(F("[DEBUG]| ")); log(x); log(y); log(F("\n"));}
#else
    #define logDebug(x)
    #define logDebug2(x, y)
#endif


// emptys a buffer with char null
#define empty_buffer(buffer, size)\
    for(int i = 0; i < size && buffer[i] != '\0'; i++)\
        buffer[i] = '\0';


// report the amount of free SRAM (space between the heap and the stack)
int freeRam ();