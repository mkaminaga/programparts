//
// @file util.cc
// @brief Matrix text.
// @author Mamoru Kaminaga
// @date 2019-10-23 17:57:12
// Copyright 2019 Mamoru Kaminaga
//
#include <stdio.h>
#include "./matrix.h"

#define execute(EXPRESSION)       \
  {                               \
    wprintf(L"%s\n", L#EXPRESSION); \
    EXPRESSION;                   \
  }

namespace mk {

void seq(mk::matrix<int>* m);
void show_capacity(const mk::matrix<int>& m);
void show_size(const mk::matrix<int>& m);
void show_data(const mk::matrix<int>& m);
void show_addr(const mk::matrix<int>& m);

}  // namespace mk
