//
// @file util.h
// @brief Combo box test.
// @author Mamoru Kaminaga
// @date 2019-12-25 19:02:14
// Copyright 2019 Mamoru Kaminaga
//
#include "./util.h"
#include <windows.h>

namespace mk {

bool OpenConsole() {
  FILE* fp = nullptr;
  AllocConsole();
  freopen_s(&fp, "CONOUT$", "w", stdout);
  freopen_s(&fp, "CONOUT$", "w", stderr);
  freopen_s(&fp, "CONIN$", "r", stdin);
  return true;
}

void CloseConsole() {
  FreeConsole();
  return;
}

}  // namespace mk
