//
// @file list_view.h
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#ifndef LIST_VIEW_H_
#define LIST_VIEW_H_

#include <stdint.h>
#include <windows.h>
#include <string>
#include <vector>

#include <commctrl.h>  // Included at last.

namespace mk {

class ListView {
 public:
  enum MODE {
    ICON,
    SMALLICON,
    LIST,
    REPORT,
  };
  ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
           uint32_t column_max);
  virtual ~ListView();

  // Methods to set properties.
  void Resize(mk::ListView::MODE mode, uint32_t row_max, uint32_t column_max);
  void SetFocus();
  void SetImageList(HIMAGELIST hImageList);

  // For headers.
  void SetHeaderWidth(uint32_t column, uint32_t width);
  void SetHeaderText(uint32_t column, const wchar_t* text);
  enum ARROW {
    NONE,
    UP,
    DOWN,
  };
  void SetHeaderArrow(uint32_t index, mk::ListView::ARROW arrow);
  void FixHeader(bool fixment);

  // Methods for data input.
  void SetSelectedItem(uint32_t item);
  void SetText(uint32_t column, const std::vector<std::wstring>& data);
  void SetIcon(uint32_t column, const std::vector<uint32_t>& index);
  template <typename T>
  void SetData(uint32_t column, const wchar_t* format,
               const std::vector<T>& data);

  // Methods for data output.
  HWND GetHandle();
  uint32_t GetSelectedItem();
  void GetText(uint32_t column, std::vector<std::wstring>* data);

  // Methods for global purpose.
  static bool EnableListView();

 private:
  void ResizeRow(uint32_t old_row_max, uint32_t new_row_max);
  void ResizeColumn(uint32_t old_column_max, uint32_t new_column_max);

 private:
  ListView::MODE _mode;
  HWND _hListView;
  HWND _hHeader;
  uint32_t _row_max;
  uint32_t _column_max;
};

}  // namespace mk

#endif  // LIST_VIEW_H_
