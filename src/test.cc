#include <stdio.h>
#include "host.tcc"

#include "device.h"


int main(void) {
  printf("%i\n", call(inc, 2));
  printf("%i\n", call(add, 2, 3));
  call(set_led, 10);

  int a = 1;
  printf("%i\n", call(inc, a));

  return 0;
}
