#ifndef CPP_SIMPLE_RPC_DYNAMIC_TCC_
#define CPP_SIMPLE_RPC_DYNAMIC_TCC_

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <unistd.h>

using std::get;
using std::string;
using std::tuple;
using std::unordered_map;
using std::vector;

extern unordered_map<char, int> _rpcTypeSize;

//! \defgroup interface

/*! \ingroup interface
 */
class Interface {
  public:
    Interface(void) {}
    Interface(int);
    ~Interface(void);
    void open(int);
    void close(void);
    template <class T>
      void read(T*);
    void read(string*);
    template <class T>
      void write(T*);
    template <class T>
      void write(T*, char);
    template <class R>
      R get(void);
    template <class T>
      void put(T const&);
    template <class R, class... Args>
      void call(R&, char const*, Args...);
    template <class R, class... Args>
      R call(char const*, Args...);
    template <class... Args>
      void call(char const*, Args...);
    bool ready = false;  //!< Initialisation status.
  private:
    inline void _call(vector<string>) {}
    template <class T, class... Args>
      void _call(vector<string>, T const&, Args const&...);
    int _fd;
    uint8_t _endianness;
    uint8_t _sizeT;
    unordered_map<string, tuple<uint8_t, string, vector<string>, string>> _map;
};


/*!
 */
template <class T>
void Interface::read(T* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    ::read(_fd, &((uint8_t*)data)[i], 1);
  }
}

/*!
 */
template <class T>
void Interface::write(T* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    ::write(_fd, &((uint8_t*)data)[i], 1);
  }
}

/*!
 */
template <class T>
void Interface::write(T* data, char type) {
  for (uint8_t i = 0; i < _rpcTypeSize[type]; i++) {
    ::write(_fd, &((uint8_t*)data)[i], 1);
  }
}

/*!
 */
template <class R>
R Interface::get(void) {
  R data;
  read(&data);
  return data;
}

/*!
 */
template <class T>
void Interface::put(T const& data) {
  write(&data);
}

template <class T, class... Args>
void Interface::_call(vector<string> sig, T const& val, Args const&... args) {
  write(&val, sig.front()[0]);
  sig.erase(sig.begin());
  _call(sig, args...);
}

/*!
 */
template <class... Args>
void Interface::call(char const* cmd, Args... args) {
  write(&::get<0>(_map[cmd]), 'B');
  _call(::get<2>(_map[cmd]), args...);
}

/*!
 */
template <class R, class... Args>
void Interface::call(R& data, char const* cmd, Args... args) {
  call(cmd, args...);
  read(&data);
}

/*!
 */
template <class R, class... Args>
R Interface::call(char const* cmd, Args... args) {
  R data;
  call(data, cmd, args...);
  return data;
}

#endif
