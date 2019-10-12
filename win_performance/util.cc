//
// @file util.h
// @brief CPU performance monitoring test.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "./util.h"

ULARGE_INTEGER FILETIME_to_ULARGE_INTEGER(const FILETIME& file_time) {
  ULARGE_INTEGER result;
  result.LowPart = file_time.dwLowDateTime;
  result.HighPart = file_time.dwHighDateTime;
  return result;
}

bool PrintEdit(HWND hEdit, const wchar_t* format, ...) {
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

bool ClearEdit(HWND hEdit) {
  SendMessage(hEdit, WM_SETTEXT, (WPARAM)0, (LPARAM)L"");
  return true;
}

bool CopyEdit(HWND hEdit) {
  const int length = GetWindowTextLength(hEdit);
  if (length == 0) {
    return true;
  }

  wchar_t* buffer = (wchar_t*)malloc(length * sizeof(wchar_t));
  GetWindowText(hEdit, buffer, length);
  if (!CopyTextToClipBoard(buffer, length)) {
    free(buffer);
    return false;
  }
  free(buffer);
  return true;
}

bool CopyTextToClipBoard(const wchar_t* text, size_t length) {
  // Open and clean clipboard.
  if (!OpenClipboard(NULL)) {
    return false;
  }
  EmptyClipboard();

  // Allocate memory.
  HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, length * sizeof(wchar_t));
  if (hGlobal == NULL) {
    return false;
  }
  wchar_t* dst = (wchar_t*)GlobalLock(hGlobal);
  wcscpy_s(dst, length, text);

  // Copy text to clipboard.
  GlobalUnlock(hGlobal);
  SetClipboardData(CF_UNICODETEXT, hGlobal);

  // Close clipboard.
  CloseClipboard();
  return true;
}
