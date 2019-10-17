//
// @file edit.h
// @brief Edit control functions.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#include "./edit.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>

namespace {
constexpr int EDIT_BUFFER_MAX = 512;
}  // namespace

namespace mk {

Edit::Edit(HWND hEdit) : hEdit(hEdit) { return; }

Edit::~Edit() { return; }

HWND Edit::GetHandle() { return hEdit; }

void Edit::EnableInput() {
  SendMessage(hEdit, EM_SETREADONLY, FALSE, 0);
  return;
}

void Edit::DisableInput() {
  SendMessage(hEdit, EM_SETREADONLY, TRUE, 0);
  return;
}

void Edit::Show() {
  ShowWindow(hEdit, SW_SHOW);
  return;
}

void Edit::Hide() {
  ShowWindow(hEdit, SW_HIDE);
  return;
}

void Edit::Clear() {
  SendMessage(hEdit, WM_CLEAR, 0, 0);
  return;
}

void Edit::ClearAll() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_CLEAR, 0, 0);
  return;
}

void Edit::Copy() {
  SendMessage(hEdit, WM_COPY, 0, 0);  // Current selection.
  return;
}

void Edit::CopyAll() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_COPY, 0, 0);
  return;
}

void Edit::Cut() {
  SendMessage(hEdit, WM_CUT, 0, 0);
  return;
}

void Edit::CutAll() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_CUT, 0, 0);
  return;
}

void Edit::Get(wchar_t* dst, size_t dst_size) {
  assert(dst);

  // Current selected region is acquired.
  int begin = 0;
  int end = 0;
  SendMessage(hEdit, EM_GETSEL, (WPARAM)&begin, (LPARAM)&end);

  // Whole text length in edit control.
  int length = GetWindowTextLength(hEdit);
  if (length == 0) {
    return;
  }

  // Allocate heap memory.
  wchar_t* buffer = (wchar_t*)malloc(length * sizeof(wchar_t));
  if (buffer == NULL) {
    return;
  }

  // Get all text then cut selected region only.
  SendMessage(hEdit, WM_GETTEXT, (WPARAM)length, (LPARAM)buffer);
  for (int i = 0; i <= (end - begin); i++) {
    if (i == static_cast<int>(dst_size)) {
      dst[dst_size - 1] = '\0';
      break;
    }
    dst[i] = buffer[begin + i];
  }

  // Free heap memory.
  free(buffer);
  return;
}

void Edit::GetAll(wchar_t* dst, size_t dst_size) {
  assert(dst);
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_GETTEXT, (WPARAM)dst_size, (LPARAM)dst);
  return;
}

void Edit::Paste() {
  SendMessage(hEdit, WM_PASTE, 0, 0);
  return;
}

void Edit::Set(const wchar_t* format, ...) {
  wchar_t buffer[EDIT_BUFFER_MAX] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  // Set buffered text.
  SetFocus(hEdit);
  SendMessage(hEdit, WM_SETTEXT, (WPARAM)0, (LPARAM)buffer);
  return;
}

void Edit::Add(const wchar_t* format, ...) {
  wchar_t buffer[EDIT_BUFFER_MAX] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  // Add buffered text to tail.
  int index = GetWindowTextLength(hEdit);
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
  return;
}

void Edit::Focus() { SetFocus(hEdit); }

void Edit::Tail() {
  int index = GetWindowTextLength(hEdit);
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
}

}  // namespace mk
