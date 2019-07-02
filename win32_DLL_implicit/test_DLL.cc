//
// @file test_DLL.cc
// @brief Test for dynamic link library.
// @author Mamoru Kaminaga
// @date 2019-07-02 10:13:52
// Copyright 2019 Mamoru Kaminaga
//
#define DLLAPI extern "C" __declspec(dllexport)

#include "./test_DLL.h"
#include <stdio.h>

DLLAPI void HelloWorld() { printf("Hello World!\n"); }
DLLAPI int Increment(int v) { return v + 1; }
DLLAPI int Decrement(int v) { return v - 1; }
