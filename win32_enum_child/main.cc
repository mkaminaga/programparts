//
// @file main.cc
// @brief Enumerate shell child windows.
// @author Mamoru Kaminaga
// @date 2019-09-21 10:32:06
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "./resource.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"Template window";
constexpr wchar_t CLASS_NAME[] = L"Template class";

BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {
  (void)lParam;

  wchar_t title[256] = {0};
  GetWindowText(hwnd, title, ARRAYSIZE(title));
#ifdef DEBUG
  fwprintf(stderr, L"title:%ls\n", title);
#endif

  RECT rc;
  GetWindowRect(hwnd, &rc);
#ifdef DEBUG
  fwprintf(stderr, L"x:%d, y:%d\n", rc.left, rc.top);
  fwprintf(stderr, L"w:%d, h:%d\n", rc.right - rc.left, rc.bottom - rc.top);
  fwprintf(stderr, L"\n");
#endif
  return TRUE;
}
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
  fwprintf(stderr, L"\n");
#endif

  LPARAM lp;
  EnumChildWindows(GetShellWindow(), EnumChildProc, lp);
  system("PAUSE");

#ifdef DEBUG
  FreeConsole();
#endif
  return 0;
}
