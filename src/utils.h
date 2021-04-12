#ifndef CPP_SIMPLE_RPC_UTILS_H_
#define CPP_SIMPLE_RPC_UTILS_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> split(string const&, string const&);
string join(vector<string>&, string const&);
string trim(string const&, string const&);

#endif
