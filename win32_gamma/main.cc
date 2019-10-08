//
// @file main.cc
// @brief Screen gamma test.
// @author Mamoru Kaminaga
// @date 2019-10-08 20:28:30
// Copyright 2019 Mamoru Kaminaga
//
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./resource.h"

// Message cracker wrapper for DialogProc.
#define HANDLE_DLG_MSG(hwndDlg, msg, fn)     \
  case (msg):                                \
    return SetDlgMsgResult((hwndDlg), (msg), \
                           HANDLE_##msg((hwndDlg), (wParam), (lParam), (fn)));

namespace {
HWND hEdit1 = NULL;
HDC hDisplay = NULL;
WORD ramp[3 * 256] = {0};
}  // namespace

bool PrintToEdit(HWND hEdit, const wchar_t* format, ...) {
  wchar_t buffer[64] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);
  Edit_SetText(hEdit, buffer);

  int index = GetWindowTextLength(hEdit);
  SetFocus(hEdit);
  SendMessage(hEdit, EM_SETSEL, (WPARAM)index, (LPARAM)index);
  SendMessage(hEdit, EM_REPLACESEL, 0, (LPARAM)buffer);
#if 1
  fwprintf(stderr, L"%d, %ls", index, buffer);
#endif
  return true;
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;

  // Get handles for desktop.
  hDisplay = GetDC(hEdit1);

  // Get edit handle.
  hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);

  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;

  // Release handles for desktop.
  DeleteDC(hDisplay);

  PostQuitMessage(0);
}

void Cls_OnClose(HWND hwnd) { DestroyWindow(hwnd); }

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;
  switch (id) {
    case IDGET:
      if (GetDeviceGammaRamp(hDisplay, ramp) == FALSE) {
        MessageBox(hwnd, L"Failed to get gamma ramp.", L"Error", MB_OK);
        break;
      }
      for (int i = 0; i < 256; i++) {
        PrintToEdit(hEdit1, L"%d, %d, %d, %d\n", i, static_cast<int>(ramp[i]),
                    static_cast<int>(ramp[256 + i]),
                    static_cast<int>(ramp[512 + i]));
      }
      break;
    case IDSET:
      break;
    default:
      // No implementation.
      break;
  }
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    HANDLE_DLG_MSG(hwndDlg, WM_INITDIALOG, Cls_OnInitDialog);
    HANDLE_DLG_MSG(hwndDlg, WM_DESTROY, Cls_OnDestroy);
    HANDLE_DLG_MSG(hwndDlg, WM_COMMAND, Cls_OnCommand);
    HANDLE_DLG_MSG(hwndDlg, WM_CLOSE, Cls_OnClose);
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

#ifdef DEBUG
  FILE* fp = nullptr;
  AllocConsole();
  _wfreopen_s(&fp, L"CONOUT$", L"w", stdout);
  _wfreopen_s(&fp, L"CONOUT$", L"w", stderr);
  _wfreopen_s(&fp, L"CONIN$", L"r", stdin);
#endif

#ifdef DEBUG
  fwprintf(stdout, L"Hello world to stdout!\n");
  fwprintf(stderr, L"Hello world to stderr!\n");
  fwprintf(stderr, L"\n");
#endif

  // The dialog is opened.
  DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, &DialogProc,
                 NULL);

#ifdef DEBUG
  FreeConsole();
#endif

  return 0;
}
