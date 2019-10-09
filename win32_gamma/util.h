//
// @file util.h
// @brief Miscellaneous functions.
// @author Mamoru Kaminaga
// @date 2019-10-09 20:30:44
// Copyright 2019
//
#ifndef UTIL_H_
#define UTIL_H_

#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>

// Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwndDlg, msg, fn)     \
  case (msg):                                \
    return SetDlgMsgResult((hwndDlg), (msg), \
                           HANDLE_##msg((hwndDlg), (wParam), (lParam), (fn)));

bool PrintToEdit(HWND hEdit, const wchar_t* format, ...);

#endif  // UTIL_H_
