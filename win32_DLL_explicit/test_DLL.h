//
// @file test_DLL.h
// @brief Test for dynamic link library.
// @author Mamoru Kaminaga
// @date 2019-07-02 10:09:01
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>

#ifndef _TEST_DLL_H_
//
// In source file of DLL, define DLLAPI for export in the following:
// #define DLLAPI extern "C" __declspec(dllexport)
//
// In source file of EXE, you don't have to define DLLAPI.
// The include guard in this header defines DLLAPI for import.
//
#ifndef DLLAPI
#define DLLAPI extern "C" __declspec(dllimport)
#endif

DLLAPI void HelloWorld();
DLLAPI int Increment(int v);
DLLAPI int Decrement(int v);

#endif  // _TEST_DLL_H_
