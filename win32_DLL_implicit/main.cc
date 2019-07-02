//
// @file main.cc
// @brief Test for dynamic link library (loaded implicitly).
// @author Mamoru Kaminaga
// @date 2019-07-02 10:28:02
// Copyright 2019 Mamoru Kaminaga
//
#include "./test_DLL.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  int v = 10;

  HelloWorld();

  printf("v = %d\n", v);

  v = Increment(v);
  printf("Incremented, v = %d\n", v);

  v = Decrement(v);
  printf("Decremented, v = %d\n", v);

  return 0;
}
