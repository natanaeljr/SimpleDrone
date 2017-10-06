#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include <Module.h>


// CN_READ_TIMEOUT custom timeout for read Serial incomings (to be quicker as possible)
// in microseconds. Must be greater than 250ms (for 38400 baudrate)
#define CN_READ_TIMEOUT 260
#define CN_RXBUFFER_SIZE 64


class Console_t : public Module_t {
private:
	uint8_t receive(char * rxbuffer);
	void translate(char * buffer);
public:
	void check_input();
	void debug();
	void init() override;
	Console_t();
};

extern Console_t Console;




#endif /* end of include guard: __CONSOLE_H__ */
