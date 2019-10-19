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

namespace mk {

class Edit {
 public:
  Edit(HWND hEdit);
  virtual ~Edit();
  HWND Edit::GetHandle();

  // Status.
  void EnableInput();
  void DisableInput();
  void Show();
  void Hide();
  void SetFocus();

  // Read.
  void Clear();
  void Copy();
  void Cut();
  void Get(wchar_t* dst, size_t dst_size);

  // Write.
  void Paste();
  void Set(const wchar_t* format, ...);
  void Add(const wchar_t* format, ...);

 private:
  HWND _hEdit;
};

}  // namespace mk

#endif  // _EDIT_H_
