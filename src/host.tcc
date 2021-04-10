#include <stdio.h>          // DUMMY code.

//! \defgroup call


//! Recursion terminator for `_call()`.
inline void _call(void (*)(void)) {}

/*!
 * Write parameter values.
 *
 * \param f_ Dummy function pointer.
 * \param h Value to write.
 * \param args Remaining values.
 */
template <class H, class... Tail>
void _call(void (*f_)(H, Tail...), H const& h, Tail const&... args) {
  printf("write %i\n", h);  // DUMMY code.
  _call((void (*)(Tail...))f_, args...);
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
R call(R (*f)(Args...), FArgs const&... args) {
  _call((void (*)(Args...))f, args...);
  printf("read result\n");  // DUMMY code.
  return 10;                // DUMMY code.
}

/*! \ingroup call
 * RPC call.
 *
 * \param f Function pointer.
 * \param args Parameter values.
 */
template <class... Args, class... FArgs>
void call(void (*f)(Args...), FArgs const&... args) {
  _call((void (*)(Args...))f, args...);
}
