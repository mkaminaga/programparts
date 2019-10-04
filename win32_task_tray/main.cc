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
HMENU hMenu = NULL;
HMENU hSubMenu = NULL;
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
  StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Task tray test");

  if (Shell_NotifyIcon(NIM_ADD, &nid) != TRUE) {
#ifdef DEBUG
    fwprintf(stderr, L"Failed to add an icon on task tray!\n");
#endif
    return FALSE;
  }

  // Initialization of menu.
  hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
  hSubMenu = GetSubMenu(hMenu, 0);
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;

  // Finalization of menu.
  DestroyMenu(hMenu);

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

  switch (id) {
    case IDM_FOLDER:
      MessageBox(hwnd, L"Folder is clicked", WINDOW_NAME, MB_OK);
      break;
    case IDM_QUIT:
      DestroyWindow(hwnd);
      break;
    default:
      break;
  }
}

void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg) {
  (void)hwnd;

  if (id != TASKTRAY_ICONID) {
    return;
  }
  switch (uMsg) {
    case WM_LBUTTONDOWN:
      MessageBox(hwnd, L"main.exe", WINDOW_NAME, MB_OK);
      break;
    case WM_RBUTTONDOWN: {
      // Display menu when right button is clicked on task tray icon.
      POINT point;
      GetCursorPos(&point);
      SetForegroundWindow(hwnd);
      TrackPopupMenu(hSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN, point.x,
                     point.y, 0, hwnd, NULL);
      PostMessage(hwnd, WM_NULL, 0, 0);
    } break;
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

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = CLASS_NAME;
  if (!RegisterClass(&wc)) {
    return FALSE;
  }

  HWND hWnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_DISABLED, CW_USEDEFAULT,
                           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
                           NULL, hInstance, NULL);
  if (hWnd == NULL) {
    return FALSE;
  }

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
