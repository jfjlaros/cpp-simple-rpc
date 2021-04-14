#include "utils.h"

//! \defgroup utils


/*! \ingroup utils
 * Split a string.
 *
 * \param s String.
 * \param sep Separator.
 *
 * \return Vector of substrings.
 */
vector<string> split(string const& s, string const& sep, size_t max) {
  vector<string> v;
  size_t start = 0;
  size_t end = s.find(sep);

  for (size_t i = 0; i < max && end != string::npos; i++) {
    v.push_back(s.substr(start, end - start));
    start = end + sep.length();
    end = s.find(sep, start);
  }
  v.push_back(s.substr(start, string::npos));

  return v;
}

/*! \ingroup utils
 * Concatenate a vector of strings using `sep` as a separator.
 *
 * \param v Vector of strings.
 * \param sep Separator.
 *
 * \return Concatenated string.
 */
string join(vector<string>& v, string const& sep) {
  string s = v[0];

  for (size_t i = 1; i < v.size(); i++) {
    s += sep + v[i];
  }

  return s;
}

/*! \ingroup utils
 * Remove leading and trailing characters.
 *
 * \param s String.
 * \param chars Characters to remove.
 *
 * \return Stripped string.
 */
string strip(string const& s, string const& chars) {
  string s_ = s;

  while (!s_.find(chars)) {
    s_ = s_.substr(chars.length(), string::npos);
  }
  // TODO: Strip end.

  return s_;
}
