#ifndef __TYPES_H__
#define __TYPES_H__
#include <avr/pgmspace.h>


// type to create a string in PROGMEM -> must use with [] to define
using PString_t = PROGMEM char;
// pointer to a string in PROGMEM -> may use with PSTR("string")
using PStringPtr_t = const char*; // = PGM_P


// pointer to a method inside a class // 4bytes
template<class class_t>
using methodptr_t = void(class_t::*)(void); // member function pointer













#endif /* end of include guard: __TYPES_H__ */
