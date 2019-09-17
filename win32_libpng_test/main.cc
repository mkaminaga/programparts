//
// @file main.cc
// @brief Template project for Windows desktop application.
// @author Mamoru Kaminaga
// @date 2019-09-16 18:51:54
// Copyright 2019 Mamoru Kaminaga
//
#include <png.h>
#include <stdint.h>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <vector>
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

  // Read image data from PNG file.
  PNGData png_data;
  if (!ReadPNGFile(L"src_img.png", &png_data)) {
    fwprintf(stderr, L"ReadPNGFile() failed.\n");
    return 1;
  }
  PrintPNGData(stderr, png_data);
  fwprintf(stderr, L"\n");

  // Show corner colors.
  fwprintf(stderr, L"(%d,%d), (%d,%d,%d)\n", 0, 0, png_data.red_buffer[0],
           png_data.green_buffer[0], png_data.blue_buffer[0]);
  fwprintf(stderr, L"(%d,%d), (%d,%d,%d)\n", png_data.width-1, 0,
           png_data.red_buffer[png_data.width-1],
           png_data.green_buffer[png_data.width-1],
           png_data.blue_buffer[png_data.width-1]);
  fwprintf(stderr, L"(%d,%d), (%d,%d,%d)\n", 0, png_data.height-1,
           png_data.red_buffer[png_data.width * (png_data.height - 1)],
           png_data.green_buffer[png_data.width * (png_data.height - 1)],
           png_data.blue_buffer[png_data.width * (png_data.height - 1)]);
  fwprintf(stderr, L"(%d,%d), (%d,%d,%d)\n", png_data.width, png_data.height,
           png_data.red_buffer[png_data.width * png_data.height - 1],
           png_data.green_buffer[png_data.width * png_data.height - 1],
           png_data.blue_buffer[png_data.width * png_data.height - 1]);
  fwprintf(stderr, L"\n");

  // Modify image.
  for (int i = 0; i < static_cast<int>(png_data.width * png_data.height); ++i) {
    png_data.red_buffer[i] /= 4;
    png_data.blue_buffer[i] /= 4;
    png_data.alpha_buffer[i] = 255;
  }
  png_data.interlace_type = PNG_INTERLACE_NONE;

  // Write image data to PNG file.
  if (!WritePNGFile(L"dst_img.png", png_data)) {
    fwprintf(stderr, L"WritePNGFile() failed.\n");
    return 1;
  }

  fwprintf(stderr, L"src_img.png => dst_img.png\n");
  return 0;
}

