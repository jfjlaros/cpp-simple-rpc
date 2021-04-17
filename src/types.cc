#include <unordered_map>

#include "types.h"

using std::unordered_map;

//! \defgroup types

unordered_map<char, char const*> _type = {
  {'?', "bool"}, {'c', "char"}, {'b', "int8_t"}, {'B', "uint8_t"},
  {'h', "int16_t"}, {'H', "uint16_t"}, {'i', "int32_t"}, {'I', "uint32_t"},
  {'l', "int32_t"}, {'L', "uint32_t"}, {'q', "int64_t"}, {'Q', "uint64_t"},
  {'f', "float"}, {'d', "double"}};


/*! \ingroup types
 * Type encoding.
 *
 * \param - Value.
 *
 * \return Python-struct encoded type.
 */
uint8_t rpcTypeOf(bool) {
  return '?';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(char) {
  return 'c';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(int8_t) {
  return 'b';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(uint8_t) {
  return 'B';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(int16_t) {
  return 'h';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(uint16_t) {
  return 'H';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(int32_t) {
  return 'l';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(uint32_t) {
  return 'L';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(int64_t) {
  return 'q';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(uint64_t) {
  return 'Q';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(float) {
  return 'f';
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
uint8_t rpcTypeOf(double) {
  return 'd';
}
