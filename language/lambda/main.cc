//
// @file main.cc
// @brief Test of lambda function.
// @author Mamoru Kaminaga
// @date 2019-11-03 10:38:13
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <functional>

#define show(EXPRESSION)         \
  {                              \
    printf("%s\n", #EXPRESSION); \
    printf("%d\n", EXPRESSION);  \
    printf("\n");                \
  }

std::function<int(int)> CreateAdd(int add) {
  return [add](int i) { return i + add; };  // Use copy of add.
}

std::function<int(int)> CreateAddRef(int add) {
  return [&add](int i) { return i + add; };  // Use reference to add.
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  auto add1 = CreateAdd(1);
  auto add2 = CreateAdd(2);
  show(add1(1))
  show(add2(1))

#if 0
  auto addref1 = CreateAddRef(1);
  auto addref2 = CreateAddRef(2);
  show(addref1(1))  // Behavior is undefined.
  show(addref2(1))  // Behavior is undefined.
#endif

  return 0;
}
