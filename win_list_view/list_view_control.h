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
#include <string>
#include <vector>

#include <commctrl.h>  // Included at last.

#define LISTVIEW_DEFAULT_COLUMN_WIDTH       (40)

class ListViewControl {
 public:
  enum MODE {
    ICON,
    SMALLICON,
    LIST,
    REPORT,
  };
  ListViewControl(HWND hListView, ListViewControl::MODE mode, int row_max,
                  int column_max);
  virtual ~ListViewControl();
  void Resize(ListViewControl::MODE mode, int row_max, int column_max);
  void SetColumnWidth(int column, int width);
  template <class T>
  void SetColumn(int column, const wchar_t* format, std::vector<T> data);
  // template <class T>
  // void SetColumn<std::wstring>(std::vector<T> data);

  static bool EnableListView();

 private:
  void ResizeRow(int old_row_max, int new_row_max);
  void ResizeColumn(int old_column_max, int new_column_max);

 private:
  HWND _hListView;
  int _row_max;
  int _column_max;
};

#endif  // LIST_VIEW_H_
