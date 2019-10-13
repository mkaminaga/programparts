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

EditControl::EditControl(HWND hEdit) : hEdit(hEdit) { return; }

EditControl::~EditControl() { return; }

HWND EditControl::GetHandle() { return hEdit; }

void EditControl::EnableInput() {
  SendMessage(hEdit, EM_SETREADONLY, FALSE, 0);
  return;
}

void EditControl::DisableInput() {
  SendMessage(hEdit, EM_SETREADONLY, TRUE, 0);
  return;
}

void EditControl::Show() {
  ShowWindow(hEdit, SW_SHOW);
  return;
}

void EditControl::Hide() {
  ShowWindow(hEdit, SW_HIDE);
  return;
}

void EditControl::Clear() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_CLEAR, 0, 0);
  return;
}

void EditControl::Copy() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_COPY, 0, 0);
  return;
}

void EditControl::Cut() {
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_CUT, 0, 0);
  return;
}

void EditControl::Get(wchar_t* dst, size_t dst_size) {
  assert(dst);
  SendMessage(hEdit, EM_SETSEL, 0, -1);
  SendMessage(hEdit, WM_GETTEXT, (WPARAM)dst_size, (LPARAM)dst);
  return;
}

void EditControl::Paste() {
  SendMessage(hEdit, WM_PASTE, 0, 0);
  return;
}

void EditControl::Set(const wchar_t* format, ...) {
  wchar_t buffer[EDIT_BUFFER_MAX] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);

  // Set buffered text.
  SetFocus(hEdit);
  SendMessage(hEdit, WM_SETTEXT, (WPARAM)0, (LPARAM)buffer);
  return;
}

void EditControl::Focus() {
  int index = GetWindowTextLength(hEdit);
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
}
