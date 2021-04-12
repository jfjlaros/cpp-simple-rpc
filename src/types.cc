#include "types.h"

//! \defgroup types


/*! \ingroup types
 * See: https://docs.python.org/3/library/struct.html
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

/*! \ingroup types
 */
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
