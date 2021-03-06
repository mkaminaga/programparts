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

Edit::Edit(HWND hEdit) : _hEdit(hEdit) { return; }

Edit::~Edit() { return; }

HWND Edit::GetHandle() { return _hEdit; }

void Edit::EnableInput() {
  SendMessage(_hEdit, EM_SETREADONLY, FALSE, 0);
  return;
}

void Edit::DisableInput() {
  SendMessage(_hEdit, EM_SETREADONLY, TRUE, 0);
  return;
}

void Edit::Show() {
  ShowWindow(_hEdit, SW_SHOW);
  return;
}

void Edit::Hide() {
  ShowWindow(_hEdit, SW_HIDE);
  return;
}

void Edit::SetFocus() {
  ::SetFocus(_hEdit);
}

void Edit::Clear() {
  SendMessage(_hEdit, EM_SETSEL, 0, -1);
  SendMessage(_hEdit, WM_CLEAR, 0, 0);
  return;
}

void Edit::Copy() {
  SendMessage(_hEdit, EM_SETSEL, 0, -1);
  SendMessage(_hEdit, WM_COPY, 0, 0);
  return;
}

void Edit::Cut() {
  SendMessage(_hEdit, EM_SETSEL, 0, -1);
  SendMessage(_hEdit, WM_CUT, 0, 0);
  return;
}

void Edit::Get(wchar_t* dst, size_t dst_size) {
  assert(dst);
  SendMessage(_hEdit, EM_SETSEL, 0, -1);
  SendMessage(_hEdit, WM_GETTEXT, (WPARAM)dst_size, (LPARAM)dst);
  return;
}

void Edit::Paste() {
  SendMessage(_hEdit, WM_PASTE, 0, 0);
  return;
}

void Edit::Set(const wchar_t* format, ...) {
  wchar_t buffer[EDIT_BUFFER_MAX] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  // Set buffered text.
  SendMessage(_hEdit, WM_SETTEXT, (WPARAM)0, (LPARAM)buffer);
  return;
}

void Edit::Add(const wchar_t* format, ...) {
  wchar_t buffer[EDIT_BUFFER_MAX] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  // Add buffered text to tail.
  int index = GetWindowTextLength(_hEdit);
  SendMessage(_hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
  SendMessage(_hEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
  return;
}

}  // namespace mk
