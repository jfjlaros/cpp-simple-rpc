#ifndef CPP_SIMPLE_RPC_IO_TCC_
#define CPP_SIMPLE_RPC_IO_TCC_

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <unistd.h>

using std::string;
using std::tuple;
using std::vector;
using std::unordered_map;

/*
 * Format | C Type             | Python type       | Standard size
 * -------+--------------------+-------------------+--------------
 *      x | pad byte           | no value          |
 *      c | char               | bytes of length 1 | 1
 *      b | signed char        | integer           | 1
 *      B | unsigned char      | integer           | 1
 *      ? | _Bool              | bool              | 1
 *      h | short              | integer           | 2
 *      H | unsigned short     | integer           | 2
 *      i | int                | integer           | 4
 *      I | unsigned int       | integer           | 4
 *      l | long               | integer           | 4
 *      L | unsigned long      | integer           | 4
 *      q | long long          | integer           | 8
 *      Q | unsigned long long | integer           | 8
 *      n | ssize_t            | integer           |
 *      N | size_t             | integer           |
 *      e |                    | float             | 2
 *      f | float              | float             | 4
 *      d | double             | float             | 8
 *      s | char[]             | bytes             |
 *      p | char[]             | bytes             |
 *      P | void *             | integer           |
 */
unordered_map<char, int> _rpcTypeSize = {
  {'c', 1}, {'b', 1}, {'B', 1}, {'?', 1}, {'h', 2}, {'H', 2}, {'i', 4},
  {'I', 4}, {'l', 4}, {'L', 4}, {'q', 8}, {'Q', 8}, {'e', 2}, {'f', 4},
  {'d', 8}};


//! \defgroup io


/*! \ingroup io
 * Read from a file descriptor.
 *
 * \param fd File descriptor.
 *
 * \return Data.
 */
template <class T>
void ioRead(int fd, T* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    read(fd, &((uint8_t*)data)[i], 1);
  }
}

/*! \ingroup io
 * \copydoc ioRead(int) */
inline void ioRead(int fd, string* data) {
  uint8_t c;
  ioRead(fd, &c);
  while (c) {
    *data += c;
    ioRead(fd, &c);
  }
}


/*! \ingroup io
 * Write to a file descriptor.
 *
 * \param fd File descriptor.
 * \param data Data.
 */
template <class T>
void ioWrite(int fd, T const* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    write(fd, &((uint8_t*)data)[i], 1);
  }
}

template <class T>
void ioWrite(int fd, T* data, char type) {
  for (uint8_t i = 0; i < _rpcTypeSize[type]; i++) {
    write(fd, &((uint8_t*)data)[i], 1);
  }
}


/*! \ingroup io
 * Convenience function for reading data.
 *
 * \param fd File descriptor.
 *
 * \return Data.
 */
template <class R>
R ioGet(int fd) {
  R data;
  ioRead(fd, &data);
  return data;
}

/*! \ingroup io
 * Convenience function for writing data.
 *
 * \param fd File descriptor.
 * \param data Data.
 */
template <class T>
void ioPut(int fd, T const& data) {
  ioWrite(fd, &data);
}

#endif
