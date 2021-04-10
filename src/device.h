#ifndef CPP_SIMPLE_RPC_DEVICE_H_
#define CPP_SIMPLE_RPC_DEVICE_H_

uint8_t (*ping)(uint8_t);
int16_t (*inc)(int16_t);
void (*set_led)(uint8_t);
uint32_t (*milli_time)(void);
//Object<char, Object<int, char> > (*o)(Object<char, Object<int, char> >&);
//Vector<float> (*vector)(Vector<int>);
//Vector<float> (*c_vector)(Vector<int>);
//int (*add)(int, int);

void* _rpcMethod[] = {
  &ping,
  &inc,
  &set_led,
  &milli_time};

#endif
