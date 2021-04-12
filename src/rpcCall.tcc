#ifndef CPP_SIMPLE_RPC_RPCCALL_TCC_
#define CPP_SIMPLE_RPC_RPCCALL_TCC_

#include "io.tcc"

extern void* _rpcMethod[];

//! \defgroup call


/*!
 * Get the index of an RPC method.
 *
 * \param f RPC method.
 *
 * \return Index of `f`.
 */
template <class F>
uint8_t _methodIndex(F& f) {
  for (uint8_t i = 0; i < sizeof(_rpcMethod) / sizeof(void*); i++) {
    if (&f == _rpcMethod[i]) {
      return i;
    }
  }
  return 0xff;
}


//! Recursion terminator for `_call()`.
inline void _call(int, void (*)(void)) {}

/*!
 * Write parameter values.
 *
 * \param fd File descriptor.
 * \param f_ Dummy function pointer.
 * \param v Value to write.
 * \param args Remaining values.
 */
template <class H, class... Tail, class T, class... Args>
void _call(int fd, void (*f_)(H, Tail...), T const& v, Args const&... args) {
  ioWrite(fd, (H*)&v);
  _call(fd, (void (*)(Tail...))f_, args...);
}


/*! \ingroup call
 * RPC call.
 *
 * \param fd File descriptor.
 * \param f Function pointer.
 * \param args Parameter values.
 */
template <class... FArgs, class... Args>
void call(int fd, void (*&f)(FArgs...), Args const&... args) {
  uint8_t index = _methodIndex(f);
  ioWrite(fd, &index);
  _call(fd, (void (*)(FArgs...))f, args...);
}

/*! \ingroup call
 * RPC call.
 *
 * \param fd File descriptor.
 * \param f Function pointer.
 * \param args Parameter values.
 *
 * \return Result.
 */
template <class R, class... FArgs, class... Args>
R call(int fd, R (*&f)(FArgs...), Args const&... args) {
  call(fd, (void (*&)(FArgs...))f, args...);

  R data;
  ioRead(fd, &data);
  return data;
}

#endif
