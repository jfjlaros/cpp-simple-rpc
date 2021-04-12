#include <cstring>
#include <iostream>
#include <thread>

#include <fcntl.h>

#include "serial.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::cout;

//! \defgroup serial


/*! \ingroup serial
 * Open and configure a serial device.
 *
 * \param device Device name.
 * \param baudrate Baud rate.
 * \param wait Time before communication starts.
 *
 * \return File descriptor. 
 */
int serialOpen(char const* device, speed_t baudrate, uint8_t wait) {
  int fd = open(device, O_RDWR| O_NOCTTY);

  termios tty;
  if (tcgetattr(fd, &tty)) {
     cout << "Error: " << strerror(errno) << '\n';
     return -1;
  }

  cfsetospeed(&tty, baudrate);
  cfsetispeed(&tty, baudrate);

  tty.c_cflag = CLOCAL | CREAD | CRTSCTS | CS8 | CSIZE | CSTOPB | PARENB;
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 0;

  cfmakeraw(&tty);

  if (tcsetattr(fd, TCSANOW, &tty)) {
     cout << "Error: " << strerror(errno) << '\n';
     return -1;
  }

  sleep_for(seconds(wait));

  return fd;
}
