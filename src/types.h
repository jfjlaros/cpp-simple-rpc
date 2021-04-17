#ifndef CPP_SIMPLE_RPC_TYPES_H_
#define CPP_SIMPLE_RPC_TYPES_H_

#include <string>

using std::string;

uint8_t rpcTypeOf(bool);
uint8_t rpcTypeOf(char);
uint8_t rpcTypeOf(int8_t);
uint8_t rpcTypeOf(uint8_t);
uint8_t rpcTypeOf(int16_t);
uint8_t rpcTypeOf(uint16_t);
uint8_t rpcTypeOf(int32_t);
uint8_t rpcTypeOf(uint32_t);
uint8_t rpcTypeOf(int64_t);
uint8_t rpcTypeOf(uint64_t);
uint8_t rpcTypeOf(float);
uint8_t rpcTypeOf(double);

#endif
