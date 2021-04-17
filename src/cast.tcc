#ifndef CPP_SIMPLE_RPC_CAST_TCC_
#define CPP_SIMPLE_RPC_CAST_TCC_

using std::enable_if;


template <char t, class T>
typename enable_if<t == '?', bool>::type cast(T const& data) {
  return (bool)data;
}

template <char t, class T>
typename enable_if<t == 'c', char>::type cast(T const& data) {
  return (char)data;
}

template <char t, class T>
typename enable_if<t == 'b', int8_t>::type cast(T const& data) {
  return (int8_t)data;
}

template <char t, class T>
typename enable_if<t == 'B', uint8_t>::type cast(T const& data) {
  return (uint8_t)data;
}

template <char t, class T>
typename enable_if<t == 'h', int16_t>::type cast(T const& data) {
  return (int16_t)data;
}

template <char t, class T>
typename enable_if<t == 'H', uint16_t>::type cast(T const& data) {
  return (uint16_t)data;
}

template <char t, class T>
typename enable_if<t == 'i', int32_t>::type cast(T const& data) {
  return (int32_t)data;
}

template <char t, class T>
typename enable_if<t == 'I', uint32_t>::type cast(T const& data) {
  return (uint32_t)data;
}

template <char t, class T>
typename enable_if<t == 'l', int32_t>::type cast(T const& data) {
  return (int32_t)data;
}

template <char t, class T>
typename enable_if<t == 'L', uint32_t>::type cast(T const& data) {
  return (uint32_t)data;
}

template <char t, class T>
typename enable_if<t == 'q', int64_t>::type cast(T const& data) {
  return (int64_t)data;
}

template <char t, class T>
typename enable_if<t == 'Q', uint64_t>::type cast(T const& data) {
  return (uint64_t)data;
}

template <char t, class T>
typename enable_if<t == 'f', float>::type cast(T const& data) {
  return (float)data;
}

template <char t, class T>
typename enable_if<t == 'd', double>::type cast(T const& data) {
  return (double)data;
}

#endif
