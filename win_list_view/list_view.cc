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
      _sort_order(mk::ListView::SORT::ASCENDING),
      _last_key_column(0),
      _key_column(0),
      _row_max(0),
      _column_max(0) {
  Resize(mode, row_max, column_max);
  _hHeader = ListView_GetHeader(_hListView);
  return;
}

ListView::~ListView() {
  ListView::_sort_order = mk::ListView::SORT::ASCENDING;
  return;
}

void ListView::Resize(mk::ListView::MODE mode, uint32_t row_max,
                      uint32_t column_max) {
  const uint32_t old_row_max = _row_max;
  const uint32_t old_column_max = _column_max;
  _mode = mode;
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
      DWORD mask = LVS_REPORT | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT |
                   LVS_EX_HEADERDRAGDROP;
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
    (*data)[i] = buffer;
  }
  return;
}

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

void ListView::SetSelectedItem(uint32_t item) {
  ASSERT_RAW(item);
  ListView_SetItemState(_hListView, -1, 0, LVIS_SELECTED);
  SendMessage(_hListView, LVM_ENSUREVISIBLE, (WPARAM)item, FALSE);
  ListView_SetItemState(_hListView, item, LVIS_SELECTED, LVIS_SELECTED);
  return;
}

void ListView::SetIcon(uint32_t column, const std::vector<uint32_t>& index) {
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

void ListView::SetItems_TEXT(uint32_t column,
                             const std::vector<std::wstring>& data) {
  ASSERT_COLUMN(column);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.iSubItem = column;
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    lvi.pszText = (LPWSTR)data[i].c_str();
    lvi.cchTextMax = data[i].size();
    if (column == 0) {
      lvi.mask = LVIF_TEXT | LVIF_PARAM;
      lvi.lParam = i;  // Referenced in Compare_TEXT.
    } else {
      lvi.mask = LVIF_TEXT;
    }
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

void ListView::SortItems_TEXT(uint32_t key_column) {
  ASSERT_COLUMN(key_column);
  ListView_SortItems(_hListView, &ListView::Compare_TEXT, this);
  UpdateHeader(key_column);
  return;
}

void ListView::SetItems_INT(uint32_t column, const wchar_t* format,
                            const std::vector<int>& data) {
  ASSERT_COLUMN(column);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  lvi.iSubItem = column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    if (column == 0) {
      lvi.mask = LVIF_TEXT | LVIF_PARAM;
      lvi.lParam = i;  // Referenced in Compare_INT.
    } else {
      lvi.mask = LVIF_TEXT;
    }
    swprintf_s(buffer, ARRAYSIZE(buffer), format, data[i]);
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

void ListView::SortItems_INT(uint32_t key_column) {
  ASSERT_COLUMN(key_column);
  ListView_SortItems(_hListView, &ListView::Compare_INT, this);
  UpdateHeader(key_column);
  return;
}

void ListView::SetItems_DOUBLE(uint32_t column, const wchar_t* format,
                               const std::vector<double>& data) {
  ASSERT_COLUMN(column);
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  lvi.iSubItem = column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  uint32_t i_max = _row_max;
  if (i_max > data.size()) {
    i_max = data.size();
  }
  for (uint32_t i = 0; i < i_max; i++) {
    lvi.iItem = i;
    if (column == 0) {
      lvi.mask = LVIF_TEXT | LVIF_PARAM;
      lvi.lParam = i;  // Referenced in Compare_DOUBLE.
    } else {
      lvi.mask = LVIF_TEXT;
    }
    swprintf_s(buffer, ARRAYSIZE(buffer), format, data[i]);
    ListView_SetItem(_hListView, &lvi);
  }
  return;
}

void ListView::SortItems_DOUBLE(uint32_t key_column) {
  ASSERT_COLUMN(key_column);
  ListView_SortItems(_hListView, &ListView::Compare_DOUBLE, this);
  UpdateHeader(key_column);
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
    lvc.cx = MK_LV_DEF_COL_WIDTH;  // default.
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

void ListView::UpdateHeader(uint32_t new_key_column) {
  if (new_key_column == _last_key_column) {
    // Toggle sort state of current sort key column.
    switch (_sort_order) {
      case mk::ListView::SORT::DESCENDING:
        SetSortArrow(new_key_column, mk::ListView::SORT::ASCENDING);
        _sort_order = mk::ListView::SORT::ASCENDING;
        break;
      case mk::ListView::SORT::ASCENDING:
        SetSortArrow(new_key_column, mk::ListView::SORT::DESCENDING);
        _sort_order = mk::ListView::SORT::DESCENDING;
        break;
      default:
        // none.
        break;
    }
  } else {
    // Set arrow of header key of new sort key column.
    SetSortArrow(new_key_column, mk::ListView::SORT::DESCENDING);
    _sort_order = mk::ListView::SORT::DESCENDING;
    // Clear arrow of header key of last sort key column.
    SetSortArrow(_last_key_column, mk::ListView::SORT::NONE);
  }
  _key_column = new_key_column;
  _last_key_column = _key_column;
  return;
}

void ListView::SetSortArrow(uint32_t column, mk::ListView::SORT sort_order) {
  ASSERT_COLUMN(column);
  HDITEM hdi;
  ZeroMemory(&hdi, sizeof(hdi));
  hdi.mask = HDI_FORMAT;
  Header_GetItem(_hHeader, _last_key_column, &hdi);
  hdi.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP | HDF_IMAGE | HDF_BITMAP);
  switch (sort_order) {
    case mk::ListView::SORT::DESCENDING:
      hdi.fmt |= HDF_SORTDOWN;
      break;
    case mk::ListView::SORT::ASCENDING:
      hdi.fmt |= HDF_SORTUP;
      break;
    default:
      // none.
      break;
  }
  Header_SetItem(_hHeader, column, &hdi);
}

int CALLBACK ListView::Compare_TEXT(LPARAM lParam1, LPARAM lParam2,
                                    LPARAM lParamSort) {
  ListView* list_view = (ListView*)lParamSort;
  const int item1 = (int)lParam1;
  const int item2 = (int)lParam2;
  LVITEM lvi;
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = list_view->_key_column;
  // Read first value.
  lvi.iItem = item1;
  wchar_t first[MK_LV_BUF_MAX] = {0};
  lvi.pszText = first;
  lvi.cchTextMax = ARRAYSIZE(first);
  ListView_GetItem(list_view->_hListView, &lvi);
  // Read second value.
  wchar_t second[MK_LV_BUF_MAX] = {0};
  lvi.pszText = second;
  lvi.cchTextMax = ARRAYSIZE(second);
  lvi.iItem = item2;
  ListView_GetItem(list_view->_hListView, &lvi);
  // Comparison.
  int32_t cmp_result = wcscmp(first, second);
  if (cmp_result > 0) {
    return -1;
  } else if (cmp_result < 0) {
    return 1;
  } else {
    return 0;
  }
}

int CALLBACK ListView::Compare_INT(LPARAM lParam1, LPARAM lParam2,
                                   LPARAM lParamSort) {
  ListView* list_view = (ListView*)lParamSort;
  const int item1 = (int)lParam1;
  const int item2 = (int)lParam2;
  LVITEM lvi;
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = list_view->_key_column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  // Read first value.
  lvi.iItem = item1;
  ListView_GetItem(list_view->_hListView, &lvi);
  int first = 0;
  swscanf_s(buffer, L"%d", &first);
  // Read second value.
  lvi.iItem = item2;
  ListView_GetItem(list_view->_hListView, &lvi);
  int second = 0;
  swscanf_s(buffer, L"%d", &second);
  if (first > second) {
    return -1;
  } else if (first < second) {
    return 1;
  } else {
    return 0;
  }
}

int CALLBACK ListView::Compare_DOUBLE(LPARAM lParam1, LPARAM lParam2,
                                      LPARAM lParamSort) {
  ListView* list_view = (ListView*)lParamSort;
  const int item1 = (int)lParam1;
  const int item2 = (int)lParam2;
  LVITEM lvi;
  wchar_t buffer[MK_LV_BUF_MAX] = {0};
  ZeroMemory(&lvi, sizeof(lvi));
  lvi.mask = LVIF_TEXT;
  lvi.iSubItem = list_view->_key_column;
  lvi.pszText = buffer;
  lvi.cchTextMax = ARRAYSIZE(buffer);
  // Read first value.
  lvi.iItem = item1;
  ListView_GetItem(list_view->_hListView, &lvi);
  double first = 0;
  swscanf_s(buffer, L"%lf", &first);
  // Read second value.
  lvi.iItem = item2;
  ListView_GetItem(list_view->_hListView, &lvi);
  double second = 0;
  swscanf_s(buffer, L"%lf", &second);
  if (first > second) {
    return -1;
  } else if (first < second) {
    return 1;
  } else {
    return 0;
  }
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
