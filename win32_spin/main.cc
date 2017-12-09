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

int g_no = 0;

BOOL OnCreate(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  // The icon is loaded.
  HINSTANCE hinstance = (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(
      hwnd,
      WM_SETICON,
      ICON_BIG,
      (LPARAM) LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1)));

  // The edit is initialized.
  wchar_t buf[32] = {0};
  swprintf_s(buf, 10, L"%d", 0);
  SetDlgItemText(hwnd, IDC_ED_1, (LPCTSTR)buf);

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
      wprintf(L"OK\n");
      }
      break;
    case IDC_CANCEL:
      {
        wprintf(L"Cancel\n");
      }
      break;
    default:
      // No implementation.
      break;
  }
  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(hwnd);
  UNREFERENCED_PARAMETER(hwnd_ctrl);
  UNREFERENCED_PARAMETER(code_notify);
}
void OnNotify(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (wp) {
    case IDC_SP_1:
      {
        LPNMUPDOWN spin;
        wchar_t buf[32] = {0};
        spin = (LPNMUPDOWN) lp;
        if (spin->hdr.code == UDN_DELTAPOS) {
          GetDlgItemText(hwnd, IDC_ED_1, buf, sizeof(buf));
          g_no = _wtoi(buf);
          if ((spin->iDelta) < 0) {
            ++g_no;
          } else if ((spin->iDelta) > 0) {
            g_no -= 1;
          }
          swprintf_s(buf, 10, L"%d", g_no);
          SetDlgItemText(hwnd, IDC_ED_1, (LPCTSTR)buf);
        }
      }
      break;
    default:
      break;
  }

  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(msg);
}
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    HANDLE_DLG_MSG(hwnd, WM_INITDIALOG, OnCreate);
    HANDLE_DLG_MSG(hwnd, WM_DESTROY, OnDestroy);
    HANDLE_DLG_MSG(hwnd, WM_COMMAND, OnCommand);
    HANDLE_DLG_MSG(hwnd, WM_CLOSE, OnClose);
    case WM_NOTIFY:
      OnNotify(hwnd, msg, wp, lp);
      break;
    default:
      return FALSE;
  }
  return FALSE;
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
