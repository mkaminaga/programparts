//
// @file main.cc
// @brief Performance monitor test.
// @author Mamoru Kaminaga
// @date 2019-10-12 15:43:10
// Copyright 2019 Mamoru Kaminaga
#include <assert.h>
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

int row_max = 3;
int col_max = 3;
int selected_column = 0;
std::vector<int> data_d;
std::vector<double> data_f;
std::vector<std::wstring> data_s;
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
  data_d = {
    0, 1, 2,
  };
  data_f = {
    3.0, 4.0, 5.0,
  };
  data_s = {
    L"Apple", L"Banana", L"Grape",
  };
  list_view->SetText(0, data_s);
  list_view->SetData(1, L"%d", data_d);
  list_view->SetData(2, L"%5.3f", data_f);

  // Set column.
  list_view->SetColumnText(0, L"col 0");
  list_view->SetColumnText(1, L"col 1");
  list_view->SetColumnText(2, L"col 2");
  list_view->SetColumnWidth(0, 100);
  list_view->SetColumnWidth(1, 80);
  list_view->SetColumnWidth(2, 40);
  selected_column = 0;
  width_edit->Set(L"100\n");

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
    case IDGETITEM:
      out_edit->Add(L"Reserved\n");
      break;
    case IDSETITEM:
      out_edit->Add(L"Reserved\n");
      break;
    case IDSETSIZE: {
      wchar_t buffer[256] = {0};
      row_edit->Get(buffer, ARRAYSIZE(buffer));
      row_max = std::stoi(buffer);
      col_edit->Get(buffer, ARRAYSIZE(buffer));
      col_max = std::stoi(buffer);
      out_edit->Add(L"IDSETSIZE\n");
      out_edit->Add(L"row_max = %d, col_max = %d\n", row_max, col_max);
      out_edit->Add(L"\n");
      // Resize list view.
      list_view->Resize(mk::ListView::MODE::REPORT, row_max, col_max);
    } break;
    case IDSETWIDTH: {
      wchar_t buffer[256] = {0};
      width_edit->Get(buffer, ARRAYSIZE(buffer));
      int width = std::stoi(buffer);
      out_edit->Add(L"IDSETWIDTH\n");
      out_edit->Add(L"width = %d\n", width);
      out_edit->Add(L"\n");
      // Set column width.
      list_view->SetColumnWidth(0, width);
      break;
    }
    default:
      // none.
      break;
  }
  return;
}

LRESULT OnNofity(HWND hwndDlg, NMHDR* nmhdr) {
  assert(nmhdr);
  // if (nmhdr->hwndFrom == list_view->GetHandle()) {  // Access violation.
  if (nmhdr->hwndFrom == GetDlgItem(hwndDlg, IDC_LIST1)) {
    switch (nmhdr->code) {
      case LVN_COLUMNCLICK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        out_edit->Add(L"LVN_COLUMNCLICK\n");
        out_edit->Add(L"column = %d\n", lv->iSubItem);
        out_edit->Add(L"\n");
      } break;
      case NM_CLICK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        out_edit->Add(L"NM_CLICK\n");
        out_edit->Add(L"item = %d\n", lv->iItem);
        out_edit->Add(L"\n");
      } break;
      case NM_DBLCLK: {
        LPNMLISTVIEW lv = (LPNMLISTVIEW)nmhdr;
        out_edit->Add(L"NM_DBLCLK\n");
        out_edit->Add(L"item = %d\n", lv->iItem);
        out_edit->Add(L"\n");
      } break;
      case NM_CUSTOMDRAW: {
        LPNMLVCUSTOMDRAW draw = (LPNMLVCUSTOMDRAW)nmhdr;
        switch (draw->nmcd.dwDrawStage) {
          case CDDS_PREPAINT:
            out_edit->Add(L"CDDS_PREPAINT\n");
            SetWindowLong(hwndDlg, DWL_MSGRESULT, (LONG)CDRF_NOTIFYITEMDRAW);
            break;
          case CDDS_ITEMPREPAINT:
            out_edit->Add(L"CDDS_ITEMPREPAINT\n");
            assert(color_FG.size() >= draw->nmcd.dwItemSpec);
            assert(color_BG.size() >= draw->nmcd.dwItemSpec);
            draw->clrText = color_FG[draw->nmcd.dwItemSpec];
            draw->clrTextBk = color_BG[draw->nmcd.dwItemSpec];
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
