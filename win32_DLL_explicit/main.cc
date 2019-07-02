//
// @file main.cc
// @brief Test for dynamic link library (loaded implicitly).
// @author
// @date 2019-07-02 10:28:02
// Copyright 2019
//
#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // Load DLL in explicit way.
  HINSTANCE hDLL = LoadLibrary("test_DLL.dll");
  if (hDLL == nullptr) {
    fprintf(stderr, "Failed to load DLL\n");
    return 1;
  }

  // Load "Hello World" function.
  void (*hello_func)() = nullptr;
  hello_func = (void (*)())GetProcAddress(hDLL, "HelloWorld");
  if (hello_func == nullptr) {
    fprintf(stderr, "Failed to load function HelloWorld\n");
  } else {
    hello_func();
  }

  int v = 10;
  printf("v = %d\n", v);

  // Load increment function.
  int (*increment_func)(int v) = nullptr;
  increment_func = (int (*)(int))GetProcAddress(hDLL, "Increment");
  if (increment_func == nullptr) {
    fprintf(stderr, "Failed to load function Increment\n");
  } else {
    v = increment_func(v);
    printf("Incremented, v = %d\n", v);
  }

  // Load decrement function.
  int (*decrement_func)(int v) = nullptr;
  decrement_func = (int (*)(int))GetProcAddress(hDLL, "Decrement");
  if (decrement_func == nullptr) {
    fprintf(stderr, "Failed to load function Decrement\n");
    return 1;
  } else {
    v = decrement_func(v);
    printf("Decremented, v = %d\n", v);
  }

  // Release dynamic link library.
  FreeLibrary(hDLL);

  return 0;
}
