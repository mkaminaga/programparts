//
// @file util.cc
// @brief Miscellaneous functions.
// @author Mamoru Kaminaga
// @date 2019-10-09 20:30:44
// Copyright 2019
//
#include "./util.h"
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>

bool PrintToEdit(HWND hEdit, const wchar_t* format, ...) {
  wchar_t buffer[256] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  int index = GetWindowTextLength(hEdit);
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
  return true;
}
