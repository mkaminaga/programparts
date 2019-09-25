//
// @file main.cc
// @brief Compile option experiment.
// @author Mamoru Kaminaga
// @date 2019-09-25 18:37:12
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

namespace {
constexpr wchar_t WINDOW_NAME[] = L"MyWindow";
constexpr wchar_t CLASS_NAME[] = L"MyWindowClass";
}  // namespace

void PrintVector() {
  std::vector<int> array(3);
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  for (unsigned int i = 0; i < array.size(); i++) {
    fwprintf(stdout, L"array[%d] = %d\n", i, array[i]);
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hInstance;
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

  FILE* fp = nullptr;
  AllocConsole();
  _wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
  _wfreopen_s(&fp, L"CONOUT$", L"w", stderr);
  _wfreopen_s(&fp, L"CONIN$", L"r", stdin);

  // Use C++ features.
  PrintVector();
  system("pause");

  FreeConsole();
  return 0;
}
