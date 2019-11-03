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

#define ASSERT_COLUMN(c) (assert(((c) >= 0) && ((c) <= _column_max)))
#define ASSERT_RAW(r) (assert(((r) >= 0) && ((r) <= _row_max)))

namespace {

const uint32_t MK_LV_BUF_MAX = 256;
const uint32_t MK_LV_DEF_COL_WIDTH = 40;

}  // namespace

namespace mk {

ListView::ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
                   uint32_t column_max)
    : _hListView(hListView),
      _mode(mode),
      _row_max(row_max),
      _column_max(column_max) {
  _hHeader = ListView_GetHeader(_hListView);
  ResizeTable(mode, 0, 0, row_max, column_max);
  return;
}

ListView::~ListView() { return; }

void ListView::Resize(mk::ListView::MODE mode, uint32_t row_max,
                      uint32_t column_max) {
  ResizeTable(mode, _row_max, _column_max, row_max, column_max);
}

void ListView::SetFocus() {
  ::SetFocus(_hListView);
  return;
}

uint32_t ListView::GetSelection() {
  uint32_t result = 0;
  for (uint32_t i = 0; i < _row_max; i++) {
    if (ListView_GetItemState(_hListView, i, LVIS_SELECTED) & LVIS_SELECTED) {
      result = i;
      break;
    }
  }
  return result;
}

void ListView::SetSelection(uint32_t item) {
  ASSERT_RAW(item);
  ListView_SetItemState(_hListView, -1, 0, LVIS_SELECTED);
  SendMessage(_hListView, LVM_ENSUREVISIBLE, (WPARAM)item, FALSE);
  ListView_SetItemState(_hListView, item, LVIS_SELECTED, LVIS_SELECTED);
  return;
}

void ListView::SetData(uint32_t column, const std::vector<std::wstring>& data,
                       const wchar_t* format) {
  ASSERT_COLUMN(column);
  assert(format);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  lvi.iSubItem = column;
  lvi.mask = LVIF_TEXT;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  // apply size limit.
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    swprintf_s(buffer, ARRAYSIZE(buffer), format, data[i].c_str());
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

void ListView::SetData(uint32_t column, const std::vector<int>& data,
                       const wchar_t* format) {
  ASSERT_COLUMN(column);
  assert(format);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  lvi.iSubItem = column;
  lvi.mask = LVIF_TEXT;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  // apply size limit.
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

void ListView::SetData(uint32_t column, const std::vector<double>& data,
                       const wchar_t* format) {
  ASSERT_COLUMN(column);
  assert(format);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  lvi.iSubItem = column;
  lvi.mask = LVIF_TEXT;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  // apply size limit.
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

void ListView::GetText(uint32_t column, std::vector<std::wstring>* data) {
  ASSERT_COLUMN(column);
  assert(data);
  LVITEM lvi;
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  data->resize(_row_max);
  for (uint32_t i = 0; i < _row_max; i++) {
    lvi.iItem = i;
    ListView_GetItem(_hListView, &lvi);
    (*data)[i] = buffer;  // Set string.
  }
  return;
}

uint32_t ListView::GetRow() const { return _row_max; }

uint32_t ListView::GetColumn() const { return _column_max; }

void ListView::SetImageList(HIMAGELIST hImageList) {
  switch (_mode) {
    case mk::ListView::MODE::ICON:
      // Reserved.
      break;
    case mk::ListView::MODE::SMALLICON:
      // Reserved.
      break;
    case mk::ListView::MODE::LIST:
      // Reserved.
      break;
    case mk::ListView::MODE::REPORT:
      // Image list with small icons.
      ListView_SetImageList(_hListView, hImageList, LVSIL_SMALL);
      break;
    default:
      // none.
      break;
  }
  return;
}

void ListView::SetImage(uint32_t column, const std::vector<uint32_t>& index) {
  ASSERT_COLUMN(column);
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

HWND ListView::GetHeaderHandle() { return _hHeader; }

void ListView::SetHeaderWidth(uint32_t column, uint32_t width) {
  ASSERT_COLUMN(column);
  assert(width >= 0);
  ListView_SetColumnWidth(_hListView, column, width);
  return;
}

void ListView::SetHeaderText(uint32_t column, const wchar_t* text) {
  ASSERT_COLUMN(column);
  LVCOLUMNA lvc;
  ZeroMemory(&lvc, sizeof(lvc));
  lvc.mask = LVCF_TEXT;
  lvc.pszText = (LPSTR)text;
  lvc.cchTextMax = wcslen(text);
  ListView_SetColumn(_hListView, column, &lvc);
  return;
}

HWND ListView::GetHandle() { return _hListView; }

void ListView::ResizeTable(mk::ListView::MODE mode, uint32_t old_row_max,
                           uint32_t old_column_max, uint32_t new_row_max,
                           uint32_t new_column_max) {
  // Mode and size is changed.
  ListView_SetExtendedListViewStyleEx(
      _hListView, LVS_ICON | LVS_SMALLICON | LVS_LIST | LVS_REPORT,
      0);  // Reset mode.
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
      const DWORD mask = LVS_REPORT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
                         LVS_EX_HEADERDRAGDROP;
      ListView_SetExtendedListViewStyleEx(_hListView, mask, mask);
      ResizeRow(old_row_max, new_row_max);
      ResizeColumn(old_column_max, new_column_max);
    } break;
    default:
      break;
  }
  // Copy to member.
  _row_max = new_row_max;
  _column_max = new_column_max;
  _mode = mode;
  return;
}

void ListView::ResizeRow(uint32_t old_row_max, uint32_t new_row_max) {
  assert(old_row_max >= 0);
  assert(new_row_max >= 0);
  if (new_row_max > old_row_max) {
    // Push rows.
    LVITEM lvi;
    ZeroMemory(&lvi, sizeof(lvi));
    lvi.mask = LVIF_TEXT;
    lvi.pszText = L"";
    lvi.cchTextMax = 1;
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
    lvc.cx = MK_LV_DEF_COL_WIDTH;  // default.
    lvc.pszText = L"";
    lvc.cchTextMax = 1;
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

void ListView::SetHeaderArrow(uint32_t column,
                              mk::ListView::SORTORDER sort_order) {
  ASSERT_COLUMN(column);
  HDITEM hdi;
  ZeroMemory(&hdi, sizeof(hdi));
  hdi.mask = HDI_FORMAT;
  Header_GetItem(_hHeader, column, &hdi);
  hdi.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP | HDF_IMAGE | HDF_BITMAP);
  switch (sort_order) {
    case mk::ListView::SORTORDER::DOWN:
      hdi.fmt |= HDF_SORTDOWN;
      break;
    case mk::ListView::SORTORDER::UP:
      hdi.fmt |= HDF_SORTUP;
      break;
    default:
      // none.
      break;
  }
  Header_SetItem(_hHeader, column, &hdi);
}

bool ListView::EnableListView() {
  // Set flag of comctl32.dll to use ListView control.
  INITCOMMONCONTROLSEX ic;
  ic.dwSize = sizeof(ic);
  ic.dwICC = ICC_LISTVIEW_CLASSES;
  if (InitCommonControlsEx(&ic) == FALSE) {
    return false;
  }
  return true;
}

}  // namespace mk
