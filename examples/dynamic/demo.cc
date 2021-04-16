#include <cstring>
#include <iostream>

#include "serial.h"
#include "dynamic.tcc"

using std::cerr;
using std::cout;


int main(int argc, char** argv) {
  int fd = serialOpen("/dev/ttyACM0", 9600, 1);
  if (fd == -1) {
    cerr << "Error: " << strerror(errno) << '\n';
    return errno;
  }
  Interface interface(fd);
  if (!interface.ready) {
    cerr << "Error: " << strerror(errno) << '\n';
    return errno;
  }

  // Pass immediate values, specify return type.
  cout << interface.call<int16_t>("inc", 2) << ' '
       << interface.call<int16_t>("inc", 4) << ' ';

  // Pass an immediate value, pass result variable by reference.
  int16_t result;
  interface.call(result, "inc", 8);
  cout << result << ' ';

  // Pass a variable.
  int16_t a = 1;
  cout << interface.call<int16_t>("inc", a) << '\n';

  // Call a void function.
  interface.call("set_led", 3);

  close(fd);

  return 0;
}
