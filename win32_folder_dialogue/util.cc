//
// @file util.cc
// @brief Test project for folder dialogue.
// @author Mamoru Kaminaga
// @date 2019-07-02 18:56:28
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <shlobj.h>
#include <wchar.h>
#include <windows.h>

static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam,
                                       LPARAM lpData) {
  (void)hWnd;
  (void)lpData;

  wchar_t dir[MAX_PATH] = {0};
  ITEMIDLIST *pidl = NULL;

  switch (uMsg) {
    case BFFM_INITIALIZED:
      // The dialog box has finished initializing.
      break;
    case BFFM_IUNKNOWN:
      // An IUnknown interface is available to the dialog box.
      break;
    case BFFM_VALIDATEFAILED:
      // The user typed an invalid name into the dialog's edit box.
      // A nonexistent folder is considered an invalid name.
      MessageBox(hWnd, L"Invalid folder name!", L"Error", MB_OK);
      return 1;
    case BFFM_SELCHANGED:
      // The selection has changed in the dialog box.
      pidl = (ITEMIDLIST *)lParam;
      SHGetPathFromIDList(pidl, dir);
#ifdef DEBUG
      fwprintf(stderr, L"Select changed:%ls\n", dir);
      fwprintf(stderr, L"\n");
#endif
      break;
  }
  return 0;
}

bool GetDirectoryName(HWND hwnd, const wchar_t *title, const wchar_t *root_dir,
                      wchar_t *selected_dir) {
  assert(title);
  assert(selected_dir);

  PIDLIST_ABSOLUTE pidlRoot = NULL;

  // When root directory path is specified, the input path is converted to the
  // id list.
  if (root_dir != NULL) {
    // Root directory to item ID list.
    HRESULT hr = SHParseDisplayName((PCWSTR)root_dir, NULL, &pidlRoot, 0, NULL);
    if ((hr != S_OK) || (pidlRoot == NULL)) {
#ifdef DEBUG
      fwprintf(stderr, L"Invalid root directory\n");
#endif
      return false;
    }
  }

  // Set information about the folder dialog.
  BROWSEINFO bi;
  memset(&bi, 0, sizeof(BROWSEINFO));
  bi.hwndOwner = hwnd;
  bi.pidlRoot = pidlRoot;
  bi.pszDisplayName = (LPWSTR)selected_dir;
  bi.lpszTitle = title;
  bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_VALIDATE | BIF_USENEWUI;
  bi.lpfn = BrowseCallbackProc;
  bi.lParam = (LPARAM)root_dir;

  // Displays a dialog box that enables you to select a shell folder.
  LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
  if (pIDList == NULL) {
    selected_dir[0] = L'\0';
    return false;
  }

  //  Converts acquired item ID list to a file system path.
  if (!SHGetPathFromIDList(pIDList, selected_dir)) {
    CoTaskMemFree(pIDList);
    return false;
  }

  // Free the ID list allocated by SHBrowseForFolder.
  CoTaskMemFree(pIDList);
  return true;
}
