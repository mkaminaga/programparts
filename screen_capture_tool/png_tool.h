//
// @file png_tool.h
// @brief libpng wrapper functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#ifndef _PNG_TOOL_H_
#define _PNG_TOOL_H_

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
  // Pixel buffer for RGBA format.
  std::vector<uint8_t> red_buffer;
  std::vector<uint8_t> green_buffer;
  std::vector<uint8_t> blue_buffer;
  std::vector<uint8_t> alpha_buffer;
};

bool WritePNGFile(const wchar_t *file_name, const PNGData &png_data);

#endif  // _PNG_TOOL_H_
