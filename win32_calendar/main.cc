  // @file main.cc
  // @brief Entry point.
  // @author Mamoru Kaminaga
  // @date 2017-12-07
  // Copyright 2017 Mamoru Kaminaga
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include "./resource.h"

  // Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwnd, msg, fn)\
  case (msg): return SetDlgMsgResult((hwnd), (msg), \
      HANDLE_##msg((hwnd), (wp), (lp), (fn)));

BOOL OnCreate(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  // The icon is loaded.
  HINSTANCE hinstance = (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(
      hwnd,
      WM_SETICON,
      ICON_BIG,
      (LPARAM) LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1)));

  // The calendar is initialized.
  HWND hwnd_cal = GetDlgItem(hwnd, IDC_CAL);
  MonthCal_SetMaxSelCount(hwnd_cal, 20);
  MonthCal_SetMonthDelta(hwnd_cal, 1);

  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(hwnd_forcus);
  UNREFERENCED_PARAMETER(lp);
  return TRUE;
}
void OnDestroy(HWND hwnd) {
  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(hwnd);
}
void OnClose(HWND hwnd) {
  // The modal dialog is ended.
  EndDialog(hwnd, TRUE);
}
void OnCommand(HWND hwnd, int id, HWND hwnd_ctrl, UINT code_notify) {
  switch (id) {
    case IDC_OK:
      {
        // The range is acquired.
        SYSTEMTIME range[2] = {0};
        HWND hwnd_cal = GetDlgItem(hwnd, IDC_CAL);
        MonthCal_GetSelRange(hwnd_cal, range);
        wprintf(L"Selected: %4d/%2d/%2d - %2d/%2d/%2d\n",
            range[0].wYear, range[0].wMonth, range[0].wDay,
            range[1].wYear, range[1].wMonth, range[1].wDay);
      }
      break;
    case IDC_CANCEL:
      {
        // The range is cleared.
        SYSTEMTIME today;
        HWND hwnd_cal = GetDlgItem(hwnd, IDC_CAL);
        MonthCal_GetToday(hwnd_cal, &today);
        SYSTEMTIME range[2] = { today, today };
        MonthCal_SetSelRange(hwnd_cal, range);
        wprintf(L"Cleared: %4d/%2d/%2d\n",
            today.wYear, today.wMonth, today.wDay);
      }
      break;
    default:
      // No implementation.
      break;
  }
  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(hwnd_ctrl);
  UNREFERENCED_PARAMETER(code_notify);
}
void OnNotify(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  NMSELCHANGE* nmsel_change = (NMSELCHANGE*) lp;
  HWND hwnd_cal = GetDlgItem(hwnd, IDC_CAL);
  if (nmsel_change->nmhdr.hwndFrom == hwnd_cal) {
    if (nmsel_change->nmhdr.code == MCN_SELCHANGE) {
      // The range is acquired.
      wprintf(L"Notify: %4d/%2d/%2d - %2d/%2d/%2d\n",
          nmsel_change->stSelStart.wYear,
          nmsel_change->stSelStart.wMonth,
          nmsel_change->stSelStart.wDay,
          nmsel_change->stSelEnd.wYear,
          nmsel_change->stSelEnd.wMonth,
          nmsel_change->stSelEnd.wDay);
    }
  }
  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(hwnd);
}
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    HANDLE_DLG_MSG(hwnd, WM_INITDIALOG, OnCreate);
    HANDLE_DLG_MSG(hwnd, WM_DESTROY, OnDestroy);
    HANDLE_DLG_MSG(hwnd, WM_COMMAND, OnCommand);
    HANDLE_DLG_MSG(hwnd, WM_CLOSE, OnClose);
    case WM_NOTIFY:  // For this case, message cracker doesn't exist.
      OnNotify(hwnd, msg, wp, lp);
      break;
    default:
      return FALSE;
  }
}

int WINAPI wWinMain(
    HINSTANCE hinstance,
    HINSTANCE not_used,
    LPTSTR cmdline,
    int cmdshow) {
  // An console is allocated for stdio.
  FILE* fp = nullptr;
  AllocConsole();
  _wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
  _wfreopen_s(&fp, L"CONOUT$", L"w", stderr);
  _wfreopen_s(&fp, L"CONIN$", L"r", stdin);

  // The dialog is opened.
  DialogBoxParam(
      hinstance,
      MAKEINTRESOURCE(IDD_DIALOG1),
      nullptr,
      &DialogProc,
      NULL);

  // The console is released.
  FreeConsole();

  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(not_used);
  UNREFERENCED_PARAMETER(cmdline);
  UNREFERENCED_PARAMETER(cmdshow);
  return 0;
}
