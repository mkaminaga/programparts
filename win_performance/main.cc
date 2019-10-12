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
#include "./resource.h"
#include "./system_performance_monitor.h"
#include "./util.h"

namespace {
// Timer.
constexpr int TIMER_ID = 0;
constexpr int SAMPLING_TIME = 500;  // [ms].

// Performance monitor classes.
SystemPerformaceMonitor system_performance_monitor;

// Edit control.
HWND hEdit = NULL;

}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  SetTimer(hwnd, TIMER_ID, SAMPLING_TIME, NULL);

  // Get edit control handle.
  hEdit = GetDlgItem(hwnd, IDC_EDIT1);
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  PostQuitMessage(0);
}

void Cls_OnClose(HWND hwnd) { DestroyWindow(hwnd); }

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;
  switch (id) {
    case IDCLEAR:
      ClearEdit(hEdit);
      break;
    case IDCOPY:
      CopyEdit(hEdit);
      break;
    default:
      // No implementation.
      break;
  }
}

void Cls_OnTimer(HWND hwnd, UINT id) {
  (void)hwnd;
  (void)id;

  // system_performance_monitor.Sample();

#if 1
  PrintEdit(hEdit, L"Test!\n");
#endif
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    HANDLE_DLG_MSG(hwndDlg, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_DLG_MSG(hwndDlg, WM_DESTROY, Cls_OnDestroy);
    HANDLE_DLG_MSG(hwndDlg, WM_CLOSE, Cls_OnClose);
    HANDLE_DLG_MSG(hwndDlg, WM_COMMAND, Cls_OnCommand);
    HANDLE_DLG_MSG(hwndDlg, WM_TIMER, Cls_OnTimer);
    default:
      return FALSE;
  }
  return FALSE;
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
