//
// @file folder_dialog.h
// @brief Folder dialogue related functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _FOLDER_DIALOG_H_
#define _FOLDER_DIALOG_H_

#include <wchar.h>
#include <windows.h>

bool GetDirectoryName(HWND hwnd, const wchar_t *title, const wchar_t *root_dir,
                      wchar_t *selected_dir);
#endif  // _FOLDER_DIALOG_H_
