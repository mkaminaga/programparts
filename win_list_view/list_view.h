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
  enum class MODE {
    ICON,
    SMALLICON,
    LIST,
    REPORT,
  };
  enum class SORTORDER {
    DOWN,
    UP,
    NONE,
  };
  ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
           uint32_t column_max);
  virtual ~ListView();
  HWND GetHandle();

  // Properties.
  void Resize(mk::ListView::MODE mode, uint32_t row_max, uint32_t column_max);
  void SetFocus();
  uint32_t GetSelection();
  void SetSelection(uint32_t item);

  // Setters and getters.
  void SetData(uint32_t column, const std::vector<std::wstring>& data,
               const wchar_t* format);
  void SetData(uint32_t column, const std::vector<int>& data,
               const wchar_t* format);
  void SetData(uint32_t column, const std::vector<double>& data,
               const wchar_t* format);
  void GetText(uint32_t column, std::vector<std::wstring>* data);
  uint32_t GetRow() const;
  uint32_t GetColumn() const;
  void SetImageList(HIMAGELIST hImageList);
  void SetImage(uint32_t column, const std::vector<uint32_t>& index);

  // Headers.
  HWND GetHeaderHandle();
  void SetHeaderWidth(uint32_t column, uint32_t width);
  void SetHeaderText(uint32_t column, const wchar_t* text);
  void SetHeaderArrow(uint32_t column, mk::ListView::SORTORDER sort_order);

  // Methods for global purpose.
  static bool EnableListView();

 private:
  void ResizeTable(mk::ListView::MODE mode, uint32_t old_row_max,
                   uint32_t old_column_max, uint32_t new_row_max,
                   uint32_t new_column_max);
  void ResizeRow(uint32_t old_row_max, uint32_t new_row_max);
  void ResizeColumn(uint32_t old_column_max, uint32_t new_column_max);
  static int CALLBACK CompareFunction(LPARAM lParam1, LPARAM lParam2,
                                      LPARAM lParamSort);

 private:
  HWND _hListView;
  HWND _hHeader;
  mk::ListView::MODE _mode;
  uint32_t _row_max;
  uint32_t _column_max;
};

}  // namespace mk

#endif  // LIST_VIEW_H_
