#include "exercise.h"

#include <iostream>

#include "gtest/gtest.h"
#include <type_traits>

template <typename T>
std::string type_name();

// 2-0
TEST(AddConstRefTest, Base) {
  bool result = std::is_same<add_const_ref<int>::type, const int &>::value;
  EXPECT_TRUE(result);
  result = std::is_same<add_const_ref<int &>::type, int>::value;
  EXPECT_TRUE(result);
  result = std::is_same<add_const_ref<const int>::type, const int &>::value;
  EXPECT_TRUE(result);
}

// 2-1
TEST(ReplaceType, Base) {
  bool result =
      std::is_same<replace_type<void *, void, int>::type, int *>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char &, char, int>::type, int &>::value;
  EXPECT_TRUE(result);

  // This case introduce extra layer of abstraction.
  result = std::is_same<replace_type<char &, char &, int>::type, int>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char &&, char, int>::type, int &&>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<int const * [10], int const, long>::type,
                        long * [10]>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char &(*)(int &), char &, long &>::type,
                        long &(*)(int &)>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char &(*)(char &), char &, long &>::type,
                        long &(*)(long &)>::value;
  EXPECT_TRUE(result);

  // result = std::is_same<replace_type<char& (*)(char&, char&), char&,
  // long&>::type, long&(*)(long&, char&)>::value;
  // EXPECT_TRUE(result);
}

// 2-2
TEST(PolymorphicDowncast, Base) {
  struct A {
    virtual ~A() {}
  };
  struct B : A {};
  B b;
  A *a_ptr = &b;
  B *b_ptr = polymorphic_downcast<B *>(a_ptr);
  EXPECT_TRUE(b_ptr != nullptr);

  A &a_ref = b;
  B &b_ref = polymorphic_downcast<B &>(a_ref);
  EXPECT_TRUE(&b_ref != nullptr);
  // This test is wins if it compiles.
}

template <class T>
void EXPECT_TYPE_DESC(std::string result) {
  std::ostringstream out;
  out << type_descriptor<T>();
  EXPECT_EQ(out.str(), result);
}

// 2-3
TEST(TypeDescriptor, Base) {
  // prints "int"
  EXPECT_TYPE_DESC<int>("int");
  EXPECT_TYPE_DESC<int &>("int&");
  EXPECT_TYPE_DESC<int *>("int*");
  EXPECT_TYPE_DESC<char *>("char*");
  EXPECT_TYPE_DESC<long const *&>("long const*&");
  // std::cout << type_descriptor<long const*&>();
}
