//
// @file main.cc
// @brief Template project for Windows desktop application.
// @author Mamoru Kaminaga
// @date 2019-07-02 15:46:34
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./resource.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"Template window";
constexpr wchar_t CLASS_NAME[] = L"Template class";
}  // namespace

BOOL Cls_OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) {
  (void)hWnd;
  (void)lpCreateStruct;
  return TRUE;
}

void Cls_OnDestroy(HWND hWnd) {
  (void)hWnd;
  PostQuitMessage(0);
}

void Cls_OnClose(HWND hWnd) { DestroyWindow(hWnd); }

void Cls_OnCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hWnd;
  (void)id;
  (void)hWndCtl;
  (void)codeNotify;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
    HANDLE_MSG(hWnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hWnd, WM_DESTROY, Cls_OnDestroy);
    HANDLE_MSG(hWnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hWnd, WM_CLOSE, Cls_OnClose);
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hPrevInstance;
  (void)lpsCmdLine;

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

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = 0;
  wc.lpszClassName = CLASS_NAME;
  if (!RegisterClass(&wc)) {
    return FALSE;
  }

  HWND hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                           CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
  if (hWnd == NULL) {
    return FALSE;
  }
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

#ifdef DEBUG
  FreeConsole();
#endif
  return 0;
}
