//
// @file util.cc
// @brief Test for dynamic link library.
// @author Mamoru Kaminaga
// @date 2019-07-02 10:13:52
// Copyright 2019 Mamoru Kaminaga
//
#define DLLAPI extern "C" __declspec(dllexport)

#include "./util.h"
#include <stdio.h>

DLLAPI void HelloWorld() { wprintf(L"Hello World!\n"); }
