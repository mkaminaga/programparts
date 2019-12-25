//
// @file util.h
// @brief Combo box test.
// @author Mamoru Kaminaga
// @date 2019-12-25 19:02:14
// Copyright 2019 Mamoru Kaminaga
//
#pragma once

#include <windows.h>
#include <windowsx.h>

#include <stdio.h>

// Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwndDlg, msg, fn)     \
  case (msg):                                \
    return SetDlgMsgResult((hwndDlg), (msg), \
                           HANDLE_##msg((hwndDlg), (wParam), (lParam), (fn)));

namespace mk {

bool OpenConsole();
void CloseConsole();

}  // namespace mk
