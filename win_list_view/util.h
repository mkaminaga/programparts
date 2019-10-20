//
// @file util.h
// @brief List view test tool.
// @author Mamoru Kaminaga
// @date 2019-10-18 20:46:40
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include "./list_view.h"

// Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwndDlg, msg, fn)     \
  case (msg):                                \
    return SetDlgMsgResult((hwndDlg), (msg), \
                           HANDLE_##msg((hwndDlg), (wParam), (lParam), (fn)));

namespace mk {

std::wstring SynthString(const wchar_t* format, ...);

}  // namespace mk

#endif  // _UTIL_H_
