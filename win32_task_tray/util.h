//
// @file util.h
// @brief Test for task tray.
// @author Mamoru Kaminaga
// @date 2019-07-04 10:15:01
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <wchar.h>
#include <windows.h>
#include <windowsx.h>

// Application-defined message identifiers.
#define WM_TASKTRAY (WM_APP + 1)

// void Cls_OnTaskTray(HWND hwnd, UINT id, UINT uMsg)
#define HANDLE_WM_TASKTRAY(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (UINT)(wParam), (UINT)(lParam)), 0L)

#endif  // _UTIL_H_
