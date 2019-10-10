//
// @file main.cc
// @brief Argument list test.
// @author Mamoru Kaminaga
// @date 2019-10-08 20:28:30
// Copyright 2019 Mamoru Kaminaga
//
#include <stdarg.h>
#include <stdio.h>

void print_va_collect(int arg0, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, arg0);
  printf("va 0:%d\n", va_arg(arg_ptr, int));
  printf("va 1:%f\n", va_arg(arg_ptr, double));  // Correct code.
  printf("va 2:%f\n", va_arg(arg_ptr, double));
  printf("va 3:%c\n", va_arg(arg_ptr, char));
  printf("arg5:%s\n", va_arg(arg_ptr, const char*));
  va_end(arg_ptr);
}

void print_va_wrong(int arg0, ...) {
  va_list arg_ptr;
  va_start(arg_ptr, arg0);
  printf("va 0:%d\n", va_arg(arg_ptr, int));
  printf("va 1:%f\n", va_arg(arg_ptr, float));  // Wrong code.
  printf("va 2:%f\n", va_arg(arg_ptr, double));
  printf("va 3:%c\n", va_arg(arg_ptr, char));
  // printf("arg5:%s\n", va_arg(arg_ptr, const char*));  // Segmentation Fault.
  va_end(arg_ptr);
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;

  printf("\n");
  printf("collect:\n");
  print_va_collect(0, 128, 0.1F, 0.2L, 'a', "abc");

  printf("\n");
  printf("wrong:\n");
  print_va_wrong(0, 128, 0.1F, 0.2L, 'a', "abc");

  return 0;
}
