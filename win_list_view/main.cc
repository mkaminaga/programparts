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
#include "../win32_edit_mini/edit.h"
#include "./list_view_control.h"
#include "./resource.h"
#include "./util.h"

#include <commctrl.h>  // Included at last.

namespace {
// List view.
std::unique_ptr<ListViewControl> list_view;
std::unique_ptr<EditControl> out_edit;

int row_max = 3;
int column_max = 4;
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
                                      column_max));

  // Edit control for test interface.
  out_edit.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT_OUTPUT)));
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
    case IDDETAIL:
      out_edit->Add(L"IDDETAIL\n");
      break;
    case IDLICON:
      out_edit->Add(L"IDLICON\n");
      break;
    case IDSICON:
      out_edit->Add(L"IDSICON\n");
      break;
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
