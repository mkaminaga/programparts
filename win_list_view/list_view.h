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
  enum class SORT {
    DESCENDING,
    ASCENDING,
    NONE,
  };
  ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
           uint32_t column_max);
  virtual ~ListView();

  //
  // Methods to set properties.
  //
  void Resize(mk::ListView::MODE mode, uint32_t row_max, uint32_t column_max);
  void SetFocus();
  void SetImageList(HIMAGELIST hImageList);

  //
  // For headers.
  //
  void SetHeaderWidth(uint32_t column, uint32_t width);
  void SetHeaderText(uint32_t column, const wchar_t* text);

  //
  // Methods for data input.
  //
  void SetSelectedItem(uint32_t item);
  void SetIcon(uint32_t column, const std::vector<uint32_t>& index);

  // SortItems_TEXT must be called to sort column which items are set by
  // SetItems_TEXT.
  void SetItems_TEXT(uint32_t column, const std::vector<std::wstring>& data);
  void SortItems_TEXT(uint32_t key_column);

  // SortItems_INT must be called to sort column which items are set by
  // SetItems_INT.
  void SetItems_INT(uint32_t column, const wchar_t* format,
                    const std::vector<int>& data);
  void SortItems_INT(uint32_t key_column);

  // SortItems_DOUBLE must be called to sort column which items are set by
  // SetItems_DOUBLE.
  void SetItems_DOUBLE(uint32_t column, const wchar_t* format,
                       const std::vector<double>& data);
  void SortItems_DOUBLE(uint32_t key_column);

  //
  // Methods for data output.
  //
  HWND GetHandle();
  uint32_t GetSelectedItem();
  void GetText(uint32_t column, std::vector<std::wstring>* data);

  // Methods for global purpose.
  static bool EnableListView();

 private:
  void ResizeRow(uint32_t old_row_max, uint32_t new_row_max);
  void ResizeColumn(uint32_t old_column_max, uint32_t new_column_max);
  void ToggleSortStatus(uint32_t key_column);
  static int CALLBACK Compare_TEXT(LPARAM lParam1, LPARAM lParam2,
                                   LPARAM lParamSort);
  static int CALLBACK Compare_INT(LPARAM lParam1, LPARAM lParam2,
                                  LPARAM lParamSort);
  static int CALLBACK Compare_DOUBLE(LPARAM lParam1, LPARAM lParam2,
                                     LPARAM lParamSort);

 private:
  mk::ListView::MODE _mode;
  mk::ListView::SORT _sort_order;  // For sort.
  uint32_t _last_key_column;       // For sort.
  uint32_t _key_column;            // For sort.
  HWND _hListView;
  HWND _hHeader;
  uint32_t _row_max;
  uint32_t _column_max;
};

}  // namespace mk

#endif  // LIST_VIEW_H_
