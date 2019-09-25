//
// @file sub.cc
// @brief Compile option experiment.
// @author Mamoru Kaminaga
// @date 2019-09-25 19:45:45
// Copyright 2019
//
#include "./sub.h"
#include <stdio.h>
#include <vector>

void PrintVector() {
  std::vector<int> array(3);
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  for (unsigned int i = 0; i < array.size(); i++) {
    fwprintf(stdout, L"array[%d] = %d\n", i, array[i]);
  }
}
