//
// @file list_view_control.cc
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#include "./list_view_control.h"
#include <windows.h>

#include <commctrl.h>  // Last include.

ListViewControl::ListViewControl(HWND h, DWORD style_flag, int item_count)
    : hListView(h) {
  ListView_SetItemCountEx(hListView, item_count, style_flag);
  return;
}

ListViewControl::~ListViewControl() { return; }

void ListViewControl::ResetStyle(int item_count, DWORD style_flag) {
  ListView_SetItemCountEx(hListView, item_count, style_flag);
}

bool ListViewControl::EnableListView() {
  // Bit flags for comctl32.dll.
  INITCOMMONCONTROLSEX ic;
  ic.dwSize = sizeof(ic);
  ic.dwICC = ICC_LISTVIEW_CLASSES;
  if (InitCommonControlsEx(&ic) == FALSE) {
    return false;
  }
  return true;
}

