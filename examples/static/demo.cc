#include <cstring>
#include <iostream>

#include <simpleRPC.h>

#include "device.h"

using std::cerr;
using std::cout;


int main(void) {
  int fd = serialOpen(DEVICE, BAUDRATE, WAIT);
  if (fd == -1) {
    cerr << "Error: " << strerror(errno) << '\n';
    return errno;
  }

  // Pass immediate values.
  cout << call(fd, methods::inc, 2) << ' '
       << call(fd, methods::inc, 4) << ' '
       << call(fd, methods::inc, 8) << ' ';

  // Pass a variable.
  int16_t a = 1;
  cout << call(fd, methods::inc, a) << '\n';

  // Call a void function.
  call(fd, methods::set_led, 63);

  close(fd);

  return 0;
}
