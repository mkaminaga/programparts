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

void Cls_OnCommand(HWND hwnd, int id, HWND hWndCtl, UINT codeNotify) {
  (void)hwnd;
  (void)hWndCtl;
  (void)codeNotify;

  wchar_t buffer[256] = {0};
  switch (id) {
    case IDENABLE:
      edit_user->Enable();

      // Response.
      edit_app->Set(L"Edit control is enabled.\n");
      break;
    case IDDISABLE:
      edit_user->Disable();

      // Response.
      edit_app->Set(L"Edit control is disabled.\n");
      break;
    case IDSHOW:
      edit_user->Show();

      // Response.
      edit_app->Set(L"Edit control is shown.\n");
      break;
    case IDHIDE:
      edit_user->Hide();

      // Response.
      edit_app->Set(L"Edit control is hidden.\n");
      break;
    case IDCLEAR:
      edit_user->Clear();

      // Response.
      edit_app->Set(L"Text is cleared.\n");
      break;
    case IDCLEARALL:
      edit_user->ClearAll();

      // Response.
      edit_app->Set(L"All text is cleared.\n");
      break;
    case IDCOPY:
      edit_user->Copy();

      // Response.
      edit_app->Set(L"Text is copied.\n");
      break;
    case IDCOPYALL:
      edit_user->CopyAll();

      // Response.
      edit_app->Set(L"All text is copied.\n");
      break;
    case IDCUT:
      edit_user->Cut();

      // Response.
      edit_app->Set(L"Text is cut.\n");
      break;
    case IDCUTALL:
      edit_user->CutAll();

      // Response.
      edit_app->Set(L"All text is cut.\n");
      break;
    case IDGET:
      edit_user->Get(buffer, ARRAYSIZE(buffer));

      // Response.
      edit_app->Set(L"Text is get from edit control.\n");
      edit_app->Add(L"%s", buffer);
      break;
    case IDGETALL:
      edit_user->GetAll(buffer, ARRAYSIZE(buffer));

      // Response.
      edit_app->Set(L"All text is get from edit control.\n");
      edit_app->Add(L"%s", buffer);
      break;
    case IDPASTE:
      edit_user->Paste();

      // Response.
      edit_app->Set(L"Pasted text.\n");
      break;
    case IDSET:
      edit_user->Set(L"Set text.\n");

      // Response.
      edit_app->Set(L"Text is set to edit control.\n");
      break;
    case IDADD:
      edit_user->Add(L"Added text.\n");

      // Response.
      edit_app->Set(L"Text is added to edit control.\n");
      break;
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
