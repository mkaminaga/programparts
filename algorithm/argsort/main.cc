//
// @file main.cc
// @brief Test of sort of indices.
// @author Mamoru Kaminaga
// @date 2019-11-03 10:38:13
// Copyright 2019 Mamoru Kaminaga
//
#include <stdint.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  std::vector<int> data = {7, 5, 4, 9, 2, 8, 3, 1, 6, 0};
  std::vector<size_t> index(data.size());
  std::iota(index.begin(), index.end(), 0);

  wprintf(L"original data\n");
  for (auto& it : index) {
    wprintf(L"  data[%d] = %d\n", it, data[it]);
  }
  wprintf(L"\n");

  // Ascending sort.
  std::sort(index.begin(), index.end(),
            [&data](size_t l, size_t r) { return data[l] < data[r]; });

  wprintf(L"ascending order\n");
  for (auto& it : index) {
    wprintf(L"  data[%d] = %d\n", it, data[it]);
  }
  wprintf(L"\n");

  // Descending sort.
  std::sort(index.begin(), index.end(),
            [&data](size_t l, size_t r) { return data[l] > data[r]; });

  wprintf(L"descending order\n");
  for (auto& it : index) {
    wprintf(L"  data[%d] = %d\n", it, data[it]);
  }
  wprintf(L"\n");

  return 0;
}
