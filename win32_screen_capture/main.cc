//
// @file main.cc
// @brief Test project for screen capture.
// @author Mamoru Kaminaga
// @date 2019-09-20 12:51:16
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./resource.h"
#include "./util.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"Template window";
constexpr wchar_t CLASS_NAME[] = L"Template class";
}  // namespace

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hInstance;
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

#ifdef DEBUG
  FILE* fp = nullptr;
  AllocConsole();
  _wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
  _wfreopen_s(&fp, L"CONOUT$", L"w", stderr);
  _wfreopen_s(&fp, L"CONIN$", L"r", stdin);
#endif

#ifdef DEBUG
  fwprintf(stdout, L"Hello world to stdout!\n");
  fwprintf(stderr, L"Hello world to stderr!\n");
#endif

  PNGData png_data;
#if 0
  // Test case 1 : Use of PaintDesktop().
  if (!ScreenToPNG(TESTCASE_PAINT_DESKTOP, &png_data)) {
    MessageBox(NULL, L"Case 1 failed.", L"Error", MB_OK);
  } else {
    WritePNGFile(L"case_1.png", png_data);
  }

  // Test case 2 : Use of PaintWindow().
  if (!ScreenToPNG(TESTCASE_PAINT_WINDOW, &png_data)) {
    MessageBox(NULL, L"Case 2 failed.", L"Error", MB_OK);
  } else {
    WritePNGFile(L"case_2.png", png_data);
  }
#endif

  // Test case 3 : Use of BitBlt().
  if (!ScreenToPNG(TESTCASE_BITBLT, &png_data)) {
    MessageBox(NULL, L"Case 3 failed.", L"Error", MB_OK);
  } else {
    WritePNGFile(L"case_3.png", png_data);
  }

  // Everything is done!
  MessageBox(NULL, L"End of test.", L"main.exe", MB_OK);
  DestroyWindow(NULL);

#ifdef DEBUG
  FreeConsole();
#endif
  return 0;
}
