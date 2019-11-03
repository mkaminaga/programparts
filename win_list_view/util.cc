//
// @file util.h
// @brief List view test tool.
// @author Mamoru Kaminaga
// @date 2019-10-18 20:46:40
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include "./list_view.h"

namespace mk {

std::wstring SynthString(const wchar_t* format, ...) {
  wchar_t buffer[MAX_PATH] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);
  return buffer;
}

void TestData::Resize(uint32_t row_max) {
  icon_id.resize(row_max);
  data_d.resize(row_max);
  data_f.resize(row_max);
  data_s.resize(row_max);
}

HIMAGELIST GetImageList(SHFILEINFO* file_info) {
  assert(file_info);
  return (HIMAGELIST)SHGetFileInfo(L"C:\\", FILE_ATTRIBUTE_NORMAL, file_info,
                                   sizeof(SHFILEINFO),
                                   SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
}

uint32_t GetIconId(SHFILEINFO* file_info, const wchar_t* file_name) {
  assert(file_info);
  SHGetFileInfo(file_name, FILE_ATTRIBUTE_NORMAL, file_info, sizeof(SHFILEINFO),
                SHGFI_ICON | SHGFI_SMALLICON);
  return file_info->iIcon;
}

void SortIndices(uint32_t key_column, mk::ListView::SORTORDER sort_order,
                 mk::TestData* data, std::vector<size_t>* id) {
  assert(data);
  assert(id);
  switch (sort_order) {
    case mk::ListView::SORTORDER::DOWN:
      // argsort (up to down).
      switch (key_column) {
        case 0:  // data_s
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_s[l] > data->data_s[r];
          });
          break;
        case 1:  // data_d
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_d[l] > data->data_d[r];
          });
          break;
        case 2:  // data_f
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_f[l] > data->data_f[r];
          });
          break;
        default:
          // none.
          break;
      }
      break;
    case mk::ListView::SORTORDER::UP:
      // argsort (down to up).
      switch (key_column) {
        case 0:  // data_s
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_s[l] < data->data_s[r];
          });
          break;
        case 1:  // data_d
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_d[l] < data->data_d[r];
          });
          break;
        case 2:  // data_f
          std::sort(id->begin(), id->end(), [&data](size_t l, size_t r) {
            return data->data_f[l] < data->data_f[r];
          });
          break;
        default:
          // none.
          break;
      }
    default:
      break;
  }
  return;
}

void SortListViewItems(mk::ListView* list_view, TestData* src, TestData* dst,
                       uint32_t key_column, uint32_t* last_key_column,
                       mk::ListView::SORTORDER* sort_order) {
  assert(list_view);
  assert(sort_order);
  assert(src);
  assert(dst);

  // argument sort.
  std::vector<size_t> id(src->icon_id.size());
  std::iota(id.begin(), id.end(), 0);

  // Sort items and set header arrows.
  if (key_column == *last_key_column) {
    // Toggle sort state of current sort key column.
    switch (*sort_order) {
      case mk::ListView::SORTORDER::DOWN:
        // down to up.
        SortIndices(key_column, mk::ListView::SORTORDER::UP, src, &id);
        list_view->SetHeaderArrow(key_column, mk::ListView::SORTORDER::UP);
        *sort_order = mk::ListView::SORTORDER::UP;
        break;
      case mk::ListView::SORTORDER::UP:
        // up to down.
        SortIndices(key_column, mk::ListView::SORTORDER::DOWN, src, &id);
        list_view->SetHeaderArrow(key_column, mk::ListView::SORTORDER::DOWN);
        *sort_order = mk::ListView::SORTORDER::DOWN;
        break;
      default:
        // none.
        break;
    }
  } else {
    // Clear arrow of last key column header.
    if (*last_key_column < list_view->GetColumn()) {
      list_view->SetHeaderArrow(*last_key_column,
                                mk::ListView::SORTORDER::NONE);
    }
    // Set arrow of header key of new sort key column.
    SortIndices(key_column, mk::ListView::SORTORDER::DOWN, src, &id);
    list_view->SetHeaderArrow(key_column, mk::ListView::SORTORDER::DOWN);
    *sort_order = mk::ListView::SORTORDER::DOWN;
    *last_key_column = key_column;
  }

  // Apply sorted indices to list view.
  dst->icon_id.resize(src->icon_id.size());
  dst->data_s.resize(src->data_s.size());
  dst->data_d.resize(src->data_d.size());
  dst->data_f.resize(src->data_f.size());
  for (uint32_t i = 0; i < id.size(); i++) {
    dst->icon_id[i] = src->icon_id[id[i]];
    dst->data_s[i] = src->data_s[id[i]];
    dst->data_d[i] = src->data_d[id[i]];
    dst->data_f[i] = src->data_f[id[i]];
  }
  list_view->SetImage(0, dst->icon_id);
  list_view->SetData(0, dst->data_s, L"%s");
  list_view->SetData(1, dst->data_d, L"%d");
  list_view->SetData(2, dst->data_f, L"%f");
  return;
}

}  // namespace mk
