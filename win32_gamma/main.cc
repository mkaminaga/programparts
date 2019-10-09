//
// @file main.cc
// @brief Screen gamma test.
// @author Mamoru Kaminaga
// @date 2019-10-08 20:28:30
// Copyright 2019 Mamoru Kaminaga
//
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include "./resource.h"
#include "./util.h"

namespace {
HWND hEdit = NULL;
HDC hDisplay = NULL;
WORD ramp[3 * 256] = {0};
}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;

  // Get handles for desktop.
  hDisplay = GetDC(hEdit);

  // Get edit handle.
  hEdit = GetDlgItem(hwnd, IDC_EDIT1);

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
        PrintToEdit(hEdit, L"%d\t%d\t%d\t%d\n", i, static_cast<int>(ramp[i]),
                    static_cast<int>(ramp[256 + i]),
                    static_cast<int>(ramp[512 + i]));
      }
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
