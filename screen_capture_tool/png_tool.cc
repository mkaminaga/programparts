//
// @file png_tool.cc
// @brief libpng wrapper functions.
// @author Mamoru Kaminaga
// @date 2019-09-21 18:22:39
// Copyright 2019 Mamoru Kaminaga
//
#include "./png_tool.h"
#include <assert.h>
#include <png.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>
#include <vector>

bool WritePNGFile(const wchar_t *file_name, const PNGData &png_data) {
  assert(file_name);

  FILE *fp = NULL;
  _wfopen_s(&fp, file_name, L"wb");
  if (!fp) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to open file.\n");
#endif
    return false;
  }

  // Memory initialization.
  png_structp png_ptr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate png_struct.\n");
#endif
    fclose(fp);
    return false;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate info_ptr.\n");
#endif
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return false;
  }

  // Error handling with setjmp/longjmp.
  if (setjmp(png_jmpbuf(png_ptr))) {
#ifdef DEBUG
    fwprintf(stderr, L"WARNING... longjmp() is called by libpng.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  // File pointer is set.
  png_init_io(png_ptr, fp);

  // Get access to some of the IHDR settings.
  png_set_IHDR(png_ptr, info_ptr, png_data.width, png_data.height,
               png_data.bit_depth, png_data.color_type, png_data.interlace_type,
               png_data.compression_type, png_data.filter_type);

  // Image buffer is created.
  png_bytepp rows =
      (png_bytepp)png_malloc(png_ptr, sizeof(png_bytep) * png_data.height);
  if (!rows) {
#ifdef DEBUG
    fwprintf(stderr, L"ERROR... Failed to allocate rows.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  memset(rows, 0, sizeof(png_bytep) * png_data.height);
  bool alloc_is_ok = true;
  for (int y = 0; y < static_cast<int>(png_data.height); y++) {
    rows[y] = (png_byte *)png_malloc(png_ptr, png_data.rowbytes);
    if (!rows[y]) {
#ifdef DEBUG
      fwprintf(stderr, L"ERROR... Failed to allocate rows[%d].\n", y);
#endif
      alloc_is_ok = false;
      break;
    }
  }
  if (!alloc_is_ok) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  // Pixels are written to in RGBA format.
  if (png_data.color_type != PNG_COLOR_TYPE_RGBA) {
#ifdef DEBUG
    fwprintf(stderr, L"color_type is not PNG_COLOR_TYPE_RGBA, exit.\n");
#endif
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  png_bytep row = NULL;
  for (int y = 0; y < static_cast<int>(png_data.height); y++) {
    row = rows[y];
    for (int x = 0; x < static_cast<int>(png_data.width); x++) {
      *(row++) =
          static_cast<png_byte>(png_data.red_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.green_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.blue_buffer[y * png_data.width + x]);
      *(row++) =
          static_cast<png_byte>(png_data.alpha_buffer[y * png_data.width + x]);
    }
  }

  // Reflect buffered image to info structure.
  png_set_rows(png_ptr, info_ptr, rows);

  // Data access by high-level write interface.
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  // Memory finalization.
  if (!rows) {
    for (int y = 0; y < static_cast<int>(png_data.height); y++) {
      if (!rows[y]) {
        png_free(png_ptr, rows[y]);
      }
    }
    png_free(png_ptr, rows);
  }

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);
  return true;
}
