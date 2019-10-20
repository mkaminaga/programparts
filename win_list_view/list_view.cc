//
// @file list_view.cc
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#include "./list_view.h"
#include <assert.h>
#include <stdint.h>
#include <windows.h>

#include <commctrl.h>  // Included at last.

namespace mk {

ListView::ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
                   uint32_t column_max)
    : _hListView(hListView), _row_max(0), _column_max(0) {
  Resize(mode, row_max, column_max);
  return;
}

ListView::~ListView() { return; }

void ListView::Resize(mk::ListView::MODE mode, uint32_t row_max,
                      uint32_t column_max) {
  const uint32_t old_row_max = _row_max;
  const uint32_t old_column_max = _column_max;
  _row_max = row_max;
  _column_max = column_max;
  ListView_SetExtendedListViewStyleEx(
      _hListView, LVS_ICON | LVS_SMALLICON | LVS_LIST | LVS_REPORT, 0);
  switch (mode) {
    case mk::ListView::MODE::ICON:
      // Reserved.
      break;
    case mk::ListView::MODE::SMALLICON:
      // Reserved.
      break;
    case mk::ListView::MODE::LIST:
      // Reserved.
      break;
    case mk::ListView::MODE::REPORT: {
      DWORD mask = LVS_REPORT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;
      ListView_SetExtendedListViewStyleEx(_hListView, mask, mask);
      ResizeRow(old_row_max, _row_max);
      ResizeColumn(old_column_max, _column_max);
    } break;
    default:
      break;
  }
  return;
}

void ListView::SetFocus() {
  ::SetFocus(_hListView);
  return;
}

void ListView::SetImageList(HIMAGELIST hImageList) {
  ListView_SetImageList(_hListView, hImageList, LVSIL_NORMAL);
  return;
}

void ListView::SetColumnWidth(uint32_t column, uint32_t width) {
  assert(column >= 0);
  assert(width >= 0);
  ListView_SetColumnWidth(_hListView, column, width);
  return;
}

void ListView::SetColumnText(uint32_t column, const wchar_t* text) {
  assert((column >= 0) && (column <= _column_max));
  LVCOLUMNA lvc;
  ZeroMemory(&lvc, sizeof(lvc));
  lvc.mask = LVCF_TEXT;
  lvc.pszText = (LPSTR)text;
  lvc.cchTextMax = wcslen(text);
  ListView_SetColumn(_hListView, column, &lvc);
  return;
}

void ListView::SelectItem(uint32_t item) {
  assert((item >= 0) && (item <= _row_max));
  ListView_SetItemState(_hListView, -1, 0, LVIS_SELECTED);
  SendMessage(_hListView, LVM_ENSUREVISIBLE, (WPARAM)item, FALSE);
  ListView_SetItemState(_hListView, item, LVIS_SELECTED, LVIS_SELECTED);
  return;
}

uint32_t ListView::GetSelectedItem() {
  uint32_t result = 0;
  for (uint32_t i = 0; i < _row_max; i++) {
    if ((ListView_GetItemState(_hListView, i, LVIS_SELECTED) & LVIS_SELECTED)) {
      result = i;
      break;
    }
  }
  return result;
}

void ListView::GetText(uint32_t column, std::vector<std::wstring>* data) {
  assert((column >= 0) && (column <= _column_max));
  assert(data);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[256] = {0};
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  data->resize(_row_max);
  for (uint32_t i = 0; i < _row_max; i++) {
    lvi.iItem = i;
    ListView_GetItem(_hListView, &lvi);
    (*data)[i] = buffer;
  }
  return;
}

void ListView::SetText(uint32_t column, const std::vector<std::wstring>& data) {
  assert(column >= 0);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = column;
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    lvi.pszText = (LPWSTR)data[i].c_str();
    lvi.cchTextMax = data[i].size();
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

void ListView::SetIcon(uint32_t column, const std::vector<uint32_t>& index) {
  assert((column >= 0) && (column <= _column_max));
  assert(index.size() >= _row_max);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  for (uint32_t i = 0; i < index.size(); i++) {
    lvi.mask = LVIF_IMAGE;
    lvi.iItem = i;
    lvi.iSubItem = column;
    lvi.iImage = index[i];
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

template void ListView::SetData<uint32_t>(uint32_t, const wchar_t*,
                                          const std::vector<uint32_t>&);
template void ListView::SetData<double>(uint32_t, const wchar_t*,
                                        const std::vector<double>&);
template <typename T>
void ListView::SetData(uint32_t column, const wchar_t* format,
                       const std::vector<T>& data) {
  assert((column >= 0) && (column <= _column_max));
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[256] = {0};
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    swprintf_s(buffer, ARRAYSIZE(buffer), format, data[i]);
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

HWND ListView::GetHandle() { return _hListView; }

void ListView::ResizeRow(uint32_t old_row_max, uint32_t new_row_max) {
  assert(old_row_max >= 0);
  assert(new_row_max >= 0);
  if (new_row_max > old_row_max) {
    // Push rows.
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_TEXT;
    lvi.pszText = L"";
    for (uint32_t i = 0; i < (new_row_max - old_row_max); i++) {
      lvi.iItem = old_row_max + i;
      ListView_InsertItem(_hListView, &lvi);
    }
  } else if (new_row_max < old_row_max) {
    // Delete tail.
    for (uint32_t i = 0; i < (old_row_max - new_row_max); i++) {
      ListView_DeleteItem(_hListView, old_row_max - i - 1);
    }
  } else {
    // none.
  }
  return;
}

void ListView::ResizeColumn(uint32_t old_column_max, uint32_t new_column_max) {
  assert(old_column_max >= 0);
  assert(new_column_max >= 0);
  if (new_column_max > old_column_max) {
    // Push columns.
    LVCOLUMN lvc;
    ZeroMemory(&lvc, sizeof(lvc));
    lvc.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc.cx = 40;  // default.
    lvc.pszText = L"";
    for (uint32_t i = 0; i < (new_column_max - old_column_max); i++) {
      ListView_InsertColumn(_hListView, old_column_max + i, &lvc);
    }
  } else if (new_column_max < old_column_max) {
    // Delete tail.
    for (uint32_t i = 0; i < (old_column_max - new_column_max); i++) {
      ListView_DeleteColumn(_hListView, old_column_max - i - 1);
    }
  } else {
    // none.
  }
  return;
}

bool ListView::EnableListView() {
  // Bit flags for comctl32.dll.
  INITCOMMONCONTROLSEX ic;
  ic.dwSize = sizeof(ic);
  ic.dwICC = ICC_LISTVIEW_CLASSES;
  if (InitCommonControlsEx(&ic) == FALSE) {
    return false;
  }
  return true;
}

}  // namespace mk
