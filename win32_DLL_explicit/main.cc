//
// @file main.cc
// @brief Test for dynamic link library (loaded implicitly).
// @author Mamoru Kaminaga
// @date 2019-07-02 10:28:02
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <windows.h>
#include "./util.h"

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  // Load DLL.
  HINSTANCE hDLL = LoadLibrary(L"util.dll");
  if (hDLL == NULL) {
    fwprintf(stderr, L"Failed to load DLL\n");
    return 1;
  }

  // Load DLL function.
  void (*func)() = NULL;
  func = (void (*)())GetProcAddress(hDLL, "HelloWorld");
  if (func == NULL) {
    fwprintf(stderr, L"Failed to get function\n");
  } else {
    func();
  }

  // Release DLL.
  FreeLibrary(hDLL);

  return 0;
}
