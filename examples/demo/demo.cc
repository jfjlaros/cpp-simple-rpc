#include <iostream>

#include <simpleRPC.h>

#include "device.h"

using std::cout;


int main(void) {
  int fd = serialOpen(DEVICE, BAUDRATE, WAIT);

  for (int i = 0; i < 10; i++) {
    // Immediate values.
    cout << call(fd, methods::inc, 2) << ' '
         << call(fd, methods::inc, 4) << ' '
         << call(fd, methods::inc, 8) << ' ';

    // Variables.
    int16_t a = 1;
    cout << call(fd, methods::inc, a) << '\n';

    // Void function.
    call(fd, methods::set_led, 63);
  }

  close(fd);

  return 0;
}
