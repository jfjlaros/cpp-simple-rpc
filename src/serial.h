#ifndef CPP_SIMPLE_RPC_SERIAL_H_
#define CPP_SIMPLE_RPC_SERIAL_H_

#include <termios.h>
#include <unistd.h>

int serialOpen(char const*, speed_t, uint8_t);

#endif
