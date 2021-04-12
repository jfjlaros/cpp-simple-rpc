#include <iostream>

#include <serial.h>
#include <simpleRPC.h>

#include "device.h"

using std::cout;


int main(void) {
  int fd = serialOpen("/dev/ttyACM0", 9600, 2);

  for (int i = 0; i < 10; i++) {
    // Immediate values.
    cout << call(fd, inc, 2) << ' ';
    cout << call(fd, inc, 4) << ' ';
    cout << call(fd, inc, 8) << ' ';

    // Variables.
    int16_t a = 1;
    cout << call(fd, inc, a) << '\n';

    // Void function.
    call(fd, set_led, 63);
  }

  close(fd);

  return 0;
}
