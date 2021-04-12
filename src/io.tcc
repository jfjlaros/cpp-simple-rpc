#ifndef CPP_SIMPLE_RPC_IO_TCC_
#define CPP_SIMPLE_RPC_IO_TCC_

#include <string>
#include <tuple>
#include <vector>

#include <unistd.h>

using std::string;
using std::tuple;
using std::vector;


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
