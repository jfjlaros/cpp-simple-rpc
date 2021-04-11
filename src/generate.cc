#include <iostream>
#include <vector>

#include "serial.h"
#include "simpleRPC.h"

#define _PROTOCOL "simpleRPC"
#define _VERSION "\3\0\0"

#define _LIST_REQ (uint8_t)0xff

using std::cout;
using std::min;
using std::vector;


/*!
 * https://docs.python.org/3/library/struct.html
 */
char const* _typeOf(uint8_t type) {
  switch (type) {
    case '?':
      return "bool";
    case 'c':
      return "char";
    case 'b':
      return "int8_t";
    case 'B':
      return "uint8_t";
    case 'h':
      return "int16_t";
    case 'H':
      return "uint16_t";
    case 'i':
      return "int32_t";
    case 'I':
      return "uint32_t";
    case 'l':
      return "int32_t";
    case 'L':
      return "uint32_t";
    case 'q':
      return "int64_t";
    case 'Q':
      return "uint64_t";
    case 'f':
      return "float";
    case 'd':
      return "double";
  }
  return "void";
}

string rpcTypeOf(string s, bool cat) {
  if (!s.length()) {
    if (cat) {
      return "";
    }
    return "void";
  }

  string spacer;
  if (cat) {
    spacer += ", ";
  }

  switch (s[0]) {
    case '(':
      return spacer + "object<" + rpcTypeOf(s.substr(1, string::npos), false);
    case '[':
      return spacer + "vector<" + rpcTypeOf(s.substr(1, string::npos), false);
    case ')':
    case ']':
      return " >" + rpcTypeOf(s.substr(1, string::npos), cat);
  }
  return spacer + _typeOf(s[0]) + rpcTypeOf(s.substr(1, string::npos), true);
}


vector<string> split(string const& s, string const& token) {
  vector<string> v;
  size_t start = 0;
  size_t end = s.find(token);

  while (end != string::npos) {
    v.push_back(s.substr(start, end - start));
    start = end + token.length();
    end = s.find(token, start);
  }
  v.push_back(s.substr(start, string::npos));

  return v;
}

string join(vector<string>& v, string const& spacer) {
  string s = v[0];

  for (size_t i = 1; i < v.size(); i++) {
    s += spacer + v[i];
  }

  return s;
}

string trim(string const& s, string const& token) {
  string s_ = s;
  while (!s_.find(token)) {
    s_ = s_.substr(token.length(), string::npos);
  }
  // TODO: Trim end.

  return s_;
}


template <class R>
R ioGet(int fd) {
  R data;
  ioRead(fd, &data);
  return data;
}

template <class T>
void ioPut(int fd, T const& data) {
  ioWrite(fd, &data);
}


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

  cout << "// Hardware: " << ioGet<string>(fd) << '\n';

  string pointers;
  vector<string> methods;
  string line = ioGet<string>(fd);
  while (line.length()) {
    vector<string> v = split(line, ";");
    vector<string> signature = split(v[0], ":");
    string name = split(v[1], ":")[0];

    pointers += rpcTypeOf(signature[0], false) + " (*" + name + ")(";
    methods.push_back(name);

    vector<string> parameters = split(trim(signature[1], " "), " ");
    for (size_t i = 0; i < parameters.size(); i++) {
      pointers += rpcTypeOf(parameters[i], false);
    }
    pointers += ");\n";

    line = ioGet<string>(fd);
  }

  cout << pointers << '\n';
  cout << "void* _rpcMethod[] = {\n  "  << join(methods, ",\n  ") << "};\n";

  close(fd);

  return 0;
}
