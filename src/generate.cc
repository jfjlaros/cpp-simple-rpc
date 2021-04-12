#include <iostream>
#include <vector>

#include "serial.h"
#include "simpleRPC.h"
#include "types.h"
#include "utils.h"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"

#define _LIST_REQ (uint8_t)0xff

using std::cout;


int main(void) {
  int fd = serialOpen("/dev/ttyACM0", 9600, 2);

  ioPut<char>(fd, _LIST_REQ);

  if (ioGet<string>(fd) != _PROTOCOL) {
    cout << "Error: missing protocol header\n";
    return 1;
  }
  for (uint8_t i = 0; i < 3; i++) {
    if (ioGet<char>(fd) != _VERSION[i]) {  // TODO: Semantic versioning.
      cout << "Error: version mismatch\n";
      return 2;
    }
  }
  string hardware = ioGet<string>(fd);

  string pointers;
  vector<string> methods;
  string line = ioGet<string>(fd);
  while (line.length()) {
    vector<string> v = split(line, ";");
    vector<string> signature = split(v[0], ":");
    string name = split(v[1], ":")[0];

    pointers += rpcTypeOf(signature[0]) + " (*" + name + ")(";
    methods.push_back('&' + name);

    vector<string> parameters = split(strip(signature[1], " "), " ");
    for (size_t i = 0; i < parameters.size(); i++) {
      pointers += rpcTypeOf(parameters[i]);
    }
    pointers += ");\n";

    line = ioGet<string>(fd);
  }

  cout << "#ifndef MY_PROJECT_DEVICE_H_\n"
       << "#define MY_PROJECT_DEVICE_H_\n\n"
       << "#include <tuple>\n"
       << "#include <vector>\n\n"
       << "using std::tuple;\n"
       << "using std::vector;\n\n"
       << pointers << "\n"
       << "char const _rpcEndianness = '" << hardware[0] << "';\n"
       << "char const _rpcSizeT = '" << hardware[1] << "';\n"
       << "void* _rpcMethod[] = {\n  "  << join(methods, ",\n  ") << "};\n\n"
       << "#endif\n";

  close(fd);

  return 0;
}
