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
  return 255;
}


//! Recursion terminator for `_call()`.
inline void _call(bStream&, void (*)(void)) {}

/*!
 * Write parameter values.
 *
 * \param io Binary blocking input / output stream.
 * \param f_ Dummy function pointer.
 * \param h Value to write.
 * \param args Remaining values.
 */
template <class H, class... Tail>
void _call(
    bStream& io, void (*f_)(H, Tail...), H const& h, Tail const&... args) {
  io.write(h);
  _call(io, (void (*)(Tail...))f_, args...);
}


/*! \ingroup call
 * RPC call.
 *
 * \param io Binary blocking input / output stream.
 * \param f Function pointer.
 * \param args Parameter values.
 *
 * \return Result.
 */
template <class R, class... Args, class... FArgs>
R call(bStream& io, R (*&f)(Args...), FArgs const&... args) {
  io.write(_methodIndex(f));
  _call(io, (void (*)(Args...))f, args...);
  return io.read<R>();
}

/*! \ingroup call
 * RPC call.
 *
 * \param io Binary blocking input / output stream.
 * \param f Function pointer.
 * \param args Parameter values.
 */
template <class... Args, class... FArgs>
void call(bStream& io, void (*&f)(Args...), FArgs const&... args) {
  io.write(_methodIndex(f));
  _call(io, (void (*)(Args...))f, args...);
}

#endif
