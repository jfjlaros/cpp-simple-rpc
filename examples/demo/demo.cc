#include <cstring>
#include <iostream>

#include <simpleRPC.h>

using std::cout;


int main(int argc, char** argv) {
  int fd = serialOpen("/dev/ttyACM0", 9600, 1);
  if (fd == -1) {
    perror("Error");
    return errno;
  }
  Interface interface(fd);
  if (!(interface.status & STATUS_INITIALISED)) {
    return interface.status;
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

  // Call a void function, show type conversion warning.
  interface.call("set_led", 3);
  if (interface.status & STATUS_PARAM_TYPE_WARNING) {
    cout << "Warning: a parameter type conversion occurred" << '\n';
  }

  // Call a void function so that no type conversion warning occurs.
  interface.call("set_led", (uint8_t)3);
  if (interface.status & STATUS_PARAM_TYPE_WARNING) {
    cout << "Warning: a parameter type conversion occurred" << '\n';
  }

  close(fd);

  return 0;
}
