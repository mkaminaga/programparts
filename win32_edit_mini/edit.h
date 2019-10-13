//
// @file edit.h
// @brief Edit control functions.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _EDIT_H_
#define _EDIT_H_

#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>

class EditControl {
 public:
  EditControl(HWND hEdit);
  virtual ~EditControl();
  HWND EditControl::GetHandle();

  // Status.
  void EnableInput();
  void DisableInput();
  void Show();
  void Hide();

  // Read.
  void Clear();
  void Copy();
  void Cut();
  void Get(wchar_t* dst, size_t dst_size);

  // Write.
  void Paste();
  void Set(const wchar_t* format, ...);

  // Misc.
  void Focus();

 private:
  HWND hEdit;
};

#endif  // _EDIT_H_
