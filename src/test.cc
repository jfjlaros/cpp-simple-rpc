#include <chrono>
#include <thread>
#include <iostream>  // Debug code.

#include "rpcCall.tcc"

#include "device.h"

using std::chrono::seconds;
using std::this_thread::sleep_for;
using std::cout;     // Debug code.
using std::cin;      // Debug code.


int main(void) {
  bStream handle("/dev/ttyACM0");
  sleep_for(seconds(2));

  // Immediate values.
  cout << call(handle, inc, 2) << '\n';
  cout << call(handle, inc, 4) << '\n';
  cout << call(handle, inc, 8) << '\n';

  // Variables.
  int16_t a = 1;
  cout << call(handle, inc, a) << '\n';

  // Void function.
  call(handle, set_led, 63);

  return 0;
}
