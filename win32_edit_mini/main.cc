//
// @file main.cc
// @brief Entry point.
// @author Mamoru Kaminaga
// @date 2017-12-07
// Copyright 2017 Mamoru Kaminaga
//
#include <wchar.h>
#include <windows.h>
#include <windowsx.h>
#include <memory>
#include "./edit.h"
#include "./resource.h"
#include "./util.h"

namespace {
std::unique_ptr<EditControl> edit_user;
std::unique_ptr<EditControl> edit_app;
std::unique_ptr<EditControl> edit_paste;
}  // namespace

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwnd_forcus, LPARAM lp) {
  (void)hwnd_forcus;
  (void)lp;

  // The icon is loaded.
  HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
  SendMessage(hwnd, WM_SETICON, ICON_BIG,
              (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1)));

  // Edit control classes are created .
  edit_user.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT1)));
  edit_app.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT2)));
  edit_paste.reset(new EditControl(GetDlgItem(hwnd, IDC_EDIT3)));
  return TRUE;
}

void Cls_OnDestroy(HWND hwnd) {
  (void)hwnd;
  return;
}

void Cls_OnClose(HWND hwnd) {
  EndDialog(hwnd, TRUE);
  return;
}

void ResetEditApps() {
  edit_app->Clear();
  edit_paste->Clear();
}

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;

  wchar_t buffer[256] = {0};
  switch (id) {
    case IDENABLE:
      ResetEditApps();
      edit_user->EnableInput();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Input is enabled.\n");
      break;
    case IDDISABLE:
      ResetEditApps();
      edit_user->DisableInput();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Input is disables (Read only).\n");
      break;
    case IDSHOW:
      ResetEditApps();
      edit_user->Show();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Edit control is shown.\n");
      break;
    case IDHIDE:
      ResetEditApps();
      edit_user->Hide();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Edit control is hidden.\n");
      break;
    case IDCLEAR:
      ResetEditApps();
      edit_user->Clear();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Text is cleared.\n");
      break;
    case IDCOPY:
      ResetEditApps();
      edit_user->Copy();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Text is copied.\n");
      break;
    case IDCUT:
      ResetEditApps();
      edit_user->Cut();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Text is cut.\n");
      break;
    case IDGET:
      ResetEditApps();
      edit_user->Get(buffer, ARRAYSIZE(buffer));

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Text is get from edit control\n%s\n", buffer);
      break;
    case IDPASTE:
      ResetEditApps();
      edit_user->Paste();

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Pasted text.\n");
      break;
    case IDSET:
      ResetEditApps();
      edit_user->Set(L"Set text.\n");

      // Response.
      edit_paste->Paste();
      edit_app->Set(L"Text is set to edit control.\n");
      break;
    case IDFOCUS:
      edit_paste->Paste();
      edit_app->Set(L"Set focus.\n");

      ResetEditApps();
      edit_user->Focus();
      break;
    case IDCBCLEAR:
      if (OpenClipboard(hwnd)) {
        EmptyClipboard();
        CloseClipboard();
        edit_app->Set(L"Clipboard is cleared.\n");
        edit_paste->Clear();
      } else {
        edit_app->Set(L"Error... Failed to clear clipboard.\n");
      }
    default:
      // No implementation.
      break;
  }
  return;
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

  DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, &DialogProc,
                 NULL);
  return 0;
}
