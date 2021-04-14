#include <iostream>

#include "io.tcc"

#include "serial.h"
#include "utils.h"

#include "call.tcc"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"

#define _LIST_REQ (uint8_t)0xff

using std::cout;
using std::get;


class Interface {
  public:
    Interface(void) {}
    Interface(char const*, speed_t, uint8_t);
    ~Interface(void);
    void open(char const*, speed_t, uint8_t);
    template <class R, class... Args>
    R call(char const*, Args...);
    template <class... Args>
    void call(char const*, Args...);
  private:
    int _fd;
    uint8_t _endianness;
    uint8_t _sizeT;
    unordered_map<string, tuple<uint8_t, string, vector<string>, string>> _map;
};


Interface::Interface(char const* device, speed_t baudrate, uint8_t wait) {
  open(device, baudrate, wait);
}

Interface::~Interface(void) {
  close(_fd);
}

void Interface::open(char const* device, speed_t baudrate, uint8_t wait) {
  _fd = serialOpen(device, baudrate, wait);

  ioPut<char>(_fd, _LIST_REQ);

  if (ioGet<string>(_fd) != _PROTOCOL) {
    cout << "Error: missing protocol header\n";
  }
  for (uint8_t i = 0; i < 3; i++) {
    // TODO: Semantic versioning.
    if (ioGet<char>(_fd) != _VERSION[i]) {
      cout << "Error: version mismatch\n";
    }
  }
  string line = ioGet<string>(_fd);
  _endianness = line[0];
  _sizeT = line[1];

  uint8_t index = 0;
  line = ioGet<string>(_fd);
  while (line.length()) {
    _map.insert({
      split(split(line, ";")[1], ":")[0],
      tuple<uint8_t, string, vector<string>, string> {
        index,
        split(split(line, ";")[0], ":")[0],
        split(strip(split(split(line, ";")[0], ":", 1)[1], " "), " "),
        strip(split(split(line, ";")[1], ":", 1)[1], " ")}});

    line = ioGet<string>(_fd);
    index++;
  }
}

template <class... Args>
void Interface::call(char const* cmd, Args... args) {
  ioWrite(_fd, &get<0>(_map[cmd]), 'B');
  _call(_fd, get<2>(_map[cmd]), args...);
}

template <class R, class... Args>
R Interface::call(char const* cmd, Args... args) {
  call(cmd, args...);
  R data;
  ioRead(_fd, &data);
  return data;
}


int main(int argc, char** argv) {
  Interface interface("/dev/ttyACM0", 9600, 1);

  cout << interface.call<int16_t>("inc", 3) << '\n';
  interface.call("set_led", 3);

  return 0;
}
