inline void _call(int, vector<string>) {}

template <class T, class... Args>
void _call(int fd, vector<string> types, T const& val, Args const&... args) {
  ioWrite(fd, &val, types.front()[0]);
  types.erase(types.begin());
  _call(fd, types, args...);
}

/*
template <class... Args>
void call(int fd, vector<string> types, Args const&... args) {
  _call(fd, types, args...);
}

template <class R, class... Args>
R call(int fd, vector<string> types, Args const&... args) {
  _call(fd, types, args...);

  R data;
  ioRead(fd, &data);

  return data;
}
*/
