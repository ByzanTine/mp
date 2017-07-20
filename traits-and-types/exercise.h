#include <iterator>

// 2-0
// add_const_ref
template <bool IsRef, class T>
struct add_const_ref_impl {
}; 

template <class T>
struct add_const_ref {
  using type = typename add_const_ref_impl<false, T>::type;
};

// This is using partial tempalte specialization.
template <class T>
struct add_const_ref <T&> {
  using type = typename add_const_ref_impl<true, T>::type;
};

template <class T>
struct add_const_ref_impl<true, T> {
  using type = T;
}; 

template <class T>
struct add_const_ref_impl<false, T> {
  using type = const T&;
}; 

// 2-1
// replace_type
template <class C, class X, class Y, bool IsSame>
struct replace_type_impl {
  using type = C;
};

template <class C, class X, class Y>
struct replace_type {
  using type = typename replace_type_impl<C, X, Y, std::is_same<C, X>::value>::type;
};

// Need to introduce another intermediate func to avoid recursion.
template <class C, class X, class Y>
struct replace_type_im {
  using type = C;
};

template <class C, class X, class Y>
struct replace_type_impl<C, X, Y, true> {
  using type = Y;
};

template <class C, class X, class Y>
struct replace_type_impl<C, X, Y, false> {
  using type = typename replace_type_im<C, X, Y>::type;
};

template <class C, class X, class Y>
struct replace_type_im<C*, X, Y> {
  using type = typename std::add_pointer<typename replace_type_impl<C, X, Y, std::is_same<C, X>::value>::type>::type;
};

template <class C, class X, class Y>
struct replace_type_im<C&, X, Y> {
  using type = typename std::add_lvalue_reference<typename replace_type_impl<C, X, Y, std::is_same<C, X>::value>::type>::type;
};

template <class C, class X, class Y>
struct replace_type_im<C&&, X, Y> {
  using type = typename std::add_rvalue_reference<typename replace_type_impl<C, X, Y, std::is_same<C, X>::value>::type>::type;
};

template <class C, class X, class Y, size_t N>
struct replace_type_im<C[N], X, Y> {
  using type = typename replace_type_impl<C, X, Y, std::is_same<C, X>::value>::type [N];
};

template <class R, class X, class Y, class T, class ... Args>
struct replace_type_im<R(*)(T, Args...), X, Y> {
  using typeT = typename replace_type_impl<R, X, Y, std::is_same<R, X>::value>::type (*)
      (typename replace_type_impl<T, X, Y, std::is_same<T, X>::value>::type);
  using typeArgs = typename replace_type_im<R(*)(Args...), X, Y>::type; 
  //TODO(yejiayu): join this two type, need function traits?.
  using type = short;
};

template <class R, class X, class Y, class T>
struct replace_type_im<R(*)(T), X, Y> {
  using type = typename replace_type_impl<R, X, Y, std::is_same<R, X>::value>::type (*)(
      typename replace_type_impl<T, X, Y, std::is_same<T, X>::value>::type);
};

