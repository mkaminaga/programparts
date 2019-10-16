//
// @file list_view_control.h
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#ifndef LIST_VIEW_H_
#define LIST_VIEW_H_

#include <windows.h>

#include <commctrl.h>  // Last include.

class ListViewControl {
 public:
  ListViewControl(HWND h, DWORD style_flag, int item_count);
  virtual ~ListViewControl();
  void ResetStyle(int item_count, DWORD style_flag);

  static bool EnableListView();

 private:
  HWND hListView;
};

#endif  // LIST_VIEW_H_
