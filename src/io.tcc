#ifndef CPP_SIMPLE_RPC_IO_TCC
#define CPP_SIMPLE_RPC_IO_TCC

#include <cstdio>

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


bStream::bStream(char const* name) {
  open(name);
}

void bStream::open(char const* name) {
  _handle = fopen(name, "ab+");
  setbuf(_handle, NULL);
}

void bStream::close(void) {
  fclose(_handle);
}

template <class R>
R bStream::read(void) {
  R data;

  fread((void*)&data, sizeof(R), 1, _handle);
  return data;
}

template <class T>
void bStream::write(T const data) {
  fwrite((void*)&data, sizeof(T), 1, _handle);
}

#endif
