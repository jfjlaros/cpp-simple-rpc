#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <iostream>

#include <unistd.h>

#include "serial.h"
#include "utils.h"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"

#define _LIST_REQ (uint8_t)0xff

using std::string;
using std::tuple;
using std::vector;
using std::unordered_map;

using std::cout;
using std::get;

unordered_map<char, int> _rpcTypeSize = {
  {'c', 1}, {'b', 1}, {'B', 1}, {'?', 1}, {'h', 2}, {'H', 2}, {'i', 4},
  {'I', 4}, {'l', 4}, {'L', 4}, {'q', 8}, {'Q', 8}, {'e', 2}, {'f', 4},
  {'d', 8}};

class Interface {
  public:
    Interface(void) {}
    Interface(char const*, speed_t, uint8_t);
    ~Interface(void);
    void open(char const*, speed_t, uint8_t);
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
  private:
    inline void _call(vector<string>) {}
    template <class T, class... Args>
      void _call(vector<string>, T const&, Args const&...);
    int _fd;
    uint8_t _endianness;
    uint8_t _sizeT;
    unordered_map<string, tuple<uint8_t, string, vector<string>, string>> _map;
};


Interface::Interface(char const* device, speed_t baudrate, uint8_t wait) {
  open(device, baudrate, wait);
}

Interface::~Interface(void) {
  close();
}

template <class T>
void Interface::read(T* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    ::read(_fd, &((uint8_t*)data)[i], 1);
  }
}

void Interface::read(string* data) {
  uint8_t c;
  read(&c);
  while (c) {
    *data += c;
    read(&c);
  }
}

template <class T>
void Interface::write(T* data) {
  for (uint8_t i = 0; i < sizeof(T); i++) {
    ::write(_fd, &((uint8_t*)data)[i], 1);
  }
}

template <class T>
void Interface::write(T* data, char type) {
  for (uint8_t i = 0; i < _rpcTypeSize[type]; i++) {
    ::write(_fd, &((uint8_t*)data)[i], 1);
  }
}

template <class R>
R Interface::get(void) {
  R data;
  read(&data);
  return data;
}

template <class T>
void Interface::put(T const& data) {
  write(&data);
}

void Interface::open(char const* device, speed_t baudrate, uint8_t wait) {
  _fd = serialOpen(device, baudrate, wait);

  put<char>(_LIST_REQ);

  if (get<string>() != _PROTOCOL) {
    cout << "Error: missing protocol header\n";
  }
  for (uint8_t i = 0; i < 3; i++) {
    // TODO: Semantic versioning.
    if (get<char>() != _VERSION[i]) {
      cout << "Error: version mismatch\n";
    }
  }
  string line = get<string>();
  _endianness = line[0];
  _sizeT = line[1];

  uint8_t index = 0;
  line = get<string>();
  while (line.length()) {
    _map.insert({
      split(split(line, ";")[1], ":")[0],
      tuple<uint8_t, string, vector<string>, string> {
        index,
        split(split(line, ";")[0], ":")[0],
        split(strip(split(split(line, ";")[0], ":", 1)[1], " "), " "),
        strip(split(split(line, ";")[1], ":", 1)[1], " ")}});

    line = get<string>();
    index++;
  }
}

void Interface::close(void) {
  ::close(_fd);
}

template <class T, class... Args>
void Interface::_call(vector<string> sig, T const& val, Args const&... args) {
  write(&val, sig.front()[0]);
  sig.erase(sig.begin());
  _call(sig, args...);
}

template <class... Args>
void Interface::call(char const* cmd, Args... args) {
  write(&::get<0>(_map[cmd]), 'B');
  _call(::get<2>(_map[cmd]), args...);
}

template <class R, class... Args>
void Interface::call(R& data, char const* cmd, Args... args) {
  call(cmd, args...);
  read(&data);
}

template <class R, class... Args>
R Interface::call(char const* cmd, Args... args) {
  R data;
  call(data, cmd, args...);
  return data;
}
