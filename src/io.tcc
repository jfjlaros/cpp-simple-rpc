#ifndef CPP_SIMPLE_RPC_IO_TCC_
#define CPP_SIMPLE_RPC_IO_TCC_

#include <unistd.h>

//! \defgroup io


/*! \ingroup io
 * Read from a file descriptor.
 *
 * \param fd File descriptor.
 *
 * \return Data.
 */
template <class R>
R ioRead(int fd) {
  R data;

  for (uint8_t i = 0; i < sizeof(R); i++) {
    read(fd, &((uint8_t*)&data)[i], 1);
  }
  return data;
}

/*! \ingroup io
 * Write to a file descriptor.
 *
 * \param fd File descriptor.
 * \param data Data.
 */
template <class T>
void ioWrite(int fd, T const data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    write(fd, &((uint8_t*)&data)[i], 1);
  }
}

#endif
