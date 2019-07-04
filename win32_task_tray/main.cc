//
// @file main.cc
// @brief Test for task tray.
// @author Mamoru Kaminaga
// @date 2019-07-04 10:46:57
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <strsafe.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./resource.h"
#include "./util.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"Template window";
constexpr wchar_t CLASS_NAME[] = L"Template class";
constexpr int TASKTRAY_ICONID = 1;
}  // namespace

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  (void)hwnd;
  (void)lpCreateStruct;

  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

  // Add task tray icon.
  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = TASKTRAY_ICONID;
  nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid.uCallbackMessage = WM_TASKTRAY;
  nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Test application");

  if (Shell_NotifyIcon(NIM_ADD, &nid) != TRUE) {
#ifdef DEBUG
    fwprintf(stderr, L"Failed to add icon on task tray!\n");
#endif
  }

  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;

  // Remove task tray icon.
  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = TASKTRAY_ICONID;
  nid.uFlags = 0;
  Shell_NotifyIcon(NIM_DELETE, &nid);

  PostQuitMessage(0);
}

void Cls_OnClose(HWND hwnd) { DestroyWindow(hwnd); }

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)id;
  (void)hWndCtl;
  (void)codeNotify;
}

void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg) {
  (void)hwnd;

  if (id != TASKTRAY_ICONID) {
    return;
  }
  switch (uMsg) {
    case WM_RBUTTONDOWN:
      break;
    default:
      break;
  }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
  switch (message) {
    HANDLE_MSG(hwnd, WM_CREATE, Cls_OnCreate);
    HANDLE_MSG(hwnd, WM_DESTROY, Cls_OnDestroy);
    HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
    HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
    HANDLE_MSG(hwnd, WM_TASKTRAY, Cls_OnTaskTray);
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
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
