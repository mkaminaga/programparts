//
// @file util.cc
// @brief Matrix text.
// @author Mamoru Kaminaga
// @date 2019-10-23 17:57:12
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include "./matrix.h"

namespace mk {

void seq(mk::matrix<int>* m) {
  for (size_t i = 0; i < m->row(); i++) {
    for (size_t j = 0; j < m->column(); j++) {
      (*m)[i][j] = i * m->column() + j;
    }
  }
}

void show_capacity(const mk::matrix<int>& m) {
  wprintf(L"capacity:\n");
  wprintf(L"row = %d, column = %d\n", m.row_capacity(), m.column_capacity());
}

void show_size(const mk::matrix<int>& m) {
  wprintf(L"size:\n");
  wprintf(L"row = %d, column = %d\n", m.row(), m.column());
}

void show_data(const mk::matrix<int>& m) {
  wprintf(L"data:\n");
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
  wprintf(L"address:\n");
  for (size_t i = 0; i < m.row_capacity(); i++) {
    wprintf(L"  ");
    for (size_t j = 0; j < m.column_capacity(); j++) {
      wprintf(L"%9p", &(m.data()[i][j]));
    }
    wprintf(L"\n");
  }
  wprintf(L"\n");
}

}  // namespace mk
