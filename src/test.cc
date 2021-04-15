#include "dynamic.tcc"


int main(int argc, char** argv) {
  Interface interface("/dev/ttyACM0", 9600, 1);

  cout << interface.call<int16_t>("inc", 3) << '\n';

  int16_t result;
  interface.call(result, "inc", 4);
  cout << result << '\n';

  interface.call("set_led", 3);

  return 0;
}
