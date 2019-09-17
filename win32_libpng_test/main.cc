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

  // Modify image.
  // for (int i = 0; i < static_cast<int>(png_data.width * png_data.height); ++i) {
  //   png_data.red_buffer[i] = 0;
  //   png_data.green_buffer[i] = static_cast<uint8_t>((png_data.red_buffer[i] +
  //                                                    png_data.green_buffer[i] +
  //                                                    png_data.blue_buffer[i]) /
  //                                                   (255.0 * 3));
  //   png_data.blue_buffer[i] = 0;
  //   png_data.alpha_buffer[i] = 255;
  // }
  png_data.interlace_type = PNG_INTERLACE_NONE;

  // Write image data to PNG file.
  if (!WritePNGFile(L"dst_img.png", png_data)) {
    fwprintf(stderr, L"WritePNGFile() failed.\n");
    return 1;
  }
  fwprintf(stderr, L"\n");

  fwprintf(stderr, L"src_img.png => dst_img.png\n");
  return 0;
}

