#include "io.tcc"

//! \defgroup call


//! Recursion terminator for `_call()`.
inline void _call(bStream&, void (*)(void)) {}

/*!
 * Write parameter values.
 *
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
 * \param f Function pointer.
 * \param args Parameter values.
 *
 * \return Result.
 */
template <class R, class... Args, class... FArgs>
R call(bStream& io, R (*f)(Args...), FArgs const&... args) {
  _call(io, (void (*)(Args...))f, args...);
  return io.read<R>();
}

/*! \ingroup call
 * RPC call.
 *
 * \param f Function pointer.
 * \param args Parameter values.
 */
template <class... Args, class... FArgs>
void call(bStream& io, void (*f)(Args...), FArgs const&... args) {
  _call(io, (void (*)(Args...))f, args...);
}
