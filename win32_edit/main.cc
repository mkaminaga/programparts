  // @file main.cc
  // @brief Entry point.
  // @author Mamoru Kaminaga
  // @date 2017-12-07
  // Copyright 2017 Mamoru Kaminaga
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>

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
  HWND hwnd_edit = GetDlgItem(hwnd, IDC_ED);
  switch (id) {
    case IDC_ENABLE:
      Edit_Enable(hwnd_edit, TRUE);
      Edit_SetText(hwnd_edit, L"Enabled");
      break;
    case IDC_DISABLE:
      Edit_Enable(hwnd_edit, FALSE);
      Edit_SetText(hwnd_edit, L"Disabled");
      break;
    default:
      // No implementation.
      break;
  }
  // Warnings are prevented for non-used parameters.
  UNREFERENCED_PARAMETER(id);
  UNREFERENCED_PARAMETER(hwnd_ctrl);
  UNREFERENCED_PARAMETER(code_notify);
}
INT_PTR CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    HANDLE_DLG_MSG(hwnd, WM_INITDIALOG, OnCreate);
    HANDLE_DLG_MSG(hwnd, WM_DESTROY, OnDestroy);
    HANDLE_DLG_MSG(hwnd, WM_COMMAND, OnCommand);
    HANDLE_DLG_MSG(hwnd, WM_CLOSE, OnClose);
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
