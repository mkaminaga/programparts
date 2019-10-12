//
// @file util.h
// @brief CPU performance monitoring test.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

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

ULARGE_INTEGER FILETIME_to_ULARGE_INTEGER(const FILETIME& file_time);

bool PrintEdit(HWND hEdit, const wchar_t* format, ...);
bool ClearEdit(HWND hEdit);
bool CopyEdit(HWND hEdit);
bool CopyTextToClipBoard(const wchar_t* text, size_t length);

#endif  // _UTIL_H_
