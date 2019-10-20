//
// @file main.cc
// @brief Performance monitor test.
// @author Mamoru Kaminaga
// @date 2019-10-12 15:43:10
// Copyright 2019 Mamoru Kaminaga
//
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <string>
#include <vector>
#include "../win32_edit_mini/edit.h"
#include "./list_view.h"
#include "./resource.h"
#include "./util.h"

#include <commctrl.h>  // Included at last.

namespace {

// List view.
std::unique_ptr<mk::ListView> list_view;
std::unique_ptr<mk::Edit> in_edit;
std::unique_ptr<mk::Edit> out_edit;
std::unique_ptr<mk::Edit> row_edit;
std::unique_ptr<mk::Edit> col_edit;
std::unique_ptr<mk::Edit> width_edit;
std::unique_ptr<mk::Edit> select_edit;

uint32_t row_max = 3;
uint32_t col_max = 3;
uint32_t select_column = 0;
std::vector<uint32_t> icon_id;
std::vector<std::wstring> data_s;
std::vector<int> data_d;
std::vector<double> data_f;
std::vector<COLORREF> color_FG;
std::vector<COLORREF> color_BG;

}  // namespace

void ResetListViewForReportMode() {
  row_max = 3;
  col_max = 3;
  list_view->Resize(mk::ListView::MODE::REPORT, row_max, col_max);
  out_edit->Set(L"Reset ListView in REPORT mode.\n");
  row_edit->Set(L"%d", row_max);
  col_edit->Set(L"%d", col_max);

  // Set default data.
  data_s = {
      L"Apple",
      L"Banana",
      L"Grape",
  };
  data_d = {
      0,
      1,
      2,
  };
  data_f = {
      3.0,
      4.0,
      5.0,
  };
  list_view->SetItems_TEXT(0, data_s);
  list_view->SetItems_INT(1, L"%d", data_d);
  list_view->SetItems_DOUBLE(2, L"%5.3f", data_f);

  // Set header.
  list_view->SortItems_TEXT(0);
  list_view->SortItems_TEXT(0);

  // Icon image list.
  SHFILEINFO file_info;
  HIMAGELIST hImageList =
      (HIMAGELIST)SHGetFileInfo(L"C:\\", 0, &file_info, sizeof(file_info),
                                SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
  list_view->SetImageList(hImageList);

  // Icon image.
  icon_id.resize(3);
  SHGetFileInfo(L"apple.ico", 0, &file_info, sizeof(file_info),
                SHGFI_SYSICONINDEX);
  icon_id[0] = file_info.iIcon;
  SHGetFileInfo(L"banana.ico", 0, &file_info, sizeof(file_info),
                SHGFI_SYSICONINDEX);
  icon_id[1] = file_info.iIcon;
  SHGetFileInfo(L"grape.ico", 0, &file_info, sizeof(file_info),
                SHGFI_SYSICONINDEX);
  icon_id[2] = file_info.iIcon;
  list_view->SetIcon(0, icon_id);

  // Set column.
  list_view->SetHeaderText(0, L"col 0");
  list_view->SetHeaderText(1, L"col 1");
  list_view->SetHeaderText(2, L"col 2");
  list_view->SetHeaderWidth(0, 100);
  list_view->SetHeaderWidth(1, 80);
  list_view->SetHeaderWidth(2, 40);
  select_column = 0;
  width_edit->Set(L"100");
  select_edit->Set(L"0");

  // Prepare user color.
  color_FG.resize(row_max);
  color_BG.resize(row_max);
  for (auto& c : color_FG) {
    c = RGB(0x56, 0x3E, 0xA3);
  }
  for (auto& c : color_BG) {
    c = RGB(0xFF, 0xDA, 0x90);
  }
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  // The icon is loaded.
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(hwnd, WM_SETICON, ICON_BIG,
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

  // Edit control for test interface.
  out_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_OUTPUT)));
  in_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_INPUT)));
  row_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_SETROW)));
  col_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_SETCOL)));
  width_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_SETWIDTH)));
  select_edit.reset(new mk::Edit(GetDlgItem(hwnd, IDC_EDIT_SETSELECT)));

  // List view for test.
  mk::ListView::EnableListView();
  list_view.reset(new mk::ListView(GetDlgItem(hwnd, IDC_LIST1),
                                   mk::ListView::MODE::REPORT, row_max,
                                   col_max));
  ResetListViewForReportMode();

  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  PostQuitMessage(0);
  return;
}

