//
// @file util.h
// @brief CPU performance monitoring test.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:30:36
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <windows.h>

ULARGE_INTEGER FILETIME_to_ULARGE_INTEGER(const FILETIME& file_time);

#endif  // _UTIL_H_
