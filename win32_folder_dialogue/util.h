//
// @file util.h
// @brief Test project for folder dialogue.
// @author Mamoru Kaminaga
// @date 2019-07-02 18:56:28
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <wchar.h>
#include <windows.h>

bool GetDirectoryName(HWND hwnd, const wchar_t *title, const wchar_t *root_dir,
                      wchar_t *selected_dir);
#endif  // _UTIL_H_
