#include "exercise.h"

#include <iostream>

#include <type_traits>
#include "gtest/gtest.h"

template <typename T> std::string type_name();

// 2-0
TEST(AddConstRefTest, Base) {
  bool result = std::is_same<add_const_ref<int>::type, const int&>::value;
  EXPECT_TRUE(result);
  result = std::is_same<add_const_ref<int &>::type, int>::value;
  EXPECT_TRUE(result);
  result = std::is_same<add_const_ref<const int>::type, const int&>::value;
  EXPECT_TRUE(result);
}

// 2-1
TEST(ReplaceType, Base) {
  bool result = std::is_same<replace_type<void*, void, int>::type, int*>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char&, char, int>::type, int&>::value;
  EXPECT_TRUE(result);

  // This case introduce extra layer of abstraction. 
  result = std::is_same<replace_type<char&, char&, int>::type, int>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char&&, char, int>::type, int&&>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<int const*[10], int const, long>::type, long*[10]>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char& (*)(int&), char&, long&>::type, long&(*)(int&)>::value;
  EXPECT_TRUE(result);

  result = std::is_same<replace_type<char& (*)(char&), char&, long&>::type, long&(*)(long&)>::value;
  EXPECT_TRUE(result);

  // result = std::is_same<replace_type<char& (*)(char&, char&), char&, long&>::type, long&(*)(long&, char&)>::value;
  // EXPECT_TRUE(result);
}

// 2-3
TEST(TypeDescriptor, Base) {
  // // prints "int"
  // std::cout << type_descriptor<int>();
  // // prints "char*"
  // std::cout << type_descriptor<char*>();
  // // prints "long const*&"
  // std::cout << type_descriptor<long const*&>();
}
