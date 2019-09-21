//
// @file key_hook.h
// @brief Keyboard hook related functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:31:20
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _DLL_UTIL_H_
#define _DLL_UTIL_H_

#include <windows.h>

#ifndef DLLAPI
#define DLLAPI extern "C" __declspec(dllimport)
#endif

// Application-defined message identifiers.
#define WM_KEYHOOK (WM_APP + 100)

// void Cls_OnKeyHook(HWND hwnd, WPARAM wParam, LPARAM lParam)
#define HANDLE_WM_KEYHOOK(hwnd, wParam, lParam, fn) \
  ((fn)((hwnd), (WPARAM)(wParam), (LPARAM)(lParam)), 0L)

DLLAPI bool SetKeyHook(HWND hWnd);
DLLAPI bool RemoveKeyHook();

#endif  // _DLL_UTIL_H_
