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
  enum class DATATYPE {
    TEXT,
    INT,
    DOUBLE,
  };
  ListView(HWND hListView, mk::ListView::MODE mode, uint32_t row_max,
           uint32_t column_max);
  virtual ~ListView();

  //
  // Methods to set properties.
  //
  void Resize(mk::ListView::MODE mode, uint32_t new_row_max,
              uint32_t new_column_max);
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
  void SetItems_TEXT(uint32_t column, const std::vector<std::wstring>& data);
  void SetItems_INT(uint32_t column, const wchar_t* format,
                    const std::vector<int>& data);
  void SetItems_DOUBLE(uint32_t column, const wchar_t* format,
                       const std::vector<double>& data);
  void SortItems(uint32_t key_column);

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
  void SetSortArrow(uint32_t column, mk::ListView::SORTORDER sort_order);
  static int CALLBACK CompareFunction(LPARAM lParam1, LPARAM lParam2,
                                      LPARAM lParamSort);

 private:
  mk::ListView::MODE _mode;
  HWND _hListView;
  HWND _hHeader;
  uint32_t _row_max;
  uint32_t _column_max;
  uint32_t _last_key_column;                       // For sort.
  uint32_t _key_column;                            // For sort.
  mk::ListView::SORTORDER _sort_order;             // For sort.
  std::vector<mk::ListView::DATATYPE> _data_type;  // For sort.
  std::vector<std::vector<LPARAM>> _mirror_data;   // For sort.
};

}  // namespace mk

#endif  // LIST_VIEW_H_
