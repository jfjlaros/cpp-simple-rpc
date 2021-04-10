#include <chrono>
#include <ios>
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

  handle.write('\x01');
  cout << call(handle, inc, (int16_t)2) << '\n';
  handle.write('\x01');
  cout << call(handle, inc, (int16_t)4) << '\n';
  handle.write('\x01');
  cout << call(handle, inc, (int16_t)8) << '\n';
  /*
  printf("%i\n", call(add, 2, 3));
  call(set_led, 10);

  int a = 1;
  printf("%i\n", call(inc, a));
  */

  return 0;
}
