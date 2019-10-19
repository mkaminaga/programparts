//
// @file list_view.h
// @brief List view wrapper.
// @author Mamoru Kaminaga.
// @date 2019-10-16 09:03:55
// Copyright 2019 Mamoru Kaminaga.
//
#ifndef LIST_VIEW_H_
#define LIST_VIEW_H_

#include <windows.h>
#include <string>
#include <vector>

#include <commctrl.h>  // Included at last.

#define LISTVIEW_DEFAULT_COLUMN_WIDTH (40)

namespace mk {

class ListView {
 public:
  enum MODE {
    ICON,
    SMALLICON,
    LIST,
    REPORT,
  };
  ListView(HWND hListView, mk::ListView::MODE mode, int row_max,
           int column_max);
  virtual ~ListView();
  void Resize(mk::ListView::MODE mode, int row_max, int column_max);
  void SetColumnWidth(int column, int width);
  void SetColumnText(int column, const std::vector<std::wstring>& data);

  template <typename T>
  void SetColumnData(int column, const wchar_t* format,
                     const std::vector<T>& data);

  static bool EnableListView();

 private:
  void ResizeRow(int old_row_max, int new_row_max);
  void ResizeColumn(int old_column_max, int new_column_max);

 private:
  HWND _hListView;
  int _row_max;
  int _column_max;
};

}  // namespace mk

#endif  // LIST_VIEW_H_
