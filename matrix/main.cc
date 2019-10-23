//
// @file main.cc
// @brief Matrix text.
// @author Mamoru Kaminaga
// @date 2019-10-22 17:50:59
// Copyright 2019 Mamoru Kaminaga
//
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "./matrix.h"
#define _CRTDBG_MAP_ALLOC

namespace {
void seq(mk::matrix<int>* m) {
  for (size_t i = 0; i < m->row(); i++) {
    for (size_t j = 0; j < m->column(); j++) {
      (*m)[i][j] = i * m->column() + j;
    }
  }
}

void show_data(const mk::matrix<int>& m) {
  wprintf(L"data information\n");
  wprintf(L"Total capacity = %d, Total size = %d\n", m.capacity(), m.size());
  wprintf(L"Row capacity = %d, Column capacity = %d\n", m.row_capacity(),
          m.column_capacity());
  wprintf(L"Row size = %d, Column size = %d\n", m.row(), m.column());
  wprintf(L"----\n");
  for (size_t i = 0; i < m.row(); i++) {
    wprintf(L"  ");
    for (size_t j = 0; j < m.column(); j++) {
      wprintf(L"%5d", m[i][j]);
    }
    wprintf(L"\n");
  }
  wprintf(L"\n");
}

void show_addr(const mk::matrix<int>& m) {
  wprintf(L"address information\n");
  wprintf(L"Total capacity = %d, Total size = %d\n", m.capacity(), m.size());
  wprintf(L"Row capacity = %d, Column capacity = %d\n", m.row_capacity(),
          m.column_capacity());
  wprintf(L"Row size = %d, Column size = %d\n", m.row(), m.column());
  wprintf(L"----\n");
  for (size_t i = 0; i < m.row_capacity(); i++) {
    wprintf(L"  ");
    for (size_t j = 0; j < m.column_capacity(); j++) {
      wprintf(L"%9p", &(m[i][j]));
    }
    wprintf(L"\n");
  }
  wprintf(L"\n");
}

}  // namespace

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  {
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1);

    wprintf(L"constructor\n");
    mk::matrix<int> m(3, 4);
    m[0][0] = 0;
    m[1][1] = 1;
    m[2][2] = 2;
    seq(&m);
    show_data(m);
    show_addr(m);

    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2)) {
      _CrtMemDumpStatistics(&s3);
    }
  }

  return 0;
}
