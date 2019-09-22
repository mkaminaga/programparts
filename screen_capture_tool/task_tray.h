//
// @file task_tray.h
// @brief Screen capture tool.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _TASK_TRAY_H_
#define _TASK_TRAY_H_

#include <wchar.h>
#include <windows.h>
#include <windowsx.h>

// Application-defined message identifiers.
#define WM_TASKTRAY (WM_APP + 1)

// void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg)
#define HANDLE_WM_TASKTRAY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (UINT)(lParam)), 0L)

bool SetTaskTrayIcon(HWND hwnd, int tray_icon_id, int icon_id);
void RemoveTaskTrayIcon(HWND hwnd, int tray_icon_id);

#endif  // _TASK_TRAY_H_
