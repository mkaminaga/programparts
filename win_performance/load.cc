//
// @file main.cc
// @brief Load application for performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:22:26
// Copyright 2019 Mamoru Kaminaga
//
#include <wchar.h>
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hInstance;
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

  MessageBox(NULL, L"Continue", L"Error", MB_OK);

  // Consume CPU a lot.
  float f = 1000.0;
  while (true) {
    f = f / 3;
    f = f * 3;
    f = f / 3;
    f = f * 3;
    f = f / 3;
    f = f * 3;
    f = f / 3;
    f = f * 3;
    f = f / 3;
    f = f * 3;
  }
  return 0;
}
