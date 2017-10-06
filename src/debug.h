#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <HardwareSerial.h>
#include <Streaming.h> // usefull code for override << operator
#include <defines.h>
#include <types.h>

////////////////////////////////////////////////////////////////////////////////
#define ENABLE_DEBUG true
// LOG_LEVEL change to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational
// 4: DEBUG: errors, warnings, informational and debug
#define DEBUG_LEVEL 4
////////////////////////////////////////////////////////////////////////////////


// check debugging levels
#if ENABLE_DEBUG
    #define Log   Serial
#else
    #define Log   _CancellStream::CANCELL
#endif

#if DEBUG_LEVEL > 0
    #define Error Log
#else
    #define Error _CancellStream::CANCELL
#endif

#if DEBUG_LEVEL > 1
    #define Warn  Log
#else
    #define Warn _CancellStream::CANCELL
#endif

#if DEBUG_LEVEL > 2
    #define Info  Log
#else
    #define Info _CancellStream::CANCELL
#endif

#if DEBUG_LEVEL > 3
    #define Debug Log
#else
    #define Debug _CancellStream::CANCELL
#endif



enum class _CancellStream {
	CANCELL
};

enum class LogArg : uint8_t {
    HEADER,
    PLACE
};

enum class LogType : uint8_t {
    ERROR,
    WARN,
    INFO,
    DEBUG
};



template<class T>
inline _CancellStream operator << (_CancellStream cs, T arg) { return cs; }


inline Print& operator << (Print &obj, const LogArg logarg) {
    switch (logarg) {
        case LogArg::HEADER:
            Log << F(">> ") << F(PROJECT) << F(" {v: ") << F(VERSION)
            << F("} [build: ") << F(__DATE__) << F(" - ") << F(__TIME__) << F("]") << endl;
            break;
        case LogArg::PLACE:
            Log << F(" [") << F(__FILE__) << F(" : ") << __LINE__ << F("]") << endl;
            break;
    }
    return obj;
}


const PString_t ERROR_STRING	[] = "[ERROR] ";
const PString_t WARN_STRING		[] = "[WARNN] ";
const PString_t INFO_STRING		[] = "[INFOR] ";
const PString_t DEBUG_STRING	[] = "[DEBUG] ";

inline Print& operator << (Print &obj, const LogType logtype) {
    switch (logtype) {
        case LogType::ERROR:
            Log << ERROR_STRING;
            break;
        case LogType::WARN:
            Log << WARN_STRING;
            break;
        case LogType::INFO:
            Log << INFO_STRING;
            break;
        case LogType::DEBUG:
            Log << DEBUG_STRING;
            break;
    }
    return obj;
}




#endif /* end of include guard: __DEBUG_H__ */
