//
// @file util.h
// @brief Test for dynamic link library.
// @author Mamoru Kaminaga
// @date 2019-07-02 10:09:01
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _TEST_DLL_H_

#include <stdio.h>

#ifndef DLLAPI
#define DLLAPI extern "C" __declspec(dllimport)
#endif

DLLAPI void HelloWorld();

#endif  // _TEST_DLL_H_
