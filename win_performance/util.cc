//
// @file util.h
// @brief CPU performance monitoring test.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <windows.h>

ULARGE_INTEGER FILETIME_to_ULARGE_INTEGER(const FILETIME& file_time) {
  ULARGE_INTEGER result;
  result.LowPart = file_time.dwLowDateTime;
  result.HighPart = file_time.dwHighDateTime;
  return result;
}
