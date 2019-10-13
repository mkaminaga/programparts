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
