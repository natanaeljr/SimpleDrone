#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__
#include <WString.h>
#include <stdint.h>


// cast progmem-string to print on Serial
#define castF(pstr)    (__FlashStringHelper*) pstr

// empty a buffer with char null (max size: 255)
inline void empty_buffer(char * buffer, uint8_t size) {
    for(uint8_t i = 0; i < size && buffer[i] != '\0'; i++)
        buffer[i] = '\0';
}

// report the amount of free SRAM (space between the heap and the stack)
inline int free_ram() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// return the value constrained
template<typename type_t>
inline type_t constrainf(const type_t value, const type_t min, const type_t max) {
	if(value > max) return max;
    if(value < min) return min;
    return value;
}




#endif /* end of include guard: __FUNCTIONS_H__ */
