//
// @file main.cc
// @brief Performance monitor test.
// @author Mamoru Kaminaga
// @date 2019-10-12 15:43:10
// Copyright 2019 Mamoru Kaminaga
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <memory>
#include <string>
#include <vector>
#include "../win32_edit_mini/edit.h"
#include "./list_view_control.h"
#include "./resource.h"
#include "./util.h"

#include <commctrl.h>  // Included at last.

namespace {
// List view.
std::unique_ptr<ListViewControl> list_view;
std::unique_ptr<EditControl> out_edit;
std::unique_ptr<EditControl> row_edit;
std::unique_ptr<EditControl> col_edit;
std::unique_ptr<EditControl> width_edit;

int row_max = 3;
int col_max = 4;
std::vector<int> data_d;
std::vector<double> data_f;
std::vector<std::wstring> data_s;
}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  // The icon is loaded.
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(hwnd, WM_SETICON, ICON_BIG,
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

  // List view for test.
  ListViewControl::EnableListView();
  list_view.reset(new ListViewControl(GetDlgItem(hwnd, IDC_LIST1),
                                      ListViewControl::MODE::REPORT, row_max,
                                      col_max));
  // Test data.
  data_d.resize(row_max);
  data_f.resize(row_max);
  data_s.resize(row_max);
  for (int i = 0; i < row_max; i++) {
    data_d[i] = i;
    data_f[i] = 2.0 * i;
    data_s[i] = L"text";
  }

  // Edit control for test interface.
  out_edit.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT_OUTPUT)));
  row_edit.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT_SETROW)));
  col_edit.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT_SETCOL)));
  width_edit.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT_SETWIDTH)));
  out_edit->Set(L"List view test utility\n");
  row_edit->Set(L"%d", row_max);
  col_edit->Set(L"%d", col_max);
  width_edit->Set(L"%d", LISTVIEW_DEFAULT_COLUMN_WIDTH);
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
      out_edit->Add(L"IDLIST\n");
      break;
    case IDREPORT:
      out_edit->Add(L"IDDETAIL\n");
      break;
    case IDICON:
      out_edit->Add(L"IDLICON\n");
      break;
    case IDSMALLICON:
      out_edit->Add(L"IDSICON\n");
      break;
    case IDCLEAR:
      break;
    case IDCLEARALL:
      break;
    case IDDELETE:
      break;
    case IDDELETEALL:
      break;
    case IDGETALL:
      break;
    case IDGETITEM:
      break;
    case IDSETITEM:
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
      list_view->Resize(ListViewControl::MODE::REPORT, row_max, col_max);
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

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    HANDLE_DLG_MSG(hwndDlg, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_DLG_MSG(hwndDlg, WM_DESTROY, Cls_OnDestroy);
    HANDLE_DLG_MSG(hwndDlg, WM_CLOSE, Cls_OnClose);
    HANDLE_DLG_MSG(hwndDlg, WM_COMMAND, Cls_OnCommand);
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
