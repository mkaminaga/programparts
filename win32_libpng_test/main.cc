//
// @file main.cc
// @brief Template project for Windows desktop application.
// @author Mamoru Kaminaga
// @date 2019-09-16 18:51:54
// Copyright 2019 Mamoru Kaminaga
//
#include <png.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "./util.h"

namespace {
constexpr wchar_t WINDOW_NAME[] = L"Template window";
constexpr wchar_t CLASS_NAME[] = L"Template class";
}  // namespace

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  fwprintf(stderr, L"libpng test program.\n");
  fwprintf(stderr, L"\n");

  ////////////////////////////////////////
  // PNG file is opened.
  ////////////////////////////////////////
  FILE* fp = NULL;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;
  if (!OpenPNG(L"src_img.png", &fp, &png_ptr, &info_ptr)) {
    return 1;
  }

  ////////////////////////////////////////
  // Information is read from data.
  ////////////////////////////////////////
  volatile png_bytep row = NULL;  // Volatile access for setjmp().
  png_bytep row_tmp = NULL;

  if (setjmp(png_jmpbuf(png_ptr)) != 0) {
    fwprintf(stderr, L"WARNING... longjmp() is called for internal error.\n");
    if (!row) {
      row_tmp = row;
      row = NULL;
      png_free(png_ptr, row_tmp);
    }
    ClosePNG(fp, &png_ptr, &info_ptr);
    return false;
  }

  row = (png_bytep)png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));
  row_tmp = row;  // To reduce the load of access to nonvolatile variable.

  png_uint_32 width = 0;
  png_uint_32 height = 0;
  int bit_depth = 0;
  int color_type = 0;
  int interlace_method = 0;
  int compression_method = 0;
  int filter_method = 0;

  if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                    &interlace_method, &compression_method, &filter_method)) {
    fwprintf(stderr, L"ERROR... Failed to get header information.\n");
    ClosePNG(fp, &png_ptr, &info_ptr);
    return 1;
  }
  PrintPNGInfo(stderr, width, height, bit_depth, color_type, interlace_method,
               compression_method, filter_method);
  fwprintf(stderr, L"\n");

  ////////////////////////////////////////
  // PNG file is closed.
  ////////////////////////////////////////
  ClosePNG(fp, &png_ptr, &info_ptr);

  fwprintf(stderr, L"src_img.png => dst_img.png\n");
  return 0;
}
