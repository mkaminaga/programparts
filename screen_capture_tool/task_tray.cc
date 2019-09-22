//
// @file task_tray.cc
// @brief Screen capture tool.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include "./task_tray.h"
#include <strsafe.h>
#include <wchar.h>
#include <windows.h>

bool SetTaskTrayIcon(HWND hwnd, int tray_icon_id, int icon_id) {
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);

  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = tray_icon_id;
  nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
  nid.uCallbackMessage = WM_TASKTRAY;
  nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(icon_id));
  StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Task tray test");

  if (Shell_NotifyIcon(NIM_ADD, &nid) != TRUE) {
#if DEBUG
    fwprintf(stderr, L"Failed to add an icon on task tray.\n");
#endif
    return false;
  }
  return true;
}

void RemoveTaskTrayIcon(HWND hwnd, int tray_icon_id) {
  NOTIFYICONDATA nid;
  ZeroMemory(&nid, sizeof(nid));
  nid.cbSize = sizeof(nid);
  nid.hWnd = hwnd;
  nid.uID = tray_icon_id;
  nid.uFlags = 0;
  Shell_NotifyIcon(NIM_DELETE, &nid);
}