void Cls_OnClose(HWND hwnd) {
  (void)hwnd;
  EndDialog(hwnd, TRUE);
  return;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;
  switch (id) {
    case IDLIST:
      ResetListViewForReportMode();
      break;
    case IDREPORT:
      // Reserved.
      out_edit->Add(L"Reserved\n");
      break;
    case IDICON:
      // Reserved.
      out_edit->Add(L"Reserved\n");
      break;
    case IDSMALLICON:
      // Reserved.
      out_edit->Add(L"Reserved\n");
      break;
    case IDCLEAR:
      out_edit->Add(L"Reserved\n");
      break;
    case IDCLEARALL:
      out_edit->Add(L"Reserved\n");
      break;
    case IDDELETE:
      out_edit->Add(L"Reserved\n");
      break;
    case IDDELETEALL:
      out_edit->Add(L"Reserved\n");
      break;
    case IDGETITEM: {
      out_edit->Add(L"IDGETITEM\n");
      std::vector<std::wstring> data;
      for (uint32_t i = 0; i < col_max; i++) {
        list_view->GetText(i, &data);
        // Debug string output.
        out_edit->Add(L"  column = %d:\n", i);
        for (uint32_t j = 0; j < data.size(); j++) {
          out_edit->Add(L"    item = %s\n", data[j].c_str());
        }
      }
      out_edit->Add(L"\n");
    } break;
    case IDSETITEM:
      out_edit->Add(L"Reserved\n");
      break;
    case IDSETSIZE: {
      row_max = std::stoi(row_edit->Get());
      col_max = std::stoi(col_edit->Get());
      if (data_d.size() < row_max) {
        data_d.resize(row_max);
        data_f.resize(row_max);
        data_s.resize(row_max);
        color_FG.resize(row_max);
        color_BG.resize(row_max);
      }
      // Debug string output.
      out_edit->Add(L"IDSETSIZE\n");
      out_edit->Add(L"row_max = %d, col_max = %d\n", row_max, col_max);
      out_edit->Add(L"\n");
      // Resize list view.
      list_view->Resize(mk::ListView::MODE::REPORT, row_max, col_max);
    } break;
    case IDSETWIDTH: {
      uint32_t width = std::stoi(width_edit->Get());
      list_view->SetHeaderWidth(0, width);
      // Debug string output.
      out_edit->Add(L"IDSETWIDTH\n");
      out_edit->Add(L"width = %d\n", width);
      out_edit->Add(L"\n");
      break;
    }
    case IDSETSELECT: {
      uint32_t item = std::stoi(select_edit->Get());
      if ((item < 0) || (item > row_max)) {
        out_edit->Add(L"Invalid range\n");
        break;
      }
      list_view->SetSelectedItem(item);
      // Debug string output.
      out_edit->Add(L"IDSETSELECT\n");
      out_edit->Add(L"item = %d\n", item);
      out_edit->Add(L"\n");
    } break;
    default:
      // none.
      break;
  }
  return;
}

