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
#include "./resource.h"
#include "./system_performance_monitor.h"
#include "./util.h"

namespace {
// Timer.
constexpr int TIMER_ID = 0;
constexpr int SAMPLING_TIME = 500;  // [ms].

// Performance monitor classes.
SystemPerformaceMonitor sys_monitor;

// Edit control.
HWND hEdit = NULL;
std::unique_ptr<EditControl> edit_cpu;
std::unique_ptr<EditControl> edit_idle;
std::unique_ptr<EditControl> edit_user;
std::unique_ptr<EditControl> edit_kernel;
}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  // Set refresh rate.
  SetTimer(hwnd, TIMER_ID, SAMPLING_TIME, NULL);

  // Get edit control handle.
  edit_cpu.reset(new EditControl(GetDlgItem(hwnd, IDC_CPU)));
  edit_idle.reset(new EditControl(GetDlgItem(hwnd, IDC_IDLE)));
  edit_user.reset(new EditControl(GetDlgItem(hwnd, IDC_USER)));
  edit_kernel.reset(new EditControl(GetDlgItem(hwnd, IDC_KERNEL)));
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  PostQuitMessage(0);
  return;
}

void Cls_OnClose(HWND hwnd) {
  DestroyWindow(hwnd);
  return;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;
  switch (id) {
    default:
      break;
  }
  return;
}

void Cls_OnTimer(HWND hwnd, UINT id) {
  (void)hwnd;
  (void)id;

  // Sample performances.
  sys_monitor.Sample();

  // Show system performance.
  edit_cpu->Set(L"%f", sys_monitor.GetCPU());
  edit_idle->Set(L"%lld", sys_monitor.GetIdleTime().QuadPart);
  edit_user->Set(L"%lld", sys_monitor.GetUserTime().QuadPart);
  edit_kernel->Set(L"%lld", sys_monitor.GetKernelTime().QuadPart);
  return;
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
