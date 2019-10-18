//
// @file util.h
// @brief List view test tool.
// @author Mamoru Kaminaga
// @date 2019-10-18 20:46:40
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <string>

namespace mk {

std::wstring SynthString(const wchar_t* format, ...) {
  wchar_t buffer[64] = {0};
  va_list args;
  va_start(args, format);
  vswprintf_s(buffer, ARRAYSIZE(buffer), format, args);
  return buffer;
}

}  // namespace mk
