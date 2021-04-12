#include "utils.h"

//! \defgroup utils


/*! \ingroup utils
 */
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

/*! \ingroup utils
 */
string join(vector<string>& v, string const& spacer) {
  string s = v[0];

  for (size_t i = 1; i < v.size(); i++) {
    s += spacer + v[i];
  }

  return s;
}

/*! \ingroup utils
 */
string trim(string const& s, string const& token) {
  string s_ = s;

  while (!s_.find(token)) {
    s_ = s_.substr(token.length(), string::npos);
  }
  // TODO: Trim end.

  return s_;
}
