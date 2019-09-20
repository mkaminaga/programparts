//
// @file util.h
// @brief Test project for screen capture.
// @author Mamoru Kaminaga
// @date 2019-09-20 12:51:16
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <png.h>
#include <stdint.h>
#include <wchar.h>
#include <windows.h>
#include <vector>

struct PNGData {
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int bit_depth;
  int filter_type;
  int compression_type;
  int interlace_type;
  int rowbytes;
  int channels;
  // Pixels are read from PNG data.
  // This sample only supports RGBA format.
  std::vector<uint8_t> red_buffer;
  std::vector<uint8_t> green_buffer;
  std::vector<uint8_t> blue_buffer;
  std::vector<uint8_t> alpha_buffer;
};

bool WritePNGFile(const wchar_t *file_name, const PNGData &png_data);

enum TESTCASE {
  TESTCASE_PAINT_DESKTOP,
  TESTCASE_PAINT_WINDOW,
  TESTCASE_BITBLT,
};

bool ScreenToPNG(TESTCASE test_case, PNGData *png_data);

#endif  // _UTIL_H_
