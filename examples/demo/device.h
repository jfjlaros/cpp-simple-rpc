#ifndef MY_PROJECT_DEVICE_H_
#define MY_PROJECT_DEVICE_H_
/*
 * To update your project, remove this file and run `make`.
 */

#define DEVICE "/dev/ttyACM0"
#define BAUDRATE 9600
#define WAIT 2

namespace methods {
  uint8_t (*ping)(uint8_t);
  int16_t (*inc)(int16_t);
  void (*set_led)(uint8_t);
  uint32_t (*milli_time)(void);
  tuple<char, tuple<int16_t, char > > (*object)(tuple<char, tuple<int16_t, char > >);
  vector<float > (*cpp_vector)(vector<int16_t >);
  vector<float > (*c_vector)(vector<int16_t >);
}

char const _rpcEndianness = '<';
char const _rpcSizeT = 'H';
void* _rpcMethod[] = {
  &methods::ping,
  &methods::inc,
  &methods::set_led,
  &methods::milli_time,
  &methods::object,
  &methods::cpp_vector,
  &methods::c_vector};

#endif
