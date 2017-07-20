#include <iterator>

template <class T>
struct add_const_ref {
  using type = T;
};
