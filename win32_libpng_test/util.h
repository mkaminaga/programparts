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
bool OpenPNG(const wchar_t* file_name, FILE** fp_out, png_structp* png_ptr_out,
             png_infop* info_ptr_out);
void ClosePNG(FILE* fp, png_structpp png_ptrptr, png_infopp info_ptrptr);

void PrintPNGInfo(FILE* fp, png_uint_32 width, png_uint_32 height,
                  int bit_depth, int color_type, int interlace_method,
                  int compression_method, int filter_method);

#endif  // _UTIL_H_
