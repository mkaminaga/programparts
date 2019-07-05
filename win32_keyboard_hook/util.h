//
// @file util.h
// @brief Test for keyboard hook.
// @author Mamoru Kaminaga
// @date 2019-07-04 18:49:29
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <windows.h>

#ifndef DLLAPI
#define DLLAPI extern "C" __declspec(dllimport)
#endif

// Application-defined message identifiers.
#define WM_KEYHOOK (WM_APP + 1)

// void Cls_OnKeyHook(HWND hwnd, WPARAM wParam, LPARAM lParam)
#define HANDLE_WM_KEYHOOK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (WPARAM)(wParam), (LPARAM)(lParam)), 0L)

DLLAPI bool StartKeyboardHook(HWND hWnd);
DLLAPI bool StopKeyboardHook();

#endif  // _UTIL_H_
