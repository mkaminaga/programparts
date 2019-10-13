//
// @file main.cc
// @brief
// @author
// @date 2019-10-13 17:41:15
// Copyright 2019
//
#include <stdio.h>
#include <windows.h>

#define show(EXPRESSION) (_show(#EXPRESSION, (EXPRESSION)))
void _show(const char* text, unsigned __int64 p) {
  printf("%s\n", text);
  printf("  %I64d (0x%I64x)\n", p, p);
  printf("\n");
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  printf("\n");
  printf("++++++++++ Type ++++++++\n");

  // synonym of unsigned __int64.
  ULONGLONG a;
  show(a = 0x0123456789abcdef);
  printf("\n");

  // Union including ULONGLONG.
  ULARGE_INTEGER b;
  show(b.QuadPart = a);
  show(b.LowPart);
  show(b.HighPart);
  printf("\n");

  // FILETIME structure.
  FILETIME c;
  show(c.dwLowDateTime = (DWORD)(a & 0xffffffff));
  show(c.dwHighDateTime = (DWORD)(a >> 32));
  show(((unsigned __int64)c.dwHighDateTime << 32) | c.dwLowDateTime);
  show((unsigned)(c.dwHighDateTime << 32) | c.dwLowDateTime);
  show((c.dwHighDateTime << 32) | c.dwLowDateTime);
  printf("\n");

  printf("++++++++++ Addition ++++++++\n");
  unsigned int p = 0x10000000;
  unsigned int q = 0xffffffff;

  printf("p = 0x%8x\n", p);
  printf("q = 0x%8x\n", q);
  printf("\n");

  show(p + q);
  show((unsigned __int64)p + q);
  show((unsigned __int64)(p + q));
  show((unsigned __int64)p + (unsigned __int64)q);

  printf("********** Multiply ********\n");
  unsigned int r = 0x80000000;
  unsigned int s = 2;
  printf("r = 0x%8x\n", r);
  printf("s = %d\n", s);
  printf("\n");

  show(p * r);
  show((unsigned __int64)p * r);
  show((unsigned __int64)(p * r));
  show((unsigned __int64)p * (unsigned __int64)r);

  return 0;
}
