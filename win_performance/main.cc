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
#include "./process_performance_monitor.h"
#include "./resource.h"
#include "./system_performance_monitor.h"
#include "./util.h"

namespace {
// Timer.
constexpr int TIMER_ID = 0;
constexpr int SAMPLING_TIME = 500;  // [ms].

// Performance monitor classes.
std::unique_ptr<SystemPerformaceMonitor> system_performance_monitor;
std::unique_ptr<ProcessPerformaceMonitor> process_performance_monitor;

// Handle for dummy load process.
HANDLE hLoad = NULL;

// Edit control.
HWND hEdit = NULL;
std::unique_ptr<EditControl> edit_total_cpu;
std::unique_ptr<EditControl> edit_user_cpu;
std::unique_ptr<EditControl> edit_kernel_cpu;
std::unique_ptr<EditControl> edit_idle;
std::unique_ptr<EditControl> edit_user;
std::unique_ptr<EditControl> edit_kernel;
std::unique_ptr<EditControl> edit_idle_delta;
std::unique_ptr<EditControl> edit_user_delta;
std::unique_ptr<EditControl> edit_kernel_delta;
}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  // The icon is loaded.
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(hwnd, WM_SETICON, ICON_BIG,
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

  // Set refresh rate.
  SetTimer(hwnd, TIMER_ID, SAMPLING_TIME, NULL);

  // Initialize system performance monitors.
  system_performance_monitor.reset(new SystemPerformaceMonitor());
  process_performance_monitor.reset(
      system_performance_monitor->CreateProcessPerformanceMonitor());

  // TODO(Mamoru):Start dummy load process.

  // Get edit control handle.
  edit_total_cpu.reset(new EditControl(GetDlgItem(hwnd, IDC_TOTAL_CPU)));
  edit_user_cpu.reset(new EditControl(GetDlgItem(hwnd, IDC_USER_CPU)));
  edit_kernel_cpu.reset(new EditControl(GetDlgItem(hwnd, IDC_KERNEL_CPU)));
  edit_idle.reset(new EditControl(GetDlgItem(hwnd, IDC_IDLE)));
  edit_user.reset(new EditControl(GetDlgItem(hwnd, IDC_USER)));
  edit_kernel.reset(new EditControl(GetDlgItem(hwnd, IDC_KERNEL)));
  edit_idle_delta.reset(new EditControl(GetDlgItem(hwnd, IDC_IDLE_DELTA)));
  edit_user_delta.reset(new EditControl(GetDlgItem(hwnd, IDC_USER_DELTA)));
  edit_kernel_delta.reset(new EditControl(GetDlgItem(hwnd, IDC_KERNEL_DELTA)));
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  PostQuitMessage(0);
  return;
}

void Cls_OnClose(HWND hwnd) {
  // TODO(Mamoru):Close dummy load process.

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
  system_performance_monitor->Sample();

  // Show system performance (%).
  edit_total_cpu->Set(L"%f", system_performance_monitor->GetTotalCPU());
  edit_user_cpu->Set(L"%f", system_performance_monitor->GetUserCPU());
  edit_kernel_cpu->Set(L"%f", system_performance_monitor->GetKernelCPU());

  // Show system time (absolute)
  ULONGLONG system_idle, system_user, system_kernel;
  system_performance_monitor->GetCPUTime(&system_user, &system_kernel);
  system_performance_monitor->GetCPUIdleTime(&system_idle);
  edit_idle->Set(L"%I64d", system_idle);
  edit_user->Set(L"%I64d", system_user);
  edit_kernel->Set(L"%I64d", system_kernel);

  // Show system time (delta)
  system_performance_monitor->GetCPUTime(&system_user, &system_kernel);
  system_performance_monitor->GetCPUIdleDeltaTime(&system_idle);
  edit_idle_delta->Set(L"%I64d", system_idle);
  edit_user_delta->Set(L"%I64d", system_user);
  edit_kernel_delta->Set(L"%I64d", system_kernel);

  // TODO(Mamoru): Add process performance monitor code here!
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
