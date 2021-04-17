#include "utils.h"

#include "dynamic.tcc"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"
#define _LIST_REQ (uint8_t)0xff

unordered_map<char, int> _rpcTypeSize = {
  {'c', 1}, {'b', 1}, {'B', 1}, {'?', 1}, {'h', 2}, {'H', 2}, {'i', 4},
  {'I', 4}, {'l', 4}, {'L', 4}, {'q', 8}, {'Q', 8}, {'e', 2}, {'f', 4},
  {'d', 8}};


/*!
 * Create a simpleRPC interface.
 *
 * \param fd File descriptor.
 */
Interface::Interface(int fd) {
  open(fd);
}

//! Destructor.
Interface::~Interface(void) {
  close();
}

/*!
 * Initialise the interface.
 *
 * When the initialisation fails, the following `status` flags may be updated:
 * - `STATUS_PROTOCOL_ERROR` when the Arduino response is malformed.
 * - `STATUS_PROTOCOL_VERSION_ERROR` when a version mismatch has occurred.
 *
 * \param fd File descriptor.
 */
void Interface::open(int fd) {
  _fd = fd;

  put<char>(_LIST_REQ);

  status &= ~(STATUS_PROTOCOL_ERROR | STATUS_PROTOCOL_VERSION_ERROR);
  if (get<string>() != _PROTOCOL) {
    status |= STATUS_PROTOCOL_ERROR;
    return;
  }
  for (uint8_t i = 0; i < 3; i++) {
    // TODO: Semantic versioning.
    if (get<char>() != _VERSION[i]) {
      status |= STATUS_PROTOCOL_VERSION_ERROR;
      return;
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
  status |= STATUS_INITIALISED;
}

/*!
 * Deconfigure the interface.
 */
void Interface::close(void) {
  ::close(_fd);
  status &= ~STATUS_INITIALISED;
}

/*!
 */
void Interface::read(string* data) {
  uint8_t c;
  read(&c);
  while (c) {
    *data += c;
    read(&c);
  }
}
