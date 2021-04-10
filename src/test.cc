#include <chrono>
#include <thread>
#include <iostream>  // Debug code.

#include "host.tcc"

#include "device.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::cout;     // Debug code.
using std::cin;      // Debug code.


int main(void) {
  bStream handle("/dev/ttyACM0");
  sleep_for(seconds(2));

  // Immediate values.
  handle.write('\x01');
  cout << call(handle, inc, (int16_t)2) << '\n';
  handle.write('\x01');
  cout << call(handle, inc, (int16_t)4) << '\n';
  handle.write('\x01');
  cout << call(handle, inc, (int16_t)8) << '\n';

  // Variables.
  handle.write('\x01');
  int16_t a = 1;
  cout << call(handle, inc, a) << '\n';

  // Void function.
  handle.write('\x02');
  call(handle, set_led, (uint8_t)63);

  return 0;
}
