#ifndef CPP_SIMPLE_RPC_IO_TCC_
#define CPP_SIMPLE_RPC_IO_TCC_

#include <cstdio>

//! \defgroup io

/*! \ingroup io
 * Binary blocking input / output stream.
 */
class bStream {
  public:
    bStream(void) {}
    bStream(char const*);
    void open(char const*);
    void close(void);
    template <class R>
    R read(void);
    template <class T>
    void write(T);
  private:
    FILE* _handle;
};


/*!
 * Create a binary blocking input / output stream.
 *
 * \param name File name.
 */
bStream::bStream(char const* name) {
  open(name);
}

/*!
 * Open a binary blocking input / output stream.
 *
 * \param name File name.
 */
void bStream::open(char const* name) {
  _handle = fopen(name, "ab+");
  setbuf(_handle, NULL);
}

/*!
 * Close a binary blocking input / output stream.
 *
 * \param name File name.
 */
void bStream::close(void) {
  fclose(_handle);
}

/*!
 * Read from a binary blocking input / output stream.
 *
 * \return Data.
 */
template <class R>
R bStream::read(void) {
  R data;

  fread((void*)&data, sizeof(R), 1, _handle);
  return data;
}

/*!
 * Write to a binary blocking input / output stream.
 *
 * \param data Data.
 */
template <class T>
void bStream::write(T const data) {
  fwrite((void*)&data, sizeof(T), 1, _handle);
}

#endif
