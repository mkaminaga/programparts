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
#include "./util.h"
#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  {
    _CrtMemState s1, s2, s3;
    _CrtMemCheckpoint(&s1);

    wprintf(L"\n");

    mk::matrix<int> m;
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    // Test for capacity.
    // new row > 0 && new column > 0.
    execute(m.reserve(2, 2));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    // Test for capacity.
    // new row <= old row && new column <= old column.
    execute(m.reserve(1, 1));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    // Test for capacity.
    // new row == old row && new column < old column.
    execute(m.reserve(2, 10));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

#if 0
    // Test for capacity.
    // new row > old row && new column == old column.
    execute(m.reserve(3, 3));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    // Test for capacity.
    // new row > old row && new column > old column.
    execute(m.reserve(4, 4));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    execute(m.resize(1, 1));
    execute(mk::seq(&m));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);

    execute(m.resize(3, 4));
    execute(mk::seq(&m));
    mk::show_capacity(m);
    mk::show_size(m);
    mk::show_addr(m);
#endif

    _CrtMemCheckpoint(&s2);
    if (_CrtMemDifference(&s3, &s1, &s2)) {
      _CrtMemDumpStatistics(&s3);
    }
  }

  return 0;
}