LRESULT OnNofity(HWND hwndDlg, NMHDR* nmhdr) {
  assert(nmhdr);
  if (nmhdr->hwndFrom == ListView_GetHeader(GetDlgItem(hwndDlg, IDC_LIST1))) {
    switch (nmhdr->code) {
      case HDN_ITEMCLICK:
      case HDN_ITEMDBLCLICK: {
        LPNMHEADERA hd = (LPNMHEADERA)nmhdr;
        // Debug string output.
        out_edit->Add(L"HDN_ITEMCLICK\n");
        out_edit->Add(L"index = %d\n", hd->iItem);
        // Header click sort.
        for (uint32_t i = 0; i < col_max; i++) {
          if (i == static_cast<uint32_t>(hd->iItem)) {
            switch (i) {
              case 0:
                list_view->SortItems_TEXT(0);
                out_edit->Add(L"sorted by TEXT.\n");
                out_edit->Add(L"\n");
                break;
              case 1:
                list_view->SortItems_INT(1);
                out_edit->Add(L"sorted by INT.\n");
                out_edit->Add(L"\n");
                break;
              case 2:
                list_view->SortItems_DOUBLE(2);
                out_edit->Add(L"sorted by DOUBLE.\n");
                out_edit->Add(L"\n");
                break;
              default:
                // none.
                break;
            }
          }
        }
      } break;
      default:
        // none.
        break;
    }
  } else if (nmhdr->hwndFrom == GetDlgItem(hwndDlg, IDC_LIST1)) {
    // if (nmhdr->hwndFrom == list_view->GetHandle()) {  // Access violation.
    switch (nmhdr->code) {
      case LVN_COLUMNCLICK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        // Debug string output.
        out_edit->Add(L"LVN_COLUMNCLICK\n");
        out_edit->Add(L"column = %d\n", lv->iSubItem);
        out_edit->Add(L"\n");
      } break;
      case NM_CLICK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        select_edit->Set(L"%d", lv->iItem);
        // Debug string output.
        out_edit->Add(L"NM_CLICK\n");
        out_edit->Add(L"item = %d\n", lv->iItem);
        out_edit->Add(L"\n");
      } break;
      case NM_DBLCLK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        select_edit->Set(L"%d", lv->iItem);
        // Debug string output.
        out_edit->Add(L"NM_DBLCLK\n");
        out_edit->Add(L"item = %d\n", lv->iItem);
        out_edit->Add(L"\n");
      } break;
      case NM_CUSTOMDRAW: {
        LPNMLVCUSTOMDRAW draw = (LPNMLVCUSTOMDRAW)nmhdr;
        switch (draw->nmcd.dwDrawStage) {
          case CDDS_PREPAINT:
            // Debug string output.
            out_edit->Add(L"CDDS_PREPAINT\n");
            // Use custom draw notification.
            SetWindowLong(hwndDlg, DWL_MSGRESULT, (LONG)CDRF_NOTIFYITEMDRAW);
            break;
          case CDDS_ITEMPREPAINT:
            assert(color_FG.size() >= draw->nmcd.dwItemSpec);
            assert(color_BG.size() >= draw->nmcd.dwItemSpec);
            draw->clrText = color_FG[draw->nmcd.dwItemSpec];
            draw->clrTextBk = color_BG[draw->nmcd.dwItemSpec];
            // Debug string output.
            out_edit->Add(L"CDDS_ITEMPREPAINT\n");
            // Use custom draw notification.
            SetWindowLong(hwndDlg, DWL_MSGRESULT, (LONG)CDRF_NEWFONT);
            break;
          default:
            // none.
            break;
        }
      }
      default:
        // none.
        break;
    }
  }
  return TRUE;
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    HANDLE_DLG_MSG(hwndDlg, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_DLG_MSG(hwndDlg, WM_DESTROY, Cls_OnDestroy);
    HANDLE_DLG_MSG(hwndDlg, WM_CLOSE, Cls_OnClose);
    HANDLE_DLG_MSG(hwndDlg, WM_COMMAND, Cls_OnCommand);
    case WM_NOTIFY:
      return OnNofity(hwndDlg, (NMHDR*)lParam);
    default:
      // none.
      return FALSE;
  }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;

  DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, &DialogProc,
                 NULL);
  return 0;
}
