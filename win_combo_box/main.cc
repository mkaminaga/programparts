//
// @file main.cc
// @brief Combo box test.
// @author Mamoru Kaminaga
// @date 2019-12-25 19:02:14
// Copyright 2019 Mamoru Kaminaga
//
#include <windows.h>
#include "./resource.h"
#include "./util.h"

namespace {

HWND hComboBox = nullptr;
const char* BoxItems[] = {
    "Apple", "Banana", "Grape", "Orange", "Pineapple",
};

}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;
  (void)hwnd;

  // The icon is loaded.
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(hwnd, WM_SETICON, ICON_BIG,
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

  // Get window handle of controls.
  hComboBox = GetDlgItem(hwnd, IDC_COMBO1);

  // Insert items to combo box.
  for (int i = 0; i < ARRAYSIZE(BoxItems); i++) {
    SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)BoxItems[i]);
  }

  // Select item in combo box.
  SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  PostQuitMessage(0);
  return;
}

void Cls_OnClose(HWND hwnd) {
  EndDialog(hwnd, TRUE);
  return;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;
  switch (id) {
    case ID_OK: {
      char buffer[256] = {0};
      // Get selected item index.
      int index = SendMessage(hComboBox, CB_GETCURSEL, 0, NULL);
      printf("index: %d\n", index);

      // Get selected item size.
      int length = SendMessage(hComboBox, CB_GETLBTEXTLEN, index, NULL);
      printf("text length: %d\n", length);
      if (ARRAYSIZE(buffer) < length) {
        MessageBox(hwnd, "length exceeds box limit", "Error", MB_OK);
        break;
      }

      // Get Check selected item text.
      SendMessage(hComboBox, CB_GETLBTEXT, index, (WPARAM)buffer);
      printf("text string: %s\n", buffer);
      MessageBox(hwnd, buffer, "selected text", MB_OK);
    } break;
    case ID_CANCEL:
      // Close dialog.
      EndDialog(hwnd, TRUE);
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
      // none.
      return FALSE;
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPTSTR lpsCmdLine, int nCmdShow) {
  (void)hInstance;
  (void)hPrevInstance;
  (void)lpsCmdLine;
  (void)nCmdShow;
  mk::OpenConsole();
  DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, &DialogProc,
                 NULL);
  mk::CloseConsole();
  return 0;
}
