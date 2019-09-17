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
void ClosePNG(FILE* fp, png_structp png_ptr, png_infop info_ptr);

#endif  // _UTIL_H_
