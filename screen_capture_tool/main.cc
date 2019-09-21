//
// @file main.cc
// @brief Screen capture tool.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include <strsafe.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./key_hook.h"
#include "./resource.h"
#include "./task_tray.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"ScreenCaptureTool";
constexpr wchar_t CLASS_NAME[] = L"ScreenCaptureToolClass";
constexpr int TASKTRAY_ICONID = 1;
}  // namespace

BOOL Cls_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  (void)hwnd;
  (void)lpCreateStruct;

  /////////////////////////////////////////////////////////////////////////////
  //  Task tray initialization
  /////////////////////////////////////////////////////////////////////////////
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

  /////////////////////////////////////////////////////////////////////////////
  //  Key hook initialization
  /////////////////////////////////////////////////////////////////////////////
  // Start the keyboard hook.
  if (!SetKeyHook(hwnd)) {
#ifdef DEBUG
    fwprintf(stderr, L"Failed to start hook\n");
#endif
    FreeConsole();
    return 0;
  }
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  /////////////////////////////////////////////////////////////////////////////
  //  Key hook finalization
  /////////////////////////////////////////////////////////////////////////////
  // Stop the keyboard hook.
  if (!RemoveKeyHook()) {
#ifdef DEBUG
    fwprintf(stderr, L"Failed to stop hook\n");
#endif
  }
  PostQuitMessage(0);

  /////////////////////////////////////////////////////////////////////////////
  //  Task tray finalization
  /////////////////////////////////////////////////////////////////////////////
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
#ifdef DEBUG
      fwprintf(stderr, L"Folder is clicked\n");
#endif
      break;
    case IDM_QUIT:
#ifdef DEBUG
      fwprintf(stderr, L"Quit is clicked\n");
#endif
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
    case WM_RBUTTONDOWN: {
      // Display menu when right button is clicked on task tray icon.
      POINT point;
      GetCursorPos(&point);
      HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
      HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
      HMENU hSubMenu = GetSubMenu(hMenu, 0);
      TrackPopupMenu(hSubMenu, TPM_LEFTALIGN | TPM_BOTTOMALIGN, point.x,
                     point.y, 0, hwnd, NULL);
    } break;
    default:
      break;
  }
}

void Cls_OnKeyHook(HWND hwnd, WPARAM wParam, LPARAM lParam) {
  (void)hwnd;
  const UINT vk = (UINT)wParam;
  const BOOL fDown = ((lParam & 0x80000000) == 0) ? TRUE : FALSE;
  if (fDown == TRUE) {
    fwprintf(stderr, L"key down, %2x:\n", vk);
  } else {
    fwprintf(stderr, L"key up, %2x:\n", vk);
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
    HANDLE_MSG(hwnd, WM_KEYHOOK, Cls_OnKeyHook);
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
  fwprintf(stderr, L"\n");
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
