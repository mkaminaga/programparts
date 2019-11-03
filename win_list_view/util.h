//
// @file util.h
// @brief List view test tool.
// @author Mamoru Kaminaga
// @date 2019-10-18 20:46:40
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdint.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <string>
#include "./list_view.h"

// Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwndDlg, msg, fn)     \
  case (msg):                                \
    return SetDlgMsgResult((hwndDlg), (msg), \
                           HANDLE_##msg((hwndDlg), (wParam), (lParam), (fn)));

namespace mk {

std::wstring SynthString(const wchar_t* format, ...);

struct TestData {
  std::vector<uint32_t> icon_id;
  std::vector<std::wstring> data_s;  // column 0.
  std::vector<int> data_d;           // column 1.
  std::vector<double> data_f;        // column 2.
};

HIMAGELIST GetImageList(SHFILEINFO* file_info);
uint32_t GetIconId(SHFILEINFO* file_info, const wchar_t* file_name);
void SortListViewItems(mk::ListView* list_view, TestData* src, TestData* dst,
                       uint32_t key_column, uint32_t* last_key_column,
                       mk::ListView::SORTORDER* sort_order);

}  // namespace mk

#endif  // _UTIL_H_
