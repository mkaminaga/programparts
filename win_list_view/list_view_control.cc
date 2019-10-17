//
// @file list_view_control.cc
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#include "./list_view_control.h"
#include <assert.h>
#include <windows.h>

#include <commctrl.h>  // Included at last.

ListViewControl::ListViewControl(HWND hListView, ListViewControl::MODE mode,
                                 int row_max, int column_max)
    : _hListView(hListView), _row_max(0), _column_max(0) {
  Reset(mode, row_max, column_max);
  return;
}

ListViewControl::~ListViewControl() { return; }

void ListViewControl::Reset(ListViewControl::MODE mode, int row_max,
                            int column_max) {
  const int old_row_max = _row_max;
  const int old_column_max = _column_max;
  _row_max = row_max;
  _column_max = column_max;
  ListView_SetExtendedListViewStyleEx(
      _hListView, LVS_ICON | LVS_SMALLICON | LVS_LIST | LVS_REPORT, 0);
  switch (mode) {
    case ListViewControl::MODE::ICON:
      // Reserved.
      break;
    case ListViewControl::MODE::SMALLICON:
      // Reserved.
      break;
    case ListViewControl::MODE::LIST:
      // Reserved.
      break;
    case ListViewControl::MODE::REPORT: {
      DWORD mask = LVS_REPORT | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
      ListView_SetExtendedListViewStyleEx(_hListView, mask, mask);
      ResizeRow(old_row_max, _row_max);
      ResizeColumn(old_column_max, _column_max);
    } break;
    default:
      break;
  }
}

void ListViewControl::ResizeRow(int old_row_max, int new_row_max) {
  assert(old_row_max >= 0);
  assert(new_row_max >= 0);

  if (new_row_max > old_row_max) {
    // Push rows.
    LVITEM item;
    ZeroMemory(&item, sizeof(item));
    item.mask = LVIF_TEXT;
    item.pszText = L"";
    for (int i = 0; i < (new_row_max - old_row_max); i++) {
      item.iItem = old_row_max + i;
      ListView_InsertItem(_hListView, &item);
    }
  } else if (new_row_max < old_row_max) {
    // Delete tail.
    for (int i = 0; i < (old_row_max - new_row_max); i++) {
      ListView_DeleteItem(_hListView, old_row_max - i - 1);
    }
  } else {
    // none.
  }
}

void ListViewControl::ResizeColumn(int old_column_max, int new_column_max) {
  assert(old_column_max >= 0);
  assert(new_column_max >= 0);

  if (new_column_max > old_column_max) {
    // Push columns.
    LVCOLUMN column;
    ZeroMemory(&column, sizeof(column));
    column.mask = LVCF_TEXT | LVCF_WIDTH;
    column.cx = 40;
    column.pszText = L"";
    for (int i = 0; i < (new_column_max - old_column_max); i++) {
      ListView_InsertColumn(_hListView, old_column_max + i, &column);
    }
  } else if (new_column_max < old_column_max) {
    // Delete tail.
    for (int i = 0; i < (old_column_max - new_column_max); i++) {
      ListView_DeleteColumn(_hListView, old_column_max - i - 1);
    }
  } else {
    // none.
  }
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
