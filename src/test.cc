#include <cstring>
#include <iostream>
#include <thread>

#include <fcntl.h>
#include <termios.h>

#include "rpcCall.tcc"

#include "device.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::cout;


int main(void) {
  int fd = open("/dev/ttyACM0", O_RDWR| O_NOCTTY);

  termios tty;
  if (tcgetattr(fd, &tty)) {
     cout << "Error: " << strerror(errno) << '\n';
  }

  cfsetospeed(&tty, (speed_t)B9600);
  cfsetispeed(&tty, (speed_t)B9600);

  tty.c_cflag = CLOCAL | CREAD | CRTSCTS | CS8 | CSIZE | CSTOPB | PARENB;
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 0;

  cfmakeraw(&tty);

  if (tcsetattr(fd, TCSANOW, &tty)) {
     cout << "Error: " << strerror(errno) << '\n';
  }

  sleep_for(seconds(2));

  // Demo begins here.
  for (int i = 0; i < 10; i++) {
    // Immediate values.
    cout << call(fd, inc, (int16_t)2) << ' ';
    cout << call(fd, inc, (int16_t)4) << ' ';
    cout << call(fd, inc, (int16_t)8) << ' ';

    // Variables.
    int16_t a = 1;
    cout << call(fd, inc, a) << '\n';

    // Void function.
    call(fd, set_led, (uint8_t)63);
  }

  close(fd);

  return 0;
}
