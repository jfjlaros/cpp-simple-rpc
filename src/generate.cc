#include <iostream>

#include "simpleRPC.h"
#include "types.h"
#include "utils.h"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"

#define _LIST_REQ (uint8_t)0xff

using std::cout;


int main(int argc, char** argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " device baudrate wait\n";
    return 1;
  }

  int fd = serialOpen(argv[1], atoi(argv[2]), atoi(argv[3]));

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

  vector<string> pointers;
  vector<string> methods;
  string line = ioGet<string>(fd);
  while (line.length()) {
    vector<string> v = split(line, ";");
    vector<string> signature = split(v[0], ":");
    string name = split(v[1], ":")[0];

    string pointer = rpcTypeOf(signature[0]) + " (*" + name + ")(";
    methods.push_back("&methods::" + name);

    vector<string> parameters = split(strip(signature[1], " "), " ");
    for (size_t i = 0; i < parameters.size(); i++) {
      pointer += rpcTypeOf(parameters[i]);
    }
    pointer += ")";
    pointers.push_back(pointer);

    line = ioGet<string>(fd);
  }

  cout << "#ifndef MY_PROJECT_DEVICE_H_\n"
       << "#define MY_PROJECT_DEVICE_H_\n"
       << "/*\n"
       << " * To update your project, remove this file and run `make`.\n"
       << " */\n\n"
       << "#define DEVICE \"" << argv[1] << "\"\n"
       << "#define BAUDRATE " << argv[2] << "\n"
       << "#define WAIT " << argv[3] << "\n\n"
       << "namespace methods {\n"
       << "  " << join(pointers, ";\n  ") << ";\n"
       << "}\n\n"
       << "char const _rpcEndianness = '" << hardware[0] << "';\n"
       << "char const _rpcSizeT = '" << hardware[1] << "';\n"
       << "void* _rpcMethod[] = {\n  "  << join(methods, ",\n  ") << "};\n\n"
       << "#endif\n";

  close(fd);

  return 0;
}
