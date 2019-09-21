//
// @file util.h
// @brief Miscellaneous functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>
#include <windows.h>

int GetTimeFileName(wchar_t* dst, int dst_size, const wchar_t* prefix) {
  assert(dst);

  // Local time is acquired.
  time_t t = time(NULL);
  struct tm tim;
  localtime_s(&tim, &t);

  // File name is created using local time.
  int str_len = swprintf_s(dst, dst_size, L"%04d%02d%02d-%02d%02d%02d%ls",
                           tim.tm_year + 1900, tim.tm_mon, tim.tm_mday,
                           tim.tm_hour, tim.tm_min, tim.tm_sec, prefix);
  return str_len;
}
