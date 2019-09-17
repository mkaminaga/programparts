//
// @file util.h
// @brief Test for libpng.
// @author Mamoru Kaminaga
// @date 2019-09-16 18:54:54
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _UTIL_H_
#define _UTIL_H_

#include <png.h>
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

bool ReadPNGFile(const wchar_t *file_name, PNGData *png_data);
bool WritePNGFile(const wchar_t *file_name, const PNGData &png_data);
void PrintPNGData(FILE *fp, const PNGData &png_data);

#endif  // _UTIL_H_
